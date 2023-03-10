/* =============================================================================================== */
void MicroNTupleMaker::DeclareHistograms(){

  // Cutflow histogram
  cutflow = new TH1F("cutflow", "cutflow", 10,0,10);
  cutflow->GetXaxis()->SetBinLabel(1,"All");
  cutflow->GetXaxis()->SetBinLabel(2,"njets >= 2");
  cutflow->GetXaxis()->SetBinLabel(3,"|#eta_{j1}| < 2.1");
  cutflow->GetXaxis()->SetBinLabel(4,"|#eta_{j2}| < 2.1");
  cutflow->GetXaxis()->SetBinLabel(5,"d#eta(j1,j2) < 2.8");
  // SR temp additions
  cutflow->GetXaxis()->SetBinLabel(6,"d#eta(j1,j2) < 1.5");
  cutflow->GetXaxis()->SetBinLabel(7,"rT > 0.15");
  //cutflow->GetXaxis()->SetBinLabel(8,"mT > 1.5 TeV");
  cutflow->GetXaxis()->SetBinLabel(8,"d#phi_{min}(j_{1,2},MET) < 0.8");
}

/* =============================================================================================== */
void MicroNTupleMaker::WriteHistograms(){

  cout << "Writing Histograms..."<< endl;  

  cutflow->Write();

}
