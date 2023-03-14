#ifndef PLAYER_H
#define PLAYER_H

#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include <iostream>
#include <string>

class Player : public olc::PixelGameEngine{

    private:

    public:
        float fCameraPosX;
        float fCameraPosY;

        float fPlayerPosX;
        float fPlayerPosY;

        float fPlayerVelX;
        float fPlayerVelY;

        Player();
        
        void move (float fElapsedTime);
        
    
};

#endif