#include <stdio.h>
#include <string.h>

#include "Sprite.h"
#include "DLinkedList.h"
#include "GameSystem.h"
#include "Texture.h"


Sprite::Sprite(const char* fileName, bool isLoop)
{
	DLinkedList<Texture*> linkedList;
	
	char filePath[256];
	sprintf(filePath, "../Resources/%s", fileName);
	FILE* fp = fopen(filePath, "r");
	if (NULL == fp)
		printf("Can't Load %s\n", fileName);

	char* textureName;
	float scaleWidth;
	float scaleHeight;

	char buffer[1024];
	char* record = fgets(buffer, sizeof(buffer), fp);
	while (true)
	{
		record = fgets(buffer, sizeof(buffer), fp);
		if (NULL == record)
			break;

		{
			char* token = strtok(record, ",");
			textureName = token;

			token = strtok(NULL, ",");
			scaleWidth = atof(token);

			token = strtok(NULL, ",");
			scaleHeight = atof(token);

			Texture* texture = new Texture(textureName);
			texture->SetScale(scaleWidth, scaleHeight);

			linkedList.Append(texture);
		}
	}
	fclose(fp);


	_frame = 0;
	_frameMaxCount = linkedList._count;
	_aniSpeed = 500 / _frameMaxCount;
	_frameDur = 0;

	_textureFrame = new Array<Texture*>(_frameMaxCount);
	
	int frame = 0;
	DLinkedListIterator<Texture*> itr = linkedList.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Forth())
	{
		Texture* texture = itr.Item();
		_textureFrame->Set(frame, texture);
		frame++;
	}

	_isLoop = isLoop;
	if (true == _isLoop)
		_isPlay = true;

	else
		_isPlay = false;
}

Sprite::~Sprite()
{

}

void Sprite::Render()
{
	if (false == _isPlay)
		return;

	_textureFrame->Get(_frame)->Render();
}

void Sprite::Update(int deltaTime)
{
	if (false == _isPlay)
		return;

	_frameDur += deltaTime;
	if (_aniSpeed < _frameDur)
	{
		_frameDur = 0;
		_frame = (_frame + 1) % _frameMaxCount;

		if (false == _isLoop)
		{
			if (0 == _frame)
				_isPlay = false;
		}
	}
	Texture* texture = _textureFrame->Get(_frame);
	texture->SetPosition(_x, _y);
}
void Sprite::SetPosition(int x, int y)
{
	_x = x;
	_y = y;
	Texture* texture = _textureFrame->Get(_frame);
	texture->SetPosition(_x, _y);
}
	
void Sprite::Play()
{
	_frame = 0;
	_isPlay = true;
}