
#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <time.h>
#include <iostream>
#include <cstdlib>

#include <fstream>
#include <sstream>

#include "Funkcje.h"
#include "Car.h"
#include "NeuralNetwork.h"



int main()
{
	
	struct Line {
		sf::Vertex A;
		sf::Vertex B;
	

	};
	
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Render");
	window.setFramerateLimit(60);

	NeuralNetwork NN(5, 4, 2);
	

	std::vector<Car> Generation;
		for (int i = 0; i < 50; i++) 
		{
			Car car(10, 18, 800, 700, 5, 35);
			std::vector<double> temp;
			for (int j = 0; j < 32; j++)
			{
				temp.push_back(rand() / (RAND_MAX + 1.));
			}
		
			car.setWeights(temp);
			Generation.push_back(car);
		}

		std::vector<Line> LinesInner;
		std::vector<Line> LinesOuter;
	
		{
			std::ifstream file;
			file.open("Linie.csv");	
			std::string line;
			while (getline(file, line))
			{

				std::stringstream linestream(line);
				std::string value;
				int i = 0;
				Line temp;
				while (getline(linestream, value, ','))
				{

					switch (i) {
					case 0: temp.A.position.x = atof(value.c_str());
						break;
					case 1: temp.A.position.y = atof(value.c_str());
						break;
					case 2: temp.B.position.x = atof(value.c_str());
						break;
					case 3: temp.B.position.y = atof(value.c_str());
						break;
					}
					i++;
				}
				LinesInner.push_back(temp);
			}
		}
		Line temp;
		bool firstPoint = 1;
		sf::Vector2f punkt;
		int GenerationCount = 1;
		bool Merged1 = 0;
		bool Merged2 = 0;
		bool exe = 0;
		int crashedCars=0;
		int once = 0;

		while (window.isOpen())
		{
			
			sf::Vector2i mouse = sf::Mouse::getPosition(window);
			sf::Vector2f mouseCoords = window.mapPixelToCoords(mouse);

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::KeyPressed)
				{
					
					if (event.key.code == sf::Keyboard::S)
					{
						exe = 1;
					}

					if (event.key.code == sf::Keyboard::W)
					{
						for (std::vector<Car>::iterator it = Generation.begin(); it < Generation.end(); it++)
						{
							it->setPosition();
						}
					}
					if (event.key.code == sf::Keyboard::B)
					{

						if (firstPoint)
						{
							if (LinesInner.size() == 0)
							{

								temp.A.position = mouseCoords;
								firstPoint = 0;
							}
						}
						else
						{

							if (LinesInner.size() == 0)
							{
								temp.B.position = mouseCoords;
								punkt = temp.B.position;
								LinesInner.push_back(temp);
							}
							else
							{
								temp.A.position = punkt;
								temp.B.position = mouseCoords;
								punkt = temp.B.position;
								LinesInner.push_back(temp);
							}

						}

					}
					if (event.key.code == sf::Keyboard::N && LinesInner.size() > 0)
					{

						temp.A.position = punkt;
						temp.B.position = LinesInner.begin()->A.position;
						firstPoint = 1;
						Merged1 = 1;
						LinesInner.push_back(temp);
					}
					if (event.key.code == sf::Keyboard::V)
					{
						if (firstPoint)
						{
							if (LinesOuter.size() == 0)
							{

								temp.A.position = mouseCoords;
								firstPoint = 0;
							}
						}
						else
						{

							if (LinesOuter.size() == 0)
							{
								temp.B.position = mouseCoords;
								punkt = temp.B.position;
								LinesOuter.push_back(temp);
							}
							else
							{
								temp.A.position = punkt;
								temp.B.position = mouseCoords;
								punkt = temp.B.position;
								LinesOuter.push_back(temp);
							}

						}

					}
					if (event.key.code == sf::Keyboard::C && LinesOuter.size() > 0)
					{
						temp.A.position = punkt;
						temp.B.position = LinesOuter.begin()->A.position;
						firstPoint = 1;
						Merged2 = 1;
						LinesOuter.push_back(temp);
					}
				}
			}


			if (Merged1 && Merged2)
			{
				LinesInner.insert(LinesInner.end(), LinesOuter.begin(), LinesOuter.end());
				Merged1 = 0;

				std::ofstream myfile;
				myfile.open("Linie.csv");
				for (auto it : LinesInner)
				{
					myfile << it.A.position.x << "," << it.A.position.y << "," << it.B.position.x << "," << it.B.position.y << "\n";
				}
				myfile.close();
			}
			



			int temp_crashed = 0;
			
			if (exe && crashedCars < 50) {
				
				for (std::vector<Car>::iterator itt = Generation.begin(); itt < Generation.end(); itt++)
				{
					
				

					NN.init(itt->getWeights());	
					NN.reset();
		

					std::vector<Line> LinesCzujniki;
					std::vector<sf::Vector2f> test = itt->getCzujniki();
					sf::Vector2f pos = itt->getPosition();
					std::vector<double> czujnikiData;
					Line temp1;
					for (std::vector<sf::Vector2f>::iterator it = test.begin(); it < test.end(); it++)
					{
						temp1.A.position = pos;
						temp1.B.position = *it;
						LinesCzujniki.push_back(temp1);
					}


					
					double Data[5];
					int h = 0;
					for (auto it : LinesCzujniki)
					{
						if (h == 5) h = 0;

						bool flag = false;
						for (auto it2 : LinesInner)
						{
							flag = lineLineIntersection(it.A, it.B, it2.A, it2.B, pos);
							if (flag) break;
						}
						double odleglosc;
						if (flag)
						{
							odleglosc = sqrt(pow((itt->getPosition().x - pos.x), 2) + pow((itt->getPosition().y - pos.y), 2));
							Data[h] = 45 - odleglosc;
							if (h == 2) Data[h]= odleglosc;
							if (45 - odleglosc > 42) itt->setPosition();
						}

						else
							if (Data[h] != 0) { Data[h] = 1; }
						h++;

					}

					for (auto a : Data)
					{
						czujnikiData.push_back(a);
					}

					NN.networkUpdateInputs(czujnikiData);
					NN.transmit();


					switch (NN.networkOutput())
					{
					case 1: itt->rotate(2);
						break;
					case 2: itt->rotate(-2);
						break;
					case 3: itt->brake(); //Nie dziala
						break;
					case 4: itt->accelerate(); //Nie dziala
						break;

					}
					itt->accelerate();
					itt->update();
					if (itt->Crashed()) temp_crashed++;
					crashedCars = temp_crashed;
					


				}
			}

			if (exe && crashedCars == 50) {
				std::cout << "Generacja: " << GenerationCount << std::endl;
				GenerationCount++;
				once = 1;
				crashedCars = 0;
				temp_crashed = 0;

				sort(Generation.begin(), Generation.end(), [](Car a, Car b) {
					return a.getFitness() > b.getFitness();
				});


				int i = 0;
				std::vector<std::vector<double>> Wagi;
				std::vector<std::vector<double>> noweWagi;



				for (auto it : Generation)
				{

					if (i < 25) Wagi.push_back(it.getWeights());
					i++;
				
				}

				
				for (int a = 0; a < 23; a++)
				{
					i = (rand() % 55);
					if (i >= 0 && i < 24) { i = 0; }
					else if (i >= 24 && i < 35) { i = rand() % 5; }
					else if (i >= 35 && i < 45) { i = 4 + rand() % 7; }
					else if (i >= 45 && i < 52) { i = 11 + rand() % 8; }
					else if (i >= 52 && i < 55) { i = 18 + rand() % 7; }

					int j = 0;
					j = (rand() % 55);
					if (j >= 0 && j < 20) { j = 0; }
					else if (j >= 20 && j < 35) { j = rand() % 5; }
					else if (j >= 35 && j < 45) { j = 4 + rand() % 7; }
					else if (j >= 45 && j < 52) { j = 11 + rand() % 8; }
					else if (j >= 52 && j < 55) { j = 18 + rand() % 7; }

					if (i == j)
					{
						if (j == 24) j--;
						else j++;
					}

					std::vector<double> Data2;
					std::vector<double> Data1;
					std::vector<double> Mix;
					std::vector<double> Mix2;

					int ii = 0;
				

					for (std::vector<std::vector<double>>::iterator it = Wagi.begin(); it < Wagi.end(); it++)
					{

						if (ii == i)
						{

							for (std::vector<double>::iterator itt = (*it).begin(); itt < (*it).end(); itt++)

							{
								Data1.push_back(*itt);

							}
						
							
						}

						if (ii == j)
						{

							for (std::vector<double>::iterator itt = (*it).begin(); itt < (*it).end(); itt++)

							{
								Data2.push_back(*itt);

							}
						}
						ii++;
					}
					


					std::vector<double>::iterator it1 = Data1.begin();
					std::vector<double>::iterator it2 = Data2.begin();
					int swap = (rand() % 8) + 10;
				

					for (int i = 0; i < Data1.size(); i++)
					{
						int randMutacja = 95;
						if (swap < 0)
						{
							
							if (rand() % 101>randMutacja) Mix.push_back(rand() / (RAND_MAX + 1.));
							else Mix.push_back(*it2);
							if (rand() % 101>randMutacja) Mix2.push_back(rand() / (RAND_MAX + 1.));
							else Mix2.push_back(*it1);
						}
						else
						{
							if(rand()%101>randMutacja) Mix.push_back(rand() / (RAND_MAX + 1.));
							else Mix.push_back(*it1);
							if (rand() % 101>randMutacja) Mix2.push_back(rand() / (RAND_MAX + 1.));
							else Mix2.push_back(*it2);
						}
						it2++;
						it1++;
						swap--;

					}
					noweWagi.push_back(Mix);
					noweWagi.push_back(Mix2);

				}


				std::vector<double> temp;
				for (int i = 0; i < 2; i++)
				{
					for (int j = 0; j < 32; j++)
					{
						temp.push_back(rand() / (RAND_MAX + 1.));

					}
					noweWagi.push_back(temp);
					temp.clear();
				}


			
				std::vector<std::vector<double>>::iterator it3 = Wagi.begin();
				for (int i = 0; i < 2; i++)
				{
					noweWagi.push_back(*it3);

				}
			

				std::vector<Car>::iterator it = Generation.begin();
				std::vector<std::vector<double>>::iterator itt = noweWagi.begin();
			
				while (it < Generation.end() && itt < noweWagi.end())
				{
					it->setWeights(*itt);

					it++;
					itt++;
	
				}
				int licznik = 0;
				for (std::vector<Car>::iterator it = Generation.begin(); it < Generation.end(); it++)
				{
					it->reset();
					
				}
				
				
			
				
				
			}
			
			
		

		






			window.clear();		
			for (auto it : LinesInner)
			{
				sf::Vertex line[] =
				{
					sf::Vertex(it.A.position,sf::Color::Yellow),
					sf::Vertex(it.B.position,sf::Color::Yellow)
				};
				window.draw(line, 2, sf::Lines);
			}
			for (auto it : LinesOuter)
			{
				sf::Vertex line[] =
				{
					sf::Vertex(it.A.position,sf::Color::Yellow),
					sf::Vertex(it.B.position,sf::Color::Yellow)
				};
				window.draw(line, 2, sf::Lines);
			}		
			for (auto it : Generation)
			{
				it.draw(window);
			}
			window.display();
			
		}

		return 0;
}

