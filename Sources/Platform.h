#pragma once
#include <SFML\Graphics.hpp>
#include "Collider.h"

class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position); //platforma turi textura, dydi ir pozicija
	~Platform();

	void Draw(sf::RenderWindow& window); // isvedamas platformos
	Collider GetCollider() { return Collider(body); } //graziname objekta

private:
	sf::RectangleShape body;
};

