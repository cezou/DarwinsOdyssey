#ifndef MENU_H
#define MENU_H

#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include <string>
#include <iostream>
using namespace std;

/*
    \class Menu Menu.h "src/Menu.h"
*/

class Menu
{

public:
    bool bMenu; /**< Booléen pour savoir si on est dans le menu ou non */

    // déclaration des images (Sprite utilise le CPU et Decal utilise GPU lors de l'affiche)
    olc::Sprite *spriteMenuPause = nullptr;
    olc::Decal *decMenuPause = nullptr;

public:
    // \brief constructeur par deufaut
    Menu();

    void initImageMenu(olc::PixelGameEngine *pge);
    // \brief renvoie le booléen bMenu qui dit si l'on est dans le menu ou non
    // \param pge est un pointeur sur la bibliothèque PixelGameEngine pour pouvoir utiliser ses fonctions
    bool bMenuPause(olc::PixelGameEngine *pge);

    // \brief affiche le menu pause
    // \param pge est un pointeur sur la bibliothèque PixelGameEngine pour pouvoir utiliser ses fonctions
    void afficherMenuPause(olc::PixelGameEngine *pge);
};

#endif
