#ifndef GA_HPP
#define GA_HPP

class GeneticAlg{
	private:
		double cw[20][20];
		int numCities, numTours, numGen, percentMut;
	public:
		GeneticAlg(double cw[20][20], int, int, int, int);
};

#endif
