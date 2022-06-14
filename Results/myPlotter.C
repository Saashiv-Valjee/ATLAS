#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void myPlotter(){

	//string path = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v1.0/v1.2/user.ebusch.";
	string path = "../MicroNTupleMaker/MicroNTuples/v1.3/user.ebusch.";
	
	//vector<string> filetags = {"508548.mc16d", "364703.mc16d"};
	vector<string> filetags = {"508547","508548", "508549", "508550", "364702"};
	vector<string> filetags_signal = {"508547","508548", "508549", "508550"};
	vector<string> filetags_background = {"364703", "364704"};

	// - cuts
	map<string, TCut> cuts;	

	cuts["met"] = "met_met>200";
	cuts["jet"] = "jet1_pt>500";

	class MicroNTuplePlotter plotter( filetags, path );

        //***************** Plot General options *******************// 
        plotter.plot_norm = true;
        plotter.plot_log = false;
	plotter.plot_error = false;
        plotter.output_file_tag ="mT_and_jz2";
	plotter.SetTreeName( "PostSel" );
        plotter.use_weight = true;
	plotter.stamp_counts = true;

        //***************** Plot Variable options *******************//
        //plotter.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );
	//plotter.SetOverlayedPlots( {P_jet1_pt, P_jet2_pt, P_jet_svj_pt, P_jet_asvj_pt}, OP_jet_pt );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts("met_met>200");
       	//plotter.SetComparisonCuts({"dPhi_min <1.5", "dPhi_min < 2.5"});	
        //plotter.ApplySelectiveCuts("508548", "dPhi_min < 2.0");

        //***************** Binning and Legend *******************//  
        //vector<string> leg_names = {"SR Selection", "Inclusive"};
	//plotter.SetLegendManual( 0.55, 0.65, 0.9, 0.9, leg_names );

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

	plotter.SetPlots ( {P_mT_jj} );
	//plotter.SetPlots ( {P_jet1_pt, P_met_met} );
	plotter.Plot("");
}
