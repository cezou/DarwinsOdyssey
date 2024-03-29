#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <cmath>
#include "./Map.h"
#include "./Player.h"
#include "./Ennemi_Fish.h"

using namespace std;

//constructeur par defaut
Map::Map() {

	nb_cellules_b_placees = 4;
	nb_cellules_g_placees = 4;

	rester_niveau1 = false;
	rester_niveau2 = false;

	stop_a_droite = false;
	stop_a_gauche = false;
	vies = 5;


	player1 = Player(3.0, 3.0);
	player2 = Player(3.0, 3.0);


}

// initialisation des images
void Map::initImages(olc::PixelGameEngine* pge) {
	spriteMap = new olc::Sprite("./data/MAP.png");

	spriteMenu = new olc::Sprite("./data/menu.png");
	decMenu = new olc::Decal(spriteMenu);

	spriteTiles = new olc::Sprite("./data/parenchymadefault.png");
	decTiles = new olc::Decal(spriteTiles);

	spritePlayer1 = new olc::Sprite("./data/alt/Cell-J1.png");
	decPlayer1 = new olc::Decal(spritePlayer1);

	spritePlayer2 = new olc::Sprite("./data/alt/Cell-J2.png");
	decPlayer2 = new olc::Decal(spritePlayer2);

	spritePlayerLevel0 = new olc::Sprite("./data/alt/fish.png");
	decPlayerLevel0 = new olc::Decal(spritePlayerLevel0);

	spritePlayerLevel2 = new olc::Sprite("./data/alt/shark.png");
	decPlayerLevel2 = new olc::Decal(spritePlayerLevel2);

	spritePlayerLevel3 = new olc::Sprite("./data/alt/whale.png");
	decPlayerLevel3 = new olc::Decal(spritePlayerLevel3);

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

void Map::drawLevel0(olc::PixelGameEngine* pge) {
	olc::vd2d posInitImage = { 0,0 };

	// Draw le fond
	pge->DrawDecal(posInitImage, decMenu);



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
		sLevel += wideRow;
	}
}

auto Map::GetTile(int x, int y)
{
	if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
		return sLevel[y * nLevelWidth + x];
	else
		return L' ';
};

auto Map::SetTile(int x, int y, wchar_t c)
{
	if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
		sLevel[y * nLevelWidth + x] = c;
};


// mouvements joueurs et collisions
void Map::move(float fElapsedTime, Player& P) {

	P.fNewPlayerPosX = P.fPlayerPosX + P.fPlayerVelX * fElapsedTime;
	P.fNewPlayerPosY = P.fPlayerPosY + P.fPlayerVelY * fElapsedTime;

	P.fPlayerPosX = P.fNewPlayerPosX;
	P.fPlayerPosY = P.fNewPlayerPosY;

}

