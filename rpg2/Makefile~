all: linux windows


linux: main.o game.o player.o
	g++ -o rpg main.o game.o player.o -lSDLmain -lSDL -lGL -lSDL_image

main.o: main.cpp
	g++ -c -o main.o main.cpp

game.o: game.cpp
	g++ -c -o game.o game.cpp

player.o: player.cpp
	g++ -c -o player.o player.cpp


windows: mainW.o gameW.o playerW.o
	i686-w64-mingw32-g++ -o rpg.exe mainW.o gameW.o playerW.o -static-libgcc -static-libstdc++ -lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32 -lSDL_image

mainW.o: main.cpp
	i686-w64-mingw32-g++ -c -o mainW.o main.cpp

gameW.o: game.cpp
	i686-w64-mingw32-g++ -c -o gameW.o game.cpp

playerW.o: player.cpp
	i686-w64-mingw32-g++ -c -o playerW.o player.cpp


clean:
	rm -rf *.o rpg rpg.exe
