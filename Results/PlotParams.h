// -------------------------------------------------------------------------------------
struct PlotParams{
	string hist_name, title, label_x;
        int nbins;
	double xmin, xmax;
};
typedef struct PlotParams PlotParams;

// Example:
// PlotParams P_VarName 	= {"VariableName", "Plot Title", "x label [units]", NBINS, XMIN, XMAX };

// Physics Variables

PlotParams P_met_met 			= {"met_met", "Missing E_{T}", "MET [GeV]", 50, 0, 1000};
PlotParams P_met_phi			= {"met_phi", "Missing E_{T} #phi", "#phi [rad]", 50, -3.14, 3.14 };
PlotParams P_TruthMET_TruthSumEt 	= {"MET_TruthMET_TruthSumEt", "TruthMET SumE_{T}", "E [GeV]", 50, 0, 700};  
PlotParams P_TruthMET_TruthPhi	 	= {"MET_TruthMET_TruthPhi", "TruthMET #phi", "#phi [rad]", 50, -3.14, 3.14};  
PlotParams P_n_jets			= {"n_jets", "Number of R=0.4 Jets", "N_{jets}", 20, 0, 20};
PlotParams P_n_fatjets			= {"n_fatjets", "Number of R=1.0 Jets", "N_{fatjets}", 12, 0, 12};

