double fitting(double a, double b, double c, double x){
    return TMath::Sqrt(a*a/x+b*b+c*c/x/x);
}

void compare_resol()
{

    TGraphErrors* tge_OFF = new TGraphErrors();

    tge_OFF->SetPoint(0,1,0.0272902);
    tge_OFF->SetPoint(1,2.04074,0.0195585);
    tge_OFF->SetPoint(2,4.12148,0.0136602);
    tge_OFF->SetPoint(3,6.2046,0.0112252);
    tge_OFF->SetPoint(4,8.29097,0.00971242);

    tge_OFF->SetPointError(0,0.000639551,0.000482953);
    tge_OFF->SetPointError(1,0.00094145,0.000353387);
    tge_OFF->SetPointError(2,0.00134647,0.000252684);
    tge_OFF->SetPointError(3,0.00160366,0.00019458);
    tge_OFF->SetPointError(4,0.00185603,0.000169064);


    TGraphErrors* tge_ON = new TGraphErrors();

    tge_ON->SetPoint(0,1,0.0300581);
    tge_ON->SetPoint(1,2.07726,0.0233083);
    tge_ON->SetPoint(2,4.26305,0.0167516);
    tge_ON->SetPoint(3,6.46237,0.0141261);
    tge_ON->SetPoint(4,8.65919,0.0120445);

    tge_ON ->SetPointError(0,0.000432236,0.000316437);
    tge_ON->SetPointError(1,0.000696986,0.000247043);
    tge_ON->SetPointError(2,0.00102473,0.000167403);
    tge_ON->SetPointError(3,0.00131144,0.000145382);
    tge_ON->SetPointError(4,0.00150403,0.000122496);



    TGraph* line1 = new TGraph();
    for(int i=0; i<1000; i++){
        line1->SetPoint(i, 0.01+10/1000.*i, fitting(2.74773e-02, 1.94506e-03, 0., 0.01+10./1000*i));
    }

    TGraph* line2 = new TGraph();
    for(int i=0; i<1000; i++){
        line2->SetPoint(i, 0.01+10/1000.*i, fitting(3.07366e-02, 6.74628e-03, 0., 0.01+10./1000*i));
    }


    tge_OFF->SetMarkerStyle(20);
    tge_OFF->SetMarkerColor(kBlue+1);
    tge_OFF->SetLineColor(kBlue+1);

    tge_ON->SetMarkerStyle(21);
    tge_ON->SetMarkerColor(kGreen+1);
    tge_ON->SetLineColor(kGreen+1);

    line1->SetLineColor(kBlue+1);
    line1->SetLineWidth(3);

    line2->SetLineColor(kGreen+1);
    line2->SetLineWidth(3);

    TCanvas* cc = new TCanvas();
    cc->SetGrid();

    tge_OFF->SetTitle("Gamma Resolution; Evis/MeV; resolution");
    tge_OFF->GetYaxis()->SetRangeUser(0.008, 0.032);
    tge_OFF->GetYaxis()->SetTitleOffset(1.1);

    tge_OFF->Draw("AP");
    tge_ON->Draw("P SAME");
    line1->Draw("L SAME");
    line2->Draw("L SAME");

    TLegend* led = new TLegend();
    led->AddEntry(tge_ON, "Cerenkov ON");
    led->AddEntry(tge_OFF, "Cerenkov OFF");
    led->Draw("SAME");

    TText *t1 = new TText(3.,.025,"Cerenkov ON  resolution@1MeV: 3.147%");
    TText *t2 = new TText(3.,.028,"Cerenkov OFF resolution@1MeV: 2.755%");
    t1->SetTextColor(kGreen+1);
    t1->SetTextFont(43);
    t1->SetTextSize(20);
    t2->SetTextColor(kBlue+1);
    t2->SetTextFont(43);
    t2->SetTextSize(20);

    t2->Draw("SAME");
    t1->Draw("SAME");

}
