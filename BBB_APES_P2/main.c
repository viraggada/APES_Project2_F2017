/*****************************************************
 * File: main.c
 * Authors: Virag Gada and Vihanga Bare
 * Description: Source file for APES Project 2 on BBB
 ****************************************************/

#include "main.h"

int main()
{
  int32_t retval = 0;

  /* Initialize all locks */
  pthread_mutex_init(&decisionQ_mutex,NULL);
  pthread_mutex_init(&logQ_mutex,NULL);
  //pthread_mutex_init(&mainQ_mutex,NULL);

  /* Initialize all the queues */
  initialize_queue(QLog,&logger_queue_handle);
  initialize_queue(QDecide,&decision_queue_handle);
  //initialize_queue(QMain,&main_queue_handle);

  retval = pthread_create(&loggerThread,NULL,&LoggerThread,NULL);
	if(retval != 0)
	{
		printf("Thread Creation failed, error code - %d\n", retval);
		pinSet(led_path);
	}
  sleep(1);

	retval = pthread_create(&socketThread,NULL,&SocketThread,NULL);
	if(retval != 0)
	{
		printf("Thread Creation failed, error code - %d\n", retval);
		pinSet(led_path);
	}
  sleep(1);

  retval = pthread_create(&decisionThread,NULL,&DecisionThread,NULL);
  if(retval != 0)
  {
    printf("Thread Creation failed, error code - %d\n", retval);
    pinSet(led_path);
  }
	while(1){

	}

	return 0;
}
