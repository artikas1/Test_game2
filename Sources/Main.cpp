#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"

static const float VIEW_LENGTH = 1200.0f;
static const float VIEW_HEIGHT = 800.0f;

// keiciant lango dydi, objektas nepraranda proporciju
void ResizeView(const sf::RenderWindow& window, sf::View& view) 
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);//proporcijai islaikyti reikia padalinant ekrano plotį iš aukščio. Gauta reikšme pritaikyti apatiniam veiksme 
	view.setSize(VIEW_LENGTH * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	srand(time(nullptr)); // sugeneruoja random seed'a

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Epic game", sf::Style::Close | sf::Style::Resize); // lango sukurimas ir jo parametrai
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_LENGTH, VIEW_HEIGHT));
	sf::Texture playerTexture; //sukuriama textura zmogeliukui
	playerTexture.loadFromFile("standing2.png"); //ant zaidejo uzdeda textura is pasirinkto failo
	
	Player player(&playerTexture, sf::Vector2u(4, 2), 0.3f/*animacijos greitis*/, 100.0f, 200.0f); // 200 yra smfl unit'ai, 1 = 1pixel

	sf::Texture tBackground;
	tBackground.loadFromFile("artu.png");
	sf::Sprite sprBackground(tBackground);
	sprBackground.setPosition(-1000.0f, -1500.0f);

	//platformos
	std::vector<Platform> platforms; //sukuriam vektoriu platformoms

	sf::Texture platformPagrinTextura;
	platformPagrinTextura.loadFromFile("ar1.png");
	sf::Texture platformTextura;
	platformTextura.loadFromFile("ar2.png");
	
	platforms.push_back(Platform(&platformTextura, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(rand() % 500 + 1, 100.0f))); //nullptr =0, dimensijos, koordinates
	platforms.push_back(Platform(&platformTextura, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(rand() % 500 + 1, -100.0f)));
	platforms.push_back(Platform(&platformTextura, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(rand() % 500 + 1, -300.0f)));
	platforms.push_back(Platform(&platformTextura, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(rand() % 500 + 1, -500.0f)));
	platforms.push_back(Platform(&platformTextura, sf::Vector2f(200.0f, 50.0f), sf::Vector2f(rand() % 500 + 1, -700.0f)));
	platforms.push_back(Platform(&platformPagrinTextura, sf::Vector2f(1000.0f, 50.0f), sf::Vector2f(200.0f, 400.0f))); // pagrindas

	float deltaTime = 0.0f; //kintamasis reikalingas apskaičiuoti laika, nuo paskutinio pasikeitusio kadro 
	sf::Clock clock;        //rekalingas, kad gautume deltaTime

	bool gameover = true;

	while (window.isOpen()&&gameover)
	{
		deltaTime = clock.restart().asSeconds();//funkcija restart() grazina sf::Time, o tai yra = deltaTime

		// keistas fix, bet reikalingas, kad nebutu bugo kai langa perstumi ant ekrano 
		if (deltaTime > 1.0f / 20.0f) // jei kadru maziau nei 20, priskiriam 20 kadru 
		{
			deltaTime = 1.0f / 20.0f;
		} 

		sf::Event evnt;                   // reikalingas norint atlikti 58-69 eilutes
		 							      
		while (window.pollEvent(evnt))    // duoda judint langa per ekrana
		{							      
			switch (evnt.type)		      
			{						      
			case sf::Event::Closed:       // leidzia isjungti langa paspaudzius ant "X"
				window.close();		      
				break;				      
			case sf::Event::Resized:      //leidzia keisti lango dimencijas
				ResizeView(window, view); //funkcija palieka tinkamas ojbektu proporcijas ekrane
				break;
			}
		}

		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)&&player.getGlobalBounds().left>0)
		{
			player.move(-0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)&&player.getGlobalBounds().left < window.getSize().x-player.getGlobalBounds().width)
		{
			player.move(0.1f, 0.0f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			player.move(0.0f, -0.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			player.move(0.0f, 0.1f);
		}*/

		player.Update(deltaTime); //kiecia animacija, judejimas. BNūtina kviesti prieš "view.setCenter(player.GetPosition());", kad zmogeliukas labiau "smooth" vaiksciotu

		sf::Vector2f direction;   //reikalingas, kad galetume grazinti kurioje vietoje kertasi objektai

		/*for (int i = 0; i < platforms.size(); i++)
		{
			Platform& platform = platforms[i];
		}*/

		//tikrinamas susidurimas
		for (Platform& platform : platforms) 
		{
			if (platform.GetCollider().CheckCollider(player.GetCollider(), direction, 1.0f))// kai push = 1, objektaaaaaadWAWDWWWWA nepastumsime
			{
				player.OnCollission(direction);
			}
		}

		view.setCenter(player.GetPosition()); // kamera sekioja zaideja

		window.clear(sf::Color(150, 150, 150)); // updatina nauja kadra (neleidzia kadrams "overlapintis"). Backgroundo spalva 
		window.draw(sprBackground);

		window.setView(view);                 // nustatome vaizda
		player.Draw(window);                  // atsiranda pasirinktos texturos and zmogeliuko
		
		for (Platform& platform : platforms)  // visos platformos isvedamos i ekrana
			platform.Draw(window);
		
		window.display();                     // programoje ivyke pakeitimai galiausiai turi būti pateikti vizualiai į ekraną, todel sita ivykdom paskutini
	} 

	return 0;
}