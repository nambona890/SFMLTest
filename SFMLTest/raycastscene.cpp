#include "raycastscene.h"

RaycastScene::RaycastScene()
{
	rinTex.loadFromFile("rintex.png");
	emiTex.loadFromFile("emitex.png");
	defTex.loadFromFile("deftex.png");
}

void RaycastScene::Main(const float dt, sf::RenderTexture& renderTexture)
{

	ImGui::Begin("Raycast");

	ImGui::SliderFloat("X", &pos.x, 0.1f, 5.0f);
	ImGui::SliderFloat("Y", &pos.y, 0.1f, 5.0f);
	ImGui::SliderAngle("Angle", &angle, 0.0f, 360.0f);

	ImGui::End();

	frameBuffer.create(SCREENWIDTH, SCREENHEIGHT, sf::Color::Black);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		angle = modulo(angle - (0.4f * PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		angle = modulo(angle + (0.4f * PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		pos.x += sin(angle) * 4.0f * dt;
		pos.y += cos(angle) * 4.0f * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		pos.x += sin(angle) * -4.0f * dt;
		pos.y += cos(angle) * -4.0f * dt;
	}

	for (unsigned int x = 0; x < SCREENWIDTH; x++)
	{
		bool xRight = false;
		bool yBottom = false;
		bool hitHoriz = false;
		float rayAngle = (angle - (fov / 2.0f)) + ((float)x / SCREENWIDTH) * fov;
		float wallDistance = 0.0f;
		sf::Color wallColor;
		bool wallHit = false;
		bool wallCol = false;
		sf::Image* tex = &defTex;
		Vec2f relVec;
		Vec2f rayVec = { sin(rayAngle),cos(rayAngle) };

		while (!wallHit && wallDistance < 100.0f)
		{
			wallDistance += check;
			Vec2f testVec = pos + (rayVec * wallDistance);
			unsigned int index = clamp((unsigned int)(testVec.x), 0u, mapWidth) + clamp((unsigned int)(testVec.y), 0u, mapHeight) * mapWidth;
			if (map[index] != '0')
			{
				wallHit = true;
				relVec = { testVec.x-floorf(testVec.x),testVec.y-floorf(testVec.y) };
				xRight = relVec.x > 0.5f;
				yBottom = relVec.y > 0.5f;
				if (xRight && yBottom)
				{
					hitHoriz = relVec.x < relVec.y;
				}
				else if (!xRight && !yBottom)
				{
					hitHoriz = relVec.x > relVec.y;
				}
				else if (xRight && !yBottom)
				{
					hitHoriz = relVec.x < 1.0f - relVec.y;
				}
				else if (!xRight && yBottom)
				{
					hitHoriz = relVec.x > 1.0f - relVec.y;
				}
				switch (map[index])
				{
				default:
					wallCol = true;
					wallColor = sf::Color::White;
					break;
				case '1':
					tex = &rinTex;
					break;
				case '2':
					tex = &emiTex;
					break;
				}
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

		if (wallHit && wallDistance > 0.1f)
		{
			int ceiling = float((SCREENHEIGHT * 0.5f) - SCREENHEIGHT / (wallDistance));
			int floor = SCREENHEIGHT - ceiling;
			if (wallCol)
			{
				for (unsigned int y = ceiling; y < floor; y++)
				{
					if (y >= 0 && y < SCREENHEIGHT)
						frameBuffer.setPixel(x, y, wallColor);
				}
			}
			else
			{
				float curY = 255;
				float dy = -256.0f/float(floor-ceiling);
				float px = 0;
				if (!hitHoriz)
				{
					px = modulo(xRight ? -256.0f * (1.0f - relVec.y) : -256.0f * relVec.y,256.0f);
				}
				else
				{
					px = modulo(yBottom ? -256.0f * relVec.x : -256.0f * (1.0f - relVec.x),256.0f);
				}
				for (int y = ceiling; y < floor; y++,curY+=dy)
				{
					if (y >= 0 && y < SCREENHEIGHT && curY < 256.0f && px < 256.0f && curY >= 0.0f && px >= 0.0f)
						frameBuffer.setPixel(x, y, tex->getPixel(px,curY));
					else
					{
						int penis = 1;
					}
				}
			}
		}
	}

	sf::Texture frameTex;
	sf::Sprite frameSpr;
	frameTex.loadFromImage(frameBuffer);
	frameSpr.setTexture(frameTex);
	renderTexture.draw(frameSpr);
}