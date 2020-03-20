#include "raycastscene.h"

RaycastScene::RaycastScene()
{
	
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
		float rayAngle = (angle - (fov / 2.0f)) + ((float)x / SCREENWIDTH) * fov;
		float wallDistance = 0.0f;
		sf::Color wallColor;
		bool wallHit = false;

		Vec2f rayVec = { sin(rayAngle),cos(rayAngle) };

		while (!wallHit && wallDistance < 100.0f)
		{
			wallDistance += check;
			Vec2f testVec = pos + (rayVec * wallDistance);
			unsigned int index = clamp((unsigned int)(testVec.x), 0u, mapWidth) + clamp((unsigned int)(testVec.y), 0u, mapHeight) * mapWidth;
			if (map[index] != '0')
			{
				wallHit = true;
				switch (map[index])
				{
				default:
				case '1':
					wallColor = sf::Color::White;
					break;
				case '2':
					wallColor = sf::Color::Red;
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

		if (wallHit)
		{
			int ceiling = clamp(float((SCREENHEIGHT * 0.5f) - SCREENHEIGHT / (wallDistance)),0.0f,SCREENHEIGHT-1.0f);
			int floor = clamp(SCREENHEIGHT - ceiling,0,SCREENHEIGHT);
			for (unsigned int y = ceiling; y < floor; y++)
			{
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