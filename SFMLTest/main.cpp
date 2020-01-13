#include "main.h"

#define PI 3.14159265358f
#define TAU 6.28318530718f
#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define RADTODEG(ang) ((ang)*57.2957795131)

int main()
{
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ur mom");
	sf::Texture muncher[2];
	muncher[0].loadFromFile("munch1.png");
	muncher[1].loadFromFile("munch2.png");
	sf::Clock dc;
	sf::Sprite muncherSprite;
	muncherSprite.setTexture(muncher[0]);
	float dt = 0,angle = 0,time = 0.6;
	Vec2f muncherPosition = { SCREENWIDTH/2,SCREENHEIGHT/2 };
	float muncherSize = 6.0f;
	int munindex = 0;
	while (window.isOpen())
	{
		time += dt;
		if (time > 0.15)
		{
			muncherSprite.setTexture(muncher[munindex]);
			if (++munindex > 1)
			{
				munindex = 0;
			}
			time = 0.0f;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			angle -= dt * PI;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			angle += dt * PI;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (muncherSize < 12.0f)
			{
				muncherSize += dt * 10.0f;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (muncherSize > 0.5f)
			{
				muncherSize -= dt * 10.0f;
			}
		}
		if (muncherSize < 0.5f)
			muncherSize = 0.5f;
		else if (muncherSize > 12.0f)
			muncherSize = 12.0f;
		if (angle < 0)
			angle += TAU;
		else if (angle > TAU)
			angle -= TAU;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}
		window.clear(sf::Color{0,128,128});
		TransformMuncher(&muncherSprite, angle, muncherPosition, muncherSize);
		MoveMuncher(&muncherSprite, &angle, &muncherPosition, muncherSize, dt);
		window.draw(muncherSprite);
		window.display();
		dt = dc.restart().asSeconds();
	}
}

void TransformMuncher(sf::Sprite* muncherSprite, const float angle, const Vec2f position, const float size)
{
	Vec2f mSize = { (float)muncherSprite->getTexture()->getSize().x, (float)muncherSprite->getTexture()->getSize().y };
	muncherSprite->setOrigin(mSize * 0.5f);
	muncherSprite->setScale(size, size);
	muncherSprite->setRotation(RADTODEG(angle));
	muncherSprite->setPosition(position);
}

void MoveMuncher(sf::Sprite* muncherSprite, float* angle, Vec2f* position, const float size, const float dt)
{
	float speed = dt * 200;
	float radius = size * ((muncherSprite->getTexture()->getSize().x + muncherSprite->getTexture()->getSize().y) / 4);
	*position += {sinf(-*angle + PI)* speed, cosf(-*angle + PI)* speed};

	if (position->x > SCREENWIDTH - radius)
	{
		if (*angle > 0.0f && *angle < PI)
			*angle = BounceAngle(*angle, PI * 1.5f);
		position->x = SCREENWIDTH - radius;
	}
	if (position->x < radius)
	{
		if (*angle < TAU && *angle > PI)
			*angle = BounceAngle(*angle, PI * 0.5f);
		position->x = radius;
	}

	if (position->y > SCREENHEIGHT - radius)
	{
		if (*angle > PI * 0.5f && *angle < PI * 1.5f)
			*angle = BounceAngle(*angle, 0);
		position->y = SCREENHEIGHT - radius;
	}
	if (position->y < radius)
	{
		if (*angle < PI * 0.5f || *angle > PI * 1.5f)
			*angle = BounceAngle(*angle, PI);
		position->y = radius;
	}
}

float BounceAngle(const float angle, const float normal)
{
	/*Vec2f incomingVector = { sinf(angle),cosf(angle) };
	Vec2f normalVector = { sinf(normal),cosf(normal) };
	Vec2f reflectionVector = { -((Vec2f{2.0f,2.0f} * (normalVector * incomingVector) * normalVector) - incomingVector) };
	return atan2f(reflectionVector.x, reflectionVector.y);*/
	return fmod(((normal - angle) * 2 + angle)+PI, 2 * PI);
}