# raccourci pour ne pas avoir a ecrire le chemin de la lib
CFLAGS = -I/opt/homebrew/include -Wall
LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_mixer

game: background.o cube.o levels.o menu.o obstacles.o win.o jeu.o audio.o main.c
	gcc $(CFLAGS) background.o cube.o levels.o menu.o obstacles.o win.o jeu.o audio.o main.c -o game $(LDFLAGS)
background.o: background.c background.h
	gcc $(CFLAGS) -c background.c -o background.o
cube.o: cube.c cube.h
	gcc $(CFLAGS) -c cube.c -o cube.o
levels.o: levels.c levels.h
	gcc $(CFLAGS) -c levels.c -o levels.o
menu.o: menu.c menu.h
	gcc $(CFLAGS) -c menu.c -o menu.o
obstacles.o: obstacles.c obstacles.h
	gcc $(CFLAGS) -c obstacles.c -o obstacles.o
win.o: win.c win.h
	gcc $(CFLAGS) -c win.c -o win.o
jeu.o: jeu.c jeu.h
	gcc $(CFLAGS) -c jeu.c -o jeu.o
audio.o: audio.c audio.h
	gcc $(CFLAGS) -c audio.c -o audio.o
clean:
	rm -f *.o game
run:
	./game
all: clean game run