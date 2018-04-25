sROOTututu(){

    ifstream test("data_m2.txt");
    int numLines = 0;
    std::string unused;
    while ( std::getline(test, unused) )
        numLines++;
    test.close();
    numLines--;

    auto c3 = new TCanvas("c3","c3",800, 800);
    c3->Divide(1,3);
    c3->cd(1);

    //OTWIERANIE WLASCIWE PLIKU
    int states=0;
    ifstream dane("data_m2.txt");
    dane >> states;

    //DEFINICJE TABLIC
    int ** statesHistogram = new int*[states];
    for(int i=0;i<states;i++){
        statesHistogram[i] = new int[numLines];
    }
    int *interfaces = new int[numLines];
    int *order = new int[numLines];
    int *steps = new int[numLines];

    for(int i=0;i<numLines;i++){
        steps[i] = i+1;
    }

    //WYPELNIANIE TABLIC
    float tmp;
    for(int step=0;step<numLines;step++){
        for(int i=0;i<states;i++){
            dane >> statesHistogram[i][step];
            //dane >> tmp;
            //statesHistogram[i][step] = ((int)tmp)%10000;
        }
        dane >> interfaces[step];
        //dane >> tmp;
        //interfaces[step] = ((int)tmp)%10000;

        dane >> order[step];
         //dane >> tmp;
        //order[step] = ((int)tmp)%10000;

    }

    //TABLICA GRAFÓW
    TGraph ** gTab = new TGraph*[states];
    for(int i=0;i<states;i++){
        gTab[i] = new TGraph(numLines,steps,statesHistogram[i]);
    }
    TMultiGraph *mg = new TMultiGraph();
    for(int i=0;i<states;i++){
        mg->Add(gTab[i],"lp");
        gTab[i]->SetLineColor(i+3);
        gTab[i]->SetLineWidth(3);
        gTab[i]->SetTitle(Form ("%d", i));
    }

    mg->Draw("a");
    mg->SetTitle("Histogram stanow");
    c3->BuildLegend(0.85,0.8);

    c3->cd(2);
    TGraph * interfacesGraph = new TGraph(numLines,steps,interfaces);
    interfacesGraph->Draw();
    interfacesGraph->SetTitle("Interfejsy");

    c3->cd(3);
    TGraph * orderGraph= new TGraph(numLines,steps,order);
    orderGraph->Draw();
    orderGraph->SetTitle("Parametr parzadku");




    cout << "Tyle wie skrypt: " << endl;
    cout << "Spinów: " << states << ", kroków: " << numLines << endl;
    cout <<"sup?" << endl;
    cout << statesHistogram[400][0] << endl;

    dane.close();
}
