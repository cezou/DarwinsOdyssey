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
	
	olc::Sprite* spriteTiles = nullptr;
	olc::Decal* decTiles = nullptr;

    olc::Sprite* spritePlayer1 = nullptr;
	olc::Decal* decPlayer1 = nullptr;

    olc::Sprite* spritePlayer2 = nullptr;
	olc::Decal* decPlayer2 = nullptr;

    olc::Sprite* spriteFond = nullptr;
	olc::Decal* decFond = nullptr;

	int splitScreenLayerIndex, lineLayerIndex;
	//int nLayerEcranGauche = 0;
	//int nLayerEcranDroit = 0;
	//int nLayerLigne = 3;
    Map mapLevel1;

public:
	bool OnUserCreate() override
	{


		// Called once at the start, so create things here
		mapLevel1.player1.fCameraPosX = 0.0f;
    	mapLevel1.player1.fCameraPosY = 0.0f;
    	mapLevel1.player1.fPlayerPosX = 1.0f;
		mapLevel1.player1.fPlayerPosY = 1.0f;
		mapLevel1.player1.fPlayerVelX = 0.0f;
		mapLevel1.player1.fPlayerVelY = 0.0f;



		// initialisation player 2
		mapLevel1.player2.fCameraPosX = 0.0f;
    	mapLevel1.player2.fCameraPosY = 0.0f;

    	mapLevel1.player2.fPlayerPosX = 2.0f;
		mapLevel1.player2.fPlayerPosY = 2.0f;
		mapLevel1.player2.fPlayerVelX = 0.0f;
		mapLevel1.player2.fPlayerVelY = 0.0f;

		spriteTiles = new olc::Sprite("./data/parenchymadefault.png");
		decTiles = new olc:: Decal(spriteTiles);

        spritePlayer1 = new olc::Sprite("./data/alt/Cell-J1.png");
		decPlayer1 = new olc::Decal(spritePlayer1);

        spritePlayer2 = new olc::Sprite("./data/alt/Cell-J2.png");
		decPlayer2 = new olc::Decal(spritePlayer2);

        spriteFond = new olc::Sprite("./data/water.png");
		decFond = new olc::Decal(spriteFond);

		// Créer un calque pour l'écran scindé
		splitScreenLayerIndex = CreateLayer();
		SetLayerOffset(splitScreenLayerIndex, { 0.0f, 0.0f });
		SetLayerScale(splitScreenLayerIndex, { 1.0f, 1.0f });
		EnableLayer(splitScreenLayerIndex, true);

		// Créer un calque pour la ligne noire verticale
		lineLayerIndex = CreateLayer();
		SetLayerOffset(lineLayerIndex, { 0.0f, 0.0f });
		SetLayerScale(lineLayerIndex, { 1.0f, 1.0f });
		EnableLayer(lineLayerIndex, true);
		
		
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		auto GetTile = [&](int x, int y)
		{
			if (x >= 0 && x < mapLevel1.nLevelWidth && y >= 0 && y < mapLevel1.nLevelHeight)
				return mapLevel1.sLevel[y * mapLevel1.nLevelWidth + x];
			else
				return L' ';
		};

		auto SetTile = [&](int x, int y, wchar_t c)
		{
			if (x >= 0 && x < mapLevel1.nLevelWidth && y >= 0 && y < mapLevel1.nLevelHeight)
				mapLevel1.sLevel[y*mapLevel1.nLevelWidth + x] = c;
		};
		
		// Mouvements players
		mapLevel1.player1.fPlayerVelY = 0.0f;
        mapLevel1.player1.fPlayerVelX = 0.0f;

		mapLevel1.player2.fPlayerVelY = 0.0f;
        mapLevel1.player2.fPlayerVelX = 0.0f;

        if(IsFocused()){
			
			// Mouvements player 1
            if(GetKey(olc::Key::UP).bHeld){
                mapLevel1.player1.fPlayerVelY = -10.0f;
            }

            if(GetKey(olc::Key::DOWN).bHeld){
                mapLevel1.player1.fPlayerVelY = 10.0f;
            }

            if(GetKey(olc::Key::LEFT).bHeld){
                mapLevel1.player1.fPlayerVelX = -10.0f;
            }

            if(GetKey(olc::Key::RIGHT).bHeld){
                mapLevel1.player1.fPlayerVelX = 10.0f;
            }

			// Mouvements player 2
			if(GetKey(olc::Key::W).bHeld  || GetKey(olc::Key::Z).bHeld) {
                mapLevel1.player2.fPlayerVelY = -10.0f;
            }

            if(GetKey(olc::Key::S).bHeld){
                mapLevel1.player2.fPlayerVelY = 10.0f;
            }

            if(GetKey(olc::Key::A).bHeld || GetKey(olc::Key::Q).bHeld){
                mapLevel1.player2.fPlayerVelX = -10.0f;
            }

            if(GetKey(olc::Key::D).bHeld){
                mapLevel1.player2.fPlayerVelX = 10.0f;
            }

        }	

		// Collisions
		mapLevel1.player1.fPlayerPosX = mapLevel1.player1.fPlayerPosX + mapLevel1.player1.fPlayerVelX * fElapsedTime;
        mapLevel1.player1.fPlayerPosY = mapLevel1.player1.fPlayerPosY + mapLevel1.player1.fPlayerVelY * fElapsedTime;

		mapLevel1.player2.fPlayerPosX = mapLevel1.player2.fPlayerPosX + mapLevel1.player2.fPlayerVelX * fElapsedTime;
        mapLevel1.player2.fPlayerPosY = mapLevel1.player2.fPlayerPosY + mapLevel1.player2.fPlayerVelY * fElapsedTime;

		mapLevel1.player1.fCameraPosX = mapLevel1.player1.fPlayerPosX;
		mapLevel1.player1.fCameraPosY = mapLevel1.player1.fPlayerPosY;

		mapLevel1.player2.fCameraPosX = mapLevel1.player2.fPlayerPosX;
		mapLevel1.player2.fCameraPosY = mapLevel1.player2.fPlayerPosY;

		// Collisions Map - POUR NE PAS SORTIR DE LA CARTE
		// PLAYER 1
		if(mapLevel1.player1.fPlayerVelY <= 0){
			if(mapLevel1.player1.fPlayerPosY <= 0){	
				mapLevel1.player1.fPlayerVelY = 0;
				mapLevel1.player1.fPlayerPosY = 0;
			}	
		}

		if(mapLevel1.player1.fPlayerVelY >= 0){
			if(mapLevel1.player1.fPlayerPosY >= (float)mapLevel1.getNLevelHeight()){	
				mapLevel1.player1.fPlayerVelY = 0;
				mapLevel1.player1.fPlayerPosY = 16;
			}	
		}
	
		if(mapLevel1.player1.fPlayerVelX <= 0){
			if(mapLevel1.player1.fPlayerPosX <= 0){	
				mapLevel1.player1.fPlayerVelX = 0;
				mapLevel1.player1.fPlayerPosX = 0;
			}	
		}

		if(mapLevel1.player1.fPlayerVelX >= 0){
			if(mapLevel1.player1.fPlayerPosX >= (float)mapLevel1.getNLevelWidth()){	

				mapLevel1.player1.fPlayerVelX = 0;
				mapLevel1.player1.fPlayerPosX = 64;
			}	
		}
		

		// PLAYER 2
		if(mapLevel1.player2.fPlayerVelY <= 0){
			if(mapLevel1.player2.fPlayerPosY <= 0){	
				mapLevel1.player2.fPlayerVelY = 0;
				mapLevel1.player2.fPlayerPosY = 0;
			}	
		}

		if(mapLevel1.player2.fPlayerVelY >= 0){
			if(mapLevel1.player2.fPlayerPosY >= (float)mapLevel1.getNLevelHeight()){	
				mapLevel1.player2.fPlayerVelY = 0;
				mapLevel1.player2.fPlayerPosY = 16;
			}	
		}
	

		if(mapLevel1.player2.fPlayerVelX <= 0){
			if(mapLevel1.player2.fPlayerPosX <= 0){	
				mapLevel1.player2.fPlayerVelX = 0;
				mapLevel1.player2.fPlayerPosX = 0;
			}	
		}

		if(mapLevel1.player2.fPlayerVelX >= 0){
			if(mapLevel1.player2.fPlayerPosX >= (float)mapLevel1.getNLevelWidth()){	

				mapLevel1.player2.fPlayerVelX = 0;
				mapLevel1.player2.fPlayerPosX = 64;
			}	
		}


		// Draw Level
		mapLevel1.player1.nTileWidth = 32;
		mapLevel1.player1.nTileHeight = 32;
		mapLevel1.player1.nVisibleTilesX = ScreenWidth() / mapLevel1.player1.nTileWidth; 
		mapLevel1.player1.nVisibleTilesY = ScreenHeight() / mapLevel1.player1.nTileHeight;

		// Calculate Top-Leftmost visible tile
		mapLevel1.player1.fOffsetX = mapLevel1.player1.fCameraPosX  - (float)mapLevel1.player1.nVisibleTilesX / 2.0f + 7 ; // Explication du + 7 en dessous:
		// + 7 Pour Centrer l'écran sur le milieu du Sprite du Joueur : 
		// 7 car l'écran est en 16/9: 16 en horizontal. 16 - 1 taille du joueur - 1 taille de la ligne verticale du milieu.
		// = 14 / 2 car il y a deux écrans.
		// = 7
		mapLevel1.player1.fOffsetY = mapLevel1.player1.fCameraPosY - (float)mapLevel1.player1.nVisibleTilesY / 2.0f + 2;  // + 2 Pour Centrer l'écran sur le milieu du Sprite du Joueur

		// Clamp camera to game boundaries
		if (mapLevel1.player1.fOffsetX < 0) 
			mapLevel1.player1.fOffsetX = 0;
		if (mapLevel1.player1.fOffsetY < 0){
			mapLevel1.player1.fOffsetY = 0;
		} 

		if (mapLevel1.player1.fOffsetX  > (mapLevel1.nLevelWidth - mapLevel1.player1.nVisibleTilesX/2))
			mapLevel1.player1.fOffsetX = (mapLevel1.nLevelWidth - mapLevel1.player1.nVisibleTilesX/2) ;
		

		if (mapLevel1.player1.fOffsetY > (mapLevel1.nLevelHeight - mapLevel1.player1.nVisibleTilesY)) {
			mapLevel1.player1.fOffsetY = (mapLevel1.nLevelHeight - mapLevel1.player1.nVisibleTilesY);
		}

		// Get offsets for smooth movement
		mapLevel1.player1.fTileOffsetX = (mapLevel1.player1.fOffsetX - (int)mapLevel1.player1.fOffsetX) *mapLevel1.player1.nTileWidth;
		mapLevel1.player1.fTileOffsetY = (mapLevel1.player1.fOffsetY - (int)mapLevel1.player1.fOffsetY) * mapLevel1.player1.nTileHeight;


		mapLevel1.player2.nTileWidth = 32;
		mapLevel1.player2.nTileHeight = 32;
		mapLevel1.player2.nVisibleTilesX = ScreenWidth() / mapLevel1.player2.nTileWidth;
		mapLevel1.player2.nVisibleTilesY = ScreenHeight() / mapLevel1.player2.nTileHeight;


		// Calculate Top-Leftmost visible tile 
		mapLevel1.player2.fOffsetX = mapLevel1.player2.fCameraPosX  - ((float)mapLevel1.player2.nVisibleTilesX / 2.0f - 7); // - 7 Pour Centrer l'écran sur le milieu du Sprite du Joueur
		mapLevel1.player2.fOffsetY = mapLevel1.player2.fCameraPosY  - ((float)mapLevel1.player2.nVisibleTilesY / 2.0f -2); // - 2 Pour Centrer l'écran sur le milieu du Sprite du Joueur

		// Clamp camera to game boundaries
		if (mapLevel1.player2.fOffsetX < 0) mapLevel1.player2.fOffsetX = 0;
		if (mapLevel1.player2.fOffsetY < 0) mapLevel1.player2.fOffsetY = 0;

		if (mapLevel1.player2.fOffsetX > mapLevel1.nLevelWidth - mapLevel1.player2.nVisibleTilesX/2){
			mapLevel1.player2.fOffsetX = mapLevel1.nLevelWidth - mapLevel1.player2.nVisibleTilesX/2;
		}
		if (mapLevel1.player2.fOffsetY > mapLevel1.nLevelHeight - mapLevel1.player2.nVisibleTilesY){
			mapLevel1.player2.fOffsetY = (mapLevel1.nLevelHeight - mapLevel1.player2.nVisibleTilesY);
		} 

		// Get offsets for smooth movement
		mapLevel1.player2.fTileOffsetX = (mapLevel1.player2.fOffsetX - (int)mapLevel1.player2.fOffsetX) *mapLevel1.player2.nTileWidth;
		mapLevel1.player2.fTileOffsetY = (mapLevel1.player2.fOffsetY - (int)mapLevel1.player2.fOffsetY) * mapLevel1.player2.nTileHeight;

		
		// AFFICHAGE MAP ECRAN SCINDE
		//
		// Passer au calque de l'écran scindé
		SetDrawTarget(splitScreenLayerIndex);
		Clear(olc::BLANK);
		
		// MAP ECRAN 1
		
		for (int x = -1; x < mapLevel1.player1.nVisibleTilesX / 2 + 1; x++) {
			for (int y = -2; y < mapLevel1.player1.nVisibleTilesY + 2; y++) {
				wchar_t sTileID = GetTile(x + mapLevel1.player1.fOffsetX, y + mapLevel1.player1.fOffsetY);
				olc::vf2d PosBlocksJ1 = { x * mapLevel1.player1.nTileWidth - mapLevel1.player1.fTileOffsetX,
						y * mapLevel1.player1.nTileHeight - mapLevel1.player1.fTileOffsetY };
				switch (sTileID)
				{
				case L'#':
					DrawDecal(PosBlocksJ1, decTiles);

					break;
				case L'$':
					DrawDecal(PosBlocksJ1, decTiles);
					break;
				case L'.':
					DrawDecal(PosBlocksJ1, decFond);
					break;
				default:
					break;
				}
			}
		}
		
		//cout << "Joueur 1 Pos X = " << mapLevel1.player1.fPlayerPosX << " Joueur 1 Pos Y = " << mapLevel1.player1.fPlayerPosY << endl;
		//cout << "Joueur 2 Pos X = " << mapLevel1.player2.fPlayerPosX << " Joueur 2 Pos Y = " << mapLevel1.player2.fPlayerPosY << endl << endl;

		
		// MAP ECRAN 2

		for (int x = 0; x < mapLevel1.player2.nVisibleTilesX/2 +2; x++) {
			for (int y = -2; y < mapLevel1.player2.nVisibleTilesY + 2; y++) {
				wchar_t sTileID = GetTile(x + mapLevel1.player2.fOffsetX, y + mapLevel1.player2.fOffsetY);
				olc::vf2d PosBlocksJ2 = { x * mapLevel1.player2.nTileWidth - mapLevel1.player2.fTileOffsetX + (ScreenWidth() / 2)+16,
					y * mapLevel1.player2.nTileHeight - mapLevel1.player2.fTileOffsetY };
				switch (sTileID)
				{
				case L'#':
					DrawDecal(PosBlocksJ2, decTiles);
					break;
				case L'$':
					DrawDecal(PosBlocksJ2, decTiles);
					break;
				case L'.':
					DrawDecal(PosBlocksJ2, decFond);
					break;
				default:
					break;
				}
			}
		}
		// Players Screen 1
		//
		// Player 1
		olc::vf2d PosS1J1 = { (mapLevel1.player1.fPlayerPosX - mapLevel1.player1.fOffsetX) * mapLevel1.player1.nTileWidth ,
		(mapLevel1.player1.fPlayerPosY - mapLevel1.player1.fOffsetY) * mapLevel1.player1.nTileHeight };
		DrawDecal(PosS1J1, decPlayer1);

		// Player 2
		// On l'affiche seulement si:
		// La différence entre les deux Offsets est < 6.5
		// et que les deux joueurs ne sont pas aux bordures max en X de la map
		// ou si
		// La différence entre les deux Offsets est < 6.5
		// et qu'ils sont aux bordures max en X de la map
		// et que la différence de leurs positions est < 6.5

		//cout << "OFFSET J1 = " << mapLevel1.player1.fOffsetX <<  "    OFFSET J2 = " << mapLevel1.player2.fOffsetX << endl;
		if ((mapLevel1.player2.fOffsetX - mapLevel1.player1.fOffsetX > -6.5 && mapLevel1.player2.fOffsetX - mapLevel1.player1.fOffsetX < 6.5)	
			&& 
				(mapLevel1.player1.fOffsetX < (mapLevel1.nLevelWidth - 12) && mapLevel1.player2.fOffsetX < (mapLevel1.nLevelWidth - 12) ||
				( (mapLevel1.player2.fPlayerPosX - mapLevel1.player1.fPlayerPosX) < 6.5 )))
		{ 
			olc::vf2d PosS1J2 = { (mapLevel1.player2.fPlayerPosX - mapLevel1.player1.fOffsetX) * mapLevel1.player2.nTileWidth ,
			(mapLevel1.player2.fPlayerPosY - mapLevel1.player1.fOffsetY) * mapLevel1.player2.nTileHeight };
			DrawDecal(PosS1J2, decPlayer2);
		}


		// Players Screen 2
		//
		// Player 1
		// On l'affiche seulement si:
		// La différence entre les deux Offsets est < 6.5
		// et que les deux joueurs ne sont pas aux bordures min en X de la map
		// ou si
		// La différence entre les deux Offsets est < 6.5
		// et qu'ils sont aux bordures min en X de la map
		// et que la différence de leurs positions est < 6.5
		if ((mapLevel1.player2.fOffsetX - mapLevel1.player1.fOffsetX > -6.5 && mapLevel1.player2.fOffsetX - mapLevel1.player1.fOffsetX < 6.5)
			&&
			(mapLevel1.player1.fOffsetX > 0 && mapLevel1.player2.fOffsetX > 0 ||
				((mapLevel1.player2.fPlayerPosX - mapLevel1.player1.fPlayerPosX) < 6.5)))
		{
			olc::vf2d PosS2J1 = { (mapLevel1.player1.fPlayerPosX - mapLevel1.player2.fOffsetX) * mapLevel1.player1.nTileWidth + (ScreenWidth() / 2) + 16,
			(mapLevel1.player1.fPlayerPosY - mapLevel1.player2.fOffsetY) * mapLevel1.player1.nTileHeight };
			DrawDecal(PosS2J1, decPlayer1);
		}
		// Player 2
		olc::vf2d PosS2J2 = { (mapLevel1.player2.fPlayerPosX - mapLevel1.player2.fOffsetX) * mapLevel1.player2.nTileWidth  + (ScreenWidth() / 2) + 16,
		(mapLevel1.player2.fPlayerPosY - mapLevel1.player2.fOffsetY) * mapLevel1.player2.nTileHeight };
		DrawDecal(PosS2J2, decPlayer2);
		Clear(olc::BLANK);

		
		

		// Dessiner une ligne verticale au milieu de l'écran
		
		SetDrawTarget(nullptr);
		FillRectDecal({ 800 / 2 - 16 , 0 }, { 32, 450 }, olc::VERY_DARK_BLUE);

		// Revenir au calque par défaut
		
		Clear(olc::BLANK);
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