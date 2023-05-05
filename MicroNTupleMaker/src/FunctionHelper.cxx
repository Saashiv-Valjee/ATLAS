/* =================================================================== */
float MicroNTupleMaker::GetDEta(float eta1, float eta2){
	return fabs(eta1-eta2);
}

/* =================================================================== */
float MicroNTupleMaker::GetDPhi(TLorentzVector v1, TLorentzVector v2){ 
    return fabs(v1.DeltaPhi(v2));
}

/* =================================================================== */
float MicroNTupleMaker::GetDPhiMET(TLorentzVector v1, TLorentzVector v2, TLorentzVector met){
	TLorentzVector v12;
	v12 = -v1-v2;
	float dPhi = GetDPhi(v12, met);
	return dPhi;
}

/* =================================================================== */
/*vector<pair<int,float>> MicroNTupleMaker::FindSVJ( vector<float> *jet_phi ){

  	float maxphi = 0;
  	float minphi = 10; 
        n_asvj = 0;
        n_svj = 0;
        vector<pair<int,float>> jet_info;
        pair<int,float> svj_info;
        pair<int,float> asvj_info; 
	//for (int i =0; i<jet_phi->size(); i++) {
	for (int i =0; i<2; i++) {
    		float dPhi = GetDPhi(jet_phi->at(i),metFinalClusPhi);
    		if (fabs(dPhi) > maxphi){maxphi = fabs(dPhi); n_asvj = i;}
    		if (fabs(dPhi) < minphi){minphi = fabs(dPhi); n_svj = i;}
 	}
        svj_info.first = n_svj;
        svj_info.second = minphi;
        asvj_info.first = n_asvj;
        asvj_info.second = maxphi;
        jet_info.push_back(svj_info);
        jet_info.push_back(asvj_info);
	return jet_info;
	
}*/

/* =================================================================== */
float MicroNTupleMaker::GetPtBalance(TLorentzVector v1, TLorentzVector v2){
	float pt_balance;
	TLorentzVector v12;
	v12 = v1 + v2;
	pt_balance = v12.Pt() / (v1.Pt() + v2.Pt()); 
	return pt_balance;
}

/* =================================================================== */
float MicroNTupleMaker::GetMjj(TLorentzVector v1, TLorentzVector v2){
  	TLorentzVector v12;
  	v12 = v1 + v2;
  	return v12.M();
}

/* =================================================================== */
float MicroNTupleMaker::GetDeltaY(TLorentzVector v1, TLorentzVector v2){
  	return fabs(v1.Rapidity() - v2.Rapidity());
}

/* =================================================================== */
float MicroNTupleMaker::GetMt(TLorentzVector v1, TLorentzVector v2, TLorentzVector met_v){
 	TLorentzVector jj = v1 + v2;
 	float dijetEt = sqrt(pow(jj.M(),2) + pow(jj.Pt(),2));
	float mT2 = pow(dijetEt + met_v.Et(),2) - pow((jj+met_v).Pt(),2);	
 	return sqrt(mT2);
}

/* =================================================================== */
float MicroNTupleMaker::GetMtNeg(TLorentzVector v1, TLorentzVector v2){
 	TLorentzVector jj = v1 + v2;
	TLorentzVector met_v_temp;
	TLorentzVector met_v;
	met_v_temp.SetPtEtaPhiM(jj.Pt(),0,jj.Phi(),0.0);
	met_v = -met_v_temp;
 	float dijetEt = sqrt(pow(jj.M(),2) + pow(jj.Pt(),2));
	float mT2 = pow(dijetEt + met_v.Et(),2) - pow((jj+met_v).Pt(),2);	
 	return sqrt(mT2);
}

/* =================================================================== */
float MicroNTupleMaker::GetHT(vector<float> *jet_pt){
        float ht = 0;
	for(int i=0; i<jet_pt->size(); i++) ht += jet_pt->at(i);	
	return ht;
}

/* =================================================================== */
float MicroNTupleMaker::GetdR(TLorentzVector v1, TLorentzVector v2){
	return v1.DeltaR(v2);
}

/* =================================================================== */
map<string,float> MicroNTupleMaker::GetShapeVariables(vector<float> *jet_pt, vector<float> *jet_eta, vector<float> *jet_phi, vector<float> *jet_m, bool smallR){

	map<string,float> shape_variables;
	shape_variables["Sphericity"] = -999;
	shape_variables["Aplanarity"] = -999;
	shape_variables["Transverse_Sphericity"] = -999;

	TMatrixD MomentumTensor(3,3);
	float P2Sum = 0;

	// TODO - need to boost to center of mass?
 	for (int i = 0; i < jet_pt->size(); i++){
		TLorentzVector v;
		if (smallR) v.SetPtEtaPhiE(jet_pt->at(i), jet_eta->at(i), jet_phi->at(i), jet_m->at(i));
		else v.SetPtEtaPhiM(jet_pt->at(i), jet_eta->at(i), jet_phi->at(i), jet_m->at(i));
		MomentumTensor(0,0) += v.Px()*v.Px();
		MomentumTensor(0,1) += v.Px()*v.Py();
		MomentumTensor(0,2) += v.Px()*v.Pz();
		MomentumTensor(1,0) += v.Py()*v.Px();
		MomentumTensor(1,1) += v.Py()*v.Py();
		MomentumTensor(1,2) += v.Py()*v.Pz();
		MomentumTensor(2,0) += v.Pz()*v.Px();
		MomentumTensor(2,1) += v.Pz()*v.Py();
		MomentumTensor(2,2) += v.Pz()*v.Pz();
		P2Sum += v.Px()*v.Px() + v.Py()*v.Py() + v.Pz()*v.Pz();
	}

	if (P2Sum > 0){
    		for(int i=0; i<3; i++) {
      			for(int j=0; j<3; j++) {
        			MomentumTensor(i,j) /= P2Sum;
      			}
    		}
		TDecompSVD * aSVD = new TDecompSVD(MomentumTensor);
		TVectorD Lambda = aSVD->GetSig();

		if (Lambda[0] < Lambda[1] || Lambda[1] < Lambda[2]) cout << "eigenvalues must be sorted" << endl;
	
		shape_variables["Aplanarity"] = 1.5*Lambda[2];	
		shape_variables["Sphericity"] = 1.5*(Lambda[1]+Lambda[2]);
		shape_variables["Transverse_Sphericity"] = (2*Lambda[1]) / (Lambda[0]+Lambda[1]);
	}else{
		cout << "P2Sum not > 0" << endl;
	}

	return shape_variables;

}
