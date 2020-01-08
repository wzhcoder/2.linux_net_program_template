all: server client

server: server.c processer.c processer.h
	gcc -o server   server.c  processer.c 


client: client.c processer.c processer.h
	gcc -o client   client.c processer.c 


.PHONY: clean
clean:
	rm server client