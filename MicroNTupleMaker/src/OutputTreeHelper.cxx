/* =============================================================================================== */
void MicroNTupleMaker::DeclareOutputTrees(){
	treenames = {"PostSel"};

	vector<string> myvars = {
        	 
		// -- EventLevel -- //
		"runNumber", "eventNumber","mcEventWeight","weight","SumW",

		// -- JetLevel -- //
		"n_jets",
        	"jet1_pt", "jet1_eta", "jet1_phi", "jet1_E", 
        	"jet2_pt", "jet2_eta", "jet2_phi", "jet2_E", 
        	//"jet_svj_pt", "jet_svj_eta", "jet_svj_phi", "jet_svj_m", "jet_svj_n", "jet_svj_nConstituents",
        	//"jet_asvj_pt", "jet_asvj_eta", "jet_asvj_phi", "jet_asvj_m", "jet_asvj_n", "jet_asvj_nConstituents",
        	//"jet_xd1_matched_pt", "jet_xd1_matched_eta", "jet_xd1_matched_phi", "jet_xd1_matched_m", "jet_xd1_matched_n", "jet_xd1_matched_nConstituents",
        	//"jet_xd2_matched_pt", "jet_xd2_matched_eta", "jet_xd2_matched_phi", "jet_xd2_matched_m", "jet_xd2_matched_n", "jet_xd2_matched_nConstituents",
		//"jet1_Split12", "jet1_Split23", "jet1_tau32", "jet1_C2", "jet1_D2", "jet1_nTracks",
		//"jet2_Split12", "jet2_Split23", "jet2_tau32", "jet2_C2", "jet2_D2", "jet2_nTracks",
		//"jet_asvj_mT", "jet_asvj_Split12", "jet_asvj_Split23", "jet_asvj_tau32", "jet_asvj_C2", "jet_asvj_D2", "jet_asvj_nTracks",
		//"jet_svj_mT", "jet_svj_Split12", "jet_svj_Split23", "jet_svj_tau32", "jet_svj_C2", "jet_svj_D2", "jet_svj_nTracks",

		//"n_fatjets",
		//"fatjet1_pt", "fatjet1_eta", "fatjet1_phi", "fatjet1_m",
        	//"fatjet2_pt", "fatjet2_eta", "fatjet2_phi", "fatjet2_m", 

		// -- Jet Calculations -- //
		"maxphi_minphi", "dphi_min", "dphi_max",
		"dphi_min_MET",
		"dphi_MET_j1j2",
                "pt_balance_12", //"pt_balance_sa",
                "mjj_12", "mT_jj", 
		"mT_jj_neg", "met_jj_neg",
		//"mJJ_12", "mT_JJ",
		"dR_12", "deta_12",
		"deltaY_12", //"deltaY_sa",
		"hT", "rT",
		"aplanarity", "sphericity", "sphericity_T",	

		// -- MET -- //
        	"met_met", "met_phi"
        };

	vector<string> myvars_string = {
		"year"
	};
	
	vector<string> myvars_vector = {
		"all_jets_pt",
		"all_jets_eta",
		"all_jets_phi",
		"all_jets_E",
		//"all_fatjets_pt",
		//"all_fatjets_eta",
		//"all_fatjets_phi",
		//"all_fatjets_m",
	};

	for (auto treename: treenames){
		tree_output[treename] = new TTree( Form("%s",treename.c_str()), Form("%s",treename.c_str()) );
		
                for( auto var: myvars_vector ) 
			tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars_vector[var] );

                for( auto var: myvars_string ) 
			tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars_string[var] );

		for (auto var: myvars)
			tree_output[treename]->Branch( Form("%s",var.c_str()), &tree_output_vars[var]);

	}
}

