/* =============================================================================================== */
void MicroNTupleMaker::DeclareHistograms(){

  // Cutflow histogram
  cutflow = new TH1F("cutflow", "cutflow", 10,0,10);
  cutflow->GetXaxis()->SetBinLabel(1,"All");
  cutflow->GetXaxis()->SetBinLabel(2,"njets >= 2");
  cutflow->GetXaxis()->SetBinLabel(3,"MET > 200 GeV");
  cutflow->GetXaxis()->SetBinLabel(4,"jet1_pt > 150 GeV");
  cutflow->GetXaxis()->SetBinLabel(5,"|jet1_eta| < 2.8");

}

/* =============================================================================================== */
void MicroNTupleMaker::WriteHistograms(){

  cout << "Writing Histograms..."<< endl;  

  cutflow->Write();

}
