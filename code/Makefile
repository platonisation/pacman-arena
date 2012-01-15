CC=g++
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=-lsfml-graphics -lsfml-network
EXEC=Pacman_Arena Pacman_Serv

all: $(EXEC)

Pacman_Arena: main.o create.o join.o menu.o play.o option.o myOption.o Party.o Character.o network.o Pacman_Serv
	$(CC) -o $@ main.o create.o join.o menu.o play.o option.o myOption.o Party.o Character.o $(LDFLAGS)

Pacman_Serv: server.o Party.o Character.o network.o
	$(CC) -o $@ server.o Party.o Character.o network.o $(LDFLAGS)

main.o: main.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

create.o: create.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

join.o: join.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

menu.o: menu.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

play.o: play.cpp action.h myOption.h network.h
	$(CC) -o $@ -c $< $(CFLAGS)

option.o: option.cpp action.h myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

myOption.o: myOption.cpp myOption.h
	$(CC) -o $@ -c $< $(CFLAGS)

Character.o: Character.cpp Character.h
	$(CC) -o $@ -c $< $(CFLAGS)
	
Party.o: Party.cpp Party.h Character.h
	$(CC) -o $@ -c $< $(CFLAGS)

server.o: server.cpp network.h
	$(CC) -o $@ -c $< $(CFLAGS)

network.o: network.cpp network.h Party.h Character.h
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)
