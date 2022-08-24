/* ====================================================================================================================== */
void MicroNTupleMaker::SetWeight(string dsid){

	sumw = GetSumW(dsid);
	double gfe = GetGenFilterEff(dsid);
	double xs = GetXSection(dsid);

	weight_scale = xs*gfe/sumw;
}

/* ====================================================================================================================== */
double MicroNTupleMaker::GetSumW(string dsid){

	// Eventually: read from cutflow table
	// Temp solution: input by hand
	
        double my_sumw = 0.0;

	// Cross section in nb
	map<string, double> sumw;
	// Multijet
	sumw["364702"] = 121027;       
	sumw["364703"] = 4772.79;
	sumw["364704"] = 107.418;
	sumw["364705"] = 3.00517;
	sumw["364706"] = 0.0889688;
	sumw["364707"] = 0.0122396;
	sumw["364708"] = 0.00354308;
	sumw["364709"] = 0.000661628;
	sumw["364710"] = 7.54144e-05;
	sumw["364711"] = 4.15448e-05;
	sumw["364712"] = 2.41811e-05;

	// Signal
	sumw["508547"] = 52946.2;       
	sumw["508548"] = 51757.8;     
	sumw["508549"] = 995391;       
	sumw["508550"] = 1.01754e+06;  
	
        map<string, double>::iterator iter = sumw.find(dsid);
	if (iter != sumw.end()) my_sumw = sumw[dsid];
	else cout << "ERROR: No SumW info found for DSID " << dsid << endl;

	return my_sumw;

}

/* ====================================================================================================================== */
double MicroNTupleMaker::GetGenFilterEff(string dsid){

        double my_gfe = 0.0;

	// Cross section in nb
	map<string, double> gfe;
	// Multijet
	gfe["364702"] = 9.86e-3; 
	gfe["364703"] = 1.17e-2;
	gfe["364704"] = 1.34e-2;
	gfe["364705"] = 1.45e-2;
	gfe["364706"] = 9.47e-3;
	gfe["364707"] = 1.11e-2;
	gfe["364708"] = 1.02e-2;
	gfe["364709"] = 1.21e-2;
	gfe["364710"] = 5.89e-3;
	gfe["364711"] = 2.67e-3;
	gfe["364712"] = 4.29e-4;

	// Signal
	gfe["508547"] = 1.0; 
	gfe["508548"] = 1.0;
	gfe["508549"] = 1.0;
	gfe["508550"] = 1.0;
	
        map<string, double>::iterator iter = gfe.find(dsid);
	if (iter != gfe.end()) my_gfe = gfe[dsid];
	else cout << "ERROR: No GenFilterEff info found for DSID " << dsid << endl;

	return my_gfe;

}

/* ====================================================================================================================== */
double MicroNTupleMaker::GetXSection(string dsid){

        double my_xs = 0.0;

	// Cross section in nb
	map<string, double> xs;
	// Multijet
	xs["364702"] = 2.43e+6; 
	xs["364703"] = 2.65e+4;
	xs["364704"] = 2.55e+2;
	xs["364705"] = 4.55e0;
	xs["364706"] = 2.58e-1;
	xs["364707"] = 1.62e-2;
	xs["364708"] = 6.25e-4;
	xs["364709"] = 1.96e-5;
	xs["364710"] = 1.2e-6;
	xs["364711"] = 4.23e-8;  
	xs["364712"] = 1.04e-9;

	// Signal
	xs["508547"] = 3.95e-4;
	xs["508548"] = 3.95e-4;
	xs["508549"] = 7.37e-3;
	xs["508550"] = 7.37e-3;
	
        map<string, double>::iterator iter = xs.find(dsid);
	if (iter != xs.end()) my_xs = xs[dsid];
	else cout << "ERROR: No XSection info found for DSID " << dsid << endl;

	return my_xs;

}
