//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr 26 17:23:04 2023 by ROOT version 6.24/08
// from TTree PostSel/PostSel
// found on file: user.ebusch.515487.root
//////////////////////////////////////////////////////////

#ifndef fileSkimmer_h
#define fileSkimmer_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "string"

class fileSkimmer {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   TTree	  *myTree;    // pointer to the new tree
   TFile 	  *myFile;    // pointer to the new file
   TString	  fileName;
// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *all_jets_pt;
   vector<float>   *all_jets_eta;
   vector<float>   *all_jets_phi;
   vector<float>   *all_jets_E;
   vector<float>   *all_jets_NumTrkPt500PV;
   vector<float>   *all_jets_NumTrkPt1000PV;
   vector<float>   *all_jets_SumPtTrkPt500PV;
   vector<float>   *all_jets_TrackWidthPt1000PV;
   vector<float>   *all_jets_Width;
   vector<float>   *all_jets_EMFrac;
   vector<float>   *all_jets_DL1dv01;
   vector<float>   *all_jets_GN1;
   vector<float>   *all_jets_FracSamplingMax;
   string          *year;
   Double_t        runNumber;
   Double_t        eventNumber;
   Double_t        mcEventWeight;
   Double_t        weight;
   Double_t        my_weight = 0;
   Double_t        SumW;
   Double_t        n_jets;
   Double_t        jet1_pt;
   Double_t        jet1_eta;
   Double_t        jet1_phi;
   Double_t        jet1_E;
   Double_t        jet2_pt;
   Double_t        jet2_eta;
   Double_t        jet2_phi;
   Double_t        jet2_E;
   Double_t        jet1_DL1dv01;
   Double_t        jet1_GN1;
   Double_t        jet1_EMFrac;
   Double_t        jet1_FracSamplingMax;
   Double_t        jet1_Width;
   Double_t        jet2_DL1dv01;
   Double_t        jet2_GN1;
   Double_t        jet2_EMFrac;
   Double_t        jet2_FracSamplingMax;
   Double_t        jet2_Width;
   Double_t        jet1_NumTrkPt500PV;
   Double_t        jet1_NumTrkPt1000PV;
   Double_t        jet1_SumPtTrkPt500PV;
   Double_t        jet1_TrackWidthPt1000PV;
   Double_t        jet2_NumTrkPt500PV;
   Double_t        jet2_NumTrkPt1000PV;
   Double_t        jet2_SumPtTrkPt500PV;
   Double_t        jet2_TrackWidthPt1000PV;
   Double_t        maxphi_minphi;
   Double_t        dphi_min;
   Double_t        dphi_max;
   Double_t        dphi_min_MET;
   Double_t        dphi_MET_j1j2;
   Double_t        pt_balance_12;
   Double_t        mjj_12;
   Double_t        mT_jj;
   Double_t        mT_jj_neg;
   Double_t        met_jj_neg;
   Double_t        dR_12;
   Double_t        deta_12;
   Double_t        deltaY_12;
   Double_t        hT;
   Double_t        rT;
   Double_t        aplanarity;
   Double_t        sphericity;
   Double_t        sphericity_T;
   Double_t        met_met;
   Double_t        met_phi;

