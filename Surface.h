#pragma once
#include <SDL.h>

//class to hold an array of pixels and easy functions for it
class Surface
{

public:
	
	Surface(); 
	~Surface();
	//create a texture and all the inital values
	SDL_Texture* CreateTexture(SDL_Renderer* renderer, Uint32 PxFormat, unsigned int NewWidth, unsigned int NewHeight);

	void DrawColumn(SDL_Color Color, int Column, float DrawHeight);

	void DrawRectangle(SDL_Color Color, int Top, int Bot, int Left, int Right);

	void UpdateTexture();

	SDL_Texture* GetTexture() const;
	SDL_PixelFormat* GetPixelFormat() const;
	unsigned int GetWidth() const;
	unsigned int GetHeight() const;
private:

	SDL_Texture * Texture;
	SDL_PixelFormat * PixelFormat;

	unsigned int Width;
	unsigned int Height;

	Uint32 * PixelArray;
};


