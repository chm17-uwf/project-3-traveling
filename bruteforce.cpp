#include <iostream>
#include "bruteforce.hpp"

BruteForce::BruteForce(double a[20][20], int numCities){
	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			cw[i][j] = a[i][j];
		}
	}
	this->numCities = numCities;
	tour = new int[numCities];
	for(int i = 0; i < numCities; i++){
		tour[i] = i+1;
	}
}

double BruteForce::run(){
	long long n = factorial(numCities);
	double optimal = calctourWeight();
    int m, k, p , q;
    long long i;
    for(i = 1; i < n; i++)
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
    	swapCities(m,k);
    	p = m + 1;
    	q = numCities-1;
    	while( p < q)
    	{
    		swapCities(p,q);
    		p++;
      		q--;
    	}
    	if(calctourWeight() < optimal){
    		optimal = calctourWeight();
		}
    }
	return optimal;
}

double BruteForce::calctourWeight(){
	double sum = 0;
	sum += cw[0][tour[0]];
	for(int i = 0; i < numCities-1; i++){
		sum += cw[tour[i]][tour[i+1]];
	}
	sum += cw[tour[numCities-1]][0];
	return sum;
}

BruteForce::~BruteForce(){
	delete [] tour;
}

void BruteForce::printTour(){
	std::cout << "0";
	for(int i = 0; i < numCities; i++){
		std::cout << tour[i];
	}
	std::cout << "0";
}

void BruteForce::swapCities(int i1, int i2){
	int temp;
	temp = tour[i1];
	tour[i1] = tour[i2];
	tour[i2] = temp;
}

long long BruteForce::factorial(int n){
	if(n == 1){
		return 1;
	} else {
		return factorial(n-1) * n;
	}
}
