#pragma once
#include <SFML/Graphics.hpp>#



class Czujnik {
public:
	Czujnik(sf::Vector2f,double,int);
	~Czujnik();
	
	void update(float,sf::Vector2f);
	sf::Vector2f getPosition();
private:
	sf::CircleShape node;
	float kat;
	double dlugosc;
	sf::Vector2f samochod;
	sf::Vector2f position;
};


