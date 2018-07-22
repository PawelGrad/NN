#pragma once

#include "Funkcje.h"

bool inRange(sf::Vector2f a, sf::Vector2f b, float c) {
	if (sqrt((abs(a.x - b.x)*abs(a.x - b.x)) + (abs(a.y - b.y)*abs(a.y - b.y)))<c) return true;
	else return false;
}


bool inCircle(sf::Vector2f a, sf::Vector2f b, int r) {
	if (sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)) < r) return 1;
	else return 0;
}

bool inSquare(sf::Vector2f a, sf::Vector2f b, int h, int w) {
	if (a.x > b.x && a.x<b.x + w && a.y>b.y && a.y < b.y + h)
		return true;
	else return false;
}

double stopnieNaRadiany(double x) {
	double pi = 3.14159265358979323846;
	
	double stopnie = x * (pi / 180);
	return stopnie;
}
bool lineLineIntersection(sf::Vertex A, sf::Vertex B, sf::Vertex C, sf::Vertex D, sf::Vector2f &E)
{
	double minX, maxX, minY, maxY;
	minX = std::min(A.position.x, B.position.x);
	maxX = std::max(A.position.x, B.position.x);
	minY = std::min(A.position.y, B.position.y);
	maxY = std::max(A.position.y, B.position.y);

	double minX2, maxX2, minY2, maxY2;
	minX2 = std::min(C.position.x, D.position.x);
	maxX2 = std::max(C.position.x, D.position.x);
	minY2 = std::min(C.position.y, D.position.y);
	maxY2 = std::max(C.position.y, D.position.y);

	// Line AB represented as a1x + b1y = c1
	double a1 = B.position.y - A.position.y;
	double b1 = A.position.x - B.position.x;
	double c1 = a1*(A.position.x) + b1*(A.position.y);

	// Line CD represented as a2x + b2y = c2
	double a2 = D.position.y - C.position.y;
	double b2 = C.position.x - D.position.x;
	double c2 = a2*(C.position.x) + b2*(C.position.y);

	double determinant = a1*b2 - a2*b1;

	sf::Vertex temp;

	if (determinant == 0)
	{
		temp.position.x = 0;
		temp.position.y = 0;
		return 0;
	}
	else
	{
		double x = (b2*c1 - b1*c2) / determinant;
		double y = (a1*c2 - a2*c1) / determinant;
		E.x = x;
		E.y = y;
		if (E.x < minX || E.x > maxX || E.y < minY || E.y > maxY || E.x < minX2 || E.x > maxX2 || E.y < minY2 || E.y > maxY2)
		{
			temp.position.x = 0;
			temp.position.y = 0;
			return 0;
		}
		
		return 1;
	}
}
