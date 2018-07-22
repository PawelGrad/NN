#include "Link.h"


Link::Link(Neuron* a, Neuron* b, double c) {
	Input = a;
	Output = b;
	weight = c;
}
Link::~Link() {}

void Link::transmit() {
	double data = Input->getValue()*weight;
	Output->receive(data);
}

void Link::setLink(double a) {
	weight = a;
}

double Link::getLink() {
	return weight;
}