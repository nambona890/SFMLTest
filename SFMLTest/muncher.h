#pragma once
#include "common.h"

class Muncher {
public:
	Muncher(const sf::Texture* muncherImage);
	void UpdateMuncher(const float dt);
private:
	void TransformMuncher();
	void MoveMuncher(const float dt);

public:
	sf::Sprite muncherSprite;
private:
	float angle;
	Vec2f position;
	float size;
	float bounds;
	float speed;
};