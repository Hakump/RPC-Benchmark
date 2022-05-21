#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void l1()
{
	int size = 81920; //size of L1
	struct timespec start, stop;
	double accum_sec, accum_nsec;

	int arr[size];
	for(int i = 0; i < size; i++)
	{
		arr[i]=i;
	}
	
	int count = size;
	clock_gettime( CLOCK_REALTIME, &start);
	for(int i = size-1; i >= 0; i--)
	{

		arr[i]=i;
		
	}

	clock_gettime( CLOCK_REALTIME, &stop);
	
	accum_sec = (stop.tv_sec - start.tv_sec)/count;
	accum_nsec = (stop.tv_nsec - start.tv_nsec)/count;

	printf( "%lfseconds:%lfnanoseconds\n", accum_sec,accum_nsec);

}

void l2()
{
	int size = 1318912; //size of L1 + L2
	struct timespec start, stop;
	double accum_sec, accum_nsec;

	int arr[size];
	for(int i = 0; i < size; i++)
	{
		arr[i]=i;
	}
	
	int count = 0;
	clock_gettime( CLOCK_REALTIME, &start);
	for(int i = 0; i < size; i=i+16)
	{

		arr[i]=i;
		
	}

	clock_gettime( CLOCK_REALTIME, &stop);
	
	accum_sec = (stop.tv_sec - start.tv_sec)/(size/16);
	accum_nsec = (stop.tv_nsec - start.tv_nsec)/(size/16);

	printf( "%lfseconds:%lfnanoseconds\n", accum_sec,accum_nsec);

}

int main(int argc, char **argv)
{
//	l1();
	l2();
}
