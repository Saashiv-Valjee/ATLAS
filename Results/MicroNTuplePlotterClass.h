#include "PlotParams.h"
#include "PlotFunctions.h"

// -------------------------------------------------------------------------------------
class MicroNTuplePlotter{
public :

	bool debug = true;

	// Inputs
	vector<string> filetags;
	vector<string> treenames;
	vector<string> filetags_treenames;
	map<string, TTree*> trees;
	TString TreeName = "PostSel";
	bool multiple_trees = true;

	vector<string> hist_tags;	
	string infile_path;
	string infile_ext = ".root";
        TString outfile_path = "/eos/user/e/ebusch/SVJ/Plots";
	vector<PlotParams> PlotParamsList;
	PlotParams OverlayedPlotParams;
	TString MicroNtupleVersion = "";

	string output_file_tag = ""; 

	// Cuts
	TCut cuts_all;
	vector<TCut> cuts_compare = {""};
	map<string,TCut> selective_cuts;
	bool alternate_divisors = false;

	// Plot Options
	vector<Color_t> colors    = { kBlack, kMagenta-7, kRed, kOrange, kGreen+2, kAzure+7, kBlue+2 };
	vector<Style_t> linestyle = { kSolid, kSolid, kSolid,  kSolid, kSolid, kSolid, kSolid, kSolid, kSolid };
	Width_t linewidth = 4;
	vector<Style_t> markerstyle = { 1, 1, 1, 1, 1, 1, 1, 1 }; // Empty (Default)
	vector<Size_t> markersize = { 1, 1, 1, 1, 1, 1, 1, 1 }; // Empty (Default)

	bool plot_log  = false; 
	bool plot_log_x = false; 
	bool plot_log_ratio = false; // set to true if you want a log ratio or s/sqrtb panel
	bool plot_norm = false;
	bool plot_norm_full = false;
        bool plot_error = true;
        bool stamp_cuts = false;
        bool stamp_integral = true;
        bool stamp_counts = false;
        bool violin = false;
	bool manual_legend = false;
	bool use_better_legend_names = true;
	bool use_weight = true;
	bool plot_overlayed = false;
        bool solid_bkg = false;
	double legx1, legx2, legy1, legy2;
	vector<string> legend_names;

	// Significance formula
	string significance_formula = "ssqrtb";
	vector<string> reverse_cdf_plots = {""};
	bool use_normalized_cdf = false;

	// -------------------------------------------------------------------------------------
	MicroNTuplePlotter( vector<string> IN_filetags, string IN_infile_path ){
		SetStyle();

		filetags 	= IN_filetags;
		infile_path	= IN_infile_path;

	}

	// -------------------------------------------------------------------------------------
	~MicroNTuplePlotter(){
		//fout->Close();
	}

	// -------------------------------------------------------------------------------------
	string GetFiletagTreename( string filetag, string treename){

		if( debug) cout<<"MicroNTuplePlotter::GetFiletagTreename()"<<endl;

		return filetag+" | "+treename;
	}

	// -------------------------------------------------------------------------------------
	string GetFiletag( string filetag_treename){

		if( debug) cout<<"MicroNTuplePlotter::GetFiletag()"<<endl;

             	return filetag_treename.substr(0,filetag_treename.find(" "));
	}

	// -------------------------------------------------------------------------------------
	void SetTreeName( string IN_treename ){

		if( debug) cout<<"MicroNTuplePlotter::SetTreeName()"<<endl;

		treenames.clear();

		for( int i=0; i<filetags.size(); i++ )
			treenames.push_back( IN_treename );

		//use_single_treename = true;

		GetTrees();

		multiple_trees = false;

	}

	// -------------------------------------------------------------------------------------
	bool GetTree(string filetag, string treename ){

		if( debug) cout<<"MicroNTuplePlotter::GetTree()"<<endl;

		string filetag_treename = GetFiletagTreename( filetag, treename);

		//for(map<string,TTree*>::iterator it = trees.begin(); it != trees.end(); ++it){
		//	if( it->first == filetag_treename ){
		//		cout<<"NOTE: tree "<<treename<<" associated with "<<filetag<<" already exists."<<endl;
		//		return true;
		//	}
		//}

		TString filename = Form("%s%s%s", infile_path.c_str(), filetag.c_str(), infile_ext.c_str() );

		if( gSystem->AccessPathName(filename) ){
			cout<<"ERROR: File "<<filename<<" does not exist"<<endl;
			return false;
		}

		cout<<"Reading in "<<filename<<endl;
		TFile* file = new TFile( filename, "READ");

		if( !file->GetListOfKeys()->Contains( Form("%s", treename.c_str()) ) ){
			cout<<"ERROR: Tree "<<treename<<" does not exist in "<<filename<<endl;
			return false;
		}

		TTree* tree_temp = (TTree*)file->Get( Form("%s", treename.c_str()) );
		trees[filetag_treename] = (TTree*)tree_temp->Clone(); 

		return true;

	}

