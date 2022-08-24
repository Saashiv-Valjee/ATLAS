//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue May 31 18:20:37 2022 by ROOT version 6.24/06
// from TTree nominal/nominal
// found on file: user.ebusch.29093733._000001.tree.root
//////////////////////////////////////////////////////////

#ifndef MicroNTupleMaker_h
#define MicroNTupleMaker_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TH1F.h>
#include "TMatrixD.h"
#include "TDecompSVD.h"

// Header file for the classes stored in the TTree if any.
#include "vector"
#include <map>
#include <iostream>
#include <filesystem>
#include <iomanip>

class MicroNTupleMaker {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Settings
   bool debug = false;

   // Output tree
   vector<string> treenames;
   map<string,TTree*> tree_output;
   map<string,double> tree_output_vars;
   map<string,string> tree_output_vars_string;
   map<string,vector<float>*> tree_output_vars_vector;

   //string variables
   string year_mc;

   // svj & asvj variables
   float weight_scale, sumw;
   int n_svj, n_asvj;
   int n_r04_jets, n_r10_jets;
   float dphi_min, dphi_max, maxphi_minphi;
   float pt_balance_12, pt_balance_sa;
   float mjj_12, mjj_sa, mT_jj;
   float hT, dR_12, deta_12, rT;
   float jet1_mT, jet2_mT, jet_svj_mT, jet_asvj_mT;
   float deltaY_12, deltaY_sa;
   float aplanarity, sphericity, sphericity_T;

   // Cutflow histograms
   TH1F *cutflow;

   // Declaration of leaf types
   Int_t           runNumber;
   Long64_t        eventNumber;
   Int_t           lumiBlock;
   UInt_t          coreFlags;
   Int_t           bcid;
   Int_t           mcEventNumber;
   Int_t           mcChannelNumber;
   Float_t         mcEventWeight;
   Int_t           na4_pflowjets;
   vector<float>   *a4_pflowjets_E;
   vector<float>   *a4_pflowjets_pt;
   vector<float>   *a4_pflowjets_phi;
   vector<float>   *a4_pflowjets_eta;
   vector<int>     *a4_pflowjets_clean_passLooseBad;
   vector<int>     *a4_pflowjets_clean_passTightBad;
   vector<int>     *a4_pflowjets_numConstituents;
   Int_t           na10_lctopojets;
   vector<float>   *a10_lctopojets_m;
   vector<float>   *a10_lctopojets_pt;
   vector<float>   *a10_lctopojets_phi;
   vector<float>   *a10_lctopojets_eta;
   vector<float>   *a10_lctopojets_Split12;
   vector<float>   *a10_lctopojets_Split23;
   vector<float>   *a10_lctopojets_Split34;
   vector<float>   *a10_lctopojets_tau1_wta;
   vector<float>   *a10_lctopojets_tau2_wta;
   vector<float>   *a10_lctopojets_tau3_wta;
   vector<float>   *a10_lctopojets_tau21_wta;
   vector<float>   *a10_lctopojets_tau32_wta;
   vector<float>   *a10_lctopojets_ECF1;
   vector<float>   *a10_lctopojets_ECF2;
   vector<float>   *a10_lctopojets_ECF3;
   vector<float>   *a10_lctopojets_C2;
   vector<float>   *a10_lctopojets_D2;
   vector<float>   *a10_lctopojets_NTrimSubjets;
   vector<int>     *a10_lctopojets_Nclusters;
   vector<int>     *a10_lctopojets_nTracks;
   vector<int>     *a10_lctopojets_ungrtrk500;
   vector<float>   *a10_lctopojets_EMFrac;
   vector<int>     *a10_lctopojets_nChargedParticles;
   Float_t         metFinalClus;
   Float_t         metFinalClusPx;
   Float_t         metFinalClusPy;
   Float_t         metFinalClusSumEt;
   Float_t         metFinalClusPhi;

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_coreFlags;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_mcEventNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mcEventWeight;   //!
   TBranch        *b_na4_pflowjets;   //!
   TBranch        *b_a4_pflowjets_E;   //!
   TBranch        *b_a4_pflowjets_pt;   //!
   TBranch        *b_a4_pflowjets_phi;   //!
   TBranch        *b_a4_pflowjets_eta;   //!
   TBranch        *b_a4_pflowjets_clean_passLooseBad;   //!
   TBranch        *b_a4_pflowjets_clean_passTightBad;   //!
   TBranch        *b_a4_pflowjets_numConstituents;   //!
   TBranch        *b_na10_lctopojets;   //!
   TBranch        *b_a10_lctopojets_m;   //!
   TBranch        *b_a10_lctopojets_pt;   //!
   TBranch        *b_a10_lctopojets_phi;   //!
   TBranch        *b_a10_lctopojets_eta;   //!
   TBranch        *b_a10_lctopojets_Split12;   //!
   TBranch        *b_a10_lctopojets_Split23;   //!
   TBranch        *b_a10_lctopojets_Split34;   //!
   TBranch        *b_a10_lctopojets_tau1_wta;   //!
   TBranch        *b_a10_lctopojets_tau2_wta;   //!
   TBranch        *b_a10_lctopojets_tau3_wta;   //!
   TBranch        *b_a10_lctopojets_tau21_wta;   //!
   TBranch        *b_a10_lctopojets_tau32_wta;   //!
   TBranch        *b_a10_lctopojets_ECF1;   //!
   TBranch        *b_a10_lctopojets_ECF2;   //!
   TBranch        *b_a10_lctopojets_ECF3;   //!
   TBranch        *b_a10_lctopojets_C2;   //!
   TBranch        *b_a10_lctopojets_D2;   //!
   TBranch        *b_a10_lctopojets_NTrimSubjets;   //!
   TBranch        *b_a10_lctopojets_Nclusters;   //!
   TBranch        *b_a10_lctopojets_nTracks;   //!
   TBranch        *b_a10_lctopojets_ungrtrk500;   //!
   TBranch        *b_a10_lctopojets_EMFrac;   //!
   TBranch        *b_a10_lctopojets_nChargedParticles;   //!
   TBranch        *b_metFinalClus;   //!
   TBranch        *b_metFinalClusPx;   //!
   TBranch        *b_metFinalClusPy;   //!
   TBranch        *b_metFinalClusSumEt;   //!
   TBranch        *b_metFinalClusPhi;   //!

