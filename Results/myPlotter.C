#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void myPlotter(){

	//string path = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v1.0/v1.2/user.ebusch.";
	string path = "../MicroNTupleMaker/MicroNTuples/v1.6/user.ebusch.";
	
	//vector<string> filetags = {"508548.mc16d", "364703.mc16d"};
	vector<string> filetags = {"364702", "508547","508548","508549", "508550"};
	vector<string> filetags_signal = {"508547","508548", "508549", "508550"};
	vector<string> filetags_background = {"364703", "364704"};

	// - cuts
	map<string, TCut> cuts;	

	cuts["met"] = "met_met>200";
	cuts["jet"] = "jet1_pt>500";

	class MicroNTuplePlotter plotter( filetags_signal, path );

        //***************** Plot General options *******************// 
        plotter.plot_norm = true;
        plotter.plot_log = false;
	plotter.plot_error = false;
        plotter.output_file_tag ="trigger_smallr";
	plotter.SetTreeName( "PostSel" );
        plotter.use_weight = true;
	plotter.stamp_integral = true;
	plotter.colors = {kOrange+10, kBlue+2, kOrange+1, kAzure+7, kGreen+2, kAzure+7, kBlue+2 };

        //***************** Plot Variable options *******************//
        //plotter.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );
	//plotter.SetOverlayedPlots( {P_jet1_pt, P_jet2_pt, P_jet_svj_pt, P_jet_asvj_pt}, OP_jet_pt );

        //***************** Plot Cut options *******************// 
        plotter.SetCuts("mjj_12_r04>1100");
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

	plotter.SetPlots ( {P_r04_jet1_pt, P_mjj_12_r04} );
	//plotter.SetPlots ( {P_aplanarity, P_sphericity, P_sphericity_T} );
	//plotter.SetPlots ( {P_aplanarity, P_sphericity, P_sphericity_T, P_mT_jj, P_rT, P_hT, P_dR_12, P_deta_12, P_dphi_min, P_pt_balance_12, P_deltaY_12, P_jet1_C2, P_jet2_C2} );
	//plotter.SetPlots( {P_jet1_pt, P_met_met, P_hT_r04, P_mjj_12, P_mjj_12_r04, P_r04_jet1_pt});
	//plotter.SetPlots ( {P_jet1_D2, P_jet2_D2, P_jet1_Split12, P_jet2_Split12, P_jet1_Split23, P_jet2_Split23} );
	plotter.Plot("");
}
