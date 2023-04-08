#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
	animation(texture, imageCount, switchTime) //iskvieciam kontsruktoriu
{
	this->speed = speed;            //iskvieciame animacijos greiti
	this->jumpHeight = jumpHeight;  //iskvieciama pasokimo auksti
	row = 0;                        //pradedame animacija nuo pirmos eilutes
	faceRight = true;               //pradedame animaciją kai žmogeliukas žiūri į dešinę

	body.setSize(sf::Vector2f(100.0f, 120.0f)); //zaidejo dimensijos
	body.setOrigin(body.getSize() / 2.0f);      //spawnina zmogeliuka centre, be sitos funkcijos zmogeliuko virsutini kairį kampą spawnintu centre
	body.setPosition(206.0f, 206.0f);           //lango koordinate, kur bus atspawnintas zaidejas
	body.setTexture(texture);                   //ant zaidejo uzdedama textura

}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	//velocity.x *= 0.5f; //atleidus A arba D, zaidejas ne iskarto sustos

	velocity.x = 0.1f;            //kai nespaudziame nei A nei D, greiti judejimo prilyginam =0, kad nejudetume kai nereikia

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		velocity.x -= speed;      //ejimas i kaire
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x -= speed  * 2; //begimas i kaire
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x += speed;      //ejimas i desine
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		velocity.x += speed  * 2; //begimas i desine
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump) // canJump tai pat turi buti true, kad leistu zaidejui pasokti
	{
		canJump = false; //nurodom false, kad negaletume non-stop sokineti ore

		// sokimo impulso formule
		velocity.y = -sqrtf(2.0f * 981.0f * jumpHeight); //- pires sqrt, kad sokinetume i virsu, o ne i apacia
		// square root ( 2.0f * gravity * jumpHeight);
	}

	velocity.y += 981.0f * deltaTime; //gravitacija

	if (velocity.x == 0.0f)
	{
		row = 0; //stovejimo kadrai
	}
	
	//nustatome kuriuos darus naudoti ir is kokios puses juos priskirti žmogeliukui 
	else 
	{
		row = -1;  //judejimo kadrai

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight); //zmogeliukas turi animacija (rodoma skirtinga .png file dalis)
	body.setTextureRect(animation.uvRect);       //uzdedama textura ant (siuo atveju) keturkampio objekto. naudojame kai reikia isvesti tik dalį, o ne visą texturą
	body.move(velocity * deltaTime);		     //dauginame is deltaTime pabaigoje, o nei kai koda vykdomas pvz judejimo komanda, taip mes tapsime nepriklausomi nuo specifiniu kadru kiekio
}

void Player::Draw(sf::RenderWindow& window)
{ 
	window.draw(body);
}

void Player::OnCollission(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		velocity.x = 0.0f; //susidurimas kaireje
		canJump = true;    //susidurus is kaires, leidziame vel pasokti
	}
	else if (direction.x > 0.0f)
	{
		velocity.x = 0.0f; //susidurimas desineje
		canJump = true;    //susidurus is desines, leidziame vel pasokti
	}
	if (direction.y < 0.0f)
	{
		velocity.y = 0.0f; //susidurimas apacioje
		canJump = true;    //susidurus apacioje, leidziame vel pasokti
	}
	else if (direction.y > 0.0f)
	{
		velocity.y = 0.0f; //susidurimas virsuje
	}
}
