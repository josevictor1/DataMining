#include "population.h"
#include <iostream>

#define GENERATIONS 50

using namespace std;

int main(int argc, char const *argv[]) {
	// Random r;
	Population p;
	Individual max[6];
	// int flag;
	for (size_t i = 0; i < 6; i++) {
		p.setClass(i+1);
		// flag = 0;
		for (size_t j = 0; j < 10; j++) {
			p.generate();
			for (size_t k = 0; k < GENERATIONS; k++) {
			// std::vector<Individual> parents =
				p.select();

			/*for(Individual& i: parents){
				std::clog << "individuals "<< i.getFitness()<< endl;
			}*/

				p.crossover();	// parents);
			/*
			std::cout << "After" << endl;
			for(size_t i = 0; i < POPULATION_SIZE; i++){
				std::cout << "individuals "<< p.getIndividual(i).getFitness() << endl;
			}*/
				p.reinsert();
			/*
			std::cout << "Before" << endl;
			for(size_t i = 0; i < POPULATION_SIZE; i++){
				std::cout << "individuals "<< p.getIndividual(i).getFitness() << endl;
			}*/
			}

			/*if(flag == 0){
				max[i] = p.getIndividual(0);
			}
			else*/
			if(p.getIndividual(0).getFitness() > max[i].getFitness()){
				max[i] = p.getIndividual(0);
			}
		}

	}
	// Individual i;
	// cout << "Fitness = " << Individual(1).getFitness(1) << endl;
	// cout << "Fitness = " << Individual(2).getFitness(2) << endl;
	// cout << "Fitness = " << Individual(3).getFitness(3) << endl;
	// cout << "Fitness = " << Individual(4).getFitness(4) << endl;
	// cout << "Fitness = " << Individual(5).getFitness(5) << endl;
	// cout << "Fitness = " << Individual(6).getFitness(6) << endl;

	for (size_t i = 0; i < 6; i++) {
		std::cout << "Classe "<< i + 1 << endl;
		std::cout << "Fitness = " << max[i].getFitness() << endl;
		max[i].getRegra();
		std::cout << endl;
	}

	return 0;
}
