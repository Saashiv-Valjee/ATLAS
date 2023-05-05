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
   TH1F *cutflow;
   TH1F *cutflow_weighted;
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
   vector<float>   *jet_NumTrkPt1000PV;
   vector<float>   *jet_SumPtTrkPt1000PV;
   vector<float>   *jet_TrackWidthPt1000PV;
   vector<float>   *jet_NumTrkPt500PV;
   vector<float>   *jet_SumPtTrkPt500PV;
   vector<float>   *jet_TrackWidthPt500PV;
   vector<float>   *jet_JVFPV;
   vector<float>   *jet_JvtJvfcorr;
   vector<float>   *jet_JvtRpt;
   vector<float>   *jet_Jvt;
   vector<int>     *jet_JvtPass_Loose;
   vector<vector<float> > *jet_JvtEff_SF_Loose;
   vector<int>     *jet_JvtPass_Medium;
   vector<vector<float> > *jet_JvtEff_SF_Medium;
   vector<int>     *jet_JvtPass_Tight;
   vector<vector<float> > *jet_JvtEff_SF_Tight;
   vector<int>     *jet_fJvtPass_Loose;
   vector<vector<float> > *jet_fJvtEff_SF_Loose;
   vector<int>     *jet_fJvtPass_Medium;
   vector<vector<float> > *jet_fJvtEff_SF_Medium;
   vector<int>     *jet_fJvtPass_Tight;
   vector<vector<float> > *jet_fJvtEff_SF_Tight;
   vector<float>   *jet_DL1r;
   vector<float>   *jet_DL1r_pu;
   vector<float>   *jet_DL1r_pc;
   vector<float>   *jet_DL1r_pb;
   vector<float>   *jet_DL1dv00;
   vector<float>   *jet_DL1dv00_pu;
   vector<float>   *jet_DL1dv00_pc;
   vector<float>   *jet_DL1dv00_pb;
   vector<float>   *jet_DL1dv01;
   vector<float>   *jet_DL1dv01_pu;
   vector<float>   *jet_DL1dv01_pc;
   vector<float>   *jet_DL1dv01_pb;
   vector<float>   *jet_GN1;
   vector<float>   *jet_GN1_pu;
   vector<float>   *jet_GN1_pc;
   vector<float>   *jet_GN1_pb;
   vector<int>     *jet_HadronConeExclTruthLabelID;
   vector<int>     *jet_HadronConeExclExtendedTruthLabelID;
   vector<int>     *jet_ConeTruthLabelID;
   vector<int>     *jet_TruthCount;
   vector<float>   *jet_TruthLabelDeltaR_B;
   vector<float>   *jet_TruthLabelDeltaR_C;
   vector<float>   *jet_TruthLabelDeltaR_T;
   vector<int>     *jet_PartonTruthLabelID;
   vector<float>   *jet_GhostTruthAssociationFraction;
   vector<float>   *jet_truth_E;
   vector<float>   *jet_truth_pt;
   vector<float>   *jet_truth_phi;
   vector<float>   *jet_truth_eta;
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
   TBranch        *b_jet_NumTrkPt1000PV;   //!
   TBranch        *b_jet_SumPtTrkPt1000PV;   //!
   TBranch        *b_jet_TrackWidthPt1000PV;   //!
   TBranch        *b_jet_NumTrkPt500PV;   //!
   TBranch        *b_jet_SumPtTrkPt500PV;   //!
   TBranch        *b_jet_TrackWidthPt500PV;   //!
   TBranch        *b_jet_JVFPV;   //!
   TBranch        *b_jet_JvtJvfcorr;   //!
   TBranch        *b_jet_JvtRpt;   //!
   TBranch        *b_jet_Jvt;   //!
   TBranch        *b_jet_JvtPass_Loose;   //!
   TBranch        *b_jet_JvtEff_SF_Loose;   //!
   TBranch        *b_jet_JvtPass_Medium;   //!
   TBranch        *b_jet_JvtEff_SF_Medium;   //!
   TBranch        *b_jet_JvtPass_Tight;   //!
   TBranch        *b_jet_JvtEff_SF_Tight;   //!
   TBranch        *b_jet_fJvtPass_Loose;   //!
   TBranch        *b_jet_fJvtEff_SF_Loose;   //!
   TBranch        *b_jet_fJvtPass_Medium;   //!
   TBranch        *b_jet_fJvtEff_SF_Medium;   //!
   TBranch        *b_jet_fJvtPass_Tight;   //!
   TBranch        *b_jet_fJvtEff_SF_Tight;   //!
   TBranch        *b_jet_DL1r;   //!
   TBranch        *b_jet_DL1r_pu;   //!
   TBranch        *b_jet_DL1r_pc;   //!
   TBranch        *b_jet_DL1r_pb;   //!
   TBranch        *b_jet_DL1dv00;   //!
   TBranch        *b_jet_DL1dv00_pu;   //!
   TBranch        *b_jet_DL1dv00_pc;   //!
   TBranch        *b_jet_DL1dv00_pb;   //!
   TBranch        *b_jet_DL1dv01;   //!
   TBranch        *b_jet_DL1dv01_pu;   //!
   TBranch        *b_jet_DL1dv01_pc;   //!
   TBranch        *b_jet_DL1dv01_pb;   //!
   TBranch        *b_jet_GN1;   //!
   TBranch        *b_jet_GN1_pu;   //!
   TBranch        *b_jet_GN1_pc;   //!
   TBranch        *b_jet_GN1_pb;   //!
   TBranch        *b_jet_HadronConeExclTruthLabelID;   //!
   TBranch        *b_jet_HadronConeExclExtendedTruthLabelID;   //!
   TBranch        *b_jet_ConeTruthLabelID;   //!
   TBranch        *b_jet_TruthCount;   //!
   TBranch        *b_jet_TruthLabelDeltaR_B;   //!
   TBranch        *b_jet_TruthLabelDeltaR_C;   //!
   TBranch        *b_jet_TruthLabelDeltaR_T;   //!
   TBranch        *b_jet_PartonTruthLabelID;   //!
   TBranch        *b_jet_GhostTruthAssociationFraction;   //!
   TBranch        *b_jet_truth_E;   //!
   TBranch        *b_jet_truth_pt;   //!
   TBranch        *b_jet_truth_phi;   //!
   TBranch        *b_jet_truth_eta;   //!
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
   jet_NumTrkPt1000PV = 0;
   jet_SumPtTrkPt1000PV = 0;
   jet_TrackWidthPt1000PV = 0;
   jet_NumTrkPt500PV = 0;
   jet_SumPtTrkPt500PV = 0;
   jet_TrackWidthPt500PV = 0;
   jet_JVFPV = 0;
   jet_JvtJvfcorr = 0;
   jet_JvtRpt = 0;
   jet_Jvt = 0;
   jet_JvtPass_Loose = 0;
   jet_JvtEff_SF_Loose = 0;
   jet_JvtPass_Medium = 0;
   jet_JvtEff_SF_Medium = 0;
   jet_JvtPass_Tight = 0;
   jet_JvtEff_SF_Tight = 0;
   jet_fJvtPass_Loose = 0;
   jet_fJvtEff_SF_Loose = 0;
   jet_fJvtPass_Medium = 0;
   jet_fJvtEff_SF_Medium = 0;
   jet_fJvtPass_Tight = 0;
   jet_fJvtEff_SF_Tight = 0;
   jet_DL1r = 0;
   jet_DL1r_pu = 0;
   jet_DL1r_pc = 0;
   jet_DL1r_pb = 0;
   jet_DL1dv00 = 0;
   jet_DL1dv00_pu = 0;
   jet_DL1dv00_pc = 0;
   jet_DL1dv00_pb = 0;
   jet_DL1dv01 = 0;
   jet_DL1dv01_pu = 0;
   jet_DL1dv01_pc = 0;
   jet_DL1dv01_pb = 0;
   jet_GN1 = 0;
   jet_GN1_pu = 0;
   jet_GN1_pc = 0;
   jet_GN1_pb = 0;
   jet_HadronConeExclTruthLabelID = 0;
   jet_HadronConeExclExtendedTruthLabelID = 0;
   jet_ConeTruthLabelID = 0;
   jet_TruthCount = 0;
   jet_TruthLabelDeltaR_B = 0;
   jet_TruthLabelDeltaR_C = 0;
   jet_TruthLabelDeltaR_T = 0;
   jet_PartonTruthLabelID = 0;
   jet_GhostTruthAssociationFraction = 0;
   jet_truth_E = 0;
   jet_truth_pt = 0;
   jet_truth_phi = 0;
   jet_truth_eta = 0;
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
   fChain->SetBranchAddress("jet_NumTrkPt1000PV", &jet_NumTrkPt1000PV, &b_jet_NumTrkPt1000PV);
   fChain->SetBranchAddress("jet_SumPtTrkPt1000PV", &jet_SumPtTrkPt1000PV, &b_jet_SumPtTrkPt1000PV);
   fChain->SetBranchAddress("jet_TrackWidthPt1000PV", &jet_TrackWidthPt1000PV, &b_jet_TrackWidthPt1000PV);
   fChain->SetBranchAddress("jet_NumTrkPt500PV", &jet_NumTrkPt500PV, &b_jet_NumTrkPt500PV);
   fChain->SetBranchAddress("jet_SumPtTrkPt500PV", &jet_SumPtTrkPt500PV, &b_jet_SumPtTrkPt500PV);
   fChain->SetBranchAddress("jet_TrackWidthPt500PV", &jet_TrackWidthPt500PV, &b_jet_TrackWidthPt500PV);
   fChain->SetBranchAddress("jet_JVFPV", &jet_JVFPV, &b_jet_JVFPV);
   fChain->SetBranchAddress("jet_JvtJvfcorr", &jet_JvtJvfcorr, &b_jet_JvtJvfcorr);
   fChain->SetBranchAddress("jet_JvtRpt", &jet_JvtRpt, &b_jet_JvtRpt);
   fChain->SetBranchAddress("jet_Jvt", &jet_Jvt, &b_jet_Jvt);
   fChain->SetBranchAddress("jet_JvtPass_Loose", &jet_JvtPass_Loose, &b_jet_JvtPass_Loose);
   fChain->SetBranchAddress("jet_JvtEff_SF_Loose", &jet_JvtEff_SF_Loose, &b_jet_JvtEff_SF_Loose);
   fChain->SetBranchAddress("jet_JvtPass_Medium", &jet_JvtPass_Medium, &b_jet_JvtPass_Medium);
   fChain->SetBranchAddress("jet_JvtEff_SF_Medium", &jet_JvtEff_SF_Medium, &b_jet_JvtEff_SF_Medium);
   fChain->SetBranchAddress("jet_JvtPass_Tight", &jet_JvtPass_Tight, &b_jet_JvtPass_Tight);
   fChain->SetBranchAddress("jet_JvtEff_SF_Tight", &jet_JvtEff_SF_Tight, &b_jet_JvtEff_SF_Tight);
   fChain->SetBranchAddress("jet_fJvtPass_Loose", &jet_fJvtPass_Loose, &b_jet_fJvtPass_Loose);
   fChain->SetBranchAddress("jet_fJvtEff_SF_Loose", &jet_fJvtEff_SF_Loose, &b_jet_fJvtEff_SF_Loose);
   fChain->SetBranchAddress("jet_fJvtPass_Medium", &jet_fJvtPass_Medium, &b_jet_fJvtPass_Medium);
   fChain->SetBranchAddress("jet_fJvtEff_SF_Medium", &jet_fJvtEff_SF_Medium, &b_jet_fJvtEff_SF_Medium);
   fChain->SetBranchAddress("jet_fJvtPass_Tight", &jet_fJvtPass_Tight, &b_jet_fJvtPass_Tight);
   fChain->SetBranchAddress("jet_fJvtEff_SF_Tight", &jet_fJvtEff_SF_Tight, &b_jet_fJvtEff_SF_Tight);
   fChain->SetBranchAddress("jet_DL1r", &jet_DL1r, &b_jet_DL1r);
   fChain->SetBranchAddress("jet_DL1r_pu", &jet_DL1r_pu, &b_jet_DL1r_pu);
   fChain->SetBranchAddress("jet_DL1r_pc", &jet_DL1r_pc, &b_jet_DL1r_pc);
   fChain->SetBranchAddress("jet_DL1r_pb", &jet_DL1r_pb, &b_jet_DL1r_pb);
   fChain->SetBranchAddress("jet_DL1dv00", &jet_DL1dv00, &b_jet_DL1dv00);
   fChain->SetBranchAddress("jet_DL1dv00_pu", &jet_DL1dv00_pu, &b_jet_DL1dv00_pu);
   fChain->SetBranchAddress("jet_DL1dv00_pc", &jet_DL1dv00_pc, &b_jet_DL1dv00_pc);
   fChain->SetBranchAddress("jet_DL1dv00_pb", &jet_DL1dv00_pb, &b_jet_DL1dv00_pb);
   fChain->SetBranchAddress("jet_DL1dv01", &jet_DL1dv01, &b_jet_DL1dv01);
   fChain->SetBranchAddress("jet_DL1dv01_pu", &jet_DL1dv01_pu, &b_jet_DL1dv01_pu);
   fChain->SetBranchAddress("jet_DL1dv01_pc", &jet_DL1dv01_pc, &b_jet_DL1dv01_pc);
   fChain->SetBranchAddress("jet_DL1dv01_pb", &jet_DL1dv01_pb, &b_jet_DL1dv01_pb);
   fChain->SetBranchAddress("jet_GN1", &jet_GN1, &b_jet_GN1);
   fChain->SetBranchAddress("jet_GN1_pu", &jet_GN1_pu, &b_jet_GN1_pu);
   fChain->SetBranchAddress("jet_GN1_pc", &jet_GN1_pc, &b_jet_GN1_pc);
   fChain->SetBranchAddress("jet_GN1_pb", &jet_GN1_pb, &b_jet_GN1_pb);
   fChain->SetBranchAddress("jet_HadronConeExclTruthLabelID", &jet_HadronConeExclTruthLabelID, &b_jet_HadronConeExclTruthLabelID);
   fChain->SetBranchAddress("jet_HadronConeExclExtendedTruthLabelID", &jet_HadronConeExclExtendedTruthLabelID, &b_jet_HadronConeExclExtendedTruthLabelID);
   fChain->SetBranchAddress("jet_ConeTruthLabelID", &jet_ConeTruthLabelID, &b_jet_ConeTruthLabelID);
   fChain->SetBranchAddress("jet_TruthCount", &jet_TruthCount, &b_jet_TruthCount);
   fChain->SetBranchAddress("jet_TruthLabelDeltaR_B", &jet_TruthLabelDeltaR_B, &b_jet_TruthLabelDeltaR_B);
   fChain->SetBranchAddress("jet_TruthLabelDeltaR_C", &jet_TruthLabelDeltaR_C, &b_jet_TruthLabelDeltaR_C);
   fChain->SetBranchAddress("jet_TruthLabelDeltaR_T", &jet_TruthLabelDeltaR_T, &b_jet_TruthLabelDeltaR_T);
   fChain->SetBranchAddress("jet_PartonTruthLabelID", &jet_PartonTruthLabelID, &b_jet_PartonTruthLabelID);
   fChain->SetBranchAddress("jet_GhostTruthAssociationFraction", &jet_GhostTruthAssociationFraction, &b_jet_GhostTruthAssociationFraction);
   fChain->SetBranchAddress("jet_truth_E", &jet_truth_E, &b_jet_truth_E);
   fChain->SetBranchAddress("jet_truth_pt", &jet_truth_pt, &b_jet_truth_pt);
   fChain->SetBranchAddress("jet_truth_phi", &jet_truth_phi, &b_jet_truth_phi);
   fChain->SetBranchAddress("jet_truth_eta", &jet_truth_eta, &b_jet_truth_eta);
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
