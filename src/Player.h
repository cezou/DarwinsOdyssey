#ifndef PLAYER_H
#define PLAYER_H

#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include <iostream>
#include <string>

class Player : public olc::PixelGameEngine{

    private:

    public:
        float posX;
        float posY;

        float vitesseX;
        float vitesseY;
        Player();
        void move (float fElapsedTime);
        
    
};

#endif