/*****************************************************
 * File: socketThread.c
 * Authors: Virag Gada and Vihanga Bare
 * Description: Source file for socket handling task
 ****************************************************/

#include "main.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <memory.h>
#include <dirent.h>

#define MAX_CONNECTIONS   (100)
#define BACKLOG           (20)
#define PORT_NUMBER       (6000)

/* Array of child threads and function descriptiors */
pthread_t child_threads[MAX_CONNECTIONS];
int client_fd[MAX_CONNECTIONS];

/* Variable for our socket fd*/
int sockfd;

/* Function prototype */
void *respondClient(void * num);

void *SocketThread(void * input){

  /*Variables*/
  long availableSlot = 0;
  struct sockaddr_in *selfAddr;
  struct sockaddr_in fromAddr;
  socklen_t fromAddrSize;
  char buffer[MAX_SEND_BUFFER];

  pthread_attr_t attr;

  selfAddr = (struct sockaddr_in *)calloc(1,sizeof(struct sockaddr_in));

  (*selfAddr).sin_family = AF_INET;           //address family
  (*selfAddr).sin_port = htons(PORT_NUMBER); //sets port to network byte order
  (*selfAddr).sin_addr.s_addr = htonl(INADDR_ANY); //sets local address

  /*Create Socket*/
  if((sockfd = socket((*selfAddr).sin_family,SOCK_STREAM,0))< 0) {
    printf("Unable to create socket\n");
    exit(1);
  }
  printf("Socket Created\n");

  /*Call Bind*/
  if(bind(sockfd,(struct sockaddr *)selfAddr,sizeof(*selfAddr))<0) {
    printf("Unable to bind\n");
    exit(1);
  }
  printf("Socket Binded\n");

  /* Listen for incomming connections */
  if(listen(sockfd,BACKLOG)!=0){
    printf("%s\n","Listen Error");
    exit(1);
  }

  memset(&fromAddr,(int)'\0',sizeof(fromAddr));
  memset(buffer,(int)'\0',sizeof(buffer));
  fromAddrSize = sizeof(fromAddr);
  memset(client_fd,-1,sizeof(client_fd));
  pthread_attr_init(&attr);

  /*listen*/
  while(1) {
    printf("waiting for connections..\n");
    /*Accept*/
    if((client_fd[availableSlot] = accept(sockfd,(struct sockaddr *)&fromAddr,&fromAddrSize)) < 0)
    {
      printf("Failed to accept connection\n");
      break;
    }else{
      /* Create new thread to handle the client */
      pthread_create(&child_threads[availableSlot],&attr,respondClient,(void *)availableSlot);
    }
    /* Add client fd to a position in the array which is empty */
    while (client_fd[availableSlot]!=-1) {
      availableSlot = (availableSlot+1)%MAX_CONNECTIONS;
    }
    printf("Slot number - %ld\n", availableSlot);
  }

  /*Close*/
  close(sockfd);
  return 0;
}


/* Thread function to respond to client request */
void *respondClient(void * num){

  int client_no = (int )(long) num;

  printf("Thread %d created\n",client_no);

  /* Wait for data, do something */

  sleep(10);
  printf("Thread %d exiting\n",client_no);

  /* Close the thread socket */
  close(client_fd[client_no]);

  /* Set its value to -1 to use this position for some other thread */
  client_fd[client_no]=-1;
  pthread_exit(NULL);
}
