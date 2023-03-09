all: ./exec/prog

./exec/prog: ./obj/Map.o ./obj/Player.o ./obj/exemple.o
	g++ -o ./obj/exemple.o ./obj/Map.o ./obj/Player.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

./obj/exemple.o: ./obj/Map.o ./obj/Player.o
	g++ -o ./obj/exemple.o ./src/exemple.cpp ./obj/Map.o ./obj/Player.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

./obj/Map.o: ./src/Player.o
	g++ -o ./obj/Map.o ./src/Map.cpp ./src/Player.o -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

./obj/Player.o:
	g++ -o ./obj/Player.o ./src/Player.cpp -lX11 -lGL -lpthread -lpng -lstdc++fs -std=c++17

clean:
	rm -f *.o ./exec/prog