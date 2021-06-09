/*-------------------------------------------------------------------------*
 *---									---*
 *---		server_getFileByFirstLetter.c				---*
 *---									---*
 *---	    This file defines a C program that waits for a client to	---*
 *---	connect, gets a letter from the client, and looks for a file in	---*
 *---	the current directory that begins with that letter.  If it	---*
 *---	finds such a file then it sends the length of the file back as	---*
 *---	a network-endian 32-bit unsigned integer, followed by the text	---*
 *---	of the file.  Sends back the appropriate error integer code	---*
 *---	otherwise.
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1.0		2018 March 5		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

/*---		Header file inclusion					---*/

#include	"getFileByFirstLetter.h"
#include	<signal.h>		// For sigaction()
#include	<wait.h>		// For waitpid()
#include	<dirent.h>		// For opendir(), readdir(), closedir()

const int	LO_LEGAL_PORT	= 1025;
const int	HI_LEGAL_PORT	= 65535;
const int	ERROR_FD	= -1;
const int	NUM_CLIENTS_TO_SERVE
				= 4;

//  PURPOSE:  To get zombie children.  Ignores 'sig' (which will be 'SIGCHLD').
//	No return value.
void		sigChildHandler	(int	sig
				)
{
  //  I.  Application validity check:

  //  II.  Get all zombie children:
  pid_t pid;
  int s;
  while ((pid = waitpid(-1, &s, WNOHANG)) > 0)
    if (WIFEXITED(s) == 0)
      printf("%d crashed!\n", pid);

  //  III.  Finished:
}

