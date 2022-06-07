#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void plotterExamples(){

	string path = "../MicroNTupleMaker/MicroNTuples/v0.1/user.ebusch.";
	

	// - cuts
	map<string, TCut> cuts;	

	//%%%%%%%%%%%%%%%%%%% Example 1 - Basic Plot %%%%%%%%%%%%%%%%%%%//

	vector<string> filetags_example1 = {"508547","508548", "508549", "508550", "364703.mc16e", "364704.mc16e", "364705.mc16e"};
	class MicroNTuplePlotter plotter_example1( filetags_example1, path );

        //***************** Plot General options *******************// 
        plotter_example1.plot_norm = true;
        plotter_example1.plot_log = false;
	plotter_example1.plot_error = false;
        plotter_example1.output_file_tag = "test";
	plotter_example1.SetTreeName( "PostSel" );

        //***************** Plot Variable options *******************//
        plotter_example1.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts("dPhi_min < 2.0");
       	//plotter.SetComparisonCuts({"dPhi_min <1.5", "dPhi_min < 2.5"});	
        //plotter.ApplySelectiveCuts("508548", "dPhi_min < 2.0");

        //***************** Binning and Legend *******************//  
        //vector<string> leg_names = {"SR Selection", "Inclusive"};
	//plotter.SetLegendManual( 0.55, 0.65, 0.9, 0.9, leg_names );

        //***************** Reweight and Plot *******************//  
	plotter_example1.Plot("");
		
	//%%%%%%%%%%%%%%%%%%% Example 2 - Ratio Plot %%%%%%%%%%%%%%%%%%%//
	// by default, the first plot is the ratio denominator (generally background/ data) 
	vector<string> filetags_example2 = {"364703.mc16e", "508547", "508548", "508549", "508550"};
	class MicroNTuplePlotter plotter_example2( filetags_example2, path );

        plotter_example2.plot_norm = true;
        plotter_example2.SetPlots( {P_jet1_pt, P_jet2_pt} );
	plotter_example2.Plot("ratio");


	//%%%%%%%%%%%%%%%%%%% Example 3 - Comparison Cuts %%%%%%%%%%%%%%%%%%%//


}
