#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void plotterExamples(){

	string path = "../MicroNTupleMaker/MicroNTuples/v0.1/user.ebusch.";
	
	vector<string> filetags = {"508547","508548", "508549", "508550", "364703.mc16e", "364704.mc16e", "364705.mc16e"};

	// - cuts
	map<string, TCut> cuts;	

	//%%%%%%%%%%%%%%%%%%% Example 1 - Basic Plot %%%%%%%%%%%%%%%%%%%//

	class MicroNTuplePlotter plotter_example1( filetags, path );

        //***************** Plot General options *******************// 
        plotter_example1.plot_norm = true;
        plotter_example1.plot_log = false;
	plotter_example1.plot_error = false;
        plotter_example1.output_file_tag = "test";
	plotter_example1.SetTreeName( "PostSel" );

        //***************** Plot Variable options *******************//
        plotter.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts("dPhi_min < 2.0");
       	//plotter.SetComparisonCuts({"dPhi_min <1.5", "dPhi_min < 2.5"});	
        //plotter.ApplySelectiveCuts("508548", "dPhi_min < 2.0");

        //***************** Binning and Legend *******************//  
        //vector<string> leg_names = {"SR Selection", "Inclusive"};
	//plotter.SetLegendManual( 0.55, 0.65, 0.9, 0.9, leg_names );

        //***************** Reweight and Plot *******************//  
	plotter.Plot("");
		

	//%%%%%%%%%%%%%%%%%%% Example 2 - Ratio Plot %%%%%%%%%%%%%%%%%%%//

	//%%%%%%%%%%%%%%%%%%% Example 3 - Comparison Cuts %%%%%%%%%%%%%%%%%%%//

	//%%%%%%%%%%%%%%%%%%% Example 4 - Comparison Cuts %%%%%%%%%%%%%%%%%%%//
}
