#include <cmath>
#include <algorithm>

#include "project_Hv2.h"


#include <sstream>
#include <string>
#include <iostream>

template <typename Type> std::string to_str(const Type & t) // Used for converting floats to strings without the annoying .00000000
{
  std::ostringstream os;
  os << t;
  return os.str ();
}


TString datadirmain = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/"; // Strings for accessing the ntuples
TString datadirsub = "v1.0/";
TString filename1 = "user.ebusch.5085";
TString filename2 = ".MGPy8EG_SVJSChan_";
TString filevarM[2] = {"1500", "750"};
TString filevarr[2] = {"8", "3"};
TString filename3 = "_tree.root";
TString mcs[3] = {".mc16a", ".mc16d", ".mc16e"};
TString fileN[4] = {"47", "48", "49", "50"};
TString ndN[12] = {"3733", "3907", "3996", "3741", "3916", "4007", "3753", "3924", "4015", "3764", "3929", "4025"};

int COLOR[4] = {810,860,800,870}; // The Colours of the 4 signal points

TString multijetdir = "user.ebusch.364702.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ2WithSW."; // More location stuff but for multijet bkgrd
TString multijetndN[3] = {"198","165","147"};
TString multiNO[3] = {"22","04","10"};
TString fileN1[3] = {"98","65","47"};
TString fileN2[3] = {"22","04","10"};


TString tree_entry = "outTree/nominal";

    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////           Different Variables For Later Use             ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////

int nsamples = 4;

double matchcut = DRCUT; // The matching criteria for jets with dark quarks

int ptc = PTMIN;     // The small R jet minimum pt
int ptlc = PTLMIN;   // The large R jet minimum pt

int nintcuts[2] = {20, 40};      // The region edges for the interactions per bunch crossing plots
int ptcuts[3] = {PTMIN,70,100};  // The region edges for the average jets close to dark quark at diff pt

int nbins = 5040; // number of bins for each histogram

    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                Start Main Body Of Code                  ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////

