#include "mandelbrotscene.h"

typedef std::complex<double> comp;

MandelbrotScene::MandelbrotScene()
{
	GenerateSet();
}

void MandelbrotScene::Main(const float dt, sf::RenderTexture* renderTexture)
{
	ImGui::Begin("Mandelbrot Shit");

	ImGui::InputInt("Iterations", &iterations, 1, 1);
	if (ImGui::Button("Generate"))
		GenerateSet();

	ImGui::End();

	sf::Texture tex;
	sf::Sprite spr;
	tex.loadFromImage(set);
	spr.setTexture(tex);
	renderTexture->draw(spr);
}

void MandelbrotScene::GenerateSet()
{
	iterations = std::max(1, iterations);
	set.create(SCREENWIDTH, SCREENHEIGHT, sf::Color::White);

	const double xSlope = (xUBound - xLBound) / SCREENWIDTH;
	const double ySlope = (yUBound - yLBound) / SCREENHEIGHT;

	double curY = yLBound;
	for (int y = 0; y < SCREENHEIGHT; y++, curY += ySlope)
	{
		double curX = xLBound;
		for (int x = 0; x < SCREENWIDTH; x++, curX += xSlope)
		{
			comp z = { 0,0 };
			comp c = { curX,curY };
			int i = 0;
			while (std::abs(z) <= 2 && i < iterations)
			{
				z = std::pow(z, 2) + c;
				i++;
			}
			if (i == iterations)
				set.setPixel(x, y, sf::Color::Black);
			else
			{
				unsigned int color = ((i + 1 - log(log2(std::abs(z)))) / iterations) * 255;
				set.setPixel(x, y, sf::Color(color, color, color));
			}
		}
	}
}