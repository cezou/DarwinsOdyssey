// RATIO JOFRE RATIO
#define OLC_PGE_APPLICATION
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include "./Map.h"
#include <iostream>
#include <string>
#include <ctime>

const float velPlayerLevel1 = 8.0f;
const float velPlayerLevel2 = 250.0f;

/*!
 *  \brief		PROJET FINAL LIFAPCD: Darwin's Odyssey.
 *  \details	Ce fichier est le fichier principal du jeu, où se trouve le main.
				Ce projet est un jeu sous la forme d’un 2D Platformer en coop (2 joueurs sur un même ordinateur). 
				Il faut résoudre des énigmes pour retracer l’évolution de l’homme. (en suivant la Théorie de Darwin)
 *	\author		P2105932 Jofre COLL
 *	\author		P2109844 Césaire VIEGAS
 *  \date		Février-Mai 2023
 */


class DarwinsOdyssey : public olc::PixelGameEngine
{
public:
	DarwinsOdyssey()
	{
		sAppName = "Darwin's Odyssey";
	}

	//int nLayerEcranGauche = 0;
	//int nLayerEcranDroit = 0;
	//int nLayerLigne = 3;
    Map mapLevel1;
	

public:
	bool OnUserCreate() override
	{

		mapLevel1.initImages(this);
		mapLevel1.initMapFromImage(this);
		// Set du NB de Cellules Récupérées à zéro
		mapLevel1.player1.setNBCell();
		mapLevel1.player2.setNBCell();

		// Créer un calque pour l'écran scindé
		mapLevel1.splitScreenLayerIndex = CreateLayer();
		SetLayerOffset(mapLevel1.splitScreenLayerIndex, { 0.0f, 0.0f });
		SetLayerScale(mapLevel1.splitScreenLayerIndex, { 1.0f, 1.0f });
		EnableLayer(mapLevel1.splitScreenLayerIndex, true);

		// Créer un calque pour la ligne noire verticale
		mapLevel1.lineLayerIndex = CreateLayer();
		SetLayerOffset(mapLevel1.lineLayerIndex, { 0.0f, 0.0f });
		SetLayerScale(mapLevel1.lineLayerIndex, { 1.0f, 1.0f });
		EnableLayer(mapLevel1.lineLayerIndex, true);

		mapLevel1.setVelEnnemi();
		mapLevel1.initEnnemis();
		
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		

		// LEVEL 0

		if(mapLevel1.checkLevel(this, mapLevel1.player1, mapLevel1.player2) == 0){
			mapLevel1.drawLevel0(this);
		}
		
		// LEVEL 1
		
		
		if(mapLevel1.checkLevel(this, mapLevel1.player1, mapLevel1.player2) == 1){
			// Mouvements players
			mapLevel1.player1.setVel0();
			mapLevel1.player2.setVel0();

			mapLevel1.player1.detectKeysPlayer1(this, velPlayerLevel1);
			mapLevel1.player2.detectKeysPlayer2(this, velPlayerLevel1);

			mapLevel1.player1.limites_map_collisions();
			mapLevel1.player2.limites_map_collisions();
			mapLevel1.move(fElapsedTime, mapLevel1.player1);
			mapLevel1.move(fElapsedTime, mapLevel1.player2);
			mapLevel1.collisions(fElapsedTime, mapLevel1.player1);
			mapLevel1.collisions(fElapsedTime, mapLevel1.player2);

			mapLevel1.drawLevel1(this);
		}

		// LEVEL 2

		if(mapLevel1.checkLevel(this, mapLevel1.player1, mapLevel1.player2) == 2){
		
			mapLevel1.player1.setVel0();
			mapLevel1.player2.setVel0();

			mapLevel1.player1.detectKeysPlayer1(this, velPlayerLevel2);
			mapLevel1.player2.detectKeysPlayer2(this, velPlayerLevel2);

			//mapLevel1.player1.limites_map_collisions();
			//mapLevel1.player2.limites_map_collisions();
			mapLevel1.move(fElapsedTime, mapLevel1.player1);
			mapLevel1.move(fElapsedTime, mapLevel1.player2);
			//mapLevel1.collisions2(fElapsedTime, mapLevel1.player1);
			//mapLevel1.collisions2(fElapsedTime, mapLevel1.player2);

			
			for(int i = 0; i<numeroFish; i++){
				mapLevel1.tabFish[i].move(fElapsedTime);
			}
		
			mapLevel1.replaceEnnemi();
			
			mapLevel1.collisionsMap(mapLevel1.player1);
			mapLevel1.collisionsMap(mapLevel1.player2);

			mapLevel1.collisionsEnnemiFish(mapLevel1.player1);
			mapLevel1.collisionsEnnemiFish(mapLevel1.player2);
			
			mapLevel1.drawLevel2(this);
			cout<<"Numero points player 1 = " << mapLevel1.player1.numeroPoints << endl;
			cout<<"Numero points player 2 = " << mapLevel1.player2.numeroPoints << endl;
			cout<< "Numero vies = " << mapLevel1.vies << endl;
			 
		}
		return true;
	}
};


int main()
{
	srand(time(NULL));

	DarwinsOdyssey DO;
	if (DO.Construct(800, 450, 2, 2, false, true))
		DO.Start();

	return 0;
}