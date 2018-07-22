#include "Neuron.h"

Neuron::Neuron(double x) {
	value = x;
	
	
}
Neuron::~Neuron() {}



void Neuron::setValue(double x) {
	value = x;
}

double Neuron::getValue() {
	return value;
}

void Neuron::receive(double a) {
	value += a;
}