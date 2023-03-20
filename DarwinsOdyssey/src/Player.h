#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"


using namespace std;

class Player{


    public:

        //position de la camera
        float fCameraPosX;
        float fCameraPosY;

        //pasition du joueur
        float fPlayerPosX;
	    float fPlayerPosY;

        //vitesse du joueur
	    float fPlayerVelX;
	    float fPlayerVelY;

        //tiles de l'écran du joueur
        int nTileWidth;
        int nTileHeight;

        //tiles visibles de l'écran du joueur
        int nVisibleTilesX;
        int nVisibleTilesY;

        //décalage de la camera
        float fOffsetX;
        float fOffsetY;
        float fTileOffsetX;
        float fTileOffsetY;

        //nombre de cellules récupérées.
        unsigned int NbCelluleRecup;

        //constructeur par defaut
        Player();

        // constructeur avec position comme parametre
        Player(float posX, float posY);

        // mouvements du joueur
        void move (float fElapsedTime);

        // collisions du joueur
        void collisions ();

        // set vitesse à 0
        void setVel0 ();

        // init NBCell à 0
        void setNBCell();

        // touches du clavier player1
        void detectKeysPlayer1(olc::PixelGameEngine* pge);

        // touches du clavier player2
        void detectKeysPlayer2(olc::PixelGameEngine* pge);

};
        

#endif