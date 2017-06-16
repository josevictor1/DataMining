#include <fstream>
#include <iostream>
#include <utility>
#include "individual.h"

#define WEIGHT_LIMIT 0.7

using namespace std;

auto Individual::data = vector<Patient>();

Individual::Individual() {
	if ( data.empty() ) {
		ifstream file;

		try {
			file.open("dermatology.train");	//, ifstream::in);

			// for (int i = 0; i < 366; i++) {
			while ( file.good() ) {
				Patient p;

				for (int j = 0; j < 35; j++)
					file >> p.values[j];

				data.push_back(p);
			}
		}

		catch (exception&) {}

		file.close();

		// clog << data.size() << endl;
		// clog << data[0].values[0] << endl;
		// clog << data[358].values[0] << endl;
		/*for (auto& patient: data) {
			for (int j = 0; j < 34; j++)
				clog << patient.values[j] << ' ';
			clog << patient.values[34] << endl;
		}*/
	}
}

Individual::Individual(int clas) {
	/*
	for (int i = 0; i < 34; i++)
		genes[i].weight = double(i + i) / 100.;

	switch (clas) {
		case 1:
			// melanin incontinence
			genes[11].weight = 0.75;
			genes[11].op = EQUAL;
			genes[11].value = 0;

			// clubbing of the rete ridges
			genes[19].weight = 0.75;
			genes[19].op = GREATEREQUAL;
			genes[19].value = 1;

			break;

		case 2:
			// fibrosis of the papillary dermis
			genes[14].weight = 0.75;
			genes[14].op = EQUAL;
			genes[14].value = 0;

			// spongiosis
			genes[27].weight = 0.75;
			genes[27].op = DIFFERENT;
			genes[27].value = 0;

			// saw-tooth appearance of retes
			genes[28].weight = 0.75;
			genes[28].op = EQUAL;
			genes[28].value = 0;

			// perifollicular parakeratosis
			genes[30].weight = 0.75;
			genes[30].op = EQUAL;
			genes[30].value = 0;

			break;

		case 3:
			// spongiform pustule
			genes[22].weight = 0.75;
			genes[22].op = EQUAL;
			genes[22].value = 0;

			// band-like infiltrate
			genes[32].weight = 0.75;
			genes[32].op = GREATEREQUAL;
			genes[32].value = 2;

			break;

		case 4:
			// oral mucosal involvement
			genes[7].weight = 0.75;
			genes[7].op = EQUAL;
			genes[7].value = 0;

			// knee and elbow involvement
			genes[8].weight = 0.75;
			genes[8].op = EQUAL;
			genes[8].value = 0;

			// melanin incontinence
			genes[11].weight = 0.75;
			genes[11].op = GREATEREQUAL;
			genes[11].value = 0;

			// elongation of the rete ridges
			genes[20].weight = 0.75;
			genes[20].op = EQUAL;
			genes[20].value = 0;

			break;

		case 5:
			// oral mucosal involvement
			genes[7].weight = 0.75;
			genes[7].op = EQUAL;
			genes[7].value = 0;

			// fibrosis of the papillary dermis
			genes[14].weight = 0.75;
			genes[14].op = DIFFERENT;
			genes[14].value = 0;

			break;

		case 6:
			// hyperkeratosis
			genes[17].weight = 0.75;
			genes[17].op = GREATEREQUAL;
			genes[17].value = 0;

			// perifollicular parakeratosis
			genes[30].weight = 0.75;
			genes[30].op = DIFFERENT;
			genes[30].value = 0;

			break;

		default: break;
	}
	*/

	/*for (int i = 0; i < 34; i++)
		clog << "Gene " << i << ":\t" << genes[i].weight << '\t' << genes[i].op << '\t' << genes[i].value << endl;
	clog << endl;*/
}

void Individual::shuffle(Random& random) {
	static Distribution zero_to_one = Distribution(0, 1);

	for (int i = 0; i < 34; i++) {
		genes[i].weight = zero_to_one(random);	 // double(random() % 11) / 10;
		genes[i].op = Operator(random() % N_OPERATORS);
		genes[i].value = random() % 4;
	}

	genes[10].value = random() % 2;	// atributo 11 (historico familiar)
	genes[33].value = random() % 80;	// atributo 34 (idade)
	// Idade variando de 0 a 79, dado presente na terceira página(nas três primeiras linhas do primeiro paragrafo da coluna esquerda) do Artigo em portugês
	fitness = DEFAULT_FITNESS;

	/*for (int i = 0; i < 34; i++)
		clog << "Gene " << i << ":\t" << genes[i].weight << '\t' << genes[i].op << '\t' << genes[i].value << endl;
	clog << endl;*/
}

