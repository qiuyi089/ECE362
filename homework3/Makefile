CC = gcc
CFLAGS = -Wall -std=c99 -g

all:flip pipe

flip: flip.o
	$(CC) $(CFLAGS) -o flip flip.o
pipe: pipe.o
	$(CC) $(FLAGS) -o pipe pipe.o

clean:
	rm *.o *.txt flip pipe
