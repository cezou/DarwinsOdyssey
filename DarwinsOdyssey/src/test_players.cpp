
#define OLC_PGE_APPLICATION
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
//#include "./Player.h"
#include "./Map.h"
#include <iostream>
#include <string>


using namespace std;

class Game : public olc::PixelGameEngine
{
	public:
		Game()
		{
			sAppName = "Darwin's Odyssey";
		}
		olc::Sprite* spriteTiles = nullptr;
		olc::Sprite* spritePlayer = nullptr;
		olc::Sprite* spriteCellule = nullptr;
		olc::Sprite* spriteFond = nullptr;
		Map mapLevel1;
		
	public:


	~Game(){
		delete spriteTiles;
		delete spritePlayer;
	}
		bool OnUserCreate() override
		{
			// initialisation player 1
			mapLevel1.player1.fCameraPosX = 0.0f;
    		mapLevel1.player1.fCameraPosY = 0.0f;

    		mapLevel1.player1.fPlayerPosX = 1.0f;
			mapLevel1.player1.fPlayerPosY = 1.0f;
			mapLevel1.player1.fPlayerVelX = 0.0f;
			mapLevel1.player1.fPlayerVelY = 0.0f;



			// initialisation player 2
			mapLevel1.player2.fCameraPosX = 0.0f;
    		mapLevel1.player2.fCameraPosY = 0.0f;

    		mapLevel1.player2.fPlayerPosX = 8.0f;
			mapLevel1.player2.fPlayerPosY = 8.0f;
			mapLevel1.player2.fPlayerVelX = 0.0f;
			mapLevel1.player2.fPlayerVelY = 0.0f;

			spriteTiles = new olc::Sprite("./data/water.png");
			spritePlayer = new olc::Sprite("./data/Fish.png");
			spriteCellule = new olc::Sprite("./data/cellule.png");
			spriteFond = new olc::Sprite("./data/Fond.png");

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

        mapLevel1.player1.fPlayerVelY = 0.0f;
        mapLevel1.player1.fPlayerVelX = 0.0f;

		mapLevel1.player2.fPlayerVelY = 0.0f;
        mapLevel1.player2.fPlayerVelX = 0.0f;

        if(IsFocused()){
			
			// mouvements player 1
            if(GetKey(olc::Key::UP).bHeld){
                mapLevel1.player1.fPlayerVelY = -6.0f;
            }

            if(GetKey(olc::Key::DOWN).bHeld){
                mapLevel1.player1.fPlayerVelY = 6.0f;
            }

            if(GetKey(olc::Key::LEFT).bHeld){
                mapLevel1.player1.fPlayerVelX = -6.0f;
            }

            if(GetKey(olc::Key::RIGHT).bHeld){
                mapLevel1.player1.fPlayerVelX = 6.0f;
            }

			// mouvements player 2
			if(GetKey(olc::Key::W).bHeld){
                mapLevel1.player2.fPlayerVelY = -6.0f;
            }

            if(GetKey(olc::Key::S).bHeld){
                mapLevel1.player2.fPlayerVelY = 6.0f;
            }

            if(GetKey(olc::Key::A).bHeld){
                mapLevel1.player2.fPlayerVelX = -6.0f;
            }

            if(GetKey(olc::Key::D).bHeld){
                mapLevel1.player2.fPlayerVelX = 6.0f;
            }

        }


		float newPosX = mapLevel1.player1.fPlayerPosX + mapLevel1.player1.fPlayerVelX * fElapsedTime;
		float newPosY = mapLevel1.player1.fPlayerPosY + mapLevel1.player1.fPlayerVelY * fElapsedTime;
		float newPos2X = mapLevel1.player2.fPlayerPosX + mapLevel1.player2.fPlayerVelX * fElapsedTime;
		float newPos2Y = mapLevel1.player2.fPlayerPosY + mapLevel1.player2.fPlayerVelY * fElapsedTime;

		mapLevel1.player2.fPlayerPosX = mapLevel1.player2.fPlayerPosX + mapLevel1.player2.fPlayerVelX * fElapsedTime;
        mapLevel1.player2.fPlayerPosY = mapLevel1.player2.fPlayerPosY + mapLevel1.player2.fPlayerVelY * fElapsedTime;

		//collitions player1 avec virus

		if(mapLevel1.player1.fPlayerVelX <= 0){ // Moving left
			if(GetTile(newPosX + 0.0f, newPosY + 0.0f) == L'#' || GetTile(newPosX + 0.0f, newPosY + 0.9f) == L'#')
			{
				newPosX = 1.0f;
				newPosY = 1.0f;
			}
		}

		else{ // Moving right
			if(GetTile(newPosX + 1.0f, newPosY + 0.0f) == L'#' || GetTile(newPosX + 1.0f, newPosY + 0.9f) == L'#')
			{
				newPosX = 1.0f;
				newPosY = 1.0f;
			}
		}

		if (mapLevel1.player1.fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(newPosX + 0.0f, newPosY) == L'#' || GetTile(newPosX + 0.9f, newPosY) == L'#')
			{
				newPosX = 1.0f;
				newPosY = 1.0f;
			}
		}

		else{ //Moving down
			if (GetTile(newPosX + 0.0f, newPosY + 1.0f) == L'#' || GetTile(newPosX + 0.9f, newPosY + 1.0f) == L'#')
			{
				newPosX = 1.0f;
				newPosY = 1.0f;
			}
		}

