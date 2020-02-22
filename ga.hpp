#ifndef GA_HPP
#define GA_HPP

class GeneticAlg{
	private:
		double cw[20][20];
		int numCities, numTours, numGen, percentMut;
		int** genA;
		int** genB;
		double* costs;
		char currentGen;
		void copyTour(int*, int*);
		void makePerm(int*, int);
		void swapCities(int*, int, int);
		double calctourCost(int*);
		void initializeGenA();
		void setCosts();
		void setElites(int&, int&);
	public:
		GeneticAlg(double cw[20][20], int, int, int, int);
		~GeneticAlg();
		double run();
		void printGens();
};

#endif
