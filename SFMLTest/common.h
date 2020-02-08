#pragma once
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <ctime>

#define PI 3.14159265358f
#define TAU 6.28318530718f
#define SCREENWIDTH 1024
#define SCREENHEIGHT 768
#define RADTODEG(ang) ((ang)*57.2957795131f)
#define DEGTORAD(ang) ((ang)/57.2957795131f)
#define randf() (float(rand())/float((RAND_MAX)))
#define randf2(R_MAX) (float(rand())/float(RAND_MAX/R_MAX))
#define randf3(R_MIN,R_MAX) (R_MIN+(float(rand())/float(RAND_MAX/(R_MAX-R_MIN))))
#define BounceAngle(angle,normal) modulo(((normal - angle) * 2 + angle) + PI, TAU)

static unsigned int gamemode = 0;

enum : unsigned int
{
	MODE_MUNCHER,
	MODE_RAYCAST
};

typedef sf::Vector2f Vec2f;

template <typename T>
sf::Vector2<T> operator *(const sf::Vector2<T>& left, const sf::Vector2<T>& right)
{
	T X = left.x * right.x;
	T Y = left.y * right.y;
	return sf::Vector2<T>(X, Y);
}

template <typename T>
T clamp(const T& n, const T& lower, const T& upper) {
	return std::max(lower, std::min(n, upper));
}

template <typename T>
T modulo(T n, T max) //why the fuck doesn't std come with a normal modulo function
{
	T ret;
	if constexpr (std::is_integral_v<T>)
		ret = n % max;
	else
		ret = std::fmod(n, max);

	if (ret < 0)
		ret += max;

	return ret;
}