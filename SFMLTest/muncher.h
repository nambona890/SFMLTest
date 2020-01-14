#pragma once
#include "common.h"

class Muncher
{
public:
	Muncher(const sf::Texture* muncherImage, const sf::Color* initColor);
	void UpdateMuncher(const float dt);
protected:
	void TransformMuncher();
	void MoveMuncher(const float dt);

public:
	sf::Sprite muncherSprite;
protected:
	float angle;
	Vec2f position;
	float size;
	float bounds;
	float speed;
};

class ControlableMuncher : Muncher
{
public:
	ControlableMuncher(const sf::Texture* muncherImage, const sf::Color* initColor);
	void UpdateMuncher(const float dt);
	sf::Sprite GetMuncherSprite();
	void SetMuncherTexture(const sf::Texture* muncherImage);
};