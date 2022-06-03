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

PlotParams P_met_met 			= {"met_met", "Missing E_{T}", "MET [GeV]", 50, 0., 700*1e3};
PlotParams P_met_phi			= {"met_phi", "Missing E_{T} #phi", "#phi [rad]", 50, -3.14, 3.14 };
PlotParams P_TruthMET_TruthSumEt 	= {"MET_TruthMET_TruthSumEt", "TruthMET SumE_{T}", "E [GeV]", 50, 0, 700};  
PlotParams P_TruthMET_TruthPhi	 	= {"MET_TruthMET_TruthPhi", "TruthMET #phi", "#phi [rad]", 50, -3.14, 3.14};  
PlotParams P_n_jets			= {"n_jets", "Number of Jets", "N_{jets}", 20, 0, 20};

PlotParams P_jet1_pt			= {"jet1_pt", "Leading Jet p_{T}", "p_{T} [GeV]", 50, 0, 1000};
PlotParams P_jet1_eta			= {"jet1_eta", "Leading Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams P_jet1_phi			= {"jet1_phi", "Leading Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet1_m			= {"jet1_m", "Leading Jet M", "Mass [GeV]", 50, 0, 300};
PlotParams P_jet2_pt			= {"jet2_pt", "Subleading Jet p_{T}", "p_{T} [GeV]", 50, 0, 1000};
PlotParams P_jet2_eta			= {"jet2_eta", "Subleading Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams P_jet2_phi			= {"jet2_phi", "Subleading Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet2_m			= {"jet2_m", "Subleading Jet M", "Mass [GeV]", 50, 0, 300};
PlotParams P_jet_svj_pt			= {"jet_svj_pt", "Semi-visible Jet p_{T}", "p_{T} [GeV]", 50, 0, 1000};
PlotParams P_jet_svj_eta		= {"jet_svj_eta", "Semi-visible Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams P_jet_svj_phi		= {"jet_svj_phi", "Semi-visible Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet_svj_m			= {"jet_svj_m", "Semi-visible Jet Mass", "M [GeV]", 50, 0, 300};
PlotParams P_jet_asvj_pt		= {"jet_asvj_pt", "Anti Semi-visible Jet p_{T}", "p_{T} [GeV]", 50, 0, 1000};
PlotParams P_jet_asvj_eta		= {"jet_asvj_eta", "Anti Semi-visible Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams P_jet_asvj_phi		= {"jet_asvj_phi", "Anti Semi-visible Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams P_jet_asvj_m			= {"jet_asvj_m", "Anti Semi-visible Jet Mass", "M [GeV]", 50, 0, 300};

PlotParams P_maxphi_minphi		= {"maxphi_minphi", "max#phi - min#phi", "max#phi - min#phi", 50, 0, 3.14};
PlotParams P_pt_balance_12	 	= {"pt_balance_12", "p_{T} balance leading-subleading", "pt balance", 50, 0, 1};
PlotParams P_pt_balance_sa		= {"pt_balance_sa", "p_{T} balance svj-antisvj", "pt balance", 50, 0, 1};
PlotParams P_dphi_max			= {"dphi_max", "#Delta#phi (furthest jet, MET)", "#Delta#phi", 50, 0, 3.14};
PlotParams P_dphi_min			= {"dphi_min", "#Delta#phi (closest jet, MET)", "#Delta#phi", 50, 0, 3.14};
PlotParams P_deltaY_12			= {"deltaY_12", "#Delta Y (leading jet, subleading jet)", "#Delta Y", 50, 0, 10};

// Overlayed Plots
PlotParams OP_jet_pt			= {"jet_pt", "Jet Pt", "p_{T} [GeV]", 50, 0, 1000};
PlotParams OP_jet_eta			= {"jet_eta", "Jet Eta", "#eta", 50, -2.5, 2.5};
PlotParams OP_jet_phi			= {"jet_phi", "Jet Phi", "#phi", 50, -3.14, 3.14};
PlotParams OP_jet_m			= {"jet_m", "Jet M", "M [GeV]", 50, 0, 1000};