void project_Pv3(){  


  gInterpreter->GenerateDictionary("vector<vector<int> >", "vector");

    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                    Defines Histograms                   ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////

    TH1D* JETPT[nsamples][2]; // 0 -> Leading | 1 -> Subleading
    TH2D* JETPT2D[nsamples];
    TH1D* DQPT[nsamples][2]; // 0 -> Leading | 1 -> Subleading
    TH2D* DQPT2D[nsamples];
    TH1D* DRJJ[nsamples];
    TH1D* DRQQ[nsamples];
    TH2D* JETMATCHDR[nsamples];
    TH2D* JETMATCHINT[nsamples];
    TH2D* JETMATCHPT[nsamples];

    TH1D* MAXDR[nsamples][2]; // 0 -> Leading Quark | 1 -> Subleading Quark
    TH1D* NVIS[nsamples];
    TH1D* NINV[nsamples];
    TH1D* NSTAB[nsamples];
    TH1D* NUNST[nsamples];
    TH1D* VISUNSTRAT[nsamples];
    TH1D* UNSTINVRAT[nsamples];
    TH1D* STABTOTRAT[nsamples];
    TH1D* INVTOTRAT[nsamples];
    
    TH1D* VDHPT[nsamples][2];        // 0 -> Leading Quark | 1 -> Subleading Quark
    TH1D* DPHIMATCHMET[nsamples][2]; // 0 -> Leading Quark | 1 -> Subleading Quark
    TH2D* DPHIMATCHMET2D[nsamples];   
    TH1D* DPHIJETMET[nsamples][3];   // 0 -> Leading Jet | 1 -> Subleading Jet | 2 -> Sum jet
    TH1D* MINDPHIMET[nsamples];
    TH1D* MAXDPHIMET[nsamples];

    TH1D* MTJETSMET[nsamples][2]; // 0 -> Aligned Jet + Anti-Aligned Jet + MET | 1 -> All Matched Jets + MET

    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                 Signal Grid Loop &                      ////
    ////                   ntuple access                         ////
    /////////////////////////////////////////////////////////////////


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
    
    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                 Gets Variable Adresses                  ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////


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
    chain->SetBranchAddress("na4_pflowjets",&na4_pflowjets);

    vector<float> *a4_pflowjets_pt = nullptr;
    chain->SetBranchAddress("a4_pflowjets_pt",&a4_pflowjets_pt);

    vector<float> *a4_pflowjets_eta = nullptr;
    chain->SetBranchAddress("a4_pflowjets_eta",&a4_pflowjets_eta);

    vector<float> *a4_pflowjets_phi = nullptr;
    chain->SetBranchAddress("a4_pflowjets_phi",&a4_pflowjets_phi);

    vector<float> *a4_pflowjets_E = nullptr;
    chain->SetBranchAddress("a4_pflowjets_E",&a4_pflowjets_E);

    int na10_lctopojets[22];
    chain->SetBranchAddress("na10_lctopojets",&na10_lctopojets);

    vector<float> *a10_lctopojets_pt = nullptr;
    chain->SetBranchAddress("a10_lctopojets_pt",&a10_lctopojets_pt);

    vector<float> *a10_lctopojets_eta = nullptr;
    chain->SetBranchAddress("a10_lctopojets_eta",&a10_lctopojets_eta);

    vector<float> *a10_lctopojets_phi = nullptr;
    chain->SetBranchAddress("a10_lctopojets_phi",&a10_lctopojets_phi);
    
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

    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                    Create Histograms                    ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////



    JETPT[j][0] = new TH1D((const TString)("JETPT0"+to_str(j)),"Leading Jet p_{T} [GeV]",nbins,0,1000);
    JETPT[j][1] = new TH1D((const TString)("JETPT1"+to_str(j)),"Subleading Jet p_{T} [GeV]",nbins,0,700);
    JETPT2D[j] = new TH2D((const TString)("JETPT2D"+to_str(j)),"Leading Jet p_{T} VS Subleading Jet p_{T}",nbins,0,1000,nbins,0,700);
    DQPT[j][0] = new TH1D((const TString)("DQPT0"+to_str(j)),"Leading Dark Quark p_{T} [GeV]",nbins,0,1200);
    DQPT[j][1] = new TH1D((const TString)("DQPT1"+to_str(j)),"Subleading Dark Quark p_{T} [GeV]",nbins,0,1000);
    DQPT2D[j] = new TH2D((const TString)("DQPT2D"+to_str(j)),"Leading Dark Quark p_{T} VS SUbleading Dark Quaark p_{T}",nbins,0,1200,nbins,0,1000);
    DRJJ[j] = new TH1D((const TString)("DRJJ"+to_str(j)),"DR(Leading Jet, Subleading Jet)",nbins,0,6);   
    DRQQ[j] = new TH1D((const TString)("DRQQ"+to_str(j)),"DR9Leading Dark Quark, Subleading Dark Quark)",nbins,0,6);
    JETMATCHDR[j] = new TH2D((const TString)("JETMATCHDR"+to_str(j)),"Average NO. Jets With DR(J,\\chi) < X",nbins,0,6,nbins,0,6);
    // JETMATCHINT[j] = new TH2D((const TString)("JETMATCHINT"+to_str(j)),"",nbins,,,nbins,,);
    // JETMATCHPT[j] = new TH2D((const TString)("JETMATCHPT"+to_str(j)),"",nbins,,,nbins,,);

    MAXDR[j][0] = new TH1D((const TString)("MAXDR0"+to_str(j)),"Max DR(VDH_{i}, VDH_{j}) From Leading Dark Quark",nbins,0,3);
    MAXDR[j][1] = new TH1D((const TString)("MAXDR1"+to_str(j)),"Max DR(VDH_{i}, VDH_{j}) From Subleading Dark Quark",nbins,0,3);
    NVIS[j] = new TH1D((const TString)("NVIS"+to_str(j)),"NO. Visible Dark Hadrons",nbins,0,10);
    NINV[j] = new TH1D((const TString)("NINV"+to_str(j)),"NO. Invisible Dark Hadrons",nbins,0,20);
    NSTAB[j] = new TH1D((const TString)("NSTAB"+to_str(j)),"NO. Stable Dark Hadrons",nbins,0,18);
    NUNST[j] = new TH1D((const TString)("NUNST"+to_str(j)),"NO. Unstable Dark Hadrons",nbins,0,18);
    VISUNSTRAT[j] = new TH1D((const TString)("VISUNSTRAT"+to_str(j)),"Fraction Of Unstable Dark AHdrons Which Are Visible",nbins,0,1);
    UNSTINVRAT[j] = new TH1D((const TString)("UNSTINVRAT"+to_str(j)),"Fraction Of Invisible Dark Hadrons Which Are Unstable",nbins,0,1);
    STABTOTRAT[j] = new TH1D((const TString)("STABTOTRAT"+to_str(j)),"Fraction Of Total Dark Hadrons Which Are Stable",nbins,0,1);
    INVTOTRAT[j] = new TH1D((const TString)("INVTOTRAT"+to_str(j)),"Fraction Of Total Dark Hadrons Which Are Invisible",nbins,0,1);

    VDHPT[j][0] = new TH1D((const TString)("VDHPT0"+to_str(j)),"Visible Dark Hadron p_{T} From The Leading Dark Quark [GeV]",nbins,0,1000);
    VDHPT[j][1] = new TH1D((const TString)("VDHPT1"+to_str(j)),"Visible Dark Hadron p_{T} From The Subleading Dark Quark [GeV]",nbins,0,1000);
    DPHIMATCHMET[j][0] = new TH1D((const TString)("DPHIMATCHMET0"+to_str(j)),"DPhi(Matched Jet, MET) From Leading Dark Quark",nbins,0,TMath::Pi());
    DPHIMATCHMET[j][1] = new TH1D((const TString)("DPHIMATCHMET1"+to_str(j)),"DPhi(Matched Jet, MET) From Subleading Dark Quark",nbins,0,TMath::Pi());
    DPHIMATCHMET2D[j] = new TH2D((const TString)("DPHIMATCHMET2D"+to_str(j)),"DPhi(Matched Jet, MET), Leading Dark Quark VS Subleading Dark Quark",nbins,0,TMath::Pi(),nbins,0,TMath::Pi());
    DPHIJETMET[j][0] = new TH1D((const TString)("DPHIJETMET0"+to_str(j)),"DPhi(Leading Jet, MET)",nbins,0,TMath::Pi());
    DPHIJETMET[j][1] = new TH1D((const TString)("DPHIJETMET1"+to_str(j)),"DPhi(Subleading Jet, MET)",nbins,0,TMath::Pi());
    DPHIJETMET[j][2] = new TH1D((const TString)("DPHIJETMET2"+to_str(j)),"DPhi(Sum Jet, MET)",nbins,0,TMath::Pi());
    MINDPHIMET[j] = new TH1D((const TString)("MINDPHIMET"+to_str(j)),"Minimum DPhi(Jet, MET) For All Jets",nbins,0,TMath::Pi());
    MAXDPHIMET[j] = new TH1D((const TString)("MAXDPHIMET"+to_str(j)),"Maximum Dphi(Jet, MET) For All Jets",nbins,0,TMath::Pi());
    
    MTJETSMET[j][0] = new TH1D((const TString)("MTJETSMET0"+to_str(j)),"Transverse Mass Of Aligned Jet + Anti-Aligned Jet + MET",nbins,0,2000);
    MTJETSMET[j][1] = new TH1D((const TString)("MTJETSMET1"+to_str(j)),"Transverse Mass Of All Matched Jets + MET",nbins,0,2000);
    


    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                        Event Loop                       ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////


    int passes = 0;
    int nout = 0;

    for(int e = 0; e < chain->GetEntries(); e++){

      chain->GetEntry(e); // Gets the event

      int nbsm = ntruthBSM[0];       // Number of each type of object
      int njets = na4_pflowjets[0];

      TLorentzVector TEMP(0,0,0,0); // Temp lorentz vector for use during object loops


                                                             /////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////                MET Vector                  ///////////////////////////////////////////////////////////
                                                             /////////////////////////////////////////////////////

      TLorentzVector MET(0,0,0,0);
      MET.SetPtEtaPhiM(metFinalTrk,0,metFinalTrkPhi,0);
      MET.SetPz(0);
      MET.SetE(MET.Pt());

                                                             /////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////                  BSM Loop                   ///////////////////////////////////////////////////////////
                                                             /////////////////////////////////////////////////////
 
     vector <TLorentzVector> Quarks;
      vector <TLorentzVector> VisHadrons;
      vector <TLorentzVector> InvHadrons;
      vector <TLorentzVector> StabHadrons;
      vector <TLorentzVector> UnstHadrons;
      Quarks.clear();
      VisHadrons.clear();
      StabHadrons.clear();
      UnstHadrons.clear();

      for(int B = 0; B < nbsm; B++){ // BSM main loop
	
	TEMP.SetPtEtaPhiE(truthBSM_pt->at(B),truthBSM_eta->at(B),truthBSM_phi->at(B),truthBSM_e->at(B));

	int absid = std::abs(truthBSM_pdgId->at(B));

	if(absid == 5000001){;}                               // Z'
	if(absid == 4900101 && truthBSM_status->at(B) == 23){ // Dark Quark
	  Quarks.push_back(TEMP);
	} 
	if(absid == 4900111 || absid == 4900113){             // Unstable Dark Hadron
	  bool vis = false;
	  for(int C = 0; C < truthBSM_nChildren->at(B); C++){
	    int childID = std::abs(truthBSM_child_pdgId->at(B).at(C));
	    if(childID < 50 || (childID > 53 && childID < 4900000)){vis = true;} // Chekcs if any of the children are SM -> Visible Hadron
	  }
	  if(vis){VisHadrons.push_back(TEMP);}
	  else{InvHadrons.push_back(TEMP);}
	  UnstHadrons.push_back(TEMP);
	} 
	if(absid == 4900211 || absid == 4900213){             // Stable Dark Hadron
	  InvHadrons.push_back(TEMP);
	  StabHadrons.push_back(TEMP);
	} 

      }
 
      if(Quarks.size() == 2){
	if(Quarks.at(0).Pt() < Quarks.at(1).Pt()){ // Orders the dark quarks in decreasing pt order
	  Quarks.push_back(Quarks.at(0));
	  Quarks.erase(Quarks.begin());
	}
      }

      double maxdrvdh[2] = {0,0}; // Calculating the max DR between the visible dark hadrons from each dark quark
      
      if(Quarks.size() == 2){
	for(TLorentzVector v1 : VisHadrons){
	  if(Quarks.at(0).DeltaR(v1) < Quarks.at(1).DeltaR(v1)){
	    for(TLorentzVector v2 : VisHadrons){
	      if(Quarks.at(0).DeltaR(v2) < Quarks.at(1).DeltaR(v2) && v1.DeltaR(v2) > maxdrvdh[0]){
		maxdrvdh[0] = v1.DeltaR(v2);
	      }
	    }	  
	  }
	  else{
	    for(TLorentzVector v2 : VisHadrons){
	      if(Quarks.at(0).DeltaR(v2) > Quarks.at(1).DeltaR(v2) && v1.DeltaR(v2) > maxdrvdh[1]){
		maxdrvdh[1] = v1.DeltaR(v2);
	      }
	    }	  
	  }
	}
      }
                                                             /////////////////////////////////////////////////////
      ///////////////////////////////////////////////////////////             Small R Jet Loop                ///////////////////////////////////////////////////////////
                                                             /////////////////////////////////////////////////////
      vector <TLorentzVector> Jets;
      vector <TLorentzVector> LeadQuarkMatches;
      vector <TLorentzVector> SubQuarkMatches;

      Jets.clear();
      LeadQuarkMatches.clear();
      SubQuarkMatches.clear();

      TLorentzVector MinPhiV(0,0,0,0);
      TLorentzVector MaxPhiV(0,0,0,0);
	
      double mindphi = TMath::Pi();
      double maxdphi = 0;
      for(int J = 0; J < njets; J++){
        
	TEMP.SetPtEtaPhiE(a4_pflowjets_pt->at(J),a4_pflowjets_eta->at(J),a4_pflowjets_phi->at(J),a4_pflowjets_E->at(J));
	
	if(TEMP.Pt() > ptc){
	  if(TEMP.DeltaPhi(MET) < mindphi){mindphi = TEMP.DeltaPhi(MET); MinPhiV = TEMP;}
	  if(TEMP.DeltaPhi(MET) > maxdphi){maxdphi = TEMP.DeltaPhi(MET); MaxPhiV = TEMP;}
	  if(Quarks.size() == 2){
	    if(Quarks.at(0).DeltaR(TEMP) < matchcut && Quarks.at(0).DeltaR(TEMP) < Quarks.at(1).DeltaR(TEMP)){LeadQuarkMatches.push_back(TEMP);}
	    else if(Quarks.at(1).DeltaR(TEMP) < matchcut){SubQuarkMatches.push_back(TEMP);}
	  }
	  Jets.push_back(TEMP);
	}

      }

      double jetsumphi = 0;
      double jetsummetdphi = 0;
      double mt[2] = {0,0};

      if(Jets.size() >= 2){
	jetsumphi += Jets.at(0).Phi();
	jetsumphi += Jets.at(1).Phi();
	if(jetsumphi > TMath::Pi()){jetsumphi -= 2*TMath::Pi();}
	else if(jetsumphi < -TMath::Pi()){jetsumphi += 2*TMath::Pi();}
	jetsummetdphi = std::abs(jetsumphi - MET.Phi());
	if(jetsummetdphi > TMath::Pi()){jetsummetdphi -= 2*TMath::Pi();}
	
      
	TEMP.SetPtEtaPhiE(0,0,0,0); // Calculates MT JJ+MET (A + AA)
	TEMP += MaxPhiV;
	TEMP += MinPhiV;
	TEMP += MET;
	mt[0] = TEMP.Mt();

	TEMP.SetPtEtaPhiE(0,0,0,0); // Calculates MT JJ+MET (All Matched Jets)
	TEMP += MET;
	for(TLorentzVector v : LeadQuarkMatches){
	  TEMP += v;
	}
	for(TLorentzVector v : SubQuarkMatches){
	  TEMP += v;
	}
	mt[1] = TEMP.Mt();
      }
    
    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                         Cut Tests                       ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////

      int TEST = -1; // If this stays as -1 then the cuts are passed


      //if(!() && TEST == -1){TEST = 1;}    <-- Template cut for copy pasting

      if(!(Quarks.size() == 2) && TEST == -1){TEST = 1;} // New test value can be used to produce a cutflow histogram
      if(!(Jets.size() >= 2) && TEST == -1){TEST = 1;}
      if(!(metFinalTrk > 200) && TEST == -1){TEST = 1;}

      // if(TEST == -1){
      // 	if(!(Jets.at(0).Pt() > 33) && TEST == -1){TEST = 1;}
      // 	if(!(Jets.at(1).Pt() > 33) && TEST == -1){TEST = 1;}

      // 	if(!(Jets.at(0).Pt() < 66) && TEST == -1){TEST = 1;}
      // 	if(!(Jets.at(1).Pt() < 66) && TEST == -1){TEST = 1;}
      // }

      if(TEST == -1){    //Succesfully passed cuts
	passes++;
	if(passes%17 == 0 && nout < 5){
	  nout++;
	  cout << "----->> Event " << e << " Passed" << endl;
	}
    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                      Fill Histograms                    ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////
 
        JETPT[j][0]->Fill(Jets.at(0).Pt());
	JETPT[j][1]->Fill(Jets.at(1).Pt());
	JETPT2D[j]->Fill(Jets.at(0).Pt(),Jets.at(1).Pt());
	DQPT[j][0]->Fill(Quarks.at(0).Pt());
	DQPT[j][1]->Fill(Quarks.at(1).Pt());
	DQPT2D[j]->Fill(Quarks.at(0).Pt(),Quarks.at(1).Pt());
	DRJJ[j]->Fill(Jets.at(0).DeltaR(Jets.at(1)));
	DRQQ[j]->Fill(Quarks.at(0).DeltaR(Quarks.at(1)));
	//	JETMATCHDR[j]->Fill();
        if(maxdrvdh[0] > 0){MAXDR[j][0]->Fill(maxdrvdh[0]);}
	if(maxdrvdh[1] > 0){MAXDR[j][1]->Fill(maxdrvdh[1]);}
	NVIS[j]->Fill(VisHadrons.size());
	NINV[j]->Fill(InvHadrons.size());
	NSTAB[j]->Fill(StabHadrons.size());
	NUNST[j]->Fill(UnstHadrons.size());
	VISUNSTRAT[j]->Fill((double)VisHadrons.size()/(double)UnstHadrons.size());
	UNSTINVRAT[j]->Fill((double)UnstHadrons.size()/(double)InvHadrons.size());
	STABTOTRAT[j]->Fill((double)StabHadrons.size()/(double)(StabHadrons.size()+UnstHadrons.size()));
	INVTOTRAT[j]->Fill((double)InvHadrons.size()/(double)(StabHadrons.size()+UnstHadrons.size()));

	for(TLorentzVector v : VisHadrons){
	  if(Quarks.at(0).DeltaR(v) < Quarks.at(1).DeltaR(v)){VDHPT[j][0]->Fill(v.Pt());}
	  else{VDHPT[j][1]->Fill(v.Pt());}
	}
	for(TLorentzVector m : LeadQuarkMatches){
	  DPHIMATCHMET[j][0]->Fill(m.DeltaPhi(MET));
	}
	for(TLorentzVector m : SubQuarkMatches){
	  DPHIMATCHMET[j][1]->Fill(m.DeltaPhi(MET));
	}
	if(LeadQuarkMatches.size() == 1 && SubQuarkMatches.size() == 1){
	  DPHIMATCHMET2D[j]->Fill(LeadQuarkMatches.at(0).DeltaPhi(MET), SubQuarkMatches.at(0).DeltaPhi(MET));
	}
	DPHIJETMET[j][0]->Fill(Jets.at(0).DeltaPhi(MET));
	DPHIJETMET[j][1]->Fill(Jets.at(1).DeltaPhi(MET));
	DPHIJETMET[j][2]->Fill(jetsummetdphi);
	MINDPHIMET[j]->Fill(mindphi);
	MAXDPHIMET[j]->Fill(maxdphi);

	MTJETSMET[j][0]->Fill(mt[0]);
	MTJETSMET[j][1]->Fill(mt[1]);

      }
    }
    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                     Write Histograms                    ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////


    TString opname="Z"+filevarM[M]+"r"+filevarr[r]+".root";
    TFile *f=(TFile*)gROOT->GetListOfFiles()->FindObject(opname);
    if(!f){
      f = new TFile(opname, "RECREATE");
    }    


    JETPT[j][0]->Write();
    JETPT[j][1]->Write();
    JETPT2D[j]->Write();
    DQPT[j][0]->Write();
    DQPT[j][1]->Write();
    DQPT2D[j]->Write();
    DRJJ[j]->Write();
    DRQQ[j]->Write();
    JETMATCHDR[j]->Write();

    MAXDR[j][0]->Write();
    MAXDR[j][1]->Write();
    NVIS[j]->Write();
    NINV[j]->Write();
    NSTAB[j]->Write();
    NUNST[j]->Write();
    VISUNSTRAT[j]->Write();
    UNSTINVRAT[j]->Write();
    STABTOTRAT[j]->Write();
    INVTOTRAT[j]->Write();

    VDHPT[j][0]->Write();
    VDHPT[j][1]->Write();
    DPHIMATCHMET[j][0]->Write();
    DPHIMATCHMET[j][1]->Write();
    DPHIMATCHMET2D[j]->Write();
    DPHIJETMET[j][0]->Write();
    DPHIJETMET[j][1]->Write();
    DPHIJETMET[j][2]->Write();
    MINDPHIMET[j]->Write();
    MAXDPHIMET[j]->Write();

    MTJETSMET[j][0]->Write();
    MTJETSMET[j][1]->Write();

    /////////////////////////////////////////////////////////////////
    ////                                                         ////
    ////                    Output Numbers                       ////
    ////                                                         ////
    /////////////////////////////////////////////////////////////////


  }
}
