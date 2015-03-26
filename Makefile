# définition des cibles particulières
.PHONY: clean, mrproper
  
#désactivation des règles implicites
.SUFFIXES:

CC = gcc
CFLAGS = -W 

all: main.o frozen.o json.o
	$(CC) main.o frozen.o json.o -o rmanager

main.o: frozen.c json.c main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

json.o: json.c
	$(CC) -c json.c -o json.o $(CFLAGS)

frozen.o: frozen.c
	$(CC) -c frozen.c -o frozen.o $(CFLAGS)

# clean
clean:
	rm -rf *.bak rm -rf *.o

# mrproper
mrproper: clean
	rm -rf Programme
