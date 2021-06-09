/*-------------------------------------------------------------------------*
 *---									---*
 *---		NodeBuffer.h						---*
 *---									---*
 *---	    This file defines a class that implements a thread-safe 	---*
 *---	buffer of pointers to math expressions.				---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a		2018 February 22	Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

pthread_mutex_t lock;

class   NodeBuffer
{
  enum { SIZE   = 16 };

  Node*   array_[SIZE];
  int   inIndex_;
  int   outIndex_;
  int   numItems_;
  pthread_mutex_t lock;
  pthread_cond_t readyToTake;
  pthread_cond_t readyToAdd;

public :

  NodeBuffer        ()
  {
    for  (int i = 0;  i < SIZE;  i++)
    {
      array_[i]	= NULL;
    }

    inIndex_ = outIndex_ = numItems_ = 0;
    pthread_mutex_init(&lock, NULL);  
    pthread_cond_init(&readyToTake, NULL);
    pthread_cond_init(&readyToAdd, NULL);
    printf("NodeBuffer created\n"); //todo: delete
  }

  ~NodeBuffer       ()
  {
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&readyToTake);
    pthread_cond_destroy(&readyToAdd);
    printf("NodeBuffer destroyed\n"); //todo: delete
  }

  int   getNumItems  () const
  { return(numItems_); }

  void  putIn (Node* nodePtr)
  {
    pthread_mutex_lock(&lock);
    while ((getNumItems() >= SIZE))
      pthread_cond_wait(&readyToAdd, &lock);
    array_[inIndex_] = nodePtr;
    inIndex_++;
    numItems_++;
    if (inIndex_ >= SIZE)
      inIndex_ = 0;
    pthread_cond_signal(&readyToTake);
    pthread_mutex_unlock(&lock);
  }

  Node*   pullOut ()
  {
    pthread_mutex_lock(&lock);
    while ((getNumItems() <= 0))  
      pthread_cond_wait(&readyToTake, &lock);
    Node* toReturn        = array_[outIndex_];
    array_[outIndex_]	  = NULL;
    outIndex_++;
    numItems_--;
    if (outIndex_ >= SIZE)
      outIndex_ = 0;
    pthread_cond_signal(&readyToAdd);
    pthread_mutex_unlock(&lock);
    
    return(toReturn);
  }
};
