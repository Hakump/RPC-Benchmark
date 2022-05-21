#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	srand(time(NULL)); 
	int i = 0;
	int count_miss = 0;

	int arr[100];

	struct timespec start, stop;
//	double accum_sec, accum_nsec;
	double accum_sec[100], accum_nsec[100];

	for(int i = 0; i < 100; i++)
		arr[i]=-1;

	while(i < 100)
	{
		int new_int = 1+ (rand() % 1000000);
		clock_gettime( CLOCK_REALTIME, &start);
		if(new_int%2==0)
		{
			arr[i] = new_int;
		}
		clock_gettime( CLOCK_REALTIME, &stop);
		accum_sec[i] = stop.tv_sec - start.tv_sec;
		accum_nsec[i] = stop.tv_nsec - start.tv_nsec;

		i++;
	}
	
	double sec, nsec;
	sec = 0.0;
	nsec = 0.0;

	for(int i = 0; i < 100; i++)
	{
		if(arr[i] == -1)
		{
			sec = sec + accum_sec[i];
			nsec = nsec + accum_nsec[i];
			count_miss += 1;
		}
	}

	printf("With conditionals\n");
	printf( "%lfseconds:%lfnanoseconds\n", sec/count_miss, nsec/count_miss);
	printf("branch misses : %d\n",  count_miss);
/*	
	i=0;
	count_hit=0;
	if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
	       	perror( "clock gettime" );
	        exit( EXIT_FAILURE );
	}

	while(i < 100)
	{
		int new_int = rand();
		arr[i] = new_int;
		i++;
	}
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
		perror( "clock gettime" );
		exit( EXIT_FAILURE );
	}
	accum_sec = stop.tv_sec - start.tv_sec;
	accum_nsec = stop.tv_nsec - start.tv_nsec;

	printf("Without conditionals\n");
	printf( "%lf\n", accum_sec );
	printf( "%lf\n", accum_nsec );
	*/
	return 0;

}
