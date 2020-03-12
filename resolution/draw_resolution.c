void draw_resolution()
{
    gStyle->SetOptFit(1111);
    gStyle->SetOptStat(1111);

    ifstream in;
    //in.open("./resolution_gamma_cerenkov.txt");
    //in.open("./resolution_nocerenkov_electron.txt");
    in.open("./positron/positron_resolution.txt");
    string line;

    const Int_t num = 6;
    double totpe[num]; double totpe_err[num]; double sigma[num]; double sigma_err[num];

    int count = 0;
    while(getline(in,line)){
        istringstream ss(line);
        ss >> totpe[count] >> totpe_err[count] >> sigma[count] >> sigma_err[count];
        count++;
    }

    double energe_scale[num]; double resol[num]; double resol_err[num]; double energe_scale_err[num];
    for(int i=0; i<num; i++){
        energe_scale[i] = totpe[i] / totpe[0] * 1.522;
        energe_scale_err[i] = totpe_err[i] / totpe[0] *1.522;
        resol[i] = sigma[i] / totpe[i];
        resol_err[i] = TMath::Sqrt(sigma_err[i]*sigma_err[i]/totpe[i]/totpe[i] + sigma[i]*sigma[i]*totpe_err[i]*totpe_err[i]/pow(totpe[i],4));
        //cout << i << "," <<energe_scale[i] <<","<< resol[i] << endl;
        cout << i << "," <<energe_scale[i] <<","<< resol[i] << endl;
        //cout << energe_scale[i] << " " << energe_scale_err[i] <<" "<< resol[i] << " " << resol_err[i] << endl;
    }

    TF1* func_resol = new TF1("func_resol", "TMath::Sqrt([0]*[0]/x+[1]*[1]+[2]*[2]/x/x)", 0, 12);
    //func_resol->SetParameter(2,0.);

    TGraphErrors* tge = new TGraphErrors(num, energe_scale, resol, energe_scale_err, resol_err);
    tge->SetMarkerStyle(21);
    tge->SetMarkerColor(kBlue);
    tge->SetLineColor(kBlue);
    tge->SetLineWidth(2);
    tge->SetTitle("Energy resolution ;E_{vis}/MeV;resolution");
    tge->Fit(func_resol, "RE0");

    double a = func_resol->GetParameter(0); double aerr = func_resol->GetParError(0);
    double b = func_resol->GetParameter(1); double berr = func_resol->GetParError(1);
    double c = func_resol->GetParameter(2); double cerr = func_resol->GetParError(2);
    const Int_t num_draw = 1000;
    double draw_x[num_draw]; double draw_y[num_draw];
    for(int i=0; i<num_draw; i++){
        draw_x[i] = 0.05 + 10./num_draw*i;
        draw_y[i] = TMath::Sqrt(a*a/draw_x[i]+b*b+c*c/draw_x[i]/draw_x[i]);
    }

    auto fit_line = new TGraph(num_draw, draw_x, draw_y);
    fit_line->SetLineColor(kGreen+2);
    fit_line->SetLineWidth(3);

    TCanvas* cc = new TCanvas();
    cc->SetGrid();
    tge->Draw("AP");
    fit_line->Draw("LSAME");

}
