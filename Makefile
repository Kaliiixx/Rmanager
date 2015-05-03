# définition des cibles particulières
.PHONY: clean, mrproper
  
#désactivation des règles implicites
.SUFFIXES:

CC = gcc
CFLAGS = -Werror

all: main.o json.o cli.o file.o
	$(CC) main.o json.o cli.o file.o -o rmanager

main.o: main.c 
	$(CC) -c main.c -o main.o $(CFLAGS)

json.o: json.c 
	$(CC) -c json.c -o json.o $(CFLAGS)

cli.o: cli.c
	$(CC) -c cli.c -o cli.o  $(CFLAGS)

file.o: file.c
	$(CC) -c file.c -o file.o $(CFLAGS)

# clean
clean:
	rm -rf *.bak rm -rf *.o

# mrproper
mrproper: clean
	rm -rf Programme
