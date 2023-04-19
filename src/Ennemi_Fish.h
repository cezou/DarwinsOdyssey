#ifndef ENNEMI_FISH_H
#define ENNEMI_FISH_H

#include <string>
#include <iostream>
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"

using namespace std;

/*!
\brief Classe représentant un ennemi du niveau 2 dans le jeu Darwin's Odyssey.
\details Cette classe gère les mouvements et les collisions du joueur, ainsi que sa position sur l'écran.
*/

class Ennemi_Fish{
    public:
        // Position (x, y)
        float fEnnemiPosX;
        float fEnnemiPosY;

        // Niveau du poisson
        int ennemiLevel;

        float fEnnemiVelX; /**< Vitesse du joueur en X */
        float fEnnemiVelY; /**< Vitesse du joueur en Y */

        int nTileWidth; /**< Largeur en tiles de l'écran du joueur */
        int nTileHeight; /**< Hauteur en tiles de l'écran du joueur */

        /**
         * @brief Constructeur par défaut de la classe Player
         *
         */
        Ennemi_Fish();

        /**
         * @brief Constructeur avec position comme paramètre
         *
         * @param posX Position en X du joueur
         * @param posY Position en Y du joueur
         */
        Ennemi_Fish(float posX, float posY, int level_param);

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

    private:

};

#endif