	// -------------------------------------------------------------------------------------
	void GetTrees(){
		if( debug) cout<<"MicroNTuplePlotter::GetTrees()"<<endl;

		bool trees_ok = false;
		for( int i=0; i<filetags.size(); i++ ){
			if( GetTree(filetags[i], treenames[i]) ){
				trees_ok = true;
				filetags_treenames.push_back( GetFiletagTreename( filetags[i], treenames[i]) );
			}
		}
		cout << "# of trees = " << filetags_treenames.size() << endl;
		//if( !trees_ok ) cout<<"ERROR: Input files or trees do not exist. Check input file paths & parameters.."<<endl;
	}

	// -------------------------------------------------------------------------------------
	TString GetOutputFileName( PlotParams myPlotParams, string plot_type = ""){
		if( debug) cout<<"MicroNTuplePlotter::GetOutputFileName()"<<endl;		

		string output_file_name;

		output_file_name = myPlotParams.hist_name;

		if( plot_type != "") output_file_name += "_"+plot_type;
		if( plot_norm ) output_file_name += "_norm";
		if( plot_log  ) output_file_name += "_log";		
		if( output_file_tag != "" ) output_file_name += "_"+output_file_tag;

		TString output_file_name_temp = Form("%s",output_file_name.c_str() );
		output_file_name_temp.ReplaceAll("(", "");
		output_file_name_temp.ReplaceAll(")", "");
		output_file_name_temp.ReplaceAll("**", "POW");
		output_file_name_temp.ReplaceAll("*", "MULT");
		output_file_name_temp.ReplaceAll("/", "DIV");	
		output_file_name_temp.ReplaceAll(">", "GT");	
		output_file_name_temp.ReplaceAll("<", "LT");		
		output_file_name_temp.ReplaceAll(" | ", "__");		

		return output_file_name_temp;
	}
 	
	// -------------------------------------------------------------------------------------
	void SetPlots(vector<PlotParams> myPlotParamsList){
		if( debug) cout<<"MicroNTuplePlotter::SetPlots()"<<endl;		

		PlotParamsList = myPlotParamsList;
		plot_overlayed = false;	
	} 

	// -------------------------------------------------------------------------------------
        void SetOverlayedPlots(vector<PlotParams> myPlotParamsList, PlotParams myOverlayedPlotParams){
		if( debug) cout<<"MicroNTuplePlotter::SetOverlayedPlots()"<<endl;		

		PlotParamsList = myPlotParamsList;                
		OverlayedPlotParams = myOverlayedPlotParams;
		plot_overlayed = true;	
        }

	// -------------------------------------------------------------------------------------
	void AddPlot( PlotParams myPlotParams ){

		if( debug) cout<<"MicroNTuplePlotter::AddPlot()"<<endl;	

		PlotParamsList.push_back( myPlotParams );
	}

	// -------------------------------------------------------------------------------------
	void SetCuts( TCut new_cut ){
		if( debug) cout<<"MicroNTuplePlotter::SetCuts()"<<endl;		

		cuts_all = new_cut;	
	}

	// -------------------------------------------------------------------------------------
	void AddCut( TCut new_cut ){
		if( debug) cout<<"MicroNTuplePlotter::AddCut()"<<endl;

		cuts_all = cuts_all && new_cut;
	}

	// -------------------------------------------------------------------------------------
	void SetComparisonCuts( vector<TCut> cuts_compare_input ){
		if( debug) cout<<"MicroNTuplePlotter::SetComparisonCuts()"<<endl;		

		if( cuts_compare_input.size() == 0 )
			cuts_compare = {""};
		else
			cuts_compare = cuts_compare_input; 
	}	

