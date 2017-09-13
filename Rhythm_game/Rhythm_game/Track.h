#pragma once
#include "DLinkedList.h"
#include "GameObject.h"
#include "Array.h"

class Note;
class Sprite;
class Font;

enum eJudge
{
	NONE,
	PERFECT,
	NEAR,
	BREAK
};

class Track : public GameObject
{
public:
	enum eEffect
	{
		EXPLOSION
	};

private:
	/*	
	Sprite* _trackBackground;
	Sprite* _judgeLine;
	*/
	
	DLinkedList<Sprite*> _backgroundSpriteList;
	DLinkedList<Note*> _noteList;
	Array<Sprite*>* _effectList;
	
	//Sprite* _noteEffect;
	
	bool _isKeyDown;
	eJudge _judge;

	int _judgeTick;
	int _judgeStartTick;
	int _judgeEndTick;
	
public:
	Track();
	~Track();
	void Init();
	void Init(int TrackNumber);
	void Deinit();
	void Update(int deltaTime);
	void Render();

	//input
	void keyDown();
	void keyUp();

	Font* _textFont;
	
};