void Map::collisions(float fElapsedTime, Player& P) {



	// Check for Collision
	if (P.fPlayerVelX <= 0) // Moving Left
	{
		if (GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.2f) == L'#' || GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.7f) == L'#')
		{
			P.fNewPlayerPosX = (int)P.fNewPlayerPosX + 1;
			P.fPlayerVelX = 0;
		}

		if (GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.2f) == L'v' || GetTile(P.fNewPlayerPosX + 0.0f, P.fPlayerPosY + 0.7f) == L'v') {

			bool place = false;
			SetTile(P.fPlayerPosX - 0.2f, P.fPlayerPosY, L'.');

			while (place == false) {

				int x = rand() % nLevelWidth;
				int y = rand() % nLevelHeight;

				if ((GetTile(x, y) != '#') && (GetTile(x, y) != 'b') && (GetTile(x, y) != 'g') && (GetTile(x, y) != 'v')) {
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

		if (GetTile(P.fNewPlayerPosX + 1.0f, P.fPlayerPosY + 0.2f) == L'v' || GetTile(P.fNewPlayerPosX + 1.0f, P.fPlayerPosY + 0.7f) == L'v') {

			bool place = false;
			SetTile(P.fPlayerPosX + 1.2f, P.fPlayerPosY, L'.');

			while (place == false) {

				int x = rand() % nLevelWidth;
				int y = rand() % nLevelHeight;

				if ((GetTile(x, y) != '#') && (GetTile(x, y) != 'b') && (GetTile(x, y) != 'g') && (GetTile(x, y) != 'v')) {
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

		if (GetTile(P.fNewPlayerPosX + 0.2f, P.fPlayerPosY) == L'v' || GetTile(P.fNewPlayerPosX + 0.7f, P.fPlayerPosY) == L'v') {

			bool place = false;
			SetTile(P.fNewPlayerPosX, P.fPlayerPosY - 0.2f, L'.');

			while (place == false) {

				int x = rand() % nLevelWidth;
				int y = rand() % nLevelHeight;

				if ((GetTile(x, y) != '#') && (GetTile(x, y) != 'b') && (GetTile(x, y) != 'g') && (GetTile(x, y) != 'v')) {
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

		if (GetTile(P.fNewPlayerPosX + 0.2f, P.fPlayerPosY + 1.0f) == L'v' || GetTile(P.fNewPlayerPosX + 0.7f, P.fPlayerPosY + 1.0f) == L'v') {

			bool place = false;
			SetTile(P.fNewPlayerPosX, P.fPlayerPosY + 1.2f, L'.');

			while (place == false) {

				int x = rand() % nLevelWidth;
				int y = rand() % nLevelHeight;

				if ((GetTile(x, y) != '#') && (GetTile(x, y) != 'b') && (GetTile(x, y) != 'g') && (GetTile(x, y) != 'v')) {
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
void Map::drawLevel1(olc::PixelGameEngine* pge) {

	srand((unsigned)time(NULL));
	// Draw Level


		// Void RecupCellJ1
	if (pge->IsFocused()) {

		// Si Touche E (Touche "utiliser") pressée (1x où ↓)  + Si il y a une cellule à récupérer Milieu de PlayerPos (+0.5 pour avoir son centre) 
		if (pge->GetKey(olc::Key::E).bPressed && GetTile(player1.fPlayerPosX + 0.5f, player1.fPlayerPosY + 0.5f) == L'b') {

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
	player1.fOffsetX = player1.fCameraPosX - (float)player1.nVisibleTilesX / 2.0f + 7; // Explication du + 7 en dessous:
	// + 7 Pour Centrer l'écran sur le milieu du Sprite du Joueur : 
	// 7 car l'écran est en 16/9: 16 en horizontal. 16 - 1 taille du joueur - 1 taille de la ligne verticale du milieu.
	// = 14 / 2 car il y a deux écrans.
	// = 7
	player1.fOffsetY = player1.fCameraPosY - (float)player1.nVisibleTilesY / 2.0f + 2;  // + 2 Pour Centrer l'écran sur le milieu du Sprite du Joueur

	// Clamp camera to game boundaries
	if (player1.fOffsetX < 0)
		player1.fOffsetX = 0;
	if (player1.fOffsetY < 0) {
		player1.fOffsetY = 0;
	}

	if (player1.fOffsetX > (nLevelWidth - player1.nVisibleTilesX / 2))
		player1.fOffsetX = (nLevelWidth - player1.nVisibleTilesX / 2);


	if (player1.fOffsetY > (nLevelHeight - player1.nVisibleTilesY)) {
		player1.fOffsetY = (nLevelHeight - player1.nVisibleTilesY);
	}

	// Get offsets for smooth movement
	player1.fTileOffsetX = (player1.fOffsetX - (int)player1.fOffsetX) * player1.nTileWidth;
	player1.fTileOffsetY = (player1.fOffsetY - (int)player1.fOffsetY) * player1.nTileHeight;


	player2.nVisibleTilesX = pge->ScreenWidth() / player2.nTileWidth;
	player2.nVisibleTilesY = pge->ScreenHeight() / player2.nTileHeight;


	// Calculate Top-Leftmost visible tile 
	player2.fOffsetX = player2.fCameraPosX - ((float)player2.nVisibleTilesX / 2.0f - 7); // - 7 Pour Centrer l'écran sur le milieu du Sprite du Joueur
	player2.fOffsetY = player2.fCameraPosY - ((float)player2.nVisibleTilesY / 2.0f - 2); // - 2 Pour Centrer l'écran sur le milieu du Sprite du Joueur

	// Clamp camera to game boundaries
	if (player2.fOffsetX < 0) player2.fOffsetX = 0;
	if (player2.fOffsetY < 0) player2.fOffsetY = 0;

	if (player2.fOffsetX > nLevelWidth - player2.nVisibleTilesX / 2) {
		player2.fOffsetX = nLevelWidth - player2.nVisibleTilesX / 2;
	}
	if (player2.fOffsetY > nLevelHeight - player2.nVisibleTilesY) {
		player2.fOffsetY = (nLevelHeight - player2.nVisibleTilesY);
	}

	// Get offsets for smooth movement
	player2.fTileOffsetX = (player2.fOffsetX - (int)player2.fOffsetX) * player2.nTileWidth;
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

	for (int x = 0; x < player2.nVisibleTilesX / 2 + 2; x++) {
		for (int y = -2; y < player2.nVisibleTilesY + 2; y++) {
			wchar_t sTileID = GetTile(x + player2.fOffsetX, y + player2.fOffsetY);
			olc::vf2d PosBlocksJ2 = { x * player2.nTileWidth - player2.fTileOffsetX + (pge->ScreenWidth() / 2) + 16,
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
			((player2.fPlayerPosX - player1.fPlayerPosX) < 6.5)))
	{
		olc::vf2d PosS1J2 = { (player2.fPlayerPosX - player1.fOffsetX) * player2.nTileWidth ,
		(player2.fPlayerPosY - player1.fOffsetY) * player2.nTileHeight };

		pge->DrawDecal(PosS1J2, decPlayer2);
		pge->DrawPartialDecal(PosS1J2, { 32,32 }, decMultiCell, SpritePosMultiCell, { 32,32 });

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
	olc::vf2d PosS2J2 = { (player2.fPlayerPosX - player2.fOffsetX) * player2.nTileWidth + (pge->ScreenWidth() / 2) + 16,
	(player2.fPlayerPosY - player2.fOffsetY) * player2.nTileHeight };
	pge->DrawDecal(PosS2J2, decPlayer2);
	pge->DrawPartialDecal(PosS2J2, { 32,32 }, decMultiCell, SpritePosMultiCell, { 32,32 });
	pge->Clear(olc::BLANK);




	// Dessiner une ligne verticale au milieu de l'écran

	pge->SetDrawTarget(nullptr);
	pge->FillRectDecal({ 800 / 2 - 16 , 0 }, { 32, 450 }, olc::VERY_DARK_BLUE);



	// Revenir au calque par défaut

	pge->Clear(olc::BLANK);

	// Dessiner le nombre de cellules recuperées

	pge->DrawString({ 3,3 }, "CELLULES PLAYER 1:", olc::YELLOW);
	string cellules_player1_string = to_string(player1.NbCelluleRecup);
	pge->DrawString({ 155, 3 }, cellules_player1_string, olc::YELLOW);

	pge->DrawString({ 630,3 }, "CELLULES PLAYER 2:", olc::YELLOW);
	string cellules_player2_string = to_string(player2.NbCelluleRecup);
	pge->DrawString({ 780, 3 }, cellules_player2_string, olc::YELLOW);
}

int Map::checkLevel(olc::PixelGameEngine* pge, Player& P1, Player& P2) {

	int niveau;

	if ((!rester_niveau1) && (!rester_niveau2)) {
		niveau = 0;
	}

	if ((pge->GetKey(olc::Key::SPACE).bPressed) || (rester_niveau1)) {
		niveau = 1;
		rester_niveau1 = true;
	}


	if ((P1.NbCelluleRecup == 1) || (P2.NbCelluleRecup == 1)) {
		rester_niveau1 = false;
		rester_niveau2 = true;
	}

	if (rester_niveau2) {
		niveau = 2;
		if ((P1.numeroPoints > 40) && (P2.numeroPoints > 40)) {
			rester_niveau2 = false;
			niveau = 3;
		}
	}

	return niveau;
}

void Map::initEnnemis() {

	for (int i = 0; i < numeroFish / 2; i++) {

		tabFish[i].fEnnemiPosY = rand() % 371 + 30;
		tabFish[i].fEnnemiPosX = 800;
		tabFish[i].ennemiLevel = rand() % 4;
	}

	for (int i = numeroFish / 2; i < numeroFish; i++) {
		tabFish[i].fEnnemiPosY = rand() % 371 + 30;
		tabFish[i].fEnnemiPosX = 0.0f;
		tabFish[i].ennemiLevel = rand() % 4;
	}

	for (int i = 0; i < numeroFish; i++) {
		if (i != 0) {
			for (int j = 0; j < i; j++) {
				while (abs(tabFish[i].fEnnemiPosY - tabFish[j].fEnnemiPosY) < 20.0f) {
					tabFish[i].fEnnemiPosY = rand() % 371 + 30;
				}
			}
		}
	}

}

void Map::setVelEnnemi() {
	for (int i = 0; i < numeroFish / 2; i++) {
		tabFish[i].fEnnemiVelX = -200 + (rand() % 191 - 10);
		tabFish[i].fEnnemiVelY = 0;
	}

	for (int i = numeroFish / 2; i < numeroFish; i++) {
		tabFish[i].fEnnemiVelX = 10 + (rand() % 191);
		tabFish[i].fEnnemiVelY = 0;
	}
}

void Map::replaceEnnemi() {
	for (int i = 0; i < numeroFish / 2; i++) {
		if ((tabFish[i].fEnnemiPosX + 30 < 0.0f) || (tabFish[i].touche == true)) {
			tabFish[i].fEnnemiPosX = 800.0f;
			tabFish[i].fEnnemiPosY = rand() % 371 + 30;
			tabFish[i].fEnnemiVelX = -200 + (rand() % 191 - 10);
			tabFish[i].ennemiLevel = rand() % 4;
			tabFish[i].touche = false;
		}
	}

	for (int i = numeroFish / 2; i < numeroFish; i++) {
		if ((tabFish[i].fEnnemiPosX > 800) || (tabFish[i].touche == true)) {
			tabFish[i].fEnnemiPosX = 0.0f;
			tabFish[i].fEnnemiPosY = rand() % 371 + 30;
			tabFish[i].fEnnemiVelX = 10 + (rand() % 191);
			tabFish[i].ennemiLevel = rand() % 4;
			tabFish[i].touche = false;
		}
	}
}

void Map::collisionsMap(Player& P) {

	// a gauche
	if (P.fPlayerPosX < 0.0f) {
		P.fPlayerPosX = 0.0f;
	}

	// en haut
	if (P.fPlayerPosY < 0.0f) {
		P.fPlayerPosY = 0.0f;
	}

	// a droite
	if (P.fPlayerPosX + 30 > 800.0f) {
		P.fPlayerPosX = 800.0f - 30;
	}

	// en bas
	if (P.fPlayerPosY + 30 > 450.0f) {
		P.fPlayerPosY = 450.0f - 30;
	}
}

void Map::collisionsEnnemiFish(Player& P) {

	// collisions

	for (int i = 0; i < numeroFish; i++) {

		if (P.level > tabFish[i].ennemiLevel) {

			if ((P.fPlayerVelX <= 0) || (P.fPlayerVelX > 0) || (P.fPlayerVelY <= 0) || (P.fPlayerVelY > 0)) {

				if (tabFish[i].ennemiLevel == 0) {

					// OK
					if ((P.level == 1) && (P.bDirection) && ((P.distance(P.fPlayerPosX - 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX, tabFish[i].fEnnemiPosY) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 1;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (!P.bDirection) && ((P.distance(P.fPlayerPosX + 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX, tabFish[i].fEnnemiPosY) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 1;
						tabFish[i].touche = true;
					}

					// OK

					if ((P.level == 2) && (P.bDirection) && ((P.distance(P.fPlayerPosX - 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX, tabFish[i].fEnnemiPosY) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 1;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (!P.bDirection) && ((P.distance(P.fPlayerPosX + 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX, tabFish[i].fEnnemiPosY) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 1;
						tabFish[i].touche = true;
					}

					// OK
					if ((P.level == 3) && (P.bDirection) && ((P.distance(P.fPlayerPosX - 20, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX, tabFish[i].fEnnemiPosY) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 1;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (!P.bDirection) && ((P.distance(P.fPlayerPosX + 20, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX, tabFish[i].fEnnemiPosY) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 1;
						tabFish[i].touche = true;
					}
				}

				if (tabFish[i].ennemiLevel == 1) {

					// collision ennemi level 1 player level 2
					// OK
					if ((P.level == 2) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX - 10, tabFish[i].fEnnemiPosY + 18) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX - 10, tabFish[i].fEnnemiPosY + 18) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX + 10, tabFish[i].fEnnemiPosY + 18) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX + 10, tabFish[i].fEnnemiPosY + 18) <= 17) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

					// OK

					if ((P.level == 3) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX - 10, tabFish[i].fEnnemiPosY + 18) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX - 10, tabFish[i].fEnnemiPosY + 18) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX + 10, tabFish[i].fEnnemiPosY + 18) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX + 10, tabFish[i].fEnnemiPosY + 18) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 2;
						tabFish[i].touche = true;
					}

				}

				if (tabFish[i].ennemiLevel == 2) {

					// OK
					if ((P.level == 3) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX - 15, tabFish[i].fEnnemiPosY + 25) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 4;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX - 15, tabFish[i].fEnnemiPosY + 25) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 4;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX + 15, tabFish[i].fEnnemiPosY + 25) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 4;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX + 15, tabFish[i].fEnnemiPosY + 25) <= 20) && (tabFish[i].touche == false))) {
						P.numeroPoints = P.numeroPoints + 4;
						tabFish[i].touche = true;
					}

				}
			}
		}

		else {
			if ((P.fPlayerVelX <= 0) || (P.fPlayerVelX > 0) || (P.fPlayerVelY <= 0) || (P.fPlayerVelY > 0)) {

				if (tabFish[i].ennemiLevel == 1) {

					//OK

					if ((P.level == 1) && (tabFish[i].fEnnemiVelX > 0) && (P.bDirection) && ((P.distance(P.fPlayerPosX - 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX - 10, tabFish[i].fEnnemiPosY + 18) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX + 10, tabFish[i].fEnnemiPosY + 18) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (tabFish[i].fEnnemiVelX < 0) && (P.bDirection) && ((P.distance(P.fPlayerPosX - 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX - 10, tabFish[i].fEnnemiPosY + 18) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX + 10, tabFish[i].fEnnemiPosY + 18) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}
				}

				if (tabFish[i].ennemiLevel == 2) {

					// OK
					if ((P.level == 1) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX - 15, tabFish[i].fEnnemiPosY + 25) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX + 15, tabFish[i].fEnnemiPosY + 25) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX - 15, tabFish[i].fEnnemiPosY + 25) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX + 15, tabFish[i].fEnnemiPosY + 25) <= 12) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					// collision ennemi level 2 et player level 2

					// OK

					if ((P.level == 2) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX - 15, tabFish[i].fEnnemiPosY + 25) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX - 15, tabFish[i].fEnnemiPosY + 25) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX + 15, tabFish[i].fEnnemiPosY + 25) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX + 15, tabFish[i].fEnnemiPosY + 25) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

				}

				if (tabFish[i].ennemiLevel == 3) {

					if ((P.level == 1) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX - 25, tabFish[i].fEnnemiPosY + 35) <= 20) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX + 25, tabFish[i].fEnnemiPosY + 35) <= 20) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX - 25, tabFish[i].fEnnemiPosY + 35) <= 20) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 1) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 10, P.fPlayerPosY + 18, tabFish[i].fEnnemiPosX + 25, tabFish[i].fEnnemiPosY + 35) <= 20) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX - 25, tabFish[i].fEnnemiPosY + 35) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX - 25, tabFish[i].fEnnemiPosY + 35) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX + 25, tabFish[i].fEnnemiPosY + 35) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 2) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 15, P.fPlayerPosY + 25, tabFish[i].fEnnemiPosX + 25, tabFish[i].fEnnemiPosY + 35) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX - 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX - 25, tabFish[i].fEnnemiPosY + 25) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (!P.bDirection) && (tabFish[i].fEnnemiVelX > 0) && ((P.distance(P.fPlayerPosX + 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX - 25, tabFish[i].fEnnemiPosY + 35) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX - 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX + 25, tabFish[i].fEnnemiPosY + 35) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

					if ((P.level == 3) && (!P.bDirection) && (tabFish[i].fEnnemiVelX < 0) && ((P.distance(P.fPlayerPosX + 25, P.fPlayerPosY + 35, tabFish[i].fEnnemiPosX + 25, tabFish[i].fEnnemiPosY + 35) <= 17) && (tabFish[i].touche == false))) {
						vies--;
						tabFish[i].touche = true;
					}

				}
			}
		}
	}

	if (vies == 0) {
		P.numeroPoints = 0;
		P.level = 1;
		vies = 5;
	}
}



