void cerenkov_fit()
{
  TFile* file = TFile::Open("./sample_detsim_user.root");
  TTree* evt;
  TRandom3 r;

  TH1F* h_cerop = new TH1F("h_cerop", "", 100, 600, 1400);

  float m_stepL[1000]; TBranch* b_stepL;
  float m_beta[1000]; TBranch* b_beta;
  int m_stepnum; TBranch* b_stepnum;
  int m_secnum; TBranch* b_secnum;
  int m_CerOP; TBranch* b_CerOP;

  evt = (TTree*)file->Get("evt");
  evt->SetBranchAddress("stepnum", &m_stepnum, &b_stepnum);
  evt->SetBranchAddress("stepL", m_stepL, &b_stepL);
  evt->SetBranchAddress("secnum", &m_secnum, &b_secnum);
  evt->SetBranchAddress("stepBeta", m_beta, &b_beta);

  double dp = 15.5-1.55; double ge = 2;  double totCerOP;
  const int entries = evt->GetEntries(); //cout << entries << endl;
  for(int i=0; i<entries; i++){
    totCerOP = 0;
    evt->GetEntry(i);
    if(m_secnum==0){ // events w/o secondary particles
      //cout << m_stepnum << endl;
      for(int j=0; j<m_stepnum; j++){
        if(1.47>1/m_beta[j]) totCerOP += (369.8*(dp-ge/m_beta[j]))*m_stepL[j]/10;
      }//cout << "MeanTotCerOP: " << totCerOP << endl;
      h_cerop->Fill(r.PoissonD(totCerOP));
    }
  }

  h_cerop->DrawClone("");

  //file->Close();

}
