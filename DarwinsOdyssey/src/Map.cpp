#include <iostream>
#include <fstream>
#include "./Map.h"

//#include "./Player.h"

using namespace std;



//constructeur par defaut
Map::Map(){

    nLevelWidth = 64;
	nLevelHeight = 16;
	nb_cellules_prises = 0;
	sLevel += L"#.$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#";
	sLevel += L"#..........o...................$..$$$......$$$............ooo..#";
	sLevel += L"#..........................................................oo..#";
	sLevel += L"#........................................o..................o..#";
	sLevel += L"#..............................................................#";
	sLevel += L"#..........................o...................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#....................................o.........................#";
	sLevel += L"#..................................................o...........#";
	sLevel += L"#...............#####..........................................#";
	sLevel += L"#...............#.o.#..........................................#";
	sLevel += L"#...............#...#..........................................#";
	sLevel += L"#........................................o.....................#";
	sLevel += L"#..o.................o.........................................#";
	sLevel += L"#$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#";
}

//constructeur avec parametres
Map::Map(wstring sLevel_param, int nLevelWidth_param, int nLevelHeight_param){
    sLevel = sLevel_param;
    nLevelWidth = nLevelWidth_param;
    nLevelHeight = nLevelHeight_param;
}

void Map::setPlayerVelX(float fPlayerVelX_param){
	player1.fPlayerVelX = fPlayerVelX_param;
}

void Map::setPlayerVelY(float fPlayerVelY_param){
	player1.fPlayerVelY = fPlayerVelY_param;
}

int Map::getNLevelWidth(){
    return nLevelWidth;
}

int Map::getNLevelHeight(){
    return nLevelHeight;
}




