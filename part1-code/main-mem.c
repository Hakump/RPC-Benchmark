#include<time.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv)
{
	int size = 1000000;
	
	int a[size];
	
	struct timespec start, stop;
	double accum_sec[size/16], accum_nsec[size/16];

	int count  = 0;
	for(int i = 0; i < size; i=i+16)
	{
		clock_gettime( CLOCK_REALTIME, &start);
		a[i]=i;
		clock_gettime( CLOCK_REALTIME, &stop);
		accum_sec[count] = (stop.tv_sec - start.tv_sec);
		accum_nsec[count] = (stop.tv_nsec - start.tv_nsec);
		count++;
	}	

	double second, nsecond;
	second = 0;
	nsecond = 0;
	int len = size/16;
	for(int i = 0; i < len; i++)
	{
		second = second + (accum_sec[i]/len);
		nsecond = nsecond + (accum_nsec[i]/len);
	}

	printf( "%lf seconds:%lf nanoseconds\n", second,nsecond);

	return 0;
}