	// -------------------------------------------------------------------------------------
	void ApplySelectiveCuts( string match_filetag_or_treename, TCut cut ){
		if( debug) cout<<"MicroNTuplePlotter::ApplySelectiveCuts()"<<endl;
		// filetag_or_treename can be either -- there is string matching

		for( auto filetag_treename: filetags_treenames ){
			if( filetag_treename.find( match_filetag_or_treename ) != string::npos ){
				selective_cuts[filetag_treename] = selective_cuts[filetag_treename] && cut;
			}
		}	
	}

	// -------------------------------------------------------------------------------------
	void SetHistDrawStyle( TH1F* h, string hist_tag, int i ){
		if( debug) cout<<"MicroNTuplePlotter::SetHistDrawStyle()"<<endl;		

		// All
		if ((hist_tag.find("GeV") == string::npos && hist_tag.find("515") == string::npos) && solid_bkg)  h->SetFillColorAlpha(colors[i], 0.5);
		else h->SetFillColor(0);
		// Line Color
		h->SetLineColor( colors[i] );
		h->SetLineStyle( linestyle[i] );
		h->SetLineWidth( linewidth );
		// 	Marker
		h->SetMarkerColor(colors[i]);
		h->SetMarkerStyle(markerstyle[i]);
		h->SetMarkerSize(markersize[i]);

	}

	// -------------------------------------------------------------------------------------
	void SetLegendManual( double legx1_temp, double legx2_temp, double legy1_temp, double legy2_temp, vector<string> legend_names_temp = {} ){
		if( debug) cout<<"MicroNTuplePlotter::SetLegendManual()"<<endl;

		legx1 = legx1_temp;
		legx2 = legx2_temp;
		legy1 = legy1_temp;
		legy2 = legy2_temp;
		legend_names = legend_names_temp;
		manual_legend = true;
	}

	// -------------------------------------------------------------------------------------
	TString GetDrawOption(){
		TString draw_option = "nostack";
		if (!plot_error) draw_option = "nostack hist";

		return draw_option;
	}	

	// -------------------------------------------------------------------------------------
	TH1F* GetHist1D( PlotParams myPlotParams, string filetag_treename, TCut cut_compare ){
                if( debug) cout<<"MicroNTuplePlotter::GetHist1D()"<<endl;  

                string hist_name = myPlotParams.hist_name;
                string label_x   = myPlotParams.label_x;
                int NBins 	 = myPlotParams.nbins;
                double xmin      = myPlotParams.xmin;
                double xmax      = myPlotParams.xmax;

		TCanvas *c_temp = new TCanvas();
		TH1F *h_temp;

		TString hist_name_full = Form("%s__%s", hist_name.c_str(), filetag_treename.c_str());
		while (hist_name_full.Contains("(")){
			hist_name_full.Replace(hist_name_full.First("("), 1, "");
			hist_name_full.Replace(hist_name_full.First(")"), 1, "");
		}
		while (gDirectory->FindObject(hist_name_full)) {
			cout << hist_name_full << " exists" << endl; 
			hist_name_full.Append("x");
			cout << "changed name to " << hist_name_full << endl;
  		}

		if (false) {
                        // place holder for conditions on making hists, like variable bins
		} else {
                        h_temp = new TH1F( hist_name_full, "", NBins, xmin, xmax);
                }

		TCut cut_weight = Form( "weight" ); 
		//TCut cut_total   = (cuts_all && cut_compare && selective_cuts[filetag_treename]);
		TCut cut_total   = cut_weight * (cuts_all && cut_compare && selective_cuts[filetag_treename]);
		if( !use_weight ) cut_total = (cuts_all && cut_compare && selective_cuts[filetag_treename]);
                if( hist_name_full.Contains("data")) cut_total = (cuts_all && cut_compare && selective_cuts[filetag_treename]);
		if (debug) cout << "cut_total = " << cut_total << endl;

		cout << "hist_name: " << hist_name << endl;
		cout << "hist_name_full: " << hist_name_full << endl;
		trees[filetag_treename]->Draw( Form( "%s >> "+hist_name_full, hist_name.c_str() ), cut_total , "");
		cout << "hist_n_entries: " << h_temp->GetEntries() << endl;
		//if( use_weight ){
                //        if( debug ) cout<<Form( "%s - %f*(weight/weight) >> "+hist_name_full, hist_name.c_str(), shift )<<endl;
                //        trees[filetag_treename]->Draw( Form( "%s - %f*(weight/weight) >> "+hist_name_full, hist_name.c_str(), shift ), cut_total , "");
                //} else {
                //        if( debug ) cout<<Form( "%s >> "+hist_name_full, hist_name.c_str() )<<endl;
                //        trees[filetag_treename]->Draw( Form( "%s >> "+hist_name_full, hist_name.c_str() ), cut_total , "");
                //}

   		TH1F *h;
		h = (TH1F*)h_temp->Clone();

		return h;

	}

