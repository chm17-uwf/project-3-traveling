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
}
