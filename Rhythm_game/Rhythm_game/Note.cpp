#include <stdio.h>

#include "Note.h"
#include "GameSystem.h"
#include "Sprite.h"

Note::Note(float startSec, int judgeDeltaLine)
{
	_sprite = 0;
	_startTick = GameSystem::GetInstance()->GetPlayTime() - (int)(startSec * 1000.0f);
	_judgeDeltaLine = judgeDeltaLine;
	_isPass = false;
}

Note::~Note()
{
	Deinit();
}

void Note::Init()
{
	_sprite = new Sprite("SpriteDATA.csv", true);
	
	int gameTimeTick = GameSystem::GetInstance()->GetPlayTime();

	_updateDuration = 0;
	_updateDuration = _startTick;

	UpdatePosition(0);

	_sprite->SetPosition(_x, _y);
	_isLive = true;
}

void Note::Deinit()
{
	if (NULL != _sprite)
	{
		delete _sprite;
		_sprite = 0;
	}
}

void Note::Update(int deltaTime)
{
	_sprite->Update(deltaTime);

	UpdatePosition(deltaTime);
	
	_sprite->SetPosition(_x, _y);
}

void Note::Render()
{
	_sprite->Render();
}

void Note::UpdatePosition(int deltaTime)
{
	_updateDuration += deltaTime;
	if (_updateDuration <= GameSystem::GameSystem::GetInstance()->GetPlayTime() + 100)
	{
		int gameTimeTick = GameSystem::GetInstance()->GetPlayTime();
		int trackHeight = GameSystem::GetInstance()->GetTrackHeight();
		float positionRate = (float)_updateDuration / (float)gameTimeTick;
		float positionInSec = trackHeight * positionRate;

		_y = positionInSec - (trackHeight - GameSystem::GetInstance()->GetHeight() + _judgeDeltaLine);
	}
	else
	{
		_isLive = false;
	}
}

bool Note::IsLive()
{
	return _isLive;
}

int Note::GetNoteTime()
{
	return _updateDuration;
}

bool Note::IsPass()
{
	return _isPass;
}

void Note::Pass()
{
	_isPass = true;
}

void Note::SetPosition(int x)
{
	_x = x;
}