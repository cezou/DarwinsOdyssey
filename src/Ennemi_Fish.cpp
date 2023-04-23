#include "./Ennemi_Fish.h"

Ennemi_Fish::Ennemi_Fish(){
    
    	fEnnemiPosX = 0.0f;
		fEnnemiPosY = 0.0f;
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

void Ennemi_Fish::setVel(float velParam){
        fEnnemiVelX = velParam;
        fEnnemiVelY = velParam;
}