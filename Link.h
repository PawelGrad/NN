#pragma once
#include <iostream>
#include "Neuron.h"


class Link {
public:
	Link(Neuron*, Neuron*, double);
	~Link();
	void transmit();
	void setLink(double);
	double getLink();
private:
	Neuron* Input;
	Neuron* Output;
	double weight;
};