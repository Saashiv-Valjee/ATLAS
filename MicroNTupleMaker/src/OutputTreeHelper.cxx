/* =============================================================================================== */
void MicroNTupleMaker::DeclareOutputTrees(){
	treenames = {"PostSel"};

	vector<string> myvars = {
        	 
		// -- EventLevel -- //
		"runNumber", "eventNumber","mcEventWeight","weight","SumW",

		// -- JetLevel -- //
		"n_r04_jets", "n_r10_jets",
        	"jet1_pt", "jet1_eta", "jet1_phi", "jet1_E", "jet1_nConstituents",
        	"jet2_pt", "jet2_eta", "jet2_phi", "jet2_E", "jet2_nConstituents",
        	//"jet_svj_pt", "jet_svj_eta", "jet_svj_phi", "jet_svj_m", "jet_svj_n", "jet_svj_nConstituents",
        	//"jet_asvj_pt", "jet_asvj_eta", "jet_asvj_phi", "jet_asvj_m", "jet_asvj_n", "jet_asvj_nConstituents",
        	//"jet_xd1_matched_pt", "jet_xd1_matched_eta", "jet_xd1_matched_phi", "jet_xd1_matched_m", "jet_xd1_matched_n", "jet_xd1_matched_nConstituents",
        	//"jet_xd2_matched_pt", "jet_xd2_matched_eta", "jet_xd2_matched_phi", "jet_xd2_matched_m", "jet_xd2_matched_n", "jet_xd2_matched_nConstituents",
		//"jet1_Split12", "jet1_Split23", "jet1_tau32", "jet1_C2", "jet1_D2", "jet1_nTracks",
		//"jet2_Split12", "jet2_Split23", "jet2_tau32", "jet2_C2", "jet2_D2", "jet2_nTracks",
		//"jet_asvj_mT", "jet_asvj_Split12", "jet_asvj_Split23", "jet_asvj_tau32", "jet_asvj_C2", "jet_asvj_D2", "jet_asvj_nTracks",
		//"jet_svj_mT", "jet_svj_Split12", "jet_svj_Split23", "jet_svj_tau32", "jet_svj_C2", "jet_svj_D2", "jet_svj_nTracks",

		// -- Jet Calculations -- //
		"maxphi_minphi", "dphi_min", "dphi_max",
                "pt_balance_12", //"pt_balance_sa",
                "mjj_12", "mT_jj", 
		"dR_12", "deta_12",
		"deltaY_12", //"deltaY_sa",
		"hT", "rT",
		"aplanarity", "sphericity", "sphericity_T",	

		// -- MET -- //
		//"MET_TruthMET_TruthPhi","MET_TruthMET_TruthSumEt",
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
		//"all_jets_numConstituents",
		"all_LRjets_pt",
		"all_LRjets_eta",
		"all_LRjets_phi",
		"all_LRjets_m",		
		"all_LRjets_Split12",
		"all_LRjets_Split23",
		"all_LRjets_tau32",
		"all_LRjets_C2",
		"all_LRjets_D2",
		//"all_LRjets_nTracks"	
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

	tree_output_vars_vector["all_jets_pt"] = a4_pflowjets_pt;
	tree_output_vars_vector["all_jets_eta"] = a4_pflowjets_eta;
	tree_output_vars_vector["all_jets_phi"] = a4_pflowjets_phi;
	tree_output_vars_vector["all_jets_E"]= a4_pflowjets_E;
	//tree_output_vars_vector["all_jets_numConstituents"] = a4_pflowjets_numConstituents;

	tree_output_vars_vector["all_LRjets_pt"] = a10_lctopojets_pt;
	tree_output_vars_vector["all_LRjets_eta"]= a10_lctopojets_eta;
	tree_output_vars_vector["all_LRjets_phi"]= a10_lctopojets_phi;
	tree_output_vars_vector["all_LRjets_m"] =  a10_lctopojets_m;
	tree_output_vars_vector["all_LRjets_Split12"] = a10_lctopojets_Split12;
	tree_output_vars_vector["all_LRjets_Split23"] = a10_lctopojets_Split23;
	tree_output_vars_vector["all_LRjets_tau32"] = a10_lctopojets_tau32_wta;
	tree_output_vars_vector["all_LRjets_C2"] = a10_lctopojets_C2;
	tree_output_vars_vector["all_LRjets_D2"] = a10_lctopojets_D2;
	//tree_output_vars_vector["all_LRjets_nTracks"] = a10_lctopojets_nTracks;
	

	tree_output_vars["runNumber"] = runNumber;
	tree_output_vars["eventNumber"] = eventNumber;
	tree_output_vars["mcEventWeight"] = mcEventWeight;
	tree_output_vars["weight"] = mcEventWeight*weight_scale;
	tree_output_vars["SumW"] = sumw;

	tree_output_vars["n_r04_jets"] = na4_pflowjets;
	tree_output_vars["n_r10_jets"] = na10_lctopojets;

	/*
	tree_output_vars["lr_jet1_pt"] = a10_lctopojets_pt->at(0); // GeV
	tree_output_vars["lr_jet1_eta"] = a10_lctopojets_eta->at(0);
	tree_output_vars["lr_jet1_phi"] = a10_lctopojets_phi->at(0);
	tree_output_vars["lr_jet1_m"] = a10_lctopojets_m->at(0);
	tree_output_vars["lr_jet1_mT"] = jet1_mT;
	tree_output_vars["lr_jet1_Split12"] = a10_lctopojets_Split12->at(0);
	tree_output_vars["lr_jet1_Split23"] = a10_lctopojets_Split23->at(0);
	tree_output_vars["lr_jet1_tau32"] = a10_lctopojets_tau32_wta->at(0);
	tree_output_vars["lr_jet1_C2"] = a10_lctopojets_C2->at(0);
	tree_output_vars["lr_jet1_D2"] = a10_lctopojets_D2->at(0);
	tree_output_vars["lr_jet1_nTracks"] = a10_lctopojets_nTracks->at(0);

	tree_output_vars["lr_jet2_pt"] = a10_lctopojets_pt->at(1);
	tree_output_vars["lr_jet2_eta"] = a10_lctopojets_eta->at(1);
	tree_output_vars["lr_jet2_phi"] = a10_lctopojets_phi->at(1);
	tree_output_vars["lr_jet2_m"] = a10_lctopojets_m->at(1);
	tree_output_vars["lr_jet2_mT"] = jet2_mT;
	tree_output_vars["lr_jet2_Split12"] = a10_lctopojets_Split12->at(1);
	tree_output_vars["lr_jet2_Split23"] = a10_lctopojets_Split23->at(1);
	tree_output_vars["lr_jet2_tau32"] = a10_lctopojets_tau32_wta->at(1);
	tree_output_vars["lr_jet2_C2"] = a10_lctopojets_C2->at(1);
	tree_output_vars["lr_jet2_D2"] = a10_lctopojets_D2->at(1);
	tree_output_vars["lr_jet2_nTracks"] = a10_lctopojets_nTracks->at(1);
	*/      

	/*
        tree_output_vars["jet_svj_n"] = n_svj;
	tree_output_vars["jet_svj_pt"] = a10_lctopojets_pt->at(n_svj);
	tree_output_vars["jet_svj_eta"] = a10_lctopojets_eta->at(n_svj);
	tree_output_vars["jet_svj_phi"] = a10_lctopojets_phi->at(n_svj);
	tree_output_vars["jet_svj_m"] = a10_lctopojets_m->at(n_svj);
	tree_output_vars["jet_svj_mT"] = jet_svj_mT;
	tree_output_vars["jet_svj_Split12"] = a10_lctopojets_Split12->at(n_svj);
	tree_output_vars["jet_svj_Split23"] = a10_lctopojets_Split23->at(n_svj);
	tree_output_vars["jet_svj_tau32"] = a10_lctopojets_tau32_wta->at(n_svj);
	tree_output_vars["jet_svj_C2"] = a10_lctopojets_C2->at(n_svj);
	tree_output_vars["jet_svj_D2"] = a10_lctopojets_D2->at(n_svj);
	tree_output_vars["jet_svj_nTracks"] = a10_lctopojets_nTracks->at(n_svj);

        tree_output_vars["jet_asvj_n"] = n_asvj;
	tree_output_vars["jet_asvj_pt"] = a10_lctopojets_pt->at(n_asvj);
	tree_output_vars["jet_asvj_eta"] = a10_lctopojets_eta->at(n_asvj);
	tree_output_vars["jet_asvj_phi"] = a10_lctopojets_phi->at(n_asvj);
	tree_output_vars["jet_asvj_m"] = a10_lctopojets_m->at(n_asvj);
	tree_output_vars["jet_asvj_mT"] = jet_asvj_mT;
	tree_output_vars["jet_asvj_Split12"] = a10_lctopojets_Split12->at(n_asvj);
	tree_output_vars["jet_asvj_Split23"] = a10_lctopojets_Split23->at(n_asvj);
	tree_output_vars["jet_asvj_tau32"] = a10_lctopojets_tau32_wta->at(n_asvj);
	tree_output_vars["jet_asvj_C2"] = a10_lctopojets_C2->at(n_asvj);
	tree_output_vars["jet_asvj_D2"] = a10_lctopojets_D2->at(n_asvj);
	tree_output_vars["jet_asvj_nTracks"] = a10_lctopojets_nTracks->at(n_asvj);
	*/

	tree_output_vars["jet1_pt"] = a4_pflowjets_pt->at(0); // GeV
	tree_output_vars["jet1_eta"] = a4_pflowjets_eta->at(0);
	tree_output_vars["jet1_phi"] = a4_pflowjets_phi->at(0);
	tree_output_vars["jet1_E"] = a4_pflowjets_E->at(0);
	tree_output_vars["jet1_numConstituents"] = a4_pflowjets_numConstituents->at(0);
	tree_output_vars["jet2_pt"] = a4_pflowjets_pt->at(1);
	tree_output_vars["jet2_eta"] = a4_pflowjets_eta->at(1);
	tree_output_vars["jet2_phi"] = a4_pflowjets_phi->at(1);
	tree_output_vars["jet2_numConstituents"] = a4_pflowjets_numConstituents->at(1);

	tree_output_vars["met_met"] = metFinalClusSumEt;
	tree_output_vars["met_phi"] = metFinalClusPhi;
	tree_output_vars["hT"] = hT;
	tree_output_vars["rT"] = rT;

	tree_output_vars["maxphi_minphi"] = maxphi_minphi;
        tree_output_vars["pt_balance_12"] = pt_balance_12;
        tree_output_vars["mjj_12"] = mjj_12;
        tree_output_vars["mT_jj"] = mT_jj;
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
