#pragma once
#include "common.h"

class Scene
{
public:
	Scene();
	virtual void Main(const float dt, sf::RenderTexture* renderTexture);
};