#include <stdlib.h>

#include "GameSystem.h"

#include "Track.h"
#include "Note.h"
#include "Sprite.h"


Track::Track()
{
	_isKeyDown = false;
	_judge = eJudge::NONE;
}
Track::~Track()
{

}
void Track::Init()
{

}

void Track::Init(int TrackNumber)
{
	int judgeDeltaLine = 100;
	int Width = GameSystem::GetInstance()->GetWidth() / 2;
	int trackHeight = GameSystem::GameSystem::GetInstance()->GetHeight() / 2;
	int judgeHeight = GameSystem::GetInstance()->GetHeight() - judgeDeltaLine;

	if (TrackNumber == 1)
	{
		Width = Width - 90;
	}
	if (TrackNumber == 2)
	{
		Width = Width - 30;
	}
	if (TrackNumber == 3)
	{
		Width = Width + 30;
	}
	if (TrackNumber == 4)
	{
		Width = Width + 90;
	}
		

	Sprite* trackBackground = new Sprite("trackBackground.csv ", true);
	trackBackground->SetPosition(Width, trackHeight);
	_backgroundSpriteList.Append(trackBackground);
			
	Sprite* judgeLine = new Sprite("JudgeLine.csv ", true);
	judgeLine->SetPosition(Width, judgeHeight);
	_backgroundSpriteList.Append(judgeLine);

	Sprite* noteEffect = new Sprite("noteEffect.csv ", false);
	noteEffect->SetPosition(Width, judgeHeight);

	_effectList = new Array<Sprite*>(1);
	_effectList->Set(eEffect::EXPLOSION, noteEffect);

	int gameTime = GameSystem::GetInstance()->GetPlayTime();
	int deltaTick = 0;
	for (int noteTick = 0; noteTick < gameTime;)
	{
		int randValue = rand() % 3;
		switch (randValue)
		{
		case 0:
			deltaTick = 250;
			break;
		case 1:
			deltaTick = 500;
			break;
		case 2:
			deltaTick = 750;
			break;
		default:
			deltaTick = 1000;
			break;
		}

		noteTick += deltaTick;
		float sec = (float)noteTick / 1000.0f;

		Note* note = new Note(sec, judgeDeltaLine);
		note->SetPosition(Width);
		note->Init();
		_noteList.Append(note);
	}
}

void Track::Deinit()

{
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->Deinit();
		delete itr.Item();
		_noteList.Remove(itr);
	}
	
	DLinkedListIterator<Sprite*> backItr = _backgroundSpriteList.GetIterator();
	for (backItr.Start(); backItr.Valid(); backItr.Forth())
	{
		if (NULL != backItr.Item())
		{
			delete backItr.Item();
		}
		_backgroundSpriteList.Remove(backItr);
	}
	
	if (NULL != _effectList)
	{
		for (int i = 0; i < _effectList->getSize(); i++)
		{
			delete _effectList->Get(i);
		}
		_effectList = NULL;
	}
}

void Track::Update(int deltaTime)
{
	DLinkedListIterator<Sprite*> backItr = _backgroundSpriteList.GetIterator();
	for (backItr.Start(); backItr.Valid(); backItr.Forth())
	{
		backItr.Item()->Update(deltaTime);
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->IsLive())
		{
			itr.Item()->Update(deltaTime);
		}
		else
		{
			delete itr.Item();
			_noteList.Remove(itr);
		}

		_judgeTick = GameSystem::GetInstance()->GetPlayTime();
		_judgeStartTick = _judgeTick - 200;
		_judgeEndTick = _judgeTick + 200;

		if (_judgeEndTick < itr.Item()->GetNoteTime() && false == itr.Item()->IsPass())
		{
			
			itr.Item()->Pass();
			_judge = eJudge::BREAK;
		
			delete itr.Item();
			_noteList.Remove(itr);
		}
	}
	
	for (int i = 0; i < _effectList->getSize(); i++)
	{
		_effectList->Get(i)->Update(deltaTime);
	}
}

void Track::Render()
{
	DLinkedListIterator<Sprite*> backItr = _backgroundSpriteList.GetIterator();
	for (backItr.Start(); backItr.Valid(); backItr.Forth())
	{
		backItr.Item()->Render();
	}

	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		itr.Item()->Render();
	}

	for (int i = 0; i < _effectList->getSize(); i++)
	{
		_effectList->Get(i)->Render();
	}
}

void Track::keyDown()
{
	if (_isKeyDown)
		return;
	_isKeyDown = true;
	
	DLinkedListIterator<Note*> itr = _noteList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		if (itr.Item()->GetNoteTime() < _judgeStartTick)
		{
			_judge = eJudge::NONE;
			break;
		}

		if (_judgeStartTick <= itr.Item()->GetNoteTime() && itr.Item()->GetNoteTime() <= _judgeEndTick)
		{
			if (_judgeStartTick + 170 <= itr.Item()->GetNoteTime() && itr.Item()->GetNoteTime() <= _judgeEndTick - 170)
			{
				_judge = eJudge::PERFECT;
				break;
			}
			else
			{
				_judge = eJudge::NEAR;
				break;
			}
			
		}
	}

	switch (_judge)
	{
	case eJudge::PERFECT:
		printf("PERFECT\n");
		_effectList->Get(eEffect::EXPLOSION)->Play();
		_noteList.Remove(itr);
		break;
	case eJudge::NEAR:
		printf("NEAR\n");
		if (_judgeTick > itr.Item()->GetNoteTime())
		{
			printf("--ealry--\n");
		}
		else
		{
			printf("--late--\n");
		}
		_effectList->Get(eEffect::EXPLOSION)->Play();
		_noteList.Remove(itr);
		break;
	}
	
	_judge = NONE;
}

void Track::keyUp()
{
	_isKeyDown = false;
}