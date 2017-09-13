#pragma once
#include "Texture.h"

class Font : public Texture
{
private:
	TTF_Font* _sansFont;

public:
	Font(const char* fileName, int fontSize);
	~Font();

	void SetText(const char* text);
};