	// -------------------------------------------------------------------------------------
	TH2F* GetHist2D( PlotParams myPlotParams_x, PlotParams myPlotParams_y, string filetag_treename, TCut cut_compare ){
                if( debug) cout<<"MicroNTuplePlotter::GetHist2D()"<<endl;  

                string hist_name_x	 = myPlotParams_x.hist_name;
                string label_x		 = myPlotParams_x.label_x;
                int NBins_x	 	 = myPlotParams_x.nbins;
                double xmin    		 = myPlotParams_x.xmin;
                double xmax      	 = myPlotParams_x.xmax;
		
                string hist_name_y	 = myPlotParams_y.hist_name;
                string label_y		 = myPlotParams_y.label_x;
                int NBins_y	 	 = myPlotParams_y.nbins;
                double ymin    		 = myPlotParams_y.xmin;
                double ymax      	 = myPlotParams_y.xmax;

		TCanvas *c_temp = new TCanvas();
		TH2F *h_temp;

		TString hist_name_full = Form("%s__%s__%s", hist_name_x.c_str(), hist_name_y.c_str(), filetag_treename.c_str());
		h_temp = new TH2F( hist_name_full, "", NBins_x, xmin, xmax, NBins_y, ymin, ymax);	
		
		TCut cut_weight = Form( "weight/SumW" ); 

		//TCut cut_total   = (cuts_all && cut_compare && selective_cuts[filetag_treename]);
		TCut cut_total   = cut_weight * (cuts_all && cut_compare && selective_cuts[filetag_treename]);
		if( !use_weight ) cut_total = (cuts_all && cut_compare && selective_cuts[filetag_treename]);
		if(debug) cout << "cut_total = " << cut_total << endl;
		
		trees[filetag_treename]->Draw( Form( "%s:%s >> "+hist_name_full, hist_name_y.c_str(), hist_name_x.c_str() ), cut_total , "");
 		h_temp->GetYaxis()->SetTitle(Form("%s",label_y.c_str())); 
 		h_temp->GetXaxis()->SetTitle(Form("%s",label_x.c_str())); 
 		TH2F *h2;
		h2 = (TH2F*)h_temp->Clone();

		return h2;

	}


	// -------------------------------------------------------------------------------------
	map<string,TH1F*> GetHists( PlotParams myPlotParams ){
		if( debug ) cout<<"MicroNTuplePlotter::GetHists()"<<endl;

		map<string,TH1F*> hists; 
		hist_tags.clear(); 

		int i = 0;
		for( auto filetag_treename: filetags_treenames ){
			for( auto cut_compare: cuts_compare ){
				TH1F* h;
				h = (TH1F*)GetHist1D( myPlotParams, filetag_treename, cut_compare);
				string hist_tag;
				if (multiple_trees){
					hist_tag = Form( "%s", filetag_treename.c_str() );
				}else{
					string filetag_only = GetFiletag(filetag_treename);
 					if (cuts_compare.size() > 1){hist_tag = Form("%s ; "+cut_compare, filetag_only.c_str());}
					else if (use_better_legend_names){hist_tag = GetLegendNames(filetag_only);}
					else {hist_tag = Form( "%s", filetag_only.c_str());}
   				}
				hist_tags.push_back( hist_tag );
				if(debug) cout <<"filetag_treename: " <<filetag_treename<<endl;
				if(debug) cout <<"hist_tag: "<< hist_tag<<endl;
				hists[hist_tag] = h;
				i++;
			}
		}
		return hists; 
	}

	// -------------------------------------------------------------------------------------
	map<string,TH1F*> GetOverlayedHists( vector<PlotParams> myPlotParamsList ){
		if( debug ) cout<<"MicroNTuplePlotter::GetOverlayedHists()"<<endl;

		map<string,TH1F*> hists; 
		hist_tags.clear(); 

		int i = 0;
		for( auto filetag_treename: filetags_treenames ){
			for (auto cut_compare : cuts_compare) {
				for( auto myPlotParams: myPlotParamsList ){
					TH1F* h;
					h = (TH1F*)GetHist1D( myPlotParams, filetag_treename, cut_compare);
					string hist_tag = Form( "%s (%s)", myPlotParams.hist_name.c_str(), filetag_treename.c_str() );
					hist_tags.push_back( hist_tag );
					hists[hist_tag] = h;
					i++;
				}
			}
		}
		return hists; 
	}