void Map::checkLevelPlayer(Player& P1, Player& P2) {

	if ((P1.numeroPoints >= 10) && (P2.numeroPoints >= 10)) {
		P1.level = 2;
		P2.level = 2;
	}

	if ((P1.numeroPoints >= 30) && (P2.numeroPoints >= 30)) {
		P1.level = 3;
		P2.level = 3;
	}
}
void Map::drawLevel2(olc::PixelGameEngine* pge) {

	olc::vf2d SpritePosMultiCell1 = { 0, 0 };
	olc::vd2d posInitImage = { 0,0 };

	// Draw le fond
	pge->DrawSprite(posInitImage, spriteBackGroundLevel2);

	// Draw joueur 1

	if (player1.level == 0) {
		olc::vd2d posJ1 = { player1.fPlayerPosX, player1.fPlayerPosY };
		if (player1.bDirection)
		{
			pge->DrawDecal(posJ1, decPlayerLevel0, { -0.5f, 0.5f });
		}
		else
			pge->DrawDecal(posJ1, decPlayerLevel0, { 0.5f, 0.5f });
	}

	if (player1.level == 1) {
		olc::vd2d posJ1 = { player1.fPlayerPosX, player1.fPlayerPosY };
		if (player1.bDirection)
		{
			pge->DrawDecal(posJ1, decPlayerLevel0, { -1.0f, 1.0f });
		}
		else
			pge->DrawDecal(posJ1, decPlayerLevel0, { 1.0f, 1.0f });
	}

	if (player1.level == 2) {
		olc::vd2d posJ1 = { player1.fPlayerPosX, player1.fPlayerPosY };
		if (player1.bDirection)
		{
			pge->DrawDecal(posJ1, decPlayerLevel0, { -1.5f, 1.5f });
		}
		else
			pge->DrawDecal(posJ1, decPlayerLevel0, { 1.5f, 1.5f });
	}

	if (player1.level == 3) {
		olc::vd2d posJ1 = { player1.fPlayerPosX, player1.fPlayerPosY };
		if (player1.bDirection)
		{
			pge->DrawDecal(posJ1, decPlayerLevel0, { -2.0f, 2.0f });
		}
		else
			pge->DrawDecal(posJ1, decPlayerLevel0, { 2.0f, 2.0f });
	}

	// Player 2
	if (player2.level == 0) {
		olc::vd2d posJ2 = { player2.fPlayerPosX, player2.fPlayerPosY };
		if (player2.bDirection)
		{
			pge->DrawDecal(posJ2, decPlayerLevel0, { -0.5f, 0.5f });
		}
		else
			pge->DrawDecal(posJ2, decPlayerLevel0, { 0.5f, 0.5f });
	}

	if (player2.level == 1) {
		olc::vd2d posJ2 = { player2.fPlayerPosX, player2.fPlayerPosY };
		olc::vd2d posCircleR = { player2.fPlayerPosX - 10 , player2.fPlayerPosY + 18 };
		olc::vd2d posCircleL = { player2.fPlayerPosX + 10, player2.fPlayerPosY + 18 };
		if (player2.bDirection)
		{
			pge->DrawDecal(posJ2, decPlayerLevel0, { -1.0f, 1.0f });
			//pge->DrawCircle(posCircleR, 12, olc::RED );
		}
		else {
			pge->DrawDecal(posJ2, decPlayerLevel0, { 1.0f, 1.0f });
			//pge->DrawCircle(posCircleL, 12, olc::GREEN );
		}

	}

	if (player2.level == 2) {
		olc::vd2d posJ2 = { player2.fPlayerPosX, player2.fPlayerPosY };
		olc::vd2d posCircleR = { player2.fPlayerPosX - 15 , player2.fPlayerPosY + 25 };
		olc::vd2d posCircleL = { player2.fPlayerPosX + 15, player2.fPlayerPosY + 25 };
		if (player2.bDirection)
		{
			pge->DrawDecal(posJ2, decPlayerLevel0, { -1.5f, 1.5f });
			//pge->DrawCircle(posCircleR, 17, olc::RED );
		}
		else {
			pge->DrawDecal(posJ2, decPlayerLevel0, { 1.5f, 1.5f });
			//pge->DrawCircle(posCircleL, 17, olc::GREEN );
		}

	}

	if (player2.level == 3) {
		olc::vd2d posJ2 = { player2.fPlayerPosX, player2.fPlayerPosY };
		olc::vd2d posCircleR = { player2.fPlayerPosX - 20.0f, player2.fPlayerPosY + 35.0f };
		olc::vd2d posCircleL = { player2.fPlayerPosX + 20.0f, player2.fPlayerPosY + 35.0f };
		if (player2.bDirection)
		{
			pge->DrawDecal(posJ2, decPlayerLevel0, { -2.0f, 2.0f });
			//pge->DrawCircle(posCircleR, 20, olc::RED );
		}
		else {
			pge->DrawDecal(posJ2, decPlayerLevel0, { 2.0f, 2.0f });
			//pge->DrawCircle(posCircleL, 20, olc::GREEN );
		}

	}

	// Draw ennemis
	for (int i = 0; i < numeroFish; i++) {

		olc::vf2d posEnnemi = { tabFish[i].fEnnemiPosX, tabFish[i].fEnnemiPosY };
		if (tabFish[i].ennemiLevel == 0) {

			olc::vd2d posCircleR = { tabFish[i].fEnnemiPosX - 5 , tabFish[i].fEnnemiPosY + 10 };
			olc::vd2d posCircleL = { tabFish[i].fEnnemiPosX + 5 , tabFish[i].fEnnemiPosY + 10 };

			if (tabFish[i].fEnnemiVelX > 0)
			{
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { -0.5f, 0.5f });
				//pge->DrawCircle(posCircleR, 20, olc::RED );
			}
			else {
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { 0.5f, 0.5f });
				//pge->DrawCircle(posCircleL, 20, olc::GREEN );
			}


		}

		if (tabFish[i].ennemiLevel == 1) {

			olc::vd2d posCircleR = { tabFish[i].fEnnemiPosX - 10 , tabFish[i].fEnnemiPosY + 18 };
			olc::vd2d posCircleL = { tabFish[i].fEnnemiPosX + 10 , tabFish[i].fEnnemiPosY + 18 };
			if (tabFish[i].fEnnemiVelX > 0)
			{
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { -1.0f, 1.0f });
				//pge->DrawCircle(posCircleR, 12, olc::RED );
			}
			else {
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { 1.0f, 1.0f });
				//pge->DrawCircle(posCircleL, 12, olc::GREEN );
			}

		}

		if (tabFish[i].ennemiLevel == 2) {

			olc::vd2d posCircleR = { tabFish[i].fEnnemiPosX - 15 , tabFish[i].fEnnemiPosY + 25 };
			olc::vd2d posCircleL = { tabFish[i].fEnnemiPosX + 15 , tabFish[i].fEnnemiPosY + 25 };

			if (tabFish[i].fEnnemiVelX > 0)
			{
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { -1.5f, 1.5f });
				//pge->DrawCircle(posCircleR, 17, olc::RED );
			}
			else {
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { 1.5f, 1.5f });
				//pge->DrawCircle(posCircleL, 17, olc::GREEN );
			}

		}

		if (tabFish[i].ennemiLevel == 3) {

			olc::vd2d posCircleR = { tabFish[i].fEnnemiPosX - 20 , tabFish[i].fEnnemiPosY + 35 };
			olc::vd2d posCircleL = { tabFish[i].fEnnemiPosX + 20 , tabFish[i].fEnnemiPosY + 35 };
			if (tabFish[i].fEnnemiVelX > 0)
			{
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { -2.0f, 2.0f });
				//pge->DrawCircle(posCircleR, 20, olc::RED );
			}
			else {
				pge->DrawDecal(posEnnemi, decPlayerLevel0, { 2.0f, 2.0f });
				//pge->DrawCircle(posCircleL, 20, olc::GREEN );
			}

		}


	}

	pge->DrawString({ 3, 3 }, "POINTS PLAYER 1", olc::YELLOW);
	string points_player_1 = to_string(player1.numeroPoints);
	string points_player_2 = to_string(player2.numeroPoints);
	pge->DrawString({ 50, 20 }, points_player_1, olc::YELLOW);
	pge->DrawString({ 680, 3 }, "POINTS PLAYER 2", olc::YELLOW);
	pge->DrawString({ 730, 20 }, points_player_2, olc::YELLOW);
	pge->DrawString({ 300, 3 }, "NEXT LEVEL:", olc::GREEN);

	if ((player1.numeroPoints < 10) && (player2.numeroPoints < 10)) {
		pge->DrawString({ 305, 20 }, "10 POINTS", olc::GREEN);
	}

	else if ((player1.numeroPoints < 30) && (player2.numeroPoints < 30)) {
		pge->DrawString({ 305, 20 }, "30 POINTS", olc::GREEN);
	}

	else if ((player1.numeroPoints < 40) && (player2.numeroPoints < 40)) {
		pge->DrawString({ 305, 20 }, "40 POINTS", olc::GREEN);
	}

	string lives_string = to_string(vies);
	pge->DrawString({ 450, 3 }, "LIVES: ", olc::RED);
	pge->DrawString({ 465, 20 }, lives_string, olc::RED);



}