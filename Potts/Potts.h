#ifndef POTTS_H_
#define POTTS_H_

#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
namespace Potts {

typedef struct Color{
		char r;
		char g;
		char b;
		Color(int rc, int gc, int bc) : r(rc), g(gc), b(bc){};

	} Color;

class MainMatrix{

	//char ** matrix;	//pointer to the main square array of cells
	//char matrix[40][40];
	std::vector <char>* matrix;
	std::vector <Color> colors;
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
    void randomizeMatrix();
	Color getColor(int i){ return colors[i]; }
    MainMatrix(int newMatrixSize, float simTemperature, float couplingFactor, int maxSpin, int minSpin );
    ~MainMatrix();
	void MetropolisStep();	//does one step of calculation
	int getMatrixSize() const {return matrixSize;};
	char getSpin(int x, int y);
	void getSpinColor(int x, int y);
	void adjustTemperature(float dT);
	float getTemperature() const { return this-> temperature; }
	int getSpinsN() const { return states; };
};

class InfoPack{

    MainMatrix * matrix;

    float temperature;
    int interfaces;
    float orderFactor;
    int * stateHistogram;

    bool thisSimulationIsOffTheShoreAndThisFileHasBeenUsedBefore; //no po prostu musiałem no XD

    public:
    InfoPack(MainMatrix * currMatrix);
    void calcStateHistogram(bool doFurtherCalculations);
    void consolePrintData();
    void filePrintData();

};

class MultiPack{

    MainMatrix * matrix;

    long * interfaces;
    long * orderFactor;

    long * spin0;
    long * spin1;
    long * spin2;
    long * spin3;
    long * spin4;
    long * spin5;

    //float ** stateHistogram;
    //std::vector <float>* stateHistogram;
    int sim_iterator;   //zmienna do przechowywania aktualnego numeru symulacji


    public:
    int repeats;    //jak wiele razy ma się wykonać jedna symulacja
    int steps;      //ile kroków ma miec jedna symulacja
    MultiPack(MainMatrix * currMatrix,float repeats_param,int steps_param);
    ~MultiPack();
    void calcStateHistogram(int currentStep);
    void filePrintData();
    int getSimIterator() const {return sim_iterator;};
    void setIteratorUp();
    int getRepeats() const {return repeats;};

};

class MultiPack2{

    MainMatrix * matrix;
    long maxSimRepeat;
    long maxStepInSim;
    long currSimStep;
    long currSimRepeat;

    long * interfaces;
    long * orderFactor;

    long * spin0;
    long * spin1;
    long * spin2;
    long * spin3;
    long * spin4;
    long * spin5;

    public:
    MultiPack2(MainMatrix * matrix_param,long maxSimRepeat_param,long maxStepInSim_param);

    long getMaxSimRepeat() const {return maxSimRepeat;};
    long getMaxSteppInSim() const {return maxStepInSim;};
    long getCurrSimStep() const {return currSimStep;};
    long getCurrSimRepeat() const {return currSimRepeat;};
    long getInterfaces(long step) const {return interfaces[step];}
    long getOrderFactor(long step) const {return orderFactor[step];};

    void IncrCurrSimRepeat();
    void IncrCurrSimStep();
    void ResCurrSimStep();
    void ResCurrSimRepeat();

    void AddSpin(char spinNumber,int value);
    long calcStepData();
    long scaleData(long data);

    void printDataToFile();


};

}
#endif
