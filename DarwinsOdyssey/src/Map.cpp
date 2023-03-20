#include <iostream>
#include<cstdlib>
#include <fstream>
#include "./Map.h"
#include "./Player.h"

using namespace std;

//constructeur par defaut
Map::Map(){

    nLevelWidth = 64;
	nLevelHeight = 16;
	nb_cellules_b_placees = 4;
	nb_cellules_g_placees = 4;
	sLevel += L"#.$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$#";
	sLevel += L"#..............................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#.......r......................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#........b.....................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#...............#####..........................................#";
	sLevel += L"#...............#...#..........................................#";
	sLevel += L"#...............#...#..........................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"#..............................................................#";
	sLevel += L"################################################################";

	player1 = Player(1.0, 1.0);
	player2 = Player(2.0, 2.0);


}

//constructeur avec parametres
Map::Map(wstring sLevel_param, int nLevelWidth_param, int nLevelHeight_param){
    sLevel = sLevel_param;
    nLevelWidth = nLevelWidth_param;
    nLevelHeight = nLevelHeight_param;
}

void Map::initImages(olc::PixelGameEngine* pge){
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
}

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

		// Placer les cellules 'b'

		while (nb_cellules_b_placees>0)
		{
			int x = rand() % nLevelWidth;
			int y = rand() % nLevelHeight;
			if( (GetTile(x, y)!='#') && (GetTile(x, y)!='b') && (GetTile(x, y)!='v') && (GetTile(x, y)!='$')){
				SetTile(x, y, 'b');
				nb_cellules_b_placees--;
			}
		}
		
		// Placer les cellules 'g'
		while (nb_cellules_g_placees>0)
		{
			int x = rand() % nLevelWidth;
			int y = rand() % nLevelHeight;
			if( (GetTile(x, y)!='#') && (GetTile(x, y)!='g') && (GetTile(x, y)!='v') && (GetTile(x, y)!='$')){
				SetTile(x, y, 'g');
				nb_cellules_g_placees--;
			}
		}

		// Void RecupCellJ1
		if (pge->IsFocused()) {

			// Si Touche E (Touche "utiliser") pressée (1x où ↓)  + Si il y a une cellule à récupérer Milieu de PlayerPos (+0.5 pour avoir son centre) 
			if (pge->GetKey(olc::Key::E).bPressed && GetTile(player1.fPlayerPosX+0.5f, player1.fPlayerPosY+0.5f) == L'b') {

				player1.NbCelluleRecup++;
				cout << "YES" << endl;
				SetTile(player1.fPlayerPosX + 0.5f, player1.fPlayerPosY + 0.5f, L'.');
			}
		}

		// Void RecupCellJ1
		if (pge->IsFocused()) {

			// Si Touche E (Touche "utiliser") pressée (1x où ↓)  + Si il y a une cellule à récupérer Milieu de PlayerPos (+0.5 pour avoir son centre) 
			if (pge->GetKey(olc::Key::SHIFT).bPressed && GetTile(player2.fPlayerPosX + 0.5f, player2.fPlayerPosY + 0.5f) == L'g') {

				player2.NbCelluleRecup++;
				cout << "YES" << endl;
				SetTile(player2.fPlayerPosX + 0.5f, player2.fPlayerPosY + 0.5f, L'.');
				cout << player2.NbCelluleRecup << endl;
				cout << static_cast<float>(player2.NbCelluleRecup) << endl;
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
		
		//cout << "OFFSET J1 = " << player1.fOffsetX <<  "    OFFSET J2 = " << player2.fOffsetX << endl;
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
