#include "mandelbrotscene.h"

typedef std::complex<double> comp;

MandelbrotScene::MandelbrotScene()
{
	GenerateSet();
}

void MandelbrotScene::Main(const float dt, sf::RenderTexture& renderTexture)
{
	std::ostringstream time;
	time << "Generated in " << genTime << " seconds.";
	ImGui::Begin("Mandelbrot Scene");

	ImGui::InputInt("Iterations", &iterations, 1, 1);
	if (ImGui::Button("Generate"))
		GenerateSet();
	ImGui::Checkbox("Parallelism", &parallel);
	ImGui::Text(time.str().c_str());
	ImGui::End();

	sf::Texture tex;
	sf::Sprite spr;
	tex.loadFromImage(set);
	spr.setTexture(tex);
	renderTexture.draw(spr);
}

class MandelbrotScene::GenClass
{
private:
	int iterations;
	double xSlope;
	double ySlope;
public:
	GenClass(int it) : iterations(it)
	{
		xSlope = (xUBound - xLBound) / SCREENWIDTH;
		ySlope = (yUBound - yLBound) / SCREENHEIGHT;
	}
	unsigned char operator()(const int a)
	{
		int index = a;
		unsigned int x = modulo(index++, SCREENWIDTH);
		unsigned int y = (unsigned int)std::floor((float)index / (float)SCREENWIDTH);
		float curX = xLBound + xSlope*(float)x;
		float curY = yLBound + ySlope*(float)y;

		comp z = { 0,0 };
		comp c = { curX,curY };
		int i = 0;
		while (std::abs(z) <= 2 && i < iterations)
		{
			z = std::pow(z, 2) + c;
			i++;
		}
		if (i == iterations)
			return 0;
		else
		{
			unsigned char color = ((i + 1 - log(log2(std::abs(z)))) / iterations) * 255;
			return color;
		}
	}
};

void MandelbrotScene::GenerateSet()
{
	sf::Clock c;
	std::vector<int> indexes(SCREENHEIGHT * SCREENWIDTH);
	std::vector<unsigned char> setVals(SCREENHEIGHT * SCREENWIDTH);
	iterations = std::max(1, iterations);
	std::iota(indexes.begin(), indexes.end(),0);
	set.create(SCREENWIDTH, SCREENHEIGHT, sf::Color::White);
	GenClass g(iterations);
	if (parallel)
		std::transform(std::execution::par, indexes.begin(), indexes.end(), setVals.begin(), g);
	else
		std::transform(indexes.begin(), indexes.end(), setVals.begin(), g);
	for (int x = 0; x < SCREENWIDTH; x++)
	{
		for (int y = 0; y < SCREENHEIGHT; y++)
		{
			unsigned char color = setVals[x + (y * SCREENWIDTH)];
			set.setPixel(x, y, { color,color,color });
		}
	}
	genTime = c.getElapsedTime().asSeconds();
}