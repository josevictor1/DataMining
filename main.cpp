#include "population.h"
#include <iostream>
#define GENERATIONS 50

using namespace std;



int main(int argc, char const *argv[]) {
	Random r;
	Population p;

	p.setClass(1);
	p.generate();

	for (size_t i = 0; i < GENERATIONS; i++) {
		/* code */

		// std::vector<Individual> parents =
		p.select();

		/*for(Individual& i: parents){
			std::clog << "individuals "<< i.getFitness()<< '\n';
		}*/

		p.crossover();	// parents);
		std::cout << "After" << '\n';
		for(size_t i = 0; i < POPULATION_SIZE; i++){
			std::cout << "individuals "<< p.getIndividual(i).getFitness() << '\n';
		}
		p.reinsert();
		std::cout << "Before" << '\n';
		for(size_t i = 0; i < POPULATION_SIZE; i++){
			std::cout << "individuals "<< p.getIndividual(i).getFitness() << '\n';
		}
	}
	// Individual i;
	// cout << "Fitness = " << Individual(1).getFitness(1) << endl;
	// cout << "Fitness = " << Individual(2).getFitness(2) << endl;
	// cout << "Fitness = " << Individual(3).getFitness(3) << endl;
	// cout << "Fitness = " << Individual(4).getFitness(4) << endl;
	// cout << "Fitness = " << Individual(5).getFitness(5) << endl;
	// cout << "Fitness = " << Individual(6).getFitness(6) << endl;

	return 0;
}
