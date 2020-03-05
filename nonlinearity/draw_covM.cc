void draw_covM()
{
    gStyle->SetOptStat(0);
    const Int_t nx = 2;
    const Int_t ny = 2;
    const char* photon[nx] = { "Scintillation", "Cerenkov" };
    TH2D* h1 = new TH2D("h1", "", 2,0,2, 2,0,2);

    Double_t std_Scint[8]; Double_t std_Cer[8]; Double_t cov[8];
    TH2D* h_Cov[8]; TH2D* h_Corr[8];
    TCanvas* c1 = new TCanvas();
    c1->SetLeftMargin(0.15);
    c1->SetBottomMargin(0.15);

    ifstream in;
    in.open("./correlation.txt");
    string line;
    double Energy[8]; double totpe; double totScint; double totCer; double std_totpe[8];
    int count = 0;
    while(getline(in,line)){
        istringstream ss(line);
        ss >> Energy[count] >> totpe >> std_totpe[count] >> totScint >>
        std_Scint[count] >> totCer >> std_Cer[count] >> cov[count];
        count++;
    }

    for(int i=0; i<8; i++){

      h1->Reset();

      h1->SetBinContent(1,1,1);
      h1->SetBinContent(2,2,1);
      h1->SetBinContent(1,2,cov[i]/TMath::Sqrt(std_Cer[i]*std_Scint[i]));
      h1->SetBinContent(2,1,cov[i]/TMath::Sqrt(std_Cer[i]*std_Scint[i]));

      h1->SetMarkerSize(2);
      TAxis* xa = h1->GetXaxis();
      xa->SetNdivisions(-404);
      xa->ChangeLabel(2,-1,-1,-1,kBlue,20,"Scintillation");
      xa->ChangeLabel(-2,-1,-1,-1,kBlue,-1,"Cerenkov");
      TAxis* ya = h1->GetYaxis();
      ya->SetNdivisions(-404);
      ya->ChangeLabel(2,30.,-1,-1,kBlue,-1,"Scintillation");
      ya->ChangeLabel(-2,30.,-1,-1,kBlue,-1,"Cerenkov");

      string title = Form("%0.fkeV Gamma Correlation Matrix", Energy[i]);
      h1->SetTitle(title.c_str());
      h1->Draw("TEXT COLZ");
      string picName = Form("CorrM_%0.fkeV.eps", Energy[i]);
      c1->SaveAs(picName.c_str());
      c1->Clear();
    }

}
