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
		sAppName = "Example";
	}
	
	olc::Sprite* spriteTiles = nullptr;
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

		spriteTiles = new olc::Sprite("./data/water.png");

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
		
		//mouvements players
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

		//collitions



		mapLevel1.player1.fPlayerPosX = mapLevel1.player1.fPlayerPosX + mapLevel1.player1.fPlayerVelX * fElapsedTime;
        mapLevel1.player1.fPlayerPosY = mapLevel1.player1.fPlayerPosY + mapLevel1.player1.fPlayerVelY * fElapsedTime;

		mapLevel1.player2.fPlayerPosX = mapLevel1.player2.fPlayerPosX + mapLevel1.player2.fPlayerVelX * fElapsedTime;
        mapLevel1.player2.fPlayerPosY = mapLevel1.player2.fPlayerPosY + mapLevel1.player2.fPlayerVelY * fElapsedTime;

		mapLevel1.player1.fCameraPosX = mapLevel1.player1.fPlayerPosX;
		mapLevel1.player1.fCameraPosY = mapLevel1.player1.fPlayerPosY;

		mapLevel1.player2.fCameraPosX = mapLevel1.player2.fPlayerPosX;
		mapLevel1.player2.fCameraPosY = mapLevel1.player2.fPlayerPosY;

		/*colitions map
		if(mapLevel1.player1.fPlayerVelY <= 0){
			if(mapLevel1.player1.fPlayerPosY <= 0){	
				mapLevel1.player1.fPlayerVelY = 0;
				mapLevel1.player1.fPlayerPosY = 0;
			}	
		}

		/*
		if(mapLevel1.player1.fPlayerVelY >= 0){
			if(mapLevel1.player1.fPlayerPosY >= ScreenHeight() / 2){	
				mapLevel1.player1.fPlayerVelY = 0;
				mapLevel1.player1.fPlayerPosY = ScreenHeight() / 2;
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
				cout<<"passed"<<endl;
				mapLevel1.player1.fPlayerVelX = 0;
				mapLevel1.player1.fPlayerPosX = 63;
			}	
		}
		*/
		// Draw Level
		mapLevel1.player1.nTileWidth = 32;
		mapLevel1.player1.nTileHeight = 32;
		mapLevel1.player1.nVisibleTilesX = ScreenWidth() / mapLevel1.player1.nTileWidth;
		mapLevel1.player1.nVisibleTilesY = ScreenHeight() / mapLevel1.player1.nTileHeight;

		// Calculate Top-Leftmost visible tile
		mapLevel1.player1.fOffsetX = mapLevel1.player1.fCameraPosX - (float)mapLevel1.player1.nVisibleTilesX / 2.0f;
		mapLevel1.player1.fOffsetY = mapLevel1.player1.fCameraPosY - (float)mapLevel1.player1.nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (mapLevel1.player1.fOffsetX < 0) mapLevel1.player1.fOffsetX = 0;
		if (mapLevel1.player1.fOffsetY < 0) mapLevel1.player1.fOffsetY = 0;
		if (mapLevel1.player1.fOffsetX > mapLevel1.nLevelWidth - mapLevel1.player1.nVisibleTilesX) mapLevel1.player1.fOffsetX = mapLevel1.nLevelWidth - mapLevel1.player1.nVisibleTilesX;
		if (mapLevel1.player1.fOffsetY > mapLevel1.nLevelHeight - mapLevel1.player1.nVisibleTilesY) mapLevel1.player1.fOffsetY = mapLevel1.nLevelHeight - mapLevel1.player1.nVisibleTilesY;

		// Get offsets for smooth movement
		mapLevel1.player1.fTileOffsetX = (mapLevel1.player1.fOffsetX - (int)mapLevel1.player1.fOffsetX) *mapLevel1.player1.nTileWidth;
		mapLevel1.player1.fTileOffsetY = (mapLevel1.player1.fOffsetY - (int)mapLevel1.player1.fOffsetY) * mapLevel1.player1.nTileHeight;


		mapLevel1.player2.nTileWidth = 32;
		mapLevel1.player2.nTileHeight = 32;
		mapLevel1.player2.nVisibleTilesX = ScreenWidth() / mapLevel1.player2.nTileWidth;
		mapLevel1.player2.nVisibleTilesY = ScreenHeight() / mapLevel1.player2.nTileHeight;

		// Calculate Top-Leftmost visible tile
		mapLevel1.player2.fOffsetX = mapLevel1.player2.fCameraPosX - (float)mapLevel1.player2.nVisibleTilesX / 2.0f;
		mapLevel1.player2.fOffsetY = mapLevel1.player2.fCameraPosY - (float)mapLevel1.player2.nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (mapLevel1.player2.fOffsetX < 0){
			mapLevel1.player2.fOffsetX = 0;
		}
		if (mapLevel1.player2.fOffsetY < 0) mapLevel1.player2.fOffsetY = 0;

		if (mapLevel1.player2.fOffsetX > mapLevel1.nLevelWidth - mapLevel1.player2.nVisibleTilesX){
			mapLevel1.player2.fOffsetX = mapLevel1.nLevelWidth - mapLevel1.player2.nVisibleTilesX;
		} 

		if (mapLevel1.player2.fOffsetY > mapLevel1.nLevelHeight - mapLevel1.player2.nVisibleTilesY) mapLevel1.player2.fOffsetY = mapLevel1.nLevelHeight - mapLevel1.player2.nVisibleTilesY;

		// Get offsets for smooth movement
		mapLevel1.player2.fTileOffsetX = (mapLevel1.player2.fOffsetX - (int)mapLevel1.player2.fOffsetX) *mapLevel1.player2.nTileWidth;
		mapLevel1.player2.fTileOffsetY = (mapLevel1.player2.fOffsetY - (int)mapLevel1.player2.fOffsetY) * mapLevel1.player2.nTileHeight;

		// called once per frame
        for(int x = 0; x < ScreenWidth(); x++){

		    for (int y = 0; y < ScreenHeight() / 2; y++){


				Draw(x, y, olc::Pixel(255, x, 0));
				FillRect((mapLevel1.player1.fPlayerPosX - mapLevel1.player1.fOffsetX) * mapLevel1.player1.nTileWidth, (mapLevel1.player1.fPlayerPosY - mapLevel1.player1.fOffsetY) * mapLevel1.player1.nTileWidth, 8.0f, 8.0f, olc::Pixel(0, 255, 0));
				FillRect((mapLevel1.player2.fPlayerPosX - mapLevel1.player1.fOffsetX) * mapLevel1.player2.nTileWidth, (mapLevel1.player2.fPlayerPosY - mapLevel1.player1.fOffsetY) * mapLevel1.player2.nTileWidth, 8.0f, 8.0f, olc::Pixel(0, 0, 255));
			}
					
            for (int y = ScreenHeight() / 2; y < ScreenHeight(); y++){
				Draw(x, y, olc::Pixel(255, 0, x));
				FillRect((mapLevel1.player1.fPlayerPosX - mapLevel1.player2.fOffsetX) * mapLevel1.player1.nTileWidth, (mapLevel1.player1.fPlayerPosY - mapLevel1.player2.fOffsetY) * mapLevel1.player1.nTileWidth + (ScreenHeight() / 2), 8.0f, 8.0f, olc::Pixel(0, 255, 0));
				FillRect((mapLevel1.player2.fPlayerPosX - mapLevel1.player2.fOffsetX) * mapLevel1.player2.nTileWidth, (mapLevel1.player2.fPlayerPosY - mapLevel1.player2.fOffsetY) * mapLevel1.player2.nTileWidth + (ScreenHeight() / 2), 8.0f, 8.0f, olc::Pixel(0, 0, 255));
			}
				
        }


        for (int x = 0; x < mapLevel1.player1.nVisibleTilesX; x++){
            for(int y = 0; y < mapLevel1.player1.nVisibleTilesY; y++){
                wchar_t sTileID = GetTile(x + mapLevel1.player1.fOffsetX, y + mapLevel1.player1.fOffsetY);
				//olc::vf2d positionBackScreen(x + fOffsetX, y + fOffsetY);
                switch (sTileID)
                {
                case L'o':
                    FillRect(x * mapLevel1.player1.nTileWidth - mapLevel1.player1.fTileOffsetX, y * mapLevel1.player1.nTileHeight - mapLevel1.player1.fTileOffsetY, (x + 1) * mapLevel1.player1.nTileWidth - mapLevel1.player1.fTileOffsetX, (y + 1) * mapLevel1.player1.nTileHeight - mapLevel1.player1.fTileOffsetY, olc::Pixel(255, 0, 0));
                    //DrawPartialSprite(x * mapLevel1.player1.nTileWidth - mapLevel1.player1.fTileOffsetX, y * mapLevel1.player1.nTileHeight - mapLevel1.player1.fTileOffsetY, spriteTiles, 2 * mapLevel1.player1.nTileWidth, 0 * mapLevel1.player1.nTileHeight, mapLevel1.player1.nTileWidth, mapLevel1.player1.nTileHeight);
					break;               
                default:
                    break;
                }
            }
        }


		    return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}



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
                mapLevel1.player1.fPlayerVelY = -4.0f;
            }

            if(GetKey(olc::Key::DOWN).bHeld){
                mapLevel1.player1.fPlayerVelY = 4.0f;
            }

            if(GetKey(olc::Key::LEFT).bHeld){
                mapLevel1.player1.fPlayerVelX = -4.0f;
            }

            if(GetKey(olc::Key::RIGHT).bHeld){
                mapLevel1.player1.fPlayerVelX = 4.0f;
            }

			// mouvements player 2
			if(GetKey(olc::Key::W).bHeld){
                mapLevel1.player2.fPlayerVelY = -4.0f;
            }

            if(GetKey(olc::Key::S).bHeld){
                mapLevel1.player2.fPlayerVelY = 4.0f;
            }

            if(GetKey(olc::Key::A).bHeld){
                mapLevel1.player2.fPlayerVelX = -4.0f;
            }

            if(GetKey(olc::Key::D).bHeld){
                mapLevel1.player2.fPlayerVelX = 4.0f;
            }

        }


		mapLevel1.player1.fPlayerPosX = mapLevel1.player1.fPlayerPosX + mapLevel1.player1.fPlayerVelX * fElapsedTime;
        mapLevel1.player1.fPlayerPosY = mapLevel1.player1.fPlayerPosY + mapLevel1.player1.fPlayerVelY * fElapsedTime;
		mapLevel1.player2.fPlayerPosX = mapLevel1.player2.fPlayerPosX + mapLevel1.player2.fPlayerVelX * fElapsedTime;
        mapLevel1.player2.fPlayerPosY = mapLevel1.player2.fPlayerPosY + mapLevel1.player2.fPlayerVelY * fElapsedTime;

		//COLLISIONS

        mapLevel1.player1.fCameraPosX = mapLevel1.player1.fPlayerPosX;
		mapLevel1.player1.fCameraPosY = mapLevel1.player1.fPlayerPosY;

		mapLevel1.player2.fCameraPosX = mapLevel1.player2.fPlayerPosX;
		mapLevel1.player2.fCameraPosY = mapLevel1.player2.fPlayerPosY;


		// Draw Level
		mapLevel1.player1.nTileWidth = 32;
		mapLevel1.player1.nTileHeight = 32;
		mapLevel1.player1.nVisibleTilesX = ScreenWidth() / mapLevel1.player1.nTileWidth;
		mapLevel1.player1.nVisibleTilesY = ScreenHeight() / mapLevel1.player1.nTileHeight;

		// Calculate Top-Leftmost visible tile
		mapLevel1.player1.fOffsetX = mapLevel1.player1.fCameraPosX - (float)mapLevel1.player1.nVisibleTilesX / 2.0f;
		mapLevel1.player1.fOffsetY = mapLevel1.player1.fCameraPosY - (float)mapLevel1.player1.nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (mapLevel1.player1.fOffsetX < 0) mapLevel1.player1.fOffsetX = 0;
		if (mapLevel1.player1.fOffsetY < 0) mapLevel1.player1.fOffsetY = 0;
		if (mapLevel1.player1.fOffsetX > mapLevel1.nLevelWidth - mapLevel1.player1.nVisibleTilesX) mapLevel1.player1.fOffsetX = mapLevel1.nLevelWidth - mapLevel1.player1.nVisibleTilesX;
		if (mapLevel1.player1.fOffsetY > mapLevel1.nLevelHeight - mapLevel1.player1.nVisibleTilesY) mapLevel1.player1.fOffsetY = mapLevel1.nLevelHeight - mapLevel1.player1.nVisibleTilesY;

		// Get offsets for smooth movement
		mapLevel1.player1.fTileOffsetX = (mapLevel1.player1.fOffsetX - (int)mapLevel1.player1.fOffsetX) * mapLevel1.player1.nTileWidth;
		mapLevel1.player1.fTileOffsetY = (mapLevel1.player1.fOffsetY - (int)mapLevel1.player1.fOffsetY) * mapLevel1.player1.nTileHeight;

		mapLevel1.player2.nTileWidth = 32;
		mapLevel1.player2.nTileHeight = 32;
		mapLevel1.player2.nVisibleTilesX = ScreenWidth() / mapLevel1.player2.nTileWidth;
		mapLevel1.player2.nVisibleTilesY = ScreenHeight() / mapLevel1.player2.nTileHeight;

		// Calculate Top-Leftmost visible tile
		mapLevel1.player2.fOffsetX = mapLevel1.player2.fCameraPosX - (float)mapLevel1.player2.nVisibleTilesX / 2.0f;
		mapLevel1.player2.fOffsetY = mapLevel1.player2.fCameraPosY - (float)mapLevel1.player2.nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (mapLevel1.player2.fOffsetX < 0){
			mapLevel1.player2.fOffsetX = 0;
		}
		if (mapLevel1.player2.fOffsetY < 0) mapLevel1.player2.fOffsetY = 0;

		if (mapLevel1.player2.fOffsetX > mapLevel1.nLevelWidth - mapLevel1.player2.nVisibleTilesX){
			mapLevel1.player2.fOffsetX = mapLevel1.nLevelWidth - mapLevel1.player2.nVisibleTilesX;
		} 

		if (mapLevel1.player2.fOffsetY > mapLevel1.nLevelHeight - mapLevel1.player2.nVisibleTilesY) mapLevel1.player2.fOffsetY = mapLevel1.nLevelHeight - mapLevel1.player2.nVisibleTilesY;

		// Get offsets for smooth movement
		mapLevel1.player2.fTileOffsetX = (mapLevel1.player2.fOffsetX - (int)mapLevel1.player2.fOffsetX) *mapLevel1.player2.nTileWidth;
		mapLevel1.player2.fTileOffsetY = (mapLevel1.player2.fOffsetY - (int)mapLevel1.player2.fOffsetY) * mapLevel1.player2.nTileHeight;

        
		for(int x = 0; x < ScreenWidth(); x++){

		    for (int y = 0; y < ScreenHeight() / 2; y++){


				Draw(x, y, olc::Pixel(255, x, 0));
				FillRect((mapLevel1.player1.fPlayerPosX - mapLevel1.player1.fOffsetX) * mapLevel1.player1.nTileWidth, (mapLevel1.player1.fPlayerPosY - mapLevel1.player1.fOffsetY) * mapLevel1.player1.nTileWidth, 8.0f, 8.0f, olc::Pixel(0, 255, 0));
				FillRect((mapLevel1.player2.fPlayerPosX - mapLevel1.player1.fOffsetX) * mapLevel1.player2.nTileWidth, (mapLevel1.player2.fPlayerPosY - mapLevel1.player1.fOffsetY) * mapLevel1.player2.nTileWidth, 8.0f, 8.0f, olc::Pixel(0, 0, 255));
			}
					
            for (int y = ScreenHeight() / 2; y < ScreenHeight(); y++){
				Draw(x, y, olc::Pixel(255, 0, x));
				FillRect((mapLevel1.player1.fPlayerPosX - mapLevel1.player2.fOffsetX) * mapLevel1.player1.nTileWidth, (mapLevel1.player1.fPlayerPosY - mapLevel1.player2.fOffsetY) * mapLevel1.player1.nTileWidth + (ScreenHeight() / 2), 8.0f, 8.0f, olc::Pixel(0, 255, 0));
				FillRect((mapLevel1.player2.fPlayerPosX - mapLevel1.player2.fOffsetX) * mapLevel1.player2.nTileWidth, (mapLevel1.player2.fPlayerPosY - mapLevel1.player2.fOffsetY) * mapLevel1.player2.nTileWidth + (ScreenHeight() / 2), 8.0f, 8.0f, olc::Pixel(0, 0, 255));
			}
				
        }
		//DrawPartialSprite((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
		//DrawSprite((mapLevel1.player1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player1.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer);
		//DrawPartialSprite((mapLevel1.player2.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.player2.fPlayerPosY - fOffsetY) * nTileWidth, spritePlayer, 0 * nTileWidth, 0 * nTileHeight, nTileWidth, nTileHeight);
		
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

