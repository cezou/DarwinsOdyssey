
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
			spritePlayer = new olc::Sprite("./data/Fish1.png");

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


		mapLevel1.player1.fPlayerPosX = mapLevel1.player1.fPlayerPosX + mapLevel1.player1.fPlayerVelX * fElapsedTime;
		mapLevel1.player1.fPlayerPosY = mapLevel1.player1.fPlayerPosY + mapLevel1.player1.fPlayerVelY * fElapsedTime;

		mapLevel1.player2.fPlayerPosX = mapLevel1.player2.fPlayerPosX + mapLevel1.player2.fPlayerVelX * fElapsedTime;
        mapLevel1.player2.fPlayerPosY = mapLevel1.player2.fPlayerPosY + mapLevel1.player2.fPlayerVelY * fElapsedTime;

		//coaltions à gauche

		if(mapLevel1.player1.fPlayerVelX <= 0){ // il va à gauche
			if(GetTile(mapLevel1.player1.fPlayerPosX + 0.0f, mapLevel1.player1.fPlayerPosY + 0.0f) != L'.' || GetTile(mapLevel1.player1.fPlayerPosX + 0.0f, mapLevel1.player1.fPlayerPosY + 0.9f) != L'.')
			{
				mapLevel1.player1.fPlayerPosX = (int)mapLevel1.player1.fPlayerPosX + 1;
				mapLevel1.player1.fPlayerVelX = 0;
			}
		}

		if(mapLevel1.player2.fPlayerVelX <= 0){ // il va à gauche
			if(GetTile(mapLevel1.player2.fPlayerPosX + 0.0f, mapLevel1.player2.fPlayerPosY + 0.0f) != L'.' || GetTile(mapLevel1.player2.fPlayerPosX + 0.0f, mapLevel1.player2.fPlayerPosY + 0.9f) != L'.')
			{
				mapLevel1.player2.fPlayerPosX = (int)mapLevel1.player2.fPlayerPosX + 1;
				mapLevel1.player2.fPlayerVelX = 0;
			}
		}

		//coalitions à droite

		if(mapLevel1.player1.fPlayerVelX >= 0){
			if(GetTile(mapLevel1.player1.fPlayerPosX + 1.0f, mapLevel1.player1.fPlayerPosY + 0.0f) != L'.' || GetTile(mapLevel1.player1.fPlayerPosX + 1.0f, mapLevel1.player1.fPlayerPosY + 0.9f) != L'.')
			{
				mapLevel1.player1.fPlayerPosX = (int)mapLevel1.player1.fPlayerPosX;
				mapLevel1.player1.fPlayerVelX = 0;
			}
		}

		if(mapLevel1.player2.fPlayerVelX >= 0){
			if(GetTile(mapLevel1.player2.fPlayerPosX + 1.0f, mapLevel1.player2.fPlayerPosY + 0.0f) != L'.' || GetTile(mapLevel1.player2.fPlayerPosX + 1.0f, mapLevel1.player2.fPlayerPosY + 0.9f) != L'.')
			{
				mapLevel1.player2.fPlayerPosX = (int)mapLevel1.player2.fPlayerPosX;
				mapLevel1.player2.fPlayerVelX = 0;
			}
		}

		//coalitions en bas
		if (mapLevel1.player1.fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(mapLevel1.player1.fPlayerPosX + 0.0f, mapLevel1.player1.fPlayerPosY + 0.0f) != L'.' || GetTile(mapLevel1.player1.fPlayerPosX + 0.9f, mapLevel1.player1.fPlayerPosY + 0.0f) != L'.')
			{
				mapLevel1.player1.fPlayerPosY = (int)mapLevel1.player1.fPlayerPosY + 1;
				mapLevel1.player1.fPlayerVelY = 0;
			}
		}
		
		if (mapLevel1.player2.fPlayerVelY <= 0) // Moving Up
		{
			if (GetTile(mapLevel1.player2.fPlayerPosX + 0.0f, mapLevel1.player2.fPlayerPosY) != L'.' || GetTile(mapLevel1.player2.fPlayerPosX + 1.0f, mapLevel1.player2.fPlayerPosY) != L'.')
			{
				mapLevel1.player2.fPlayerPosY = (int)mapLevel1.player2.fPlayerPosY + 1;
				mapLevel1.player2.fPlayerVelY = 0;
			}
		}

		//collitions en haut
		if (mapLevel1.player1.fPlayerVelY >= 0) // Moving Down
		{
			if (GetTile(mapLevel1.player1.fPlayerPosX + 0.0f, mapLevel1.player1.fPlayerPosY + 1.0f) != L'.' || GetTile(mapLevel1.player1.fPlayerPosX + 0.9f, mapLevel1.player1.fPlayerPosY + 1.0f) != L'.')
			{
				mapLevel1.player1.fPlayerPosY = (int)mapLevel1.player1.fPlayerPosY;
				mapLevel1.player1.fPlayerVelY = 0;
			}
		}

		if (mapLevel1.player2.fPlayerVelY >= 0) // Moving Down
		{
			if (GetTile(mapLevel1.player2.fPlayerPosX + 0.0f, mapLevel1.player2.fPlayerPosY + 1.0f) != L'.' || GetTile(mapLevel1.player2.fPlayerPosX + 0.9f, mapLevel1.player2.fPlayerPosY + 1.0f) != L'.')
			{
				mapLevel1.player2.fPlayerPosY = (int)mapLevel1.player2.fPlayerPosY;
				mapLevel1.player2.fPlayerVelY = 0;
			}
		}


        mapLevel1.player1.fCameraPosX = mapLevel1.player1.fPlayerPosX;
		mapLevel1.player1.fCameraPosY = mapLevel1.player1.fPlayerPosY;

		mapLevel1.player2.fCameraPosX = mapLevel1.player2.fPlayerPosX;
		mapLevel1.player2.fCameraPosY = mapLevel1.player2.fPlayerPosY;

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
                    FillRect(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, olc::Pixel(0, 0, 255));
					//DrawSprite(positionBackScreen, spriteTiles);
					break;
                case L'#':
                    //FillRect(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, olc::Pixel(255, 0, 0));
                    DrawPartialSprite(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, spriteTiles, 2 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
					break;
				case L'o':
                    FillRect(x * nTileWidth - fTileOffsetX, y * nTileHeight - fTileOffsetY, (x + 1) * nTileWidth - fTileOffsetX, (y + 1) * nTileHeight - fTileOffsetY, olc::Pixel(255, 255, 0));
                    
					break;                 
                default:
                    break;
                }
            }
        }

        
		//FillRect((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, 8.0f, 8.0f, olc::Pixel(0, 255, 0));
		DrawPartialSprite((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer, 2 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
		//DrawSprite((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer);
		FillRect((mapLevel1.player2.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player2.fPlayerPosY - fOffsetY) * nTileWidth, 8.0f, 8.0f, olc::Pixel(0, 255, 255));
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