	// -------------------------------------------------------------------------------------
	THStack* GetStackHist( map<string,TH1F*> hists, PlotParams myPlotParams ){ 
		if( debug) cout<<"MicroNTuplePlotter::GetStackHist()"<<endl;		

		string label_y = "Events";
		if( plot_norm ) label_y = "A.U.";

		THStack* hs = new THStack(Form( "hs_%s", myPlotParams.hist_name.c_str() ), Form("%s; %s; %s", myPlotParams.title.c_str(), myPlotParams.label_x.c_str(), label_y.c_str() ));

		int i = -1;
		for( auto hist_tag: hist_tags ){
			i++;
			TH1F *h = (TH1F*)hists[hist_tag]->Clone();
		
			string legend_name = hist_tag;
			if( stamp_integral && !stamp_counts ){
				legend_name = Form("%s (Int=%.4e)", hist_tag.c_str(), h->Integral(1,myPlotParams.nbins) );
			}
			if (stamp_counts && !stamp_integral){
				legend_name = Form("%s (NE=%i)", hist_tag.c_str(), int(h->GetEntries()));
			}
			if (stamp_counts && stamp_integral){
				legend_name = Form("%s (NE=%i, Int=%.2e)", hist_tag.c_str(), int(h->GetEntries()), h->Integral(0,myPlotParams.nbins+1)*1.39e8 );
			}

			if( plot_norm )
				h->Scale( 1./h->Integral() );
			if( plot_norm_full && !plot_norm)
				h->Scale( 1./h->Integral(0,h->GetNbinsX()+1) );
			if( plot_norm_full && plot_norm)
				cout << "ERROR: Please select only plot_norm or plot_norm_full";

			if( plot_log )	 h->SetMaximum( h->GetMaximum()*20. );
			else  		 h->SetMaximum( h->GetMaximum()*1.25 );

			SetHistDrawStyle( h, hist_tag, i);

			if( manual_legend && legend_names.size() > 0 )
				h->SetName( Form("%s", legend_names.at(i).c_str() ) );
			else 
				h->SetName( Form("%s", legend_name.c_str()) );	// GetBetterCutTitle
			hs->Add( h );	
		}

		return hs; 
	}	

	// -------------------------------------------------------------------------------------
	THStack* GetStackRatio( map<string,TH1F*> hists, PlotParams myPlotParams, string filetag_treename_divisor = "" ){
		if( debug) cout<<"MicroNTuplePlotter::GetStackRatio()"<<endl;		

		if( filetag_treename_divisor == "" ) 
			filetag_treename_divisor = hist_tags[0];

		string label_y = Form( "Hist / %s", filetag_treename_divisor.c_str() );
		if( plot_norm ) label_y += " (norm)";
		if( alternate_divisors ) label_y = "Efficiency";

		THStack* hs = new THStack(Form( "hs_%s", myPlotParams.hist_name.c_str() ), Form(" ; %s; %s", myPlotParams.label_x.c_str(), label_y.c_str() ));	

		TH1F *h_divisor = (TH1F*)hists[filetag_treename_divisor]->Clone();
		if( plot_norm )
			h_divisor->Scale( 1./h_divisor->Integral() );

		int i = -1;
		int j = -1;
		for( auto hist_tag: hist_tags ){
			j++; 

			if( alternate_divisors && j%2 != 1 ) continue;
			i++;

			TH1F *h = (TH1F*)hists[hist_tag]->Clone();
			h->SetName( Form("%s", hist_tag.c_str() ) );

			if( plot_norm )
				h->Scale( 1./h->Integral() );

			h->Divide( h_divisor );

			//h->SetMinimum( 0.8 );
			h->SetMaximum( 2.0 );
			if( plot_log_ratio ) h->SetMaximum( 10. );			

			//if( i == 0 ){
			//for( int ib = 0; ib < h->GetNbinsX()+1; ib++ ) h->SetBinError(ib, 0.0);
			//}

			SetHistDrawStyle( h, hist_tag, j );
			hs->Add( h );
		}

		return hs; 
	}

