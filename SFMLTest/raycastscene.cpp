#include "raycastscene.h"

RaycastScene::RaycastScene()
{
	verts.push_back({ -64,-64 });
	verts.push_back({ 64,-64 });
	verts.push_back({ 64,64 });
	verts.push_back({ -64,64 });
	lines.push_back({ 0,1,sf::Color::Red });
	lines.push_back({ 1,2,sf::Color::Green });
	lines.push_back({ 2,3,sf::Color::Blue });
	lines.push_back({ 3,0,sf::Color::Yellow });
}

void RaycastScene::Main(const float dt, sf::RenderTexture* renderTexture)
{
	float dspeed = dt * speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		angle = modulo(angle - (PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		angle = modulo(angle + (PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		pos += {sinf(-angle + PI)* dspeed, cosf(-angle + PI)* dspeed};
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		pos -= {sinf(-angle + PI)* dspeed, cosf(-angle + PI)* dspeed};



	framebuffer.create(SCREENWIDTH, SCREENHEIGHT, sf::Color::Black);
	for (int i = 0; i < lines.size(); i++)
	{
		Vec2f cv = verts[lines[i].v1];
		Vec2f tv1 = { ((cv.x * cos(-angle)) - pos.x) - ((cv.y * sin(-angle)) - pos.y),((cv.x * sin(-angle) - pos.x)) + ((cv.y * cos(-angle)) - pos.y) };
		cv = verts[lines[i].v2];
		Vec2f tv2 = { ((cv.x * cos(-angle)) - pos.x) - ((cv.y * sin(-angle)) - pos.y),((cv.x * sin(-angle) - pos.x)) + ((cv.y * cos(-angle)) - pos.y) };

		if (tv1.y > 0 && tv2.y > 0 )
		{
			float tx1 = (SCREENWIDTH / 2) + tv1.x * (tanf(fov) / tv1.y);
			float tx2 = (SCREENWIDTH / 2) + tv2.x * (tanf(fov) / tv2.y);
			float uty1 = (SCREENHEIGHT / 2) + (playerHeight - wallHeight) * (tanf(fov) / tv1.y);
			float bty1 = (SCREENHEIGHT / 2) + -playerHeight * (tanf(fov) / tv1.y);
			float uty2 = (SCREENHEIGHT / 2) + (playerHeight - wallHeight) * (tanf(fov) / tv2.y);
			float bty2 = (SCREENHEIGHT / 2) + -playerHeight * (tanf(fov) / tv2.y);
			if (tx2 > tx1)
			{
				float ucury = uty1;
				float bcury = bty1;
				float slope1 = (uty2 - uty1) / (tx2 - tx1);
				float slope2 = (bty2 - bty1) / (tx2 - tx1);
				for (int sl = (int)tx1;sl<(int)tx2;sl++)
				{
					if (sl >= 0)
					{
						for (int p = clamp(ucury, 0.0f, (float)SCREENHEIGHT); p < clamp(bcury, 0.0f, (float)SCREENHEIGHT); p++)
						{
							framebuffer.setPixel((unsigned)sl, (unsigned)p, lines[i].color);
						}
					}
					ucury += slope1;
					bcury += slope2;
				}
			}
		}


	}
}