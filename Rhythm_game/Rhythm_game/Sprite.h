#pragma once
#include "Array.h"

class Texture;

class Sprite
{
private:

	Array<Texture*>* _textureFrame;
	int _frameMaxCount;
	int _frame;
	int _frameDur;
	int _aniSpeed;
	int _x;
	int _y;

	bool _isLoop;
	bool _isPlay;
	
public:
	Sprite(const char* fileName, bool isLoop);
	~Sprite();

	void Render();
	void Update(int deltaTime);
	void SetPosition(int x, int y);
	void Play();
};