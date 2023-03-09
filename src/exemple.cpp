#define OLC_PGE_APPLICATION
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
//#include "./Player.h"
#include "./Map.h"

class Game : public olc::PixelGameEngine
{
	public:
		game()
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


		}
};


int main()
{
	Game game;

	if (game.Construct(240, 135, 8, 8))
		game.Start();
		

	return 0;
}