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
   map<string,double> tree_output_string;

   // svj & asvj variables
   int n_svj, n_asvj;
   int n_r04_jets, n_r10_jets;
   float dphi_min, dphi_max, maxphi_minphi;
   float pt_balance_12, pt_balance_sa;
   float mjj_12, mjj_sa, mT_jj;
   float jet1_mT, jet2_mT, jet_svj_mT, jet_asvj_mT;
   float deltaY_12, deltaY_sa;

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
   vector<float>   *mcEventWeights;
   UInt_t          timeStamp;
   UInt_t          timeStampNSOffset;
   Bool_t          TileError;
   Bool_t          SCTError;
   Bool_t          LArError;
   UInt_t          TileFlags;
   UInt_t          SCTFlags;
   UInt_t          LArFlags;
   Bool_t          eventClean_LooseBad;
   Int_t           NPV;
   Float_t         actualInteractionsPerCrossing;
   Float_t         averageInteractionsPerCrossing;
   Float_t         weight_pileup;
   Float_t         correctedAverageMu;
   Float_t         correctedAndScaledAverageMu;
   Float_t         correctedActualMu;
   Float_t         correctedAndScaledActualMu;
   Float_t         weight_pileup_up;
   Float_t         weight_pileup_down;
   Int_t           rand_run_nr;
   Int_t           rand_lumiblock_nr;
   Int_t           passL1;
   Int_t           passHLT;
   vector<string>  *passedTriggers;
   vector<string>  *disabledTriggers;
   Int_t           na4_pflowjets;
   vector<float>   *a4_pflowjets_E;
   vector<float>   *a4_pflowjets_pt;
   vector<float>   *a4_pflowjets_phi;
   vector<float>   *a4_pflowjets_eta;
   vector<int>     *a4_pflowjets_clean_passLooseBad;
   vector<int>     *a4_pflowjets_clean_passTightBad;
   vector<int>     *a4_pflowjets_numConstituents;
   vector<int>     *a4_pflowjets_ConeTruthLabelID;
   vector<int>     *a4_pflowjets_TruthCount;
   vector<float>   *a4_pflowjets_TruthLabelDeltaR_B;
   vector<float>   *a4_pflowjets_TruthLabelDeltaR_C;
   vector<float>   *a4_pflowjets_TruthLabelDeltaR_T;
   vector<int>     *a4_pflowjets_PartonTruthLabelID;
   vector<float>   *a4_pflowjets_GhostTruthAssociationFraction;
   vector<float>   *a4_pflowjets_truth_E;
   vector<float>   *a4_pflowjets_truth_pt;
   vector<float>   *a4_pflowjets_truth_phi;
   vector<float>   *a4_pflowjets_truth_eta;
   Int_t           na4_truth;
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
   vector<int>     *a10_lctopojets_numConstituents;
   Int_t           na10_truth;
   vector<float>   *a10_truth_m;
   vector<float>   *a10_truth_pt;
   vector<float>   *a10_truth_phi;
   vector<float>   *a10_truth_eta;
   vector<float>   *a10_truth_Split12;
   vector<float>   *a10_truth_Split23;
   vector<float>   *a10_truth_Split34;
   vector<float>   *a10_truth_tau1_wta;
   vector<float>   *a10_truth_tau2_wta;
   vector<float>   *a10_truth_tau3_wta;
   vector<float>   *a10_truth_tau21_wta;
   vector<float>   *a10_truth_tau32_wta;
   vector<float>   *a10_truth_ECF1;
   vector<float>   *a10_truth_ECF2;
   vector<float>   *a10_truth_ECF3;
   vector<float>   *a10_truth_C2;
   vector<float>   *a10_truth_D2;
   vector<float>   *a10_truth_NTrimSubjets;
   vector<int>     *a10_truth_Nclusters;
   vector<int>     *a10_truth_nTracks;
   vector<int>     *a10_truth_ungrtrk500;
   vector<float>   *a10_truth_EMFrac;
   vector<int>     *a10_truth_nChargedParticles;
   vector<int>     *a10_truth_numConstituents;
   Float_t         MET_TruthMET_Truth;
   Float_t         MET_TruthMET_TruthPx;
   Float_t         MET_TruthMET_TruthPy;
   Float_t         MET_TruthMET_TruthSumEt;
   Float_t         MET_TruthMET_TruthPhi;
   Float_t         metFinalTrk;
   Float_t         metFinalTrkPx;
   Float_t         metFinalTrkPy;
   Float_t         metFinalTrkSumEt;
   Float_t         metFinalTrkPhi;
   Int_t           ntruthBSM;
   vector<int>     *truthBSM_pdgId;
   vector<int>     *truthBSM_status;
   vector<int>     *truthBSM_barcode;
   vector<float>   *truthBSM_m;
   vector<float>   *truthBSM_px;
   vector<float>   *truthBSM_py;
   vector<float>   *truthBSM_pz;
   vector<float>   *truthBSM_e;
   vector<float>   *truthBSM_pt;
   vector<float>   *truthBSM_eta;
   vector<float>   *truthBSM_phi;
   vector<int>     *truthBSM_is_higgs;
   vector<int>     *truthBSM_is_bhad;
   vector<int>     *truthBSM_nParents;
   vector<vector<int> > *truthBSM_parent_pdgId;
   vector<vector<int> > *truthBSM_parent_barcode;
   vector<vector<int> > *truthBSM_parent_status;
   vector<int>     *truthBSM_nChildren;
   vector<vector<int> > *truthBSM_child_pdgId;
   vector<vector<int> > *truthBSM_child_barcode;
   vector<vector<int> > *truthBSM_child_status;
   vector<float>   *truthBSM_pt_dressed;
   vector<float>   *truthBSM_eta_dressed;
   vector<float>   *truthBSM_phi_dressed;
   vector<float>   *truthBSM_e_dressed;
   vector<unsigned int> *truthBSM_origin;

   // List of branches
   TBranch        *b_runNumber;   //!
   TBranch        *b_eventNumber;   //!
   TBranch        *b_lumiBlock;   //!
   TBranch        *b_coreFlags;   //!
   TBranch        *b_bcid;   //!
   TBranch        *b_mcEventNumber;   //!
   TBranch        *b_mcChannelNumber;   //!
   TBranch        *b_mcEventWeight;   //!
   TBranch        *b_mcEventWeights;   //!
   TBranch        *b_timeStamp;   //!
   TBranch        *b_timeStampNSOffset;   //!
   TBranch        *b_TileError;   //!
   TBranch        *b_SCTError;   //!
   TBranch        *b_LArError;   //!
   TBranch        *b_TileFlags;   //!
   TBranch        *b_SCTFlags;   //!
   TBranch        *b_LArFlags;   //!
   TBranch        *b_eventClean_LooseBad;   //!
   TBranch        *b_NPV;   //!
   TBranch        *b_actualInteractionsPerCrossing;   //!
   TBranch        *b_averageInteractionsPerCrossing;   //!
   TBranch        *b_weight_pileup;   //!
   TBranch        *b_correctedAverageMu;   //!
   TBranch        *b_correctedAndScaledAverageMu;   //!
   TBranch        *b_correctedActualMu;   //!
   TBranch        *b_correctedAndScaledActualMu;   //!
   TBranch        *b_weight_pileup_up;   //!
   TBranch        *b_weight_pileup_down;   //!
   TBranch        *b_rand_run_nr;   //!
   TBranch        *b_rand_lumiblock_nr;   //!
   TBranch        *b_passL1;   //!
   TBranch        *b_passHLT;   //!
   TBranch        *b_passedTriggers;   //!
   TBranch        *b_disabledTriggers;   //!
   TBranch        *b_na4_pflowjets;   //!
   TBranch        *b_a4_pflowjets_E;   //!
   TBranch        *b_a4_pflowjets_pt;   //!
   TBranch        *b_a4_pflowjets_phi;   //!
   TBranch        *b_a4_pflowjets_eta;   //!
   TBranch        *b_a4_pflowjets_clean_passLooseBad;   //!
   TBranch        *b_a4_pflowjets_clean_passTightBad;   //!
   TBranch        *b_a4_pflowjets_numConstituents;   //!
   TBranch        *b_a4_pflowjets_ConeTruthLabelID;   //!
   TBranch        *b_a4_pflowjets_TruthCount;   //!
   TBranch        *b_a4_pflowjets_TruthLabelDeltaR_B;   //!
   TBranch        *b_a4_pflowjets_TruthLabelDeltaR_C;   //!
   TBranch        *b_a4_pflowjets_TruthLabelDeltaR_T;   //!
   TBranch        *b_a4_pflowjets_PartonTruthLabelID;   //!
   TBranch        *b_a4_pflowjets_GhostTruthAssociationFraction;   //!
   TBranch        *b_a4_pflowjets_truth_E;   //!
   TBranch        *b_a4_pflowjets_truth_pt;   //!
   TBranch        *b_a4_pflowjets_truth_phi;   //!
   TBranch        *b_a4_pflowjets_truth_eta;   //!
   TBranch        *b_na4_truth;   //!
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
   TBranch        *b_a10_lctopojets_numConstituents;   //!
   TBranch        *b_na10_truth;   //!
   TBranch        *b_a10_truth_m;   //!
   TBranch        *b_a10_truth_pt;   //!
   TBranch        *b_a10_truth_phi;   //!
   TBranch        *b_a10_truth_eta;   //!
   TBranch        *b_a10_truth_Split12;   //!
   TBranch        *b_a10_truth_Split23;   //!
   TBranch        *b_a10_truth_Split34;   //!
   TBranch        *b_a10_truth_tau1_wta;   //!
   TBranch        *b_a10_truth_tau2_wta;   //!
   TBranch        *b_a10_truth_tau3_wta;   //!
   TBranch        *b_a10_truth_tau21_wta;   //!
   TBranch        *b_a10_truth_tau32_wta;   //!
   TBranch        *b_a10_truth_ECF1;   //!
   TBranch        *b_a10_truth_ECF2;   //!
   TBranch        *b_a10_truth_ECF3;   //!
   TBranch        *b_a10_truth_C2;   //!
   TBranch        *b_a10_truth_D2;   //!
   TBranch        *b_a10_truth_NTrimSubjets;   //!
   TBranch        *b_a10_truth_Nclusters;   //!
   TBranch        *b_a10_truth_nTracks;   //!
   TBranch        *b_a10_truth_ungrtrk500;   //!
   TBranch        *b_a10_truth_EMFrac;   //!
   TBranch        *b_a10_truth_nChargedParticles;   //!
   TBranch        *b_a10_truth_numConstituents;   //!
   TBranch        *b_MET_TruthMET_Truth;   //!
   TBranch        *b_MET_TruthMET_TruthPx;   //!
   TBranch        *b_MET_TruthMET_TruthPy;   //!
   TBranch        *b_MET_TruthMET_TruthSumEt;   //!
   TBranch        *b_MET_TruthMET_TruthPhi;   //!
   TBranch        *b_metFinalTrk;   //!
   TBranch        *b_metFinalTrkPx;   //!
   TBranch        *b_metFinalTrkPy;   //!
   TBranch        *b_metFinalTrkSumEt;   //!
   TBranch        *b_metFinalTrkPhi;   //!
   TBranch        *b_ntruthBSM;   //!
   TBranch        *b_truthBSM_pdgId;   //!
   TBranch        *b_truthBSM_status;   //!
   TBranch        *b_truthBSM_barcode;   //!
   TBranch        *b_truthBSM_m;   //!
   TBranch        *b_truthBSM_px;   //!
   TBranch        *b_truthBSM_py;   //!
   TBranch        *b_truthBSM_pz;   //!
   TBranch        *b_truthBSM_e;   //!
   TBranch        *b_truthBSM_pt;   //!
   TBranch        *b_truthBSM_eta;   //!
   TBranch        *b_truthBSM_phi;   //!
   TBranch        *b_truthBSM_is_higgs;   //!
   TBranch        *b_truthBSM_is_bhad;   //!
   TBranch        *b_truthBSM_nParents;   //!
   TBranch        *b_truthBSM_parent_pdgId;   //!
   TBranch        *b_truthBSM_parent_barcode;   //!
   TBranch        *b_truthBSM_parent_status;   //!
   TBranch        *b_truthBSM_nChildren;   //!
   TBranch        *b_truthBSM_child_pdgId;   //!
   TBranch        *b_truthBSM_child_barcode;   //!
   TBranch        *b_truthBSM_child_status;   //!
   TBranch        *b_truthBSM_pt_dressed;   //!
   TBranch        *b_truthBSM_eta_dressed;   //!
   TBranch        *b_truthBSM_phi_dressed;   //!
   TBranch        *b_truthBSM_e_dressed;   //!
   TBranch        *b_truthBSM_origin;   //!

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
   virtual vector<pair<int,float>> FindSVJ();
   virtual float    GetPtBalance(TLorentzVector v1, TLorentzVector v2);
   virtual float    GetDPhi(float phi1, float phi2);
   virtual float    GetMjj(TLorentzVector v1, TLorentzVector v2);
   virtual float    GetMt(TLorentzVector v1, TLorentzVector v2, float met, float met_phi);
   virtual float    GetDeltaY(TLorentzVector v1, TLorentzVector v2);

   // OutputTreeHelper
   virtual void     DeclareOutputTrees();
   virtual void     FillOutputTrees( string treename );
   virtual void     WriteOutputTrees();

   // HistHelper
   virtual void     DeclareHistograms();
   virtual void     WriteHistograms();
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
   mcEventWeights = 0;
   passedTriggers = 0;
   disabledTriggers = 0;
   a4_pflowjets_E = 0;
   a4_pflowjets_pt = 0;
   a4_pflowjets_phi = 0;
   a4_pflowjets_eta = 0;
   a4_pflowjets_clean_passLooseBad = 0;
   a4_pflowjets_clean_passTightBad = 0;
   a4_pflowjets_numConstituents = 0;
   a4_pflowjets_ConeTruthLabelID = 0;
   a4_pflowjets_TruthCount = 0;
   a4_pflowjets_TruthLabelDeltaR_B = 0;
   a4_pflowjets_TruthLabelDeltaR_C = 0;
   a4_pflowjets_TruthLabelDeltaR_T = 0;
   a4_pflowjets_PartonTruthLabelID = 0;
   a4_pflowjets_GhostTruthAssociationFraction = 0;
   a4_pflowjets_truth_E = 0;
   a4_pflowjets_truth_pt = 0;
   a4_pflowjets_truth_phi = 0;
   a4_pflowjets_truth_eta = 0;
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
   a10_lctopojets_numConstituents = 0;
   a10_truth_m = 0;
   a10_truth_pt = 0;
   a10_truth_phi = 0;
   a10_truth_eta = 0;
   a10_truth_Split12 = 0;
   a10_truth_Split23 = 0;
   a10_truth_Split34 = 0;
   a10_truth_tau1_wta = 0;
   a10_truth_tau2_wta = 0;
   a10_truth_tau3_wta = 0;
   a10_truth_tau21_wta = 0;
   a10_truth_tau32_wta = 0;
   a10_truth_ECF1 = 0;
   a10_truth_ECF2 = 0;
   a10_truth_ECF3 = 0;
   a10_truth_C2 = 0;
   a10_truth_D2 = 0;
   a10_truth_NTrimSubjets = 0;
   a10_truth_Nclusters = 0;
   a10_truth_nTracks = 0;
   a10_truth_ungrtrk500 = 0;
   a10_truth_EMFrac = 0;
   a10_truth_nChargedParticles = 0;
   a10_truth_numConstituents = 0;
   truthBSM_pdgId = 0;
   truthBSM_status = 0;
   truthBSM_barcode = 0;
   truthBSM_m = 0;
   truthBSM_px = 0;
   truthBSM_py = 0;
   truthBSM_pz = 0;
   truthBSM_e = 0;
   truthBSM_pt = 0;
   truthBSM_eta = 0;
   truthBSM_phi = 0;
   truthBSM_is_higgs = 0;
   truthBSM_is_bhad = 0;
   truthBSM_nParents = 0;
   truthBSM_parent_pdgId = 0;
   truthBSM_parent_barcode = 0;
   truthBSM_parent_status = 0;
   truthBSM_nChildren = 0;
   truthBSM_child_pdgId = 0;
   truthBSM_child_barcode = 0;
   truthBSM_child_status = 0;
   truthBSM_pt_dressed = 0;
   truthBSM_eta_dressed = 0;
   truthBSM_phi_dressed = 0;
   truthBSM_e_dressed = 0;
   truthBSM_origin = 0;
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
   fChain->SetBranchAddress("mcEventWeights", &mcEventWeights, &b_mcEventWeights);
   fChain->SetBranchAddress("timeStamp", &timeStamp, &b_timeStamp);
   fChain->SetBranchAddress("timeStampNSOffset", &timeStampNSOffset, &b_timeStampNSOffset);
   fChain->SetBranchAddress("TileError", &TileError, &b_TileError);
   fChain->SetBranchAddress("SCTError", &SCTError, &b_SCTError);
   fChain->SetBranchAddress("LArError", &LArError, &b_LArError);
   fChain->SetBranchAddress("TileFlags", &TileFlags, &b_TileFlags);
   fChain->SetBranchAddress("SCTFlags", &SCTFlags, &b_SCTFlags);
   fChain->SetBranchAddress("LArFlags", &LArFlags, &b_LArFlags);
   fChain->SetBranchAddress("eventClean_LooseBad", &eventClean_LooseBad, &b_eventClean_LooseBad);
   fChain->SetBranchAddress("NPV", &NPV, &b_NPV);
   fChain->SetBranchAddress("actualInteractionsPerCrossing", &actualInteractionsPerCrossing, &b_actualInteractionsPerCrossing);
   fChain->SetBranchAddress("averageInteractionsPerCrossing", &averageInteractionsPerCrossing, &b_averageInteractionsPerCrossing);
   fChain->SetBranchAddress("weight_pileup", &weight_pileup, &b_weight_pileup);
   fChain->SetBranchAddress("correctedAverageMu", &correctedAverageMu, &b_correctedAverageMu);
   fChain->SetBranchAddress("correctedAndScaledAverageMu", &correctedAndScaledAverageMu, &b_correctedAndScaledAverageMu);
   fChain->SetBranchAddress("correctedActualMu", &correctedActualMu, &b_correctedActualMu);
   fChain->SetBranchAddress("correctedAndScaledActualMu", &correctedAndScaledActualMu, &b_correctedAndScaledActualMu);
   fChain->SetBranchAddress("weight_pileup_up", &weight_pileup_up, &b_weight_pileup_up);
   fChain->SetBranchAddress("weight_pileup_down", &weight_pileup_down, &b_weight_pileup_down);
   fChain->SetBranchAddress("rand_run_nr", &rand_run_nr, &b_rand_run_nr);
   fChain->SetBranchAddress("rand_lumiblock_nr", &rand_lumiblock_nr, &b_rand_lumiblock_nr);
   fChain->SetBranchAddress("passL1", &passL1, &b_passL1);
   fChain->SetBranchAddress("passHLT", &passHLT, &b_passHLT);
   fChain->SetBranchAddress("passedTriggers", &passedTriggers, &b_passedTriggers);
   fChain->SetBranchAddress("disabledTriggers", &disabledTriggers, &b_disabledTriggers);
   fChain->SetBranchAddress("na4_pflowjets", &na4_pflowjets, &b_na4_pflowjets);
   fChain->SetBranchAddress("a4_pflowjets_E", &a4_pflowjets_E, &b_a4_pflowjets_E);
   fChain->SetBranchAddress("a4_pflowjets_pt", &a4_pflowjets_pt, &b_a4_pflowjets_pt);
   fChain->SetBranchAddress("a4_pflowjets_phi", &a4_pflowjets_phi, &b_a4_pflowjets_phi);
   fChain->SetBranchAddress("a4_pflowjets_eta", &a4_pflowjets_eta, &b_a4_pflowjets_eta);
   fChain->SetBranchAddress("a4_pflowjets_clean_passLooseBad", &a4_pflowjets_clean_passLooseBad, &b_a4_pflowjets_clean_passLooseBad);
   fChain->SetBranchAddress("a4_pflowjets_clean_passTightBad", &a4_pflowjets_clean_passTightBad, &b_a4_pflowjets_clean_passTightBad);
   fChain->SetBranchAddress("a4_pflowjets_numConstituents", &a4_pflowjets_numConstituents, &b_a4_pflowjets_numConstituents);
   fChain->SetBranchAddress("a4_pflowjets_ConeTruthLabelID", &a4_pflowjets_ConeTruthLabelID, &b_a4_pflowjets_ConeTruthLabelID);
   fChain->SetBranchAddress("a4_pflowjets_TruthCount", &a4_pflowjets_TruthCount, &b_a4_pflowjets_TruthCount);
   fChain->SetBranchAddress("a4_pflowjets_TruthLabelDeltaR_B", &a4_pflowjets_TruthLabelDeltaR_B, &b_a4_pflowjets_TruthLabelDeltaR_B);
   fChain->SetBranchAddress("a4_pflowjets_TruthLabelDeltaR_C", &a4_pflowjets_TruthLabelDeltaR_C, &b_a4_pflowjets_TruthLabelDeltaR_C);
   fChain->SetBranchAddress("a4_pflowjets_TruthLabelDeltaR_T", &a4_pflowjets_TruthLabelDeltaR_T, &b_a4_pflowjets_TruthLabelDeltaR_T);
   fChain->SetBranchAddress("a4_pflowjets_PartonTruthLabelID", &a4_pflowjets_PartonTruthLabelID, &b_a4_pflowjets_PartonTruthLabelID);
   fChain->SetBranchAddress("a4_pflowjets_GhostTruthAssociationFraction", &a4_pflowjets_GhostTruthAssociationFraction, &b_a4_pflowjets_GhostTruthAssociationFraction);
   fChain->SetBranchAddress("a4_pflowjets_truth_E", &a4_pflowjets_truth_E, &b_a4_pflowjets_truth_E);
   fChain->SetBranchAddress("a4_pflowjets_truth_pt", &a4_pflowjets_truth_pt, &b_a4_pflowjets_truth_pt);
   fChain->SetBranchAddress("a4_pflowjets_truth_phi", &a4_pflowjets_truth_phi, &b_a4_pflowjets_truth_phi);
   fChain->SetBranchAddress("a4_pflowjets_truth_eta", &a4_pflowjets_truth_eta, &b_a4_pflowjets_truth_eta);
   fChain->SetBranchAddress("na4_truth", &na4_truth, &b_na4_truth);
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
   fChain->SetBranchAddress("a10_lctopojets_numConstituents", &a10_lctopojets_numConstituents, &b_a10_lctopojets_numConstituents);
   fChain->SetBranchAddress("na10_truth", &na10_truth, &b_na10_truth);
   fChain->SetBranchAddress("a10_truth_m", &a10_truth_m, &b_a10_truth_m);
   fChain->SetBranchAddress("a10_truth_pt", &a10_truth_pt, &b_a10_truth_pt);
   fChain->SetBranchAddress("a10_truth_phi", &a10_truth_phi, &b_a10_truth_phi);
   fChain->SetBranchAddress("a10_truth_eta", &a10_truth_eta, &b_a10_truth_eta);
   fChain->SetBranchAddress("a10_truth_Split12", &a10_truth_Split12, &b_a10_truth_Split12);
   fChain->SetBranchAddress("a10_truth_Split23", &a10_truth_Split23, &b_a10_truth_Split23);
   fChain->SetBranchAddress("a10_truth_Split34", &a10_truth_Split34, &b_a10_truth_Split34);
   fChain->SetBranchAddress("a10_truth_tau1_wta", &a10_truth_tau1_wta, &b_a10_truth_tau1_wta);
   fChain->SetBranchAddress("a10_truth_tau2_wta", &a10_truth_tau2_wta, &b_a10_truth_tau2_wta);
   fChain->SetBranchAddress("a10_truth_tau3_wta", &a10_truth_tau3_wta, &b_a10_truth_tau3_wta);
   fChain->SetBranchAddress("a10_truth_tau21_wta", &a10_truth_tau21_wta, &b_a10_truth_tau21_wta);
   fChain->SetBranchAddress("a10_truth_tau32_wta", &a10_truth_tau32_wta, &b_a10_truth_tau32_wta);
   fChain->SetBranchAddress("a10_truth_ECF1", &a10_truth_ECF1, &b_a10_truth_ECF1);
   fChain->SetBranchAddress("a10_truth_ECF2", &a10_truth_ECF2, &b_a10_truth_ECF2);
   fChain->SetBranchAddress("a10_truth_ECF3", &a10_truth_ECF3, &b_a10_truth_ECF3);
   fChain->SetBranchAddress("a10_truth_C2", &a10_truth_C2, &b_a10_truth_C2);
   fChain->SetBranchAddress("a10_truth_D2", &a10_truth_D2, &b_a10_truth_D2);
   fChain->SetBranchAddress("a10_truth_NTrimSubjets", &a10_truth_NTrimSubjets, &b_a10_truth_NTrimSubjets);
   fChain->SetBranchAddress("a10_truth_Nclusters", &a10_truth_Nclusters, &b_a10_truth_Nclusters);
   fChain->SetBranchAddress("a10_truth_nTracks", &a10_truth_nTracks, &b_a10_truth_nTracks);
   fChain->SetBranchAddress("a10_truth_ungrtrk500", &a10_truth_ungrtrk500, &b_a10_truth_ungrtrk500);
   fChain->SetBranchAddress("a10_truth_EMFrac", &a10_truth_EMFrac, &b_a10_truth_EMFrac);
   fChain->SetBranchAddress("a10_truth_nChargedParticles", &a10_truth_nChargedParticles, &b_a10_truth_nChargedParticles);
   fChain->SetBranchAddress("a10_truth_numConstituents", &a10_truth_numConstituents, &b_a10_truth_numConstituents);
   fChain->SetBranchAddress("MET_TruthMET_Truth", &MET_TruthMET_Truth, &b_MET_TruthMET_Truth);
   fChain->SetBranchAddress("MET_TruthMET_TruthPx", &MET_TruthMET_TruthPx, &b_MET_TruthMET_TruthPx);
   fChain->SetBranchAddress("MET_TruthMET_TruthPy", &MET_TruthMET_TruthPy, &b_MET_TruthMET_TruthPy);
   fChain->SetBranchAddress("MET_TruthMET_TruthSumEt", &MET_TruthMET_TruthSumEt, &b_MET_TruthMET_TruthSumEt);
   fChain->SetBranchAddress("MET_TruthMET_TruthPhi", &MET_TruthMET_TruthPhi, &b_MET_TruthMET_TruthPhi);
   fChain->SetBranchAddress("metFinalTrk", &metFinalTrk, &b_metFinalTrk);
   fChain->SetBranchAddress("metFinalTrkPx", &metFinalTrkPx, &b_metFinalTrkPx);
   fChain->SetBranchAddress("metFinalTrkPy", &metFinalTrkPy, &b_metFinalTrkPy);
   fChain->SetBranchAddress("metFinalTrkSumEt", &metFinalTrkSumEt, &b_metFinalTrkSumEt);
   fChain->SetBranchAddress("metFinalTrkPhi", &metFinalTrkPhi, &b_metFinalTrkPhi);
   fChain->SetBranchAddress("ntruthBSM", &ntruthBSM, &b_ntruthBSM);
   fChain->SetBranchAddress("truthBSM_pdgId", &truthBSM_pdgId, &b_truthBSM_pdgId);
   fChain->SetBranchAddress("truthBSM_status", &truthBSM_status, &b_truthBSM_status);
   fChain->SetBranchAddress("truthBSM_barcode", &truthBSM_barcode, &b_truthBSM_barcode);
   fChain->SetBranchAddress("truthBSM_m", &truthBSM_m, &b_truthBSM_m);
   fChain->SetBranchAddress("truthBSM_px", &truthBSM_px, &b_truthBSM_px);
   fChain->SetBranchAddress("truthBSM_py", &truthBSM_py, &b_truthBSM_py);
   fChain->SetBranchAddress("truthBSM_pz", &truthBSM_pz, &b_truthBSM_pz);
   fChain->SetBranchAddress("truthBSM_e", &truthBSM_e, &b_truthBSM_e);
   fChain->SetBranchAddress("truthBSM_pt", &truthBSM_pt, &b_truthBSM_pt);
   fChain->SetBranchAddress("truthBSM_eta", &truthBSM_eta, &b_truthBSM_eta);
   fChain->SetBranchAddress("truthBSM_phi", &truthBSM_phi, &b_truthBSM_phi);
   fChain->SetBranchAddress("truthBSM_is_higgs", &truthBSM_is_higgs, &b_truthBSM_is_higgs);
   fChain->SetBranchAddress("truthBSM_is_bhad", &truthBSM_is_bhad, &b_truthBSM_is_bhad);
   fChain->SetBranchAddress("truthBSM_nParents", &truthBSM_nParents, &b_truthBSM_nParents);
   fChain->SetBranchAddress("truthBSM_parent_pdgId", &truthBSM_parent_pdgId, &b_truthBSM_parent_pdgId);
   fChain->SetBranchAddress("truthBSM_parent_barcode", &truthBSM_parent_barcode, &b_truthBSM_parent_barcode);
   fChain->SetBranchAddress("truthBSM_parent_status", &truthBSM_parent_status, &b_truthBSM_parent_status);
   fChain->SetBranchAddress("truthBSM_nChildren", &truthBSM_nChildren, &b_truthBSM_nChildren);
   fChain->SetBranchAddress("truthBSM_child_pdgId", &truthBSM_child_pdgId, &b_truthBSM_child_pdgId);
   fChain->SetBranchAddress("truthBSM_child_barcode", &truthBSM_child_barcode, &b_truthBSM_child_barcode);
   fChain->SetBranchAddress("truthBSM_child_status", &truthBSM_child_status, &b_truthBSM_child_status);
   fChain->SetBranchAddress("truthBSM_pt_dressed", &truthBSM_pt_dressed, &b_truthBSM_pt_dressed);
   fChain->SetBranchAddress("truthBSM_eta_dressed", &truthBSM_eta_dressed, &b_truthBSM_eta_dressed);
   fChain->SetBranchAddress("truthBSM_phi_dressed", &truthBSM_phi_dressed, &b_truthBSM_phi_dressed);
   fChain->SetBranchAddress("truthBSM_e_dressed", &truthBSM_e_dressed, &b_truthBSM_e_dressed);
   fChain->SetBranchAddress("truthBSM_origin", &truthBSM_origin, &b_truthBSM_origin);
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
