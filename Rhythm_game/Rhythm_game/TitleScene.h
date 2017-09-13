#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Update(int deltaTime);
	void Render();
	void Deinit();
};