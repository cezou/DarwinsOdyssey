#ifndef MAP_H
#define MAP_H

#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include <iostream>
#include <string>

using namespace std;

class Map : public olc::PixelGameEngine{

    public:
        wstring sLevel;
        int nLevelWidth;
	    int nLevelHeight;
        float fCameraPosX;
        float fCameraPosY;

        float fPlayerPosX;
	    float fPlayerPosY;
	    float fPlayerVelX;
	    float fPlayerVelY;
    
    public:

        //constructeur par deufaut
        Map();

        //constructeur avec parametres
        Map(wstring slevel_param, int nLevelWidth_param, int nLevelHeight_param);

        void setPlayerVelX (float fPlayerVelX_param);

        void setPlayerVelY (float fPlayerVelY);

        //retourne nLevelWidth
        int getNLevelWidth();

        //retourne nLevelHeight
        int getNLevelHeight();

       void setCamera(float fElapsedTime);

       void drawPlayer();



};

    
    
#endif
