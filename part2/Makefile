CC     := g++
CFLAGS := -Wall -g

DEPS   := udp.cc
DEP_CLIENT := client_helper.cc
.PHONY: all
all: server client

server: server.o ${DEPS}
	${CC} ${CFLAGS} -o server server.o ${DEPS}

client: client.o
	${CC} ${CFLAGS} -o client client.o ${DEP_CLIENT} ${DEPS}

opt: server_opt client_opt

server_opt: server.o ${DEPS}
	${CC} ${CFLAGS} -o server server.o ${DEPS} -O

client_opt: client.o
	${CC} ${CFLAGS} -o client client.o ${DEP_CLIENT} ${DEPS} -O

clean:
	rm -f ./client ./server *.o

%.o: %.c Makefile
	${CC} ${CFLAGS} -c $<
