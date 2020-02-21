#ifndef BRUTE_HPP
#define BRUTE_HPP

class BruteForce{
	private:
		double cw[20][20];
		int* tour;
		int numCities;
	public:
		BruteForce(double a[20][20], int);
		~BruteForce();
		double calctourWeight();
		void printTour();
		void swapCities(int,int);
		double run();
		long long factorial(int);
};

#endif
