#pragma once
#include <iostream>
#include <memory>
#include "Link.h"


class NeuralNetwork {
public:
	NeuralNetwork(int,int,int);
	~NeuralNetwork();
	void networkDisplay();
	void transmit();
	void networkUpdateInputs(std::vector<double>);
	int networkOutput();
	void init(std::vector<double>);

	void reset();
private:
	std::vector<Neuron*> InputLayer;
	std::vector<Neuron*> HiddenLayer;
	std::vector<Neuron*> OutputLayer;
	std::vector<Link*> Links;
};