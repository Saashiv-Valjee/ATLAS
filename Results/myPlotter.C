#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void myPlotter(){

	string path = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v5/v5.2/user.ebusch.";
	//string path = "../MicroNTupleMaker/MicroNTuples/user.ebusch.";
	
	//vector<string> filetags = {"QCDbkg", "WpJets", "ZpJets", "ttbarr", "singlt", "dibson", "508547","508548","508549","508550" };
	vector<string> filetags = {/*"QCDbkg",*/ "515480", "515482", "515499", "515502", "515524", "515526"};
	//vector<string> filetags = {"QCDtest.mc20e", "515479.mc20e", "515482.mc20e", "515499.mc20e", "515502.mc20e", "515523.mc20e", "515526.mc20e"};
	//vector<string> filetags_signal = {"508547.mc16d","508548.mc16d", "508549.mc16d", "508550.mc16d"};
	vector<string> filetags_background = {"364702", "364703", "364704", "364705", "364706", "364707", "364708", "364709", "364710", "364711", "364712", "QCDbkg"};

	// - cuts
	map<string, TCut> cuts;	

	cuts["met"] = "met_met>200";
	cuts["jet"] = "fatjet_pt>500";

	class MicroNTuplePlotter plotter( filetags, path );

        //***************** Plot General options *******************// 
        plotter.plot_norm =true;
        plotter.plot_log = true;
	plotter.plot_error = false;
        plotter.output_file_tag ="v5p2";
	plotter.SetTreeName( "PostSel" );
        plotter.use_weight = true;
	plotter.stamp_counts = false;
	plotter.stamp_integral = true;
        plotter.solid_bkg = false;
	plotter.use_better_legend_names=true;
	//plotter.SetLegendManual( 0.5, 0.5, 0.9, 0.9 );
	plotter.colors = {/*kBlack,*/ kBlue+1, kAzure+7, kGreen+3, kSpring, kRed+1, kOrange-3, kPink+10, kPink+1, kYellow, kYellow-3  }; //1 background
        //plotter.colors = {kBlack, kCyan+3, kTeal-5, kBlue+1, kAzure+10, kViolet-3, kRed+2, kOrange+10, kRed-7, kOrange+1};
        //plotter.colors = { kRed, kOrange-3, kYellow+1, kSpring-1, kAzure, kBlue+2, kViolet}; //rainbow
        //plotter.colors = { kRed, kRed+2, kOrange-3, kYellow+1, kSpring, kGreen+3, kCyan+1, kAzure, kBlue+2, kViolet, kMagenta-9, kBlack}; //10 gradient + black

        //***************** Plot Variable options *******************//
        //plotter.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );
	//plotter.SetOverlayedPlots( {P_jet1_pt, P_jet2_pt, P_jet_svj_pt, P_jet_asvj_pt}, OP_jet_pt );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts("pt_balance_12 < 1.0");
       	//plotter.SetComparisonCuts({"", "jet1_pt > 450", "met_met > 200", "jet1_pt > 450 || met_met > 200", "hT > 1100"});	
        //plotter.ApplySelectiveCuts("508548", "dPhi_min < 2.0");

        //***************** Binning and Legend *******************//  
        //vector<string> leg_names = {"Inclusive","jet1_pt > 450", "met_met > 200", "jet1_pt > 450 || met_met > 200"};
	plotter.SetLegendManual( 0.45, 0.65, 0.9, 0.9, {} );

        //***************** Reweight and Plot *******************//  
	//plotter.SetOverlayedPlots( {P_jet1_pt, P_jet2_pt, P_jet_svj_pt, P_jet_asvj_pt}, OP_jet_pt );
	//plotter.PlotOverlay("");
	//      
	//plotter.SetOverlayedPlots( {P_jet1_eta, P_jet2_eta, P_jet_svj_eta, P_jet_asvj_eta}, OP_jet_eta );
	//plotter.PlotOverlay("");

	//plotter.SetOverlayedPlots( {P_jet1_phi, P_jet2_phi, P_jet_svj_phi, P_jet_asvj_phi}, OP_jet_phi );
	//plotter.PlotOverlay("");

	//plotter.SetOverlayedPlots( {P_jet1_m, P_jet2_m, P_jet_svj_m, P_jet_asvj_m}, OP_jet_m );
	//plotter.PlotOverlay("");

	//plotter.SetPlots ( {P_jet1_pt, P_jet2_pt, P_jet2_eta, P_n_r04_jets, P_n_r10_jets} );
	//plotter.SaveOutputFile("test");
        //plotter.SetPlots ( { P_mT_jj} );
	//plotter.SetPlots ( {P_aplanarity, P_sphericity, P_sphericity_T, P_jet1_D2, P_jet1_C2, P_jet1_Split12, P_jet1_Split23, P_jet1_tau23} );
	//plotter.SetPlots ( {P_aplanarity, P_sphericity, P_sphericity_T, P_mT_jj, P_rT, P_hT, P_dR_12, P_deta_12, P_dphi_min, P_pt_balance_12, P_deltaY_12, P_jet1_C2, P_jet2_C2} );
	plotter.SetPlots( {P_n_jets, P_n_fatjets});
	//plotter.SetPlots ( {P_jet1_D2, P_jet2_D2, P_jet1_Split12, P_jet2_Split12, P_jet1_Split23, P_jet2_Split23} );
	plotter.Plot("");
}
