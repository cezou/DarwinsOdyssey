#ifndef MAP_H
#define MAP_H

#include "./Player.h"
#include <string>
#include <iostream>

using namespace std;


class Map{

    public:
        wstring sLevel;
        int nLevelWidth;
	    int nLevelHeight;
        int nb_cellules_b_placees;
        int nb_cellules_g_placees;
        Player player1;
        Player player2;

        int splitScreenLayerIndex, lineLayerIndex;

	    olc::Sprite* spriteTiles = nullptr;
	    olc::Decal* decTiles = nullptr;

        olc::Sprite* spritePlayer1 = nullptr;
	    olc::Decal* decPlayer1 = nullptr;

        olc::Sprite* spritePlayer2 = nullptr;
	    olc::Decal* decPlayer2 = nullptr;

        olc::Sprite* spriteFond = nullptr;
	    olc::Decal* decFond = nullptr;
    
    public:

        //constructeur par deufaut
        Map();
    
        //constructeur avec parametres
        Map(wstring slevel_param, int nLevelWidth_param, int nLevelHeight_param);

        void initImages(olc::PixelGameEngine* pge);

        void drawLevel(olc::PixelGameEngine* pge);


};

    
    
#endif
