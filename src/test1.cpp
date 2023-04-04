// RATIO JOFRE RATIO
#define OLC_PGE_APPLICATION
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include "./Map.h"
#include <iostream>
#include <string>

class Example : public olc::PixelGameEngine
{
public:
	Example()
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
		
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		
		// Mouvements players
		mapLevel1.player1.setVel0();
		mapLevel1.player2.setVel0();

		mapLevel1.player1.detectKeysPlayer1(this);
		mapLevel1.player2.detectKeysPlayer2(this);

		mapLevel1.player1.limites_map_collisions();
		mapLevel1.player2.limites_map_collisions();
		mapLevel1.move(fElapsedTime, mapLevel1.player1);
		mapLevel1.move(fElapsedTime, mapLevel1.player2);
		mapLevel1.collisions(fElapsedTime, mapLevel1.player1);
		mapLevel1.collisions(fElapsedTime, mapLevel1.player2);

		mapLevel1.drawLevel(this);

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(800, 450, 2, 2, false, true))
		demo.Start();

	return 0;
}