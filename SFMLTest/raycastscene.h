#pragma once
#include "common.h"
#include "scene.h"
#include "imgui.h"

class RaycastScene : public Scene
{
private:
	sf::Image frameBuffer;
	Vec2f pos = { 5.5f,9.5f };
	float angle = -PI;
	float fov = PI / 4.0f;
	char* map = new char[mapWidth*mapHeight + 1] {
		"111111111111"
		"100000000001"
		"100000000001"
		"100000000001"
		"100000000001"
		"100002200001"
		"100002200001"
		"100000000001"
		"100000000001"
		"100000000001"
		"100000000001"
		"111111111111"
	};
	float height = 48.0f;
	static constexpr float check = 0.01f;
	static constexpr unsigned int mapWidth = 12u;
	static constexpr unsigned int mapHeight = 12u;
public:
	RaycastScene();
	void Main(const float dt, sf::RenderTexture& renderTexture);
};