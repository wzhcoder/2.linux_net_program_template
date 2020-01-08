all: server client

server: server.o process.o
	gcc -o server server.c  process.o


client: client.c process.o
	gcc -o client client.c process.o

process.o:
	gcc -c process.c -o process.o

.PHONY: clean
clean:
	rm *.o 
	rm server client