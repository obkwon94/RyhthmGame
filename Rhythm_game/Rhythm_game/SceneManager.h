#pragma once

struct Scene;
enum eScene
{
	SCENE_TITLE,
	SCENE_GAME
};
class SceneManager
{

private:
	static SceneManager* _instance;

public:
	static SceneManager* GetInstance();

private:
	Scene* _scene;
	eScene  _sceneType;
public:
	void ChangeScene(const char* sceneName);
	void KeyUp(int keyCode);
	void KeyDown(int keyCode);
	void Update(int deltaTime);
	void Render();
private:
	SceneManager();
public:
	~SceneManager();

};