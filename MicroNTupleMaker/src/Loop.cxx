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
		if (njet < 2) continue;
		cutflow->Fill(1);      
		
		//jet1_eta preselection
		if (fabs(jet_eta->at(0)) > 2.1) continue;
		cutflow->Fill(2);      
	
                // check DSID
                if (dsid_int != mcChannelNumber) cout << "ERROR: Entry 0 DSID " << dsid_int << " does not match event " << mcEventNumber << "(" << jentry << ") DSID" << mcChannelNumber << endl;
 
		// get svj info 
		vector<pair<int,float>> svj_info; // {{n_svj,dphi_min}, {n_asvj,dphi_max}}
		//vector<pair<int,float>> svj_info_r04;
		svj_info = FindSVJ( jet_phi );
		//svj_info_r04 = FindSVJ( jet_phi );
		
		// apply dphi < 2.0
		//if (svj_info[0].second > 2.0) continue;
		//cutflow->Fill(3);
		
		// assign SVJ variables
		dphi_min = svj_info[0].second;
		dphi_max = svj_info[1].second;

		dphi_min_MET = dphi_min/ metFinalClus;

		//dphi_min_r04 = svj_info_r04[0].second;

		// create relevant 4 vectors
		TLorentzVector v1, v2, v1fat, v2fat;

		// 2 jet situation
		if (njet > 1) {
			v1.SetPtEtaPhiE(jet_pt->at(0), jet_eta->at(0), jet_phi->at(0), jet_E->at(0));
			v2.SetPtEtaPhiE(jet_pt->at(1), jet_eta->at(1), jet_phi->at(1), jet_E->at(1));
			//v_svj.SetPtEtaPhiE(jet_pt->at(n_svj), jet_eta->at(n_svj), jet_phi->at(n_svj), jet_E->at(n_svj));
			//v_asvj.SetPtEtaPhiE(jet_pt->at(n_asvj), jet_eta->at(n_asvj), jet_phi->at(n_asvj), jet_E->at(n_asvj));

			// y* preselection
			deltaY_12 = GetDeltaY(v1,v2);
			if (deltaY_12 > 2.8) continue;
			cutflow->Fill(3);      

			// distance between jets
			dR_12 = GetdR(v1,v2);
			deta_12 = GetDEta(v1.Eta(),v2.Eta());
			//deltaY_sa = GetDeltaY(v_svj,v_asvj);
			
			// svj variablei
			maxphi_minphi = dphi_max - dphi_min;
	
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
                	mT_jj = GetMt(v1,v2,metFinalClus, metFinalClusPhi);

			// -j1_pT -j2_pT
			met_jj_neg = jet_pt->at(0) + jet_pt->at(1);
			mT_jj_neg = GetMtNeg(v1,v2);
			dphi_MET_j1j2 = GetDPhiMET(v1,v2,metFinalClusPhi);

		
			// rT
			rT = metFinalClus / mT_jj;
			
			// event shape variables
			map<string,float> shape_variables = GetShapeVariables(jet_pt, jet_eta, jet_phi, jet_E, true);
			aplanarity = shape_variables["Aplanarity"];
			sphericity = shape_variables["Sphericity"];
			sphericity_T = shape_variables["Transverse_Sphericity"];		
		// 1 jet situation
		} else {
			maxphi_minphi = -999; 
			pt_balance_12 = -999;
			mjj_12 = -999;
			mT_jj = -999;
			mT_jj_neg = -999;
			met_jj_neg = -999;
			dR_12 = -999;
			deta_12 = -999;
			deltaY_12 = -999;
			rT = -999;
			aplanarity = -999;
			sphericity = -999;
			sphericity_T = -999;
		}	

		// 2 fatjet situation
		/*if (nfatjet > 1) {
			//cout << "fat jets" <<endl;
			//cout << "nfatjet: " << nfatjet <<endl;
			//cout << "size fatjet_pt: " << fatjet_pt->size() << endl;
			v1fat.SetPtEtaPhiM(fatjet_pt->at(0), fatjet_eta->at(0), fatjet_phi->at(0), fatjet_m->at(0));
			v2fat.SetPtEtaPhiM(fatjet_pt->at(1), fatjet_eta->at(1), fatjet_phi->at(1), fatjet_m->at(1));
                	mT_JJ = GetMt(v1fat,v2fat,metFinalClus, metFinalClusPhi);
			mJJ_12 = GetMjj(v1fat,v2fat);      
		} else {
			mT_JJ = -999;
			mJJ_12 = -999;	
		}*/
		// HT
		hT = GetHT(jet_pt);
		
		// save output tree
		//cout << "Filling" << endl;
		FillOutputTrees("PostSel");
		finalEntries++;
	}
	cout << "Events passing cutflow: " << finalEntries << endl;

}

