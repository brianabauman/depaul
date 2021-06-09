/*-------------------------------------------------------------------------*
 *---									---*
 *---		mathSolver.cpp						---*
 *---									---*
 *---	    This file defines the high-level functions of the math 	---*
 *---	generator and solver program.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 February 22	Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//
//	Compile with:
//	$ g++ mathSolver.cpp -o mathSolver -lpthread -g
//


#include	"mathSolverHeader.h"
#include	<unistd.h>

void*		evaluate	(void*		vPtr
				)
{
  NodeBuffer*	nodeBufferPtr	= (NodeBuffer*)vPtr;

  //  YOUR CODE HERE
  int i;
  for (i = 0; i < NUM_PROBLEMS / 2; i++) {
    Node* thisNode = nodeBufferPtr->pullOut();
    printf("iteration: %d, expression: %s, evaluation: %f\n", i, thisNode->toString().c_str(), thisNode->eval());
    delete(thisNode);
  }

  return(NULL);
}


//  PURPOSE:  To return a randomly generated Node.
Node*		makeNode	()
{
  return( (rand() % 3) ? (Node*)new ConstNode() : (Node*)new OperatorNode() );
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  NodeBuffer	nodeBuffer;
  pthread_t	consumer0;
  pthread_t	consumer1;
  int		toReturn	= EXIT_SUCCESS;

  srand( (argc < 2) ? getpid() : atoi(argv[1]) );

  //  YOUR CODE HERE
  pthread_create(&consumer0, NULL, evaluate, (void*)&nodeBuffer);
  pthread_create(&consumer1, NULL, evaluate, (void*)&nodeBuffer);
  
  int i;
  for (i = 0; i < NUM_PROBLEMS; i++) {
    printf("Made %d\n", i);    
    Node* newNode = makeNode();
    nodeBuffer.putIn(newNode);
  }

  pthread_join(consumer0, (void**)NULL);
  pthread_join(consumer1, (void**)NULL);

  return(toReturn);
}
