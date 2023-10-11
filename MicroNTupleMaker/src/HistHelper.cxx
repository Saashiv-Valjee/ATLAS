/* =============================================================================================== */
void MicroNTupleMaker::DeclareHistograms(TH1F* m, TH1F* c, TH1F* cw){

  cout << "Declaring Histograms..." << endl;

  metadata = (TH1F*) m->Clone();
  cutflow = (TH1F*) c->Clone();
  cutflow_weighted = (TH1F*) cw->Clone();

  // Cutflow histogram
  cutflow->GetXaxis()->SetBinLabel(16,"met > 200");
  cutflow_weighted->GetXaxis()->SetBinLabel(16,"met > 200");

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
  cutflow_weighted->Write();
  metadata->Write();
}
