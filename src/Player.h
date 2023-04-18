#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
using namespace std;

/*!
\brief Classe représentant un joueur dans le jeu Darwin's Odyssey.
\details Cette classe gère les mouvements et les collisions du joueur, ainsi que sa position sur l'écran et la caméra.
*/

class Player{


    public:

        
        float fCameraPosX; /**< Position de la caméra en X */
        float fCameraPosY; /**< Position de la caméra en Y */

        
        float fPlayerPosX; /**< Position du joueur en X */
        float fPlayerPosY; /**< Position du joueur en Y */

        
        float fNewPlayerPosX; /**< Nouvelle Position du joueur en X  */
        float fNewPlayerPosY; /**< Nouvelle Position du joueur en Y */

        
        float fPlayerVelX; /**< Vitesse du joueur en X */
        float fPlayerVelY; /**< Vitesse du joueur en Y */

        
        int nTileWidth; /**< Largeur en tiles de l'écran du joueur */
        int nTileHeight; /**< Hauteur en tiles de l'écran du joueur */

        
        int nVisibleTilesX; /**< Nombre de tiles horizontalement visibles dans l'écran du joueur */
        int nVisibleTilesY; /**< Nombre de tiles verticalement visibles dans l'écran du joueur */

        
        float fOffsetX; /**< Décalage de la caméra en X */
        float fOffsetY; /**< Décalage de la caméra en Y */
        float fTileOffsetX; /**< Décalage des tiles en X */
        float fTileOffsetY; /**< Décalage des tiles en Y */

        
        unsigned int NbCelluleRecup; /**< Nombre de cellules récupérées par le joueur */

        /**
         * @brief Constructeur par défaut de la classe Player
         *
         */
        Player();

        /**
         * @brief Constructeur avec position comme paramètre
         *
         * @param posX Position en X du joueur
         * @param posY Position en Y du joueur
         */
        Player(float posX, float posY);

        /**
         * @brief Fonction permettant de mettre à jour la position du joueur en fonction de sa vitesse et du temps écoulé
         *
         * @param fElapsedTime Temps écoulé depuis la dernière mise à jour (entre une image et la suivante)
         */
        void move(float fElapsedTime);

        /**
         * @brief Fonction gérant les collisions du joueur avec les limites de la carte.
         *
         */
        void limites_map_collisions();

        /**
         * @brief Fonction permettant de mettre la vitesse du joueur à 0
         *
         */
        void setVel0();

        /**
         * @brief Fonction permettant d'initialiser le nombre de cellules récupérées à 0
         *
         */
        void setNBCell();

        /**
         * @brief Fonction permettant de détecter les touches du clavier pour le joueur 1
         *
         * @param pge Pointeur vers la classe PixelGameEngine
         */
        void detectKeysPlayer1(olc::PixelGameEngine* pge);

        /**
        * @brief Détermine les touches du clavier pour le joueur 2.
        *
        * @param pge Pointeur vers l'instance de PixelGameEngine utilisée.
        */
        void detectKeysPlayer2(olc::PixelGameEngine* pge);


};
        

#endif