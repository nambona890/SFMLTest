#include "main.h"

int main()
{
	srand((unsigned int)time(NULL));
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ur mom");
	window.setKeyRepeatEnabled(false);
	sf::Texture muncherTex[2];
	muncherTex[0].loadFromFile("munch1.png");
	muncherTex[1].loadFromFile("munch2.png");
	sf::Clock dc;
	std::vector<Muncher> munchers;
	for (int i = 0; i < 8; i++)
		munchers.push_back(Muncher(&muncherTex[0]));
	float dt = 0,time = 0.6;
	int munindex = 0;
	while (window.isOpen())
	{
		time += dt;
		if (time > 0.15)
		{
			for(int i=0;i<8;i++)
				munchers[i].muncherSprite.setTexture(muncherTex[munindex]);
			if (++munindex > 1)
				munindex = 0;
			time = 0.0f;
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::R)
			{
				munchers.clear();
				for (int i = 0; i < 8; i++)
					munchers.push_back(Muncher(&muncherTex[munindex]));
			}
		}
		window.clear(sf::Color{0,128,128});
		for (int i = 0; i < 8; i++)
		{
			munchers[i].UpdateMuncher(dt);
			window.draw(munchers[i].muncherSprite);
		}
		window.display();
		dt = dc.restart().asSeconds();
	}
}

