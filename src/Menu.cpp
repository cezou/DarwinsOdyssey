#include <string>
#include <iostream>
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include "./Menu.h"
using namespace std;

Menu::Menu()
{

    bMenu = 0;
    // chargement des images
}

void Menu::initImageMenu(olc::PixelGameEngine *pge)
{

    // chargement des images
    spriteMenuPause = new olc::Sprite("./data/MenuPause.png");
    decMenuPause = new olc::Decal(spriteMenuPause);
}

bool Menu::bMenuPause(olc::PixelGameEngine *pge)
{

    if (pge->GetKey(olc::Key::ESCAPE).bPressed)
    {
        bMenu = !bMenu;
    }

    return bMenu;
}

void Menu::afficherMenuPause(olc::PixelGameEngine *pge)
{

    // affichage de l'image
    pge->SetDrawTarget(nullptr);
    pge->DrawDecal({0, 0}, decMenuPause, {1, 1});
}
