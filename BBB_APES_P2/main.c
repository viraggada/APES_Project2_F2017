/*****************************************************
 * File: main.c
 * Authors: Virag Gada and Vihanga Bare
 * Description: Source file for APES Project 2 on BBB
 ****************************************************/

#include "main.h"

int main()
{
  int32_t retval = 0;

	retval = pthread_create(&socketThread,NULL,&SocketThread,NULL);
	if(retval != 0)
	{
		printf("Thread Creation failed, error code - %d\n", retval);
		pinSet(led_path);
	}

	while(1){

	}
	
	return 0;
}
