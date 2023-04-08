#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
	body.setSize(size);				//platformos dimensijos
	body.setOrigin(size / 2.0f);    //spawnina platforma centre, be sitos funkcijos platformos virsutini kairį kampą spawnintu centre
	body.setTexture(texture);		//ant platformos uzdedama textura
	body.setPosition(position);     //lango koordinate, kur bus atspawninta platforma
}

Platform::~Platform()
{
}

void Platform :: Draw(sf::RenderWindow& window)
{
	window.draw(body);
}