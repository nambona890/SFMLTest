#pragma once
#include "common.h"
#include "scene.h"
#include <complex>
#include "imgui.h"

class MandelbrotScene : public Scene
{
private:
	sf::Image set;
	const double xLBound = -2.0;
	const double xUBound = 1.0;
	const double yLBound = -1.2;
	const double yUBound = 1.2;
	int iterations = 128;
	
public:
	MandelbrotScene();
	void Main(const float dt, sf::RenderTexture* renderTexture);
private:
	void GenerateSet();
};