        // -------------------------------------------------------------------------------------
        THStack* GetStackSignificance( map<string,TH1F*> hists, PlotParams myPlotParams, string filetag_treename_divisor = "" ){
                if( debug) cout<<"MicroNTuplePlotter::GetStackSignificance()"<<endl;

                string label_y;
                if( significance_formula == "ssqrtb" && ! use_normalized_cdf )
                        label_y = Form("Signal CDF / #sqrt{bkg CDF}");
		else if ( significance_formula == "ssqrtb" &&  use_normalized_cdf )
                        label_y = Form("Norm Sig CDF / #sqrt{bkg CDF}");	
                else if( significance_formula == "Z" )
                        label_y = Form("Significance Z");
                else if( significance_formula == "Zprime" )
                        label_y = Form("Significance Z'");
                else if( significance_formula == "ssqrtb_sigeff" )
                        label_y = Form("Eff_{S} * #frac{S}{#sqrt(data)}");
                else{
                        cout<<"ERROR: Invalid significance_formula."<<endl;
                        THStack* hs_empty;
                        return hs_empty;
                }

                THStack* hs = new THStack(Form( "hs_%s", myPlotParams.hist_name.c_str() ), Form(" ; %s; %s", myPlotParams.label_x.c_str(), label_y.c_str() ));

                if( filetag_treename_divisor == "" ) filetag_treename_divisor = hist_tags[0];

                TH1F *h_b_temp      = (TH1F*)hists[filetag_treename_divisor]->Clone();
		if( use_normalized_cdf )
			h_b_temp->Scale(1./h_b_temp->Integral());	
                TH1F *h_cdf_b       = (TH1F*) GetCDF( h_b_temp );
                TH1F *h_cdf_b_r     = (TH1F*) GetReverseCDF( h_b_temp );
                TH1F *h_cdf_sqrtb   = (TH1F*) GetSqrtTH1( h_cdf_b );
                TH1F *h_cdf_sqrtb_r = (TH1F*) GetSqrtTH1( h_cdf_b_r );
		legend_names.clear();

                int i = -1;
                for( auto hist_tag: hist_tags ){
                        i++;

                        if( hist_tag == filetag_treename_divisor ) continue;
			bool use_reverse_cdf = find(reverse_cdf_plots.begin(),reverse_cdf_plots.end(), myPlotParams.hist_name) != reverse_cdf_plots.end();

                        TH1F *h_s_temp    = (TH1F*) hists[hist_tag]->Clone();
			if( use_normalized_cdf )
				h_s_temp->Scale(1./h_s_temp->Integral());	
                        TH1F *h_cdf_s;
			if (use_reverse_cdf)
			    h_cdf_s = (TH1F*) GetReverseCDF( h_s_temp );	
			else
			    h_cdf_s = (TH1F*) GetCDF( h_s_temp );
                        TH1F *h_cdf_sqrts = (TH1F*) GetSqrtTH1( h_cdf_s );
                        TH1F *h_cdf_seff  = (TH1F*) h_cdf_s->Clone();
                        h_cdf_seff->Scale( 1./h_cdf_seff->GetBinContent(1) );

                        // S/Sqrt(b) (default)
                        TH1F *h_ssqrtb = (TH1F*)h_cdf_s->Clone();
			if (use_reverse_cdf)
                        	h_ssqrtb->Divide( h_cdf_sqrtb_r );
			else
                        	h_ssqrtb->Divide( h_cdf_sqrtb );	
		
                        TH1F* h;
                        if( significance_formula == "ssqrtb"){
                                h = (TH1F*) h_ssqrtb->Clone();
                        }/* else if( significance_formula == "Z"){ // Significance
                                TH1F *h_Z = (TH1F*) GetSignificanceZ( h_cdf_s, h_cdf_b);
                                h = (TH1F*) h_Z->Clone();
                        } else if( significance_formula == "Zprime"){ // Devin's Formula
                                TH1F *h_Zprime = (TH1F*) DevinsFormulaZprime( h_cdf_s, h_cdf_b);
                                h = (TH1F*) h_Zprime->Clone();
                        } else if ( significance_formula == "ssqrtb_sigeff" ){ // sig_eff * S/Sqrt(b)
                                TH1F *h_sigeff_ssqrtb = (TH1F*)h_ssqrtb->Clone();
                                h_sigeff_ssqrtb->Multiply( h_cdf_seff );
                                h = (TH1F*) h_sigeff_ssqrtb->Clone();
                        }*/ else {
				cout << "ERROR: significance formula not implemented" << endl;
			}

                        SetHistDrawStyle( h, hist_tag, i );

                        double max_x = h->GetXaxis()->GetBinCenter( h->GetMaximumBin() );
                        double max_y = h->GetMaximum();
			string max_vals =  Form("%.1e , %.3f ", max_y, max_x );
                        h->SetName( Form("%s", max_vals.c_str() ));
			legend_names.push_back(Form("%s", max_vals.c_str()));
			

                        if( plot_log_ratio ) h->SetMaximum( h->GetMaximum()*10. );
                        else               h->SetMaximum( h->GetMaximum()*1.25 );

                        hs->Add( h );
                }

                return hs;

        }

