#include <cmath>
#include <algorithm>

#include "project_Hv2.h"


#include <sstream>
#include <string>
#include <iostream>

template <typename Type> std::string to_str(const Type & t)
{
  std::ostringstream os;
  os << t;
  return os.str ();
}


TString datadirmain = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/";
TString datadirsub = "v1.0/";
TString filename1 = "user.ebusch.5085";
TString filename2 = ".MGPy8EG_SVJSChan_";
TString filevarM[2] = {"1500", "750"};
TString filevarr[2] = {"8", "3"};
TString filename3 = "_tree.root";
TString mcs[3] = {".mc16a", ".mc16d", ".mc16e"};
TString fileN[4] = {"47", "48", "49", "50"};
TString ndN[12] = {"3733", "3907", "3996", "3741", "3916", "4007", "3753", "3924", "4015", "3764", "3929", "4025"};

int COLOR[4] = {810,860,800,870};

TString multijetdir = "user.ebusch.364702.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ2WithSW.";
TString multijetndN[3] = {"198","165","147"};
TString multiNO[3] = {"22","04","10"};
TString fileN1[3] = {"98","65","47"};
TString fileN2[3] = {"22","04","10"};


TString tree_entry = "outTree/nominal";

int nsamples = 4;

double matchcut = DRCUT;

bool istruth = false;

int ptc = PTMIN;
int ptlc = PTLMIN;
int ptmax = 200;

float vptmin = 20;

int nintcuts[2] = {20, 40};
int ptcuts[3] = {PTMIN,70,100};

double drbinr = 2;

float catchdr = 0.4;

const int eventpicmax = NOEVENTPIC;
const int eventpicd = EVENTPICDIF;

