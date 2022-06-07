#include "string.h"
#include "TPave.h"
#include <TArrayD.h>
#include <math.h>
#include "PlotParams.h"

string dir_data = "../MicroNTupleMaker/MicroNTuples/v0.1";
string outfile_path = "/eos/user/e/ebusch/SVJ/Plots";
Color_t mycolors[12] = { kGreen, kBlue, kBlack, kMagenta, kBlack, kCyan, kOrange, kMagenta+1, kAzure+7, kOrange };

vector<TH1F*> Get1DHists(vector<string> inputFiles, string branch, PlotParams myParams){
  // Collect the same 1D histogram from various input files
  vector<TH1F*> hists;
  for (auto inputFile: inputFiles){
    TFile *file_data  = new TFile( Form("%s/%s", dir_data.c_str(), inputFile.c_str() ), "READ");
    TTree *tree0 = (TTree*) file_data->Get("PostSel");
    TH1F* h = new TH1F("h", Form("%s",branch.c_str()), myParams.nbins, myParams.xmin, myParams.xmax);
    tree0->Draw(Form("%s >> h", branch.c_str()));
    cout << "entries: " << h->GetEntries() << ", integral: " << h->Integral() << endl;
    hists.push_back(h);
  }
  return hists;
}

void Plot1DHists(vector<TH1F*> hists, vector<string> leg_names, string branch){

  TCanvas* canv = new TCanvas(); 
  TLegend *leg = new TLegend(.6,.6,.98,.98);


  for( int i=0; i<hists.size(); i++){
    if( hists[i]->Integral() == 0 ){cout << "No entries for " << leg_names[i] << " " << branch << "; skipping" << endl; continue;}
    hists[i]->GetYaxis()->SetRangeUser(0.0001,1);
    hists[i]->SetLineColor(mycolors[i]);
    //hists[i]->Scale(1.0/hists[i]->Integral() );
    hists[i]->SetMaximum( hists[i]->GetMaximum()*1.25);
    hists[i]->Draw("SAME HIST"); 
    string full_name = Form("%s (N = %i)", leg_names[i].c_str(), h->GetEntries());
    leg->AddEntry(hists[i],full_name[i].c_str());
  }
  leg->Draw();
  canv->SaveAs( Form("%s/%s.png", outfile_path.c_str(), branch.c_str()) );
}

void simplePlotter(){

  vector<string> inputFiles = {"user.ebusch.508547.root", "user.ebusch.508548.root", "user.ebusch.508549.root", "user.ebusch.508550.root"};
  vector<string> leg_names = {"Z': 1500, r: 0.8", "Z': 1500, r: 0.3", "Z': 750, r: 0.8", "Z': 750, r: 0.3"};

  vector<TH1F*> jet_svj_pt;
  Jet1Pt_hists = Get1DHists(inputFiles, "jet_svj_pt", P_jet_svj_pt);
  Plot1DHists(jet_svj_pt, leg_names, "jet_svj_pt"); 

  vector<TH1F*> pt_balance;
  Jet1Pt_hists = Get1DHists(inputFiles, "pt_balance", P_pt_balance);
  Plot1DHists(pt_balance, leg_names, "pt_balance"); 

  vector<TH1F*> dPhi_min;
  Jet1Pt_hists = Get1DHists(inputFiles, "dphi_min", P_dphi_min);
  Plot1DHists(dPhi_min, leg_names, "dphi_min"); 

   
}
