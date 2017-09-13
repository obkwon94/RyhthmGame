#include <stdio.h>

#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"

SceneManager* SceneManager::_instance = NULL;

SceneManager::SceneManager()
{
	_scene = NULL;
}
SceneManager::~SceneManager()
{
	if (NULL != _scene)
	{
		_scene->Deinit();
		delete _scene;
	}
}

SceneManager* SceneManager::GetInstance()
{
	if (NULL == _instance)
		_instance = new SceneManager();
	return _instance;
}

void SceneManager::ChangeScene(const char* sceneName)
{
	
	if (NULL != _scene)
	{
		_scene->Deinit();
		delete _scene;
	}
	if (sceneName == "Title")
		_sceneType = eScene::SCENE_TITLE;
	else if (sceneName == "Game")
		_sceneType = eScene::SCENE_GAME;
	switch (_sceneType)
	{
	case eScene::SCENE_TITLE:
		_scene = new TitleScene;
		break;
	case eScene::SCENE_GAME:
		_scene = new GameScene;
		break;
	}
	_scene->Init();
}

void SceneManager::KeyUp(int keyCode)
{
	_scene->KeyUp(keyCode);
}

void SceneManager::KeyDown(int keyCode)
{
	_scene->KeyDown(keyCode);
}

void SceneManager::Update(int deltaTime)
{
	_scene->Update(deltaTime);
}

void SceneManager::Render()
{
	_scene->Render();
}
