GEN_SRC = ThriftMessage.cpp testing_types.cpp testing_constants.cpp

default: client server

clean:
	rm client server

client: client.cpp
	g++ -DHAVE_NETINET_IN_H -o client client.cpp ${GEN_SRC} -lthrift

server: server.cpp
	g++ -DHAVE_NETINET_IN_H -o server server.cpp ${GEN_SRC} -lthrift

fast: client.cpp server.cpp
	g++ -DHAVE_NETINET_IN_H -o client client.cpp ${GEN_SRC} -lthrift -Ofast
	g++ -DHAVE_NETINET_IN_H -o server server.cpp ${GEN_SRC} -lthrift -Ofast