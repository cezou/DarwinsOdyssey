#include "./Ennemi_Fish.h"

Ennemi_Fish::Ennemi_Fish(){
    
    	fEnnemiPosX = 3.0f;
		fEnnemiPosY = 3.0f;
		fEnnemiVelX = 0.0f;
		fEnnemiVelY = 0.0f;
        nTileWidth = 32;
		nTileHeight = 32;
}

Ennemi_Fish::Ennemi_Fish(float posX, float posY, int level_param){
    
    	fEnnemiPosX = posX;
		fEnnemiPosY = posY;
		fEnnemiVelX = 0.0f;
		fEnnemiVelY = 0.0f;
        nTileWidth = 32;
		nTileHeight = 32;
        ennemiLevel = level_param;
}

void Ennemi_Fish::move(float fElapsedTime){

    fEnnemiPosX = fEnnemiPosX + fEnnemiVelX * fElapsedTime;
    fEnnemiPosY = fEnnemiPosY + fEnnemiVelY * fElapsedTime;

}

// Pour ne pas sortir de la carte.
void Ennemi_Fish::limites_map_collisions(){

		if(fEnnemiVelY <= 0){
			if(fEnnemiVelY <= 0){	
				fEnnemiVelY = 0;
				fEnnemiPosY = 0;
			}	
		}

		if(fEnnemiVelY >= 0){
			if(fEnnemiVelY >= 41){	
				fEnnemiVelY = 0;
				fEnnemiPosY = 41;
			}	
		}
	
		if(fEnnemiVelX <= 0){
			if(fEnnemiVelX <= 0){	
				fEnnemiVelX = 0;
				fEnnemiPosX = 0;
			}	
		}

		if(fEnnemiVelX >= 0){
			if(fEnnemiVelX >= 58){	

				fEnnemiVelX = 0;
				fEnnemiPosX = 58;
			}	
		}
}

void Ennemi_Fish::setVel0(){
        fEnnemiVelX = 0.0f;
        fEnnemiVelY = 0.0f;
}