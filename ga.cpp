#include "ga.hpp"
#include <iostream>

GeneticAlg::GeneticAlg(double a[20][20], int n, int t, int g, int p){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			cw[i][j] = a[i][j];
		}
	}
	numCities = n;
	numTours = t;
	numGen = g;
	percentMut = p;
	
	genA = new int*[numTours];
	genB = new int*[numTours];
	costs = new double[numTours];
	currentGen = 'A';
	for(int i = 0; i < numTours; i++){
		genA[i] = new int[numCities];
		genB[i] = new int[numCities];
	}
	
}

void GeneticAlg::setCosts(){
	if(currentGen == 'A'){
		for(int i = 0; i < numTours; i++){
			costs[i] = calctourCost(genA[i]);
		}	
	} else {
		for(int i = 0; i < numTours; i++){
			costs[i] = calctourCost(genB[i]);
		}		
	}
}

void GeneticAlg::printGens(){
	if(currentGen == 'A'){
		std::cout << "Generation A: " << std::endl;
		for(int i = 0; i < numTours; i++){
			for(int j = 0; j < numCities; j++){
				std::cout << genA[i][j] << " ";
			}
			std::cout << costs[i];
			std::cout << std::endl;
		}	
	}else {
		std::cout << std::endl << "Generation B: " << std::endl;
		for(int i = 0; i < numTours; i++){
			for(int j = 0; j < numCities; j++){
				std::cout << genB[i][j] << " ";
			}
			std::cout << costs[i];
			std::cout << std::endl;
		}	
	}
	std::cout << std::endl;
}

double GeneticAlg::run(){
	int e1 = 0;
	int e2 = 0;
	initializeGenA();
	setCosts();
	setElites(e1, e2);
}

void GeneticAlg::setElites(int& e1, int& e2){
	for(int i = 0; i < numTours; i++){
		if(costs[i] < costs[e1]){
			e1 = i;
		}
	}
	for(int i = 0; i < numTours; i++){
		if(costs[i] < costs[e2] && costs[i] != costs[e1]){
			e2 = i;
		}
	}
}

void GeneticAlg::initializeGenA(){
	for(int i = 0; i < numTours; i++){
		for(int j = 0; j < numCities; j++){
			genA[i][j] = j+1;
		}
	}
	for(int i = 1; i < numTours; i++){
		makePerm(genA[i], i);
	}
}

void GeneticAlg::makePerm(int* tour, int n){
    int m, k, p , q;
    long long i;
    for(i = 0; i < n; i++)
    {
    	m = numCities - 2;
    	while(tour[m]>tour[m+1])
    	{
    		m = m - 1;
    	}
    	k = numCities-1;
    	while(tour[m] > tour[k])
    	{
    		k = k - 1;
    	}
    	swapCities(tour,m,k);
    	p = m + 1;
    	q = numCities-1;
    	while( p < q)
    	{
    		swapCities(tour,p,q);
    		p++;
      		q--;
    	}
    }
}

double GeneticAlg::calctourCost(int* tour){
	double sum = 0;
	sum += cw[0][tour[0]];
	for(int i = 0; i < numCities-1; i++){
		sum += cw[tour[i]][tour[i+1]];
	}
	sum += cw[tour[numCities-1]][0];
	return sum;	
}

void GeneticAlg::swapCities(int* tour, int c1, int c2){
	int temp = tour[c1];
	tour[c1] = tour[c2];
	tour[c2] = temp;
}

void GeneticAlg::copyTour(int* t1, int* t2){
	for(int i = 0; i < numCities; i++){
		t2[i] = t1[i];
	}
}

GeneticAlg::~GeneticAlg(){
	for(int i = 0; i < numTours; i++){
		delete [] genA[i];
		delete [] genB[i];
	}
	delete [] genA;
	delete [] genB;
	
	delete [] costs;
}
