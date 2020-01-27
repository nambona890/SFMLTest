#include "main.h"

int main()
{
	srand((unsigned int)time(NULL));
	sf::RenderWindow window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "ur mom");
	sf::RenderTexture renderTexture;
	renderTexture.create(SCREENWIDTH, SCREENHEIGHT);
	window.setKeyRepeatEnabled(false);
	sf::Clock dc;
	sf::Time dtt;
	float dt = 0;
	float timescale = 1.0;
	ImGui::SFML::Init(window);
	MuncherScene scene;
	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			/*if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::R)
			{
				munchers.clear();
				for (int i = 0; i < 8; i++)
					munchers.push_back(Muncher(&muncherTex[munindex], &sf::Color{ 255,0,0 }));
			}*/
			ImGui::SFML::ProcessEvent(event);
		}
		renderTexture.clear(sf::Color{ 0, 0, 0 });
		scene.Main(dt,&renderTexture);
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