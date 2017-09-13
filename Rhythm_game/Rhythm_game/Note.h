#pragma once
#include"GameObject.h"

class Sprite;

class Note : public GameObject
{
private:
	Sprite* _sprite;
	
	int _x;
	int _y;
	int _updateDuration;
	int _startTick;
	int _judgeDeltaLine;

	bool _isLive;
	bool _isPass;
public:
	Note(float startSec, int judgeDeltaLine);
	~Note();

	void Init();
	void Deinit();
	void Update(int deltaTime);
	void Render();
	void UpdatePosition(int deltaTime);
	void SetPosition(int x);
	void Pass();

	bool IsLive();
	bool IsPass();

	int GetNoteTime();
	
};