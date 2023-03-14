#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include "./Player.h"

Player::Player(){
    
	fCameraPosX = 0.0f;
    fCameraPosY = 0.0f;

    fPlayerPosX = 1.0f;
	fPlayerPosY = 1.0f;
	fPlayerVelX = 0.0f;
	fPlayerVelY = 0.0f;
    
}


void Player::move(float fElapsedTime){

        fPlayerVelY = 0.0f;
        fPlayerVelX = 0.0f;
        if(IsFocused()){
            if(GetKey(olc::Key::UP).bHeld){
                fPlayerVelY = -6.0f;
            }

            if(GetKey(olc::Key::DOWN).bHeld){
                fPlayerVelY = 6.0f;
            }

            if(GetKey(olc::Key::LEFT).bHeld){
                fPlayerVelX = -6.0f;
            }

            if(GetKey(olc::Key::RIGHT).bHeld){
                fPlayerVelX = 6.0f;
            }
        }

        fPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
        fPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;
}




