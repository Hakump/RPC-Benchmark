#include <stdio.h>
#include <string.h>  // for strlen
#include <assert.h>
#include "zlib.h"
#include <time.h>

// adapted from: http://stackoverflow.com/questions/7540259/deflate-and-inflate-zlib-h-in-c
int main(int argc, char* argv[])
{   
    long unsigned size = 1000;
    char a[size+1];
    for(int i = 0; i < size; i++)
    {
	    a[i]= 'a';
    }

    // b will be the compressed/deflated version of "a"
    char b[size];
     

    printf("Uncompressed size is: %lu\n", strlen(a));
    printf("Uncompressed string is: %s\n", a);


    printf("\n----------\n\n");

    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    // setup "a" as the input and "b" as the compressed output
    defstream.avail_in = (uInt)strlen(a)+1; // size of input, string + terminator
    defstream.next_in = (Bytef *)a; // input char array
    defstream.avail_out = (uInt)sizeof(b); // size of output
    defstream.next_out = (Bytef *)b; // output char array
    
    struct timespec start, stop;
    double accum_sec, accum_nsec;

    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    clock_gettime( CLOCK_REALTIME, &start);
    deflate(&defstream, Z_FINISH);
    clock_gettime( CLOCK_REALTIME, &stop);
    
    accum_sec = (stop.tv_sec - start.tv_sec);
    accum_nsec = (stop.tv_nsec - start.tv_nsec);
    
    printf( "Compression time - %lfseconds:%lfnanoseconds\n", accum_sec,accum_nsec);

    deflateEnd(&defstream);
    
    return 0;
}
