#ifndef MAP_H
#define MAP_H

#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include <iostream>
#include <string>

using namespace std;

class Map : public olc::PixelGameEngine{

    private:
        wstring sLevel;
        int nLevelWidth;
	    int nLevelHeight;
        float fCameraPosX = 0.0f;
        float fCameraPosY = 0.0f;
    
    public:

        //constructeur par deufaut
        Map();

        //constructeur avec parametres
        Map(wstring slevel_param, int nLevelWidth_param, int nLevelHeight_param);

        //retourne nLevelWidth
        int getNLevelWidth();

        //retourne nLevelHeight
        int getNLevelHeight();

       void setCamera(float fElapsedTime);

       void drawPlayer();



};

    
    
#endif
