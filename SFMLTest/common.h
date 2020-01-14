#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctime>

#define PI 3.14159265358f
#define TAU 6.28318530718f
#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define RADTODEG(ang) ((ang)*57.2957795131)
#define randf() (float(rand())/float((RAND_MAX)))
#define randf2(R_MAX) (randf()*R_MAX)
#define randf3(R_MIN,R_MAX) (randf2(R_MAX-R_MIN)+R_MIN)
#define BounceAngle(angle,normal) fmod(((normal - angle) * 2 + angle) + PI, TAU)

typedef sf::Vector2f Vec2f;

template <typename T>
sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	T X = left.x * right.x;
	T Y = left.y * right.y;
	return sf::Vector2<T>(X, Y);
}