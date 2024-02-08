#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void plotterExamples(){

	string path = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v12/v12.5/user.ebusch.";

	// - cuts
	map<string, TCut> cuts;	

	//%%%%%%%%%%%%%%%%%%% Example 1 - Basic Plot %%%%%%%%%%%%%%%%%%%//

	vector<string> filetags_example1 = {"515502","515503","515504","v9p2.515502","v9p2.515503","v9p2.515504"};
	class MicroNTuplePlotter plotter_example1( filetags_example1, path );

        //***************** Plot General options *******************// 
        plotter_example1.plot_norm = true;
        plotter_example1.plot_log = true;
	plotter_example1.solid_bkg = true;
	plotter_example1.plot_error = false;
	plotter_example1.manual_legend = true;
	plotter_example1.outfile_path ="/afs/cern.ch/user/s/svaljee/private/test_plots";
        plotter_example1.output_file_tag = "v12.5";
	plotter_example1.SetTreeName( "PostSel" );

        //***************** Plot Variable options *******************//
        plotter_example1.SetPlots( {P_jet1_pt,P_mT_jj} );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts("dPhi_min < 2.0");
       	//plotter.SetComparisonCuts({"dPhi_min <1.5", "dPhi_min < 2.5"});	
        //plotter.ApplySelectiveCuts("508548", "dPhi_min < 2.0");

        //***************** Binning and Legend *******************//  
        vector<string> leg_names = {"v12 2000 GeV 0.8", "v12 2500 GeV 0.2","v12 2500 GeV 0.4","v9 2000 GeV 0.8","v9 2500 GeV 0.2","v9 2500 GeV 0.4"};
	plotter_example1.SetLegendManual( 0.55, 0.65, 0.9, 0.9, leg_names );

        //***************** Reweight and Plot *******************//  
	plotter_example1.Plot("");

	//%%%%%%%%%%%%%%%%%%% Example 2 - Ratio Plot %%%%%%%%%%%%%%%%%%%//
	// by default, the first plot is the ratio denominator (generally background/ data) 
	//vector<string> filetags_example2 = {"364703.mc16e", "508547", "508548", "508549", "508550"};
	//class MicroNTuplePlotter plotter_example2( filetags_example2, path );

        //plotter_example2.plot_norm = true;
        //plotter_example2.SetPlots( {P_jet1_pt, P_jet2_pt} );
	//plotter_example2.Plot("ratio");


	//%%%%%%%%%%%%%%%%%%% Example 3 - Comparison Cuts %%%%%%%%%%%%%%%%%%%//


}
