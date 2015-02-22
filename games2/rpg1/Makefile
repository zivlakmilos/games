all: main.o game.o
    g++ -o rpg main.o game.o -lSDLmain -lSDL -lGL

main.o: main.cpp headers.h
    g++ -c -o main.o main.cpp

game.o: game.cpp headers.h
    g++ -c -o game.o main.cpp

clean:
    rm -rf *.o
    rm rpg
