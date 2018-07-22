#pragma once

#include <SFML/Graphics.hpp>#
#include <memory>
#include "Czujnik.h"
#include "Funkcje.h"



class Car{
public:
	Car(int, int, int, int, int, int);
	~Car();
	void draw(sf::RenderWindow&);
	void rotate(double);
	void accelerate();
	void update();
	void brake();
	void setWeights(std::vector<double>);
	std::vector<double> getWeights();
	sf::Vector2f getPosition();
	std::vector<sf::Vector2f> getCzujniki();
	void setPosition();
	double getFitness();
	bool Crashed();
	void reset();
private:
	int rotation;
	float acc;
	sf::RectangleShape car;
	std::vector<Czujnik> czujniki;
	sf::Vector2f velocity;
	double fitness;
	std::vector<double> weights;
	bool isCrashed  = 0;
	
};
