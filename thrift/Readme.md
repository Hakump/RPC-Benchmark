Compile with thrift:
make && ./client or server
Optimized version: make fast
Machine used: c220g5 with 1Gb network

Line 19 - 150:
Benchmark_type() are functions measuring the marshalling time that includes whole packet serialization and deserialization

Line 151 - 233:
Benchmark_ser_des() is the one that measure packing time used for each type of message

Line 234 - 276:
Measure functions are measuring the time used for sending packets, rtt small packet is ping()/measure_int that returns a packet with null/int value plus headers.

Line 277-337
The measure_string function is generating large packets that used for measuring the bandwidth achieved by thrift.
The measure_large function is generating complex packet (similar behavior of simple large string implementation in result time)

Line 346 :
This line of code is used for removing the fixed overhead of warmup that influence the first function call

Line 347 - 385 :
Benchmarking the time use for packing a int, double, strings, a short complex and large complex structure.

Line 387 :
Measuring the time solely for writing/serializing and reading/deserializing a packet of int double complex structure

Line 398 - 403 :
Small packet RTT ping() first several packets & average of later ones

Line 398 - 403 :
Small packet RTT int() first several packets & average of later ones

Line 409 - 411:
Measure packet RTT for individual string packets

Line 412 - 416 measure bandwidth for several large string packets

Line 420 - 425:
Measuring the bandwidth achieved by different packet size

Line 431-end:
Code for comparing the latency of time measurement functions

Note:
For string generation, the size = 16 bytes * 2^k,
where k is user defined

Results: marshalling
![img_1.png](img_1.png)

Results: RTT
![img_2.png](img_2.png)

Results of varying packet size is in another file

Peak performance of single machine: 100 MB
Peak performance of two machines: 50MB

results_raw file are the testing printout version