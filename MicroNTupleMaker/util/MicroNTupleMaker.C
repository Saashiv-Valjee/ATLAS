#define MicroNTupleMaker_cxx

using namespace std;

#include "../MicroNTupleMaker/MicroNTupleMaker.h"
#include "../src/FunctionHelper.cxx"
#include "../src/OutputTreeHelper.cxx"
#include "../src/HistHelper.cxx"
#include "../src/WeightHelper.cxx"
#include "../src/Loop.cxx"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using filesystem::directory_iterator;

void MicroNTupleMaker(string infiletag = "", bool local = false, string infilepath = ""){
	
	// Check for infile //
	
	string fullinfilepath;
	
	// Running remotely
	if( !local ) { // Path from base dir -- when ONLY file tag is provided
	        fullinfilepath = infiletag;
		
		/*
	        // Local & global paths
	        TString infilepath_local = "../" + tmp_infilepath;
	        TString infilepath_global1  = "/afs/cern.ch/work/e/ebusch/public/SVJ/analysisTop/"+tmp_infilepath; // for files on lxplus
	
	        if( !gSystem->AccessPathName(infilepath_local) ) // Look locally
	                fullinfilepath = infilepath_local;
	        else if( !gSystem->AccessPathName(infilepath_global1) ) // Then look globally on lxplus
	                fullinfilepath = infilepath_global1;
	        else {
	                cout<<"ERROR: could not find input file, exiting program. Checked the following file paths:"<<endl;
	                cout<<infilepath_local<<endl;
	                cout<<infilepath_global1<<endl;
	                return;
	        }
		*/
 	// Running locally - must provide path to inputs and true flag
	} else {
		fullinfilepath = infilepath + infiletag;
	}
	
	// ----- Read in File(s) & Tree ----- // 
	
	cout<<"Reading in "<<fullinfilepath<<endl;
	
	TChain *fChain = new TChain("outTree");
	TH1F *metadata;
	
	if ( !local ){
		
		TString path_tstring = Form("%s", fullinfilepath.c_str());
		fChain->Add(path_tstring);
	} else {
		int file_count = 0;
		for (const auto & entry : directory_iterator(fullinfilepath)){
			file_count++;
 			TString path_string = Form("%s",entry.path().string().c_str());
			fChain->Add(path_string);
			TFile *f = new TFile( path_string, "READ");
			TH1F* h = (TH1F*) f->Get("MetaData_EventCount");
			if (file_count ==1){metadata = (TH1F*) h->Clone(); metadata->SetDirectory(0);} 
			else metadata->Add(h);
			cout << "h sumW: " << h->GetBinContent(3) << endl;
			f->Close();
			cout << "metadata sumW: " << metadata->GetBinContent(3) << endl;
		}
		cout << "Added " << file_count << " files to the chain" << endl;
	}

	// Create output file
	string dsid = "";
        if (local) dsid = infiletag.substr(12,6);
	cout << "DSID: " << dsid << endl;

	string outfiletag="";
	string mc = "";
	if (infiletag.find("mc16a") != string::npos) mc = "mc16a";
	if (infiletag.find("mc16d") != string::npos) mc = "mc16d";
	if (infiletag.find("mc16e") != string::npos) mc = "mc16e";
	outfiletag = "user.ebusch." + dsid + "." + mc;
        TString outfilename;
     
	if (local) outfilename = Form( "MicroNTuples/%s.root", outfiletag.c_str() );
	else outfilename = "output.root";

	TFile *fout = new TFile( outfilename, "RECREATE" );	
	cout << "Will write to "<<outfilename<<endl;

        // Weight from Metadata histogram
        //cout << "Nbins: " << metadata->GetNbinsX() << endl;
        double sumWInput = metadata->GetBinContent(3);

        cout << "Declaring class" <<endl;
	// Class instance
	class MicroNTupleMaker myMaker(fChain);
	
        myMaker.year_mc = mc;
	myMaker.SetWeight(sumWInput);

	myMaker.DeclareHistograms();
	myMaker.DeclareOutputTrees();
	myMaker.Loop();
	myMaker.WriteOutputTrees();
	myMaker.WriteHistograms();
}

int main(int argc, char** argv){

  int Nargs = argc;

  if( Nargs == 2 )
        MicroNTupleMaker( argv[1], false, "" );
  else if (Nargs == 4)
        MicroNTupleMaker( argv[1], argv[2], argv[3] );
  else
        cout<<"ERROR: Not enough arguments!"<<endl;

}

