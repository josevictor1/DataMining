#include <cstdint>

#include "population.h"

#define HELP 1E-3

using namespace std;

Population::Population() {}
void Population::generate(){
    for (size_t i = 0; i < POPULATION_SIZE; i++) {
        individuals[i].shuffle(random);
        individuals[i].calcFitness(clas);
        // std::cout << "FITNESS" << individuals[i].getFitness()<< '\n';
    }

    //for (size_t i = 0; i < POPULATION_SIZE; i++) {
        //for (size_t j = 0; j < 34; j++) {
            //std::cout << individuals[i].getGene(j).weight << '\n';
        //}
    //}

}
void Population::setClass(int n){
    clas = n;
}
// std::vector<Individual>
void Population::select() {
    // bool repeated;
    double total = 0, sum = 0;
    // std::vector<Individual> result;
    // Random r;
    for (size_t i = 0; i < POPULATION_SIZE; i++) {
        total += individuals[i].getFitness() + HELP;
    }

    Distribution roulette = Distribution(0, total);

    for (size_t i = POPULATION_SIZE; i < POPULATION_MAX; i++) {
        Individual aux;
        int l = 0;
        for (size_t j = 0; j < TOUR; j++) {
            // int64_t select = int64_t(random())%int64_t(total);
            double select = roulette(random);
            sum = individuals[l].getFitness() + HELP;

            while (sum < select) {
                l++;
                l %= POPULATION_SIZE;
                sum += individuals[l].getFitness() + HELP;
            }

            if (individuals[l].getFitness() > aux.getFitness()){
                //std::cout << individuals[l%TCROSS].getFitness() << '\n';
                aux = individuals[l];
            }
        }

        if ((i % 2 == 1) and (individuals[i - 1] == aux))   // (result.back() == aux))
            i--;

        else
            individuals[i] = aux;
            // result.push_back(aux);
    }
    // return result;

    /*for (size_t i = POPULATION_SIZE; i < POPULATION_MAX; i++)
        clog << "individuals "<< individuals[i].getFitness()<< endl;*/
}
void Population::crossover() {  // (std::vector<Individual> parents) {
    /*clog << "Before" << endl;
    for (size_t i = 0; i < POPULATION_MAX; i++) {
        for (size_t j = 0; j < 34; j++) {
            std::clog << individuals[i].getGene(j).weight << ' ';   //'\n';
        }
        clog << endl;
    }*/

    for (size_t i = POPULATION_SIZE; i < POPULATION_MAX; i = i + 2) {

        int p1 = (random()%34), p2 = (random()%34),aux;

        while(p1 == p2){
            p2 = (random()%34);
        }
        if(p1 > p2){
            aux = p1;
            p1 = p2;
            p2 = p1;
        }

        /*clog.precision(3);
        // clog << "Before" << endl;
        for (size_t j = 0; j < 34; j++) {
            std::clog << fixed << individuals[i].getGene(j).weight << ' ';
        }
        clog << endl;
        for (size_t j = 0; j < 34; j++) {
            std::clog << fixed << individuals[i+1].getGene(j).weight << ' ';
        }
        clog << endl;
        clog << "Start = " << p1 << " End = " << p2 << endl;*/

        for (size_t j = 0; j < 34; j++) {
            /*if (j >= p1 and j <= p2) {
                individuals[i-1].setGene(j, individuals[j].getGene(j));
                individuals[i].setGene(j, individuals[i-1].getGene(j));
            }*/
            if (j >= p1 and j <= p2)
                individuals[i].swapGene(individuals[i + 1], j);
        }
        /*clog << "After" << endl;
        for (size_t j = 0; j < 34; j++) {
            std::clog << fixed << individuals[i].getGene(j).weight << ' ';
        }
        clog << endl;
        for (size_t j = 0; j < 34; j++) {
            std::clog << fixed << individuals[i+1].getGene(j).weight << ' ';
        }*/
        //mutação conferida ... resultados no arquivo
        mutate(i);
        mutate(i+1);
        individuals[i].calcFitness(clas);
        individuals[i+1].calcFitness(clas);

        /*clog << "\nAfter with mutation" << endl;
        for (size_t j = 0; j < 34; j++) {
            std::clog << fixed << individuals[i].getGene(j).weight << ' ';
        }
        clog << endl;
        for (size_t j = 0; j < 34; j++) {
            std::clog << fixed << individuals[i+1].getGene(j).weight << ' ';
        }
        clog << endl << endl;*/

        //std::cout << "1 - fit " << individuals[i-1].getFitness() << '\n';
        //std::cout << "2 - fit " << individuals[i].getFitness() << '\n';
    }

    /*clog << "After" << endl;
    for (size_t i = 0; i < POPULATION_MAX; i++) {
        for (size_t j = 0; j < 34; j++) {
            std::clog << individuals[i].getGene(j).weight << ' ';   //'\n';
        }
        clog << endl;
    }*/
}


