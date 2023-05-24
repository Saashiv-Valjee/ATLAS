#define v8p1Class_cxx
#include "v8p1Class.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void fileSkimmer::WriteOutput(){
	myTree->Write();
	myFile->Close();
}

void v8p1Class::Loop()
{
//   In a ROOT session, you can do:
//      root> .L v8p1Class.C
//      root> v8p1Class t
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
   Long64_t increment = 100;
   //if (target_events > nentries) cout << "ERROR: requesting more events than available (" << nentries << ")" << endl;

   Long64_t nbytes = 0, nb = 0;
   int counter = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry+=increment) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      my_weight = weight * 100;
      myTree->Fill();
      counter++;
      //if (counter == target_events) break;
      if (nentries < 1000000 && counter%1000 == 0) cout << "Added " << counter << " events, on entry " << jentry << endl;
      if (nentries >= 1000000 && counter%10000 == 0) cout << "Added " << counter << " events, on entry " << jentry << endl;
   }
   cout << "Finished loop; added " << counter << " events" << endl;
}

void v8p1Class(TString fileName){
	class v8p1Class t(fileName);
        cout << fileName << endl;
        t.declareNewTree(fileName);
	t.Loop();
        cout << "Writing output..." << endl;
        t.WriteOutput();
        cout << "DONE" << endl;
}

