#define MicroNTupleMaker_cxx

using namespace std;

#include "../MicroNTupleMaker/MicroNTupleMaker.h"
#include "../src/FunctionHelper.cxx"
#include "../src/OutputTreeHelper.cxx"
#include "../src/HistHelper.cxx"
#include "../src/Loop.cxx"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using filesystem::directory_iterator;

void MicroNTupleMaker(string infiletag = "", string infilepath = ""){
	
	// Check for infile //
	
	string fullinfilepath;
	
	if( infilepath == "" ) { // Path from base dir -- when ONLY file tag is provided
	        string tmp_infilepath = "run/"+infiletag+".root";
	
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
	} else {
		fullinfilepath = infilepath + infiletag;
	}
	
	// ----- Read in File(s) & Tree ----- // 
	
	cout<<"Reading in "<<fullinfilepath<<endl;
	
	TChain *fChain = new TChain("outTree/nominal");

	if (infilepath == ""){
		
		TString path_tstring = Form("%s", fullinfilepath.c_str());
		fChain->Add(path_tstring);
	} else {
		int file_count = 0;
		for (const auto & entry : directory_iterator(fullinfilepath)){
			file_count++;
 			TString path_string = Form("%s",entry.path().string().c_str());
			cout << path_string << endl;
			fChain->Add(path_string);
		}
		cout << "Added " << file_count << " files to the chain" << endl;
	}
	// Create output file
	TString outfilename = Form( "MicroNTuples/%s.root", infiletag.c_str() );
	TFile *fout = new TFile( outfilename, "RECREATE" );
	
	
	// Class instance
	class MicroNTupleMaker myMaker(fChain);
	
	myMaker.DeclareHistograms();
	myMaker.DeclareOutputTrees();
	myMaker.Loop();
	myMaker.WriteOutputTrees();
	myMaker.WriteHistograms();
}

int main(int argc, char** argv){

  int Nargs = argc;

  if( Nargs == 2 )
        MicroNTupleMaker( argv[1], "" );
  else if (Nargs == 3)
        MicroNTupleMaker( argv[1], argv[2]);
  else
        cout<<"ERROR: Not enough arguments!"<<endl;

}

