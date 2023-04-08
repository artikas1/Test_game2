#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	void Update(float deltaTime);		      //reikalingas, kad galetume "updatint" animaciją ir judėjimą
	void Draw(sf::RenderWindow& window);      //draw funkcija, kad galėtume turėti "body" kaip privatų, & "and" reikalingas, kad naudotume ta patį langą
	void OnCollission(sf::Vector2f direction);//funkcija tikrinanti ar susiduria objektai

	//Vector2f, nes jį sudaro du float
	sf::Vector2f GetPosition() { return body.getPosition(); } //graziname zaidejo pozicija
	Collider GetCollider() { return Collider(body); }	      //graziname realiai susidurima

private:
	sf::RectangleShape body; //sukuriamas zaidejo objektas 
	Animation animation;     //sukuriam, kad galėtume animuoti "body"
	unsigned int row;		 //kintamasis, kuriame bus saugoma eilute animacijos kadru
	float speed;			 //animacijos greitis		 
	bool faceRight;			 //reikalingas, kad žinotume ar zaidejas pasisukęs į kairę ar dešinę

	sf::Vector2f velocity;   //greitis 
	bool canJump;            //reikalingas tikrinimui ar galime nuo kazko atsokti 
	float jumpHeight;		 //pasokimo aukstis
};

