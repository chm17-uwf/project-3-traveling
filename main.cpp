#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "bruteforce.hpp"
#include "ga.hpp"
using namespace std;

void setCW(double a[][20]);
void getInput(int&, int&, int&, int&);

int main(){
	double cw[20][20];
	int c, t, g, p;
	double optimal, tempTime;
	setCW(cw);
	
	struct timeval * time;
	time = (struct timeval *)malloc(sizeof(struct timeval));	

	/*for(int i = 0; i < 20; i++){
		for(int j = 0; j < 20; j++){
			cout << cw[i][j] << " ";
		}
		cout << endl;
	}*/

	getInput(c,t,g,p);	
	cout << "----------Running simulation for " << c << " cities!----------" << endl;
	
	gettimeofday(time,NULL);
	time_t startSec = time->tv_sec;
	time_t startuSec = time->tv_usec;
	
	BruteForce bf(cw, c);
	optimal = bf.run();
	gettimeofday(time,NULL);	
	cout << "Optimal Cost from Brute Force: " << optimal << endl;
	tempTime = ((double)time->tv_sec-startSec) + (((double)time->tv_usec-startuSec)*0.000001);
	cout << "Time for Brute Force(s): " << tempTime << endl;
	
	GeneticAlg ga(cw, c, t, g, p);
	ga.run();
	ga.printGens();
	
	free(time);
	return 0;
}

void getInput(int& c, int& t, int& g, int& p){
	cout << "Please enter the number of cities to simulate(<=19): ";
	cin >> c;
	cout << endl;
	while(c > 19 || c < 1){
		cout << "Invalid size please re-enter: ";
		cin >> c;
		cout << endl;
	}
	cout << "----------Genetic Parameters----------" << endl;
	cout << "Please enter the number of tours in a generation(>=2): ";
	cin >> t;
	cout << endl << endl;;
	while(t < 2){
		cout << "Invalid size please re-enter: ";
		cin >> t;
		cout << endl << endl;
	}
	cout << "Please enter the number of generations to run(>0): ";
	cin >> g;
	cout << endl << endl;;
	while(g < 1 ){
		cout << "Invalid size please re-enter: ";
		cin >> g;
		cout << endl << endl;
	}
	cout << "Please enter the percentage of a generation that should be mutations(0-100): ";
	cin >> p;
	cout << endl << endl;;
	while(p < 0 || p > 100 ){
		cout << "Invalid size please re-enter: ";
		cin >> p;
		cout << endl << endl;
	}
}

void setCW(double a[][20]){
	ifstream inFile;
	inFile.open("distances.txt");
	if(inFile.is_open()){
		double temp;
		for(int i = 0; i < 20; i++){
			for(int j = 0; j < 20; j++){
				if(i == j){
					a[i][j] = -1.0;
				} else {
					inFile >> temp;
					a[i][j] = temp;
				}
			}
		}
	} else {
		cout << "Couldn't Find \"distances.txt\"!" << endl;
	}
	inFile.close();
}
