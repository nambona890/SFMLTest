#include "muncherscene.h"

MuncherScene::MuncherScene()
{
	muncherTex[0].loadFromFile("munch1.png");
	muncherTex[1].loadFromFile("munch2.png");
	for (int i = 0; i < 8; i++)
	{
		munchers.push_back(Muncher(&muncherTex[0], sf::Color{ 255,0,0 }));
	}
	controlMuncher = ControlableMuncher(&muncherTex[0], sf::Color{ 255,255,255 });
}

void MuncherScene::Main(const float dt, sf::RenderTexture* renderTexture)
{

	munchTime += dt;
	if (munchTime > 0.15)
	{
		for (int i = 0; i < 8; i++)
			munchers[i].muncherSprite.setTexture(muncherTex[munchIndex]);
		controlMuncher.SetMuncherTexture(&muncherTex[munchIndex]);
		if (++munchIndex > 1)
			munchIndex = 0;
		munchTime = 0.0f;
	}
	renderTexture->clear(sf::Color{ 0, 128, 128 });
	for (int i = 0; i < 8; i++)
	{
		munchers[i].UpdateMuncher(dt);
		renderTexture->draw(munchers[i].muncherSprite);
	}
	controlMuncher.UpdateMuncher(dt);
	renderTexture->draw(controlMuncher.GetMuncherSprite());
}