#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <chrono>
#include <utility>
#include <time.h>

#include "ThriftMessage.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

//using namespace shared;

/**
 * done
 * @return
 */
double benckmark_Int(){
    auto trans = make_shared<TMemoryBuffer>(2048);
    TBinaryProtocol proto(trans);

    IntMessage outgoing, res;
    outgoing.num = 9753;
    auto begin = std::chrono::high_resolution_clock::now();
    proto.writeMessageBegin("sendInt", apache::thrift::protocol::T_CALL, 0);
    ThriftMessage_sendInt_args arg;
    arg.intMsg = outgoing;
    arg.write(&proto);
    proto.writeMessageEnd();
    auto tt = proto.getTransport();
    tt->writeEnd();
    auto end = std::chrono::high_resolution_clock::now();
    auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    tt->flush();
    return (double)(time_used.count())* 1e-3;
}

/**
 * done
 * @return
 */
double benckmark_double(){
    auto trans = make_shared<TMemoryBuffer>(2048);
    TBinaryProtocol proto(trans);

    DoubleMessage outgoing, res;
    outgoing.num = 1010.0202;
    auto begin = std::chrono::high_resolution_clock::now();
    proto.writeMessageBegin("sendDouble", apache::thrift::protocol::T_CALL, 0);
    ThriftMessage_sendDouble_args arg;
    arg.doubleMsg = outgoing;
    arg.write(&proto);
    proto.writeMessageEnd();
    auto tt = proto.getTransport();
    tt->writeEnd();
    auto end = std::chrono::high_resolution_clock::now();
    auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    tt->flush();
    return (double)(time_used.count())* 1e-3;
}

/**
 * done
 * @return
 */
double benckmark_string(string str){
    auto trans = make_shared<TMemoryBuffer>(1 << 16);
    TBinaryProtocol proto(trans);

    StringMessage outgoing, res;
    outgoing.str = std::move(str);
    auto begin = std::chrono::high_resolution_clock::now();
    proto.writeMessageBegin("sendStr", apache::thrift::protocol::T_CALL, 0);
    ThriftMessage_sendStr_args arg;
    arg.strMsg = outgoing;
    arg.write(&proto);
    proto.writeMessageEnd();
    auto tt = proto.getTransport();
    tt->writeEnd();
    auto end = std::chrono::high_resolution_clock::now();
    tt->flush();
    auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    return (double)(time_used.count())* 1e-3;
}

double benchmark_small(){
    auto trans = make_shared<TMemoryBuffer>(2048);
    TBinaryProtocol proto(trans);

    ShortMessage outgoing, res;
    outgoing.num1 = 9753;
    outgoing.num2 = 1010.0202;
    outgoing.str = "hello, world";
    auto begin = std::chrono::high_resolution_clock::now();
    proto.writeMessageBegin("sendShortMsg", apache::thrift::protocol::T_CALL, 0);
    ThriftMessage_sendShortMsg_args arg;
    arg.srtMsg = outgoing;
    arg.write(&proto);
    proto.writeMessageEnd();
    auto tt = proto.getTransport();
    tt->writeEnd();
    auto end = std::chrono::high_resolution_clock::now();
    auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    tt->flush();
    return (double)(time_used.count())* 1e-3;
}

double benchmark_large(int size, int num){
    auto trans = make_shared<TMemoryBuffer>(1 << 22);
    TBinaryProtocol proto(trans);

    LargeMessage outgoing, res;
    std::string large_string = "1234567890123456";
    for (int i = 0; i < size; ++i) {
        large_string += large_string;
    }
    outgoing.string1 = large_string;
    outgoing.size = num;
    vector<int> ints(num, 97531);
    vector<double> doubles(num, 97531.0);
    vector<bool> bool_list(num, true);
    outgoing.ints = ints;
    outgoing.doubles = doubles;
    outgoing.bools = bool_list;

    auto begin = std::chrono::high_resolution_clock::now();
    proto.writeMessageBegin("sendLargeMsg", apache::thrift::protocol::T_CALL, 0);
    ThriftMessage_sendLargeMsg_args arg;
    arg.lrgMsg = outgoing;
    arg.write(&proto);
    proto.writeMessageEnd();
    auto tt = proto.getTransport();
    tt->writeEnd();
    auto end = std::chrono::high_resolution_clock::now();
    auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    begin = std::chrono::high_resolution_clock::now();
    tt->flush();
    end = std::chrono::high_resolution_clock::now();
    cout << "SendLargeMsg flush time: " << (double) std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << endl;
    return (double)(time_used.count())* 1e-3;
}

