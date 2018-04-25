#include "Potts.h"

namespace Potts {

    /*
    *   METODY MainMatrix
    *
    */

    MainMatrix::MainMatrix(int newMatrixSize, float simTemperature, float couplingFactor, int maxSpin, int minSpin ){
        matrixSize = newMatrixSize;
        temperature = simTemperature;
        coupling = couplingFactor;
        maxState = maxSpin;
        minState = minSpin;
        states = maxState-minState;

        for(int i=0;i<maxSpin;i++){
          colors.push_back(Color(255/maxSpin * (i+1), 255/maxSpin * (maxSpin -i), 255/maxSpin * ((maxSpin+2*i) % maxSpin)));
        }

		matrix =  new std::vector <char> (matrixSize*matrixSize);

        for(int x=0 ; x<matrixSize ; x++)
            for(int y=0 ; y<matrixSize ; y++)
                setSpin(x,y, getRandomSpin() );



	}
    MainMatrix::~MainMatrix(){
    	delete matrix;
    }
    float MainMatrix::random01(){
        return (float)(rand()%100) / 100;
    }
	char MainMatrix::getSpin(int x, int y){
		return (*matrix)[x*matrixSize+y];
	}
	void MainMatrix::setSpin(int x,int y, char newSpin){
		(*matrix)[x*matrixSize+y] = newSpin;
	}

	void MainMatrix::adjustTemperature(float dT){
		if (this->temperature + dT > 0)
			this->temperature += dT;

	}
	int MainMatrix::validRandom(){
		return 	rand()%matrixSize;
	}
    char MainMatrix::getRandomSpin(){
        return rand()%states+minState;
    }
	int MainMatrix::cronecker(int a, int b){
		if(a==b) return 1;
		else return 0;
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
		int x=validRandom();	//random cell picking
		int y=validRandom();	//

		float currentHamilton = calcHamilton(x,y);			//calculating next state
		char newSpin = getRandomSpin();					    //newsSPin value is by default set to the random one, thus less code to overwrite the value (may be changed)
		float probableHamilton = calcHamilton(x,y,false,newSpin);

		if( currentHamilton > probableHamilton )            //if new state is better than current, overwrite the newSpin as current spin
            setSpin(x,y,newSpin);
        else{
            if( random01() < exp(-(probableHamilton-currentHamilton)/temperature) )                                     //if we have luck them set spin to newSpin
                setSpin(x,y,newSpin);
        }
        //if we do not have luck the spin stays the same
	}
	void MainMatrix::getSpinColor(int x, int y){

    }
    void MainMatrix::randomizeMatrix(){
        for(int x=0 ; x<matrixSize ; x++)
            for(int y=0 ; y<matrixSize ; y++)
                setSpin(x,y, getRandomSpin() );
    }

    /*
    *   METODY InfoCluster
    *
    */

    InfoPack::InfoPack(MainMatrix * currMatrix){
        this->matrix = currMatrix;
        stateHistogram = new int[ this->matrix->getSpinsN() ];
        thisSimulationIsOffTheShoreAndThisFileHasBeenUsedBefore=false;
    }

    void InfoPack::calcStateHistogram(bool doFurtherCalculations){

        int sizeOfMatrix = this->matrix->getMatrixSize();

        for(int a=0;a<this->matrix->getSpinsN();a++){
              stateHistogram[a]=0;
        }
        interfaces=0;

        for(int x=0;x< sizeOfMatrix;x++ ){
            for(int y=0;y< sizeOfMatrix;y++ ){
                stateHistogram[ this->matrix->getSpin(x,y) ]++;

                if( ((x+1) != sizeOfMatrix))
                    if( matrix->getSpin(x,y) != matrix->getSpin(x+1,y) )
                        interfaces++;

                if( ((y+1) != sizeOfMatrix))
                    if( matrix->getSpin(x,y) != matrix->getSpin(x,y+1) )
                        interfaces++;

            }
        }
        orderFactor = 0;
        float N_over_Q = (float)(sizeOfMatrix*sizeOfMatrix) / (float)matrix->getSpinsN();
        for(int a=0;a<this->matrix->getSpinsN();a++){
              orderFactor += abs( (float)stateHistogram[a] - N_over_Q );
        }



    }

    void InfoPack::consolePrintData(){
        for(int i=0; i<this->matrix->getSpinsN();i++){
            printf("#%d=%-4d ",i,this->stateHistogram[i]);
        }
        printf("| INT=%-4d ",interfaces);
        printf("MAG=%-4.1f ",orderFactor);
        printf("\n");

    }
    void InfoPack::filePrintData(){

        std::fstream plik;
        //plik.open("data.txt",std::fstream::app);

        if(thisSimulationIsOffTheShoreAndThisFileHasBeenUsedBefore){
             plik.open("data2.txt",std::fstream::app);
        }
        else{
            plik.open("data2.txt",std::fstream::out);
            plik << matrix->getSpinsN() << "\n";
            thisSimulationIsOffTheShoreAndThisFileHasBeenUsedBefore=true;
        }

        for(int i=0;i<matrix->getSpinsN();i++){
            plik << stateHistogram[i] << " ";
        }
        plik << interfaces << " " << (int)orderFactor;
        plik << "\n";

        plik.close();

    }

