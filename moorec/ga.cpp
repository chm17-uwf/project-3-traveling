#include "ga.hpp"
#include <iostream>
#include <stdlib.h>

GeneticAlg::GeneticAlg(double a[20][20], int n, int t, int g, int p, bool e){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			cw[i][j] = a[i][j];
		}
	}
	numCities = n;
	numTours = t;
	numGen = g;
	percentMut = p;
	
	gen = new int*[numTours];
	costs = new double[numTours];
	for(int i = 0; i < numTours; i++){
		gen[i] = new int[numCities];
	}
	mutateElites = e;
	base = new int[numCities];
	for(int i = 0; i < numCities; i++){
		base[i] = i+1;
	}
}

void GeneticAlg::setCosts(){
	for(int i = 0; i < numTours; i++){
		costs[i] = calctourCost(gen[i]);
	}	
}

void GeneticAlg::printGen(){
	std::cout << "Generation: " << std::endl;
	for(int i = 0; i < numTours; i++){
		for(int j = 0; j < numCities; j++){
			std::cout << gen[i][j] << " ";
		}
		std::cout << costs[i];
		std::cout << std::endl;
	}	
	std::cout << std::endl;
}

double GeneticAlg::run(){
	int e1 = 0;
	int e2 = 0;
	int numMut = (numTours-2)*0.01*percentMut;
	initializeGen();
	
	for(int i = 0; i < numGen; i++){
		setCosts();
		setElites(e1, e2);
		swapTours(e1, 0);
		swapTours(e2, 1);
		e1 = 0;
		e2 = 1;
		for(int i = 2+numMut; i < numTours; i++){
			makePerm(gen[i], 1);
		}
		
		if(mutateElites){
			for(int i = 2; i < 2+numMut; i++){
				copyTour(gen[0], gen[i]);
			}	
		}
		
		for(int i = 2; i < 2+numMut; i++){
			mutateTour(gen[i], 2);
		}
		
		
		setCosts();
	}
	
	if(costs[e2] < costs[e1]){
		return costs[e2];
	} else {
		return costs[e1];
	}

}

void GeneticAlg::copyTour(int t1, int t2){
	for(int i = 0; i < numCities; i++){
		gen[t2][i] = gen[t1][i];
	}
}

void GeneticAlg::swapCosts(int c1, int c2){
	double temp = costs[c1];
	costs[c1] = costs[c2];
	costs[c2] = temp;
}

void GeneticAlg::swapTours(int t1, int t2){
	int* temp = new int[numCities];
	
	for(int i = 0; i < numCities; i++){
		temp[i] = gen[t1][i];
		gen[t1][i] = gen[t2][i];
		gen[t2][i] = temp[i];
	}
	
	delete [] temp;
	
	swapCosts(t1, t2);
	
}

void GeneticAlg::mutateTour(int* tour, int n){
	for(int i = 0; i < n; i++){
		int n1, n2;
		n1 = rand() % ((numCities/2)+1);
		n2 = rand() % (numCities);
	
		while(n2 == n1){
			n2 = rand() % (numCities);	
		}
	
		swapCities(tour, n1, n2);
	}
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

void GeneticAlg::initializeGen(){
	copyTour(base, gen[0]);
	for(int i = 1; i < numTours; i++){
		makePerm(gen[i], 1);
	}
}

void GeneticAlg::makePerm(int* tour, int n){
    int m, k, p , q;
    long long i;
    for(i = 0; i < n; i++)
    {
    	m = numCities - 2;
    	while(base[m]>base[m+1])
    	{
    		m = m - 1;
    	}
    	k = numCities-1;
    	while(base[m] > base[k])
    	{
    		k = k - 1;
    	}
    	swapCities(base,m,k);
    	p = m + 1;
    	q = numCities-1;
    	while( p < q)
    	{
    		swapCities(base,p,q);
    		p++;
      		q--;
    	}
    	if(checkPerm(base)){
    		resetPerm(base);
		}
    }
    copyTour(base, tour);
    
}

void GeneticAlg::resetPerm(int* tour){
	for(int i = 0; i < numCities; i++){
		tour[i] = i+1;
	}
}

bool GeneticAlg::checkPerm(int* tour){
	for(int i = 0; i < numCities; i++){
		if(tour[i] == 0){
			return true;
		}
	}
	return false;
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
		delete [] gen[i];
	}
	delete [] gen;
	
	delete [] costs;
}
