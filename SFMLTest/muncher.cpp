#include "muncher.h"

Muncher::Muncher(const sf::Texture* muncherImage)
{
	muncherSprite.setTexture(*muncherImage);
	size = randf3(1.5f, 6.0f);
	angle = randf2(TAU);
	bounds = size*((muncherImage->getSize().x + muncherImage->getSize().y) / 4);
	position = {randf3(bounds,SCREENWIDTH-bounds),randf3(bounds,SCREENHEIGHT-bounds)};
	speed = randf3(100.0f, 300.0f);
}

void Muncher::UpdateMuncher(const float dt)
{
	TransformMuncher();
	MoveMuncher(dt);
}

void Muncher::TransformMuncher()
{
	Vec2f mSize = { (float)muncherSprite.getTexture()->getSize().x, (float)muncherSprite.getTexture()->getSize().y };
	muncherSprite.setOrigin(mSize * 0.5f);
	muncherSprite.setScale(size, size);
	muncherSprite.setRotation(RADTODEG(angle));
	muncherSprite.setPosition(position);
}

void Muncher::MoveMuncher(const float dt)
{
	float dspeed = dt * speed;
	angle = modulo(angle, TAU);
	position += {sinf(-angle + PI)* dspeed, cosf(-angle + PI)* dspeed};

	if (position.x > SCREENWIDTH - bounds)
	{
		if (angle > 0.0f && angle < PI)
			angle = BounceAngle(angle, PI * 1.5f);
		position.x = SCREENWIDTH - bounds;
	}
	if (position.x < bounds)
	{
		if (angle < TAU && angle > PI)
			angle = BounceAngle(angle, PI * 0.5f);
		position.x = bounds;
	}

	if (position.y > SCREENHEIGHT - bounds)
	{
		if (angle > PI * 0.5f && angle < PI * 1.5f)
			angle = BounceAngle(angle, 0);
		position.y = SCREENHEIGHT - bounds;
	}
	if (position.y < bounds)
	{
		if (angle < PI * 0.5f || angle > PI * 1.5f)
			angle = BounceAngle(angle, PI);
		position.y = bounds;
	}
}