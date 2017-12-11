/*****************************************************
 * File: loggerThread.c
 * Authors: Virag Gada and Vihanga Bare
 * Description: Source file for logger task
 ****************************************************/

#include "main.h"
#include "logger.h"


#define BUFFER_SIZE (50)

struct mq_attr attr;
FILE *logFile;

void *LoggerThread(void *args)
{
  uint32_t msgPriority;
  LogMsg *logmsg1;
  uint32_t bytes_read;
  char command[BUFFER_SIZE] = {(int)'\0'};
  printf("Log file create status - %d,\n", create_log_file(&logFile, "dataLog"));

  if(create_log_struct(&logmsg1)!=DONE){
		printf("%s\n","Error creating struct");
	}else{
    while(1){
      mq_getattr(logger_queue_handle, &attr);
      while(attr.mq_curmsgs > 0)
				{
					pthread_mutex_lock(&logQ_mutex);
					//bytes_read = mq_receive(logger_queue_handle, (char *)&logmsg1, sizeof(LogMsg)+1, &msgPriority);
          bytes_read = mq_receive(logger_queue_handle, (char *)&command,BUFFER_SIZE , &msgPriority);
					if (bytes_read == -1)
					{
						perror("LoggerThread] Failed to recieve:");
					}
					else
					{
						printf("[LoggerThread] Queue %s currently holds %ld messages\n",QLog,attr.mq_curmsgs);
						mq_getattr(logger_queue_handle, &attr);
						/*if(logmsg1->requestID == LOG_DATA)
						{
							printf("Logging status -%d\n",log_item(logFile,logmsg1) );
							printf ("[LoggerThread] source ID: %d \n", logmsg1->sourceId);
							printf ("[LoggerThread] Log Level: %d \n", logmsg1->level);
							printf ("[LoggerThread] Payload: %s \n\n", logmsg1->payload);
							// Get the attributes
							printf ("[LoggerThread] Timestamp: %s \n", ctime(&logmsg1->timestamp));
					  }// Clear buffer*/

					}
					pthread_mutex_unlock(&logQ_mutex);
          memset(logmsg1,(int)'\0',sizeof(LogMsg));
				}
    }
  }

  pthread_exit(NULL);
}
                                                                                                        