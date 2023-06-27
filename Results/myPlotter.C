#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void myPlotter(){

	string path = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1/skim.user.ebusch.";
	//string path = "/eos/user/e/ebusch/SVJ/v7.1_micro/user.kipark.";
	
	///vector<string> filetags = {"QCDbkg"};// "515495", "515498", "515503", "515506", "515515", "515518"}; // pairs
	//vector<string> filetags = {"QCDskim", "515487", "515499", "515507", "515515", "515519", "515523"}; // masses
	//vector<string> filetags = {"QCDbkg", "Znunu", "515503", "515506"};
	//vector<string> filetags_signal = {"508547.mc16d","508548.mc16d", "508549.mc16d", "508550.mc16d"};
	//vector<string> filetags = {"QCDskim.mc20e","364703.mc20e", "364704.mc20e", "364705.mc20e", "364706.mc20e", "364707.mc20e", "364708.mc20e", "364709.mc20e"};
	vector<string> filetags = {"QCDskim.mc20e","515495.mc20e", "515498.mc20e", "515515.mc20e", "515518.mc20e"};

	// - cuts
	//map<string, TCut> cuts;	

	//cuts["met"] = "met_met>50 && met_met<200";
	//cuts["njet"] = "n_jets>1";
	//cuts["fatjet"] = "fatjet1_pt>0 && fatjet2_pt>0";

	vector<PlotParams> plot_all = {	P_jet1_pt, P_jet2_pt,
  					P_jet1_Width, P_jet2_Width,
					P_jet1_NumTrkPt1000PV, P_jet2_NumTrkPt1000PV,
					//P_jet1_eta, P_jet2_eta,
					//P_jet1_phi, P_jet2_phi,
					P_met_met, P_met_phi,
					P_mT_jj,
					P_mT_jj_neg, /*P_met_jj_neg, P_dphi_MET_j1j2,*/
					P_pt_balance_12, P_maxphi_minphi, P_rT,
					//P_n_jets, P_hT, P_deltaY_12,
					P_dphi_12, P_dphi_min, P_dR_12, P_deta_12
					};

	vector<PlotParams> plot_trks= {	P_jet2_SumPtTrkPt500PV, P_jet2_NumTrkPt500PV, 
					P_jet2_TrackWidthPt1000PV, P_jet2_NumTrkPt1000PV,
					P_jet2_Width, P_jet2_EMFrac,
					P_jet1_SumPtTrkPt500PV, P_jet1_NumTrkPt500PV, 
					P_jet1_TrackWidthPt1000PV, P_jet1_NumTrkPt1000PV, 
					P_jet1_Width, P_jet1_EMFrac,
					P_jet1_DL1dv01, P_jet2_DL1dv01, 
					P_jet1_GN1, P_jet2_GN1
					};

	class MicroNTuplePlotter plotter( filetags, path );

        //***************** Plot General options *******************// 
        plotter.plot_norm = true;
        plotter.plot_log = true;
        plotter.plot_log_ratio = false;
	plotter.plot_error = false;
        plotter.output_file_tag ="v8p1";
	plotter.SetTreeName( "PostSel" );
        plotter.use_weight = true;
	plotter.stamp_counts = false;
	plotter.stamp_integral = false;
	plotter.stamp_cuts = false;
        plotter.violin = false;
        plotter.solid_bkg = true;
	plotter.use_better_legend_names=true;
	plotter.reverse_cdf_plots = {"fabs(jet1_eta)", "fabs(jet2_eta)", "dphi_min", "deltaY_12"};
	plotter.use_normalized_cdf = true;
	//plotter.SetLegendManual( 0.5, 0.5, 0.9, 0.9 );
	//plotter.colors = {kBlack, /*kGray+2,*/ kBlue+1, kAzure+7, /*kGreen+3, kSpring,*/ kRed+1, kOrange-3, kPink+10, kPink+1, kYellow, kYellow-3  }; //pairs
        plotter.colors = { kBlack, kRed, kOrange-3, kYellow+1, kSpring-1, kAzure, kBlue+2, kViolet}; //rainbow
        //plotter.colors = { kRed, kRed+2, kOrange-3, kYellow+1, kSpring, kGreen+3, kCyan+1, kAzure, kBlue+2, kViolet, kMagenta-9, kBlack}; //10 gradient + black

        //***************** Plot Variable options *******************//
        //plotter.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );
	//plotter.SetOverlayedPlots( {P_jet1_pt, P_jet2_pt, P_jet_svj_pt, P_jet_asvj_pt}, OP_jet_pt );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts("jet2_Width > 0.07");
       	//plotter.SetComparisonCuts({"", "dphi_min>0.1", "dphi_min>0.5"});	
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
	plotter.SetPlots ( {P_jet1_eta, P_jet2_eta} );
	//plotter.SaveOutputFile("test");
        //plotter.SetPlots ( { P_jet1_DL1dv01, P_jet2_DL1dv01, P_jet1_GN1, P_jet2_GN1} );
	//plotter.SetPlots( {P_dphi_min_MET, P_mT_jj_neg, P_met_jj_neg, P_dphi_MET_j1j2});
	//plotter.SetPlots ( {P_mT_jj, P_jet1_pt} );
	plotter.Plot("");

        //***************** 2D Plot *******************// 	
	//plotter.Plot2D(P_mT_jj, P_met_met);
}
