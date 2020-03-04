#include "mode7scene.h"



Mode7Scene::Mode7Scene()
{
	planeImg->loadFromFile("ayylmao.png");
}

void Mode7Scene::Main(const float dt, sf::RenderTexture* renderTexture)
{
	ImGui::Begin("Mode 7");

	ImGui::SliderInt("Center Y", &centerY, -200, 200);
	ImGui::SliderFloat("Scale Factor", &scaleFactor, 0.1f, 5.0f);
	ImGui::SliderAngle("Angle", &angle, 0.0f, 360.0f);

	ImGui::End();



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		angle = modulo(angle - (0.4f * PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		angle = modulo(angle + (0.4f * PI * dt), TAU);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		pos.x += sin(-angle) * -600.0f * dt;
		pos.y += cos(-angle) * -600.0f * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		pos.x += sin(-angle) * 600.0f * dt;
		pos.y += cos(-angle) * 600.0f * dt;
	}


	const unsigned int planeHeight = unsigned int(SCREENHEIGHT * 0.85);

	sf::Image* planeRndr = new sf::Image;
	planeRndr->create(SCREENWIDTH, planeHeight, sf::Color::Black);

	sf::Texture planeTex;
	sf::Sprite planeSpr;

	for (int i = 0; i < planeHeight; i++)
	{
		float tmpScale = 1 / ((planeHeight - (float)i)*(float(scaleFactor*0.01)));
		sf::Transform tmpTransform;
		tmpTransform.rotate(RADTODEG(-angle)).scale({ tmpScale,tmpScale });
		for (int j = 0; j < SCREENWIDTH; j++)
		{
			Vec2f tranPoint = tmpTransform.transformPoint({ (float)j - (SCREENWIDTH / 2),float(planeHeight + centerY) });
			planeRndr->setPixel(j, i,
				planeImg->getPixel(
					modulo((int)tranPoint.x+(int)pos.x, (int)planeImg->getSize().x),
					modulo((int)-tranPoint.y+ (int)pos.y, (int)planeImg->getSize().y)
				)
			);
		}
	}

	planeTex.loadFromImage(*planeRndr);
	planeSpr.setTexture(planeTex);
	planeSpr.setPosition({0,-int(SCREENHEIGHT-planeHeight)});
	renderTexture->draw(planeSpr);
	delete planeRndr;
}