   MicroNTupleMaker(TTree *tree=0);
   virtual ~MicroNTupleMaker();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   // FunctionHelpers 
   virtual vector<pair<int,float>> FindSVJ( vector<float> *jet_phi);
   virtual float    		GetPtBalance(TLorentzVector v1, TLorentzVector v2);
   virtual float    		GetDPhi(float phi1, float phi2);
   virtual float    		GetMjj(TLorentzVector v1, TLorentzVector v2);
   virtual float    		GetMt(TLorentzVector v1, TLorentzVector v2, float met, float met_phi);
   virtual float    		GetDeltaY(TLorentzVector v1, TLorentzVector v2);
   virtual float    		GetHT(vector<float> *jet_pt);
   virtual float    		GetdR(TLorentzVector v1, TLorentzVector v2);
   virtual float    		GetDEta(float eta1, float eta2);
   virtual map<string,float> 	GetShapeVariables(vector<float> *jet_pt, vector<float> *jet_eta, vector<float> *jet_phi, vector<float> *jet_m, bool smallR);

   // OutputTreeHelper
   virtual void		DeclareOutputTrees();
   virtual void		FillOutputTrees( string treename );
   virtual void		WriteOutputTrees();

   // HistHelper
   virtual void    	DeclareHistograms();
   virtual void     	WriteHistograms();

   // WeightHelper
   virtual void     	SetWeight(string dsid);
   virtual double     	GetSumW(string dsid);
   virtual double     	GetGenFilterEff(string dsid);
   virtual double     	GetXSection(string dsid);
};

#endif

#ifdef MicroNTupleMaker_cxx
MicroNTupleMaker::MicroNTupleMaker(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      cout<<"Error: Tree not specified"<<endl;
      return;
   }
   Init(tree);
}

