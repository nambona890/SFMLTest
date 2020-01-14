#include "muncher.h"

Muncher::Muncher(const sf::Texture* muncherImage, const sf::Color* initColor)
{
	muncherSprite.setTexture(*muncherImage);
	muncherSprite.setColor(*initColor);
	size = randf3(1.5f, 6.0f);
	angle = randf2(TAU);
	bounds = size*((muncherImage->getSize().x + muncherImage->getSize().y) / 4);
	position = {randf3(bounds,SCREENWIDTH-bounds),randf3(bounds,SCREENHEIGHT-bounds)};
	speed = randf3(100.0f, 300.0f);
}

void Muncher::UpdateMuncher(const float dt)
{
	MoveMuncher(dt);
	TransformMuncher();
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




ControlableMuncher::ControlableMuncher(const sf::Texture* muncherImage, const sf::Color* initColor) : Muncher(muncherImage, initColor)
{

}

void ControlableMuncher::UpdateMuncher(const float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		angle = modulo(angle - (PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		angle = modulo(angle + (PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		size = clamp(float(size + (3 * dt)), 1.5f, 6.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		size = clamp(float(size - (3 * dt)), 1.5f, 6.0f);
	bounds = size * ((muncherSprite.getLocalBounds().width + muncherSprite.getLocalBounds().height) / 4);
	Muncher::MoveMuncher(dt);
	Muncher::TransformMuncher();
}

sf::Sprite ControlableMuncher::GetMuncherSprite()
{
	return muncherSprite;
}

void ControlableMuncher::SetMuncherTexture(const sf::Texture* muncherImage)
{
	muncherSprite.setTexture(*muncherImage);
}