PlotParams P_jet1_pt			= {"jet1_pt", "Leading R=0.4 Jet p_{T}", "p_{T} [GeV]", 70, 0, 3500};
PlotParams P_jet1_eta			= {"jet1_eta", "Leading R=0.4 Jet Eta", "#eta", 50, -5.0, 5.0};
PlotParams P_jet1_phi			= {"jet1_phi", "Leading R=0.4 Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet1_E			= {"jet1_E", "Leading R=0.4 Jet E", "Energy [GeV]", 50, 0, 3000};
PlotParams P_jet2_pt			= {"jet2_pt", "Subleading R=0.4 Jet p_{T}", "p_{T} [GeV]", 70, 0, 1500};
PlotParams P_jet2_eta			= {"jet2_eta", "Subleading R=0.4 Jet Eta", "#eta", 50, -5.0, 5.0};
PlotParams P_jet2_phi			= {"jet2_phi", "Subleading R=0.4 Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet2_E			= {"jet2_E", "Subleading R=0.4 Jet E", "Energy [GeV]", 50, 0, 300};
PlotParams P_fabs_jet1_eta		= {"fabs(jet1_eta)", "Leading R=0.4 Jet |Eta|", "|#eta|", 50, 0, 3.0};
PlotParams P_fabs_jet2_eta		= {"fabs(jet2_eta)", "Subleading R=0.4 Jet |Eta|", "|#eta|", 50, 0, 3.0};

PlotParams P_fatjet1_pt			= {"fatjet1_pt", "Leading R=1.0 Jet p_{T}", "p_{T} [GeV]", 70, 0, 3500};
PlotParams P_fatjet1_eta		= {"fatjet1_eta", "Leading R=1.0 Jet Eta", "#eta", 50, -5.0, 5.0};
PlotParams P_fatjet1_phi		= {"fatjet1_phi", "Leading R=1.0 Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_fatjet1_m			= {"fatjet1_m", "Leading R=1.0 Jet Mass", "Mass [GeV]", 50, 0, 3000};
PlotParams P_fatjet1_C2			= {"fatjet1_C2", "Leading R=1.0 Jet C2", "C2", 50, 0, 1};
PlotParams P_fatjet1_D2			= {"fatjet1_D2", "Leading R=1.0 Jet D2", "D2", 50, 0, 10};
PlotParams P_fatjet1_Split12		= {"fatjet1_Split12", "Leading R=1.0 Jet Split 12", "Split12", 50, 0, 150};
PlotParams P_fatjet1_Split23		= {"fatjet1_Split23", "Leading R=1.0 Jet Split 23", "Split23", 50, 0, 200};
PlotParams P_fatjet1_tau23		= {"fatjet1_tau32", "Leading R=1.0 Jet N-subjettiness", "N-subjettiness", 50, 0, 200};
PlotParams P_fatjet2_pt			= {"fatjet2_pt", "Subleading R=1.0 Jet p_{T}", "p_{T} [GeV]", 70, 0, 3500};
PlotParams P_fatjet2_eta		= {"fatjet2_eta", "Subleading R=1.0 Jet Eta", "#eta", 50, -5.0, 5.0};
PlotParams P_fatjet2_phi		= {"fatjet2_phi", "Subleading R=1.0 Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_fatjet2_m			= {"fatjet2_m", "Subleading R=1.0 Jet Mass", "Mass [GeV]", 50, 0, 3000};
PlotParams P_fatjet2_mT			= {"fatjet2_mT", "Subleading R=1.0 Jet MT", "Mass [GeV]", 50, 0, 2000};
PlotParams P_fatjet2_C2			= {"fatjet2_C2", "Subleading R=1.0 Jet C2", "C2", 50, 0, 1};
PlotParams P_fatjet2_D2			= {"fatjet2_D2", "Subleading R=1.0 Jet D2", "D2", 50, 0, 10};
PlotParams P_fatjet2_Split12		= {"fatjet2_Split12", "Subleading R=1.0 Jet Split 12", "Split12", 50, 0, 500};
PlotParams P_fatjet2_Split23		= {"fatjet2_Split23", "Subleading R=1.0 Jet Split 23", "Split23", 50, 0, 200};
PlotParams P_fatjet2_tau23		= {"fatjet2_tau32", "Subleading R=1.0 Jet N-subjettiness", "N-subjettiness", 50, 0, 200};

PlotParams P_jet_svj_pt			= {"jet_svj_pt", "Semi-visible Jet p_{T}", "p_{T} [GeV]", 50, 0, 1000};
PlotParams P_jet_svj_eta		= {"jet_svj_eta", "Semi-visible Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams P_jet_svj_phi		= {"jet_svj_phi", "Semi-visible Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet_svj_m			= {"jet_svj_m", "Semi-visible Jet Mass", "M [GeV]", 50, 0, 300};
PlotParams P_jet_asvj_pt		= {"jet_asvj_pt", "Anti Semi-visible Jet p_{T}", "p_{T} [GeV]", 50, 0, 1000};
PlotParams P_jet_asvj_eta		= {"jet_asvj_eta", "Anti Semi-visible Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams P_jet_asvj_phi		= {"jet_asvj_phi", "Anti Semi-visible Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet_asvj_m			= {"jet_asvj_m", "Anti Semi-visible Jet Mass", "M [GeV]", 50, 0, 300};

PlotParams P_maxphi_minphi		= {"maxphi_minphi", "max#phi - min#phi", "max#phi - min#phi", 50, 0, 3.14};
PlotParams P_pt_balance_12	 	= {"pt_balance_12", "p_{T} balance leading-subleading", "pt balance", 50, 0.0, 1.0};
PlotParams P_pt_balance_sa		= {"pt_balance_sa", "p_{T} balance svj-antisvj", "pt balance", 50, 0, 1};
PlotParams P_dphi_max			= {"dphi_max", "#Delta#phi (furthest jet, MET)", "#Delta#phi", 50, 0, 3.14};
PlotParams P_dphi_min			= {"dphi_min", "#Delta#phi (closest jet, MET)", "#Delta#phi", 50, 0, 3.14};
PlotParams P_dphi_min_MET		= {"dphi_min_MET", "#Delta#phi (closest jet, MET) / MET", "#Delta#phi/MET", 50, 0, 0.5};
PlotParams P_dphi_MET_j1j2		= {"dphi_MET_j1j2", "#Delta#phi (MET, -j1-j2)", "#Delta#phi", 50, 0, 3.14};
PlotParams P_deltaY_12			= {"deltaY_12", "#Delta Y (leading jet, subleading jet)", "#Delta Y", 50, 0, 5};
PlotParams P_mjj_12			= {"mjj_12", "Invariant Mass R=0.4 Jets (Leading, Subleading)", "m_{jj} [GeV]", 80, 500, 6500};
PlotParams P_mJJ_12			= {"mJJ_12", "Invariant Mass R=1.0 Jets (Leading, Subleading)", "m_{JJ} [GeV]", 100, 0, 3000};
PlotParams P_mT_jj			= {"mT_jj", "mT System", "mT [GeV]", 80, 500, 6500};
PlotParams P_mT_jj_neg			= {"mT_jj_neg", "mT(j1,j2,-(j1+j2))", "mT Neg [GeV]", 80, 500, 6000};
PlotParams P_met_jj_neg 		= {"met_jj_neg", "-j1-j2", "MET Approx [GeV]", 80, 400, 3000};
PlotParams P_mT_JJ			= {"mT_JJ", "mT System (R=1.0)", "mT [GeV]", 150, 0, 10000};
PlotParams P_deta_12			= {"deta_12", "#Delta#eta (leading, subleading jet)", "#Delta#eta", 50, 0, 10};
PlotParams P_dR_12			= {"dR_12", "#Delta R (leading, subleading jet)", "#Delta R", 50, 0, 10};
PlotParams P_rT			 	= {"rT", "MET/mT", "RT", 50, 0, 1.5};
PlotParams P_hT				= {"hT", "Jet pT Sum", "HT [GeV]", 50, 0, 2500};
PlotParams P_hT_r04			= {"hT_r04", "Small-R Jet pT Sum", "HT [GeV]", 100, 0, 3000};

PlotParams P_aplanarity			= {"aplanarity", "Aplanarity", "aplanarity", 50, 0, 0.5};
PlotParams P_sphericity			= {"sphericity", "Sphericity", "sphericity", 50, 0, 1.0};
PlotParams P_sphericity_T		= {"sphericity_T", "Transverse Sphericity", "sphericity_T", 50, 0, 1.0};

// Overlayed Plots
PlotParams OP_jet_pt			= {"jet_pt", "Jet Pt", "p_{T} [GeV]", 50, 0, 1000};
PlotParams OP_jet_eta			= {"jet_eta", "Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams OP_jet_phi			= {"jet_phi", "Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams OP_jet_m			= {"jet_m", "Jet M", "M [GeV]", 50, 0, 1000};
PlotParams OP_met_neg			= {"met_neg", "MET and Neg MET", "MET [GeV]", 50, 0, 1000};
PlotParams OP_mT_neg			= {"mT_neg", "mT and Neg mT", "mT [GeV]", 50, 500, 3000};

