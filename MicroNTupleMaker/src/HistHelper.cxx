/* =============================================================================================== */
void MicroNTupleMaker::DeclareHistograms(){

  // Cutflow histogram
  cutflow = new TH1F("cutflow", "cutflow", 10,0,10);
  cutflow->GetXaxis()->SetBinLabel(1,"All");
  cutflow->GetXaxis()->SetBinLabel(2,"njets >= 2");
  cutflow->GetXaxis()->SetBinLabel(3,"jet1_pt > 150 GeV");
  cutflow->GetXaxis()->SetBinLabel(4,"dPhi_min < 2.0");
  //cutflow->GetXaxis()->SetBinLabel(5,"nBtags < 2");

}

/* =============================================================================================== */
void MicroNTupleMaker::WriteHistograms(){

  cout << "Writing Histograms..."<< endl;  

  cutflow->Write();

}
