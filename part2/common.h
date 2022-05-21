#include<time.h>
extern struct timespec start_pack_timer;
extern struct timespec stop_pack_timer;
extern double time_spent_pack_timer;

#define SERVER_PORT 9586
#define SERVER_HOST "localhost"

#define BILLION 1000000000L

#define BUFFER_SIZE 65000
//#define BUFFER_SIZE 32000
//#define BUFFER_SIZE 16000
//#define BUFFER_SIZE 8000
//#define BUFFER_SIZE 4000
//#define BUFFER_SIZE 20

//Can enable one measurement at a time by enabling one macro
//Poor code development? - Enabled bandwidth measurements

//#define MEASURE_PACKING
//#define MEASURE_RTT
//#define MEASURE_RELIABILITY
#define MEASURE_BW

typedef struct __message__ {
        int operation;
        char buffer[BUFFER_SIZE];
} message;

typedef struct __response__ {
        int rc;
        //char buffer[MAX_BUFFER];
} response;

int host_init(char *hostname, int port);
int send_message(char *buffer);
int host_shutdown();
int get_stats();

extern int bw_num_msgs_sent;
extern long int total_bytes_sent;
extern long int total_bytes_received;