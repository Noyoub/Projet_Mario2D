CC = gcc
CFLAGS = -W -Wall  #windows


INCLUDES = -I ../include
LIBS = -L ../lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf
EXEC = ../bin/mario2d

OBJ= sons.o polices.o dessin.o init.o input.o map.o joueur.o monstre.o menu.o main.o 
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(INCLUDES) $(LIBS)


%.o: %.c 
	$(CC) -o $@ -c $< $(INCLUDES) $(LIBS)

clean:
	del /f *.o

# commande de compilation
#gcc src/main.c src/menu.c src/sons.c src/polices.c src/dessin.c src/init.c src/input.c src/map.c src/joueur.c src/monstre.c -o bin/mario2d -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf