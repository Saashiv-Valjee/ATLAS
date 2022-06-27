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
		// apply nJets >= 2
		if (na10_lctopojets < 2) continue;
		cutflow->Fill(1);      
		
		// apply jet1_pt > 150 GeV
		//if (a10_lctopojets_pt->at(0) < 200000) continue;
		//cutflow->Fill(2);    
		
		// get svj info 
		vector<pair<int,float>> svj_info; // {{n_svj,dphi_min}, {n_asvj,dphi_max}}
		svj_info = FindSVJ();
		
		// apply dphi < 2.0
		//if (svj_info[0].second > 2.0) continue;
		//cutflow->Fill(3);
		
		// assign SVJ variables
		dphi_min = svj_info[0].second;
		dphi_max = svj_info[1].second;
		maxphi_minphi = dphi_max - dphi_min;

		// create relevant 4 vectors
		TLorentzVector v1, v2, v_svj, v_asvj, v1_r04, v2_r04;
		v1.SetPtEtaPhiM(a10_lctopojets_pt->at(0), a10_lctopojets_eta->at(0), a10_lctopojets_phi->at(0), a10_lctopojets_m->at(0));
		v2.SetPtEtaPhiM(a10_lctopojets_pt->at(1), a10_lctopojets_eta->at(1), a10_lctopojets_phi->at(1), a10_lctopojets_m->at(1));
		v_svj.SetPtEtaPhiM(a10_lctopojets_pt->at(n_svj), a10_lctopojets_eta->at(n_svj), a10_lctopojets_phi->at(n_svj), a10_lctopojets_m->at(n_svj));
		v_asvj.SetPtEtaPhiM(a10_lctopojets_pt->at(n_asvj), a10_lctopojets_eta->at(n_asvj), a10_lctopojets_phi->at(n_asvj), a10_lctopojets_m->at(n_asvj));
		v1_r04.SetPtEtaPhiE(a4_pflowjets_pt->at(0), a4_pflowjets_eta->at(0), a4_pflowjets_phi->at(0), a4_pflowjets_E->at(0));
		v2_r04.SetPtEtaPhiE(a4_pflowjets_pt->at(1), a4_pflowjets_eta->at(1), a4_pflowjets_phi->at(1), a4_pflowjets_E->at(1));
			
		// pt balance
		pt_balance_12 = GetPtBalance(v1,v2);
		pt_balance_sa = GetPtBalance(v_svj,v_asvj);
		
		//Mjj
		mjj_12 = GetMjj(v1,v2);      
		mjj_sa = GetMjj(v_svj,v_asvj);      
		mjj_12_r04 = GetMjj(v1_r04, v2_r04);	

		//mT
		jet1_mT = v1.Mt();
		jet2_mT = v2.Mt();
		jet_svj_mT = v_svj.Mt();
		jet_asvj_mT = v_asvj.Mt();
                mT_jj = GetMt(v1,v2,metFinalTrkSumEt, metFinalTrkPhi);
                mT_jj_r04 = GetMt(v1_r04,v2_r04,metFinalTrkSumEt, metFinalTrkPhi);

		// distance between jets
		dR_12 = GetdR(v1,v2);
		deta_12 = GetDEta(v1.Eta(),v2.Eta());
		deltaY_12 = GetDeltaY(v1,v2);
		deltaY_sa = GetDeltaY(v_svj,v_asvj);
		
		// HT
		hT = GetHT(a10_lctopojets_pt);
		hT_r04 = GetHT(a4_pflowjets_pt);

		// rT
		rT = metFinalTrkSumEt / mT_jj;

		// event shape variables
		map<string,float> shape_variables = GetShapeVariables(a10_lctopojets_pt, a10_lctopojets_eta, a10_lctopojets_phi, a10_lctopojets_m);
		aplanarity = shape_variables["Aplanarity"];
		sphericity = shape_variables["Sphericity"];
		sphericity_T = shape_variables["Transverse_Sphericity"];		
		
		// save output tree
		FillOutputTrees("PostSel");
		finalEntries++;
	}
	cout << "Events passing cutflow: " << finalEntries << endl;

}