void Population::mutate(int n){
    static Distribution delta = Distribution(-0.1, 0.1);
    Gene aux;
    for (size_t j = 0; j < 34; j++) {
        if(random()%100 < 30){
            /*double value = delta(random);
            if(individuals[n].getGene(j).weight < value){
                aux = individuals[n].getGene(j);
                aux.weight = aux.weight + value;
                aux.weight > 1 ? aux.weight = aux.weight - 1: aux.weight;
                individuals[n].setGene(j,aux);
            }
            else{
                aux = individuals[n].getGene(j);
                aux.weight = aux.weight - value;
                individuals[n].setGene(j,aux);
            }*/
            double value = delta(random);
            aux = individuals[n].getGene(j);
            aux.weight += value;
            individuals[n].setGene(j,aux);
        }
        if(random()%100 < 30){
            aux = individuals[n].getGene(j);
            aux.op = Operator(random()%N_OPERATORS);
            individuals[n].setGene(j,aux);
        }
        if(random()%100 < 30){
            aux = individuals[n].getGene(j);

            switch (j) {
                case 10:
                    aux.value = random() % 2;
                    break;

                case 33:
                    aux.value = random() % 80;
                    break;

                default:
                    aux.value = random()%4;
                    break;
            }

            individuals[n].setGene(j,aux);
        }
    }

    // individuals[n].calcFitness(clas);
}

/*
void Population::mutate() {

    Distribution roulette = Distribution(0, 1);
    Gene aux;
    for (size_t i = POPULATION_SIZE; i < POPULATION_MAX; i++){
        for (size_t j = 0; j < 34; j++) {
            if(random()%100 <= 30){
                float value = roulette(random);
                if(individuals[i].getGene(j).weight < value){
                    aux = individuals[i].getGene(j);
                    aux.weight = aux.weight + value;
                    aux.weight > 1 ? aux.weight = aux.weight - 1: aux.weight;
                    individuals[i].setGene(j,aux);
                }
                else{
                    aux = individuals[i].getGene(j);
                    aux.weight = aux.weight - value;
                    individuals[i].setGene(j,aux);
                }
            }
            if(random()%100 <= 30){
                aux = individuals[i].getGene(j);
                aux.op = Operator(random()%N_OPERATORS);
                individuals[i].setGene(j,aux);
            }
            if(random()%100 <= 30){
                aux = individuals[i].getGene(j);
                aux.value = random()%4;
                individuals[i].setGene(j,aux);
            }
        }
    }
}
*/
void Population::reinsert() {

    for (size_t i = 1; i < POPULATION_SIZE; i++) {
        //std::cout << " primeiro"<<individuals[0].getFitness() <<'\n';
        if(individuals[i].getFitness() > individuals[0].getFitness()){
            individuals[0] = individuals[i];
        }
        individuals[i] = individuals[i+POPULATION_SIZE];
    }

}

Individual Population::getIndividual(int n){
    return individuals[n];
}