		//collitions player1 avec cellules
		if(mapLevel1.player1.fPlayerVelX <= 0){ // Moving left
			if(GetTile(newPosX + 0.0f, newPosY + 0.0f) == L'o' || GetTile(newPosX + 0.0f, newPosY + 0.9f) == L'o')
			{
				mapLevel1.nb_cellules_prises ++;
				SetTile(newPosX, newPosY, L'.');
			}
		}

		else{ // Moving right
			if(GetTile(newPosX + 1.0f, newPosY + 0.0f) == L'o' || GetTile(newPosX + 1.0f, newPosY + 0.9f) == L'o')
			{
				mapLevel1.nb_cellules_prises ++;
				SetTile(newPosX, newPosY, L'.');
			}
		}

		if (mapLevel1.player1.fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(newPosX + 0.0f, newPosY) == L'o' || GetTile(newPosX + 0.9f, newPosY) == L'o')
			{
				mapLevel1.nb_cellules_prises ++;
				SetTile(newPosX, newPosY, L'.');
			}
		}

		else{ //Moving down
			if (GetTile(newPosX + 0.0f, newPosY + 1.0f) == L'o' || GetTile(newPosX + 0.9f, newPosY + 1.0f) == L'o')
			{
				mapLevel1.nb_cellules_prises ++;
				SetTile(newPosX, newPosY, L'.');
			}
		}

		//collitions player2
		

		if(newPos2X <= 0){ // Moving left
			if(GetTile(newPos2X + 0.0f, newPos2Y + 0.0f) == L'#' || GetTile(newPos2X + 0.0f, newPos2Y + 0.9f) == L'#')
			{
				newPos2X = 1.0f;
				newPos2Y = 1.0f;
			}
		}

		else{ // Moving right
			if(GetTile(newPos2X + 1.0f, newPos2Y + 0.0f) == L'#' || GetTile(newPos2X + 1.0f, newPos2Y + 0.9f) == L'#')
			{
				newPos2X = 1.0f;
				newPos2Y = 1.0f;
			}
		}

		if (mapLevel1.player1.fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(newPos2X + 0.0f, newPos2Y) == L'#' || GetTile(newPos2X + 0.9f, newPos2Y) == L'#')
			{
				newPos2X = 1.0f;
				newPos2Y = 1.0f;
			}
		}

		else{ //Moving down
			if (GetTile(newPos2X + 0.0f, newPos2Y + 1.0f) == L'#' || GetTile(newPos2X + 0.9f, newPos2Y + 1.0f) == L'#')
			{
				newPos2X = 1.0f;
				newPos2Y = 1.0f;
			}
		}

		mapLevel1.player1.fPlayerPosX = newPosX;
		mapLevel1.player1.fPlayerPosY = newPosY;

		mapLevel1.player2.fPlayerPosX = newPos2X;
		mapLevel1.player2.fPlayerPosY = newPos2Y;

        mapLevel1.player1.fCameraPosX = mapLevel1.player1.fPlayerPosX;
		mapLevel1.player1.fCameraPosY = mapLevel1.player1.fPlayerPosY;

		mapLevel1.player2.fCameraPosX = mapLevel1.player2.fPlayerPosX;
		mapLevel1.player2.fCameraPosY = mapLevel1.player2.fPlayerPosY;

		if (mapLevel1.nb_cellules_prises != 0){
			cout<<"Nb cellules = " << mapLevel1.nb_cellules_prises<< endl;
		}
		// Draw Level
		int nTileWidth = 32;
		int nTileHeight = 32;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile
		float fOffsetX = mapLevel1.player1.fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = mapLevel1.player1.fCameraPosY - (float)nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > mapLevel1.nLevelWidth - nVisibleTilesX) fOffsetX = mapLevel1.nLevelWidth - nVisibleTilesX;
		if (fOffsetY > mapLevel1.nLevelHeight - nVisibleTilesY) fOffsetY = mapLevel1.nLevelHeight - nVisibleTilesY;

		// Get offsets for smooth movement
		float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
		float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;



        for (int x = -2; x < nVisibleTilesX + 2; x++){
            for(int y = -2; y < nVisibleTilesY + 2; y++){
                wchar_t sTileID = GetTile(x + fOffsetX, y + fOffsetY);
				//olc::vf2d positionBackScreen(x + fOffsetX, y + fOffsetY);
                switch (sTileID)
                {
                case L'.':
                    DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteFond, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					//DrawSprite(positionBackScreen, spriteTiles);
					break;
                case L'#':
                    //FillRect(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, olc::Pixel(255, 0, 0));
                    DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 2 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'o':
                    DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteCellule, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
                    
					break;                 
                default:
                    break;
                }
            }
        }

        
		//FillRect((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, 8.0f, 8.0f, olc::Pixel(0, 255, 0));
		DrawPartialSprite((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
		//DrawSprite((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer);
		DrawPartialSprite((mapLevel1.player2.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player2.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
		

		for(int x = 0; x < ScreenWidth(); x++){
		    for (int y = 0; y < ScreenHeight() / 2; y++){ 
				// Boucle Player 1 
				Draw(x, y, olc::Pixel(0, 0, 255));
			}
	
            for (int y = ScreenHeight() / 2; y < ScreenHeight(); y++){
				// Boucle Player 2
				Draw(x, y, olc::Pixel(255, 0, 0));
			}
				
        }
		return true;
		}
};


int main()
{
	Game game;

	if (game.Construct(256, 240, 8, 8))
		game.Start();
	
	

	return 0;
}

