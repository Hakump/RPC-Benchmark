#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<mutex>

using namespace std;
int main(int argc, char **argv)
{
	std::mutex new_lock;
	struct timespec start, stop;
	double accum_sec_lock, accum_nsec_lock, accum_sec_unlock, accum_nsec_unlock;
	for(uint i = 0; i < 50; i++)
	{
		clock_gettime( CLOCK_REALTIME, &start);
		new_lock.lock();
		clock_gettime( CLOCK_REALTIME, &stop);
		
		accum_sec_lock = (stop.tv_sec - start.tv_sec);
		accum_nsec_lock = (stop.tv_nsec - start.tv_nsec);
		
		clock_gettime( CLOCK_REALTIME, &start);
		new_lock.unlock();

		clock_gettime( CLOCK_REALTIME, &stop);
		
		accum_sec_unlock = (stop.tv_sec - start.tv_sec);
		accum_nsec_unlock = (stop.tv_nsec - start.tv_nsec);

		printf( "Locking time - %lf:%lf\n", accum_sec_lock,accum_nsec_lock);
		printf( "Unlocking time - %lf:%lf\n\n", accum_sec_unlock,accum_nsec_unlock);
	}


	return 0;
}
