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

execute.o : src/execute.c
			$(CC) -c src/execute.c  -o execute.o $(CFLAGS)

decode.o : src/decode.c
			$(CC) -c src/decode.c  -o decode.o $(CFLAGS)

fetch.o : src/fetch.c
			$(CC) -c src/fetch.c  -o fetch.o $(CFLAGS)

functions.o : src/functions.c
			$(CC) -c src/functions.c  -o functions.o $(CFLAGS)

main.o : src/main.c
			$(CC) -c src/main.c  -o main.o $(CFLAGS)

clean :
			rm -rf *.o