    /*
    *
    *   METODY MultiPack
    *
    */

    MultiPack::MultiPack(MainMatrix * currMatrix,float repeats_param,int steps_param){

        this->matrix = currMatrix;
        sim_iterator=0;
        repeats = repeats_param;
        steps = steps_param;

        this->interfaces = new long[repeats];
        this->orderFactor = new long[repeats];

        this->spin0 = new long[repeats];
        this->spin1 = new long[repeats];
        this->spin2 = new long[repeats];
        this->spin3 = new long[repeats];
        this->spin4 = new long[repeats];
        this->spin5 = new long[repeats];

        for(int i=0;i<repeats;i++){
            this->interfaces[i]=0;
            this->orderFactor[i]=0;

            spin0[i]=0;
            spin1[i]=0;
            spin2[i]=0;
            spin3[i]=0;
            spin4[i]=0;
            spin5[i]=0;
        }


/*
        stateHistogram =  new std::vector <float> (matrix->getSpinsN()*repeats);
        for(int i=0;i<matrix->getSpinsN()*repeats;i++){
            (*stateHistogram)[i]=0;
        }
*/
        /*
        this->stateHistogram = new float*[currMatrix->getSpinsN()];
        for(int a=0;a<currMatrix->getSpinsN();a++){
            this->stateHistogram[a] = new float[repeats];
        }
        for(int a=0;a<currMatrix->getSpinsN();a++){
            for(int n=0;n<repeats;n++){
                this->stateHistogram[a][n]=0;
            }
        }
        */
    }
    MultiPack::~MultiPack(){
        delete [] interfaces;
        delete [] orderFactor;
    }
    void MultiPack::setIteratorUp(){
        sim_iterator++;
    }
    void MultiPack::calcStateHistogram(int currentStep){
        int sizeOfMatrix = this->matrix->getMatrixSize();
        float interfaces_TMP=0;
        float orderFactor_TMP=0;
                                                                //OBLICZANIE INTERFEJSÓW
        for(int x=0;x< sizeOfMatrix;x++ ){
            for(int y=0;y< sizeOfMatrix;y++ ){
                //stateHistogram[ this->matrix->getSpin(x,y) ][currentStep] +=(1./this->repeats);
            switch(this->matrix->getSpin(x,y)){
                case 0:
                    spin0[currentStep]++;
                    break;
                case 1:
                    spin1[currentStep]++;
                    break;
                case 2:
                    spin2[currentStep]++;
                    break;
                case 3:
                    spin3[currentStep]++;
                    break;
                case 4:
                    spin4[currentStep]++;
                    break;
                case 5:
                    spin5[currentStep]++;
                    break;
            }
            if( ((x+1) != sizeOfMatrix))
                if( matrix->getSpin(x,y) != matrix->getSpin(x+1,y) )
                    interfaces_TMP += 1;

            if( ((y+1) != sizeOfMatrix))
                if( matrix->getSpin(x,y) != matrix->getSpin(x,y+1) )
                    interfaces_TMP += 1;

            }
            /*  Energia śr na spin to iloraz sumy ((wsyztskie linki - interfejsów) i sizeofmatrix^2)
            */
        }
        std::cout << spin0[currentStep] << " " << spin1[currentStep] << " " << spin2[currentStep] << " " << spin3[currentStep] << " " << spin4[currentStep] << " " << spin5[currentStep] << std::endl;
        this->interfaces[currentStep] += (interfaces_TMP/getRepeats());

        //OBLICZANIE ORDERFACTOR
        float N_over_Q = (float)(sizeOfMatrix*sizeOfMatrix) / (float)matrix->getSpinsN();
        orderFactor_TMP += abs( spin0[sim_iterator] - N_over_Q );
        orderFactor_TMP += abs( spin1[sim_iterator] - N_over_Q );
        orderFactor_TMP += abs( spin2[sim_iterator] - N_over_Q );
        orderFactor_TMP += abs( spin3[sim_iterator] - N_over_Q );
        orderFactor_TMP += abs( spin4[sim_iterator] - N_over_Q );
        orderFactor_TMP += abs( spin5[sim_iterator] - N_over_Q );
        orderFactor[currentStep] += (orderFactor_TMP/(float)repeats);
    }
    void MultiPack::filePrintData(){
        std::fstream plik;
        plik.open("data_multi.txt",std::fstream::out);
        plik << matrix->getSpinsN() << "\n";
        std::cout << "printuje" << std::endl;

        for(int step=0;step<steps;step++){
               /* for(int a=0;a<matrix->getSpinsN();a++){
                    plik << (float)stateHistogram[a][step] << " ";
                }*/
                switch(matrix->getSpinsN()){
                    case 6:
                        plik << spin5[step] << " ";
                    case 5:
                        plik << spin4[step] << " ";
                    case 4:
                        plik << spin3[step] << " ";
                    case 3:
                        plik << spin2[step] << " ";
                    case 2:
                        plik << spin1[step] << " " << spin0[step] << " ";
                }
                plik << (float)interfaces[step] << " " << (float)orderFactor[step];
                plik << "\n";
        }

    }


