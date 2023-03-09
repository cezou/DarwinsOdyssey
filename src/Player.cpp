#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include "./Player.h"

Player::Player(){
    posX=0.0f;
    posY=0.0f;

    vitesseX = 0.0f;
    vitesseY = 0.0f;
    
}


void Player::move(float fElapsedTime){

    vitesseY = 0.0f;
    vitesseX = 0.0f;
    if(IsFocused()){
        if(GetKey(olc::Key::UP).bHeld){
            vitesseY = -6.0f;
        }

        if(GetKey(olc::Key::DOWN).bHeld){
            vitesseY = 6.0f;
        }

        if(GetKey(olc::Key::LEFT).bHeld){
            vitesseY = -6.0f;
        }

        if(GetKey(olc::Key::RIGHT).bHeld){
            vitesseY = 6.0f;
        }
    }

    posX = posX + vitesseX * fElapsedTime;
    posY = posY + vitesseY * fElapsedTime;
    
}




