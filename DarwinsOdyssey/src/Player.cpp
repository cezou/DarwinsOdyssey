#include "./Player.h"

Player::Player(){
    	fCameraPosX = 0.0f;
    	fCameraPosY = 0.0f;
    	fPlayerPosX = 1.0f;
		fPlayerPosY = 1.0f;
		fPlayerVelX = 0.0f;
		fPlayerVelY = 0.0f;
        nTileWidth = 32;
		nTileHeight = 32;
        
}

Player::Player(float posX, float posY){
    	fCameraPosX = 0.0f;
    	fCameraPosY = 0.0f;
    	fPlayerPosX = posX;
		fPlayerPosY = posY;
		fPlayerVelX = 0.0f;
		fPlayerVelY = 0.0f;
        nTileWidth = 32;
		nTileHeight = 32;
        
}

void Player::move(float fElapsedTime){

    	fPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
        fPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

}

void Player::collisions(){

		if(fPlayerVelY <= 0){
			if(fPlayerPosY <= 0){	
				fPlayerVelY = 0;
				fPlayerPosY = 0;
			}	
		}

		if(fPlayerVelY >= 0){
			if(fPlayerPosY >= 15){	
				fPlayerVelY = 0;
				fPlayerPosY = 15;
			}	
		}
	
		if(fPlayerVelX <= 0){
			if(fPlayerPosX <= 0){	
				fPlayerVelX = 0;
				fPlayerPosX = 0;
			}	
		}

		if(fPlayerVelX >= 0){
			if(fPlayerPosX >= 63){	

				fPlayerVelX = 0;
				fPlayerPosX = 63;
			}	
		}
}

void Player::setVel0(){
        fPlayerVelY = 0.0f;
        fPlayerVelX = 0.0f;
        
}

void Player::setNBCell() {
    NbCelluleRecup = 0;
}

void Player::detectKeysPlayer1(olc::PixelGameEngine* pge){

        // Mouvements player 1
         if (pge->IsFocused()) {

        // aller en haut pour clavier qwerty et azerty
        if (pge->GetKey(olc::Key::W).bHeld || pge->GetKey(olc::Key::Z).bHeld) {
            fPlayerVelY = -10.0f;
        }

        // aller en bas
        if (pge->GetKey(olc::Key::S).bHeld) {
            fPlayerVelY = 10.0f;
        }

        // aller à gauche pour clavier qwerty et azerty
        if (pge->GetKey(olc::Key::A).bHeld || pge->GetKey(olc::Key::Q).bHeld) {
            fPlayerVelX = -10.0f;
        }

        // aller à droite
        if (pge->GetKey(olc::Key::D).bHeld) {
            fPlayerVelX = 10.0f;
        }

        }	
}

void Player::detectKeysPlayer2(olc::PixelGameEngine* pge){

    	// Mouvements player 2
        if (pge->IsFocused()) {

        // Aller en haut
        if (pge->GetKey(olc::Key::UP).bHeld) {
            fPlayerVelY = -10.0f;
        }

        // Aller en bas
        if (pge->GetKey(olc::Key::DOWN).bHeld) {
            fPlayerVelY = 10.0f;
        }

        // Aller à gauche
        if (pge->GetKey(olc::Key::LEFT).bHeld) {
            fPlayerVelX = -10.0f;
        }

        // Aller à droite
        if (pge->GetKey(olc::Key::RIGHT).bHeld) {
            fPlayerVelX = 10.0f;
        }


        }
}