double benchmark_ser_des(int iterations){
    std::shared_ptr<TMemoryBuffer> buffer1(new TMemoryBuffer());
    std::shared_ptr<TMemoryBuffer> buffer2(new TMemoryBuffer());

    TBinaryProtocolT<TMemoryBuffer> binary_protocol1(buffer1);
    TBinaryProtocolT<TMemoryBuffer> binary_protocol2(buffer2);

    ShortMessage s1, s2;
    s1.num1 = 100;
    s1.num2 = 10.0;
    s1.str = "hello, world";

    string serialized_str;
    double res_time_serial = 0.0;
    double res_time_de_serial = 0.0;
    auto start = std::chrono::high_resolution_clock::now();
    auto finish = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    for (size_t i = 0; i < iterations; i++) {
        buffer1->resetBuffer();
        start = std::chrono::high_resolution_clock::now();
        s1.write(&binary_protocol1);
        finish = std::chrono::high_resolution_clock::now();
        res_time_serial += (double) std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        serialized_str = buffer1->getBufferAsString();
        buffer2->resetBuffer((uint8_t*)serialized_str.data(), serialized_str.length());

        start = std::chrono::high_resolution_clock::now();
        s2.read(&binary_protocol2);
        finish = std::chrono::high_resolution_clock::now();
        res_time_de_serial += (double) std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    }
    cout<< "benchmark short message serialization: " << res_time_serial / iterations << " us" << endl;
    cout<< "benchmark short message deserialization: " << res_time_de_serial / iterations << " us" << endl;

    DoubleMessage d1;
    d1.num = 100.0;

    double serialized_double;
    res_time_serial = 0.0;
    res_time_de_serial = 0.0;
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    for (size_t i = 0; i < iterations; i++) {
        buffer1->resetBuffer();
        start = std::chrono::high_resolution_clock::now();
        d1.write(&binary_protocol1);
        finish = std::chrono::high_resolution_clock::now();
        res_time_serial += (double) std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        start = std::chrono::high_resolution_clock::now();
        binary_protocol1.readDouble(serialized_double);
        finish = std::chrono::high_resolution_clock::now();
        res_time_de_serial += (double) std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    }
    cout<< "benchmark double serialization: " << res_time_serial / iterations << " us" << endl;
    cout<< "benchmark double deserialization: " << res_time_de_serial / iterations << " us" << endl;

    IntMessage i1;
    i1.num = 100;

    int serialized_int;
    res_time_serial = 0.0;
    res_time_de_serial = 0.0;
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    for (size_t i = 0; i < iterations; i++) {
        buffer1->resetBuffer();
        start = std::chrono::high_resolution_clock::now();
        i1.write(&binary_protocol1);
        finish = std::chrono::high_resolution_clock::now();
        res_time_serial += (double) std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();

        start = std::chrono::high_resolution_clock::now();
        binary_protocol1.readI32(serialized_int);
        finish = std::chrono::high_resolution_clock::now();
        res_time_de_serial += (double) std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count();
    }
    cout<< "benchmark int serialization: " << res_time_serial / iterations << " us" << endl;
    cout<< "benchmark int deserialization: " << res_time_de_serial / iterations << " us" << endl;

    return 0.0;
}

double measure_rtt(ThriftMessageClient &client, int packet_num){
    double res = 0.0;
    for (int i = 0; i < packet_num; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        client.ping();
        auto end = std::chrono::high_resolution_clock::now();
        auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        res += (double)(time_used.count());
    }

    return res / packet_num;
}

double measure_int(ThriftMessageClient &client, int n){
    double res = 0.0;
    IntMessage intMessage;
    intMessage.num = 9753;
    for (int i = 0; i < n; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        client.sendInt(intMessage);
        auto end = std::chrono::high_resolution_clock::now();
        auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        res += (double)(time_used.count());
    }

    return res / n;
}

//double measure_double(ThriftMessageClient &client){
//    double res = 0.0;
//    DoubleMessage doubleMessage;
//    doubleMessage.num = 1010.0101;
//    for (int i = 0; i < 10; ++i) {
//        auto begin = std::chrono::high_resolution_clock::now();
//        client.sendDouble(doubleMessage);
//        auto end = std::chrono::high_resolution_clock::now();
//        auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
//        res += (double)(time_used.count());
//    }
//
//    return res / 10;
//}

double measure_string(ThriftMessageClient &client, int size, int packet_num){
    double res = 0.0;
    StringMessage stringMessage;
    string return_;
    string test_str = "abcdefghijklmnop";
    for (int multiply = 0; multiply < size; ++multiply) {
        test_str += test_str;
    }
//    cout << test_str.size() << " strsize" << endl;
    stringMessage.str = test_str;
    for (int i = 0; i < packet_num; ++i) {
        auto begin = std::chrono::high_resolution_clock::now();
        client.sendStr(return_, stringMessage);
        auto end = std::chrono::high_resolution_clock::now();
        auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        res += (double)(time_used.count());
//        cout<< "packet #: " << time_used.count() * 1e-3 << endl;
    }

    return res / packet_num;
}

//double measure_small(ThriftMessageClient &client){
//
//}

/**
 * we are going to send large amount of large packets to see when will them be finished - throughput
 * @param client
 * @param size size of string = 16 * 2^size byte
 * @param num length of the lists inside the struct
 * @param packet_num number of packet sending together (blocking?)
 * @return
 */
