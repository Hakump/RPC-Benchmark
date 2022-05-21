/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <fstream>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerReader;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;
using helloworld::Chunk;
using helloworld::Reply;
using helloworld::TransferFile;
using helloworld::IntMessage;
using helloworld::DoubleMessage;
using helloworld::StringMessage;
using helloworld::ComplexMessage;

#define CHUNK_SIZE 1024 * 1024

// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    std::string prefix("This RPC is called to get round-trip time, ");
    reply->set_message(prefix + request->name());
    // std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    return Status::OK;
  }
};

class TransferFileImpl final : public TransferFile::Service {
public:
    Status Upload(ServerContext* context, ServerReader<Chunk>* reader, Reply* reply);
};

Status TransferFileImpl::Upload(ServerContext* context, ServerReader<Chunk>* reader, Reply* reply) {
    Chunk chunk;
    const char *filename = "./uploaded_aa";
    std::ofstream outfile;
    const char *data;
    outfile.open(filename, std::ofstream::out | std::ofstream::trunc | std::ofstream::binary);
    while (reader->Read(&chunk)) {
        data = chunk.buffer().c_str();
        outfile.write(data, chunk.buffer().length());
    }
    long pos = outfile.tellp();
    reply->set_length(pos);
    outfile.close();
    return Status::OK;
}

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  GreeterServiceImpl service;
  // TransferFileImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

void benchmark(){
  // Int
  auto start = std::chrono::high_resolution_clock::now();

  int count = 500;
  for (size_t i = 0; i < count; i++)
  {
    helloworld::IntMessage intMsg;
    intMsg.set_i(12345);

    // Serialization
    std::fstream output1("./int.bin", std::ios::out | std::ios::binary);
    intMsg.SerializePartialToOstream(&output1);
    output1.close();

    // Deserialization
    helloworld::IntMessage intMsg1;
    // std::cout << intMsg1.i() << std::endl; 
    std::fstream input1("./int.bin", std::ios::in | std::ios::binary);
    intMsg1.ParseFromIstream(&input1);
    input1.close();
  }
  // Get data
  // std::cout << intMsg1.i() << std::endl; 
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  std::cout << "Int serialization and deserialization took "<< duration.count() << " ms."<< std::endl;

  // Double
  start = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < count; i++)
  {
    helloworld::DoubleMessage doubleMsg;
    doubleMsg.set_d(1628967892.2231231);

    // Serialization
    std::fstream output2("./double.bin", std::ios::out | std::ios::binary);
    doubleMsg.SerializePartialToOstream(&output2);
    output2.close();

    // Deserialization
    helloworld::DoubleMessage doubleMsg1;
    // std::cout << doubleMsg1.d() << std::endl; 
    std::fstream input2("./double.bin", std::ios::in | std::ios::binary);
    doubleMsg1.ParseFromIstream(&input2);
    input2.close();
  }
  
  // Get data
  // std::cout << doubleMsg1.d() << std::endl; 
  end = std::chrono::high_resolution_clock::now();
  duration = end - start;
  std::cout << "Double serialization and deserialization took "<< duration.count() << " ms."<< std::endl;

  // String
  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < count; i++)
  {
    helloworld::StringMessage strMsg;
    strMsg.set_s("hello, world");

    // Serialization
    std::fstream output3("./string.bin", std::ios::out | std::ios::binary);
    strMsg.SerializePartialToOstream(&output3);
    output3.close();

    // Deserialization
    helloworld::StringMessage strMsg1;
    // std::cout << strMsg1.s() << std::endl; 
    std::fstream input3("./string.bin", std::ios::in | std::ios::binary);
    strMsg1.ParseFromIstream(&input3);
    input3.close();
  }
  
  // Get data
  // std::cout << strMsg1.s() << std::endl; 
  end = std::chrono::high_resolution_clock::now();
  duration = end - start;
  std::cout << "String serialization and deserialization took "<< duration.count() << " ms."<< std::endl;

  // Complex
  start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < count; i++)
  {
    helloworld::ComplexMessage cpxMsg;
    cpxMsg.set_i(12345);
    cpxMsg.set_d(1628967892.2231231);
    cpxMsg.set_s("hello, world");

    // Serialization
    std::fstream output4("./cpx.bin", std::ios::out | std::ios::binary);
    cpxMsg.SerializePartialToOstream(&output4);
    output4.close();

    // Deserialization
    helloworld::ComplexMessage cpxMsg1;
    // std::cout << cpxMsg1.i() << " " << cpxMsg1.d()<< " " << cpxMsg1.s() << std::endl; 
    std::fstream input4("./cpx.bin", std::ios::in | std::ios::binary);
    cpxMsg1.ParseFromIstream(&input4);
    input4.close();
  }
  // Get data
  // std::cout << cpxMsg1.i() << " " << cpxMsg1.d()<< " " << cpxMsg1.s() << std::endl;  
  end = std::chrono::high_resolution_clock::now();
  duration = end - start;
  std::cout << "Complex message serialization and deserialization took "<< duration.count() << " ms."<< std::endl;
}

int main(int argc, char** argv) {
  // RunServer();
  benchmark();
  return 0;
}