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

   //file variable
   string year_mc;
   Int_t dsid_int = 0;

   // svj & asvj variables
   float weight_scale, sumw;
   int n_svj, n_asvj;
   float dphi_min, dphi_max, maxphi_minphi;
   float dphi_MET_j1j2;
   float pt_balance_12;
   float mjj_12, mT_jj;
   float mT_jj_neg, met_jj_neg;
   //float mJJ_12, mT_JJ;
   float hT, dR_12, deta_12, rT;
   float deltaY_12, dphi_12;
   float aplanarity, sphericity, sphericity_T;

   //Weight histogram
   TH1F *MetaData_EventCount;
   // Cutflow histograms
   TH1F *cutflow = new TH1F("cutflow", "cutflow", 25,1,26);
   TH1F *cutflow_weighted = new TH1F("cutflow_weighted", "cutflow_weighted", 25,1,26);
   TH1F *metadata;

   // Declaration of leaf types
   Int_t           runNumber;
   Long64_t        eventNumber;
   Int_t           lumiBlock;
   UInt_t          coreFlags;
   Int_t           bcid;
   Int_t           mcEventNumber;
   Int_t           mcChannelNumber;
   Float_t         mcEventWeight;
   Int_t           passL1;
   Int_t           passHLT;
   vector<string>  *passedTriggers;
   vector<string>  *disabledTriggers;
   Int_t           njet;
   vector<float>   *jet_E;
   vector<float>   *jet_pt;
   vector<float>   *jet_phi;
   vector<float>   *jet_eta;
   vector<float>   *jet_HECFrac;
   vector<float>   *jet_CentroidR;
   vector<float>   *jet_LowEtConstituentsFrac;
   vector<float>   *jet_EMFrac;
   vector<float>   *jet_FracSamplingMax;
   vector<float>   *jet_FracSamplingMaxIndex;
   vector<float>   *jet_GhostMuonSegmentCount;
   vector<float>   *jet_Width;
   vector<int>     *jet_GhostTrackCount;
   vector<float>   *jet_GhostTrackPt;
   vector<vector<float> > *jet_GhostTrack_pt;
   vector<vector<float> > *jet_GhostTrack_qOverP;
   vector<vector<float> > *jet_GhostTrack_eta;
   vector<vector<float> > *jet_GhostTrack_phi;
   vector<vector<float> > *jet_GhostTrack_e;
   vector<vector<float> > *jet_GhostTrack_d0;
   vector<vector<float> > *jet_GhostTrack_z0;
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
   TBranch        *b_passL1;   //!
   TBranch        *b_passHLT;   //!
   TBranch        *b_passedTriggers;   //!
   TBranch        *b_disabledTriggers;   //!
   TBranch        *b_njet;   //!
   TBranch        *b_jet_E;   //!
   TBranch        *b_jet_pt;   //!
   TBranch        *b_jet_phi;   //!
   TBranch        *b_jet_eta;   //!
   TBranch        *b_jet_HECFrac;   //!
   TBranch        *b_jet_CentroidR;   //!
   TBranch        *b_jet_LowEtConstituentsFrac;   //!
   TBranch        *b_jet_EMFrac;   //!
   TBranch        *b_jet_FracSamplingMax;   //!
   TBranch        *b_jet_FracSamplingMaxIndex;   //!
   TBranch        *b_jet_GhostMuonSegmentCount;   //!
   TBranch        *b_jet_Width;   //!
   TBranch        *b_jet_GhostTrackCount;   //!
   TBranch        *b_jet_GhostTrackPt;   //!
   TBranch        *b_jet_GhostTrack_pt;   //!
   TBranch        *b_jet_GhostTrack_qOverP;   //!
   TBranch        *b_jet_GhostTrack_eta;   //!
   TBranch        *b_jet_GhostTrack_phi;   //!
   TBranch        *b_jet_GhostTrack_e;   //!
   TBranch        *b_jet_GhostTrack_d0;   //!
   TBranch        *b_jet_GhostTrack_z0;   //!
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
   //virtual vector<pair<int,float>> FindSVJ( vector<float> *jet_phi);
   virtual float    		GetPtBalance(TLorentzVector v1, TLorentzVector v2);
   virtual float    		GetDPhi(TLorentzVector v1, TLorentzVector v2);
   virtual float    		GetDPhiMET(TLorentzVector v1, TLorentzVector v2, TLorentzVector met_v);
   virtual float    		GetMjj(TLorentzVector v1, TLorentzVector v2);
   virtual float    		GetMt(TLorentzVector v1, TLorentzVector v2, TLorentzVector met_v);
   virtual float    		GetMtNeg(TLorentzVector v1, TLorentzVector v2);
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
   virtual void    	DeclareHistograms(TH1F* m, TH1F* c, TH1F* cw);
   virtual void     	WriteHistograms();

   // WeightHelper
   virtual void     	SetWeight();
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
   passedTriggers = 0;
   disabledTriggers = 0;
   jet_E = 0;
   jet_pt = 0;
   jet_phi = 0;
   jet_eta = 0;
   jet_HECFrac = 0;
   jet_CentroidR = 0;
   jet_LowEtConstituentsFrac = 0;
   jet_EMFrac = 0;
   jet_FracSamplingMax = 0;
   jet_FracSamplingMaxIndex = 0;
   jet_GhostMuonSegmentCount = 0;
   jet_Width = 0;
   jet_GhostTrackCount = 0;
   jet_GhostTrackPt = 0;
   jet_GhostTrack_pt = 0;
   jet_GhostTrack_qOverP = 0;
   jet_GhostTrack_eta = 0;
   jet_GhostTrack_phi = 0;
   jet_GhostTrack_e = 0;
   jet_GhostTrack_d0 = 0;
   jet_GhostTrack_z0 = 0;
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
   fChain->SetBranchAddress("passL1", &passL1, &b_passL1);
   fChain->SetBranchAddress("passHLT", &passHLT, &b_passHLT);
   fChain->SetBranchAddress("passedTriggers", &passedTriggers, &b_passedTriggers);
   fChain->SetBranchAddress("disabledTriggers", &disabledTriggers, &b_disabledTriggers);
   fChain->SetBranchAddress("njet", &njet, &b_njet);
   fChain->SetBranchAddress("jet_E", &jet_E, &b_jet_E);
   fChain->SetBranchAddress("jet_pt", &jet_pt, &b_jet_pt);
   fChain->SetBranchAddress("jet_phi", &jet_phi, &b_jet_phi);
   fChain->SetBranchAddress("jet_eta", &jet_eta, &b_jet_eta);
   fChain->SetBranchAddress("jet_HECFrac", &jet_HECFrac, &b_jet_HECFrac);
   fChain->SetBranchAddress("jet_CentroidR", &jet_CentroidR, &b_jet_CentroidR);
   fChain->SetBranchAddress("jet_LowEtConstituentsFrac", &jet_LowEtConstituentsFrac, &b_jet_LowEtConstituentsFrac);
   fChain->SetBranchAddress("jet_EMFrac", &jet_EMFrac, &b_jet_EMFrac);
   fChain->SetBranchAddress("jet_FracSamplingMax", &jet_FracSamplingMax, &b_jet_FracSamplingMax);
   fChain->SetBranchAddress("jet_FracSamplingMaxIndex", &jet_FracSamplingMaxIndex, &b_jet_FracSamplingMaxIndex);
   fChain->SetBranchAddress("jet_GhostMuonSegmentCount", &jet_GhostMuonSegmentCount, &b_jet_GhostMuonSegmentCount);
   fChain->SetBranchAddress("jet_Width", &jet_Width, &b_jet_Width);
   fChain->SetBranchAddress("jet_GhostTrackCount", &jet_GhostTrackCount, &b_jet_GhostTrackCount);
   fChain->SetBranchAddress("jet_GhostTrackPt", &jet_GhostTrackPt, &b_jet_GhostTrackPt);
   fChain->SetBranchAddress("jet_GhostTrack_pt", &jet_GhostTrack_pt, &b_jet_GhostTrack_pt);
   fChain->SetBranchAddress("jet_GhostTrack_qOverP", &jet_GhostTrack_qOverP, &b_jet_GhostTrack_qOverP);
   fChain->SetBranchAddress("jet_GhostTrack_eta", &jet_GhostTrack_eta, &b_jet_GhostTrack_eta);
   fChain->SetBranchAddress("jet_GhostTrack_phi", &jet_GhostTrack_phi, &b_jet_GhostTrack_phi);
   fChain->SetBranchAddress("jet_GhostTrack_e", &jet_GhostTrack_e, &b_jet_GhostTrack_e);
   fChain->SetBranchAddress("jet_GhostTrack_d0", &jet_GhostTrack_d0, &b_jet_GhostTrack_d0);
   fChain->SetBranchAddress("jet_GhostTrack_z0", &jet_GhostTrack_z0, &b_jet_GhostTrack_z0);
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