double measure_large(ThriftMessageClient &client, int size, int num, int packet_num){
    double res = 0.0;
    LargeMessage outgoing, ingoing;
    std::string large_string = "1234567890123456";
    for (int i = 0; i < size; ++i) {
        large_string += large_string;
    }
    cout << large_string.size() << " str size " << endl;
    outgoing.string1 = large_string;
    outgoing.size = num;
    vector<int> ints(num, 97531);
    vector<double> doubles(num, 97531.0);
    vector<bool> bool_list(num, true);
    outgoing.ints = ints;
    outgoing.doubles = doubles;
    outgoing.bools = bool_list;
//    cout << "size of packet" << sizeof(outgoing) << endl;
    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < packet_num; ++i) {
        client.sendLargeMsg(ingoing, outgoing);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    res = (double)(time_used.count()) / packet_num;
    return res;
}


int main(){
    std::shared_ptr<TTransport> socket(new TSocket("10.10.1.2", 9090)); // localhost 10.10.1.2
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    ThriftMessageClient client(protocol);

    cout << "first bench int: " << benckmark_Int() << endl;
    int n = 10;
    double nano_time_used = 0.0;
    for (int i = 0; i < n; ++i) {
        nano_time_used += benckmark_Int();
    }
    printf("Average time measured for packing int 10 time: %.3f micro second.\n", nano_time_used / n);


    nano_time_used = 0.0;
    for (int i = 0; i < n; ++i) {
        nano_time_used += benckmark_double();
    }
    printf("Average time measured for packing double 10 time: %.3f micro second.\n", nano_time_used / n);


    std::string test_string = "1234567890123456";
    benckmark_string(test_string);
    for (int size = 0; size <= 11; ++size) {
        nano_time_used = 0.0;
        for (int i = 0; i < n; ++i) {
            nano_time_used += benckmark_string(test_string);
        }
        test_string += test_string;
        printf("Average time measured for packing string of length %d 10 time: %.3f micro second.\n",
               (int)(pow(2, size + 4)), nano_time_used / n);
    }


    nano_time_used = 0.0;
    for (int i = 0; i < n; ++i) {
        nano_time_used += benchmark_small();
    }
    printf("Average time measured for packing short msg 10 time: %.3f micro second.\n", nano_time_used / n);

    nano_time_used = 0.0;
    for (int i = 0; i < n; ++i) {
        nano_time_used += benchmark_large(10, 100);
    }
    printf("Average time measured for packing large msg 10 time: %.3f micro second.\n", nano_time_used / n);

    benchmark_ser_des(n);

    try {
        transport->open();
        // measure rtt
        for (int i = 0; i < 5; ++i) {
            printf("RTT for ping() packet %d : %.3f micro second.\n", i, measure_rtt(client, 1) * 1e-3);
        }
        printf("Average RTT for ping() on 10 packets: %.3f micro second.\n", measure_rtt(client, 10) * 1e-3);

        // rtt int
        IntMessage msg_int;
        msg_int.num = 1;
        for (int i = 0; i < 5; ++i) {
            printf("RTT for int packet %d : %.3f micro second.\n", i, measure_int(client, 1) * 1e-3);
        }
        printf("Average RTT for int on 10 packets: %.3f micro second.\n", measure_int(client, 10) * 1e-3);

        // rtt string
        int string_multiply = 18;
        int packet_multiply = 4;

        for (int i = 0; i < 5; ++i) {
            printf("RTT for string packet %d : %.3f micro second.\n", i, measure_string(client, string_multiply, 1) * 1e-3);
        }

        double ttl_string = measure_string(client, string_multiply, packet_multiply);
        double str_size = pow(2, string_multiply) * 16;
        printf("Average RTT for string() on %d packets of size %d Bytes: %.3f micro second.\n",
               packet_multiply, (int) str_size, ttl_string * 1e-3);

        cout<< "throughput: " << str_size / (ttl_string * 1e-3) << " MegaBytes/Second" << endl;

        for (int i = 0; i < 9; ++i) {
            int size_packet = (int) pow(2, i + 7) * 16;
            double res_packet_rtt_micro = measure_string(client, i + 7, 5) * 1e-3;
            printf("RTT for string packet of size %d Bytes: %.3f micro second.\n", size_packet, res_packet_rtt_micro);
            cout<< "throughput: " << size_packet * 5 / (res_packet_rtt_micro) << " MegaBytes/Second" << endl;
        }
        transport->close();
    } catch (TException& tx) {
        cout << "ERROR: " << tx.what() << endl;
    }

    clock_t start, end;

    /* Recording the starting clock tick.*/
    start = clock();

    int temp = 0;
    for (int i = 0; i < 1000; ++i) {
        temp += 9753/552;
    };

    // Recording the end clock tick.
    end = clock();

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << endl;
    cout << " sec " << endl;

    auto begin = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        temp += 9753/552;
    }
    auto end_ch = std::chrono::high_resolution_clock::now();
    auto time_used = std::chrono::duration_cast<std::chrono::nanoseconds>(end_ch - begin);
    cout << (double)(time_used.count()) * 1e-9 << endl;

    return 0;

}