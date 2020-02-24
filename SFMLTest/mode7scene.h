#pragma once
#include "common.h"
#include "scene.h"
#include "imgui.h"



class Mode7Scene : public Scene
{
private:
	sf::Image* planeImg = new sf::Image;
	Vec2f pos = { 0.0f,0.0f };
	double angle = 0;
	int centerY = 10;
	float scaleFactor = 1.0f;
public:
	Mode7Scene();
	void Main(const float dt, sf::RenderTexture* renderTexture);
};