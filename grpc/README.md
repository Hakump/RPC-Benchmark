I'm not very familiar with C/C++ build toolchains so I just modified example code to complete part3.

Compile grpc: https://grpc.io/docs/languages/cpp/quickstart/

ssh kinghyl13@34.125.65.140 (Las Vegas) -> server
ssh kinghyl13@34.81.170.200 (Taiwan)    -> client

cd ~/grpc/examples/cpp/helloworld/cmake/build

make -j

./greeter_server
./greeter_client