/* =============================================================================================== */
void MicroNTupleMaker::DeclareOutputTrees(){
	treenames = {"PostSel"};

	vector<string> myvars = {
        	 
		// -- EventLevel -- //
		"runNumber", "eventNumber","mcEventWeight","weight","sumw",

		// -- JetLevel -- //
		"n_jets",
        	"jet1_pt", "jet1_eta", "jet1_phi", "jet1_E", 
        	"jet2_pt", "jet2_eta", "jet2_phi", "jet2_E", 
		"jet1_Width", "jet2_Width",

		// -- MET -- //
        	"met_met", "met_phi",

		// -- Jet Calculations -- //
                "mT_jj", "mT_jj_neg", "met_jj_neg",
		"rT",
		"maxphi_minphi", "dphi_min", "dphi_max",
                "pt_balance_12", 
		"dR_12", "deta_12", "dphi_12",
		"deltaY_12"
        };

	vector<string> myvars_string = {
		"year"
	};
	
	vector<string> myvars_vector = {
		"jet0_GhostTrack_pt", "jet0_GhostTrack_eta", "jet0_GhostTrack_phi", "jet0_GhostTrack_e", "jet0_GhostTrack_d0", "jet0_GhostTrack_z0", "jet0_GhostTrack_qOverP",
		"jet1_GhostTrack_pt", "jet1_GhostTrack_eta", "jet1_GhostTrack_phi", "jet1_GhostTrack_e", "jet1_GhostTrack_d0", "jet1_GhostTrack_z0", "jet1_GhostTrack_qOverP"
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

	tree_output_vars_vector["jet0_GhostTrack_pt"] = &jet_GhostTrack_pt->at(0);
	tree_output_vars_vector["jet0_GhostTrack_eta"] = &jet_GhostTrack_eta->at(0);
	tree_output_vars_vector["jet0_GhostTrack_phi"] = &jet_GhostTrack_phi->at(0);
	tree_output_vars_vector["jet0_GhostTrack_e"] = &jet_GhostTrack_e->at(0);
	tree_output_vars_vector["jet0_GhostTrack_d0"] = &jet_GhostTrack_d0->at(0);
	tree_output_vars_vector["jet0_GhostTrack_z0"] = &jet_GhostTrack_z0->at(0);
	tree_output_vars_vector["jet0_GhostTrack_qOverP"] = &jet_GhostTrack_qOverP->at(0);
	tree_output_vars_vector["jet1_GhostTrack_pt"] = &jet_GhostTrack_pt->at(1);
	tree_output_vars_vector["jet1_GhostTrack_eta"] = &jet_GhostTrack_eta->at(1);
	tree_output_vars_vector["jet1_GhostTrack_phi"] = &jet_GhostTrack_phi->at(1);
	tree_output_vars_vector["jet1_GhostTrack_e"] = &jet_GhostTrack_e->at(1);
	tree_output_vars_vector["jet1_GhostTrack_d0"] = &jet_GhostTrack_d0->at(1);
	tree_output_vars_vector["jet1_GhostTrack_z0"] = &jet_GhostTrack_z0->at(1);
	tree_output_vars_vector["jet1_GhostTrack_qOverP"] = &jet_GhostTrack_qOverP->at(1);
	
	tree_output_vars["runNumber"] = runNumber;
	tree_output_vars["eventNumber"] = eventNumber;
	tree_output_vars["mcEventWeight"] = mcEventWeight;
	tree_output_vars["weight"] = mcEventWeight*weight_scale;
	tree_output_vars["sumw"] = sumw;

	tree_output_vars["n_jets"] = njet;
	tree_output_vars["jet1_pt"] = jet_pt->at(0); // GeV
	tree_output_vars["jet1_eta"] = jet_eta->at(0);
	tree_output_vars["jet1_phi"] = jet_phi->at(0);
	tree_output_vars["jet1_E"] = jet_E->at(0);
	tree_output_vars["jet1_Width"] = jet_Width->at(0);

	tree_output_vars["jet2_pt"] = jet_pt->at(1);
	tree_output_vars["jet2_eta"] = jet_eta->at(1);
	tree_output_vars["jet2_phi"] = jet_phi->at(1);
	tree_output_vars["jet2_E"] = jet_E->at(1);
	tree_output_vars["jet2_Width"] = jet_Width->at(1);

	tree_output_vars["met_met"] = metFinalClus;
        tree_output_vars["met_phi"] = metFinalClusPhi;

        tree_output_vars["mT_jj"] = mT_jj;
        tree_output_vars["mT_jj_neg"] = mT_jj_neg;
        tree_output_vars["met_jj_neg"] = met_jj_neg;

	tree_output_vars["rT"] = rT;
	tree_output_vars["maxphi_minphi"] = maxphi_minphi;
	tree_output_vars["pt_balance_12"] = pt_balance_12;	
	tree_output_vars["dR_12"] = dR_12;
	tree_output_vars["deta_12"] = deta_12;
        tree_output_vars["deltaY_12"] = deltaY_12;
        tree_output_vars["dphi_12"] = dphi_12;
	tree_output_vars["dphi_min"] = dphi_min;
	tree_output_vars["dphi_max"] = dphi_max;

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
