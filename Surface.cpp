#include "Surface.h"
#include <cmath>
Surface::Surface() : Texture(nullptr), PixelArray(nullptr), PixelFormat(nullptr), Width(0), Height(0)
{
	
}

Surface::~Surface()
{
	SDL_DestroyTexture(Texture);
	Texture = nullptr;
	
	delete[] PixelArray;	
}

SDL_Texture* Surface::CreateTexture(SDL_Renderer* renderer, Uint32 PxFormat, unsigned int NewWidth, unsigned int NewHeight)
{
	Texture = SDL_CreateTexture(renderer,PxFormat, SDL_TEXTUREACCESS_STATIC, NewWidth, NewHeight);

	PixelArray = new Uint32[NewWidth * NewHeight];
	PixelFormat = SDL_AllocFormat(PxFormat);
	Width = NewWidth;
	Height = NewHeight;

	return Texture;

}

void Surface::DrawColumn(SDL_Color Color, int Column, float DrawHeight)
{
	
	if (DrawHeight < 0)
	{
		DrawHeight = 0;
	}
	else if (DrawHeight > 1)
	{
		DrawHeight = 1;
	}

	int space = DrawHeight* Height / 2;

	int top = Height / 2 - space;
	int bot = Height / 2 + space;

	DrawRectangle(Color, top, bot, Column, Column);
}

void Surface::DrawRectangle(SDL_Color Color, int Top, int Bot, int Left, int Right)
{
	
	if (PixelArray != nullptr&& PixelFormat != nullptr)
	{
		Uint32 PixelColor = SDL_MapRGB(PixelFormat, Color.r, Color.g, Color.b);
		for (int y = Top; y <= Bot; y++)
		{
			for (int x = Left; x <= Right; x++)
			{
				int i = y * Width + x;
				PixelArray[i] = PixelColor;
			}
		}
	}

}

SDL_Texture* Surface::GetTexture() const
{
	return Texture;
}

unsigned int Surface::GetWidth() const
{
	return Width;
}

unsigned int Surface::GetHeight() const
{
	return Height;
}

SDL_PixelFormat* Surface::GetPixelFormat() const
{
	return PixelFormat;
}

void Surface::UpdateTexture()
{
	SDL_UpdateTexture(Texture, NULL, PixelArray, Width * sizeof(Uint32));
}