   // List of branches
   TBranch        *b_all_jets_pt;   //!
   TBranch        *b_all_jets_eta;   //!
   TBranch        *b_all_jets_phi;   //!
   TBranch        *b_all_jets_E;   //!
   TBranch        *b_all_jets_NumTrkPt500PV;   //!
   TBranch        *b_all_jets_NumTrkPt1000PV;   //!
   TBranch        *b_all_jets_SumPtTrkPt500PV;   //!
   TBranch        *b_all_jets_TrackWidthPt1000PV;   //!
   TBranch        *b_all_jets_Width;   //!
   TBranch        *b_all_jets_EMFrac;   //!
   TBranch        *b_all_jets_DL1dv01;   //!
   TBranch        *b_all_jets_GN1;   //!
   TBranch        *b_all_jets_FracSamplingMax;   //!
   TBranch        *b_year;   //!
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_mcEventWeight;   //!
   TBranch        *b_weight;   //!
   TBranch        *b_SumW;   //!
   TBranch        *b_n_jets;   //!
   TBranch        *b_jet1_pt;   //!
   TBranch        *b_jet1_eta;   //!
   TBranch        *b_jet1_phi;   //!
   TBranch        *b_jet1_E;   //!
   TBranch        *b_jet2_pt;   //!
   TBranch        *b_jet2_eta;   //!
   TBranch        *b_jet2_phi;   //!
   TBranch        *b_jet2_E;   //!
   TBranch        *b_jet1_DL1dv01;   //!
   TBranch        *b_jet1_GN1;   //!
   TBranch        *b_jet1_EMFrac;   //!
   TBranch        *b_jet1_FracSamplingMax;   //!
   TBranch        *b_jet1_Width;   //!
   TBranch        *b_jet2_DL1dv01;   //!
   TBranch        *b_jet2_GN1;   //!
   TBranch        *b_jet2_EMFrac;   //!
   TBranch        *b_jet2_FracSamplingMax;   //!
   TBranch        *b_jet2_Width;   //!
   TBranch        *b_jet1_NumTrkPt500PV;   //!
   TBranch        *b_jet1_NumTrkPt1000PV;   //!
   TBranch        *b_jet1_SumPtTrkPt500PV;   //!
   TBranch        *b_jet1_TrackWidthPt1000PV;   //!
   TBranch        *b_jet2_NumTrkPt500PV;   //!
   TBranch        *b_jet2_NumTrkPt1000PV;   //!
   TBranch        *b_jet2_SumPtTrkPt500PV;   //!
   TBranch        *b_jet2_TrackWidthPt1000PV;   //!
   TBranch        *b_maxphi_minphi;   //!
   TBranch        *b_dphi_min;   //!
   TBranch        *b_dphi_max;   //!
   TBranch        *b_dphi_min_MET;   //!
   TBranch        *b_dphi_MET_j1j2;   //!
   TBranch        *b_pt_balance_12;   //!
   TBranch        *b_mjj_12;   //!
   TBranch        *b_mT_jj;   //!
   TBranch        *b_mT_jj_neg;   //!
   TBranch        *b_met_jj_neg;   //!
   TBranch        *b_dR_12;   //!
   TBranch        *b_deta_12;   //!
   TBranch        *b_deltaY_12;   //!
   TBranch        *b_hT;   //!
   TBranch        *b_rT;   //!
   TBranch        *b_aplanarity;   //!
   TBranch        *b_sphericity;   //!
   TBranch        *b_sphericity_T;   //!
   TBranch        *b_met_met;   //!
   TBranch        *b_met_phi;   //!

   fileSkimmer(TString fileName);
   virtual ~fileSkimmer();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     declareNewTree(TString fileName);
   virtual void     WriteOutput();
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef fileSkimmer_cxx
fileSkimmer::fileSkimmer(TString fileName) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   TTree *tree=0;
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(fileName);
      if (!f || !f->IsOpen()) {
         f = new TFile(fileName);
      }
      f->GetObject("PostSel",tree);

   }
   Init(tree);
}

