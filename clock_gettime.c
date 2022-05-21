/*
 *  * This program calculates the time required to
 *   * execute the program specified as its first argument.
 *    * The time is printed in seconds, on standard out.
 *     */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define BILLION  1000000000L;

int main( int argc, char **argv )
{
	struct timespec start, stop;
	double accum_sec, accum_nsec;

//	int size = atoi(argv[1]);
	int count = 1000;
/*	int j[size];
	for(int i = 0; i < size; i++)
	{
		if(i%2==0)
			j[i] = i*20;
		else
			j[i] = i+20;
	}
*/	

	clock_gettime( CLOCK_REALTIME, &start);

        count = count+1;	

	clock_gettime( CLOCK_REALTIME, &stop);
	
	accum_sec = stop.tv_sec - start.tv_sec;
	accum_nsec = stop.tv_nsec - start.tv_nsec;

	printf( "%lfseconds:%lfnanoseconds\n", accum_sec, accum_nsec );

	printf("%d \n",count);
	return( EXIT_SUCCESS );
}
