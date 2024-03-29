#include <iostream>
#include<cstdlib>
#include <fstream>
#include "./Map.h"
#include "./Player.h"

using namespace std;

//constructeur par defaut
Map::Map(){

	nb_cellules_b_placees = 4;
	nb_cellules_g_placees = 4;

	
	player1 = Player(3.0, 3.0);
	player2 = Player(3.0, 3.0);
	

}

// initialisation des images
void Map::initImages(olc::PixelGameEngine* pge){
	spriteMap = new olc::Sprite("./data/MAP.png");

	spriteTiles = new olc::Sprite("./data/parenchymadefault.png");
	decTiles = new olc:: Decal(spriteTiles);

    spritePlayer1 = new olc::Sprite("./data/alt/Cell-J1.png");
	decPlayer1 = new olc::Decal(spritePlayer1);

    spritePlayer2 = new olc::Sprite("./data/alt/Cell-J2.png");
	decPlayer2 = new olc::Decal(spritePlayer2);

	spriteMultiCell = new olc::Sprite("./data/Multi-Cell.png");
	decMultiCell = new olc::Decal(spriteMultiCell);

	spriteCellRecupPlayer1 = new olc::Sprite("./data/alt/Cell-J1-RECUP.png");
	decCellRecupPlayer1 = new olc::Decal(spriteCellRecupPlayer1);

	spriteCellRecupPlayer2 = new olc::Sprite("./data/alt/Cell-J2-RECUP.png");
	decCellRecupPlayer2 = new olc::Decal(spriteCellRecupPlayer2);

    spriteFond = new olc::Sprite("./data/water.png");
	decFond = new olc::Decal(spriteFond);

	spriteVirus = new olc::Sprite("./data/virus.png");
	decVirus = new olc::Decal(spriteVirus);

	spriteBackGroundLevel2 = new olc::Sprite("./data/underwaterbg.png");

	
	

}

// initialisation de la carte depuis une image png
void Map::initMapFromImage(olc::PixelGameEngine* pge) {
	// Calcule la largeur et la hauteur de la carte en blocs 
	
	nLevelWidth = spriteMap->width;
	nLevelHeight = spriteMap->height;
	
	// Génère la chaîne de caractères représentant la carte à partir de l'image MAP.png
	for (int y = 0; y < nLevelHeight; y++)
	{
		std::string row = "";
		for (int x = 0; x < nLevelWidth; x++)
		{
			olc::Pixel pixel = spriteMap->GetPixel(x, y);
			if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0)
				row += "#";
			else if (pixel.r == 255 && pixel.g == 255 && pixel.b == 255)
				row += ".";
			else if (pixel.r == 255 && pixel.g == 0 && pixel.b == 0)
				row += "v";
			else if (pixel.r == 0 && pixel.g == 0 && pixel.b == 255)
				row += "b";
			else if (pixel.r == 0 && pixel.g == 255 && pixel.b == 0)
				row += "g";
		}
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring wideRow = converter.from_bytes(row);
		sLevel += wideRow ;
	}
}


// mouvements joueurs et collisions
void Map::move(float fElapsedTime, Player& P){

	auto GetTile = [&](int x, int y)
	{
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
			return sLevel[y * nLevelWidth + x];
		else
			return L' ';
	};
	auto SetTile = [&](int x, int y, wchar_t c)
	{
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
			sLevel[y * nLevelWidth + x] = c;
	};


	P.fNewPlayerPosX = P.fPlayerPosX + P.fPlayerVelX * fElapsedTime;
	P.fNewPlayerPosY = P.fPlayerPosY + P.fPlayerVelY * fElapsedTime;

}

