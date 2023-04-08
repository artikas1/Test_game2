#include "Collider.h"


Collider::Collider(sf::RectangleShape& body) :
	body(body) //reikia inicializuoti "body" siame konstruktoriuje
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollider(Collider other, sf::Vector2f& direction, float push)
{
	const sf::Vector2f otherPosition = other.GetPosition();  //gauname pozicija pirmo objekto
	const sf::Vector2f otherHalfSize = other.GetHalfSize();  //gauname puse dydzio pirmo objekto
	const sf::Vector2f thisPosition = GetPosition();		 //gauname pozicija antro objekto
	const sf::Vector2f thisHalfSize = GetHalfSize();		 //gauname puse dydzio antro objekto

	//apskaiciuojame pagal formule
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x); //abs, kad butu realus skaicius, nepriklausomai ar jis neigiamas ar teigiamas
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)// tikrinam ar objektai susiduria	
	{
		push = std::min(std::max(push, 0.0f), 1.0f); // vyksta "clamping" tarp value 1 ir value 2							

		if (intersectX > intersectY) //tikrinam su kuria ašimi/puse daugiausiai liečiasi, siuo atveju stumtume X asyje						
		{
			if (deltaX > 0.0f) //tikrinam is kurios puses susidure
			{
				Move(intersectX * (1.0f - push), 0.0f); //stumiantis objektas (zaidejas) juda leciau X ašyje tam tikrui greiciu 
				other.Move(-intersectX * push, 0.0f);   //stumiamas objektas juda i priešinga puse X ašyje tam tikru greiciu 

				direction.x = 1.0f; // susiduriam su kazkuo is desines				
				direction.y = 0.0f; // 0, nes su nieko nesusiduriam y asyje			
			}
			else               //tikrinam is kurios puses susidure
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);

				direction.x = -1.0f;// susiduriam su kazkuo is kaires				
				direction.y = 0.0f; // 0, nes su nieko nesusiduriam y asyje			
			}
		}

		else//tikrinam su kuria ašimi/puse daugiausiai liečiasi, siuo atveju stumtume Y ašyje																			
		{
			if (deltaY > 0.0f) //tikrinam ar is virsaus susidure
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);

				direction.x = 0.0f;
				direction.y = 1.0f; // juda objektas virsu 			
			}
			else//tikrinam ar is apacios susidure
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);

				direction.x = 0.0f;
				direction.y = -1.0f; // juda objektas i apacia 
			}
		}
		return true; //grazinam true jei įvyksta susidurimas															
	}

	return false; //reikia grazinti false, jei neįvyks joks susidurimas				
}