#pragma once
#include "SDL_image.h"

class Texture
{
protected:
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;
	
public:
	Texture();
	Texture(const char* filename);
	~Texture();

	void SetScale(float width, float height);
	void SetPosition(int x, int y);
	void Render();
	int GetRenderWidth();
	int GetRenderHeight();
};