void Map::collisions(float fElapsedTime, Player& P){

	auto GetTile = [&](int x, int y)
	{
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
			return sLevel[y * nLevelWidth + x];
		else
			return L' ';
	};
	auto SetTile = [&](int x, int y, wchar_t c)
	{
		if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
			sLevel[y * nLevelWidth + x] = c;
	};

		// Check for Collision
		if (P.fPlayerVelX <= 0) // Moving Left
		{
			if (GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.2f) == L'#' || GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.7f) == L'#')
			{
				P.fNewPlayerPosX = (int)P.fNewPlayerPosX + 1;
				P.fPlayerVelX = 0;
			}

			if(GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.2f) == L'v' || GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.7f) == L'v'){

				bool place = false;
				SetTile(P.fPlayerPosX - 0.2f , P.fPlayerPosY, L'.');

				while(place == false){

					int x = rand() % nLevelWidth;
					int y = rand() % nLevelHeight;

					if ((GetTile(x, y)!='#') && (GetTile(x, y)!='b') && (GetTile(x, y)!='g') && (GetTile(x, y)!='v')){
						P.fNewPlayerPosX = x;
						P.fNewPlayerPosY = y;
						place = true;
					}
				}		
			}
		}

		else // Moving Right
		{
			if (GetTile(P.fNewPlayerPosX + 1.0f, P.fPlayerPosY + 0.2f) == L'#' || GetTile(P.fNewPlayerPosX + 1.0f, P.fPlayerPosY + 0.7f) == L'#')
			{
				P.fNewPlayerPosX = (int)P.fNewPlayerPosX;
				P.fPlayerVelX = 0;
				
			}

			if(GetTile(P.fNewPlayerPosX + 1.0f, P.fPlayerPosY + 0.2f) == L'v' || GetTile(P.fNewPlayerPosX + 1.0f, P.fPlayerPosY + 0.7f) == L'v'){

				bool place = false;
				SetTile(P.fPlayerPosX +1.2f , P.fPlayerPosY, L'.');

				while(place == false){

					int x = rand() % nLevelWidth;
					int y = rand() % nLevelHeight;

					if ((GetTile(x, y)!='#') && (GetTile(x, y)!='b') && (GetTile(x, y)!='g') && (GetTile(x, y)!='v')){
						P.fNewPlayerPosX = x;
						P.fNewPlayerPosY = y;
						place = true;
					}
				}		
			}
		}
		
		if (P.fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(P.fNewPlayerPosX + 0.2f, P.fNewPlayerPosY) == L'#' || GetTile(P.fNewPlayerPosX + 0.7f, P.fNewPlayerPosY) == L'#')
			{
				P.fNewPlayerPosY = (int)P.fNewPlayerPosY + 1;
				P.fPlayerVelY = 0;
			}

			if(GetTile(P.fNewPlayerPosX + 0.2f, P.fPlayerPosY) == L'v' || GetTile(P.fNewPlayerPosX + 0.7f, P.fPlayerPosY) == L'v'){

				bool place = false;
				SetTile(P.fNewPlayerPosX, P.fPlayerPosY - 0.2f, L'.');

				while(place == false){

					int x = rand() % nLevelWidth;
					int y = rand() % nLevelHeight;

					if ((GetTile(x, y)!='#') && (GetTile(x, y)!='b') && (GetTile(x, y)!='g') && (GetTile(x, y)!='v')){
						P.fNewPlayerPosX = x;
						P.fNewPlayerPosY = y;
						place = true;
					}
				}		
			}
		}
		else // Moving Down
		{
			if (GetTile(P.fNewPlayerPosX + 0.2f, P.fNewPlayerPosY + 1.0f) == L'#' || GetTile(P.fNewPlayerPosX + 0.7f, P.fNewPlayerPosY + 1.0f) == L'#')
			{
				P.fNewPlayerPosY = (int)P.fNewPlayerPosY;
				P.fPlayerVelY = 0;
				
			}

			if(GetTile(P.fNewPlayerPosX + 0.2f, P.fPlayerPosY + 1.0f) == L'v' || GetTile(P.fNewPlayerPosX + 0.7f, P.fPlayerPosY + 1.0f) == L'v'){

				bool place = false;
				SetTile(P.fNewPlayerPosX, P.fPlayerPosY + 1.2f, L'.');

				while(place == false){

					int x = rand() % nLevelWidth;
					int y = rand() % nLevelHeight;

					if ((GetTile(x, y)!='#') && (GetTile(x, y)!='b') && (GetTile(x, y)!='g') && (GetTile(x, y)!='v')){
						P.fNewPlayerPosX = x;
						P.fNewPlayerPosY = y;
						place = true;
						
					}
				}		
			}
		}

	// Apply new position
	P.fPlayerPosX = P.fNewPlayerPosX;
	P.fPlayerPosY = P.fNewPlayerPosY;

	// Link camera to player position
	P.fCameraPosX = P.fPlayerPosX;
	P.fCameraPosY = P.fPlayerPosY;
}

