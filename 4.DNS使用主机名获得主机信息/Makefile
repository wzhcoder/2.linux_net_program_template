all: test

test: test.o
	gcc -o test  test.o
test.o: test.c
	gcc -c test.c -o test.o

.PHONY:clean
clean:
	rm *.o 
	rm test