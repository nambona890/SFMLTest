#pragma once
#include "common.h"

class Scene
{
public:
	Scene();
	void Main(const float dt, sf::RenderTexture* renderTexture);
};