//  PURPOSE:  To attempt to create and return a file-descriptor for listening
//	to the OS telling this server when a client process has connect()-ed
//	to 'port'.  Returns that file-descriptor, or 'ERROR_FD' on failure.
int		getServerFileDescriptor
				(int		port,
				 const char*	progName
				)
{
  //  I.  Application validity check:
  if  (progName == NULL)
  {
    fprintf(stderr,"BUG: NULL ptr to getServerFileDescriptor().\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Attempt to get socket file descriptor and bind it to 'port':
  //  II.A.  Create a socket
  int socketDescriptor = socket(AF_INET, // AF_INET domain
			        SOCK_STREAM, // Reliable TCP
			        0);

  if  (socketDescriptor < 0)
  {
    perror(progName);
    return(ERROR_FD);
  }

  //  II.B.1.  We'll fill in this datastruct
  struct sockaddr_in socketInfo;

  //  II.B.2.  Fill socketInfo with 0's
  memset(&socketInfo,'\0',sizeof(socketInfo));

  //  II.B.3.  Use TCP/IP:
  socketInfo.sin_family = AF_INET;

  //  II.B.4.  Tell port in network endian with htons()
  socketInfo.sin_port = htons(port);

  //  II.B.5.  Allow machine to connect to this service
  socketInfo.sin_addr.s_addr = INADDR_ANY;

  //  II.B.6.  Try to bind socket with port and other specifications
  int status = bind(socketDescriptor, // from socket()
		    (struct sockaddr*)&socketInfo,
		    sizeof(socketInfo)
		   );

  if  (status < 0)
  {
    perror(progName);
    return(ERROR_FD);
  }

  //  II.B.6.  Set OS queue length:
  listen(socketDescriptor,5);

  //  III.  Finished:
  return(socketDescriptor);
}


//  PURPOSE:  To install 'sigChildHandler()' as the signal simple handler for
//	the 'SIGCHLD' signal.  Tells OS to restarts system calls if receives
//	'SIGCHLD'.
void	installSigChildHandler	()
{
  //  I.  Application validity check:

  //  II.  Install 'sigChildHandler()' as the 'SIGCHLD' handler:
  struct sigaction act;
  memset(&act,'\0',sizeof(struct sigaction));
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_NOCLDSTOP | SA_RESTART;;
  act.sa_handler = sigChildHandler;
  sigaction(SIGCHLD, &act, NULL);  
  
  //  III.  Finished:
}


//  PURPOSE:  To ask the user which port to attempt to monopolize, and to return
//	entered port number.
int		getPort		()
{
  //  I.  Application validity check:

  //  II.  Get port number
  int	port;

  do
  {
    char	buffer[BUFFER_LEN];

    printf("Please enter port number to monopolize [%d-%d]: ",
	   LO_LEGAL_PORT,HI_LEGAL_PORT
	  );
    fgets(buffer,BUFFER_LEN,stdin);
    port = strtol(buffer,NULL,10);
  }
  while  ( (port < LO_LEGAL_PORT)  ||  (port > HI_LEGAL_PORT) );

  //  III.  Finished:
  return(port);
}



//  PURPOSE:  To do the work of handling the client.  Communication with the
//	client take place using file-descriptor 'fd'.  No return value.
void		handleClient	(int	fd
				)
{
  //  I.  Application validity check:
  if  (fd < 0)
  {
    fprintf(stderr,"BUG: Illegal file descriptor to handleClient()\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Handle the client:
  char letter[BUFFER_LEN];
  read(fd, letter, BUFFER_LEN);
  
  const char* dirName = ".";
  DIR* dirPtr = opendir(dirName);

  if (dirPtr == NULL)
  {
    uint32_t returnCode = htonl(CANT_READ_DIR_CODE);
    char* returnChar = (char*)&returnCode;

    write(fd, returnChar, sizeof(returnCode));
    printf("Can't read directory\n");
    return;
  }

  char fileFound = 0;

  struct dirent* entryPtr;
  struct stat statBuffer;
  char entryPath[BUFFER_LEN];

  while ((entryPtr = readdir(dirPtr)) != NULL)
  {
    char* name = entryPtr->d_name;
    snprintf(entryPath, BUFFER_LEN, "%s/%s", dirName, name);
    stat(entryPath, &statBuffer);
      
    if (S_ISREG(statBuffer.st_mode))
      if (letter[0] == *name) 
      {
        fileFound = 1;
        FILE* filePtr = fopen(entryPath, "r");
        
        if (filePtr == NULL)
        {
          uint32_t returnCode = htonl(CANT_READ_FILE_CODE);
          char* returnChar = (char*)&returnCode;

          write(fd, returnChar, sizeof(returnCode));
          printf("Cannot read file %s\n", name);  
          return;
        }
        
        uint32_t fileSize = statBuffer.st_size;
        printf("Sending %s, %d bytes\n", name, fileSize);

        uint32_t returnSize = htonl(fileSize);
        char* returnChar = (char*)&returnSize;

        write(fd, returnChar, sizeof(returnSize));
        
        int fileFd = open(entryPath, O_RDONLY, 0660);
       
        char buffer[BUFFER_LEN];
        int bytesRead;
        while ((bytesRead = read(fileFd, buffer, BUFFER_LEN)) > 0)
        {
          write(fd, buffer, bytesRead); 
        }     
      
        close(fileFd);
        close(fd);
        break;
      }
  } 

  if (!fileFound)
  {
      uint32_t returnCode = htonl(NO_MATCH_CODE);
      char* returnChar = (char*)&returnCode;

      write(fd, returnChar, sizeof(returnCode));
      printf("No file found\n");
      return;
  }  

  closedir(dirPtr);

  //  III.  Finished:
}


//  PURPOSE:  To serve the clients using file-descriptor 'listenFd' to tell
//	when a client has connected.  Each client is handled by its own child
//	process.  Both the parent and the child processes close unnecesary
//	file-descriptorors.  Serves 'NUM_CLIENTS_TO_SERVE' clients, then quits.
//	No return value.
void	       	doServer  	(int  	 	listenFd
				)
{
  //  I.  Application validity check:
  if  (listenFd < 0)
  {
    fprintf(stderr,"Illegal file-descriptor to doServer()\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Do the work of the server:
  int	i;

  for  (i = 0;  i < NUM_CLIENTS_TO_SERVE;  i++)
  {
    int clientFd = accept(listenFd, NULL, NULL);
    
    if (fork() == 0)
    {
      close(listenFd);
      handleClient(clientFd);
      exit(EXIT_SUCCESS);
    } 

    close(clientFd); 
  }

  //  III.  Finished:
}


//  PURPOSE:  To oversee the main work of the server.  Ignores 'argc' but
//	uses 'argv[0]' as the name of the program.  Returns 'EXIT_SUCCESS' to
//	OS on success or 'EXIT_FAILURE' otherwise.
int		main		(int		argc,
				 char*		argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Do server:
  int	port		= getPort();
  int	socketFd	= getServerFileDescriptor(port,argv[0]);

  installSigChildHandler();
  doServer(socketFd);

  //  III.  Finished:
  return(EXIT_SUCCESS);
}
