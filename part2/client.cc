#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include<unistd.h>
#include<signal.h>
#include<iostream>
using namespace std;
#define BILLION 1000000000L
//long int total_bytes_sent=0;
//long int total_bytes_received=0;
struct timespec start_pack_timer;
double time_spent_pack_timer;

#ifdef MEASURE_RELIABILITY
struct timespec start_rel_timer, stop_rel_timer;
double time_spent_rel;
double avg_rtt = 0.0;
int num_messages = 0;
int total_messages_sent = 0;
#endif

//Signal handler firing to measure B/W after 1 second
void sig_handler(int signum){
  get_stats();
  printf("Num msgs sent %d\n",bw_num_msgs_sent);
  printf("Bandwidth = %ld KBps\n",(total_bytes_sent+total_bytes_received)/1024);
  exit(1);
}

int main(int argc, char *argv[])
{
	
	if(argc != 3){
		printf("Client invoke requires hostname and portnumber [./client localhost portnumber]\n");
		exit(1);
	}
	
	char *hostname = new char[30];
	strcpy(hostname,argv[1]);
	int port = atoi(argv[2]);
	//Binding portnumber and hostname
	host_init(hostname, port);
	
	//Sending message to server
	char *buffer=new char[BUFFER_SIZE];
	//strcpy(buffer,"Hello world\n");
	for(int i=0;i<BUFFER_SIZE-1;i++)
		buffer[i]='c';
	
	//Packing measurements
	#ifdef MEASURE_PACKING
	clock_gettime( CLOCK_REALTIME, &start_pack_timer);
	int rc2=send_message(buffer);
	time_spent_pack_timer = (( stop_pack_timer.tv_sec - start_pack_timer.tv_sec )*BILLION)
		+ ( stop_pack_timer.tv_nsec - start_pack_timer.tv_nsec );
	printf("Packing time : %lf ns\n", time_spent_pack_timer );
	#endif

	#ifdef MEASURE_RTT
	//send_message(buffer);
	for(int i=0;i<10;i++)
		send_message(buffer);
	//get_stats();
	#endif

	#ifdef MEASURE_RELIABILITY
	clock_gettime( CLOCK_REALTIME, &start_rel_timer);
	send_message(buffer);
	int number_of_messages = 500;
	for(int i=0;i<498;i++)
		send_message(buffer);
	get_stats();
	clock_gettime( CLOCK_REALTIME, &stop_rel_timer);
	  time_spent_rel = (( stop_rel_timer.tv_sec - start_rel_timer.tv_sec )*BILLION)
          + ( stop_rel_timer.tv_nsec - start_rel_timer.tv_nsec );
  
  	avg_rtt += time_spent_rel;
  	printf("Round trip time : %lf ns\n", time_spent_rel );
  	printf("Total round trip time %lf ns\n",avg_rtt);
  	printf("Avg round trip time %lf ns ; Num messages : %d\n",avg_rtt/number_of_messages,number_of_messages);
	#endif
	printf("Sending hello world message to server\n");

	#ifdef MEASURE_BW
	//Start timer for sending a message
	signal(SIGALRM,sig_handler); // Register signal handler
 
  	alarm(1);  // Scheduled alarm after 1 seconds
	//Send a stream of messages and catch it in sig handler in 1sec
	int num_msg = 50000;
	for(int i=0;i<num_msg;i++)
		send_message(buffer);
	printf("Total messages sent %d\n",num_msg);
	#endif

	//host_shutdown(); 	
	return 0;
}