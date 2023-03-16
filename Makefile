all: ./test

./test: obj/test.o obj/Map.o obj/Player.o
	g++ -o ./test obj/test.o obj/Map.o obj/Player.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

obj/test.o: ./src/test.cpp ./src/Map.h
	g++ -c -o obj/test.o ./src/test.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

obj/Map.o: ./src/Map.cpp ./src/Map.h ./src/Player.h
	g++ -c -o obj/Map.o ./src/Map.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

obj/Player.o: ./src/Player.cpp ./src/Player.h
	g++ -c -o obj/Player.o ./src/Player.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

clean:
	rm -rf exec/* obj/*