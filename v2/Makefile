#THe compiler to use : GCC
CC=gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -lm

#files to link:
#LFLAGS = -lcs50


EXEC = VCORE

all : $(EXEC) clean

VCORE : execute.o decode.o fetch.o functions.o main.o
			$(CC) execute.o decode.o fetch.o functions.o main.o -lm -o VCORE

execute.o : execute.c
			$(CC) -c execute.c  -o execute.o $(CFLAGS)

decode.o : decode.c
			$(CC) -c decode.c  -o decode.o $(CFLAGS)

fetch.o : fetch.c
			$(CC) -c fetch.c  -o fetch.o $(CFLAGS)

functions.o : functions.c
			$(CC) -c functions.c  -o functions.o $(CFLAGS)

main.o : main.c
			$(CC) -c main.c  -o main.o $(CFLAGS)

clean :
			rm -rf *.o
