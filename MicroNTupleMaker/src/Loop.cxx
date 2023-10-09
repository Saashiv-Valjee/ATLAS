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
		
                // check DSID
                if (dsid_int != mcChannelNumber) cout << "ERROR: Entry 0 DSID " << dsid_int << " does not match event " << mcEventNumber << "(" << jentry << ") DSID" << mcChannelNumber << endl;

		// create relevant 4 vectors
		TLorentzVector v1, v2, met_v;

		// MET preselection
		if(metFinalClus < 70) continue;
		cutflow->Fill(16);
		cutflow_weighted->Fill(16,mcEventWeight);
                
		v1.SetPtEtaPhiE(jet_pt->at(0), jet_eta->at(0), jet_phi->at(0), jet_E->at(0));
		v2.SetPtEtaPhiE(jet_pt->at(1), jet_eta->at(1), jet_phi->at(1), jet_E->at(1));
		//v_svj.SetPtEtaPhiE(jet_pt->at(n_svj), jet_eta->at(n_svj), jet_phi->at(n_svj), jet_E->at(n_svj));
		//v_asvj.SetPtEtaPhiE(jet_pt->at(n_asvj), jet_eta->at(n_asvj), jet_phi->at(n_asvj), jet_E->at(n_asvj));
		met_v.SetPtEtaPhiM(metFinalClus,0,metFinalClusPhi,0.0);

		// y* preselection
		deltaY_12 = GetDeltaY(v1,v2);
                float dPhi1 = GetDPhi(v1,met_v);
                float dPhi2 = GetDPhi(v2,met_v);
		dphi_min = min(dPhi1,dPhi2);		
		dphi_max = max(dPhi1,dPhi2);		
		// svj variablei
		maxphi_minphi = dphi_max - dphi_min;

		// distance between jets
		dR_12 = GetdR(v1,v2);
		deta_12 = GetDEta(v1.Eta(),v2.Eta());
        	dphi_12 = GetDPhi(v1,v2);
	
		// pt balance
		pt_balance_12 = GetPtBalance(v1,v2);
	
		//mT
                mT_jj = GetMt(v1,v2,met_v);

		// -j1_pT -j2_pT
		met_jj_neg = jet_pt->at(0) + jet_pt->at(1);
		mT_jj_neg = GetMtNeg(v1,v2);
		//dphi_MET_j1j2 = GetDPhiMET(v1,v2,met_v);

		// rT
		rT = metFinalClus / mT_jj;
		
		// save output tree
		//cout << "Filling" << endl;
		FillOutputTrees("PostSel");
		finalEntries++;
	}
	cout << "Events passing cutflow: " << finalEntries << endl;

}

