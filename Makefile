all: test1

test1: obj/test1.o obj/Map.o obj/Player.o obj/Ennemi_Fish.o
	g++ -o test1 obj/test1.o obj/Map.o obj/Player.o obj/Ennemi_Fish.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

obj/test1.o: src/test1.cpp src/Map.h src/Player.h src/Ennemi_Fish.h
	g++ -c -o obj/test1.o src/test1.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

obj/Map.o: src/Map.cpp src/Map.h src/Player.h src/Ennemi_Fish.h
	g++ -c -o obj/Map.o src/Map.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

obj/Player.o: src/Player.cpp src/Player.h src/Map.h
	g++ -c -o obj/Player.o src/Player.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

obj/Ennemi_Fish.o: src/Ennemi_Fish.cpp src/Ennemi_Fish.h
	g++ -c -o obj/Ennemi_Fish.o src/Ennemi_Fish.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

clean:
	rm -rf test1 obj/*

