#pragma once
#include "common.h"
#include "scene.h"
#include "imgui.h"

class RaycastScene : public Scene
{
private:
	sf::Image frameBuffer;
	Vec2f pos = { 0.0f,0.0f };
	float angle = -PI;
	float fov = PI / 4.0f;
	Vec2f offset;
	const Vec2f vertices[4] = {
		{-128.0f,-128.0f},
		{150.0f,-150.0f},
		{128.0f,128.0f},
		{-128.0f,128.0f},
	};
	struct Line
	{
		unsigned int v1;
		unsigned int v2;
		sf::Color col;
	};
	const Line lines[4]
	{
		{0,1,sf::Color::Red},
		{1,2,sf::Color::Green},
		{2,3,sf::Color::Blue},
		{3,0,sf::Color::Magenta}
	};
	float height = 48.0f;
	static constexpr float check = 0.5f;
	sf::Image nodes;
	static constexpr float mapSize = 2048;
public:
	RaycastScene();
	void Main(const float dt, sf::RenderTexture& renderTexture);
};