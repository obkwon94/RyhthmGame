#pragma once


struct SDL_Renderer;

class GameSystem
{
	// SingleTon
private:
	static GameSystem* _instance;
	
public:
	static GameSystem* GetInstance();

	// WindowInfo
public:
	int GetWidth();
	int GetHeight();
	void Quit();

	// GameInfo
private:
	int _trackHeight;
	int _playTimeTick;

public:
	void SetPlayTime(float sec);
	int GetPlayTime();
	void SetTrackHeight(int height);
	int GetTrackHeight();

	// SDL
private:
	SDL_Renderer* _renderer;

public:
	void SetRenderer(SDL_Renderer* renderer);
	SDL_Renderer* GetRenderer();
	// GameSystem
private:
	GameSystem();
public:
	~GameSystem();
};