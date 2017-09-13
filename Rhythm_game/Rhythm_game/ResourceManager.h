#pragma once
#include<iostream>
#include<map>
#include<string>

#include "SDL.h"
#include "SDL_image.h"

class ResourceManager
{
	//SingleTon
private:
	static ResourceManager* _instance;
public:
	static ResourceManager* GetInstance();

	//FindTexture
private:
	std::map<std::string, SDL_Texture*> _textureMap;
public:
	SDL_Texture* FindTexture(std::string filePath);

	//ResourceManager
private:
	ResourceManager();
public:
	~ResourceManager();
};