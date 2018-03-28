#ifndef POTTS_H_
#define POTTS_H_

#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>

namespace Potts {

class MainMatrix{

	//char ** matrix;	//pointer to the main square array of cells
	char matrix[40][40];
	int matrixSize;		//dimension of matrix

	float temperature;
	float coupling;
	int maxState;
	int minState;
	int states;

	void setSpin(int x,int y, char newSpin);
	int cronecker(int a, int b);
	int validRandom(); 	//returns random number from 0 to matrixSize;
	float random01();
	float calcHamilton(int x, int y, bool fromMatrix=true, char subSpin=0);	//calculates hamiltonian for point (x,y)
	char getRandomSpin(); //zwraca losową wartość spinu spomiędzy 0-masSpin


	public:
    MainMatrix(int newMatrixSize, float simTemperature, float couplingFactor, int maxSpin, int minSpin );
    ~MainMatrix();
	void MetropolisStep();	//does one step of calculation
	int getMatrixSize() const {return matrixSize;};
	int getSpin(int x, int y);
	void getSpinColor(int x, int y);
	char getSpinsN() const {return states;};
};


}
#endif
