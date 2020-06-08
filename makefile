CFLAGS = -ansi -Wall -pedantic
CC = gcc

all: main title principals common binary name 
	$(CC) $(CFLAGS) title.o principals.o common.o binary.o name.o main.o -o a3 

clean:
	rm -rf main ds_memory ds_array*.o *.txt *.bin
	
main: main.c
	$(CC) $(CFLAGS) main.c -o main.o -c

title: title.c title.h
	$(CC) $(CFLAGS) title.c -o title.o -c

principals: principals.c principals.h
	$(CC) $(CFLAGS) principals.c -o principals.o -c	
	
common: common.c common.h
	$(CC) $(CFLAGS) common.c -o common.o -c	

binary: binary.c binary.h
	$(CC) $(CFLAGS) binary.c -o binary.o -c	
	
name: name.c name.h
	$(CC) $(CFLAGS) name.c -o name.o -c		

run: all
	./a3 
