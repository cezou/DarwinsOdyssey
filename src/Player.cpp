#include "./Player.h"

Player::Player(){
    	fCameraPosX = 0.0f;
    	fCameraPosY = 0.0f;
    	fPlayerPosX = 3.0f;
		fPlayerPosY = 3.0f;
		fPlayerVelX = 0.0f;
		fPlayerVelY = 0.0f;
        nTileWidth = 32;
		nTileHeight = 32;
        level = 2;
        numeroPoints = 0;
        bDirection = 1;

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
        level = 2;
        numeroPoints = 0;
        bDirection = 1;

}

void Player::move(float fElapsedTime){

    	fPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime;
        fPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;

		fCameraPosX = fPlayerPosX;
		fCameraPosY = fPlayerPosY;

}


// Pour ne pas sortir de la carte.
void Player::limites_map_collisions(){

		if(fPlayerVelY <= 0){
			if(fPlayerPosY <= 0){	
				fPlayerVelY = 0;
				fPlayerPosY = 0;
			}	
		}

		if(fPlayerVelY >= 0){
			if(fPlayerPosY >= 41){	
				fPlayerVelY = 0;
				fPlayerPosY = 41;
			}	
		}
	
		if(fPlayerVelX <= 0){
			if(fPlayerPosX <= 0){	
				fPlayerVelX = 0;
				fPlayerPosX = 0;
			}	
		}

		if(fPlayerVelX >= 0){
			if(fPlayerPosX >= 58){	

				fPlayerVelX = 0;
				fPlayerPosX = 58;
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

void Player::detectKeysPlayer1(olc::PixelGameEngine* pge, float velPlayer){

        // Mouvements player 1
         if (pge->IsFocused()) {

        // aller en haut pour clavier qwerty et azerty
        if (pge->GetKey(olc::Key::W).bHeld || pge->GetKey(olc::Key::Z).bHeld) {
            fPlayerVelY = -velPlayer;
          
        }

        // aller en bas
        if (pge->GetKey(olc::Key::S).bHeld) {
            fPlayerVelY = velPlayer;
        }

        // aller à gauche pour clavier qwerty et azerty
        if (pge->GetKey(olc::Key::A).bHeld || pge->GetKey(olc::Key::Q).bHeld) {
            fPlayerVelX = -velPlayer;
            bDirection = 0;

        }

        // aller à droite
        if (pge->GetKey(olc::Key::D).bHeld) {
            fPlayerVelX = velPlayer;
            bDirection = 1;
        
        }

        }	
}

void Player::detectKeysPlayer2(olc::PixelGameEngine* pge, float velPlayer){

    	// Mouvements player 2
        if (pge->IsFocused()) {

        // Aller en haut
        if (pge->GetKey(olc::Key::UP).bHeld) {
            fPlayerVelY = -velPlayer;
        }

        // Aller en bas
        if (pge->GetKey(olc::Key::DOWN).bHeld) {
            fPlayerVelY = velPlayer;
        }

        // Aller à gauche
        if (pge->GetKey(olc::Key::LEFT).bHeld) {
            fPlayerVelX = -velPlayer;
            bDirection = 0;

        }

        // Aller à droite
        if (pge->GetKey(olc::Key::RIGHT).bHeld) {
            fPlayerVelX = velPlayer;
            bDirection = 1;

        }


        }
}

float Player::distance(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}