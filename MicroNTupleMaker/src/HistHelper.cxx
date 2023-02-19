/* =============================================================================================== */
void MicroNTupleMaker::DeclareHistograms(){

  // Cutflow histogram
  cutflow = new TH1F("cutflow", "cutflow", 10,0,10);
  cutflow->GetXaxis()->SetBinLabel(1,"All");
  cutflow->GetXaxis()->SetBinLabel(2,"njets >= 2");
  cutflow->GetXaxis()->SetBinLabel(3,"|#eta_{j1}| < 2.0");
  cutflow->GetXaxis()->SetBinLabel(4,"Y*(j1,j2) < 2.8");

}

/* =============================================================================================== */
void MicroNTupleMaker::WriteHistograms(){

  cout << "Writing Histograms..."<< endl;  

  cutflow->Write();

}
