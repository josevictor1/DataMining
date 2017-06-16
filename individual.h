#pragma once

#include <random>
#include <vector>
#include "gene.h"

#define DEFAULT_FITNESS -1.0

using Distribution = std::uniform_real_distribution<double>;
using Random = std::default_random_engine;

struct Patient {
	int values[35];
};

class Individual {
	static std::vector<Patient> data;
	Gene genes[34];
	double fitness = DEFAULT_FITNESS;

public:
	Individual();
	Individual(int clas);
	void shuffle(Random& random);
	void calcFitness(int clas);
	double getFitness();
	double getFitness(int clas);
	void setGene(int position, Gene gene);
	Gene getGene(int position);
	void swapGene(Individual& other, int gene_i);
	bool operator==(const Individual& other);
	void getRegra();
};