// dessiner le niveau 1
void Map::drawLevel(olc::PixelGameEngine* pge){

	srand((unsigned) time(NULL));
	// Draw Level

		auto GetTile = [&](int x, int y)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				return sLevel[y * nLevelWidth + x];
			else
				return L' ';
		};

		auto SetTile = [&](int x, int y, wchar_t c)
		{
			if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
				sLevel[y * nLevelWidth + x] = c;
		};

		// Void RecupCellJ1
		if (pge->IsFocused()) {

			// Si Touche E (Touche "utiliser") pressée (1x où ↓)  + Si il y a une cellule à récupérer Milieu de PlayerPos (+0.5 pour avoir son centre) 
			if (pge->GetKey(olc::Key::E).bPressed && GetTile(player1.fPlayerPosX+0.5f, player1.fPlayerPosY+0.5f) == L'b') {

				player1.NbCelluleRecup++;
				SetTile(player1.fPlayerPosX + 0.5f, player1.fPlayerPosY + 0.5f, L'.');
			}
		}

		// Void RecupCellJ1
		if (pge->IsFocused()) {

			// Si Touche E (Touche "utiliser") pressée (1x où ↓)  + Si il y a une cellule à récupérer Milieu de PlayerPos (+0.5 pour avoir son centre) 
			if (pge->GetKey(olc::Key::SHIFT).bPressed && GetTile(player2.fPlayerPosX + 0.5f, player2.fPlayerPosY + 0.5f) == L'g') {

				player2.NbCelluleRecup++;
				SetTile(player2.fPlayerPosX + 0.5f, player2.fPlayerPosY + 0.5f, L'.');
			}
		}
		 
		player1.nVisibleTilesX = pge->ScreenWidth() / player1.nTileWidth; 
		player1.nVisibleTilesY = pge->ScreenHeight() / player1.nTileHeight;

		// Calculate Top-Leftmost visible tile
		player1.fOffsetX = player1.fCameraPosX  - (float)player1.nVisibleTilesX / 2.0f + 7 ; // Explication du + 7 en dessous:
		// + 7 Pour Centrer l'écran sur le milieu du Sprite du Joueur : 
		// 7 car l'écran est en 16/9: 16 en horizontal. 16 - 1 taille du joueur - 1 taille de la ligne verticale du milieu.
		// = 14 / 2 car il y a deux écrans.
		// = 7
		player1.fOffsetY = player1.fCameraPosY - (float)player1.nVisibleTilesY / 2.0f + 2;  // + 2 Pour Centrer l'écran sur le milieu du Sprite du Joueur

		// Clamp camera to game boundaries
		if (player1.fOffsetX < 0) 
			player1.fOffsetX = 0;
		if (player1.fOffsetY < 0){
			player1.fOffsetY = 0;
		} 

		if (player1.fOffsetX  > (nLevelWidth - player1.nVisibleTilesX/2))
			player1.fOffsetX = (nLevelWidth - player1.nVisibleTilesX/2) ;
		

		if (player1.fOffsetY > (nLevelHeight - player1.nVisibleTilesY)) {
			player1.fOffsetY = (nLevelHeight - player1.nVisibleTilesY);
		}

		// Get offsets for smooth movement
		player1.fTileOffsetX = (player1.fOffsetX - (int)player1.fOffsetX) *player1.nTileWidth;
		player1.fTileOffsetY = (player1.fOffsetY - (int)player1.fOffsetY) * player1.nTileHeight;


		player2.nVisibleTilesX = pge->ScreenWidth() / player2.nTileWidth;
		player2.nVisibleTilesY = pge->ScreenHeight() / player2.nTileHeight;


		// Calculate Top-Leftmost visible tile 
		player2.fOffsetX = player2.fCameraPosX  - ((float)player2.nVisibleTilesX / 2.0f - 7); // - 7 Pour Centrer l'écran sur le milieu du Sprite du Joueur
		player2.fOffsetY = player2.fCameraPosY  - ((float)player2.nVisibleTilesY / 2.0f -2); // - 2 Pour Centrer l'écran sur le milieu du Sprite du Joueur

		// Clamp camera to game boundaries
		if (player2.fOffsetX < 0) player2.fOffsetX = 0;
		if (player2.fOffsetY < 0) player2.fOffsetY = 0;

		if (player2.fOffsetX > nLevelWidth - player2.nVisibleTilesX/2){
			player2.fOffsetX = nLevelWidth - player2.nVisibleTilesX/2;
		}
		if (player2.fOffsetY > nLevelHeight - player2.nVisibleTilesY){
			player2.fOffsetY = (nLevelHeight - player2.nVisibleTilesY);
		} 

		// Get offsets for smooth movement
		player2.fTileOffsetX = (player2.fOffsetX - (int)player2.fOffsetX) *player2.nTileWidth;
		player2.fTileOffsetY = (player2.fOffsetY - (int)player2.fOffsetY) * player2.nTileHeight;

		
		// AFFICHAGE MAP ECRAN SCINDE
		//
		// Passer au calque de l'écran scindé
		pge->SetDrawTarget(splitScreenLayerIndex);
		pge->Clear(olc::BLANK);
		
		// MAP ECRAN 1
		
		for (int x = -1; x < player1.nVisibleTilesX / 2 + 1; x++) {
			for (int y = -2; y < player1.nVisibleTilesY + 2; y++) {
				wchar_t sTileID = GetTile(x + player1.fOffsetX, y + player1.fOffsetY);
				olc::vf2d PosBlocksJ1 = { x * player1.nTileWidth - player1.fTileOffsetX,
						y * player1.nTileHeight - player1.fTileOffsetY };
				switch (sTileID)
				{
				case L'#':
					pge->DrawDecal(PosBlocksJ1, decTiles);
					break;
				case L'$':
					pge->DrawDecal(PosBlocksJ1, decTiles);
					break;
				case L'.':
					pge->DrawDecal(PosBlocksJ1, decFond);
					break;
				case L'g':
					pge->DrawDecal(PosBlocksJ1, decFond);
					pge->DrawDecal(PosBlocksJ1, decCellRecupPlayer2);
					break;
				case L'b':
					pge->DrawDecal(PosBlocksJ1, decFond);
					break;
				case L'v':
					pge->DrawDecal(PosBlocksJ1, decFond);
					pge->DrawDecal(PosBlocksJ1, decVirus);
					break;
				default:
					break;
				}
			}
		}
		
		// MAP ECRAN 2

		for (int x = 0; x < player2.nVisibleTilesX/2 +2; x++) {
			for (int y = -2; y < player2.nVisibleTilesY + 2; y++) {
				wchar_t sTileID = GetTile(x + player2.fOffsetX, y + player2.fOffsetY);
				olc::vf2d PosBlocksJ2 = { x * player2.nTileWidth - player2.fTileOffsetX + (pge->ScreenWidth() / 2)+16,
					y * player2.nTileHeight - player2.fTileOffsetY };
				switch (sTileID)
				{
				case L'#':
					pge->DrawDecal(PosBlocksJ2, decTiles);
					break;
				case L'$':
					pge->DrawDecal(PosBlocksJ2, decTiles);
					break;
				case L'.':
					pge->DrawDecal(PosBlocksJ2, decFond);
					break;
				case L'g':
					pge->DrawDecal(PosBlocksJ2, decFond);
					break;
				case L'b':
					pge->DrawDecal(PosBlocksJ2, decFond);
					pge->DrawDecal(PosBlocksJ2, decCellRecupPlayer1);
					break;
					break;
				case L'v':
					pge->DrawDecal(PosBlocksJ2, decFond);
					pge->DrawDecal(PosBlocksJ2, decVirus);
					break;
				default:
					break;
				}
			}
		}

		// Calque supérieur NBCellulesRécupérées.
		olc::vf2d SpritePosMultiCell = { static_cast<float>(player2.NbCelluleRecup) * 32, static_cast<float>(player1.NbCelluleRecup) * 32 };
		

		// Players Screen 1
		//
		// Player 2
		// On l'affiche seulement si:
		// La différence entre les deux Offsets est < 6.5
		// et que les deux joueurs ne sont pas aux bordures max en X de la map
		// ou si
		// La différence entre les deux Offsets est < 6.5
		// et qu'ils sont aux bordures max en X de la map
		// et que la différence de leurs positions est < 6.5
		
		if ((player2.fOffsetX - player1.fOffsetX > -6.5 && player2.fOffsetX - player1.fOffsetX < 6.5)	
			&& 
				(player1.fOffsetX < (nLevelWidth - 12) && player2.fOffsetX < (nLevelWidth - 12) ||
				((player2.fPlayerPosX - player1.fPlayerPosX) < 6.5 )))
		{ 
			olc::vf2d PosS1J2 = { (player2.fPlayerPosX - player1.fOffsetX) * player2.nTileWidth ,
			(player2.fPlayerPosY - player1.fOffsetY) * player2.nTileHeight };
			
			pge->DrawDecal(PosS1J2, decPlayer2);
			pge->DrawPartialDecal(PosS1J2, { 32,32 } , decMultiCell, SpritePosMultiCell, { 32,32 });
			
		}

		// Player 1
		olc::vf2d PosS1J1 = { (player1.fPlayerPosX - player1.fOffsetX) * player1.nTileWidth ,
		(player1.fPlayerPosY - player1.fOffsetY) * player1.nTileHeight };
		pge->DrawDecal(PosS1J1, decPlayer1);
		pge->DrawPartialDecal(PosS1J1, { 32,32 }, decMultiCell, SpritePosMultiCell, { 32,32 });

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
		if ((player2.fOffsetX - player1.fOffsetX > -6.5 && player2.fOffsetX - player1.fOffsetX < 6.5)
			&&
			(player1.fOffsetX > 0 && player2.fOffsetX > 0 ||
				((player2.fPlayerPosX - player1.fPlayerPosX) < 6.5)))
		{
			olc::vf2d PosS2J1 = { (player1.fPlayerPosX - player2.fOffsetX) * player1.nTileWidth + (pge->ScreenWidth() / 2) + 16,
			(player1.fPlayerPosY - player2.fOffsetY) * player1.nTileHeight };
			pge->DrawDecal(PosS2J1, decPlayer1);
			pge->DrawPartialDecal(PosS2J1, { 32,32 }, decMultiCell, SpritePosMultiCell, { 32,32 });
		}
		// Player 2
		olc::vf2d PosS2J2 = { (player2.fPlayerPosX - player2.fOffsetX) * player2.nTileWidth  + (pge->ScreenWidth() / 2) + 16,
		(player2.fPlayerPosY - player2.fOffsetY) * player2.nTileHeight };
		pge->DrawDecal(PosS2J2, decPlayer2);
		pge->DrawPartialDecal(PosS2J2, { 32,32 }, decMultiCell, SpritePosMultiCell, { 32,32 });
		pge->Clear(olc::BLANK);
		
		
		

		// Dessiner une ligne verticale au milieu de l'écran
		
		pge->SetDrawTarget(nullptr);
		pge->FillRectDecal({ 800 / 2 - 16 , 0 }, { 32, 450 }, olc::VERY_DARK_BLUE);

		// Revenir au calque par défaut
		
		pge->Clear(olc::BLANK);
}

int Map::checkLevel(Player& P1, Player& P2){
	int niveau;

	if((P1.NbCelluleRecup<4) || (P2.NbCelluleRecup<4)){
		niveau = 1;
	}

	else if ((P1.NbCelluleRecup==4) || (P2.NbCelluleRecup==4)){
		niveau = 2;
	}

	return niveau;
}

void Map::drawLevel2(olc::PixelGameEngine* pge){
	olc::vd2d posInitImage = {0,0};
	pge->DrawSprite(posInitImage, spriteBackGroundLevel2);
}