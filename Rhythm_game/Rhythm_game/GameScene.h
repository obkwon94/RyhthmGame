#pragma once
#include "Scene.h"

class Track;
class Sprite;

class Font;

class GameScene : public Scene
{
private:
	Sprite* _backgroundSprite;
	Track* _track1;
	Track* _track2;
	Track* _track3;
	Track* _track4;
	int _gameDuration;
	//SDL_Texture* _textTexture;
	
public:

	GameScene();
	~GameScene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
};