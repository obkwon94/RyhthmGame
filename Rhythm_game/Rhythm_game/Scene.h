#pragma once
#include "GameObject.h"

class Scene : public GameObject
{
public:
	Scene();
	~Scene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();
	virtual void KeyDown(int keyCode);
	virtual void KeyUp(int keyCode);
};