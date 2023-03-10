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
			return true;
		}

		bool OnUserUpdate(float fElapsedTime) override
		{
			//cout<<"prova 1 = " << fElapsedTime << endl;
			//mapLevel1.setCamera(fElapsedTime);

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

        mapLevel1.fPlayerVelY = 0.0f;
        mapLevel1.fPlayerVelX = 0.0f;

        if(IsFocused()){
			cout<<"passed 1"<< endl;
            if(GetKey(olc::Key::W).bHeld){
                mapLevel1.fPlayerVelY = -6.0f;
            }

            if(GetKey(olc::Key::S).bHeld){
				cout<< "passed 2" << endl;
                mapLevel1.fPlayerVelY = 6.0f;
            }

            if(GetKey(olc::Key::A).bHeld){
                mapLevel1.fPlayerVelX = -6.0f;
            }

            if(GetKey(olc::Key::D).bHeld){
                mapLevel1.fPlayerVelX = 6.0f;
            }
        }


        mapLevel1.fPlayerPosX = mapLevel1.fPlayerPosX + mapLevel1.fPlayerVelX * fElapsedTime;
        mapLevel1.fPlayerPosY = mapLevel1.fPlayerPosY + mapLevel1.fPlayerVelY * fElapsedTime;

        mapLevel1.fCameraPosX = mapLevel1.fPlayerPosX;
		mapLevel1.fCameraPosY = mapLevel1.fPlayerPosY;

		// Draw Level
		int nTileWidth = 8;
		int nTileHeight = 8;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile
		float fOffsetX = mapLevel1.fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = mapLevel1.fCameraPosY - (float)nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > mapLevel1.nLevelWidth - nVisibleTilesX) fOffsetX = mapLevel1.nLevelWidth - nVisibleTilesX;
		if (fOffsetY > mapLevel1.nLevelHeight - nVisibleTilesY) fOffsetY = mapLevel1.nLevelHeight - nVisibleTilesY;

		// Get offsets for smooth movement
		float fTileOffsetX = (fOffsetX - (int)fOffsetX) * nTileWidth;
		float fTileOffsetY = (fOffsetY - (int)fOffsetY) * nTileHeight;

        for (int x = 0; x < nVisibleTilesX; x++){
            for(int y = 0; y < nVisibleTilesY; y++){
                wchar_t sTileID = GetTile(x + fOffsetX, y + fOffsetY);
                switch (sTileID)
                {
                case L'.':
                    FillRect(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, olc::Pixel(0, 0, 255));
                    break;
                case L'#':
                    FillRect(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, olc::Pixel(255, 0, 0));
                    break;               
                default:
                    break;
                }
            }
        }

        FillRect((mapLevel1.fPlayerPosX - fOffsetX) * nTileWidth, (mapLevel1.fPlayerPosY - fOffsetY) * nTileWidth, (mapLevel1.fPlayerPosX - fOffsetX + 1.0f) * nTileWidth, (mapLevel1.fPlayerPosY - fOffsetY + 1.0f) * nTileHeight, olc::Pixel(0, 255, 0));
		return true;
		}
};


int main()
{
	Game game;

	if (game.Construct(240, 135, 8, 8))
		game.Start();
	
	

	return 0;
}