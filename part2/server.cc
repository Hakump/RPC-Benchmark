#include <stdio.h>
#include "udp.h"
#include "common.h"

#define SHUTDOWN 8
#define WRITE 1
#define STAT 2

int sendResponseToClient(int sd, struct sockaddr_in s, response outputPacket)
{
  //printf("Sending response\n");
  int result = UDP_Write(sd, &s, (char *)&outputPacket, sizeof(response));
  return result;
}

// server code
int main(int argc, char *argv[])
{

  if(argc != 3){
		printf("Server invoke requires portnumber [./server port_number drop_percent]\n");
		exit(1);
	}
  printf("\n::: SERVER STARTED __main__:::\n");

  int port = atoi(argv[1]);
  int drop_percent = atoi(argv[2]);
  //Get port number and will try to bind it to this socket desc
  int sd = UDP_Open(port);
  int dropped_messages = 0;
  int total_messages_received = 0;
  while(1) { //listen for requests
    struct sockaddr_in s;
    message inputPacket;
    //printf("\n::: Waiting for requests __main__::: Port=%d\n",port);

    int r = (rand() % 100) + 1;
    //printf("\n Value of r is %d\n",r);
    
    int result = UDP_Read(sd, &s, (char *)&inputPacket, sizeof(message));
    total_messages_received+=1;
    if(r < drop_percent){
      //printf("Message dropped on server\n");
      dropped_messages +=1;
      continue;
    }

    //printf("UDP read done message = %d\n",inputPacket.operation);
    if (result > 0)
    {
      if (inputPacket.operation == WRITE){
        //printf("Message from client : %s\n",inputPacket.buffer);
        response outputPacket;
        outputPacket.rc = 0;
        sendResponseToClient(sd, s, outputPacket);
      }
      if (inputPacket.operation == STAT){
        printf("STATS from server\n total messages received : %d\n",total_messages_received);
        printf("Total messages dropped : %d\n",dropped_messages);
        response outputPacket;
        outputPacket.rc = 0;
        dropped_messages = 0 ;
        total_messages_received = 0;
        sendResponseToClient(sd, s, outputPacket);
      }
      else if (inputPacket.operation == SHUTDOWN)
      {
        response outputPacket;
        outputPacket.rc = 0;
        sendResponseToClient(sd, s, outputPacket);
        //printf("Total dropped messages %d ;Total received messages %d; Drop percent %d\n",dropped_messages, total_messages_received,drop_percent);
        exit(0);
      }
    }
  }
  
}
