#include "assign2Headers.h"

int answererPid, guesserPid;
int shouldRun = 1;

void alrmHandler(int signum) {
	kill(answererPid, TIME_OVER_SIGNAL);
	kill(guesserPid, TIME_OVER_SIGNAL);
	shouldRun = 0;
}

void chldHandler(int signum) {
	pid_t childId = 0;
	do {
		int* statusPtr;
		childId = waitpid(-1, statusPtr, 0); 
	} while (childId > 0);
	
	shouldRun = 0;
}

int main() {
	
	struct sigaction alrmAct;
	memset(&alrmAct, '\0', sizeof(alrmAct));
	alrmAct.sa_handler = alrmHandler;
	sigaction(SIGALRM, &alrmAct, NULL);

	struct sigaction chldAct;
	memset(&chldAct, '\0', sizeof(chldAct));
	chldAct.sa_handler = chldHandler;
	sigaction(SIGCHLD, &chldAct, NULL);
	
	answererPid = fork();
	if (answererPid == 0) {
		execl(ANSWERER_PROGNAME, ANSWERER_PROGNAME, NULL);
	}
		
	guesserPid = fork();
	if (guesserPid == 0) {
		char line[LINE_LEN];
		snprintf(line, LINE_LEN, "%d", answererPid);
		execl(GUESSER_PROGNAME, GUESSER_PROGNAME, line, NULL);
	}
	
	alarm(NUM_SECONDS);

	while (shouldRun)
		sleep(1);
	
	sleep(1);
	sleep(1);

	printf("launcher finished\n");
	return(EXIT_SUCCESS);
}
