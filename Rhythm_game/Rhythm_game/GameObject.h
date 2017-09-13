#pragma once

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Init() = 0;
	virtual void Update(int deltaTime) = 0;
	virtual void Render() = 0;
	virtual void Deinit() = 0;
};