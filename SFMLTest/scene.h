#pragma once
#include "common.h"

class Scene
{
public:
	Scene()
	{

	}
	virtual ~Scene() = default;
	virtual void Main(const float dt, sf::RenderTexture& renderTexture)
	{

	}
	virtual void Main(const float dt)
	{

	}
	static const bool opengl = false;
};