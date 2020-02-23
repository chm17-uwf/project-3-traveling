#ifndef GA_HPP
#define GA_HPP

class GeneticAlg{
	private:
		double cw[20][20];
		int numCities, numTours, numGen, percentMut;
		int** gen;
		int* base;
		double* costs;
		bool mutateElites;
		void copyTour(int*, int*);
		void makePerm(int*, int);
		void swapCities(int*, int, int);
		double calctourCost(int*);
		void initializeGen();
		void setCosts();
		void setElites(int&, int&);
		void mutateTour(int*, int);
		void swapTours(int, int);
		void swapCosts(int ,int);
		void copyTour(int, int);
		bool checkPerm(int*);
		void resetPerm(int*);
	public:
		GeneticAlg(double cw[20][20], int, int, int, int, bool);
		~GeneticAlg();
		double run();
		void printGen();
};

#endif
