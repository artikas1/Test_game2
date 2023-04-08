#include "Animation.h"

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;// naudojamas pointeris this->, kad pasiektume specifine klase. Naudojame, nes kartojasi pavadinimai.
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0; // 0, nes pradedame animacija nuo pirmo kadro

	uvRect.width = texture->getSize().x / float(imageCount.x); //suzinome kadro ploti
	uvRect.height = texture->getSize().y / float(imageCount.y);//suzinome kadro auksti
}

Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime; // atimame, kad butu lygiai =0 ir nebutu mazos paklaidos
	
		currentImage.x++; //keičiam į sekantį kadrą

		//pasiekus paskutini kadra, butina nunulint, kad nebandytume naudoti neegzistuojančio (nematomo) kadro 
		if (currentImage.x >= imageCount.x) 
		{
			currentImage.x = 0;
		}
	}

	uvRect.top = currentImage.y * -uvRect.height; // apskaičiuojame virsutine kadro vieta

	if (faceRight)
	{
		uvRect.left = currentImage.x * uvRect.width; // apskaičiuojame kaire kadro vieta
		uvRect.width = abs(uvRect.width); //uzdedabe abs, kad nebutu neigiamas
	}

	else
	{
		uvRect.left = (currentImage.x + 1) * abs(uvRect.width); //padarome kadro pradzios vieta is desines
		uvRect.width = -abs(uvRect.width);//"flippinam" kadra. Uzdedame -abs, kad nesikaitaliotu tarp neigiamo ir teigiamo
	}
}