/* =================================================================== */
float MicroNTupleMaker::GetDPhi(float phi1, float phi2){
    float dPhi = phi1 - phi1;
    if(dPhi > 3.14)  dPhi -= 2*3.14;
    if(dPhi < -3.14) dPhi += 2*3.14;
    return dPhi;
}

/* =================================================================== */
vector<pair<int,float>> MicroNTupleMaker::FindSVJ(){

  	float maxphi = 0;
  	float minphi = 10; 
        n_asvj = 0;
        n_svj = 0;
        vector<pair<int,float>> jet_info;
        pair<int,float> svj_info;
        pair<int,float> asvj_info; 
	for (int i =0; i<a10_lctopojets_phi->size(); i++) {
    		float dPhi = GetDPhi(a10_lctopojets_phi->at(i),metFinalTrkPhi);
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
	
}

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
float MicroNTupleMaker::GetMt(TLorentzVector v1, TLorentzVector v2, float met, float met_phi){
  TLorentzVector jj = v1 + v2;
  float dphi = GetDPhi(jj.Phi(), met_phi); 
  float mT2 = pow(jj.M(),2) + 2*met*(sqrt( pow(jj.M(),2) + pow(jj.Pt(),2) ) - jj.Pt()*cos(dphi));
  return sqrt(mT2);
}
