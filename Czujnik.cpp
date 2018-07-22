#pragma once
#include "Czujnik.h"
#include <iostream>


Czujnik::Czujnik(sf::Vector2f x, double y, int z) {
	samochod = x;
	kat = y;
	dlugosc = z;
	node.setFillColor(sf::Color::Green);
	node.setRadius(3);
	node.setOrigin(node.getLocalBounds().width / 2, node.getLocalBounds().height / 2);
	double xx = samochod.x + (cos(kat) * dlugosc);
	double yy = samochod.y + (sin(kat) * dlugosc);
	position = sf::Vector2f(xx, yy);
	node.setPosition(position);
	
	
}


Czujnik::~Czujnik() {}



void Czujnik::update(float x,sf::Vector2f pos) {
	kat += x;
	samochod = pos;
	double xx = samochod.x + (cos(kat) * dlugosc);
	double yy = samochod.y + (sin(kat) * dlugosc);
	position = sf::Vector2f(xx, yy);
	node.setPosition(position);
	
}

sf::Vector2f Czujnik::getPosition() {
	return node.getPosition();
}