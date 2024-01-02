#include "MicroNTuplePlotterClass.h"

// -------------------------------------------------------------------------------------------------
void myPlotter(){

	string path = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v7/v7.4/user.ebusch.";
	//string path = "/eos/user/e/ebusch/SVJ/v7.1_micro/user.kipark.";
	
	//vector<string> filetags = {"METbkg", "515495", "515498", "515503", "515506", "515515", "515518"}; // pairs
	//vector<string> filetags = {"METBkg", "515487", "515499", "515507", "515515", "515519", "515523"}; // masses
	//vector<string> filetags = { "dataAll", "data15", "data16", "data17", "data18" };//, "QCDskim", "Znunu", "Wjets", "topPhys", "diboson"};
	//vector<string> filetags = { "data16", "QCDskim", "Znunu", "Wjets", "topPhys"};
	vector<string> filetags = {"dataAll", "515495", "515498", "515507","515510"}; // rinv

	// - cuts
	//map<string, TCut> cuts;	

	//cuts["met"] = "met_met>50 && met_met<200";
	//cuts["njet"] = "n_jets>1";
	//cuts["fatjet"] = "fatjet1_pt>0 && fatjet2_pt>0";

	vector<PlotParams> plot_all = {	P_jet1_pt, P_jet2_pt,
  					//P_jet1_Width, P_jet2_Width,
					//P_jet1_NumTrkPt1000PV, P_jet2_NumTrkPt1000PV,
					P_jet1_eta, P_jet2_eta,
					P_jet1_phi, P_jet2_phi,
					P_met_met, P_met_phi,
					//P_mT_jj,
					//P_mT_jj_neg, /*P_met_jj_neg, P_dphi_MET_j1j2,*/
					//P_pt_balance_12, P_maxphi_minphi, P_rT,
					P_n_jets, P_hT, P_deltaY_12, P_runNumber,
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
        plotter.output_file_tag ="data";
	plotter.SetTreeName( "PostSel" );
        plotter.use_weight = false;
	plotter.stamp_counts = false;
	plotter.stamp_integral = false;
	plotter.stamp_cuts = false;
        plotter.violin = false;
        plotter.solid_bkg = false;
	plotter.use_better_legend_names=true;
	plotter.reverse_cdf_plots = {"fabs(jet1_eta)", "fabs(jet2_eta)", "dphi_min", "deltaY_12"};
	plotter.use_normalized_cdf = true;
	//plotter.SetLegendManual( 0.5, 0.5, 0.9, 0.9 );
	//plotter.colors = {kBlack, kRed, /*kGray+2,*/ kBlue+1, kAzure+7,kGreen+3, kSpring, kRed+1, kOrange-3, kPink+10, kPink+1, kViolet-1, kViolet-4 }; //pairs
        plotter.colors = { kBlack, kRed, kOrange-3, kYellow+1, kSpring-1, kAzure, kBlue+2, kViolet}; //rainbow
        //plotter.colors = { kRed, kRed+2, kOrange-3, kYellow+1, kSpring, kGreen+3, kCyan+1, kAzure, kBlue+2, kViolet, kMagenta-9, kBlack}; //10 gradient + black

        //***************** Plot Variable options *******************//
        //plotter.SetPlots( {P_jet1_pt, P_jet_svj_pt, P_jet_asvj_pt, P_pt_balance_12, P_pt_balance_sa, P_dphi_min, P_maxphi_minphi, P_met_met} );
	//plotter.SetOverlayedPlots( {P_jet1_pt, P_jet2_pt, P_jet_svj_pt, P_jet_asvj_pt}, OP_jet_pt );

        //***************** Plot Cut options *******************// 
        //plotter.SetCuts("rT > 0.2 && met_met > 200");
       	//plotter.SetComparisonCuts({"met_phi < -1.5 && met_phi > -2.8", "met_phi < -1.0 && met_phi > -1.5", "met_phi > -0.5 && met_phi <0", "met_phi > 0.0 && met_phi < 0.7", "met_phi > 2.5"});	
       	//plotter.SetComparisonCuts({"runNumber < 290000", "runNumber > 290000 && runNumber < 320000", "runNumber > 320000 && runNumber < 345000", "runNumber > 345000"});	
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
	//plotter.SetPlots ( {P_dphi_min, P_met_met, P_met_phi, P_jet1_pt, P_jet1_phi, P_jet2_phi});//, P_jet1_pt, P_jet1_phi, P_jet2_phi, P_met_phi} );
	//plotter.SaveOutputFile("test");
        //plotter.SetPlots ( { P_jet1_DL1dv01, P_jet2_DL1dv01, P_jet1_GN1, P_jet2_GN1} );
	plotter.SetPlots( {P_met_met});
	//plotter.SetPlots ( {P_met_phi, P_jet1_phi, P_jet2_phi} );
        plotter.Plot("ssqrtb");

        //***************** 2D Plot *******************// 	
	//plotter.Plot2D(P_jet2_phi, P_jet2_eta);
}
