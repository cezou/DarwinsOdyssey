#ifndef MAP_H
#define MAP_H

#include "./Player.h"
#include <string>
#include <iostream>

using namespace std;


class Map{

    public:
        wstring sLevel;
        int nLevelWidth;
	    int nLevelHeight;
        int nb_cellules_prises;
        Player player1;
        Player player2;
    
    public:

        //constructeur par deufaut
        Map();
    
        //constructeur avec parametres
        Map(wstring slevel_param, int nLevelWidth_param, int nLevelHeight_param);

};

    
    
#endif