	// -------------------------------------------------------------------------------------
	void Plot( string plot_type = "", string filetag_treename_divisor = "" ){
		if( debug) cout<<"MicroNTuplePlotter::Plot()"<<endl;		

		if (plot_overlayed){
			PlotOverlay(plot_type, filetag_treename_divisor);
			return;
		}

		TString draw_option = GetDrawOption();

		for( auto PlotParams_temp: PlotParamsList ){
			map<string,TH1F*> hists = GetHists( PlotParams_temp );

			TCanvas *myCanvas;
			TPad *p1;
			TPad *p2;

			if( plot_type == "" || plot_type == "ratioonly" ) 
				myCanvas = new TCanvas("c", "c", 1600, 1200);
			else {
				myCanvas = new TCanvas("c", "c", 1600, 1200);	
				p1 = new TPad("p1", "p1", 0.1,0.2,0.9,1.0);
				p2 = new TPad("p2", "p2", 0.1,0.0,0.9,0.2);
				p1->Draw();	
				p2->Draw();	
			}

			THStack* hs;

			if( plot_type == "" || plot_type == "ratioonly" ){
				hs = GetStackHist( hists, PlotParams_temp );
				myCanvas->cd(1);
				hs->Draw(draw_option);
				if( plot_log )		gPad->SetLogy(); 
				if( plot_log_x )	gPad->SetLogx(); 
 
			} else {
				p1->cd();
				hs = GetStackHist( hists, PlotParams_temp );
				hs->Draw(draw_option); 				
				if( plot_log )		p1->SetLogy(); 
				if( plot_log_x )	p1->SetLogx(); 

				THStack* hsr;
				if (plot_type == "ratio"){
					p2->cd();
					hsr = GetStackRatio( hists, PlotParams_temp, filetag_treename_divisor );
 					hsr->Draw(draw_option);
				} else if (plot_type == "sig" || plot_type == "ssqrtb" ){
					p2->cd();
					hsr = GetStackSignificance( hists, PlotParams_temp, filetag_treename_divisor );
					hsr->Draw("nostack");
				} else {
					cout << "ERROR: unrecognized plot type " << plot_type << "; Exiting..." << endl;
					return;
				}
					
				hsr->GetYaxis()->SetLabelSize(0.12);
				hsr->GetYaxis()->SetTitleSize(0.08);
				hsr->GetYaxis()->SetTitleOffset(0.6);
				hsr->GetXaxis()->SetLabelSize(0.12);
				hsr->GetXaxis()->SetTitleSize(0.0);

				if( plot_log_ratio ) p2->SetLogy(); 	
				if( plot_log_x ) p2->SetLogx(); 

				p1->cd();
		
			}

			if( manual_legend )
				gPad->BuildLegend(legx1,legx2,legy1,legy2,"");
			else if ( plot_type == "sig" || plot_type == "ssqrtb"){
				gPad->BuildLegend(0.55,0.65,0.78,0.9,"");
				TPaveText *t = new TPaveText(.72,.65,.9,.9, "NDC");
				bool use_reverse_cdf = find(reverse_cdf_plots.begin(),reverse_cdf_plots.end(), PlotParams_temp.hist_name) != reverse_cdf_plots.end();
				if (use_reverse_cdf)
					t->AddText("Significance, Max Cut");
				else
					t->AddText("Significance, Min Cut");

				for (auto sig_val: legend_names){
					t->AddText(Form("%s", sig_val.c_str()));
				}
				t->Draw("same");
			}else
				gPad->BuildLegend(0.70,0.65,0.9,0.9,"");
	
			StampATLAS( "Internal", 140., 0.14, 0.84, 0.045 );
			//if (stamp_cuts) StampCuts( 0.1, 0.91, 0.015 );			

			myCanvas->cd(1);
			/*if (plot_type == "sig" || plot_type == "ssqrtb"){
				TPaveText *t = new TPaveText(.75,.65,.9,.9, "NDC");
				for (auto sig_val: legend_names){
					cout << sig_val << endl;
					t->AddText(Form("A %s", sig_val.c_str()));
				}
				t->Draw("same");
				myCanvas->Modified();
				myCanvas->Update();
			}*/

			//if( plot_log )		gPad->SetLogy(); 
			//if( plot_log_x )		gPad->SetLogx(); 

			TString output_file_name = GetOutputFileName(PlotParams_temp, plot_type);
			myCanvas->SaveAs( outfile_path+"/"+output_file_name+".png", "png" );
			delete myCanvas;
			hists.clear();

		}

	}