MicroNTupleMaker::~MicroNTupleMaker()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MicroNTupleMaker::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MicroNTupleMaker::LoadTree(Long64_t entry)
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

void MicroNTupleMaker::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   a4_pflowjets_E = 0;
   a4_pflowjets_pt = 0;
   a4_pflowjets_phi = 0;
   a4_pflowjets_eta = 0;
   a4_pflowjets_clean_passLooseBad = 0;
   a4_pflowjets_clean_passTightBad = 0;
   a4_pflowjets_numConstituents = 0;
   a10_lctopojets_m = 0;
   a10_lctopojets_pt = 0;
   a10_lctopojets_phi = 0;
   a10_lctopojets_eta = 0;
   a10_lctopojets_Split12 = 0;
   a10_lctopojets_Split23 = 0;
   a10_lctopojets_Split34 = 0;
   a10_lctopojets_tau1_wta = 0;
   a10_lctopojets_tau2_wta = 0;
   a10_lctopojets_tau3_wta = 0;
   a10_lctopojets_tau21_wta = 0;
   a10_lctopojets_tau32_wta = 0;
   a10_lctopojets_ECF1 = 0;
   a10_lctopojets_ECF2 = 0;
   a10_lctopojets_ECF3 = 0;
   a10_lctopojets_C2 = 0;
   a10_lctopojets_D2 = 0;
   a10_lctopojets_NTrimSubjets = 0;
   a10_lctopojets_Nclusters = 0;
   a10_lctopojets_nTracks = 0;
   a10_lctopojets_ungrtrk500 = 0;
   a10_lctopojets_EMFrac = 0;
   a10_lctopojets_nChargedParticles = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runNumber", &runNumber, &b_runNumber);
   fChain->SetBranchAddress("eventNumber", &eventNumber, &b_eventNumber);
   fChain->SetBranchAddress("lumiBlock", &lumiBlock, &b_lumiBlock);
   fChain->SetBranchAddress("coreFlags", &coreFlags, &b_coreFlags);
   fChain->SetBranchAddress("bcid", &bcid, &b_bcid);
   fChain->SetBranchAddress("mcEventNumber", &mcEventNumber, &b_mcEventNumber);
   fChain->SetBranchAddress("mcChannelNumber", &mcChannelNumber, &b_mcChannelNumber);
   fChain->SetBranchAddress("mcEventWeight", &mcEventWeight, &b_mcEventWeight);
   fChain->SetBranchAddress("na4_pflowjets", &na4_pflowjets, &b_na4_pflowjets);
   fChain->SetBranchAddress("a4_pflowjets_E", &a4_pflowjets_E, &b_a4_pflowjets_E);
   fChain->SetBranchAddress("a4_pflowjets_pt", &a4_pflowjets_pt, &b_a4_pflowjets_pt);
   fChain->SetBranchAddress("a4_pflowjets_phi", &a4_pflowjets_phi, &b_a4_pflowjets_phi);
   fChain->SetBranchAddress("a4_pflowjets_eta", &a4_pflowjets_eta, &b_a4_pflowjets_eta);
   fChain->SetBranchAddress("a4_pflowjets_clean_passLooseBad", &a4_pflowjets_clean_passLooseBad, &b_a4_pflowjets_clean_passLooseBad);
   fChain->SetBranchAddress("a4_pflowjets_clean_passTightBad", &a4_pflowjets_clean_passTightBad, &b_a4_pflowjets_clean_passTightBad);
   fChain->SetBranchAddress("a4_pflowjets_numConstituents", &a4_pflowjets_numConstituents, &b_a4_pflowjets_numConstituents);
   fChain->SetBranchAddress("na10_lctopojets", &na10_lctopojets, &b_na10_lctopojets);
   fChain->SetBranchAddress("a10_lctopojets_m", &a10_lctopojets_m, &b_a10_lctopojets_m);
   fChain->SetBranchAddress("a10_lctopojets_pt", &a10_lctopojets_pt, &b_a10_lctopojets_pt);
   fChain->SetBranchAddress("a10_lctopojets_phi", &a10_lctopojets_phi, &b_a10_lctopojets_phi);
   fChain->SetBranchAddress("a10_lctopojets_eta", &a10_lctopojets_eta, &b_a10_lctopojets_eta);
   fChain->SetBranchAddress("a10_lctopojets_Split12", &a10_lctopojets_Split12, &b_a10_lctopojets_Split12);
   fChain->SetBranchAddress("a10_lctopojets_Split23", &a10_lctopojets_Split23, &b_a10_lctopojets_Split23);
   fChain->SetBranchAddress("a10_lctopojets_Split34", &a10_lctopojets_Split34, &b_a10_lctopojets_Split34);
   fChain->SetBranchAddress("a10_lctopojets_tau1_wta", &a10_lctopojets_tau1_wta, &b_a10_lctopojets_tau1_wta);
   fChain->SetBranchAddress("a10_lctopojets_tau2_wta", &a10_lctopojets_tau2_wta, &b_a10_lctopojets_tau2_wta);
   fChain->SetBranchAddress("a10_lctopojets_tau3_wta", &a10_lctopojets_tau3_wta, &b_a10_lctopojets_tau3_wta);
   fChain->SetBranchAddress("a10_lctopojets_tau21_wta", &a10_lctopojets_tau21_wta, &b_a10_lctopojets_tau21_wta);
   fChain->SetBranchAddress("a10_lctopojets_tau32_wta", &a10_lctopojets_tau32_wta, &b_a10_lctopojets_tau32_wta);
   fChain->SetBranchAddress("a10_lctopojets_ECF1", &a10_lctopojets_ECF1, &b_a10_lctopojets_ECF1);
   fChain->SetBranchAddress("a10_lctopojets_ECF2", &a10_lctopojets_ECF2, &b_a10_lctopojets_ECF2);
   fChain->SetBranchAddress("a10_lctopojets_ECF3", &a10_lctopojets_ECF3, &b_a10_lctopojets_ECF3);
   fChain->SetBranchAddress("a10_lctopojets_C2", &a10_lctopojets_C2, &b_a10_lctopojets_C2);
   fChain->SetBranchAddress("a10_lctopojets_D2", &a10_lctopojets_D2, &b_a10_lctopojets_D2);
   fChain->SetBranchAddress("a10_lctopojets_NTrimSubjets", &a10_lctopojets_NTrimSubjets, &b_a10_lctopojets_NTrimSubjets);
   fChain->SetBranchAddress("a10_lctopojets_Nclusters", &a10_lctopojets_Nclusters, &b_a10_lctopojets_Nclusters);
   fChain->SetBranchAddress("a10_lctopojets_nTracks", &a10_lctopojets_nTracks, &b_a10_lctopojets_nTracks);
   fChain->SetBranchAddress("a10_lctopojets_ungrtrk500", &a10_lctopojets_ungrtrk500, &b_a10_lctopojets_ungrtrk500);
   fChain->SetBranchAddress("a10_lctopojets_EMFrac", &a10_lctopojets_EMFrac, &b_a10_lctopojets_EMFrac);
   fChain->SetBranchAddress("a10_lctopojets_nChargedParticles", &a10_lctopojets_nChargedParticles, &b_a10_lctopojets_nChargedParticles);
   fChain->SetBranchAddress("metFinalClus", &metFinalClus, &b_metFinalClus);
   fChain->SetBranchAddress("metFinalClusPx", &metFinalClusPx, &b_metFinalClusPx);
   fChain->SetBranchAddress("metFinalClusPy", &metFinalClusPy, &b_metFinalClusPy);
   fChain->SetBranchAddress("metFinalClusSumEt", &metFinalClusSumEt, &b_metFinalClusSumEt);
   fChain->SetBranchAddress("metFinalClusPhi", &metFinalClusPhi, &b_metFinalClusPhi);
   Notify();
}

Bool_t MicroNTupleMaker::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MicroNTupleMaker::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MicroNTupleMaker::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MicroNTupleMaker_cxx