const int nbsmvars = NBSMVARS;
const int njetvars = NJETVARS;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void project_Pv2(){  


  gInterpreter->GenerateDictionary("vector<vector<int> >", "vector");


  TString VecTypes[5] = {"Z","Q","VDH","IDH","O"};
  TString VecVars[nbsmvars] = {"PT","ETA","PHI","E","ST","ID","USE"};
  TString JetVecVars[njetvars] = {"PT","ETA","PHI","E","MATCH"};

  vector<float> V[nsamples][eventpicmax][nbsmvars]; // [signal type][eventno.][BSM variables]
  vector<float> JETV[nsamples][eventpicmax][njetvars]; // [signal type][eventno.][JET variables]
  vector<float> LJETV[nsamples][eventpicmax][njetvars]; // [signal type][eventno.][JET variables]
  vector<int> EVENTV[nsamples][eventpicmax]; // [signal type][eventno.]
  vector<float> METV[nsamples][eventpicmax]; //[signal type][evento.]
  vector<int> LSQV[nsamples][eventpicmax][2]; //[signal type][eventno.][LEADING/SUBLEADING Q]
  vector<float> LSPTSV[nsamples][eventpicmax][3]; //[signal type][ecentno.][BSM/JET/LARGEJET]

  int nZ0[nsamples];
  int npasses[nsamples];
  int nevents[nsamples];

  TH1D* JPT[nsamples][2];
  TH1D* QPT[nsamples][3]; // [signal][0->Leading|1->Subleading|2->Both]
  TH1D* QDHDR[nsamples][3][2]; // [signal][0->Leading Q|1->Subleading Q|2->Both][0->Visible DH|1->Invisible DH]
  TH1D* QS[nsamples];
  TH1D* VDHNC[nsamples][2];
  TH1D* VDHCI[nsamples][2];
  TH1D* IVDHNC[nsamples][2];
  TH1D* MAXVDHDR[nsamples][2];
  TH1D* NUSEFULDH[nsamples][2];
  TH1D* USEFULID[nsamples][2];
  TH1D* NUSEFUL[nsamples];
  TH1D* NVDH[nsamples];
  TH1D* NIDH[nsamples];
  TH1D* U_VRAT[nsamples];
  TH1D* I_VRAT[nsamples];
  TH1D* I_ARAT[nsamples];
  TH1D* U_ARAT[nsamples];
  TH1D* QPTRAT[nsamples];
  TH1D* DMNC[nsamples];
  TH1D* QMATCHES[nsamples][2];
  TH1D* PTBALPT[nsamples];
  TH1D* PTBALMET[nsamples];
  TH1D* DMRAT[nsamples][2];
  TH2D* NJETDR[nsamples][2];
  TH2D* NJETINT[nsamples][2][3];
  TH2D* NJETPT[nsamples][2][3];
  TH1D* CATCHRAT[nsamples][2];
  TH1D* CATCHRATJ[nsamples][2];
  TH1D* STARTDIST[nsamples][2];
  TH1D* JETPTCATCH[nsamples][2];
  TH1D* NMISS[nsamples];
  TH1D* VDHPT[nsamples][2];
  TH1D* DPHIMATCH[nsamples][2];
  TH1D* DPHIJETS[nsamples][3]; // J1 | J2 | J1 + J2
  TH1D* DPHIMIN[nsamples][2]; // MET aligned jet | J1 or J2
  TH2D* JETPTCORR[nsamples];
  TH2D* MATCHDPHICORR[nsamples];

  TH1D* vdhnmatch[nsamples];

  int nbins = 5040;

  TString jt = "";
  if(istruth){jt = " (Truth Jets)";}

  TString QDHDRLS[3] = {"1","2","i"};
  for(int J = 0; J < nsamples; J++){
    JPT[J][0] = new TH1D((const TString)("JPT0"+std::to_string(J)),"Leading Jet P_{t}",nbins,0,1000); 
    JPT[J][1] = new TH1D((const TString)("JPT1"+std::to_string(J)),"Subleading Jet P_{t}",nbins,0,1000); 
    QPT[J][0] = new TH1D((const TString)("QPT0"+std::to_string(J)),"Leading Dark Quark P_{t}",nbins,0,1000); 
    QPT[J][1] = new TH1D((const TString)("QPT1"+std::to_string(J)),"Subleading Dark Quark P_{t}",nbins,0,1000); 
    QPT[J][2] = new TH1D((const TString)("QPT2"+std::to_string(J)),"Dark Quarks total P_{t}",nbins,0,2000);
    for(int l = 0;  l < 3; l++){
      QDHDR[J][l][0] = new TH1D((const TString)("QHDR"+std::to_string(l)+"0"+std::to_string(J)),(const TString)("DR(\\chi_{"+QDHDRLS[l]+"},DH_{vis}) "),nbins,0,6);
      QDHDR[J][l][1] = new TH1D((const TString)("QHDR"+std::to_string(l)+"1"+std::to_string(J)),(const TString)("DR(\\chi_{ "+QDHDRLS[l]+"},DH_{inv}) "),nbins,0,6);      
    }
    QS[J] = new TH1D((const TString)("QS"+std::to_string(J)),"Q Status", 150,0,150);
    VDHNC[J][0] = new TH1D((const TString)("VDHNC111"+std::to_string(J)),"Unstable Dark Hadron NO. Childern (4900111)",nbins,0,10);
    VDHNC[J][1] = new TH1D((const TString)("VDHNC113"+std::to_string(J)),"Unstable Dark Hadron NO. Childern (4900113)",nbins,0,10);
    VDHCI[J][0] = new TH1D((const TString)("VDHCI111"+std::to_string(J)),"Unstable Dark Hadron CHild pdgId's (4900111)",nbins,0,100);
    VDHCI[J][1] = new TH1D((const TString)("VDHCI113"+std::to_string(J)),"Unstable Dark Hadron CHild pdgId's (4900113)",nbins,0,100);
    IVDHNC[J][0] = new TH1D((const TString)("IVDHNC211"+std::to_string(J)),"Stable Dark Hadron NO. Childern (4900211)",nbins,0,10);
    IVDHNC[J][1] = new TH1D((const TString)("IVDHNC213"+std::to_string(J)),"Stable Dark Hadron NO. Childern (4900213)",nbins,0,10);
    MAXVDHDR[J][0] = new TH1D((const TString)("LMAXVDHDR"+std::to_string(J)),"Max DR(VDH_{i},VDH_{j}) From Leading Dark Quark",nbins,0,1);
    MAXVDHDR[J][1] = new TH1D((const TString)("SLMAXVDHDR"+std::to_string(J)),"Max DR(VDH_{i},VDH_{j}) From Subleading Dark Quark",nbins,0,1);
    NUSEFULDH[J][0] = new TH1D((const TString)("LNUSEFULDH"+to_string(J)),"NO. Visible Dark Hadrons from Leading Dark Quark",nbins,0,10);
    NUSEFULDH[J][1] = new TH1D((const TString)("SLNUSEFULDH"+to_string(J)),"NO. Visible Dark Hadrons from Subleading Dark Quark",nbins,0,10);
    USEFULID[J][0] = new TH1D((const TString)("LUSEFULID"+to_string(J)),"pdgId of Useful BSM from Leading Dark Quark",nbins,4900100,4900114);
    USEFULID[J][1] = new TH1D((const TString)("SLUSEFULID"+to_string(J)),"pdgId of Useful BSM from Subleading Dark Quark",nbins,4900100,4900114);
    NUSEFUL[J] = new TH1D((const TString)("NUSEFUL"+to_string(J)),"NO. Visible Dark Hadrons",nbins,0,16);
    NVDH[J] = new TH1D((const TString)("NVDH"+to_string(J)),"NO. Unstable Dark Hadrons",nbins,0,16);
    NIDH[J] = new TH1D((const TString)("NIDH"+to_string(J)),"NO. Stable Dark Hadrons",nbins,0,16);
    U_VRAT[J] = new TH1D((const TString)("U_VRAT"+to_string(J)),"Fraction of Unstable Dark Hadrons which are Visible",nbins,0,1);
    I_VRAT[J] = new TH1D((const TString)("I_VRAT"+to_string(J)),"Stable to Unstable Ratio",nbins,0,6);
    I_ARAT[J] = new TH1D((const TString)("I_ARAT"+to_string(J)),"Fraction of Dark Hadrons which are Stable",nbins,0,1);
    U_ARAT[J] =new TH1D((const TString)("U_ARAT"+to_string(J)),"Fraction of Dark Hadrons  which are Invisible",nbins,0,1);
    QPTRAT[J] = new TH1D((const TString)("QPTRAT"+to_string(J)),"Ratio of Subleading Dark Quark to Leading Dark Quark Pt",nbins,0.6,1);
    DMNC[J] = new TH1D((const TString)("DMNC"+to_string(J)),"BSM NO. Children",nbins,0,5);
    QMATCHES[J][0] = new TH1D((const TString)("QMATCHES0"+to_string(J)),(const TString)("NO. Jets with DR(J,\\chi_{1}) <"+(TString)to_string(matchcut)+jt),nbins,0,5);
    QMATCHES[J][1] = new TH1D((const TString)("QMATCHES1"+to_string(J)),(const TString)("NO. Jets with DR(J,\\chi_{2}) <"+(TString)to_string(matchcut)+jt),nbins,0,5);
    PTBALPT[J] = new TH1D((const TString)("PTBALPT"+std::to_string(J)),"P_{t} Balance Between Leading & Subleading Jets"+jt,nbins,0,1);
    PTBALMET[J] = new TH1D((const TString)("PTBALMET"+std::to_string(J)),"P_{t} Balance Between MET Aligned & Anti-Aligned Jets"+jt,nbins,0,1);
    DMRAT[J][0] = new TH1D((const TString)("DMRATI"+to_string(J)),"Ratio of stable dark hadron children which are DM with |pdgId| = 53,52,51 (Individual Hadrson)",nbins,0,1);
    DMRAT[J][1] = new TH1D((const TString)("DMRATA"+to_string(J)),"Ratio of stable dark hadron children which are DM with |pdgId| = 53,52,51 (All Hadrons Per Event)",nbins,0,1);
    NJETDR[J][0] = new TH2D((const TString)("NJETDR0"+to_string(J)),"NO. Jets with DR(J,\\chi_{1}) < X"+jt,30,0,drbinr,15,0,15);
    NJETDR[J][1] = new TH2D((const TString)("NJETDR1"+to_string(J)),"NO. Jets with DR(J,\\chi_{2}) < X"+jt,30,0,drbinr,15,0,15);
    for(int q = 0; q < 2; q++){
      for(int y = 0; y < 3; y++){
	NJETINT[J][q][y] = new TH2D((const TString)("NJETINT"+to_string(q)+to_string(y)+to_string(J)),"NO. Jets with DR(J,\\chi_{1}) < X"+jt,30,0,drbinr,15,0,15);
	NJETPT[J][q][y] = new TH2D((const TString)("NJETPT"+to_string(q)+to_string(y)+to_string(J)),"NO. Jets with DR(J,\\chi_{1}) < X"+jt,30,0,drbinr,15,0,15);
      }
    }
    CATCHRAT[J][0] = new TH1D((const TString)("CATCHRAT0"+to_string(J)),(const TString)("Ratio of Visible dark hadrons 'caught' by leading quark within DR<"+to_str(catchdr)),nbins,0,1.001);
    CATCHRAT[J][1] = new TH1D((const TString)("CATCHRAT1"+to_string(J)),(const TString)("Ratio of Visible dark hadrons 'caught' by subleading quark within DR<"+to_str(catchdr)),nbins,0,1.001);
    CATCHRATJ[J][0] = new TH1D((const TString)("CATCHRATJ0"+to_string(J)),(const TString)("Ratio of Visible dark hadrons 'caught' by closest jet to leading quark"+jt),nbins,0,1.001);
    CATCHRATJ[J][1] = new TH1D((const TString)("CATCHRATJ1"+to_string(J)),(const TString)("Ratio of Visible dark hadrons 'caught' by closest jet to subleading quark"+jt),nbins,0,1.001);
    STARTDIST[J][0] = new TH1D((const TString)("STARTDIST0"+to_string(J)),"Distance between average visible dark hadron position from leading quark and the closest jet"+jt,nbins,0,001);
    STARTDIST[J][1] = new TH1D((const TString)("STARTDIST1"+to_string(J)),"Distance between average visible dark hadron position from subleading quark and the closest jet"+jt,nbins,0,1);
    JETPTCATCH[J][0] = new TH1D((const TString)("JETPTCATCH0"+to_string(J)),"Pt of closest jet to the VDH average position"+jt,nbins,0,1000);
    JETPTCATCH[J][1] = new TH1D((const TString)("JETPTCATCH1"+to_string(J)),"Pt of the closest jet to the VDH average position"+jt,nbins,0,1000);
    NMISS[J] = new TH1D((const TString)("NMISS"+to_string(J)),"Number of missing BSM particles",nbins,0,20);
    VDHPT[J][0] = new TH1D((const TString)("VDHPT0"+std::to_string(J)),"Visible Dark Hadron p_{T} From Leading Dark Quark",nbins,0,1000);
    VDHPT[J][1] = new TH1D((const TString)("VDHPT1"+std::to_string(J)),"Visible Dark Hadron p_{T} From Subleading Dark Quark",nbins,0,1000);
    DPHIMATCH[J][0] = new TH1D((const TString)("DPHIMATCH0"+std::to_string(J)),"DPhi(Matched Jet,MET) From Leading Dark Quark"+jt,nbins,0,TMath::Pi());
    DPHIMATCH[J][1] = new TH1D((const TString)("DPHIMATCH1"+std::to_string(J)),"DPhi(Matched Jet,MET) From Subleading Dark Quark"+jt,nbins,0,TMath::Pi());
    DPHIJETS[J][0] = new TH1D((const TString)("DPHIJETS0"+std::to_string(J)),"DPhi(Leading Jet,MET)"+jt,nbins,0,TMath::Pi());
    DPHIJETS[J][1] = new TH1D((const TString)("DPHIJETS1"+std::to_string(J)),"DPhi(Subleading Jet,MET)"+jt,nbins,0,TMath::Pi());
    DPHIJETS[J][2] = new TH1D((const TString)("DPHIJETS2"+std::to_string(J)),"DPhi(Jet Sum,MET)"+jt,nbins,0,TMath::Pi());
    DPHIMIN[J][0] = new TH1D((const TString)("DPHIMIN0"+std::to_string(J)),(const TString)("Minimum DPhi(Jet,MET) For All Jets with p_{T} > "+(TString)to_str(ptc)+jt),nbins,0,TMath::Pi());
    DPHIMIN[J][1] = new TH1D((const TString)("DPHIMIN1"+std::to_string(J)),"Minimum DPhi(Jet,MET) For Leading And Subleading Jets"+jt,nbins,0,TMath::Pi());
    JETPTCORR[J] = new TH2D((const TString)("JETPTCORR"+std::to_string(J)),"Leading Jet p_{T} vs Subleading Jet p_{T}",nbins,0,1000,nbins,0,700);
    MATCHDPHICORR[J] = new TH2D((const TString)("MATCHDPHICORR"+std::to_string(J)),"DPhi With MET Of Leading Matched Jets vs Subleading Mathed Jets",nbins,0,TMath::Pi(),nbins,0,TMath::Pi());
  }

  /////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////////////////

  for (int j = 0; j<nsamples; j++){
    int M = 0;
    int r = 0;
    if(j == 1) r = 1;
    if(j == 2) M = 1;
    if(j == 3){
      M = 1;
      r = 1;
    }
    


    int pass1 = 0;

    int success = 0;

    TChain *chain = new TChain(tree_entry);

    cout << "Z" << filevarM[M] << "r" << filevarr[r] << ":" << endl;
    for (int i = 0;i<3;i++){
      TString ndfilenam = "user.ebusch.2909"+ndN[3*j+i]+"._000001.tree.root";
      TString filenam = datadirmain+datadirsub+filename1+fileN[j]+filename2+filevarM[M]+"_"+filevarr[r]+mcs[i]+filename3;
      chain-> Add(filenam+"/"+ndfilenam);
      cout << mcs[i] << endl;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////

    int ntruthBSM[22];
    chain->SetBranchAddress("ntruthBSM",&ntruthBSM);

    vector<int> *truthBSM_status = nullptr;
    chain->SetBranchAddress("truthBSM_status",&truthBSM_status);

    vector<int> *truthBSM_pdgId = nullptr;
    chain->SetBranchAddress("truthBSM_pdgId",&truthBSM_pdgId);

    vector<float> *truthBSM_pt = nullptr;
    chain->SetBranchAddress("truthBSM_pt",&truthBSM_pt);

    vector<float> *truthBSM_eta = nullptr;
    chain->SetBranchAddress("truthBSM_eta",&truthBSM_eta);

    vector<float> *truthBSM_phi = nullptr;
    chain->SetBranchAddress("truthBSM_phi",&truthBSM_phi);

    vector<float> *truthBSM_e = nullptr;
    chain->SetBranchAddress("truthBSM_e",&truthBSM_e);

    vector<float> *truthBSM_m = nullptr;
    chain->SetBranchAddress("truthBSM_m",&truthBSM_m);

    vector<int> *truthBSM_barcode = nullptr;
    chain->SetBranchAddress("truthBSM_barcode",&truthBSM_barcode);

    vector<int> *truthBSM_nChildren = nullptr;
    chain->SetBranchAddress("truthBSM_nChildren",&truthBSM_nChildren);

    vector<vector<int>> *truthBSM_child_status = nullptr;
    chain->SetBranchAddress("truthBSM_child_status",&truthBSM_child_status);

    vector<vector<int>> *truthBSM_child_pdgId = nullptr;
    chain->SetBranchAddress("truthBSM_child_pdgId",&truthBSM_child_pdgId);

    vector<vector<int>> *truthBSM_child_barcode = nullptr;
    chain->SetBranchAddress("truthBSM_child_barcode",&truthBSM_child_barcode);

    vector<int> *truthBSM_nParents = nullptr;
    chain->SetBranchAddress("truthBSM_nParents",&truthBSM_nParents);

    vector<vector<int>> *truthBSM_parent_status = nullptr;
    chain->SetBranchAddress("truthBSM_parent_status",&truthBSM_parent_status);

    vector<vector<int>> *truthBSM_parent_pdgId = nullptr;
    chain->SetBranchAddress("truthBSM_parent_pdgId",&truthBSM_parent_pdgId);
    
      int na4_pflowjets[22];

      vector<float> *a4_pflowjets_pt = nullptr;

      vector<float> *a4_pflowjets_eta = nullptr;

      vector<float> *a4_pflowjets_phi = nullptr;

      vector<float> *a4_pflowjets_E = nullptr;

      int na10_lctopojets[22];

      vector<float> *a10_lctopojets_pt = nullptr;

      vector<float> *a10_lctopojets_eta = nullptr;

      vector<float> *a10_lctopojets_phi = nullptr;

    if(!istruth){
      chain->SetBranchAddress("na4_pflowjets",&na4_pflowjets);

      chain->SetBranchAddress("a4_pflowjets_pt",&a4_pflowjets_pt);

      chain->SetBranchAddress("a4_pflowjets_eta",&a4_pflowjets_eta);

      chain->SetBranchAddress("a4_pflowjets_phi",&a4_pflowjets_phi);

      chain->SetBranchAddress("a4_pflowjets_E",&a4_pflowjets_E);

      chain->SetBranchAddress("na10_lctopojets",&na10_lctopojets);

      chain->SetBranchAddress("a10_lctopojets_pt",&a10_lctopojets_pt);

      chain->SetBranchAddress("a10_lctopojets_eta",&a10_lctopojets_eta);

      chain->SetBranchAddress("a10_lctopojets_phi",&a10_lctopojets_phi);
    }
    else{
      
      chain->SetBranchAddress("na4_truth",&na4_pflowjets);

      chain->SetBranchAddress("a4_pflowjets_truth_pt",&a4_pflowjets_pt);

      chain->SetBranchAddress("a4_pflowjets_truth_eta",&a4_pflowjets_eta);

      chain->SetBranchAddress("a4_pflowjets_truth_phi",&a4_pflowjets_phi);

      chain->SetBranchAddress("a4_pflowjets_truth_E",&a4_pflowjets_E);

      chain->SetBranchAddress("na10_truth",&na10_lctopojets);

      chain->SetBranchAddress("a10_truth_pt",&a10_lctopojets_pt);

      chain->SetBranchAddress("a10_truth_eta",&a10_lctopojets_eta);

      chain->SetBranchAddress("a10_truth_phi",&a10_lctopojets_phi);

    }
    float metFinalTrk;
    chain->SetBranchAddress("metFinalTrk",&metFinalTrk);

    float metFinalTrkPx;
    chain->SetBranchAddress("metFinalTrkPx",&metFinalTrkPx);
    
    float metFinalTrkPy;
    chain->SetBranchAddress("metFinalTrkPy",&metFinalTrkPy);

    float metFinalTrkPhi;
    chain->SetBranchAddress("metFinalTrkPhi",&metFinalTrkPhi);

    float metFinalTrkSumEt;
    chain->SetBranchAddress("metFinalTrkSumEt",&metFinalTrkSumEt);

    float actualInteractionsPerCrossing;
    chain->SetBranchAddress("actualInteractionsPerCrossing",&actualInteractionsPerCrossing);

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////

    int passes = 0;
    int eventpicn = 0;

    vector<int> IDS;
    IDS.clear();

    vector<int> CIDS;
    CIDS.clear();

    nevents[j] = chain->GetEntries();

    int events[eventpicmax] = {3042,4425,5089};

    TH1D* matches = new TH1D((const TString)("matches"+std::to_string(j)),"",4,0,4);        // BIN1 -> 0JETS | BIN2 -> JET1 | BIN3 -> JET2 | BIN4 -> BOTHJETS

    TH1D* matchescut = new TH1D((const TString)("matchescut"+std::to_string(j)),"",4,0,4);  // BIN1 -> 0JETS | BIN2 -> JET1 | BIN3 -> JET2 | BIN4 -> BOTHJETS

    TH1D* matchesmet = new TH1D((const TString)("matchesmet"+std::to_string(j)),"",7,0,7);        // BIN1,2 -> NONE / BIN3,4 -> J1||MET / BIN5,6 -> J2||MET / BIN7 -> (J1+J2)||MET

    TH1D* matchesmetcut = new TH1D((const TString)("matchesmetcut"+std::to_string(j)),"",7,0,7);  // BIN1,2 -> NONE / BIN3,4 -> J1||MET / BIN5,6 -> J2||MET / BIN7 -> (J1+J2)||MET

    vdhnmatch[j] = new TH1D((const TString)("vdhnmatch"+std::to_string(j)),"",7,0,7); // BIN1 -> (0,0) | BIN2 -> (0,>0) | BIN3 -> (>0,0) | BIN4 -> (>0,>0) | BIN5 -> (0,>1) ... BIN7 -> (>1,>1)

    for(int e = 0; e < chain->GetEntries(); e++){
      chain->GetEntry(e);

      int Q1MATCH = 0;
      int Q2MATCH = 0;    
      
      int njets = na4_pflowjets[0];
      int nljets = na10_lctopojets[0];
      
      njets = a4_pflowjets_pt->size();
      nljets = a10_lctopojets_pt->size();

      int nbsm = ntruthBSM[0];
      float JETPT[njets];
      float JETETA[njets];
      float JETPHI[njets];
      float JETE[njets];
      float JETMATCH[njets];

      float LJETPT[nljets];
      float LJETETA[nljets];
      float LJETPHI[nljets];
      float LJETMATCH[nljets];

      int BSMID[nbsm];
      int BSMS[nbsm];
      float BSMPT[nbsm];
      float BSMETA[nbsm];
      float BSMPHI[nbsm];
      float BSME[nbsm];
      int BSMNP[nbsm];
      int BSMNC[nbsm];
      int BSMB[nbsm];
      int BSMUSE[nbsm];

      int JN[2] = {0,0};
      int LJN[2] = {0,0};
      int BN[2] = {0,0};
      
      int njetpt = 0;
      float pttemp[2] = {0,0};
      bool closejet = false;
      for(int J = 0; J < njets; J++){
	JETPT[J] = a4_pflowjets_pt->at(J);
	JETETA[J] = a4_pflowjets_eta->at(J);
	JETPHI[J] = a4_pflowjets_phi->at(J);
	JETE[J] = a4_pflowjets_E->at(J);
	JETMATCH[J] = 0;
        if(JETPT[J] > pttemp[0]){JN[1] = JN[0]; JN[0] = J; pttemp[0] = JETPT[J];}
	else if(JETPT[J] > pttemp[1]){JN[1] = J; pttemp[1] = JETPT[J];}
	if(JETPT[J] > ptc && std::abs(JETPHI[J]) < TMath::Pi() && std::abs(JETETA[J]) < 4.5){njetpt++;}
	if(JETPT[J] > ptc && std::abs(JETPHI[J]) > 2.8 && std::abs(JETETA[J]) > 4){closejet = true;}
      }

      int nljetpt = 0;
      pttemp[0] = 0;
      pttemp[1] = 0;
      for(int J = 0; J < nljets; J++){
	LJETPT[J] = a10_lctopojets_pt->at(J);
	LJETETA[J] = a10_lctopojets_eta->at(J);
	LJETPHI[J] = a10_lctopojets_phi->at(J);
        LJETMATCH[J] = 0;
	if(LJETPT[J] > pttemp[0]){LJN[1] = LJN[0]; LJN[0] = J;pttemp[0] = LJETPT[J];}
	else if(LJETPT[J] > pttemp[1]){LJN[1] = J;pttemp[0] = LJETPT[J];}
	if(LJETPT[J] > ptlc && std::abs(LJETPHI[J]) < TMath::Pi() && std::abs(LJETETA[J]) < 4.5){nljetpt++;}
      }


      int nQ = 0;
      int nQz = 0;
      int nZ = 0;
      int nDH = 0;
      int nVDH = 0;
      int nUDH = 0;
      int nIDH = 0;
      pttemp[0] = 0; pttemp[1] = 0;

      vector<int> VDHNCV111;
      vector<int> VDHNCV113;
      VDHNCV111.clear();
      VDHNCV113.clear();      
      vector<int> IVDHNCV211;
      vector<int> IVDHNCV213;
      IVDHNCV211.clear();
      IVDHNCV213.clear();
      vector<int> VDHCIV111;
      vector<int> VDHCIV113;
      VDHCIV111.clear();
      VDHCIV113.clear();
      vector<float> dmrat;
      dmrat.clear();
      vector<float> dmrata;
      dmrata.clear();
      vector<int> barcodes;
      barcodes.clear();

      int nDMa = 0;
      int nc = 0;
      int tracker = -1;
      int trackb = 0;
      for(int B = 0; B < nbsm; B++){
	BSMID[B] = truthBSM_pdgId->at(B);
	BSMS[B] = truthBSM_status->at(B);
	BSMPT[B] = truthBSM_pt->at(B);
	BSMETA[B] = truthBSM_eta->at(B);
	BSMPHI[B] = truthBSM_phi->at(B);
	BSME[B] = truthBSM_e->at(B);
	BSMNP[B] = truthBSM_nParents->at(B);
	BSMNC[B] = truthBSM_nChildren->at(B);
	BSMB[B] = truthBSM_barcode->at(B);
	barcodes.push_back(BSMB[B]);
	if(!( count(IDS.begin(),IDS.end(),BSMID[B]) )){IDS.push_back(BSMID[B]);}
	if( std::abs(BSMID[B]) == 4900101 && BSMS[B] == 23 
	    //&& BSMNP[B] == 1 && std::abs(truthBSM_parent_pdgId->at(B).at(0)) == 5000001 //check this!!!
	    ){
	  if(BSMPT[B] > pttemp[0]){BN[1] = BN[0]; BN[0] = B;}
	  else if(BSMPT[B] > pttemp[1]){BN[1] = B;}
	  nQz++;
	}
	if(BSMID[B] == 5000001){nZ++;}
	if(std::abs(BSMID[B]) == 4900101){nQ++;}
	if(std::abs(BSMID[B]) == 4900111){
	  nVDH++; nDH++; VDHNCV111.push_back(BSMNC[B]);
	  if(BSMNC[B] != 0){
	    for(int q = 0; q < BSMNC[B]; q++){
	      VDHCIV111.push_back(truthBSM_child_pdgId->at(B).at(q)); // FILLS 111CHILD ID
	    }
	    tracker = -1;
	    for(int v = 0; v < BSMNC[B]; v++){
	      trackb = 0;
	      float cid = abs(truthBSM_child_pdgId->at(B)[v]);
	      if(cid < 50 || (53 < cid && cid < 4900000)){trackb ++;} //ADDS TO TRACKB FOR EACH BSM CHILD
	      if(trackb != 0){tracker = 1;} // SETS TO USEFUL HADRON  
	    }
	    if(tracker == 1 && BSMPT[B] > vptmin){
	      BSMUSE[B] = 1; nUDH++;
	    }
	    else{BSMUSE[B] = 0;}
	    int nDM = 0;
	    for(int c = 0; c < BSMNC[B]; c++){
	      if(std::abs(truthBSM_child_pdgId->at(B).at(c)) == 53 || std::abs(truthBSM_child_pdgId->at(B).at(c)) == 52 || std::abs(truthBSM_child_pdgId->at(B).at(c)) == 51){nDMa++;nDM++;}
	    }
	    dmrat.push_back((double)((double)nDM/(double)BSMNC[B]));
	    nc += BSMNC[B];
	  }
	}
	if(std::abs(BSMID[B]) == 4900113){
	  nVDH++; nDH++; VDHNCV113.push_back(BSMNC[B]);
	  if(BSMNC[B] != 0){
	    for(int q = 0; q < BSMNC[B]; q++){
	      VDHCIV113.push_back(truthBSM_child_pdgId->at(B).at(q));
	    }
	    tracker = -1;
	    for(int v = 0; v < BSMNC[B]; v++){
	      trackb = 0;
	      float cid = abs(truthBSM_child_pdgId->at(B)[v]);
	      if(cid < 50 || (53 < cid && cid < 4900000)){trackb ++;}
		if(trackb != 0){tracker = 1;}
	    }
	    if(tracker == 1 && BSMPT[B] > vptmin){
	      BSMUSE[B] = 1; nUDH++;  	      
	    }
	    else{BSMUSE[B] = 0;}
	    int nDM = 0;
	    for(int c = 0; c < BSMNC[B]; c++){
	      if(std::abs(truthBSM_child_pdgId->at(B).at(c)) == 53 || std::abs(truthBSM_child_pdgId->at(B).at(c)) == 52 || std::abs(truthBSM_child_pdgId->at(B).at(c)) == 51){nDMa++;nDM++;}
	    }
	    dmrat.push_back((double)((double)nDM/(double)BSMNC[B]));
	    nc += BSMNC[B];
	  }
	}
	if(std::abs(BSMID[B]) == 4900211){IVDHNCV211.push_back(BSMNC[B]); nIDH++; nDH++;}
	if(std::abs(BSMID[B]) == 4900213){IVDHNCV213.push_back(BSMNC[B]); nIDH++; nDH++;}
              	
      }

      int nmisses = 0;
      for(int B = 0; B < nbsm; B++){
      	for(int c = 0; c < BSMNC[B]; c++){
	  float cid = abs(truthBSM_child_pdgId->at(B)[c]);
	  if(!(count(barcodes.begin(),barcodes.end(),truthBSM_child_barcode->at(B)[c]) )  
      	     && !(cid < 50 || (53 < cid && cid < 4900000))
	     //&& (cid == 4900111 || cid == 4900113 || cid == 4900211 || cid == 4900213)
	     ){
	    if(!(count(CIDS.begin(),CIDS.end(),truthBSM_child_pdgId->at(B)[c]))){CIDS.push_back(truthBSM_child_pdgId->at(B)[c]);}
	    nmisses++;
	  }
      	}
      }

      dmrata.push_back((double)((double)nDMa/(double)nc));
    
      


      float JETJETDR[njets][njets]; float JETJETDETA[njets][njets]; float JETJETDPHI[njets][njets]; 
      float BSMBSMDR[nbsm][nbsm]; float BSMBSMDETA[nbsm][nbsm]; float BSMBSMDPHI[nbsm][nbsm];
      float JETBSMDR[njets][nbsm]; float JETBSMDETA[njets][nbsm]; float JETBSMDPHI[njets][nbsm]; 
      float JETMETDPHI[njets];
      
      float metphi = metFinalTrkPhi;
      int JNM[2] = {0,0};

      float tempdphi = 0;
      float tempdeta = 0;
      float metdphimin = 4;
      float metdphimax = 0;
      for(int J1 = 0; J1 < njets; J1++){
	for(int J2 = 0; J2 < njets; J2++){
	  JETJETDPHI[J1][J2] = std::abs(JETPHI[J1] - JETPHI[J2]);
	  JETJETDPHI[J1][J2] = std::min((double)JETJETDPHI[J1][J2], (double)(2*TMath::Pi() - JETJETDPHI[J1][J2]));
	  JETJETDETA[J1][J2] = std::abs(JETETA[J1] - JETETA[J2]);
	  JETJETDR[J1][J2] = std::sqrt(JETJETDPHI[J1][J2]*JETJETDPHI[J1][J2] + JETJETDETA[J1][J2]*JETJETDETA[J1][J2]);
	}
	for(int B2 = 0; B2 < nbsm; B2++){
	  JETBSMDPHI[J1][B2] = std::abs(JETPHI[J1] - BSMPHI[B2]);
	  JETBSMDPHI[J1][B2] = std::min((double)JETBSMDPHI[J1][B2], (double)(2*TMath::Pi() - JETBSMDPHI[J1][B2]));
	  JETBSMDETA[J1][B2] = std::abs(JETETA[J1] - BSMETA[B2]);
	  JETBSMDR[J1][B2] = std::sqrt(JETBSMDPHI[J1][B2]*JETBSMDPHI[J1][B2] + JETBSMDETA[J1][B2]*JETBSMDETA[J1][B2]);
	}
	if(JETBSMDR[J1][BN[0]] < matchcut){JETMATCH[J1] = 1; Q1MATCH += 1;}
	else if(JETBSMDR[J1][BN[1]] < matchcut){JETMATCH[J1] = 2; Q2MATCH += 1;}
	else{JETMATCH[J1] = 3;}
	
	JETMETDPHI[J1] = std::abs(JETPHI[J1] - metphi);
	JETMETDPHI[J1] = std::min(JETMETDPHI[J1], (float)(2*TMath::Pi() - JETMETDPHI[J1]));
	if(metdphimin > JETMETDPHI[J1]){JNM[0] = J1; metdphimin = JETMETDPHI[J1];}
	if(metdphimax < JETMETDPHI[J1]){JNM[1] = J1; metdphimax = JETMETDPHI[J1];}
      }
      for(int B1 = 0; B1 < nbsm; B1++){
	for(int B2 = 0; B2 < nbsm; B2++){
	  BSMBSMDPHI[B1][B2] = std::abs(BSMPHI[B1] - BSMPHI[B2]);
	  BSMBSMDPHI[B1][B2] = std::min((double)BSMBSMDPHI[B1][B2], (double)(2*TMath::Pi() - BSMBSMDPHI[B1][B2]));
	  BSMBSMDETA[B1][B2] = std::abs(BSMETA[B1] - BSMETA[B2]);
	  BSMBSMDR[B1][B2] = std::sqrt(BSMBSMDPHI[B1][B2]*BSMBSMDPHI[B1][B2] + BSMBSMDETA[B1][B2]*BSMBSMDETA[B1][B2]);
	}
      }

      float MET = metFinalTrk;

      float j12sumphi = std::min(JETPHI[JN[0]] + JETPHI[JN[1]],(float)(2*TMath::Pi() - JETPHI[JN[0]] - JETPHI[JN[1]]));
      float summetdphi = std::abs(j12sumphi - metphi);
      summetdphi = std::min(summetdphi,(float)(2*TMath::Pi() - summetdphi));

      float j1xp = JETPT[JN[0]]*sin(JETPHI[JN[0]]); float j1xm = JETPT[JNM[0]]*sin(JETPHI[JNM[0]]);
      float j1yp = JETPT[JN[0]]*cos(JETPHI[JN[0]]); float j1ym = JETPT[JNM[0]]*cos(JETPHI[JNM[0]]);
      float j2xp = JETPT[JN[1]]*sin(JETPHI[JN[1]]); float j2xm = JETPT[JNM[1]]*sin(JETPHI[JNM[1]]);
      float j2yp = JETPT[JN[1]]*cos(JETPHI[JN[1]]); float j2ym = JETPT[JNM[1]]*cos(JETPHI[JNM[1]]);

      float ptbalp = (double)(std::sqrt((j1xp+j2xp)*(j1xp+j2xp)+(j1yp+j2yp)*(j1yp+j2yp)))/(double)(std::sqrt(j1xp*j1xp+j1yp*j1yp) + std::sqrt(j2xp*j2xp+j2yp*j2yp));
      float ptbalm = (double)(std::sqrt((j1xm+j2xm)*(j1xm+j2xm)+(j1ym+j2ym)*(j1ym+j2ym)))/(double)(std::sqrt(j1xm*j1xm+j1ym*j1ym) + std::sqrt(j2xm*j2xm+j2ym*j2ym));
     
      // TVector3 j1;
      // TVector3 j2;
      // TVector3 j12;
      // j1.SetPtEtaPhi(JETPT[JN[0]],JETETA[JN[0]],JETPHI[JN[0]]);
      // j2.SetPtEtaPhi(JETPT[JN[1]],JETETA[JN[1]],JETPHI[JN[1]]);
      // j12.SetPtEtaPhi(0,0,0);
      // j12 += j1;
      // j12 += j2;
      // ptbalp = (double)((double)j12.Mag()/(double)(j1.Mag()+j2.Mag()));

      // j1.SetPtEtaPhi(JETPT[JNM[0]],JETETA[JNM[0]],JETPHI[JNM[0]]);
      // j2.SetPtEtaPhi(JETPT[JNM[1]],JETETA[JNM[1]],JETPHI[JNM[1]]);
      // j12.SetPtEtaPhi(0,0,0);
      // j12 = j1 + j2;
      // ptbalm = (double)(j12.Mag()/(j1.Mag()+j2.Mag()));


      float MAXDRL = 0;
      float MAXDRSL = 0;
      float tempdr = 0;
	  
      vector<int> PERMVDHN[2];
      PERMVDHN[0].clear();
      PERMVDHN[1].clear();

      for(int B = 0; B < nbsm; B++){
	if((std::abs(BSMID[B]) == 4900111 || std::abs(BSMID[B]) == 4900113) && BSMUSE[B] == 1){
	  if(BSMBSMDR[B][BN[0]] < BSMBSMDR[B][BN[1]]){
	    PERMVDHN[0].push_back(B);
	  }
	  else{PERMVDHN[1].push_back(B);}
	}
      }


      if(true){ // CALCULATES THE MAXDR
        for(int q = 0; q < PERMVDHN[0].size(); q++){
	  for(int w = q+1; w < PERMVDHN[0].size(); w++){
	    tempdr = BSMBSMDR[PERMVDHN[0].at(q)][PERMVDHN[0].at(w)];
	    if(tempdr > MAXDRL){MAXDRL = tempdr;}
	  }
	}
	tempdr = 0;
	for(int q = 0; q < PERMVDHN[1].size(); q++){
	  for(int w = q+1; w < PERMVDHN[1].size(); w++){
	    tempdr = BSMBSMDR[PERMVDHN[1].at(q)][PERMVDHN[1].at(w)];
	    if(tempdr > MAXDRSL){MAXDRSL = tempdr;}
	  }
	}	  
      }

      float startphi[2] = {0,0};
      float starteta[2] = {0,0};
      float sumeta;
      float sumphi; 
	
      for(int o = 0; o < 2; o++){
	sumeta = 0;
	sumphi = 0;
	for(int y = 0; y < PERMVDHN[o].size(); y++){
	  sumeta += BSMETA[PERMVDHN[o].at(y)];
	  sumphi += BSMPHI[PERMVDHN[o].at(y)];
	}
	startphi[o] = (float)sumphi/(float)PERMVDHN[o].size();
	starteta[o] = (float)sumeta/(float)PERMVDHN[o].size();
	// if(PERMVDHN[o].size() != 0){cout << startphi[o]<<endl;}
      }
      // cout << "_____" << endl;
      int closejets[2] = {0,0};
      float tmpdphi;
      float tmpdeta;
      float tmpdr;
      float minr[2] = {1000,1000};
      

      for(int o = 0; o < 2; o++){
	tmpdphi = 0;
	tmpdeta = 0;
	tmpdr = 0;
	for(int J = 0; J < njets; J++){
	  tmpdphi = std::abs(JETPHI[J] - startphi[o]);
	  tmpdphi = std::min((double)tmpdphi, 2*TMath::Pi() - tmpdphi);
	  tmpdeta = std::abs(JETETA[J] - starteta[o]);
	  tmpdr = std::sqrt(tmpdeta*tmpdeta + tmpdphi*tmpdphi);
	  if(tmpdr < minr[o] && JETPT[J] > ptc){closejets[o] = J; minr[o] = tmpdr;}
	}
	//cout << closejets[o] << endl;
      }
      //cout << "____" << endl;
      float DETA = 0;
      float DPHI = 0;
      float DR = 0;
      int catches[2] = {0,0};
      int jcatches[2] = {0,0};

      for(int o = 0; o < 2; o++){
	for(int y = 0; y < PERMVDHN[o].size(); y++){
	  DPHI = std::abs(BSMPHI[PERMVDHN[o].at(y)] - startphi[o]);
	  DPHI = std::min((double)DPHI, 2*TMath::Pi() - DPHI);
	  DETA = std::abs(BSMETA[PERMVDHN[o].at(y)] - starteta[o]);
	  DR = std::sqrt(DETA*DETA + DPHI*DPHI);
	  if(DR <= catchdr){catches[o]++;}
	  if(JETBSMDR[closejets[o]][PERMVDHN[o].at(y)] <= catchdr){jcatches[o]++;}
    
	}
      }
           

      

      int nc1 = BSMNC[BN[0]];
      int nc2 = BSMNC[BN[1]];
      if(nc1 > 0 && nc2 > 0 && nQz >= 2){


	vector<int> CHILDB;
	vector<int> CHILDN;

	vector<int> TEMPCHILDB;
	vector<int> TEMPCHILDN;

	vector<int> TEMPVB;
	vector<int> TEMPVN;

	// PERMVDHN[0].clear();
	// PERMVDHN[1].clear();
	CHILDB.clear();
	CHILDN.clear();
	TEMPCHILDB.clear();
	TEMPCHILDN.clear();
	TEMPVB.clear();
	TEMPVN.clear();
	


	// for(int Y = 2; Y < 2; Y++){
	
	//   int N = 0;
	//   int tracker = 0;
	//   for(int c = 0; c < nc1; c++){ // INITIALIZES THE TEMP VECTOR OF CHILD BARCODES AND NUMBER
	//     CHILDB.push_back(truthBSM_child_barcode->at(BN[Y])[c]);
	//     for(int B = 0; B < nbsm; B++){
	//       if(BSMB[B] == CHILDB[c]){CHILDN.push_back(B);}
	//     }
	//     if(CHILDN.size() != CHILDB.size()){CHILDB.pop_back();} // INCASE THE DECAY IS NON BSM
	//   }
	//   if(true){
	//     int t = -1;
	//     while(true){ // FINDS THE NUMBER OF THE USEFUL VISIBLE DARK HADRONS IN THE DECAY CHAIN OF THE ELADING BSM
	//       for(int c = 0; c < CHILDB.size(); c++){
	// 	N = CHILDN.at(c);
	// 	tracker = 0;
	// 	// if((std::abs(BSMID[N]) == 4900111 || std::abs(BSMID[N]) == 4900113) && BSMNC[N] > 0){ // CHECKS IF VDH
	// 	//   tracker = 0;
	// 	//   for(int v = 0; v < BSMNC[N]; v++){ // LOOPS OVER VDH CHILDREN TO DETERMINE IF IT IS A USEFUL VDH
	// 	//     if(std::abs(truthBSM_child_pdgId->at(N)[v]) < 50 && tracker == 0){ // CHECKS IF ANY DECAY IS SM
	// 	//       tracker = 1; 
	// 	//       // for(int B = 0; B < nbsm; B++){
	// 	//       // 	if(BSMB[B] == truthBSM_child_barcode->at(N)[v]){
	// 	// 	  t = -1;
	// 	// 	  if(PERMVDHN[Y].size() > 0){
	// 	// 	    for(int l = 0; l < PERMVDHN[Y].size(); l++){
	// 	// 	      if(PERMVDHN[Y].at(l) == N){t = 0;}
	// 	// 	    }
	// 	// 	  }
	// 	// 	  if(t == -1){PERMVDHN[Y].push_back(N);} //REMOVES DUPLICATES
	// 	// 	  //}
	// 	//     //}
	// 	//     }
	// 	//     else if(std::abs(truthBSM_child_pdgId->at(N)[v]) > 50){ // IF DM DECAY THEN MOVE THE DM TO TEMP STORAGE
	// 	//       t = -1;
	// 	//       if(TEMPVB.size() > 0){
	// 	// 	for(int l = 0; l < TEMPVB.size(); l++){
	// 	// 	  if(TEMPVB.at(l) == truthBSM_child_barcode->at(N)[v]){t = 0;}
	// 	// 	}
	// 	//       }
		  
	// 	//       if(t == -1){ // REMOVES DUPLICATES
	// 	// 	TEMPVB.push_back(truthBSM_child_barcode->at(N)[v]);
	// 	// 	for(int B = 0; B < nbsm; B++){
	// 	// 	  if(BSMB[B] == truthBSM_child_barcode->at(N)[v]){TEMPVN.push_back(B);}
	// 	// 	}
	// 	// 	if(TEMPVN.size() != TEMPVB.size()){TEMPVB.pop_back();} // INCASE THE DECAY IS NON BSM
	// 	//       }
	// 	//     }
	// 	//   }
	// 	//   if(tracker == 0){// IF VDH IS NOT USEFUL THEN STORE THE DM DECAYS IN NEXT ITERATION
	// 	//     for(int v = 0; v < TEMPVB.size(); v++){
	// 	//       t = -1;
	// 	//       if(TEMPCHILDB.size() > 0){
	// 	// 	for(int l = 0; l < TEMPCHILDB.size(); l++){
	// 	// 	  if(TEMPCHILDB.at(l) == TEMPVB.at(v)){t = 0;}
	// 	// 	}
	// 	//       }
	// 	//       if(t == -1){
	// 	// 	TEMPCHILDB.push_back(TEMPVB.at(v));
	// 	// 	TEMPCHILDN.push_back(TEMPVN.at(v));
	// 	//       }
	// 	//     }
	// 	//   }
	// 	//   TEMPVB.clear();
	// 	//   TEMPVN.clear();
	// 	// }
	// 	int track = 0;
	// 	if(BSMNC[N] > 0){
	// 	  tracker = 0;
	// 	  for(int v = 0; v < BSMNC[N]; v++){
	// 	    track = 0;
	// 	    for(int B = 0; B < nbsm; B++){
	// 	      if(BSMB[B] == truthBSM_child_barcode->at(N)[v]){track ++;}
	// 	    }
	// 	    if(track != BSMNC[N] && tracker == 0){ // IF DECAY IS SM THEN STORE AS USEFUL BSM
	// 	      t = -1;
	// 	      if(PERMVDHN[Y].size() > 0){
	// 		for(int l = 0; l < PERMVDHN[Y].size(); l++){
	// 		  if(PERMVDHN[Y].at(l) == N){t = 0;}
	// 		}
	// 	      }
	// 	      if(t == -1){PERMVDHN[Y].push_back(N);} //REMOVES DUPLICATES
	// 	      tracker = 1;
	// 	    }
		    
	// 	    else if(track == BSMNC[N]){ // IF DECAY IS PURELY BSM THEN STORE CHILDREN IN TEMP IN CASE REQUIRED FOR NEXT ITERATION
	// 	      t = -1;
	// 	      if(TEMPVB.size() > 0){
	// 		for(int l = 0; l < TEMPVB.size(); l++){
	// 		  if(TEMPVB.at(l) == truthBSM_child_barcode->at(N)[v]){t = 0;}
	// 		}
	// 	      }
	// 	      if(t == -1){ // REMOVES DUPLICATES
	// 		TEMPVB.push_back(truthBSM_child_barcode->at(N)[v]);
	// 		for(int B = 0; B < nbsm; B++){
	// 		  if(BSMB[B] == truthBSM_child_barcode->at(N)[v]){TEMPVN.push_back(B);}
	// 		}
	// 	      }
	// 	    }
		  
	// 	  }

	// 	  if(tracker == 0){// IF BSM IS NOT USEFUL THEN STORE THE DECAYS IN NEXT ITERATION
	// 	    for(int v = 0; v < TEMPVB.size(); v++){
	// 	      t = -1;
	// 	      if(TEMPCHILDB.size() > 0){
	// 		for(int l = 0; l < TEMPCHILDB.size(); l++){
	// 		  if(TEMPCHILDB.at(l) == TEMPVB.at(v)){t = 0;}
	// 		}
	// 	      }
	// 	      if(t == -1){
	// 		TEMPCHILDB.push_back(TEMPVB.at(v));
	// 		TEMPCHILDN.push_back(TEMPVN.at(v));
	// 	      }
	// 	    }
		    
	// 	  }		
	// 	  TEMPVB.clear();
	// 	  TEMPVN.clear();
	// 	}
	// 	// else if(BSMNC[N] > 0){
	// 	//   for(int v = 0; v < BSMNC[N]; v++){
	// 	//     if(TEMPCHILDB.size() > 0){
	// 	//       for(int l = 0; l < TEMPCHILDB.size(); l++){
	// 	// 	if(TEMPCHILDB.at(l) == truthBSM_child_barcode->at(N)[v]){t = 0;}
	// 	//       }
	// 	//     }
	// 	//     if(t == -1){
	// 	//       TEMPCHILDB.push_back(truthBSM_child_barcode->at(N)[v]);
	// 	//       for(int B = 0; B < nbsm; B++){
	// 	// 	if(BSMB[B] == truthBSM_child_barcode->at(N)[v]){TEMPCHILDN.push_back(B);}
	// 	//       }
	// 	//       if(TEMPCHILDN.size() != TEMPCHILDB.size()){TEMPCHILDB.pop_back();} // INCASE THE DECAY IS NON BSM
	// 	//     }
	// 	//   }
	// 	// }
	//       }
	//       CHILDB.clear();
	//       CHILDN.clear();
	//       if(TEMPCHILDB.size() > 0){
	// 	for(int v = 0; v < TEMPCHILDB.size(); v++){
	// 	  CHILDB.push_back(TEMPCHILDB.at(v));
	// 	  CHILDN.push_back(TEMPCHILDN.at(v));
	// 	}
	//       }	  
	//       else{break;}
	//       TEMPCHILDB.clear();
	//       TEMPCHILDN.clear();
	//     }
	//   }

	//   CHILDB.clear();
	//   CHILDN.clear();
	//   TEMPCHILDB.clear();
	//   TEMPCHILDN.clear();
	//   TEMPVB.clear();
	//   TEMPVN.clear();
	// }

        
	// if(true){ // CALCULATES THE MAXDR
	//   for(int q = 0; q < PERMVDHN[0].size(); q++){
	//     for(int w = q+1; w < PERMVDHN[0].size(); w++){
	//       tempdr = BSMBSMDR[PERMVDHN[0].at(q)][PERMVDHN[0].at(w)];
	//       if(tempdr > MAXDRL){MAXDRL = tempdr;}
	//     }
	//   }
	//   tempdr = 0;
	//   for(int q = 0; q < PERMVDHN[1].size(); q++){
	//     for(int w = q+1; w < PERMVDHN[1].size(); w++){
	//       tempdr = BSMBSMDR[PERMVDHN[1].at(q)][PERMVDHN[1].at(w)];
	//       if(tempdr > MAXDRSL){MAXDRSL = tempdr;}
	//     }
	//   }
	  
	// }


	//	cout << MAXDRL - MAXDRSL << endl;
      }     

      if(JETMATCH[JN[0]] == 3 && JETMATCH[JN[1]] == 3){matches->AddBinContent(1);}
      if((JETMATCH[JN[0]] == 1 || JETMATCH[JN[0]] == 2) && JETMATCH[JN[1]] == 3){matches->AddBinContent(2);}
      if((JETMATCH[JN[1]] == 1 || JETMATCH[JN[1]] == 2) && JETMATCH[JN[0]] == 3){matches->AddBinContent(3);}
      if(JETMATCH[JN[0]] != 3 && JETMATCH[JN[1]] != 3){matches->AddBinContent(4);}
      
      if(JN[0] == JNM[0]){
	if(JETMATCH[JN[0]] != 3){matchesmet->AddBinContent(3);}
	else{matchesmet->AddBinContent(4);}
      }
      else if(JN[1] == JNM[0]){
	if(JETMATCH[JN[1]] != 3){matchesmet->AddBinContent(5);}
	else{matchesmet->AddBinContent(6);}
      }
      else if(summetdphi < metdphimin){matchesmet->AddBinContent(7);}
      else{
	if(JETMATCH[JNM[0]] != 3){matchesmet->AddBinContent(1);}
	else{matchesmet->AddBinContent(2);}
      }
      
      /////////////////////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////////////////////
      /////////////////////////////////////////////////////////////////////////////////////////

      int TEST = -1;

      if(!(njetpt >= 2) && TEST == -1){TEST = 1;}
      // if(!(nQ >= 2) && TEST == -1){TEST = 1;}
      if(!(nQz == 2) && TEST == -1){TEST = 1;}
      // if(!(nZ == 1) && TEST == -1){TEST = 1;}
      if(!(MET > 200) && TEST == -1){TEST = 1;}
      // if(!(MET < 1000) && TEST == -1){TEST = 1;}
      // if(!(nc1 > 0) && TEST == -1){TEST = 1;}
      // if(!(nc2 > 0) && TEST == -1){TEST = 1;}

      // if(!(JN[0] == JNM[0] || JN[1] == JNM[0]) && TEST == -1){TEST = 1;}

      // if(!(closejet) && TEST == -1){TEST = 1;}

      // if(!(ptbalp > 0.99) && TEST == -1){TEST = 1;}

      // if(!(MAXDRL < 0.8) && TEST == -1){TEST = 1;}
      // if(!(MAXDRSL < 0.8) && TEST == -1){TEST = 1;}

      // if(!(PERMVDHN[0].size() != 0) && TEST == -1){TEST = 1;}
      // if(!(PERMVDHN[1].size() != 0) && TEST == -1){TEST = 1;}

      //if(!(closejets[0] == closejets[1]) && TEST == -1){TEST = 1;}

      // if(!(JETMETDPHI[JN[1]] < 0.5) && TEST == -1){TEST = 1;}

      // if(!(JETMETDPHI[JN[0]] > 2.8) && TEST == -1){TEST = 1;}

      // if(!(JETPT[JN[0]] > 200) && TEST == -1){TEST = 1;}
      // if(!(JETPT[JN[1]] > 20) && TEST == -1){TEST = 1;}

      if(TEST == -1){

	npasses[j]++;
	passes++;
	QPT[j][0]->Fill(BSMPT[BN[0]]);
	QPT[j][1]->Fill(BSMPT[BN[1]]);
	JPT[j][0]->Fill(JETPT[JN[0]]);
	JPT[j][1]->Fill(JETPT[JN[1]]);
	QPT[j][2]->Fill(BSMPT[BN[0]]+BSMPT[BN[1]]);
	if(MAXDRL > 0){MAXVDHDR[j][0]->Fill(MAXDRL);} 
	if(MAXDRSL > 0){MAXVDHDR[j][1]->Fill(MAXDRSL);}

	NUSEFULDH[j][0]->Fill(PERMVDHN[0].size());
	NUSEFULDH[j][1]->Fill(PERMVDHN[1].size());
        
	if(PERMVDHN[0].size() > 0){for(int q = 0; q < PERMVDHN[0].size();q++){USEFULID[j][0]->Fill(std::abs(BSMID[PERMVDHN[0].at(q)])); VDHPT[j][0]->Fill(BSMPT[PERMVDHN[0].at(q)]);}}
	if(PERMVDHN[1].size() > 0){for(int q = 0; q < PERMVDHN[1].size();q++){USEFULID[j][1]->Fill(std::abs(BSMID[PERMVDHN[1].at(q)])); VDHPT[j][1]->Fill(BSMPT[PERMVDHN[1].at(q)]);}}

	QS[j]->Fill(BSMS[BN[0]]);
	QS[j]->Fill(BSMS[BN[1]]);


        QMATCHES[j][0]->Fill(Q1MATCH);
	QMATCHES[j][1]->Fill(Q2MATCH);

	PTBALPT[j]->Fill(ptbalp);
	PTBALMET[j]->Fill(ptbalm);

	for(int B = 0; B < nbsm ; B++){
	  DMNC[j]->Fill(BSMNC[B]);
	}

	for(int l = 0; l < dmrat.size(); l++){
	  DMRAT[j][0]->Fill(dmrat.at(l));
	}
	for(int l = 0; l < dmrata.size(); l++){
	  DMRAT[j][1]->Fill(dmrata.at(l));
	}

	if(nIDH%2 == 0 || true){
	  NUSEFUL[j]->Fill(nUDH);
	  NVDH[j]->Fill(nVDH);
	  NIDH[j]->Fill(nIDH);
	  U_VRAT[j]->Fill((float)((float)nUDH/(float)nVDH));
	  I_VRAT[j]->Fill((float)((float)nIDH/(float)nVDH));
	  I_ARAT[j]->Fill((float)((float)nIDH/(float)(nIDH+nVDH)));
	  U_ARAT[j]->Fill(1-(float)((float)nUDH/(float)(nIDH+nVDH)));
	}
	QPTRAT[j]->Fill((float)((float)BSMPT[BN[1]]/(float)BSMPT[BN[0]]));

	for(int nc: VDHNCV111){
	  VDHNC[j][0]->Fill(nc);
	}
	for(int nc: VDHNCV113){
	  VDHNC[j][1]->Fill(nc);
	}
	for(int nc: IVDHNCV211){
	  IVDHNC[j][0]->Fill(nc);
	}
	for(int nc: IVDHNCV213){
	  IVDHNC[j][1]->Fill(nc);
	}
	for(int nc: VDHCIV111){
	  VDHCI[j][0]->Fill(nc);
	}
	for(int nc: VDHCIV113){
	  VDHCI[j][1]->Fill(nc);
	}
	if(nZ == 0){
	  nZ0[j]++;
	}

	if(PERMVDHN[0].size() != 0){
	  CATCHRAT[j][0]->Fill((float)catches[0]/(float)PERMVDHN[0].size());
	  CATCHRATJ[j][0]->Fill((float)jcatches[0]/(float)PERMVDHN[0].size());
	  STARTDIST[j][0]->Fill(minr[0]);
	  JETPTCATCH[j][0]->Fill(JETPT[closejets[0]]);
	}
	if(PERMVDHN[1].size() != 0){
	  CATCHRAT[j][1]->Fill((float)catches[1]/(float)PERMVDHN[1].size());
	  CATCHRATJ[j][1]->Fill((float)jcatches[1]/(float)PERMVDHN[1].size());
	  STARTDIST[j][1]->Fill(minr[1]);
	  JETPTCATCH[j][1]->Fill(JETPT[closejets[1]]);
	}

	NMISS[j]->Fill(nmisses);


	float tempdphi1 = 0;
	float tempdphi2 = 0;
	for(int J = 0; J < njets; J++){
	  if(JETMATCH[J] == 1){DPHIMATCH[j][0]->Fill(JETMETDPHI[J]);}
	  if(JETMATCH[J] == 2){DPHIMATCH[j][1]->Fill(JETMETDPHI[J]);}
	  if(Q1MATCH == 1 && Q2MATCH == 1){
	    if(JETMATCH[J] == 1){tempdphi1 = JETMETDPHI[J];}
	    if(JETMATCH[J] == 2){tempdphi2 = JETMETDPHI[J];}
	    if(tempdphi1 != 0 && tempdphi2 != 0){MATCHDPHICORR[j]->Fill(tempdphi1,tempdphi2);}
	  }
	}

	JETPTCORR[j]->Fill(JETPT[JN[0]],JETPT[JN[1]]);

	DPHIJETS[j][0]->Fill(JETMETDPHI[JN[0]]);
	DPHIJETS[j][1]->Fill(JETMETDPHI[JN[1]]);
	DPHIJETS[j][2]->Fill(summetdphi);

	DPHIMIN[j][0]->Fill(JETMETDPHI[JNM[0]]);
	if(JETMETDPHI[JN[0]] < JETMETDPHI[JN[1]]){DPHIMIN[j][1]->Fill(JETMETDPHI[JN[0]]);}
	else{DPHIMIN[j][1]->Fill(JETMETDPHI[JN[1]]);}

	// int N1 = NJTDR[j][0]->GetXaxis()->GetNbins();
	// double binA1[N1+1];
	// for(int BIN = 0; BIN < N1; BIN++){binA1[BIN] = NJETDR[j][0]->GetXaxis()->GetBinLowEdge(BIN+1);}
	// binA1[N1] = drbinr;
	// double wbinA1 = (double)std::abs(binA1[N1] - binA1[N1-1])/(double)2;

	// int N2 = NJETDR[j][1]->GetXaxis()->GetNbins();
	// double binA2[N2+1];
	// for(int BIN = 0; BIN < N2; BIN++){binA2[BIN] = NJETDR[j][1]->GetXaxis()->GetBinLowEdge(BIN+1);}
        // binA2[N2] = drbinr;
	// double wbinA2 = (double)std::abs(binA2[N2] - binA2[N2-1])/(double)2;

	// for(int bn = 0; bn < N1; bn++){
	//   int bincount = 0;
	//   int bincountP[3] = {0,0,0};
	//   for(int J = 0; J < njets; J++){
	//     if(JETBSMDR[J][BN[0]] < binA1[bn+1] && JETPT[J] > ptc){
	//       bincount++;
	//       if(JETPT[J] > ptcuts[0]){bincountP[0]++;}
	//       if(JETPT[J] > ptcuts[1]){bincountP[1]++;}
	//       if(JETPT[J] > ptcuts[2]){bincountP[2]++;}
	//     }
	//   }
	//   NJETDR[j][0]->Fill(binA1[bn],bincount);
	//   if(actualInteractionsPerCrossing < nintcuts[0]){NJETINT[j][0][0]->Fill(binA1[bn],bincount);}
	//   else if(actualInteractionsPerCrossing > nintcuts[0] && actualInteractionsPerCrossing < nintcuts[1]){NJETINT[j][0][1]->Fill(binA1[bn],bincount);}
	//   else if(actualInteractionsPerCrossing > nintcuts[1]){NJETINT[j][0][2]->Fill(binA1[bn],bincount);}
	//   NJETPT[j][0][0]->Fill(binA1[bn],bincountP[0]);
	//   NJETPT[j][0][1]->Fill(binA1[bn],bincountP[1]);
	//   NJETPT[j][0][2]->Fill(binA1[bn],bincountP[2]);
	// }

	// for(int bn = 0; bn < N2; bn++){
	//   int bincount = 0;
	//   int bincountP[3] = {0,0,0};
	//   for(int J = 0; J < njets; J++){
	//     if(JETBSMDR[J][BN[1]] < binA2[bn+1] && JETPT[J] > ptc){
	//       bincount++;
	//       if(JETPT[J] > ptcuts[0]){bincountP[0]++;}
	//       if(JETPT[J] > ptcuts[1]){bincountP[1]++;}
	//       if(JETPT[J] > ptcuts[2]){bincountP[2]++;}
	//     }
	//   }
	//   NJETDR[j][1]->Fill(binA1[bn],bincount);
	//   if(actualInteractionsPerCrossing < nintcuts[0]){NJETINT[j][1][0]->Fill(binA1[bn],bincount);}
	//   else if(actualInteractionsPerCrossing > nintcuts[0] && actualInteractionsPerCrossing < nintcuts[1]){NJETINT[j][1][1]->Fill(binA1[bn],bincount);}
	//   else if(actualInteractionsPerCrossing > nintcuts[1]){NJETINT[j][1][2]->Fill(binA1[bn],bincount);}
	//   NJETPT[j][1][0]->Fill(binA1[bn],bincountP[0]);
	//   NJETPT[j][1][1]->Fill(binA1[bn],bincountP[1]);
	//   NJETPT[j][1][2]->Fill(binA1[bn],bincountP[2]);
	// }



	if(
	   eventpicn < eventpicmax && passes % eventpicd == 0
	   //e == 3042
	   //e == events[eventpicn]
	   ){
	  cout << " -----> EVENT NUMBER " << e << " SAVED" << endl;

	  for(int B = 0; B < nbsm; B++){
	    V[j][eventpicn][0].push_back(BSMPT[B]);
	    V[j][eventpicn][1].push_back(BSMETA[B]);
	    V[j][eventpicn][2].push_back(BSMPHI[B]);
	    V[j][eventpicn][3].push_back(BSME[B]);
	    V[j][eventpicn][4].push_back(BSMS[B]);
	    V[j][eventpicn][5].push_back(BSMID[B]);
	    V[j][eventpicn][6].push_back(BSMUSE[B]);
	    
	  }
	  for(int J = 0; J < njets; J++){
	    if(JETPT[J] > ptc && std::abs(JETETA[J]) < 4.5 && std::abs(JETPHI[J]) < TMath::Pi()){
	      JETV[j][eventpicn][0].push_back(JETPT[J]);
	      JETV[j][eventpicn][1].push_back(JETETA[J]);
	      JETV[j][eventpicn][2].push_back(JETPHI[J]);
	      JETV[j][eventpicn][3].push_back(JETE[J]);
	      JETV[j][eventpicn][4].push_back(JETMATCH[J]);
	    }
	  }
	  for(int J = 0; J < nljets; J++){
	    if(LJETPT[J] > ptlc){
	      LJETV[j][eventpicn][0].push_back(LJETPT[J]);
	      LJETV[j][eventpicn][1].push_back(LJETETA[J]);
	      LJETV[j][eventpicn][2].push_back(LJETPHI[J]);
	      LJETV[j][eventpicn][3].push_back(0);
	      LJETV[j][eventpicn][4].push_back(LJETMATCH[J]);
	    }
	  }
	 
	  
	  EVENTV[j][eventpicn].push_back(e);
	  METV[j][eventpicn].push_back(metFinalTrkPhi);
	  METV[j][eventpicn].push_back(metFinalTrk);
	  LSQV[j][eventpicn][0].push_back(BN[0]);
	  LSQV[j][eventpicn][1].push_back(BN[1]);
	  LSPTSV[j][eventpicn][0].push_back(BSMPT[BN[0]]);
	  LSPTSV[j][eventpicn][0].push_back(BSMPT[BN[1]]);
	  LSPTSV[j][eventpicn][1].push_back(JETPT[JN[0]]);
	  LSPTSV[j][eventpicn][1].push_back(JETPT[JN[1]]);
	  LSPTSV[j][eventpicn][2].push_back(LJETPT[LJN[0]]);
	  LSPTSV[j][eventpicn][2].push_back(LJETPT[LJN[1]]);
	  eventpicn++;
	}

	if(JETMATCH[JN[0]] == 3 && JETMATCH[JN[1]] == 3){matchescut->AddBinContent(1);}
	if((JETMATCH[JN[0]] == 1 || JETMATCH[JN[0]] == 2) && JETMATCH[JN[1]] == 3){matchescut->AddBinContent(2);}
	if((JETMATCH[JN[1]] == 1 || JETMATCH[JN[1]] == 2) && JETMATCH[JN[0]] == 3){matchescut->AddBinContent(3);}
	if(JETMATCH[JN[0]] != 3 && JETMATCH[JN[1]] != 3){matchescut->AddBinContent(4);}
      
      if(JN[0] == JNM[0]){
	if(JETMATCH[JN[0]] != 3){matchesmetcut->AddBinContent(3);}
	else{matchesmetcut->AddBinContent(4);}
      }
      else if(JN[1] == JNM[0]){
	if(JETMATCH[JN[1]] != 3){matchesmetcut->AddBinContent(5);}
	else{matchesmetcut->AddBinContent(6);}
      }
      else if(summetdphi < metdphimin){matchesmetcut->AddBinContent(7);}
      else{
	if(JETMATCH[JNM[0]] != 3){matchesmetcut->AddBinContent(1);}
	else{matchesmetcut->AddBinContent(2);}
      }
	if(PERMVDHN[0].size() == 0 && PERMVDHN[1].size() == 0){vdhnmatch[j]->AddBinContent(0);}
	if(PERMVDHN[0].size() == 0 && PERMVDHN[1].size() > 0){vdhnmatch[j]->AddBinContent(1);}
	if(PERMVDHN[0].size() > 0 && PERMVDHN[1].size() == 0){vdhnmatch[j]->AddBinContent(2);}
	if(PERMVDHN[0].size() > 0 && PERMVDHN[1].size() > 0){vdhnmatch[j]->AddBinContent(3);}
	if((PERMVDHN[0].size() == 0 || PERMVDHN[0].size() == 1) && PERMVDHN[1].size() > 1){vdhnmatch[j]->AddBinContent(4);}
	if(PERMVDHN[0].size() > 1 && (PERMVDHN[1].size() == 0 || PERMVDHN[1].size() == 1)){vdhnmatch[j]->AddBinContent(5);}
	if(PERMVDHN[0].size() > 1 && PERMVDHN[1].size() > 1){vdhnmatch[j]->AddBinContent(6);}
	if((PERMVDHN[0].size() == 0 || PERMVDHN[0].size() == 1) && (PERMVDHN[1].size() == 0 || PERMVDHN[1].size() == 1)){vdhnmatch[j]->AddBinContent(7);}

      }
    }

    // for(int l = 0; l < IDS.size(); l++){
    //   cout << IDS.at(l) << endl;
    // }
    // cout << " --------" << endl;
    // for(int l = 0; l < CIDS.size(); l++){
    //   cout << CIDS.at(l) << endl;
    // }
    
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////


    TH1D *TEMP[2];
    TEMP[0] = (TH1D*)QMATCHES[j][0]->Clone();
    TEMP[0]->Rebin(5040/5);
    TEMP[1] = (TH1D*)QMATCHES[j][1]->Clone();
    TEMP[1]->Rebin(5040/5);

    cout << endl;


    TString MV[4] = {"1500""750"};
    TString RV[4] = {"0.8","0.3"};

    // cout << "NO. Jets matched (\u0394R<" << matchcut <<") to the leading BSM:" << endl;
    // cout << endl;
    // cout << std::setw(20) << std::right << "Signal";
    // cout << std::setw(10) << std::right << "N = 0";
    // cout << std::setw(10) << std::right << "N = 1";
    // cout << std::setw(10) << std::right << "...";
    // cout << endl;
    // cout << std::setw(20) << std::right << ("MZ" + MV[M] + "|r_inv" + RV[r]); 
    // for(int b = 0; b < TEMP[0]->GetXaxis()->GetNbins(); b++){
    //   if(TEMP[0]->GetBinContent(b+1) == 0){break;}
    //   cout << std::setw(10) << std::right << TEMP[0]->GetBinContent(b+1);
    // }
    // cout << endl;
  
    // cout << endl;
    // cout << endl;
    
    // cout << "NO. Jets matched (\u0394R<" << matchcut <<") to the subleading BSM:" << endl;
    // cout << endl;
    // cout << std::setw(20) << std::right << "Signal";
    // cout << std::setw(10) << std::right << "N = 0";
    // cout << std::setw(10) << std::right << "N = 1";
    // cout << std::setw(10) << std::right << "...";
    // cout << endl;
    // cout << std::setw(20) << std::right << ("MZ" + MV[M] + "|r_inv" + RV[r]); 
    // for(int b = 0; b < TEMP[1]->GetXaxis()->GetNbins(); b++){
    //   if(TEMP[1]->GetBinContent(b+1) == 0){break;}
    //   cout << std::setw(10) << std::right << TEMP[1]->GetBinContent(b+1);
    // }
    cout << endl;
    cout << endl;
    cout << "NO. Events: " << nevents[j] << endl;
    cout << "NO. Passes: " << passes << endl;
    cout << endl;
    cout << endl;
  
    float normval = (float)100/(float)matches->GetSumOfWeights();
    normval = 1;
    cout << "Overall Jet Matching Before Applied Cuts:" << endl;
    cout << endl;
    cout << std::setw(20) << std::right << "Matched Jets |";
    cout << std::setw(20) << std::right << "No Jets";
    cout << std::setw(20) << std::right << "Leading Jet";
    cout << std::setw(20) << std::right << "Subleading Jet";
    cout << std::setw(20) << std::right << "Both Jets";
    cout << endl;
    cout << std::setw(20) << std::right << "NO. Matches  |";
    cout << std::setw(20) << std::right << matches->GetBinContent(1)*normval;
    cout << std::setw(20) << std::right << matches->GetBinContent(2)*normval;
    cout << std::setw(20) << std::right << matches->GetBinContent(3)*normval;
    cout << std::setw(20) << std::right << matches->GetBinContent(4)*normval;
    cout << endl;
    cout << endl;
    normval = (float)100/(float)matchescut->GetSumOfWeights();
    normval = 1;
    cout << "Overall Jet Matching After Applied Cuts:" << endl;
    cout << endl;
    cout << std::setw(20) << std::right << "Matched Jets |";
    cout << std::setw(20) << std::right << "No Jets";
    cout << std::setw(20) << std::right << "Leading Jet";
    cout << std::setw(20) << std::right << "Subleading Jet";
    cout << std::setw(20) << std::right << "Both Jets";
    cout << endl;
    cout << std::setw(20) << std::right << "NO. Matches  |";
    cout << std::setw(20) << std::right << matchescut->GetBinContent(1)*normval;
    cout << std::setw(20) << std::right << matchescut->GetBinContent(2)*normval;
    cout << std::setw(20) << std::right << matchescut->GetBinContent(3)*normval;
    cout << std::setw(20) << std::right << matchescut->GetBinContent(4)*normval;
    cout << endl;
    cout << endl;

    normval = (float)100/(float)matchesmet->GetSumOfWeights();
    cout << "Overall Jet||MET Before Applied Cuts:" << endl;
    cout << endl;
    cout << std::setw(20) << std::right << "Jet||MET |";
    cout << std::setw(30) << std::right << "Other Jet";
    cout << std::setw(30) << std::right << "Leading Jet";
    cout << std::setw(30) << std::right << "Subleading Jet";
    cout << std::setw(30) << std::right << "Sum Jet";
    cout << endl;
    cout << std::setw(20) << std::right << "";
    cout << std::setw(15) << std::right << "No Match";
    cout << std::setw(15) << std::right << "Match";
    cout << std::setw(15) << std::right << "No Match";
    cout << std::setw(15) << std::right << "Match";
    cout << std::setw(15) << std::right << "No Match";
    cout << std::setw(15) << std::right << "Match";
    cout << endl;
    cout << std::setw(20) << std::right << "NO. ||MET  |";
    cout << std::setw(15) << std::right << matchesmet->GetBinContent(1)*normval;
    cout << std::setw(15) << std::right << matchesmet->GetBinContent(2)*normval;
    cout << std::setw(15) << std::right << matchesmet->GetBinContent(3)*normval;
    cout << std::setw(15) << std::right << matchesmet->GetBinContent(4)*normval;
    cout << std::setw(15) << std::right << matchesmet->GetBinContent(5)*normval;
    cout << std::setw(15) << std::right << matchesmet->GetBinContent(6)*normval;
    cout << std::setw(30) << std::right << matchesmet->GetBinContent(7)*normval;
    cout << endl;
    cout << endl;
    normval = (float)100/(float)matchesmetcut->GetSumOfWeights();
    cout << "Overall Jet||MET After Applied Cuts:" << endl;
    cout << endl;
    cout << std::setw(20) << std::right << "Jet||MET |";
    cout << std::setw(30) << std::right << "Other Jet";
    cout << std::setw(30) << std::right << "Leading Jet";
    cout << std::setw(30) << std::right << "Subleading Jet";
    cout << std::setw(30) << std::right << "Sum Jet";
    cout << endl;
    cout << std::setw(20) << std::right << "";
    cout << std::setw(15) << std::right << "No Match";
    cout << std::setw(15) << std::right << "Match";
    cout << std::setw(15) << std::right << "No Match";
    cout << std::setw(15) << std::right << "Match";
    cout << std::setw(15) << std::right << "No Match";
    cout << std::setw(15) << std::right << "Match";
    cout << endl;
    cout << std::setw(20) << std::right << "NO. ||MET  |";
    cout << std::setw(15) << std::right << matchesmetcut->GetBinContent(1)*normval;
    cout << std::setw(15) << std::right << matchesmetcut->GetBinContent(2)*normval;
    cout << std::setw(15) << std::right << matchesmetcut->GetBinContent(3)*normval;
    cout << std::setw(15) << std::right << matchesmetcut->GetBinContent(4)*normval;
    cout << std::setw(15) << std::right << matchesmetcut->GetBinContent(5)*normval;
    cout << std::setw(15) << std::right << matchesmetcut->GetBinContent(6)*normval;
    cout << std::setw(30) << std::right << matchesmetcut->GetBinContent(7)*normval;
    cout << endl;
    cout << endl;
    

    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    

    TString opname="Z"+filevarM[M]+"r"+filevarr[r]+".root";
    TFile *f=(TFile*)gROOT->GetListOfFiles()->FindObject(opname);
    if(!f){
      f = new TFile(opname, "RECREATE");
    }

    JPT[j][0]->Write();
    JPT[j][1]->Write();
    QPT[j][0]->Write();
    QPT[j][1]->Write();
    QPT[j][2]->Write();
      
    DMNC[j]->Write();

    for(int l = 0; l < 3; l++){
      QDHDR[j][l][0]->Write();
      QDHDR[j][l][1]->Write();
    }
    
    QS[j]->Write();
    VDHNC[j][0]->Write();
    VDHNC[j][1]->Write();
    IVDHNC[j][0]->Write();
    IVDHNC[j][1]->Write();
    VDHCI[j][0]->Write();
    VDHCI[j][1]->Write();
    
    MAXVDHDR[j][0]->Write();
    MAXVDHDR[j][1]->Write();

    VDHPT[j][0]->Write();
    VDHPT[j][1]->Write();

    NUSEFULDH[j][0]->Write();
    NUSEFULDH[j][1]->Write();

    USEFULID[j][0]->Write();
    USEFULID[j][1]->Write();

    QMATCHES[j][0]->Write();
    QMATCHES[j][1]->Write();

    PTBALPT[j]->Write();
    PTBALMET[j]->Write();

    DMRAT[j][0]->Write();
    DMRAT[j][1]->Write();

    NUSEFUL[j]->Write();
    NVDH[j]->Write();
    NIDH[j]->Write();
    U_VRAT[j]->Write();
    I_VRAT[j]->Write();
    I_ARAT[j]->Write();
    U_ARAT[j]->Write();
    QPTRAT[j]->Write();

    JETPTCORR[j]->Write();
    MATCHDPHICORR[j]->Write();

    NJETDR[j][0]->Write();
    NJETDR[j][1]->Write();

    CATCHRAT[j][0]->Write();
    CATCHRAT[j][1]->Write();

    CATCHRATJ[j][0]->Write();
    CATCHRATJ[j][1]->Write();
      
    STARTDIST[j][0]->Write();
    STARTDIST[j][1]->Write();

    JETPTCATCH[j][0]->Write();
    JETPTCATCH[j][1]->Write();

    NMISS[j]->Write();

    DPHIMATCH[j][0]->Write();
    DPHIMATCH[j][1]->Write();
    
    DPHIJETS[j][0]->Write();
    DPHIJETS[j][1]->Write();
    DPHIJETS[j][2]->Write();

    DPHIMIN[j][0]->Write();
    DPHIMIN[j][1]->Write();

    for(int q  = 0; q < 2; q++){
      for(int y = 0; y < 3; y++){
	NJETINT[j][q][y]->Write();
	NJETPT[j][q][y]->Write();
      }
    }
      
    for(int E = 0; E < eventpicmax; E++){
      for(int v = 0; v < nbsmvars; v++){
	f->WriteObject(&(V[j][E][v]),(const TString)("EVENTVECTORE"+(TString)std::to_string(E)+"BSMV"+VecVars[v]));
      }
      for(int v = 0; v < njetvars; v++){
	f->WriteObject(&(JETV[j][E][v]),(const TString)("EVENTVECTORE"+(TString)std::to_string(E)+"JETV"+JetVecVars[v]));
      }
      for(int v = 0; v < njetvars; v++){
	f->WriteObject(&(LJETV[j][E][v]),(const TString)("EVENTVECTORE"+(TString)std::to_string(E)+"LJETV"+JetVecVars[v]));
      }
      
      f->WriteObject(&(EVENTV[j][E]),(const TString)("EVENTVECTOR"+std::to_string(E)));
      
      f->WriteObject(&(METV[j][E]),(const TString)("EVENTMETVECTOR"+std::to_string(E)));
      
      f->WriteObject(&(LSQV[j][E][0]),(const TString)("EVENTVECTOR"+std::to_string(E)+"LQ"));
      f->WriteObject(&(LSQV[j][E][1]),(const TString)("EVENTVECTOR"+std::to_string(E)+"SLQ"));
      f->WriteObject(&LSPTSV[j][E][0],(const TString)("EVENTVECTOR"+std::to_string(E)+"LSQPT"));
    
      f->WriteObject(&LSPTSV[j][E][1],(const TString)("EVENTVECTOR"+std::to_string(E)+"LSJPT"));

      f->WriteObject(&LSPTSV[j][E][2],(const TString)("EVENTVECTOR"+std::to_string(E)+"LSLJPT"));

    }

    f->Close();

  }

  for(int J = 0; J < nsamples; J++){
    int M = 0;
    int r = 0;
    if(J == 1) r = 1;
    if(J == 2) M = 1;
    if(J == 3){
      M = 1;
      r = 1;
    }
    
    cout << "Z" << filevarM[M] << "r" << filevarr[r] << ":" << endl;
    
    cout << "NO. Visible Dark Hadrons Per Dark Quark:" << endl;
    cout << endl;
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{1} = 0";
    cout << std::setw(20) << std::right << "NVDH_{1} > 0";
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{1} = 0,1";
    cout << std::setw(20) << std::right << "NVDH_{1} > 1";    
    cout << endl;
    cout << std::setw(20) << std::right << "NVDH_{2} = 0";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(0);
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(2);
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{2} = 0,1";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(7);
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(5);
    cout << endl;
    cout << std::setw(20) << std::right << "NVDH_{2} > 0";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(1);
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(3);
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{2} > 1";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(4);
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(6);
    cout << endl;
    cout << endl;    
  }

 for(int J = 0; J < nsamples; J++){
    int M = 0;
    int r = 0;
    if(J == 1) r = 1;
    if(J == 2) M = 1;
    if(J == 3){
      M = 1;
      r = 1;
    }
    
    cout << "Z" << filevarM[M] << "r" << filevarr[r] << ":" << endl;
 
    float norm1val = (float)100/(float)(vdhnmatch[J]->GetBinContent(0)+vdhnmatch[J]->GetBinContent(1)+vdhnmatch[J]->GetBinContent(2)+vdhnmatch[J]->GetBinContent(3));
    float norm2val = (float)100/(float)(vdhnmatch[J]->GetBinContent(7)+vdhnmatch[J]->GetBinContent(6)+vdhnmatch[J]->GetBinContent(5)+vdhnmatch[J]->GetBinContent(4));
    cout << "NO. Visible Dark Hadrons Per Dark Quark (percentage):" << endl;
    cout << endl;
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{1} = 0";
    cout << std::setw(20) << std::right << "NVDH_{1} > 0";
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{1} = 0,1";
    cout << std::setw(20) << std::right << "NVDH_{1} > 1";    
    cout << endl;
    cout << std::setw(20) << std::right << "NVDH_{2} = 0";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(0)*norm1val;
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(2)*norm1val;
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{2} = 0,1";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(7)*norm2val;
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(5)*norm2val;
    cout << endl;
    cout << std::setw(20) << std::right << "NVDH_{2} > 0";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(1)*norm1val;
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(3)*norm1val;
    cout << std::setw(20) << std::right << "";
    cout << std::setw(20) << std::right << "NVDH_{2} > 1";
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(4)*norm2val;
    cout << std::setw(20) << std::right << vdhnmatch[J]->GetBinContent(6)*norm2val;
    cout << endl;
    cout << endl;
}

}
