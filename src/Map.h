#ifndef MAP_H
#define MAP_H

#include "./Player.h"
#include "./Ennemi_Fish.h"
#include <string>
#include <iostream>

using namespace std;

const int numeroFish = 10;

/*
    \class Map Map.h "src/Map.h"
*/

class Map{

    public:

        // map en format texte
        wstring sLevel;

        // taille de la map
        int nLevelWidth;
	    int nLevelHeight;

        // Niveau de la map
        int niveauMap;

        // nombre de cellules à récuperer (blue et green)
        int nb_cellules_b_placees;
        int nb_cellules_g_placees;

        // déclaration joueur 1 et 2
        Player player1;
        Player player2;

        // calque de l'écran scindé, pour le mettre en dessus de la ligne vertical au milieu de l'écran 
        int splitScreenLayerIndex;
        
        // calque pour dessiner la ligne qui sépare les deux écrans
        int lineLayerIndex;

        bool stop_a_droite;
        bool stop_a_gauche;
        int compt;

        Ennemi_Fish tabFish[numeroFish];

        // déclaration des images (Sprite utilise le CPU et Decal utilise GPU lors de l'affiche)
	    olc::Sprite* spriteTiles = nullptr;
	    olc::Decal* decTiles = nullptr;

        olc::Sprite* spritePlayer1 = nullptr;
	    olc::Decal* decPlayer1 = nullptr;

        olc::Sprite* spritePlayer2 = nullptr;
	    olc::Decal* decPlayer2 = nullptr;

        olc::Sprite* spritePlayerLevel0 = nullptr;
	    olc::Decal* decPlayerLevel0 = nullptr;

        olc::Sprite* spritePlayerLevel1 = nullptr;
	    olc::Decal* decPlayerLevel1 = nullptr;

        olc::Sprite* spritePlayerLevel2 = nullptr;
	    olc::Decal* decPlayerLevel2 = nullptr;

        olc::Sprite* spritePlayerLevel3 = nullptr;
	    olc::Decal* decPlayerLevel3 = nullptr;

        olc::Sprite* spriteFond = nullptr;
	    olc::Decal* decFond = nullptr;

        olc::Sprite* spriteMultiCell = nullptr;
        olc::Decal* decMultiCell = nullptr;

        olc::Sprite* spriteCellRecupPlayer1 = nullptr;
        olc::Decal* decCellRecupPlayer1 = nullptr;

        olc::Sprite* spriteCellRecupPlayer2 = nullptr;
        olc::Decal* decCellRecupPlayer2 = nullptr;

        olc::Sprite* spriteVirus = nullptr;
        olc::Decal* decVirus = nullptr;

        olc::Sprite* spriteMap = nullptr;
        
        olc::Sprite* spriteBackGroundLevel2 = nullptr;
    
    public:

        // \brief constructeur par deufaut
        Map();

        // \brief initialisation des images
        // @param[in] pge pointeur vers la bibliothèque OlcPixelGameEngine 
        // pour pouvoir l'utiliser dans la fonction
        void initImages(olc::PixelGameEngine* pge);

        // \brief initialisation de la carte depuis une image png
        // @param[in] pge pointeur vers la bibliothèque OlcPixelGameEngine 
        // pour pouvoir l'utiliser dans la fonction
        void initMapFromImage(olc::PixelGameEngine* pge);    

        // \brief mouvements joueurs et collisions
        // @param[in] fElapsedTime float (temps entre une image et la suivante)
        // @param[in] P Player passé par référence
        void move(float fElapsedTime, Player& P);

        void collisions (float fElapsedTime, Player& P);
        
        // \brief dessiner le niveau
        // @param[in] pge pointeur vers la bibliothèque OlcPixelGameEngine 
        // pour pouvoir l'utiliser dans la fonction
        void drawLevel(olc::PixelGameEngine* pge);

        // \brief dessiner le niveau
        // @param[in] pge pointeur vers la bibliothèque OlcPixelGameEngine 
        // pour pouvoir l'utiliser dans la fonction
        void drawLevel2(olc::PixelGameEngine* pge);

        // \brief savoir dans quel niveau on est
        // pour pouvoir l'utiliser dans la fonction
        int checkLevel(Player& P1, Player& P2);

        void initEnnemis();

        void setVelEnnemi();

        void replaceEnnemi();

        void collisionsMap(Player &P);

        void collisionsEnnemiFish(Player &P);


};

    
    
#endif
