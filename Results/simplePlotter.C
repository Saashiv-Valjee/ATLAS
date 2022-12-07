#include "string.h"
#include "TPave.h"
#include <TArrayD.h>
#include <math.h>
#include "PlotParams.h"

//string dir_data = "../MicroNTupleMaker/MicroNTuples/v1.1";
string dir_data = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v5/v5.2";
string outfile_path = "/eos/user/e/ebusch/SVJ/Plots";
Color_t mycolors[12] = { kBlack, kBlue+1, kAzure+7, kGreen+3, kSpring, kRed+1, kOrange-3, kRed, kAzure+7, kOrange };

vector<TH1F*> Get1DHists(vector<string> inputFiles, string branch, PlotParams myParams, string cut){
  // Collect the same 1D histogram from various input files
  vector<TH1F*> hists;
  cout << "Cut: " << cut << endl;
  for (auto inputFile: inputFiles){
    TFile *file_data  = new TFile( Form("%s/%s", dir_data.c_str(), inputFile.c_str() ), "READ");
    TTree *tree0 = (TTree*) file_data->Get("PostSel");
    TH1F* h = new TH1F("h", Form("%s",branch.c_str()), myParams.nbins, myParams.xmin, myParams.xmax);
    tree0->Draw(Form("%s >> h", branch.c_str()), Form("weight*(%s)", cut.c_str()));
    //cout << inputFile << endl;
    //cout << "entries: " << h->GetEntries() << ", integral: " << h->Integral(0,myParams.nbins+1) << endl;
    cout << h->Integral(0,myParams.nbins+1) << endl;
    hists.push_back(h);
  }
  return hists;
}

void Plot1DHists(vector<TH1F*> hists, vector<string> leg_names, string branch){

  TCanvas* canv = new TCanvas(); 
  TLegend *leg;
  if (branch == "jet1_tau32") leg = new TLegend(.01,.6,.4,.98); // upper left
  else if(branch == "pt_balance_21") leg = new TLegend(.1,.1,.3,.3); // bottom left
  else leg = new TLegend(.6,.6,.98,.98); // upper right (default)
  gStyle->SetOptStat(0);

  float max = 0;
  // first loop prepares histograms for plotting
  // NOTE; it's important to get the maximum AFTER normalizing
  for( int i=0; i<hists.size(); i++){
    if( hists[i]->Integral() == 0 ){cout << "No entries for " << leg_names[i] << " " << branch << "; skipping" << endl; continue;}
    //hists[i]->GetYaxis()->SetRangeUser(0.0001,1);
    hists[i]->SetLineColor(mycolors[i]);
    //hists[i]->Scale(1.0/hists[i]->Integral() );
    if (hists[i]->GetMaximum() > max){
	max = hists[i]->GetMaximum();
    }
  }
  // second loop does plotting
  for( int i=0; i<hists.size(); i++){
    hists[i]->SetMaximum(max*1.2); // set Y axis range to be slightly larger than found maximum
    hists[i]->Draw("SAME HIST"); 
    string full_name = Form("%s", leg_names[i].c_str());
    //string full_name = Form("%s (N = %i)", leg_names[i].c_str(), int(hists[i]->GetEntries()));
    leg->AddEntry(hists[i], full_name.c_str() );
  }
  leg->Draw();
  canv->SetLogy();
  canv->SaveAs( Form("%s/%s_unnorm.png", outfile_path.c_str(), branch.c_str()) );
}

void Plot1DHistsRatio(vector<TH1F*> hists, vector<string> leg_names, string branch, int denominator_index){

  TCanvas* canv = new TCanvas("c","c",1200,1600);
  canv->Divide(0,2); 
  TLegend *leg = new TLegend(.73,.6,.98,.98);
  gStyle->SetOptStat(0);

  int d = denominator_index;

  canv->cd(1);

  for( int i=0; i<hists.size(); i++){
    if( hists[i]->Integral() == 0 ){cout << "No entries for " << leg_names[i] << " " << branch << "; skipping" << endl; continue;}

    hists[i]->SetLineColor(mycolors[i]);
    //hists[i]->Scale(1.0/hists[i]->Integral() ); // normalize
    //hists[i]->SetMaximum( hists[i]->GetMaximum()*1.25);
    hists[i]->Draw("SAME HIST"); 
    string full_name = Form("%s (N = %i)", leg_names[i].c_str(), int(hists[i]->GetEntries()));
    leg->AddEntry(hists[i], full_name.c_str());
  }

  canv->cd(2);
  for( int i=0; i<hists.size(); i++){
    if( hists[i]->Integral() == 0 ){cout << "No entries for " << leg_names[i] << " " << branch << "; skipping" << endl; continue;}
    if (i==d) continue;

    TH1F* h = (TH1F*) hists[i]->Clone();
    h->Divide(hists[d]);
    h->GetYaxis()->SetRangeUser(0,2);
    h->Draw("SAME HIST"); 
  }

  canv->cd(1);
  leg->Draw();
  canv->SaveAs( Form("%s/%s_ratio.png", outfile_path.c_str(), branch.c_str()) );
}


void simplePlotter(){

  vector<string> inputFiles = {"user.ebusch.QCDbkg.root", 
				"user.ebusch.515480.root",
				"user.ebusch.515482.root", 
				//"user.ebusch.515487.root", 
				//"user.ebusch.515488.root", 
				//"user.ebusch.515489.root", 
				//"user.ebusch.515490.root", 
				"user.ebusch.515499.root", 
				//"user.ebusch.515500.root", 
				"user.ebusch.515501.root", 
				//"user.ebusch.515502.root", 
				///"user.ebusch.515516.root", 
				//"user.ebusch.515518.root", 
				"user.ebusch.515524.root", 
				//"user.ebusch.515525.root", 
				"user.ebusch.515526.root"};
 
  vector<string> leg_names = {"QCD", "500/ 0.4", "500/ 0.8", "2000/ 0.2", "2000/ 0.6", "6000/ 0.4", "6000/ 0.8"};
  /*
  vector<TH1F*> jet_svj_pt;
  jet_svj_pt = Get1DHists(inputFiles, "jet_svj_pt", P_jet_svj_pt);
  Plot1DHists(jet_svj_pt, leg_names, "jet_svj_pt"); 

  vector<TH1F*> pt_balance;
  pt_balance = Get1DHists(inputFiles, "pt_balance_12", P_pt_balance_12);
  Plot1DHistsRatio(pt_balance, leg_names, "pt_balance",0); 
  */

  string my_cut = "jet1_pt > -900";
  vector<TH1F*> jet1_pt;
  jet1_pt = Get1DHists(inputFiles, "jet1_pt", P_jet1_pt, my_cut);
  //TH1F* full_qcd = (TH1F*) jet1_pt[0]->Clone();
  //TH1F* high = (TH1F*) jet1_pt[1]->Clone();
  //jet1_pt[0]->Add(jet1_pt[1]);
  //vector<TH1F*> jet1_pt_combined;
  //jet1_pt_combined.push_back(jet1_pt[0]);
  //for (int i = 2; i<6; i++) jet1_pt_combined.push_back(jet1_pt[i]);
  Plot1DHists(jet1_pt, leg_names, "jet1_pt"); 

  vector<TH1F*> met_met;
  met_met = Get1DHists(inputFiles, "met_met", P_met_met, my_cut);
  Plot1DHists(met_met, leg_names, "met_met"); 
   
}
