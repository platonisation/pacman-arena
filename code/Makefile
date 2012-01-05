CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lsfml-graphics -lsfml-network
EXEC=Pacman_Arena Pacman_Serv

all: $(EXEC)

Pacman_Arena: main.o create.o join.o menu.o play.o option.o myOption.o Pacman_Serv
	$(CC) -o $@ main.o create.o join.o menu.o play.o option.o myOption.o $(LDFLAGS)

Pacman_Serv: server.o
	$(CC) -o $@ server.o $(LDFLAGS)

main.o: main.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

create.o: create.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

join.o: join.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

menu.o: menu.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

play.o: play.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

option.o: option.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

myOption.o: myOption.cpp myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

server.o: server.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)
