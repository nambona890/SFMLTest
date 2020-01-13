#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>

typedef sf::Vector2f Vec2f;

template <typename T>
sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	T X = left.x * right.x;
	T Y = left.y * right.y;
	return sf::Vector2<T>(X, Y);
}

void TransformMuncher(sf::Sprite* muncherSprite, const float angle, const Vec2f position, const float size);

void MoveMuncher(sf::Sprite* muncherSprite, float* angle, Vec2f* position, const float size, const float dt);

float BounceAngle(const float angle, const float normal);