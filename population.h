#pragma once

#include "individual.h"
#include <iostream>

#define POPULATION_SIZE 50
#define TCROSS int(POPULATION_SIZE*1)
#define POPULATION_MAX POPULATION_SIZE+TCROSS
#define TOUR 3

class Population {
	Individual individuals[POPULATION_SIZE+TCROSS];
	Random random;
	int clas;

public:
	Population();
	void setClass(int n);
	void generate();
	void select();
	// std::vector<Individual> select();
	void crossover();
	// void crossover(std::vector<Individual> parents);
	// void mutate();
	void mutate(int n);
	void reinsert();
	Individual getIndividual(int n);
};
