#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int a, int b, int c) {

	for (int i = 0; i < a + 1; i++)
	{
		Neuron* temp;
		if( i==a) temp = new Neuron(20);
		else temp = new Neuron(0);
		InputLayer.push_back(temp);
	}

	for (int i = 0; i < b; i++)
	{
		Neuron* temp = new Neuron(0);
		HiddenLayer.push_back(temp);
	}


	for (int i = 0; i < c; i++)
	{
		Neuron* temp = new Neuron(0);
		OutputLayer.push_back(temp);
	}



	for (auto it : InputLayer)
	{
		for (auto it2 : HiddenLayer)
		{
			Link* temp = new Link(it, it2, 1);
			Links.push_back(temp);

		}
	}

	for (auto it : HiddenLayer)
	{
		for (auto it2 : OutputLayer)
		{
			Link* temp = new Link(it, it2, 1);
			Links.push_back(temp);

		}
	}

}

NeuralNetwork::~NeuralNetwork() {}

void NeuralNetwork::networkDisplay() {


	for (auto it : InputLayer)
	{
		std::cout << it->getValue() << std::endl;
	}
	std::cout << "-----------------------" << std::endl;
	for (auto it : HiddenLayer)
	{
		std::cout << it->getValue() << std::endl;
	}
	std::cout << "-----------------------" << std::endl;
	for (auto it : OutputLayer)
	{
		std::cout << it->getValue() << std::endl;;
	}
	std::cout << "-----------------------" << std::endl;
	for (auto it : Links)
	{
		std::cout << it->getLink() << std::endl;;
	}
}

void NeuralNetwork::transmit() {

	for (auto it : Links)
	{
		it->transmit();
	}

}

void NeuralNetwork::networkUpdateInputs(std::vector<double> data) {
		std::vector<double>::iterator it=data.begin();
		std::vector<Neuron*>::iterator it2 = InputLayer.begin();
		while (it != data.end())
		{
			(*it2)->setValue(*it);
			it++;
			it2++;
		}
		

}

int NeuralNetwork::networkOutput() {
	int flag = 0;
	double max = 0;
	std::vector<Neuron*>::iterator it = OutputLayer.begin();
	for (int i = 0; i < OutputLayer.size(); i++)
	{
			if ((*it)->getValue() >= max)
			{
				max = (*it)->getValue();
				flag = i; 
			}
		it++;
	}
	return flag+1; 
	}

void NeuralNetwork::init(std::vector<double> a) {

	std::vector<double>::iterator i= a.begin();
	for (std::vector<Link*>::iterator it = Links.begin(); it < Links.end(); it++)
	{
		(*it)->setLink(*i);	
		i++;
		
	}
}


void NeuralNetwork::reset() {
	int i = 0;
	for (auto it : InputLayer)
	{
		if(i==5) it->setValue(45);
		else it->setValue(0);
		i++;
	}
	
	for (auto it : HiddenLayer)
	{
		it->setValue(0);

	}
	for (auto it : OutputLayer)
	{
		it->setValue(0);

	}

}