	// -------------------------------------------------------------------------------------
	void Plot2D( PlotParams myPlotParams_x, PlotParams myPlotParams_y  ){
		if( debug) cout<<"MicroNTuplePlotter::Plot2D()"<<endl;		


		GetTrees();
		SetStyle();

		for( auto filetag_treename: filetags_treenames ){
			for( auto cut_compare: cuts_compare ){

				TH2F* h2 = (TH2F*)GetHist2D( myPlotParams_x, myPlotParams_y, filetag_treename, cut_compare );

				TCanvas *myCanvas = new TCanvas("c", "c", 1300, 1200);
				myCanvas->SetRightMargin(0.14);
				myCanvas->SetLeftMargin(0.14);
				myCanvas->SetTopMargin(0.12);
				myCanvas->SetBottomMargin(0.12);

				if( plot_log ) 
					gPad->SetLogz();

				if( plot_norm )
					h2->Scale(1./h2->Integral());

				if( stamp_counts )
					h2->Draw("colz TEXT");
				else if ( violin ){
					//h2->SetBarWidth(3);
					h2->SetFillStyle(0);
					h2->Draw("violiny(112000000)");
				}else
					h2->Draw("colz");
				string output_file_name = myPlotParams_y.hist_name + "_vs_" + myPlotParams_x.hist_name; // GetOutputFileName(myPlotParams_x);
				string filetag_only = GetFiletag(filetag_treename);
				output_file_name += "_" + filetag_only + "_" + output_file_tag; 
				myCanvas->SaveAs( outfile_path+"/"+output_file_name+".png", "png");

			}
		}

	}

	// -------------------------------------------------------------------------------------
	void PlotOverlay( string plot_type = "", string filetag_divisor = "" ){
		if( debug) cout<<"MicroNTuplePlotter::PlotOverlay()"<<endl;		

		SetStyle();

		TCanvas *myCanvas;
		TString draw_option = GetDrawOption();

		if( plot_type == "" ) 
			myCanvas = new TCanvas("c", "c", 1600, 1200);
		else {
			myCanvas = new TCanvas("c", "c", 1200, 1600);	
			myCanvas->Divide(0,2);
		}
	
		map<string,TH1F*> hists = GetOverlayedHists( PlotParamsList );

		THStack* hs = GetStackHist( hists, OverlayedPlotParams );
		myCanvas->cd();
                hs->Draw(draw_option); 
		//if( plot_type == "ratio" ){
		//	myCanvas->cd(2);
		//	if( plot_log_ratio ) gPad->SetLogy(); 		
		//	THStack* hs_ratio = GetStackRatio( hists, PlotParams_temp, true, filetag_divisor );	
		//	hs_ratio->Draw("nostack");
		//	myCanvas->cd(1);
		//}

		if( manual_legend )
			gPad->BuildLegend(legx1,legx2,legy1,legy2,"");
		else
			gPad->BuildLegend(0.55,0.65,0.9,0.9,"");
		

		StampATLAS( "Internal", 140., 0.14, 0.84, 0.045 );
		//StampCuts( 0.1, 0.91, 0.015 );			

		myCanvas->cd();

		if( plot_log )
			gPad->SetLogy(); 
	
		TString output_file_name = OverlayedPlotParams.hist_name;
		TString output_file_path = "/eos/home-e/ebusch/SVJ/Plots/";
		//myCanvas->Write();
		myCanvas->SaveAs( output_file_path+output_file_name+".png", "png" );
	
		delete myCanvas;
	}

}; // end of class
