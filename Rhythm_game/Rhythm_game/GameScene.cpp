#include <stdio.h>
#include <string.h>

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "GameScene.h"
#include "GameSystem.h"
#include "Track.h"
#include "Font.h"
#include "Sprite.h"


GameScene::GameScene()
{
	_backgroundSprite = NULL;
	//_textFont = NULL;
}
GameScene::~GameScene()
{
	Deinit();
}

void GameScene::Init()
{
	char filePath[256];
	sprintf(filePath, "../Resources/%s", "gamePlay.csv");
	FILE* fp = fopen(filePath, "r");
	if (NULL == fp)
		printf("can't load %s", filePath);

	char backgroundSpriteName[256];
	char musicName[256];
	float playtimeTic;

	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		{
			char* token = strtok(record, ",\n");	//backgroundSprite\n 까지 읽히므로 \n도 포함
			if (!strcmp(token, "backGround"))
			{
				token = strtok(NULL, ",\n");
				strcpy(backgroundSpriteName, token);
			}
						
			else if (!strcmp(token, "musicName"))
			{
				token = strtok(NULL, ",\n");
				strcpy(musicName, token);
			}
						
			else if (!strcmp(token, "playTime"))
			{
				token = strtok(NULL, ",\n");
				playtimeTic = atof(token);
			}
		}
	}

	_backgroundSprite = new Sprite("backgroundSprite.csv ", true);
	_backgroundSprite->SetPosition(GameSystem::GetInstance()->GetWidth() / 2, GameSystem::GetInstance()->GetHeight() / 2);
	
	//노래 시간 설정
	int BPM = 120;
	int tempo = BPM / 60;
	int trackHeight = GameSystem::GetInstance()->GetHeight() * (playtimeTic * tempo);

	GameSystem::GetInstance()->SetPlayTime(playtimeTic);
	GameSystem::GetInstance()->SetTrackHeight(trackHeight / 2);
	
	//Track 생성
	_track1 = new Track();
	_track1->Init(1);

	_track2 = new Track();
	_track2->Init(2);

	_track3 = new Track();
	_track3->Init(3);

	_track4 = new Track();
	_track4->Init(4);

	_gameDuration = 0;

	//font
	/*_textFont = new Font("arialbd.ttf", 24);
	_textFont->SetPosition(0, 0);*/

	int result = Mix_Init(MIX_INIT_MP3);
	if (MIX_INIT_MP3 == result)
	{
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
		char musicFilePath[256];
		sprintf(musicFilePath, "../Resources/Music/%s", musicName);
		Mix_Music* music = Mix_LoadMUS(musicFilePath);
		if (NULL != music)
		{
			Mix_PlayMusic(music, 0);

		}
		else
		{
			printf("음악을 불러올 수 없습니다");
		}
	}
	else
	{
		printf("노래를 불러올 수 없습니다");
	}
}

void GameScene::Deinit()
{
	_track1->Deinit();
	_track2->Deinit();
	_track3->Deinit();
	_track4->Deinit();
	if (NULL != _backgroundSprite)
	{
		delete _backgroundSprite;
		_backgroundSprite = NULL;
	}
	//if (NULL != _textFont)
	//{
	//	delete _textFont;
	//	_textFont = NULL;
	//}
}

void GameScene::Update(int deltaTime)
{
	if (_gameDuration <= GameSystem::GetInstance()->GetPlayTime() + 3000)
	{
		_backgroundSprite->Update(deltaTime);
		_track1->Update(deltaTime);
		_track2->Update(deltaTime);
		_track3->Update(deltaTime);
		_track4->Update(deltaTime);

		_gameDuration += deltaTime;
	}
	else
	{
		GameSystem::GetInstance()->Quit();
	}
}

void GameScene::Render()
{
	_backgroundSprite->Render();
	_track1->Render();
	_track2->Render();
	_track3->Render();
	_track4->Render();
//	_textFont->Render();
}

void GameScene::KeyDown(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_d:
		_track1->keyDown();
		break;
	case SDLK_f:
		_track2->keyDown();
		break;
	case SDLK_j:
		_track3->keyDown();
		break;
	case SDLK_k:
		_track4->keyDown();
		break;
	}
}

void GameScene::KeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_d:
		_track1->keyUp();
		break;
	case SDLK_f:
		_track2->keyUp();
		break;
	case SDLK_j:
		_track3->keyUp();
		break;
	case SDLK_k:
		_track4->keyUp();
		break;
	}
}