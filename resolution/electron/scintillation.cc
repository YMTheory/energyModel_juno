void scintillation()
{
    gStyle->SetOptFit(1111);

    ifstream in;
    in.open("totPE.txt");
    string line;
    double tmp_edep;  double tmp_totPE;
    double totPE[39];  double totSctPE[39];
    int i=0;
    while(getline(in,line)){
        istringstream ss(line);
        ss >> tmp_edep >> tmp_totPE; totPE[i] = tmp_totPE; i++;
    }

    TGraph* g1 = new TGraph();
    TGraph* gfit1 = new TGraph();
    TGraphErrors* g2 = new TGraphErrors();
    TGraph* gfit2 = new TGraph();
    TGraph* g3 = new TGraph();


    in.close();
    in.open("./scintillationPE.txt");
    double tmp_sigma; double tmp_totSctPE;  i = 0;
    while(getline(in, line)){
        istringstream ss(line);
        ss >> tmp_edep >> tmp_sigma >> tmp_totSctPE;
        g1->SetPoint(i, totPE[i], tmp_sigma);
        g2->SetPoint(i, totPE[i], tmp_totSctPE);
        g2->SetPointError(i, 0, tmp_sigma);
        g3->SetPoint(i, totPE[i], TMath::Sqrt(tmp_totSctPE));
        i++;
    }
    in.close();

    TF1* f1 = new TF1("f1", "[0]+x*[1]", 0, 12500);
    //TF1* f2 = new TF1("f2", "[0]+[1]*TMath::Sqrt(x-[2])", 0, 12500);
    TF1* f2 = new TF1("f2", "[0]*TMath::Sqrt(x)", 0, 12500);
    //TF1* f2 = new TF1("f2","[0]+[1]*(x-[2])*(x-[2])", 0, 12500);

    TCanvas* c1 = new TCanvas();
    c1->SetGrid();

    g2->Fit(f1,"R0");

    double p0 = f1->GetParameter(0);  double p1 = f1->GetParameter(1);
    for( int j=0; j<1000; j++ ){
        double xx = 12500./1000*j;
        gfit2->SetPoint(j, xx, p0+p1*xx);
    }


    g2->SetMarkerStyle(21);
    g2->SetMarkerSize(0.8);
    g2->SetMarkerColor(kGreen+1);
    g2->SetLineColor(kGreen+1);
    g2->Draw("AP");

    gfit2->SetLineColor(9);
    gfit2->SetLineWidth(4);
    gfit2->Draw("L SAME");


    TCanvas* c2 = new TCanvas();
    c2->SetGrid();

    g1->Fit(f2, "RE0");
    double p2 = f2->GetParameter(0);  //double p3 = f2->GetParameter(1); double p4 = f2->GetParameter(2);
    for( int j=0; j<1000; j++ ){
        double xx = 12500./1000*(j)+200;
        //gfit1->SetPoint(j, xx, p2+p3*TMath::Sqrt(xx-p4));
        //cout << xx << " " << p2+p3*TMath::Sqrt(xx-p4) << endl;
        gfit1->SetPoint(j, xx, p2*TMath::Sqrt(xx));
    }


    g1->SetMarkerStyle(20);
    g1->SetMarkerSize(0.8);
    g1->SetMarkerColor(kBlue+1);
    g1->Draw("AP");

    gfit1->SetLineColor(616);
    gfit1->SetLineWidth(4);
    gfit1->Draw("L SAME");

    g3->SetMarkerSize(0.8);
    g3->SetMarkerColor(kOrange+1);
    g3->SetMarkerStyle(24);
    g3->SetLineColor(kOrange+1);
    g3->SetLineWidth(3);
    g3->Draw("PL SAME");

    TLegend* led = new TLegend();
    led->AddEntry(g1, "simulation");
    led->AddEntry(g3,"Poisson");
    led->Draw("SAME");




}
