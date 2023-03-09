#include <iostream>
#include "./Map.h"
#include "./Player.h"

using namespace std;

//constructeur par defaut
Map::Map(){
    nLevelWidth = 64;
    nLevelHeight = 16;
    sLevel += L"................................................................";
    sLevel += L"................................................................";
    sLevel += L"................................................................";
    sLevel += L"................................................................";
    sLevel += L"........................#.......................................";
    sLevel += L"................................................................";
    sLevel += L"................................................................";
    sLevel += L"................................................................";
    sLevel += L"................................................................";
    sLevel += L"................................................................";
    sLevel += L"...........................#....................................";
    sLevel += L"................................................................";
    sLevel += L"#######################################...######################";
    sLevel += L"#######################################...######################";
    sLevel += L".......................................###..............#.......";
    sLevel += L"................................................................";
}

//constructeur avec parametres
Map::Map(wstring sLevel_param, int nLevelWidth_param, int nLevelHeight_param){
    sLevel = sLevel_param;
    nLevelWidth = nLevelWidth_param;
    nLevelHeight = nLevelHeight_param;
}

int Map::getNLevelWidth(){
    return nLevelWidth;
}

int Map::getNLevelHeight(){
    return nLevelHeight;
}

void Map::setCamera(float fElapsedTime){

    Player player;

        // Utility Lambdas
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
				sLevel[y*nLevelWidth + x] = c;
		};



        player.move(fElapsedTime);



        fCameraPosX = player.posX;
        fCameraPosY = player.posY;

        // Draw Level 
		int nTileWidth = 16;
		int nTileHeight = 16;
		int nVisibleTilesX = ScreenWidth() / nTileWidth;
		int nVisibleTilesY = ScreenHeight() / nTileHeight;

		// Calculate Top-Leftmost visible tile
		float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
		float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

		// Clamp camera to game boundaries
		if (fOffsetX < 0) fOffsetX = 0;
		if (fOffsetY < 0) fOffsetY = 0;
		if (fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
		if (fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

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

        FillRect((player.posX - fOffsetX) * nTileWidth, (player.posY - fOffsetY) * nTileWidth, (player.posX - fOffsetX + 1.0f) * nTileWidth, (player.posY - fOffsetY + 1.0f) * nTileHeight, olc::Pixel(0, 255, 0));


}