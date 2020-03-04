#pragma once
#include "common.h"
#include "muncher.h"
#include "scene.h"

	

class MuncherScene : public Scene
{
private:
	sf::Texture muncherTex[2];
	std::vector<Muncher> munchers;
	ControlableMuncher controlMuncher;
	float munchTime;
	int munchIndex = 0;
public:
	MuncherScene();
	void Main(const float dt, sf::RenderTexture& renderTexture);
};