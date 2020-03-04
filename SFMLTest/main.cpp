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

	MandelbrotScene* mbScene = new MandelbrotScene();
	MuncherScene* munchScene = new MuncherScene();
	Mode7Scene* mode7Scene = new Mode7Scene();
	Scene* scene = dynamic_cast<Mode7Scene*>(mode7Scene);

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
		ImGui::SFML::Update(window, dtt);

		scene->Main(dt, &renderTexture);

		sf::Sprite renderSprite(renderTexture.getTexture());
		window.draw(renderSprite);

		dtt = dc.restart();
		dt = dtt.asSeconds() * timescale;

		ImGui::Begin("Global Controls");

		ImGui::SliderFloat("Timescale", &timescale, 0.1, 10);
		if (ImGui::Button("New Mandelbrot Scene"))
		{
			delete mbScene;
			mbScene = new MandelbrotScene();
			scene = dynamic_cast<MandelbrotScene*>(mbScene);
		}
		if (ImGui::Button("New Muncher Scene"))
		{
			delete munchScene;
			munchScene = new MuncherScene();
			scene = dynamic_cast<MuncherScene*>(munchScene);
		}
		if (ImGui::Button("New Mode 7 Scene"))
		{
			delete mode7Scene;
			mode7Scene = new Mode7Scene();
			scene = dynamic_cast<Mode7Scene*>(mode7Scene);
		}
		ImGui::End();

		ImGui::SFML::Render(window);

		window.display();
	}
	delete mbScene;
	delete munchScene;
	delete mode7Scene;
}