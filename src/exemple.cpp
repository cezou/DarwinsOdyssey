#define OLC_PGE_APPLICATION
#include "../inc/olcPixelGameEngine-master/olcPixelGameEngine.h"
#include "./Player.h"

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Darwin's Odyssey";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int x = 0; x <= ScreenWidth()/2; x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(0, 0, 255));	
	
	Player P;			
	DrawCircle(P.x, P.y, 10, olc::Pixel(255, 255, 255));
	P.move();

		for (int x = ScreenWidth()/2; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(0, 255, 0 ));	
				
		return true;
	}
};


int main()
{
	Example player1;

	if (player1.Construct(240, 135, 8, 8))
		player1.Start();
		

	return 0;
}