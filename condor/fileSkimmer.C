#define fileSkimmer_cxx
#include "fileSkimmer.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void fileSkimmer::WriteOutput(){
	myTree->Write();
        metadata->Write();
        cutflow->Write();
        cutflow_weighted->Write();
	myFile->Close();
}

void fileSkimmer::Loop()
{
//   In a ROOT session, you can do:
//      root> .L fileSkimmer.C
//      root> fileSkimmer t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   //Long64_t target_events = 1000000;
   //Long64_t increment = nentries/ target_events;
   Long64_t increment = 1;
   //if (target_events > nentries) cout << "ERROR: requesting more events than available (" << nentries << ")" << endl;

   Long64_t nbytes = 0, nb = 0;
   int counter = 0;
   double lumi = -1;
   if (my_year == 2016) lumi = 36.6467e6; //ref OflLumi-13TeV-011 https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/GoodRunListsForAnalysisRun2
   if (my_year == 2017) lumi = 44.6306e6;
   if (my_year == 2018) lumi = 58.7916e6;
   for (Long64_t jentry=0; jentry<nentries;jentry+=increment) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      //if (met_met < 200) continue;
      my_weight = lumi*weight/my_sumw;
      myTree->Fill();
      counter++;
      //if (counter == target_events) break;
      if (nentries < 1000000 && counter%1000 == 0) cout << "Added " << counter << " events, on entry " << jentry << endl;
      if (nentries >= 1000000 && counter%10000 == 0) cout << "Added " << counter << " events, on entry " << jentry << endl;
   }
   cout << "Finished loop; added " << counter << " events" << endl;
}

void fileSkimmer(TString fileName){
	class fileSkimmer t(fileName);
        cout << fileName << endl;
        t.declareNewTree(fileName);
	t.Loop();
        cout << "Writing output..." << endl;
        t.WriteOutput();
        cout << "DONE" << endl;
}

