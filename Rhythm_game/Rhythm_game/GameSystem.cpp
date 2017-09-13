#include <stdio.h>

#include "GameSystem.h"
#include "SDL.h" 

GameSystem* GameSystem::_instance = NULL;
GameSystem::GameSystem()
{
	
}

GameSystem::~GameSystem()
{

}

GameSystem* GameSystem::GetInstance()
{
	if (NULL == _instance)
		_instance = new GameSystem();
	return _instance;
}

int GameSystem::GetWidth()
{
	return 560;
}

int GameSystem::GetHeight()
{
	return 995;
}

void GameSystem::SetRenderer(SDL_Renderer* renderer)
{
	_renderer = renderer;
}

SDL_Renderer* GameSystem::GetRenderer()
{
	return _renderer;
}

void GameSystem::SetPlayTime(float sec)
{
	_playTimeTick = (int)(sec * 1000.0f);
}

int GameSystem::GetPlayTime()
{
	return _playTimeTick; //전체 플레이시간
}

void GameSystem::SetTrackHeight(int height)
{
	_trackHeight = height;
}

int GameSystem::GetTrackHeight()
{
	return _trackHeight; //트랙 길이
}

void GameSystem::Quit()
{
	SDL_Event quitEvent;
	quitEvent.type = SDL_QUIT;
	SDL_PushEvent(&quitEvent);
}