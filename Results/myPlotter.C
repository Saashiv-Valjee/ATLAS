#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void myPlotter(){

	string path = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v6/v6.5/user.ebusch.";
	//string path = "../MicroNTupleMaker/MicroNTuples/user.ebusch.";
	
	//vector<string> filetags = {"QCDbkg", "WpJets", "ZpJets", "ttbarr", "singlt", "dibson", "508547","508548","508549","508550" };
	//vector<string> filetags = {"totalBKG", "515487", "515490", "515499", "515502", "515523", "515526"}; // pairs
	//vector<string> filetags = {/*"totalBKG",*/ "515487", "515499", "515507", "515515", "515519", "515523"}; // masses
	vector<string> filetags = {"QCDbkg", "Znunu", "515503", "515506"};
	//vector<string> filetags_signal = {"508547.mc16d","508548.mc16d", "508549.mc16d", "508550.mc16d"};
	vector<string> filetags_background = {"364702", "364703", "364704", "364705", "364706", "364707", "364708", "364709", "364710", "364711", "364712", "QCDbkg"};

	// - cuts
	//map<string, TCut> cuts;	

	//cuts["met"] = "met_met>50 && met_met<200";
	//cuts["njet"] = "n_jets>1";
	//cuts["fatjet"] = "fatjet1_pt>0 && fatjet2_pt>0";

	vector<PlotParams> plot_all = {	P_jet1_pt, P_jet2_pt,
					P_jet1_eta, P_jet1_pt,
					P_jet1_phi, P_jet2_phi,
					P_met_met, P_met_phi,
					P_mT_jj,
					P_mT_jj_neg, P_met_jj_neg, P_dphi_MET_j1j2,
					P_pt_balance_12, P_maxphi_minphi, P_rT,
					P_n_jets, P_hT, P_deltaY_12
					};

	class MicroNTuplePlotter plotter( filetags, path );

        //***************** Plot General options *******************// 
        plotter.plot_norm = true;
        plotter.plot_log = true;
        plotter.plot_log_ratio = false;
	plotter.plot_error = false;
        plotter.output_file_tag ="v6p5";
	plotter.SetTreeName( "PostSel" );
        plotter.use_weight = true;
	plotter.stamp_counts = false;
        plotter.violin = false;
	plotter.stamp_integral = false;
        plotter.solid_bkg = true;
	plotter.use_better_legend_names=true;
	plotter.reverse_cdf_plots = {"fabs(jet1_eta)", "fabs(jet2_eta)", "dphi_min", "deltaY_12"};
	plotter.use_normalized_cdf = false;
	//plotter.SetLegendManual( 0.5, 0.5, 0.9, 0.9 );
	plotter.colors = {kBlack, kGray+2, kBlue+1, kAzure+7, kGreen+3, kSpring, kRed+1, kOrange-3, kPink+10, kPink+1, kYellow, kYellow-3  }; //pairs
        //plotter.colors = { kBlack, kRed, kOrange-3, kYellow+1, kSpring-1, kAzure, kBlue+2, kViolet}; //rainbow
        //plotter.colors = { kRed, kRed+2, kOrange-3, kYellow+1, kSpring, kGreen+3, kCyan+1, kAzure, kBlue+2, kViolet, kMagenta-9, kBlack}; //10 gradient + black

        //***************** Plot Variable options *******************//
        //plotter.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );
	//plotter.SetOverlayedPlots( {P_jet1_pt, P_jet2_pt, P_jet_svj_pt, P_jet_asvj_pt}, OP_jet_pt );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts(cuts["njet"]);
       	//plotter.SetComparisonCuts({"deltaY_12 < 5.0", "deltaY_12 < 3.0"});	
        //plotter.ApplySelectiveCuts("508548", "dPhi_min < 2.0");

        //***************** Binning and Legend *******************//  
        //vector<string> leg_names = {"Inclusive","jet1_pt > 450", "met_met > 200", "jet1_pt > 450 || met_met > 200"};
	//plotter.SetLegendManual( 0.45, 0.65, 0.9, 0.9, {} );

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

	//plotter.SetPlots ( plot_all );
	plotter.SetPlots ( {P_dphi_min});
	//plotter.SaveOutputFile("test");
        //plotter.SetPlots ( { P_jet1_phi, P_jet2_phi, P_pt_balance_12, P_mT_jj, P_jet1_E, P_jet2_E, P_n_jets, P_met_met, P_maxphi_minphi, P_rT, P_mT_jj_neg} );
	//plotter.SetPlots( {P_dphi_min_MET, P_mT_jj_neg, P_met_jj_neg, P_dphi_MET_j1j2});
	//plotter.SetPlots ( {P_jet1_D2, P_jet2_D2, P_jet1_Split12, P_jet2_Split12, P_jet1_Split23, P_jet2_Split23} );
	plotter.Plot("");

        //***************** 2D Plot *******************// 	
	//plotter.Plot2D(P_mT_jj, P_met_met);
}
