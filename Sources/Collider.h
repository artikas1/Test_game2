#pragma once
#include <SFML\Graphics.hpp>

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx,dy); }						  // darome funkcija, kad nereiktu sukurti kūno kaip public kintamojo

	bool CheckCollider(Collider other, sf::Vector2f & direction, float push); // push kintamasis reikalingas objekto stumimo greiciui(siame "zaidime" to nera)
	sf::Vector2f GetPosition() const {return body.getPosition(); }			  // sukuriame funkcija, kad galetume patikrinti su kitu kunu "CheckCollider" funkcijoje
	sf::Vector2f GetHalfSize() const {return body.getSize() / 2.0f; }	      // funkcija, kuri grazina pusę objekto kuno
private:
	sf::RectangleShape& body;											      // kuna issaugome klaseje, kad galetume ji modifikuoti
};

