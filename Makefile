make: build run

build:
	gcc -o main main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

run:
	./main