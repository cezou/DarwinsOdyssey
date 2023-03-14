#ifndef MAP_H
#define MAP_H

#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"

#include <string>
#include <iostream>

using namespace std;

struct Player{
    float fCameraPosX;
    float fCameraPosY;

    float fPlayerPosX;
	float fPlayerPosY;
	float fPlayerVelX;
	float fPlayerVelY;
};

class Map{

    public:
        wstring sLevel;
        int nLevelWidth;
	    int nLevelHeight;
	    Player player1;
        Player player2;

        int nb_cellules_prises;
        
    
    public:

        //constructeur par deufaut
        Map();
    
        //constructeur avec parametres
        Map(wstring slevel_param, int nLevelWidth_param, int nLevelHeight_param);

        void setPlayerVelX (float fPlayerVelX_param);

        void setPlayerVelY (float fPlayerVelY);

        //retourne nLevelWidth
        int getNLevelWidth();

        //retourne nLevelHeight
        int getNLevelHeight();

        /*

        void setCamera(float fElapsedTime);

        void drawPlayer();

        enum Key
	    {
		NONE,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		UP, DOWN, LEFT, RIGHT,
		SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
		BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
		NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
		NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
		EQUALS, COMMA, MINUS,
		OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8,
		CAPS_LOCK, ENUM_END
	    };

    	struct HWButton
	    {
		bool bPressed = false;	// Set once during the frame the event occurs
		bool bReleased = false;	// Set once during the frame the event occurs
		bool bHeld = false;		// Set true for all frames between pressed and released events
	    };

        HWButton	pKeyboardState[256] = { 0 };

       HWButton MyGetKey(Key k) const;

       */

};

    
    
#endif