    /*
    *
    *     METODY MultiPack2
    *
    */
    MultiPack2::MultiPack2( MainMatrix * matrix_param,long maxSimRepeat_param,long maxStepInSim_param){

        this->matrix = matrix_param;
        this->maxSimRepeat = maxSimRepeat_param;
        this->maxStepInSim = maxStepInSim_param;
        this->currSimStep=0;
        this->currSimRepeat=0;

        interfaces = new long[this->maxStepInSim];
        orderFactor = new long[this->maxStepInSim];

        spin0 = new long[this->maxStepInSim];
        spin1 = new long[this->maxStepInSim];
        spin2 = new long[this->maxStepInSim];
        spin3 = new long[this->maxStepInSim];
        spin4 = new long[this->maxStepInSim];
        spin5 = new long[this->maxStepInSim];

        for(int i=0 ; i<maxStepInSim ; i++){
            interfaces[i]=0;
            orderFactor[i]=0;

            spin0[i]=0;
            spin1[i]=0;
            spin2[i]=0;
            spin3[i]=0;
            spin4[i]=0;
            spin5[i]=0;
        }
    }
    void MultiPack2::IncrCurrSimRepeat(){
        currSimRepeat++;
    }
    void MultiPack2::IncrCurrSimStep(){
        currSimStep++;
    }
    void MultiPack2::ResCurrSimStep(){
        currSimStep=0;
    }
    void MultiPack2::ResCurrSimRepeat(){
        currSimRepeat=0;
    }

    void MultiPack2::AddSpin(char spinNumber,int value){
        switch(spinNumber){
            case 0:
                spin0[currSimStep]+=value;
                break;
            case 1:
                spin1[currSimStep]+=value;
                break;
            case 2:
                spin2[currSimStep]+=value;
                break;
            case 3:
                spin3[currSimStep]+=value;
                break;
            case 4:
                spin4[currSimStep]+=value;
                break;
            case 5:
                spin5[currSimStep]+=value;
                break;
        }
    }

    long MultiPack2::calcStepData(){

        int interfaces=0;                                               //zmienna na tymczasowy parametr interfejsów
        int *currentSpinsArray = new int[this->matrix->getSpinsN()];    //zmienna na tymczasowy spis ilosci spinow
        for(int i=0;i<this->matrix->getSpinsN();i++){                   //
            currentSpinsArray[i]=0;                                     //zerowanie powyzszej tablicy
        }

        for(int x=0 ; x<matrix->getMatrixSize() ; x++ ){
            for(int y=0 ; y<matrix->getMatrixSize() ; y++ ){
                currentSpinsArray[this->matrix->getSpin(x,y)]++;
                //AddSpin(this->matrix->getSpin(x,y));

                if( ((x+1) != matrix->getMatrixSize() ))
                    if( matrix->getSpin(x,y) != matrix->getSpin(x+1,y) )
                        interfaces++;
                if( ((y+1) != matrix->getMatrixSize() ))
                    if( matrix->getSpin(x,y) != matrix->getSpin(x,y+1) )
                        interfaces++;
            }
        }
        this->interfaces[this->currSimStep] += interfaces;

        for(int i=0;i<this->matrix->getSpinsN();i++){                   //
            AddSpin(i,currentSpinsArray[i]);                            //dopisywanie do glownego rejestru spinow aktualnie wyliczonych wartosci
        }


        float N_over_Q = (float)(matrix->getMatrixSize()*matrix->getMatrixSize()) / (float)matrix->getSpinsN();
        for(int a=0 ; a<this->matrix->getSpinsN() ; a++){
              orderFactor[this->currSimStep] += abs( currentSpinsArray[a] - N_over_Q );
        }

        delete [] currentSpinsArray;
    }

    void MultiPack2::printDataToFile(){
        std::fstream plik;
        plik.open("data_m2.txt",std::fstream::out);
        plik << matrix->getSpinsN() << "\n";

        for(int step=0 ; step<this->getMaxSteppInSim() ; step++){
            switch(matrix->getSpinsN()){
                    case 6:
                        plik << scaleData(spin5[step])  << " ";
                    case 5:
                        plik << scaleData(spin4[step])  << " ";
                    case 4:
                        plik << scaleData(spin3[step])  << " ";
                    case 3:
                        plik << scaleData(spin2[step])  << " ";
                    case 2:
                        plik << scaleData(spin1[step])  << " " << scaleData(spin0[step]) << " ";
            }
            plik << scaleData(this->getInterfaces(step)) << " " << scaleData(this->getOrderFactor(step)) << "\n";
        }
        plik.close();
    }

    long MultiPack2::scaleData(long data){
        return data / this->getMaxSimRepeat();
    }


}
