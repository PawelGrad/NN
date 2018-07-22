#pragma once
#include <SFML/Graphics.hpp>#
#include <cmath>



	bool inRange(sf::Vector2f, sf::Vector2f, float);
	bool inCircle(sf::Vector2f, sf::Vector2f, int);
	bool inSquare(sf::Vector2f, sf::Vector2f, int, int);
	bool lineLineIntersection(sf::Vertex, sf::Vertex B, sf::Vertex C, sf::Vertex D, sf::Vector2f &);
	double stopnieNaRadiany(double);
