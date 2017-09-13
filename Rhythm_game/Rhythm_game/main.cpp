#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"
#include "SDL_ttf.h"
#include "GameSystem.h"
//#include "GameScene.h"
//#include "TitleScene.h"
#include "SceneManager.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);

	if (TTF_Init() < 0)
		printf("Error Init SDL Font\n");
	atexit(TTF_Quit);

	int window_w = GameSystem::GetInstance()->GetWidth();
	int window_h = GameSystem::GetInstance()->GetHeight();


	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO);//텍스쳐 초기화

	SDL_Window* sdlWindow = SDL_CreateWindow
	("SDL Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_w, window_h, SDL_WINDOW_OPENGL); //윈도우 창 설정
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, 0, 0);
	GameSystem::GetInstance()->SetRenderer(sdlRenderer);
	
	/*
	GameScene* scene = new GameScene();
	scene->Init();
	*/
	SceneManager::GetInstance()->ChangeScene("Game");

	SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);

	SDL_Event sdlEvent; //이벤트 변수 추가

	int frame = 0;
	int oldFrame = 0;
	int curTick = SDL_GetTicks();
	int oldTick = curTick;

	while (1)
	{
		curTick = SDL_GetTicks();
		frame = (SDL_GetTicks() % 1000) * 60;
		frame /= 1000;

		if (oldFrame != frame)
		{
			oldFrame = frame;
			int deltaTime = curTick - oldTick;
			oldTick = curTick;

			if (SDL_PollEvent(&sdlEvent))
			{
				if (SDL_QUIT == sdlEvent.type)
					break;

				if (SDL_KEYUP == sdlEvent.type)
				{
					if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
					{
						SDL_Event quitEvent;
						quitEvent.type = SDL_QUIT;
						SDL_PushEvent(&quitEvent); //큐 데이터 타입
					}
					/*
					if (sdlEvent.key.keysym.sym == SDLK_d)
					{
						scene->KeyUp(SDLK_d);
					}
					if (sdlEvent.key.keysym.sym == SDLK_f)
					{
						scene->KeyUp(SDLK_f);
					}
					if (sdlEvent.key.keysym.sym == SDLK_j)
					{
						scene->KeyUp(SDLK_j);
					}
					if (sdlEvent.key.keysym.sym == SDLK_k)
					{
						scene->KeyUp(SDLK_k);
					}
					*/
					SceneManager::GetInstance()->KeyUp(sdlEvent.key.keysym.sym);
				}

				if (SDL_KEYDOWN == sdlEvent.type)
				{
					/*
					if (sdlEvent.key.keysym.sym == SDLK_d)
					{
						scene->KeyDown(SDLK_d);
					}
					if (sdlEvent.key.keysym.sym == SDLK_f)
					{
						scene->KeyDown(SDLK_f);
					}
					if (sdlEvent.key.keysym.sym == SDLK_j)
					{
						scene->KeyDown(SDLK_j);
					}
					if (sdlEvent.key.keysym.sym == SDLK_k)
					{
						scene->KeyDown(SDLK_k);
					}
					*/
					SceneManager::GetInstance()->KeyDown(sdlEvent.key.keysym.sym);
				}
			}
			//scene->Update(deltaTime);
			SceneManager::GetInstance()->Update(deltaTime);
			
			SDL_RenderClear(sdlRenderer); //이미지 삭제
			{
				//scene->Render();
				SceneManager::GetInstance()->Render();
			}
			
			SDL_RenderPresent(sdlRenderer);
		}	
	}
	/*
	scene->Deinit();
	*/

	return 0;
}