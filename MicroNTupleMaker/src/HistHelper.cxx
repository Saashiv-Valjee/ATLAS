/* =============================================================================================== */
void MicroNTupleMaker::DeclareHistograms(TH1F* m, TH1F* c, TH1F* cw){

  cout << "Declaring Histograms..." << endl;

  metadata = (TH1F*) m->Clone();
  TH1F* cutflow_t = (TH1F*) c->Clone();
  TH1F* cutflow_weighted_t = (TH1F*) cw->Clone();

  // Cutflow histogram
  cout << "Setting bins..." << endl;
  for (int i=1;i<cutflow->GetNbinsX()+1;i++){
    cutflow->SetBinContent(i,cutflow_t->GetBinContent(i));
    cout << i << " = " << cutflow_t->GetXaxis()->GetBinLabel(i) << endl;
    cutflow->GetXaxis()->SetBinLabel(i,cutflow_t->GetXaxis()->GetBinLabel(i));
    cutflow_weighted->SetBinContent(i,cutflow_weighted_t->GetBinContent(i));
    cutflow_weighted->GetXaxis()->SetBinLabel(i,cutflow_weighted_t->GetXaxis()->GetBinLabel(i));
    if (i == cutflow_t->GetNbinsX()) break; // because cutflow length is shorter for MC than data
  }
  cout << year_mc << endl;
  int bin_i;
  if (year_mc == "data") bin_i = 24;
  else bin_i = 17;
  cutflow->GetXaxis()->SetBinLabel(bin_i,"met > 200");
  cutflow_weighted->GetXaxis()->SetBinLabel(bin_i,"met > 200");

  cutflow->GetXaxis()->SetBinLabel(bin_i+1,"mT > 1200");
  cutflow_weighted->GetXaxis()->SetBinLabel(bin_i+1,"mT > 1200");

  // SR temp additions
  //cutflow->GetXaxis()->SetBinLabel(6,"d#eta(j1,j2) < 1.5");
  //cutflow->GetXaxis()->SetBinLabel(7,"rT > 0.15");
  //cutflow->GetXaxis()->SetBinLabel(8,"mT > 1.5 TeV");
  //cutflow->GetXaxis()->SetBinLabel(8,"d#phi_{min}(j_{1,2},MET) < 0.8");

}

/* =============================================================================================== */
void MicroNTupleMaker::WriteHistograms(){

  cout << "Writing Histograms..."<< endl;  

  cutflow->Write();
  cutflow_weighted->Sumw2();
  cutflow_weighted->Write();
  metadata->Write();
}
