#include "udp.h"
#include "common.h"
// create a socket and bind it to a port on the current machine
// used to listen for incoming packets
long int total_bytes_sent=0;
long int total_bytes_received=0;
struct timespec stop_pack_timer;
int UDP_Open(int port)
{
  int fd;
  //int sockfd = socket(domain, type, protocol)
  //domain: integer, specifies communication domain.
  //---AFINET - ipv4/ipv6
  //type: communication type
  //---SOCK_STREAM: TCP(reliable, connection oriented)
  //---SOCK_DGRAM: UDP(unreliable, connectionless)
  //protocol: Protocol value for Internet Protocol(IP), which is 0. 
  if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
  {
    perror("socket");
    return 0;
  }

  // set up the bind
  struct sockaddr_in my_addr;
  bzero(&my_addr, sizeof(my_addr));

  my_addr.sin_family = AF_INET; //ipv4/v6
  my_addr.sin_port = htons(port); //
  my_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
  {
    perror("bind");
    close(fd);
    return -1;
  }

  return fd;
}

// fill sockaddr_in struct with proper goodies
//sockaddr_in -- Structures for handling internet addresses
int UDP_FillSockAddr(struct sockaddr_in *addr, char *hostname, int port)
{
  bzero(addr, sizeof(struct sockaddr_in));
  if (hostname == NULL)
  {
    return 0; // it's OK just to clear the address
  }

  addr->sin_family = AF_INET;   // host byte order
  addr->sin_port = htons(port); // short, network byte order

  struct in_addr *in_addr;
  struct hostent *host_entry;
  if ((host_entry = gethostbyname(hostname)) == NULL)
  {
    perror("gethostbyname");
    return -1;
  }
  in_addr = (struct in_addr *)host_entry->h_addr;
  addr->sin_addr = *in_addr;

  return 0;
}

int UDP_Write(int fd, struct sockaddr_in *addr, char *buffer, int n)
{
  int addr_len = sizeof(struct sockaddr_in);
  #ifdef MEASURE_PACKING
  //Stop timer for  packing
  clock_gettime( CLOCK_REALTIME, &stop_pack_timer);
  #endif
  int rc = sendto(fd, buffer, n, 0, (struct sockaddr *)addr, addr_len);

  return rc;
}

int UDP_Read(int fd, struct sockaddr_in *addr, char *buffer, int n)
{
  int len = sizeof(struct sockaddr_in);
  int rc = recvfrom(fd, buffer, n, 0, (struct sockaddr *)addr, (socklen_t *)&len);
  // assert(len == sizeof(struct sockaddr_in));
  return rc;
}

int UDP_Close(int fd)
{
  return close(fd);
}

/*
int recvfrom(
  [in]                SOCKET   s,
  [out]               char     *buf,
  [in]                int      len,
  [in]                int      flags,
  [out]               sockaddr *from,
  [in, out, optional] int      *fromlen
);
[in] s
A descriptor identifying a bound socket.

[out] buf
A buffer for the incoming data.

[in] len
The length, in bytes, of the buffer pointed to by the buf parameter.

[in] flags
A set of options that modify the behavior of the function call beyond the options specified for the associated socket. See the Remarks below for more details.

[out] from
An optional pointer to a buffer in a sockaddr structure that will hold the source address upon return.

[in, out, optional] fromlen
An optional pointer to the size, in bytes, of the buffer pointed to by the from parameter.*/

/*
int sendto(
  [in] SOCKET         s,
  [in] const char     *buf,
  [in] int            len,
  [in] int            flags,
  [in] const sockaddr *to,
  [in] int            tolen
);

[in] s
A descriptor identifying a (possibly connected) socket.

[in] buf
A pointer to a buffer containing the data to be transmitted.

[in] len
The length, in bytes, of the data pointed to by the buf parameter.

[in] flags
A set of flags that specify the way in which the call is made.

[in] to
An optional pointer to a sockaddr structure that contains the address of the target socket.

[in] tolen
The size, in bytes, of the address pointed to by the to parameter
*/

/*
*/