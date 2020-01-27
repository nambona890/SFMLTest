#pragma once
#include "common.h"
#include "scene.h"

class RaycastScene : public Scene
{
private:
	struct Linedef
	{
		unsigned int v1;
		unsigned int v2;
		sf::Color color;
	};
	const float speed = 64;
	const float playerHeight = 48;
	const float wallHeight = 128;
	const float fov = DEGTORAD(90);
	Vec2f pos = { 0,0 };
	std::vector<Vec2f> verts;
	std::vector<Linedef> lines;
	float angle = 0;
	const float near = 0.2f;
	const float far = 2000.0f;
public:
	RaycastScene();
	void Main(const float dt, sf::RenderTexture* renderTexture);
private:

};