void Individual::calcFitness(int clas) {
	double sensitivity, specificity;
	double false_positive = 0;
	double false_negative = 0;
	double true_positive = 0;
	double true_negative = 0;
	bool triggered;
	int sum;

	for (auto& patient: data) {
		triggered = true;

		for (int i = 0; triggered and (i < 34); i++)
			//std::cout << "pesos"<< genes[i].weight << '\n';

			if (genes[i].weight > WEIGHT_LIMIT)
				//std::cout << "pesos"<< genes[i].weight << '\n';
				switch (genes[i].op) {
					case EQUAL:
						triggered = patient.values[i] == genes[i].value;
						break;

					case DIFFERENT:
						triggered = patient.values[i] != genes[i].value;
						break;

					case LESS:
						triggered = patient.values[i] < genes[i].value;
						break;

					case GREATEREQUAL:
						triggered = patient.values[i] >= genes[i].value;
						break;

					default: break;
				}

		if (triggered) {
			if (patient.values[34] == clas)
				true_positive++;

			else
				false_positive++;
		}

		else {
			if (patient.values[34] == clas)
				false_negative++;

			else
				true_negative++;
		}
	}

	sum = true_negative + false_positive;
	if(sum != 0){
		specificity = true_negative / sum;
	}
	else{
		specificity = true_negative / 1;
	}
	sum = true_positive + false_negative;
	if(sum != 0){
		sensitivity = true_positive / sum;
	}
	else{
		sensitivity = true_positive / 1;
	}
	fitness = sensitivity * specificity;

	// clog << "True Positive = " << true_positive;
	// clog << "\tTrue Negative = " << true_negative;
	// clog << "\tFalse Positive = " << false_positive;
	// clog << "\tFalse Negative = " << false_negative;
	// clog << "\tSensitivity = " << sensitivity;
	// clog << "\tSpecificity = " << specificity;
	// clog << endl;	// '\t';
}

double Individual::getFitness(){
	return fitness;
}

double Individual::getFitness(int clas){
	calcFitness(clas);
	return fitness;
}

void Individual::setGene(int position, Gene gene){
	genes[position] = gene;
}

Gene Individual::getGene(int position){
	return genes[position];
}

void Individual::swapGene(Individual& other, int gene_i) {
	swap(this->genes[gene_i], other.genes[gene_i]);
}

bool Individual::operator==(const Individual& other) {
	bool result = true;

	for (int i = 0; result and (i < 34); i++)
		result = this->genes[i].weight == other.genes[i].weight and
				 this->genes[i].op == other.genes[i].op and
				 this->genes[i].value == other.genes[i].value;

	return result;
}

void Individual::getRegra(){
	for (size_t i = 0; i < 34; i++) {
		if(genes[i].weight > 0.7){
			switch (i){
				case 0:
					std::cout <<  "erythema";
					break;
				case 1:
					std::cout <<  "scaling";
					break;
				case 2:
					std::cout <<  "definite borders";
					break;
				case 3:
					std::cout << "itching";
					break;
				case 4:
					std::cout <<  "koebner phenomenon";
					break;
				case 5:
					std::cout <<  "polygonal papules";
					break;
				case 6:
					std::cout <<  "follicular papules";
					break;
				case 7:
					std::cout <<  "oral mucosal involvement";
					break;
				case 8:
					std::cout <<  "knee and elbow involvement";
					break;
				case 9:
					std::cout <<  "scalp involvement";
					break;
				case 10:
					std::cout <<  "family history, (0 or 1)";
					break;
				case 11:
					std::cout <<  "melanin incontinence";
					break;
				case 12:
					std::cout <<  "eosinophils in the infiltrate";
					break;
				case 13:
					std::cout <<  "PNL infiltrate";
					break;
				case 14:
					std::cout <<  "fibrosis of the papillary dermis";
					break;
				case 15:
					std::cout <<  "exocytosis";
					break;
				case 16:
					std::cout <<  "acanthosis";
					break;
				case 17:
					std::cout <<  "hyperkeratosis";
					break;
				case 18:
					std::cout <<  "parakeratosis";
					break;
				case 19:
					std::cout <<  "clubbing of the rete ridges";
					break;
				case 20:
					std::cout <<  "elongation of the rete ridges";
					break;
				case 21:
					std::cout <<  "thinning of the suprapapillary epidermis";
					break;
				case 22:
					std::cout <<  "spongiform pustule";
					break;
				case 23:
					std::cout <<  "munro microabcess";
					break;
				case 24:
					std::cout <<  "focal hypergranulosis";
					break;
				case 25:
					std::cout <<  "disappearance of the granular layer";
					break;
				case 26:
					std::cout <<  "vacuolisation and damage of basal layer";
					break;
				case 27:
					std::cout <<  "spongiosis";
					break;
				case 28:
					std::cout <<  "saw-tooth appearance of retes";
					break;
				case 29:
					std::cout <<  "follicular horn plug";
					break;
				case 30:
					std::cout <<  "perifollicular parakeratosis";
					break;
				case 31:
					std::cout <<  "inflammatory monoluclear inflitrate";
					break;
				case 32:
					std::cout <<  "band-like infiltrate";
					break;
				case 33:
					std::cout <<  "Age (linear)";
					break;
			}

			switch (genes[i].op) {
				case EQUAL:
					std::cout << " = ";
					break;

				case DIFFERENT:
					std::cout << " != ";
					break;

				case LESS:
					std::cout << " < ";
					break;

				case GREATEREQUAL:
					std::cout << " >= ";
					break;

				default: break;
			}

			std::cout << genes[i].value << '\n';
		}
	}

}
