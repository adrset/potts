#include "Potts.h"

namespace Potts {

    MainMatrix::MainMatrix(int newMatrixSize, float simTemperature, float couplingFactor, int maxSpin, int minSpin ){
        matrixSize = newMatrixSize;
        temperature = simTemperature;
        coupling = couplingFactor;
        maxState = maxSpin;
        minState = minSpin;
//commented because arrays are fucked-up :(
/*
        matrix = new char*[matrixSize];
        for(int i=0; i<matrixSize ; i++){
                matrix[i] = new char[matrixSize];
        }
*/

        for(int x=0 ; x<matrixSize ; x++){
            for(int y=0 ; y<matrixSize ; y++){
                setSpin(x,y, ((float)rand()/RAND_MAX)*(maxState-minState) );
            }

        }


	}
    MainMatrix::~MainMatrix(){
    /*
        for(int i=0;i<matrixSize;i++){
                delete [] matrix[i];
        }
        delete [] matrix;
*/
    }
    float MainMatrix::random01(){
        return rand()%100 / 100;
    }
	int MainMatrix::getSpin(int x, int y){
		return matrix[x][y];
	}
	void MainMatrix::setSpin(int x,int y, char newSpin){
		matrix[x][y] = newSpin;
	}
	int MainMatrix::validRandom(){
		return 	rand()%matrixSize;
	}
    char MainMatrix::getRandomSpin(){
        return (maxState - minState) * (float)rand()/RAND_MAX;
    }
	int MainMatrix::cronecker(int a, int b){
		if(a==b) return 1;
		else return 0;
	}
	bool MainMatrix::metroDecision(int x, int y, float oldH, float youngH){
        float p=((float)rand()/RAND_MAX);
        bool flag=false;
        float z = youngH/temperature;
        if( oldH > youngH )
            flag = true;
        else{
            if( p > exp(z))
                flag = true;
        }
        return flag;
	}
	float MainMatrix::calcHamilton(int x, int y, bool fromMatrix, char subSpin){
		float H=0;
		char currentSpin;
		if(fromMatrix)
			currentSpin = getSpin(x,y);
		else
			currentSpin = subSpin;

		H -= cronecker( currentSpin, getSpin(x+1,y) );
		H -= cronecker( currentSpin, getSpin(x-1,y) );
		H -= cronecker( currentSpin, getSpin(x,y+1) );
		H -= cronecker( currentSpin, getSpin(x,y-1) );

		H *= coupling;
		return H;
	}

	void MainMatrix::MetropolisStep(){
		int x,y;		    //
		x=validRandom();	//random cell picking
		y=validRandom();	//


		float currentHamilton = calcHamilton(x,y);			//calculating next state
		char newSpin = getRandomSpin();					    //newsSPin value is by default set to the random one, thus less code to overwrite the value (may be changed)
		float probableHamilton = calcHamilton(x,y,false,newSpin);

		//float p=((float)rand()/RAND_MAX);                   //probability of change
		float p = random01();
		p = 0.35;                  //if p=0.3 funny shit happens :)
		float z = exp( probableHamilton/temperature );      //chance of change

		if( currentHamilton > probableHamilton )            //if new state is better than current, overwrite the newSpin as current spin
            setSpin(x,y,newSpin);
        else{
            if( p > z )                                     //if we have luck them set spin to newSpin
                setSpin(x,y,newSpin);
        }
        //if we do not have luck the spin stays the same
		/*
        if( metroDecision(x,y,currentHamilton,probableHamilton) ){
            setSpin(x,y,newSpin);
		}
        */
	}

}