/* =============================================================================================== */
void MicroNTupleMaker::FillOutputTrees(string treename){

	if (debug) cout << "MicroNTupleMaker::FillOutputTrees()" << endl;

	tree_output_vars_string["year"] = year_mc;

	tree_output_vars_vector["all_jets_pt"] = jet_pt;
	tree_output_vars_vector["all_jets_eta"] = jet_eta;
	tree_output_vars_vector["all_jets_phi"] = jet_phi;
	tree_output_vars_vector["all_jets_E"]= jet_E;	

	//tree_output_vars_vector["all_fatjets_pt"] = fatjet_pt;
	//tree_output_vars_vector["all_fatjets_eta"] = fatjet_eta;
	//tree_output_vars_vector["all_fatjets_phi"] = fatjet_phi;
	//tree_output_vars_vector["all_fatjets_m"]= fatjet_m;	
	
	tree_output_vars["runNumber"] = runNumber;
	tree_output_vars["eventNumber"] = eventNumber;
	tree_output_vars["mcEventWeight"] = mcEventWeight;
	tree_output_vars["weight"] = mcEventWeight*weight_scale;
	tree_output_vars["SumW"] = sumw;

	tree_output_vars["n_jets"] = njet;
	tree_output_vars["jet1_pt"] = jet_pt->at(0); // GeV
	tree_output_vars["jet1_eta"] = jet_eta->at(0);
	tree_output_vars["jet1_phi"] = jet_phi->at(0);
	tree_output_vars["jet1_E"] = jet_E->at(0);
	if (jet_pt->size() >= 2) {
		tree_output_vars["jet2_pt"] = jet_pt->at(1);
		tree_output_vars["jet2_eta"] = jet_eta->at(1);
		tree_output_vars["jet2_phi"] = jet_phi->at(1);
		tree_output_vars["jet2_E"] = jet_E->at(1);
	} else {
		tree_output_vars["jet2_pt"] = -999; 
		tree_output_vars["jet2_eta"] = -999;
		tree_output_vars["jet2_phi"] = -999;
		tree_output_vars["jet2_E"] = -999;
	}

	//tree_output_vars["n_fatjets"] = nfatjet;
	/*if (nfatjet >= 1){
		tree_output_vars["fatjet1_pt"] = fatjet_pt->at(0); // GeV
		tree_output_vars["fatjet1_eta"] = fatjet_eta->at(0);
		tree_output_vars["fatjet1_phi"] = fatjet_phi->at(0);
		tree_output_vars["fatjet1_m"] = fatjet_m->at(0);
	} else {
		tree_output_vars["fatjet1_pt"] = -999; // GeV
		tree_output_vars["fatjet1_eta"] = -999;
		tree_output_vars["fatjet1_phi"] = -999;
		tree_output_vars["fatjet1_m"] = -999;
	}
	if (nfatjet >= 2){
		tree_output_vars["fatjet2_pt"] = fatjet_pt->at(1);
		tree_output_vars["fatjet2_eta"] = fatjet_eta->at(1);
		tree_output_vars["fatjet2_phi"] = fatjet_phi->at(1);
		tree_output_vars["fatjet2_m"] = fatjet_m->at(1);
	} else {
		tree_output_vars["fatjet2_pt"] = -999;
		tree_output_vars["fatjet2_eta"] = -999;
		tree_output_vars["fatjet2_phi"] = -999;
		tree_output_vars["fatjet2_m"] = -999;
	}*/
	tree_output_vars["met_met"] = metFinalClus;
	tree_output_vars["met_phi"] = metFinalClusPhi;
	tree_output_vars["hT"] = hT;
	tree_output_vars["rT"] = rT;

	tree_output_vars["maxphi_minphi"] = maxphi_minphi;
	tree_output_vars["dphi_min_MET"] = dphi_min_MET;
	tree_output_vars["dphi_MET_j1j2"] = dphi_MET_j1j2;
        tree_output_vars["pt_balance_12"] = pt_balance_12;
        tree_output_vars["mjj_12"] = mjj_12;
        //tree_output_vars["mJJ_12"] = mJJ_12;
        tree_output_vars["mT_jj"] = mT_jj;
        tree_output_vars["mT_jj_neg"] = mT_jj_neg;
        tree_output_vars["met_jj_neg"] = met_jj_neg;
        //tree_output_vars["mT_JJ"] = mT_JJ;
	tree_output_vars["dR_12"] = dR_12;
	tree_output_vars["deta_12"] = deta_12;
        tree_output_vars["deltaY_12"] = deltaY_12;
	tree_output_vars["dphi_min"] = dphi_min;
	tree_output_vars["dphi_max"] = dphi_max;
	tree_output_vars["aplanarity"] = aplanarity;
	tree_output_vars["sphericity"] = sphericity;
	tree_output_vars["sphericity_T"] = sphericity_T;

	tree_output[treename]->Fill();
}


/* ====================================================================================================================== */
void MicroNTupleMaker::WriteOutputTrees(){

        if( debug ) cout<<"MicroNTupleMaker::WriteOutputTrees()"<<endl;

        cout<<"Writing Tree(s)..."<<endl;

        for(map<string,TTree*>::iterator it = tree_output.begin(); it != tree_output.end(); ++it){
                tree_output[it->first]->Write("", TObject::kOverwrite);
        }

}
