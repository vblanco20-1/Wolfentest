#include <iostream>
#include <SDL.h>
#include <random>
#include "MathUtils.h"
#include "SDL_pixels.h"
#include "Surface.h"
#include<vector>

using namespace std;
const int windowHeight = 480;
const int windowWidth = 640;
SDL_PixelFormat * pxformat;


float fclamp(float num, float min, float max)
{
	if (num < min)
	{
		return min;
	}
	else if (num > max)
	{
		return max;
	}
	else
	{
		return num;
	}
}

struct Viewpoint
{
	Vector2d origin;
	Vector2d orientation;
};


void drawFloorAndCeiling(Uint32 * pixels, float horizonHeight, Uint32 celingColor, Uint32 floorColor)
{
	int horizonPixel = horizonHeight*windowHeight;
	for (int y = 0; y < windowHeight; y++)
	{
		for (int x = 0; x < windowWidth; x++)
		{
			int i = y * windowWidth + x;

			if (y < horizonPixel)
			{
				pixels[i] = celingColor;
			}
			else
			{
				pixels[i] = floorColor;
			}
		}
	}

}

void drawColumn(Uint32 * pixels, Uint32 Color, int column, int top, int bot)
{
	int x = column;
	for (int y = top; y <= bot; y++)
	{
		int i = y * windowWidth + x;
		pixels[i] = Color;
	}
}
void drawColumn(Uint32 * pixels, Uint32 Color, int column, float Height)
{
	Height = fclamp(Height, 0, 1);
	int space = Height * windowHeight / 2;

	int top = windowHeight / 2 - space;
	int bot = windowHeight / 2 + space;
	drawColumn(pixels, Color, column, top, bot);
}

void DrawBoxes(Surface*Screen, vector<AABB> boxes, Vector2d origin, Vector2d orientation, Uint32 Color)
{
	Vector2d newOrigin = origin;
	//Uint32 WallColor = Color;
	Vector2d rayOrientation;
	Vector2d voffset = orientation;
	voffset.rotate(3.1416 / 2);
	for (int i = 0; i < windowWidth; i++)
	{
		//newOrigin = origin;

		rayOrientation = orientation;

		float offset = -1 + i / float(windowWidth / 2);
		
		//offset *= 10;

		newOrigin = origin + orientation;

		newOrigin = newOrigin+ voffset * offset*0.5;

		rayOrientation = newOrigin - origin;
		//cout << voffset.x << "-voffset.x" << voffset.y << "-origin.y" << endl;
		
		//cout << newOrigin.x << "-origin.x" << newOrigin.y << "-origin.y" << endl;
		//newOrientation.rotate(offset*3.1416/4  );

		float mindist = 9999999;
		//cout << "orientation x=" << orientation
		for (auto box : boxes)
		{
			HitResult hit = lineIntersectionBox(newOrigin, newOrigin + rayOrientation * 100, box);
			if (hit.HitLocation.x != 0 || hit.HitLocation.y != 0)
			{
				float dist = VSize(hit.HitLocation - newOrigin);
				
				if (dist < mindist)
				{
					mindist = dist;
				}
			}

		}
		//Uint32 WallColor = SDL_MapRGBA(pxformat, (0.5 / mindist) * 250, (0.5 / mindist) * 250, (0.5 / mindist) * 250, 255);
		SDL_Color WallColor;
		WallColor.r = (0.5 / mindist) * 250;
		WallColor.g = (0.5 / mindist) * 250;
		WallColor.b = (0.5 / mindist) * 250;
		WallColor.a = 255;
		Screen->DrawColumn(WallColor, i, 0.5 / mindist);
		//cout << mindist << "-dist" << endl;

	}
}

void updateTexture(Surface * Screen)
{

	SDL_Color CeilingColor;
	CeilingColor.r = 255;
	CeilingColor.g = 0;
	CeilingColor.b = 0;
	CeilingColor.a = 255;
	SDL_Color FloorColor;
	FloorColor.r = 0;
	FloorColor.g = 0;
	FloorColor.b = 150;
	FloorColor.a = 255;


	Screen->DrawRectangle(FloorColor, 0, Screen->GetHeight() / 2, 0, Screen->GetWidth() - 1);
	Screen->DrawRectangle(CeilingColor, Screen->GetHeight() / 2, Screen->GetHeight() - 1, 0, Screen->GetWidth() - 1);

}


int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow("SDL2 Pixel Drawing",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, 0);

	

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_Texture * texture = SDL_CreateTexture(renderer,
	//	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, windowWidth, windowHeight);

	//Uint32 * pixels = new Uint32[windowWidth * windowHeight];
	//SDL_PixelFormat * format = SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888);
	//pxformat = format;

	Surface Screen;
	Screen.CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, windowWidth, windowHeight);

	Viewpoint view;
	view.orientation = Vector2d(1, 0);
	view.origin = Vector2d(0, 0);

	vector<AABB> boxes;
	/*AABB box;
	box.Center = Vector2d(2, 0);
	box.Size = Vector2d(1, 1);
	boxes.push_back(box);

	AABB box2;
	box2.Center = Vector2d(5, -1);
	box2.Size = Vector2d(1, 1);
	boxes.push_back(box2);

	AABB box23;
	box23.Center = Vector2d(1, -3);
	box23.Size = Vector2d(1, 1);
	boxes.push_back(box23);*/

	for (int i = 0; i < 30; i++)
	{
		float xpos = rand() % 20;
		float ypos = rand() % 20 - 10;

		AABB newbox;
		newbox.Center = Vector2d(xpos, ypos);
		newbox.Size = Vector2d(1, 1);
		boxes.push_back(newbox);
	}


	

	while (!quit)
	{

		updateTexture(&Screen);

		//Uint32 WallColor = SDL_MapRGBA(format, 255, 150, 150, 255);
		DrawBoxes(&Screen, boxes,view.origin, view.orientation, 0);
		cout << "char is at" << view.origin.x << "x - " << view.origin.y << " y " << endl;

		Screen.UpdateTexture();
		//SDL_UpdateTexture(texture, NULL, pixels, windowWidth * sizeof(Uint32));
		while (SDL_PollEvent(&event)) {

			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_a)
				{
					view.origin.y -= 0.2;
				}
				else if (event.key.keysym.sym == SDLK_d)
				{
					view.origin.y += 0.2;
				}
				if (event.key.keysym.sym == SDLK_w)
				{
					view.origin.x += 0.2;
				}
				else if (event.key.keysym.sym == SDLK_s)
				{
					view.origin.x -= 0.2;
				}
				if (event.key.keysym.sym == SDLK_q)
				{
					view.orientation.rotate(3.14 / 10);
				}
				else if (event.key.keysym.sym == SDLK_e)
				{
					view.orientation.rotate(-3.14 / 10);
				}
			}
		}
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Screen.GetTexture(), NULL, NULL);
		SDL_RenderPresent(renderer);

	}

	
	//delete format;
	//SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	
	//delete[] pixels;
	SDL_Quit();

	return 0;
}