#include "raycastscene.h"

RaycastScene::RaycastScene()
{
	offset = { mapSize/2,mapSize/2 };
	nodes.create(mapSize, mapSize, sf::Color::Black);
	for (Line l : lines)
	{
		float lineAng = atan2f(vertices[l.v2].y - vertices[l.v1].y, vertices[l.v2].x - vertices[l.v1].x);
		Vec2f lineVec = { sin(lineAng) * check ,cos(lineAng) * check };
		Vec2f initVec = { vertices[l.v1].x,vertices[l.v1].y };
		float lineDist = sqrt(pow(vertices[l.v1].x - vertices[l.v2].x, 2) + pow(vertices[l.v1].y - vertices[l.v2].y, 2));
		for (float i = 0; i < lineDist; i += check * 2)
		{
			initVec += lineVec;
			sf::Vector2i nodeVec = { (int)initVec.x + (int)offset.x,(int)initVec.y + (int)offset.y };
			nodes.setPixel(nodeVec.x, nodeVec.y, l.col);
		}
	}
}

void RaycastScene::Main(const float dt, sf::RenderTexture& renderTexture)
{
	frameBuffer.create(SCREENWIDTH, SCREENHEIGHT, sf::Color::Black);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		angle = modulo(angle - (0.4f * PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		angle = modulo(angle + (0.4f * PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		pos.x += sin(-angle) * -100.0f * dt;
		pos.y += cos(-angle) * -100.0f * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		pos.x += sin(-angle) * 100.0f * dt;
		pos.y += cos(-angle) * 100.0f * dt;
	}

	for (unsigned int x = 0; x < SCREENWIDTH; x++)
	{
		float rayAngle = (angle - (fov / 2.0f)) + (x / SCREENWIDTH) * fov;
		float wallDistance = 0.0f;
		sf::Color wallColor;
		bool wallHit = false;

		Vec2f rayVec = { sin(angle),cos(angle) };

		while (!wallHit && wallDistance < 500.0f)
		{
			wallDistance += check;
			Vec2f testVec = (pos + (rayVec * wallDistance))+offset;

			if (nodes.getPixel((int)testVec.x,(int)testVec.y) != sf::Color::Black)
			{
				wallHit = true;
				wallColor = nodes.getPixel((int)testVec.x, (int)testVec.y);
			}

			//unsigned int lineInd = 0;

			/*while(!wallHit && lineInd < 4)
			{
				Line l = lines[lineInd++];
				float lineAng = atan2f(vertices[l.v2].y - vertices[l.v1].y, vertices[l.v2].x - vertices[l.v1].x);
				Vec2f lineVec = { sin(lineAng) * check ,cos(lineAng) * check };
				Vec2f initVec = { vertices[l.v1].x,vertices[l.v1].y };
				float lineDist = sqrt(pow(vertices[l.v1].x - vertices[l.v2].x, 2) + pow(vertices[l.v1].y - vertices[l.v2].y, 2));
				float distCovered = 0;
				while(!wallHit && distCovered<lineDist)
				{
					initVec += lineVec;
					distCovered += check;
					if (sqrt(pow(initVec.x - testVec.x, 2) + pow(initVec.y - testVec.y, 2)) < 0.1f)
					{
						wallHit = true;
						wallColor = l.col;
					}
				}
			}*/
		}

		if (wallHit)
		{
			int ceiling = float((SCREENHEIGHT * 0.5f) - SCREENHEIGHT / (wallDistance));
			int floor = SCREENHEIGHT - ceiling;
			for (unsigned int y = ceiling; y < floor; y++)
			{
				if (y > 0 && y < SCREENHEIGHT)
					frameBuffer.setPixel(x, y, wallColor);
			}
		}
	}

	sf::Texture frameTex;
	sf::Sprite frameSpr;
	frameTex.loadFromImage(frameBuffer);
	frameSpr.setTexture(frameTex);
	renderTexture.draw(frameSpr);
}