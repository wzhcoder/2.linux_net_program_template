all: server client

server: socket_server.o
	gcc -o server socket_server.o  
socket_server.o: socket_server.c
	gcc -c socket_server.c  		-o socket_server.o

client: socket_client.o
	gcc -o client socket_client.o
socket_client.o: socket_client.c
	gcc -c socket_client.c      	-o socket_client.o

.PHONY: clean
clean:
	rm *.o 
	rm server client