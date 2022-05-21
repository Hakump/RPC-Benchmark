#include "common.h"
#include "udp.h"
#include <sys/select.h>
#include <time.h>
#include<iostream>
using namespace std;

#define SHUTDOWN 8
#define WRITE 1
#define STAT 2

int bw_num_msgs_sent = 0;
//Timeout interval set to 2*RTT seconds
struct timeval timeConfig;
struct sockaddr_in addr, addr2;
int fd;

#ifdef MEASURE_RTT
struct timespec start, stop;
double time_spent;
double avg_round_triptime = 0.0;
int num_messages = 0;
int total_messages_sent = 0;
#endif

char *serverHost;
int sPort;

int host_init(char *host, int port)
{
  sPort = port;
  serverHost = new char[strlen(host) + 1];
  strcpy(serverHost, host);
  //Client - port 0
  fd = UDP_Open(0);
  //Assigning server port to sockaddr_in addr variable
  UDP_FillSockAddr(&addr, serverHost, sPort);
  //BW optimisation -- timeout set at 2*RTT
  //RTT = 1ms for diff machine
  timeConfig.tv_usec = 0;
  timeConfig.tv_sec = 0.002;
  int rc = setsockopt (fd, SOL_SOCKET, SO_RCVTIMEO, &timeConfig, sizeof(timeConfig) );
  if(rc<0)
    printf("Setsock opt unsuccessful");
  return 0;
}


int sendRequest(message *msg, response *res)
{ 
  int bytes_received=-1;
  int bytes_sent = 0;
  #ifdef MEASURE_RTT
  clock_gettime( CLOCK_REALTIME, &start);
  #endif
  while(bytes_received<0){
    #ifdef MEASURE_RTT
    num_messages += 1;
    #endif
    bytes_sent=UDP_Write(fd, &addr, (char *)msg, sizeof(message));
    bytes_received=UDP_Read(fd, &addr, (char *)res, sizeof(response));

    #ifdef MEASURE_BW
    total_bytes_sent += bytes_sent;
    if(bytes_received>0)
      total_bytes_received += bytes_received;
    bw_num_msgs_sent +=1;
    #endif
    //printf("Bytes received %d\n",rc);
  }
  
  #ifdef MEASURE_RTT
  clock_gettime( CLOCK_REALTIME, &stop);
  time_spent = (( stop.tv_sec - start.tv_sec )*BILLION)
          + ( stop.tv_nsec - start.tv_nsec );
  
  avg_round_triptime += time_spent;
  printf("Round trip time : %lf ns\n", time_spent );
  printf("Total round trip time %lf ns\n",avg_round_triptime);
  printf("Avg round trip time %lf ns ; Num messages : %d\n",avg_round_triptime/num_messages,num_messages);
  #endif

  return 0;
}

int send_message(char *buffer)
{
  message msg;
  response res;
  msg.operation = WRITE;
  strcpy(msg.buffer, buffer);
  sendRequest(&msg, &res);
  return 0;
}

int get_stats()
{
  message msg;
  response res;
  msg.operation = STAT;
  sendRequest(&msg, &res);
  return 0;
}

int host_shutdown()
{
  message msg;
  response res;
  msg.operation = SHUTDOWN;
  sendRequest(&msg, &res);
  return 0;
}



/*
//Select logic
int sendRequest(message *msg, response *res)
{
  //Opening a port 0 on client and binding a socket -- fd
  fd = UDP_Open(0);

  //Assigning server port to sockaddr_in addr variable
  //UDP_FillSockAddr(&addr, serverHost, sPort);
  //Set of read descriptors
  fd_set rfds;
  //printf("Value of fd is %d\n",fd);
  #ifdef ROUND_TRIP
  int restart_start_timer = 1;
  #endif
  int bytes_sent =0;
  int bytes_received=0;
  //FD_ZERO(&rfds);
  while (1)
  {
    //Clears the set
    FD_ZERO(&rfds);
    //Add fd to rfds set
    FD_SET(fd, &rfds);
    //Write msg to addr(server port) from port 0 (client - fd)
    #ifdef ROUND_TRIP
    if(restart_start_timer)
        clock_gettime( CLOCK_REALTIME, &start);
    restart_start_timer = 0;
    #endif
    
    bytes_sent=UDP_Write(fd, &addr, (char *)msg, sizeof(message));
    #ifdef BANDWIDTH
    total_bytes_sent += bytes_sent;
    //printf("Total bytes sent %ld\n",total_bytes_sent);
    #endif
    #ifdef ROUND_TRIP
    total_messages_sent+=1;
    #endif
    //Select - listens on rfds fd for the specified time --- 1 sec here
    //https://www.mkssoftware.com/docs/man3/select.3.asp
    //Select function watches from filedescriptors from 0 to nfds-1
    //int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
    //int nready = select(fd+1, &rfds, NULL, NULL, &timeConfig);
    //if (FD_ISSET(fd,&rfds))
    //setsockopt (fd, SOL_SOCKET, SO_RCVTIMEO, &timeConfig, sizeof(timeConfig) ) 
    if(select(fd+1, &rfds, NULL, NULL, &timeConfig))
    {
      //Reads on client port 0 -- addr2 will contain the server info
      //Default read even when it didn't receive?
      //printf("timeout\n");
      bytes_received = UDP_Read(fd, &addr2, (char *)res, sizeof(response));
      #ifdef ROUND_TRIP
      clock_gettime( CLOCK_REALTIME, &stop);
      time_spent = (( stop.tv_sec - start.tv_sec )*BILLION)
          + ( stop.tv_nsec - start.tv_nsec );
      num_messages += 1;
      avg_round_triptime += time_spent;
      printf("Round trip time : %lf ns\n", time_spent );
	    printf("Start time sec %ld ns %ld\n",start.tv_sec,start.tv_nsec);
	    printf("Stop time sec %ld ns %ld\n",start.tv_sec,start.tv_nsec);
      printf("Avg round trip time %lf ns ; Num messages : %d\n",avg_round_triptime/num_messages,num_messages);
      printf("Total messages sent %d\n",total_messages_sent);
      restart_start_timer = 1;
      #endif
      if (bytes_received > 0)
      {
        #ifdef BANDWIDTH
        total_bytes_received+=bytes_received;
        //printf("Total bytes received %ld\n",total_bytes_received);
        #endif
        UDP_Close(fd);
        if (res->rc == -1)
          return -1;
        return 0;
      }
    }
  }

  return 0;
}

*/