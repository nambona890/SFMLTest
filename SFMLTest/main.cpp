#include "main.h"

int main()
{
	srand((unsigned int)time(NULL));
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ur mom");
	sf::RenderTexture renderTexture;
	renderTexture.create(SCREENWIDTH, SCREENHEIGHT);
	window.setKeyRepeatEnabled(false);
	sf::Texture muncherTex[2];
	muncherTex[0].loadFromFile("munch1.png");
	muncherTex[1].loadFromFile("munch2.png");
	sf::Clock dc;
	std::vector<Muncher> munchers;
	for (int i = 0; i < 8; i++)
		munchers.push_back(Muncher(&muncherTex[0], &sf::Color{ 255,0,0 }));
	ControlableMuncher controlMuncher(&muncherTex[0], &sf::Color{ 255,255,255 });
	sf::Time dtt;
	float time = 0.6,dt = 0;
	float timescale = 1.0;
	int munindex = 0;
	ImGui::SFML::Init(window);

	while (window.isOpen())
	{
		time += dt;
		if (time > 0.15)
		{
			for(int i=0;i<8;i++)
				munchers[i].muncherSprite.setTexture(muncherTex[munindex]);
			controlMuncher.SetMuncherTexture(&muncherTex[munindex]);
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
					munchers.push_back(Muncher(&muncherTex[munindex], &sf::Color{ 255,0,0 }));
			}
			ImGui::SFML::ProcessEvent(event);
		}
		window.clear(sf::Color{0,128,128});
		renderTexture.clear(sf::Color{ 0,128,128 });
		for (int i = 0; i < 8; i++)
		{
			munchers[i].UpdateMuncher(dt);
			renderTexture.draw(munchers[i].muncherSprite);
			//window.draw(munchers[i].muncherSprite);
		}
		controlMuncher.UpdateMuncher(dt);
		//window.draw(controlMuncher.GetMuncherSprite());
		renderTexture.draw(controlMuncher.GetMuncherSprite());
		sf::Sprite renderSprite(renderTexture.getTexture());
		window.draw(renderSprite);
		dtt = dc.restart();
		dt = dtt.asSeconds()*timescale;
		ImGui::SFML::Update(window, dtt);
		StartImGui(&timescale);
		ImGui::SFML::Render(window);
		window.display();
	}
}

void StartImGui(float* timescale)
{
	ImGui::Begin("Gay shit");
	ImGui::Button("I'm gay");
	ImGui::SliderFloat("Timescale", timescale, 0.1, 10);
	ImGui::End();
}