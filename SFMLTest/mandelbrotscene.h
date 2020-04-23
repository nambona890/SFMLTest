#pragma once
#include "common.h"
#include "scene.h"
#include <complex>
#include "imgui.h"

class MandelbrotScene : public Scene
{
private:
	sf::Image set;
	int iterations = 128;
	float genTime = 0;
	bool parallel = true;
public:
	static constexpr double xLBound = -2.0;
	static constexpr double xUBound = 1.0;
	static constexpr double yLBound = -1.2;
	static constexpr double yUBound = 1.2;
	MandelbrotScene();
	void Main(const float dt, sf::RenderTexture& renderTexture);
private:
	void GenerateSet();
	class GenClass;
};