fileSkimmer::~fileSkimmer()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t fileSkimmer::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t fileSkimmer::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void fileSkimmer::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   all_jets_pt = 0;
   all_jets_eta = 0;
   all_jets_phi = 0;
   all_jets_E = 0;
   all_jets_NumTrkPt500PV = 0;
   all_jets_NumTrkPt1000PV = 0;
   all_jets_SumPtTrkPt500PV = 0;
   all_jets_TrackWidthPt1000PV = 0;
   all_jets_Width = 0;
   all_jets_EMFrac = 0;
   all_jets_DL1dv01 = 0;
   all_jets_GN1 = 0;
   all_jets_FracSamplingMax = 0;
   year = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("all_jets_pt", &all_jets_pt, &b_all_jets_pt);
   fChain->SetBranchAddress("all_jets_eta", &all_jets_eta, &b_all_jets_eta);
   fChain->SetBranchAddress("all_jets_phi", &all_jets_phi, &b_all_jets_phi);
   fChain->SetBranchAddress("all_jets_E", &all_jets_E, &b_all_jets_E);
   fChain->SetBranchAddress("all_jets_NumTrkPt500PV", &all_jets_NumTrkPt500PV, &b_all_jets_NumTrkPt500PV);
   fChain->SetBranchAddress("all_jets_NumTrkPt1000PV", &all_jets_NumTrkPt1000PV, &b_all_jets_NumTrkPt1000PV);
   fChain->SetBranchAddress("all_jets_SumPtTrkPt500PV", &all_jets_SumPtTrkPt500PV, &b_all_jets_SumPtTrkPt500PV);
   fChain->SetBranchAddress("all_jets_TrackWidthPt1000PV", &all_jets_TrackWidthPt1000PV, &b_all_jets_TrackWidthPt1000PV);
   fChain->SetBranchAddress("all_jets_Width", &all_jets_Width, &b_all_jets_Width);
   fChain->SetBranchAddress("all_jets_EMFrac", &all_jets_EMFrac, &b_all_jets_EMFrac);
   fChain->SetBranchAddress("all_jets_DL1dv01", &all_jets_DL1dv01, &b_all_jets_DL1dv01);
   fChain->SetBranchAddress("all_jets_GN1", &all_jets_GN1, &b_all_jets_GN1);
   fChain->SetBranchAddress("all_jets_FracSamplingMax", &all_jets_FracSamplingMax, &b_all_jets_FracSamplingMax);
   fChain->SetBranchAddress("year", &year, &b_year);
   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("mcEventWeight", &mcEventWeight, &b_mcEventWeight);
   fChain->SetBranchAddress("weight", &weight, &b_weight);
   fChain->SetBranchAddress("SumW", &SumW, &b_SumW);
   fChain->SetBranchAddress("n_jets", &n_jets, &b_n_jets);
   fChain->SetBranchAddress("jet1_pt", &jet1_pt, &b_jet1_pt);
   fChain->SetBranchAddress("jet1_eta", &jet1_eta, &b_jet1_eta);
   fChain->SetBranchAddress("jet1_phi", &jet1_phi, &b_jet1_phi);
   fChain->SetBranchAddress("jet1_E", &jet1_E, &b_jet1_E);
   fChain->SetBranchAddress("jet2_pt", &jet2_pt, &b_jet2_pt);
   fChain->SetBranchAddress("jet2_eta", &jet2_eta, &b_jet2_eta);
   fChain->SetBranchAddress("jet2_phi", &jet2_phi, &b_jet2_phi);
   fChain->SetBranchAddress("jet2_E", &jet2_E, &b_jet2_E);
   fChain->SetBranchAddress("jet1_DL1dv01", &jet1_DL1dv01, &b_jet1_DL1dv01);
   fChain->SetBranchAddress("jet1_GN1", &jet1_GN1, &b_jet1_GN1);
   fChain->SetBranchAddress("jet1_EMFrac", &jet1_EMFrac, &b_jet1_EMFrac);
   fChain->SetBranchAddress("jet1_FracSamplingMax", &jet1_FracSamplingMax, &b_jet1_FracSamplingMax);
   fChain->SetBranchAddress("jet1_Width", &jet1_Width, &b_jet1_Width);
   fChain->SetBranchAddress("jet2_DL1dv01", &jet2_DL1dv01, &b_jet2_DL1dv01);
   fChain->SetBranchAddress("jet2_GN1", &jet2_GN1, &b_jet2_GN1);
   fChain->SetBranchAddress("jet2_EMFrac", &jet2_EMFrac, &b_jet2_EMFrac);
   fChain->SetBranchAddress("jet2_FracSamplingMax", &jet2_FracSamplingMax, &b_jet2_FracSamplingMax);
   fChain->SetBranchAddress("jet2_Width", &jet2_Width, &b_jet2_Width);
   fChain->SetBranchAddress("jet1_NumTrkPt500PV", &jet1_NumTrkPt500PV, &b_jet1_NumTrkPt500PV);
   fChain->SetBranchAddress("jet1_NumTrkPt1000PV", &jet1_NumTrkPt1000PV, &b_jet1_NumTrkPt1000PV);
   fChain->SetBranchAddress("jet1_SumPtTrkPt500PV", &jet1_SumPtTrkPt500PV, &b_jet1_SumPtTrkPt500PV);
   fChain->SetBranchAddress("jet1_TrackWidthPt1000PV", &jet1_TrackWidthPt1000PV, &b_jet1_TrackWidthPt1000PV);
   fChain->SetBranchAddress("jet2_NumTrkPt500PV", &jet2_NumTrkPt500PV, &b_jet2_NumTrkPt500PV);
   fChain->SetBranchAddress("jet2_NumTrkPt1000PV", &jet2_NumTrkPt1000PV, &b_jet2_NumTrkPt1000PV);
   fChain->SetBranchAddress("jet2_SumPtTrkPt500PV", &jet2_SumPtTrkPt500PV, &b_jet2_SumPtTrkPt500PV);
   fChain->SetBranchAddress("jet2_TrackWidthPt1000PV", &jet2_TrackWidthPt1000PV, &b_jet2_TrackWidthPt1000PV);
   fChain->SetBranchAddress("maxphi_minphi", &maxphi_minphi, &b_maxphi_minphi);
   fChain->SetBranchAddress("dphi_min", &dphi_min, &b_dphi_min);
   fChain->SetBranchAddress("dphi_max", &dphi_max, &b_dphi_max);
   fChain->SetBranchAddress("dphi_min_MET", &dphi_min_MET, &b_dphi_min_MET);
   fChain->SetBranchAddress("dphi_MET_j1j2", &dphi_MET_j1j2, &b_dphi_MET_j1j2);
   fChain->SetBranchAddress("pt_balance_12", &pt_balance_12, &b_pt_balance_12);
   fChain->SetBranchAddress("mjj_12", &mjj_12, &b_mjj_12);
   fChain->SetBranchAddress("mT_jj", &mT_jj, &b_mT_jj);
   fChain->SetBranchAddress("mT_jj_neg", &mT_jj_neg, &b_mT_jj_neg);
   fChain->SetBranchAddress("met_jj_neg", &met_jj_neg, &b_met_jj_neg);
   fChain->SetBranchAddress("dR_12", &dR_12, &b_dR_12);
   fChain->SetBranchAddress("deta_12", &deta_12, &b_deta_12);
   fChain->SetBranchAddress("deltaY_12", &deltaY_12, &b_deltaY_12);
   fChain->SetBranchAddress("hT", &hT, &b_hT);
   fChain->SetBranchAddress("rT", &rT, &b_rT);
   fChain->SetBranchAddress("aplanarity", &aplanarity, &b_aplanarity);
   fChain->SetBranchAddress("sphericity", &sphericity, &b_sphericity);
   fChain->SetBranchAddress("sphericity_T", &sphericity_T, &b_sphericity_T);
   fChain->SetBranchAddress("met_met", &met_met, &b_met_met);
   fChain->SetBranchAddress("met_phi", &met_phi, &b_met_phi);
   Notify();
}

