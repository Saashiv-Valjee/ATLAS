/* ====================================================================================================================== */
double MicroNTupleMaker::GetGeneratorFilterEff(string dsid){

        double my_gfe = 0.0;

	// Cross section in nb
	map<string, double> gfe;
	// Multijet
	gfe["364702"] = 
	gfe["364703"] = 
	gfe["364704"] = 
	gfe["364705"] = 
	gfe["364706"] = 
	gfe["364707"] = 
	gfe["364708"] = 
	gfe["364709"] = 
	gfe["364710"] = 
	gfe["364711"] =  
	gfe["364712"] = 

	// Signal
	gfe["508547"] = 
	gfe["508548"] = 
	gfe["508549"] = 
	gfe["508550"] = 
	
        map<string, double>::iterator iter = xs.find(dsid);
	if (iter != xs.end()) my_xs = xs[dsid];
	else cout << "ERROR: No XSection info found for DSID " << dsid << endl;

	return my_xs;

}

/* ====================================================================================================================== */
double MicroNTupleMaker::GetSignalBRxSigma(string dsid){

        double my_xs = 0.0;

	// Cross section in nb
	map<string, double> xs;
	// Multijet
	xs["364702"] = 2.43e6; 
	xs["364703"] = 2.65e4;
	xs["364704"] = 2.55e2;
	xs["364705"] = 4.55e0;
	xs["364706"] = 2.58e-1;
	xs["364707"] = 1.62e-2;
	xs["364708"] = 6.25e-4;
	xs["364709"] = 1.96e-5;
	xs["364710"] = 1.2e-6;
	xs["364711"] = 4.23e-8;  
	xs["364712"] = 1.04e-9;

	// Signal
	xs["508547"] = 3.95e-4
	xs["508548"] = 3.95e-4
	xs["508549"] = 7.37e-3
	xs["508550"] = 7.37e-3
	
        map<string, double>::iterator iter = xs.find(dsid);
	if (iter != xs.end()) my_xs = xs[dsid];
	else cout << "ERROR: No XSection info found for DSID " << dsid << endl;

	return my_xs;

}
