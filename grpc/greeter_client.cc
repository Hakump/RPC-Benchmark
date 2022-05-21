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
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <string>
#include <fstream>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "helloworld.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::ClientWriter;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;
using helloworld::Chunk;
using helloworld::Reply;
using helloworld::TransferFile;
#define CHUNK_SIZE 1024 * 1024

class TransferFileClient
{
  public:
      TransferFileClient(std::shared_ptr<Channel> channel) : stub_(TransferFile::NewStub(channel)){};
      void Upload();
  private:
      std::unique_ptr<TransferFile::Stub> stub_;
};

void TransferFileClient::Upload()
{
    Chunk chunk;
    char data[CHUNK_SIZE];
    Reply stats;
    ClientContext context;
    const char *filename = "./apache-maven-3.8.4-bin.tar.gz";
    std::ifstream infile;
    int len = 0;
    auto start = std::chrono::high_resolution_clock::now();

    infile.open(filename, std::ifstream::in | std::ifstream::binary);
    std::unique_ptr<ClientWriter<Chunk>> writer(stub_->Upload(&context, &stats));
    std::cout<<"Start transfering file!"<<std::endl;
    while (!infile.eof()) {
      infile.read(data, CHUNK_SIZE);
      chunk.set_buffer(data, infile.gcount());
      if (!writer->Write(chunk)) {
        // Broken stream.
        break;
      }
      len += infile.gcount();
    }
    writer->WritesDone();
    Status status = writer->Finish();
    if (status.ok()) {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << "TransferFile took "<< duration.count() / 1000 << " s."<< std::endl;
    } else {
      std::cout << "TransferFile rpc failed." << std::endl;
    }
}

class GreeterClient {
 public:
  GreeterClient(std::shared_ptr<Channel> channel)
      : stub_(Greeter::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string SayHello(const std::string& user) {
    // Data we are sending to the server.
    HelloRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    HelloReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    auto start = std::chrono::high_resolution_clock::now();
    Status status = stub_->SayHello(&context, request, &reply);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;
    std::cout << "Round trip took "<< duration.count() << " ms."<< std::endl;

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Greeter::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  std::string target_str = "34.125.65.140:50051"; // "localhost:50051"
  // GreeterClient greeter(
  //     grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  // std::string user("Yilei");  
  // std::string reply = greeter.SayHello(user);
  // std::cout << "Greeter received: " << reply << std::endl;

  TransferFileClient client(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));
  client.Upload();
  return 0;
}