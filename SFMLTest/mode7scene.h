#pragma once
#include "common.h"
#include "scene.h"
#include "imgui.h"



class Mode7Scene : public Scene
{
private:
	sf::Image* planeImg = new sf::Image;
	Vec2f pos = { 0.0f,0.0f };
	float angle = 0.0f;
	int centerY = -60;
	float scaleFactor = 0.3f;
public:
	Mode7Scene();
	void Main(const float dt, sf::RenderTexture* renderTexture);
};