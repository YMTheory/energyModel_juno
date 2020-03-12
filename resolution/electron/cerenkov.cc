void cerenkov()
{
    gStyle->SetOptFit(1111);

    double sigma[39]; double totPE[39]; double totCerPE[39];
    double tmp_edep; double tmp_totPE;
    int i = 0;
    ifstream in;
    in.open("totPE.txt");
    string line;
    while(getline(in,line)){
        istringstream ss(line);
        ss >> tmp_edep >> tmp_totPE; totPE[i] = tmp_totPE; i++;
    }

    in.close();


    TGraph* g1 = new TGraph();
    TGraph* gfit1 = new TGraph();
    TGraphErrors* g2 = new TGraphErrors();
    TGraph* gfit2 = new TGraph();
    TGraph* g3 = new TGraph();



    in.open("./cerenkovPE.txt");
    double tmp_totCerPE; i=0;
    while(getline(in, line)){
        istringstream ss(line);
        ss >> tmp_edep >> totCerPE[i];
        g2->SetPoint(i, totPE[i], totCerPE[i]);
        //g2->SetPointError(i, 0, sigma[i]);
        g3->SetPoint(i, totPE[i], TMath::Sqrt(totCerPE[i]));i++;
    }

    in.close();

    in.open("./cerenkovPE_fluctuation.txt");

    double tmp_sigma; i = 0;
    while(getline(in, line)){
        istringstream ss(line);
        ss >> tmp_edep >> tmp_sigma;
        sigma[i] = tmp_sigma;
        g1->SetPoint(i, totPE[i], tmp_sigma); i++;
    }
    in.close();


    TF1* f0 = new TF1("f0", "[0]*TMath::Sqrt(x-[1])", 0, 12500);
    TF1* f1 = new TF1("f1", "[0] + x*[1]", 0, 12500);


    TCanvas* c1 = new TCanvas();
    c1->SetGrid();

    g1->Fit(f0, "R0");
    //g1->Fit("pol", "R0");

    double p0 = f0->GetParameter(0);  double p1 = f0->GetParameter(1);// double p2 = f0->GetParameter(2);
    for( int j=0; j<1000; j++ ){
        double xx = 12500./1000*j+600;
        gfit1->SetPoint(j, xx, p0*TMath::Sqrt(xx-p1));
    }

    g1->SetMarkerStyle(20);
    g1->SetMarkerSize(0.8);
    g1->SetMarkerColor(kBlue+1);
    g1->Draw("AP");

    gfit1->SetLineColor(kGreen+2);
    gfit1->SetLineWidth(3);
    gfit1->Draw("L SAME");


    g3->SetLineColor(kOrange+1);
    g3->SetLineWidth(4);
    g3->SetMarkerSize(1);
    g3->SetMarkerStyle(22);
    g3->SetMarkerColor(kOrange+1);
    g3->Draw("PL SAME");

    TLegend* led = new TLegend();
    led->AddEntry(g1, "simulation");
    led->AddEntry(g3,"Poisson");
    led->Draw("SAME");


    TCanvas* c2 = new TCanvas();
    c2->SetGrid();

    g2->Fit(f1,"R");

    p0 = f1->GetParameter(0);  p1 = f1->GetParameter(1);
    for( int j=0; j<1000; j++ ){
        double xx = 12500./1000*j;
        gfit2->SetPoint(j, xx, p0+xx*p1);
    }

    g2->SetMarkerStyle(20);
    g2->SetMarkerSize(0.8);
    g2->SetMarkerColor(kBlue+1);
    g2->SetLineColor(kBlue+1);
    g2->Draw("AP");


    gfit2->SetLineColor(kGreen+2);
    gfit2->SetLineWidth(3);
    gfit2->Draw("L SAME");


}
