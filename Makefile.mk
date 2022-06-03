CC=g++
CFLAGS=-g -std=c++11 -lSDL2 -lSDL2_image -I.
DEPS = Socket.h ClientServer.h GameManager.h Texture.h Game.h GameObject.h
OBJ = Socket.o ClientServer.o GameManager.o Texture.o Game.o 
LIBS=-lpthread 

%.o: %.gc $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

all: gs gc

gs: $(OBJ) GameServer.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)

gc: $(OBJ) GameClient.o
	g++ -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean

clean:
	rm -f *.o gs gc

