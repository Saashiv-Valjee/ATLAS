void MicroNTupleMaker::Loop()
{
//   In a ROOT session, you can do:
//      root> .L MicroNTupleMaker.C
//      root> MicroNTupleMaker t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntries();
	
	cout << "Initial events: " << nentries << endl;
	int finalEntries = 0;
	int processedEntries = 0;
	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		processedEntries++;
		
		if (processedEntries % 10000 == 0 && nentries <= 2000000) cout << "Processed " << processedEntries << " events..." << endl;
		if (processedEntries % 100000 == 0 && nentries > 2000000) cout << "Processed " << processedEntries << " events..." << endl;
		
		cutflow->Fill(0);
	
		// apply nSmallRJets >=2 (required for code to run) 	
		if (na4_pflowjets < 2) continue;
		cutflow->Fill(1);      
		
		// apply MET > 200 GeV
		if (metFinalClusSumEt < 200) continue;
		cutflow->Fill(2);      

		// apply jet1_pt > 125 GeV
		if (a4_pflowjets_pt->at(0) < 150) continue;
		cutflow->Fill(3);      

		// apply fabs(jet1_eta) < 2.8 GeV
		if (fabs(a4_pflowjets_eta->at(0)) > 2.8) continue;
		cutflow->Fill(4);      
		
                // check DSID
                if (dsid_int != mcChannelNumber) cout << "ERROR: Entry 0 DSID " << dsid_int << " does not match event " << mcEventNumber << "(" << jentry << ") DSID" << mcChannelNumber << endl;
 
		// get svj info 
		vector<pair<int,float>> svj_info; // {{n_svj,dphi_min}, {n_asvj,dphi_max}}
		vector<pair<int,float>> svj_info_r04;
		svj_info = FindSVJ( a4_pflowjets_phi );
		//svj_info_r04 = FindSVJ( a4_pflowjets_phi );
		
		// apply dphi < 2.0
		//if (svj_info[0].second > 2.0) continue;
		//cutflow->Fill(3);
		
		// assign SVJ variables
		dphi_min = svj_info[0].second;
		dphi_max = svj_info[1].second;
		maxphi_minphi = dphi_max - dphi_min;

		//dphi_min_r04 = svj_info_r04[0].second;

		// create relevant 4 vectors
		TLorentzVector v1, v2, v_svj, v_asvj, v1_r04, v2_r04;
		v1.SetPtEtaPhiE(a4_pflowjets_pt->at(0), a4_pflowjets_eta->at(0), a4_pflowjets_phi->at(0), a4_pflowjets_E->at(0));
		v2.SetPtEtaPhiE(a4_pflowjets_pt->at(1), a4_pflowjets_eta->at(1), a4_pflowjets_phi->at(1), a4_pflowjets_E->at(1));
		v_svj.SetPtEtaPhiE(a4_pflowjets_pt->at(n_svj), a4_pflowjets_eta->at(n_svj), a4_pflowjets_phi->at(n_svj), a4_pflowjets_E->at(n_svj));
		v_asvj.SetPtEtaPhiE(a4_pflowjets_pt->at(n_asvj), a4_pflowjets_eta->at(n_asvj), a4_pflowjets_phi->at(n_asvj), a4_pflowjets_E->at(n_asvj));
			
		// pt balance
		pt_balance_12 = GetPtBalance(v1,v2);
		//pt_balance_sa = GetPtBalance(v_svj,v_asvj);
		
		//Mjj
		mjj_12 = GetMjj(v1,v2);      
		//mjj_sa = GetMjj(v_svj,v_asvj);      

		//mT
		//jet1_mT = v1.Mt();
		//jet2_mT = v2.Mt();
		//jet_svj_mT = v_svj.Mt();
		//jet_asvj_mT = v_asvj.Mt();
                mT_jj = GetMt(v1,v2,metFinalClusSumEt, metFinalClusPhi);

		// distance between jets
		dR_12 = GetdR(v1,v2);
		deta_12 = GetDEta(v1.Eta(),v2.Eta());
		deltaY_12 = GetDeltaY(v1,v2);
		//deltaY_sa = GetDeltaY(v_svj,v_asvj);
		
		// HT
		hT = GetHT(a4_pflowjets_pt);

		// rT
		rT = metFinalClusSumEt / mT_jj;

		// event shape variables
		map<string,float> shape_variables = GetShapeVariables(a4_pflowjets_pt, a4_pflowjets_eta, a4_pflowjets_phi, a4_pflowjets_E, true);
		aplanarity = shape_variables["Aplanarity"];
		sphericity = shape_variables["Sphericity"];
		sphericity_T = shape_variables["Transverse_Sphericity"];		
		
		// save output tree
		FillOutputTrees("PostSel");
		finalEntries++;
	}
	cout << "Events passing cutflow: " << finalEntries << endl;

}

