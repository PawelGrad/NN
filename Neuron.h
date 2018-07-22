#pragma once
#include <SFML/Graphics.hpp>#



class Neuron {

	
public:
	Neuron(double);
	~Neuron();
	void setValue(double);
	double getValue();
 	void receive(double);

private:

	double value;

};