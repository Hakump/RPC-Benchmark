#include<time.h>
#include<stdlib.h>
#include<stdio.h>

int main(int argc, char **argv)
{
	int size = 250000;
	
	int a[size];
	
	struct timespec start, stop;
	double accum_sec, accum_nsec;

	clock_gettime( CLOCK_REALTIME, &start);
	for(int i = 0; i < size; i++)
	{
		a[i]=i;
	}	

	clock_gettime( CLOCK_REALTIME, &stop);
	accum_sec = (stop.tv_sec - start.tv_sec);
	accum_nsec = (stop.tv_nsec - start.tv_nsec);
	
	printf("%lf seconds:%lf nanoseconds\n", accum_sec,accum_nsec);

	return 0;
}
