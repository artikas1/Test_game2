#pragma once
#include <SFML\Graphics.hpp>

class Animation
{
public:
	//pointeris "sf::Texture* texture" reikalingas, kad galetume zinoti texturos dydi, jei tiesiogiai dydi perduoti - tai ilgiau uztruks laiko
	//"sf::Vector2u imageCount" tures kadru kieki, kuri issaugos kintamajame "imageCount"
	//"float switchTime" issaugosime animacijos laika kintamajame "switchTime"
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	//row - kuria animacijos eile norime pasiekti
	//deltaTime - laikas tarp praeito ir dabartinio kadro "frame". Realiai naudojam, kad nepriklausant nuo kompiuterio greicio, kadro pasikeitimas butu vienodas
	void Update(int row, float deltaTime, bool faceRight);

public:
	sf::IntRect uvRect; //sf::IntRect sudaro x ir y offset ir auksti bei ploti

private:
	// pasirenkame Vector2u,o ne Vector2i, nes kadras nebus maziau nei 0 (jei butu maziau, mes bandytume paimti kadra uz (siuo atveju) .png filo ribu
	sf::Vector2u imageCount; // kiek kadru tures animacija
	sf::Vector2u currentImage; //dabartinis kadras
	
	//kontroliuoja animacijos greiti
	float totalTime; //laikas nuo paskutinio pasikeitusio animacijos kadro
	float switchTime;//kiek laiko mes norime, kad viena animacija vyktu

};


