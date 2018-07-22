#include "car.h"


Car::Car(int dlugosc, int szerokosc, int posX, int posY, int ilosc, int kat) {
	car.setFillColor(sf::Color::Red);
	car.setSize(sf::Vector2f(szerokosc, dlugosc));
	car.setOrigin(car.getLocalBounds().width / 2, car.getLocalBounds().height / 2);
	car.setPosition(posX, posY);
	acc = 0.01;
	fitness = 0;
	velocity = sf::Vector2f(0, 0);
	for (int i = 0; i < ilosc; i++)
	{
	
		Czujnik czujnik(sf::Vector2f(car.getPosition().x, car.getPosition().y), stopnieNaRadiany(-70 + (kat * i)), 45);
		czujniki.push_back(czujnik);

	}
	
	
}
Car::~Car(){}

void Car::draw(sf::RenderWindow& a) {
	a.draw(car);
	
}
void Car::rotate(double kat) {
	car.rotate(kat);
	for (std::vector<Czujnik>::iterator it = czujniki.begin(); it<czujniki.end(); it++)
	{
		it->update(stopnieNaRadiany(kat), car.getPosition());

	}

}

void Car::accelerate() {
	sf::Vector2f force;
	force.x = 0;
	force.y = 0;
	float angleRads = stopnieNaRadiany(car.getRotation() + 90);
	force.x = acc*sin(angleRads);
	force.y = acc*-cos(angleRads);
	velocity += force;

}

void Car::brake() {
	velocity.x *= 0.95;
	velocity.y *= 0.95;

}

void Car::update() {
    velocity.x *= 0.99;
	velocity.y *= 0.99;
	car.move(velocity);
	for (std::vector<Czujnik>::iterator it = czujniki.begin(); it<czujniki.end(); it++)
	{
		it->update(stopnieNaRadiany(0), car.getPosition());

	}
	if (sqrt(pow(velocity.x, 2) + pow(velocity.y, 2)) < 0.001)
	{
		car.setPosition(2000, 200);
		isCrashed = 1;
	}
	if(car.getPosition().x > 1600  || car.getPosition().x < 0 || car.getPosition().y>800 || car.getPosition().y<0) isCrashed = 1;

	
	
	if(!isCrashed)fitness += sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	//if (!isCrashed)fitness += 1;
}

void Car::setWeights(std::vector<double> a) {
	weights = a;
}
std::vector<double> Car::getWeights() {
	return weights;
}

std::vector<sf::Vector2f> Car::getCzujniki() {
	std::vector<sf::Vector2f> t;
	for (auto it : czujniki)
	{
		t.push_back(it.getPosition());
	}

	
	return t;
}

sf::Vector2f Car::getPosition() {
	return car.getPosition();
}

void Car::setPosition() {
	car.setPosition(2000, 200);
	isCrashed = 1;
}

double Car::getFitness() {
	return fitness;
}

bool Car::Crashed() {
	return isCrashed;
}

void Car::reset() {
	fitness = 0;
	velocity = sf::Vector2f(0, 0);
	car.setPosition(800, 700);
	car.setRotation(0);
	isCrashed = 0;
}