void fileSkimmer::declareNewTree(TString fileName)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   myFile = new TFile("skim."+fileName, "RECREATE");
   myTree = new TTree("PostSel","PostSel");
   //all_jets_pt = 0;
   //all_jets_eta = 0;
   //all_jets_phi = 0;
   //all_jets_E = 0;
   year = 0;

   myTree->Branch("all_jets_pt", &all_jets_pt);
   myTree->Branch("all_jets_eta", &all_jets_eta);
   myTree->Branch("all_jets_phi", &all_jets_phi);
   myTree->Branch("all_jets_E", &all_jets_E);
   myTree->Branch("all_jets_NumTrkPt500PV", &all_jets_NumTrkPt500PV);
   myTree->Branch("all_jets_NumTrkPt1000PV", &all_jets_NumTrkPt1000PV);
   myTree->Branch("all_jets_SumPtTrkPt500PV", &all_jets_SumPtTrkPt500PV);
   myTree->Branch("all_jets_TrackWidthPt1000PV", &all_jets_TrackWidthPt1000PV);
   myTree->Branch("all_jets_Width", &all_jets_Width);
   myTree->Branch("all_jets_EMFrac", &all_jets_EMFrac);
   myTree->Branch("all_jets_DL1dv01", &all_jets_DL1dv01);
   myTree->Branch("all_jets_GN1", &all_jets_GN1);
   myTree->Branch("all_jets_FracSamplingMax", &all_jets_FracSamplingMax);
   myTree->Branch("year", &year);
   myTree->Branch("runNumber", &runNumber);
   myTree->Branch("eventNumber", &eventNumber);
   myTree->Branch("mcEventWeight", &mcEventWeight);
   myTree->Branch("weight", &my_weight);
   myTree->Branch("SumW", &SumW);
   myTree->Branch("n_jets", &n_jets);
   myTree->Branch("jet1_pt", &jet1_pt);
   myTree->Branch("jet1_eta", &jet1_eta);
   myTree->Branch("jet1_phi", &jet1_phi);
   myTree->Branch("jet1_E", &jet1_E);
   myTree->Branch("jet2_pt", &jet2_pt);
   myTree->Branch("jet2_eta", &jet2_eta);
   myTree->Branch("jet2_phi", &jet2_phi);
   myTree->Branch("jet2_E", &jet2_E);
   myTree->Branch("jet1_DL1dv01", &jet1_DL1dv01);
   myTree->Branch("jet1_GN1", &jet1_GN1);
   myTree->Branch("jet1_EMFrac", &jet1_EMFrac);
   myTree->Branch("jet1_FracSamplingMax", &jet1_FracSamplingMax);
   myTree->Branch("jet1_Width", &jet1_Width);
   myTree->Branch("jet2_DL1dv01", &jet2_DL1dv01);
   myTree->Branch("jet2_GN1", &jet2_GN1);
   myTree->Branch("jet2_EMFrac", &jet2_EMFrac);
   myTree->Branch("jet2_FracSamplingMax", &jet2_FracSamplingMax);
   myTree->Branch("jet2_Width", &jet2_Width);
   myTree->Branch("jet1_NumTrkPt500PV", &jet1_NumTrkPt500PV);
   myTree->Branch("jet1_NumTrkPt1000PV", &jet1_NumTrkPt1000PV);
   myTree->Branch("jet1_SumPtTrkPt500PV", &jet1_SumPtTrkPt500PV);
   myTree->Branch("jet1_TrackWidthPt1000PV", &jet1_TrackWidthPt1000PV);
   myTree->Branch("jet2_NumTrkPt500PV", &jet2_NumTrkPt500PV);
   myTree->Branch("jet2_NumTrkPt1000PV", &jet2_NumTrkPt1000PV);
   myTree->Branch("jet2_SumPtTrkPt500PV", &jet2_SumPtTrkPt500PV);
   myTree->Branch("jet2_TrackWidthPt1000PV", &jet2_TrackWidthPt1000PV);
   myTree->Branch("maxphi_minphi", &maxphi_minphi);
   myTree->Branch("dphi_min", &dphi_min);
   myTree->Branch("dphi_max", &dphi_max);
   myTree->Branch("dphi_min_MET", &dphi_min_MET);
   myTree->Branch("dphi_MET_j1j2", &dphi_MET_j1j2);
   myTree->Branch("pt_balance_12", &pt_balance_12);
   myTree->Branch("mjj_12", &mjj_12);
   myTree->Branch("mT_jj", &mT_jj);
   myTree->Branch("mT_jj_neg", &mT_jj_neg);
   myTree->Branch("met_jj_neg", &met_jj_neg);
   myTree->Branch("dR_12", &dR_12);
   myTree->Branch("deta_12", &deta_12);
   myTree->Branch("deltaY_12", &deltaY_12);
   myTree->Branch("hT", &hT);
   myTree->Branch("rT", &rT);
   myTree->Branch("aplanarity", &aplanarity);
   myTree->Branch("sphericity", &sphericity);
   myTree->Branch("sphericity_T", &sphericity_T);
   myTree->Branch("met_met", &met_met);
   myTree->Branch("met_phi", &met_phi);
}

Bool_t fileSkimmer::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void fileSkimmer::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t fileSkimmer::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef fileSkimmer_cxx
