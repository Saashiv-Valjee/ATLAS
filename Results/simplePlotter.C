#include "string.h"
#include "TPave.h"
#include <TArrayD.h>
#include <math.h>
#include "PlotParams.h"

//string dir_data = "../MicroNTupleMaker/MicroNTuples/v1.1";
string dir_data = "/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v5/v5.2";
string outfile_path = "/eos/user/e/ebusch/SVJ/Plots";
Color_t mycolors[12] = { kBlack, kGray+2, kBlue+1, kAzure+7, kGreen+3, kSpring, kRed+1, kOrange+7, kRed, kAzure+7, kOrange };
string cout_dict[25] = {"\n,", ",", ",", "\n", ",,", ",", "\n", ",", ",", ",", "\n", ",", ",,", "\n", ",", ",", ",", "\n", ",,,", "\n,", ",,", "\n,", ",", ",", "\n"}; 

vector<TH1D*> Get1DHists(vector<string> inputFiles, string branch, PlotParams myParams, string cut){
  // Collect the same 1D histogram from various input files
  vector<TH1D*> hists;
  cout << "\n" <<"Cut: " << cut << endl;
  int i=0;
  for (auto inputFile: inputFiles){
    TFile *file_data  = new TFile( Form("%s/%s", dir_data.c_str(), inputFile.c_str() ), "READ");
    TTree *tree0 = (TTree*) file_data->Get("PostSel");
    TH1D* h = new TH1D("h", Form("%s",branch.c_str()), myParams.nbins, myParams.xmin, myParams.xmax);
    tree0->Draw(Form("%s >> h", branch.c_str()), Form("weight*(%s)", cut.c_str()));
    //cout << inputFile << endl;
    //cout << "entries: " << h->GetEntries() << ", integral: " << h->Integral(0,myParams.nbins+1) << endl;
    cout << h->Integral(0,myParams.nbins+1);
    cout << cout_dict[i];
    i++;
    hists.push_back(h);
  }
  return hists;
}

void Plot1DHists(vector<TH1D*> hists, vector<string> leg_names, string branch){

  TCanvas* canv = new TCanvas("c", "c", 800, 600); 
  TLegend *leg;
  if (branch == "jet1_tau32") leg = new TLegend(.01,.6,.4,.98); // upper left
  else if(branch == "pt_balance_21") leg = new TLegend(.1,.1,.3,.3); // bottom left
  else leg = new TLegend(.6,.6,.98,.98); // upper right (default)
  gStyle->SetOptStat(0);

  float max = 0;
  vector<double> nEvents;
  // first loop prepares histograms for plotting
  // NOTE; it's important to get the maximum AFTER normalizing
  for( int i=0; i<hists.size(); i++){
    if( hists[i]->Integral() == 0 ){cout << "No entries for " << leg_names[i] << " " << branch << "; skipping" << endl; continue;}
    //hists[i]->GetYaxis()->SetRangeUser(1e-10,1e4);
    hists[i]->SetLineColor(mycolors[i]);
    if (i<2) hists[i]->SetFillColorAlpha(kBlack, 0.3*(2/(i+1)));
    double nEvent = hists[i]->Integral(0,hists[i]->GetNbinsX()+1);
    double nEventScaled = nEvent*1.39e8;
    nEvents.push_back(nEventScaled);
    hists[i]->Scale(1.0/hists[i]->Integral() );
    if (hists[i]->GetMaximum() > max){
	max = hists[i]->GetMaximum();
    }
  }
  // second loop does plotting
  for( int i=0; i<hists.size(); i++){
    hists[i]->SetMaximum(max*1.2); // set Y axis range to be slightly larger than found maximum
    hists[i]->Draw("SAME HIST"); 
    //string full_name = Form("%s", leg_names[i].c_str());
    string full_name = Form("%s (%4.2e)", leg_names[i].c_str(), nEvents[i]);
    leg->AddEntry(hists[i], full_name.c_str() );
  }
  leg->Draw();
  canv->SetLogy();
  canv->SaveAs( Form("%s/%s.png", outfile_path.c_str(), branch.c_str()) );
}

void Plot1DHistsRatio(vector<TH1D*> hists, vector<string> leg_names, string branch, int denominator_index){

  TCanvas* canv = new TCanvas("c","c",1200,1600);
  canv->Divide(0,2); 
  TLegend *leg = new TLegend(.7,.6,.98,.98);
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

    TH1D* h = (TH1D*) hists[i]->Clone();
    h->Divide(hists[d]);
    h->GetYaxis()->SetRangeUser(0,2);
    h->Draw("SAME HIST"); 
  }

  canv->cd(1);
  leg->Draw();
  canv->SaveAs( Form("%s/%s_ratio.png", outfile_path.c_str(), branch.c_str()) );
}


void simplePlotter(){

  vector<string> inputFiles = {"user.ebusch.totalBKG.root",
				//"user.ebusch.QCDbkg.root", 
				//"user.ebusch.Znunu.root",
				"user.ebusch.515480.root",
				"user.ebusch.515481.root",
				"user.ebusch.515482.root",
				"user.ebusch.515483.root",
				"user.ebusch.515485.root",
				"user.ebusch.515486.root",
				"user.ebusch.515487.root",
				"user.ebusch.515488.root",
				"user.ebusch.515489.root",
				"user.ebusch.515490.root",
				"user.ebusch.515495.root",
				"user.ebusch.515496.root",
				"user.ebusch.515498.root",
				"user.ebusch.515499.root",
				"user.ebusch.515500.root",
				"user.ebusch.515501.root",
				"user.ebusch.515502.root",
				"user.ebusch.515507.root",
				"user.ebusch.515510.root",
				"user.ebusch.515516.root",
				"user.ebusch.515518.root",
				"user.ebusch.515524.root",
				"user.ebusch.515525.root",
				"user.ebusch.515526.root"};

  vector<string> leg_names = {"QCD         ", "ZNuNu     ", "500   | 0.4", "500   | 0.8", "2000 | 0.2", "2000 | 0.6", "6000 | 0.4", "6000 | 0.8"};

  //vector<string> inputFiles = {"user.ebusch.QCDbkg.root", "user.ebusch.508547.root", "user.ebusch.508548.root", "user.ebusch.508549.root", "user.ebusch.508550.root"};
  //vector<string> leg_names = {"QCD", "1500/ 0.8", "1500/ 0.3", "750/ 0.8", "750/0.3"};
  /*
  vector<TH1D*> jet_svj_pt;
  jet_svj_pt = Get1DHists(inputFiles, "jet_svj_pt", P_jet_svj_pt);
  Plot1DHists(jet_svj_pt, leg_names, "jet_svj_pt"); 

  vector<TH1D*> pt_balance;
  pt_balance = Get1DHists(inputFiles, "pt_balance_12", P_pt_balance_12);
  Plot1DHistsRatio(pt_balance, leg_names, "pt_balance",0); 
  */
  /*
  string my_cut = "jet1_pt > -900";
  vector<TH1D*> jet1_pt;
  jet1_pt = Get1DHists(inputFiles, "jet1_pt", P_jet1_pt, my_cut);
  
  string my_cut2 = "jet1_pt > 450";
  vector<TH1D*> jet2_pt;
  jet2_pt = Get1DHists(inputFiles, "jet1_pt", P_jet1_pt, my_cut2);
  string my_cut3 = "met_met > 200";
  vector<TH1D*> jet3_pt;
  jet3_pt = Get1DHists(inputFiles, "jet1_pt", P_jet1_pt, my_cut3);
  */
  string my_cut = "fatjet1_pt > 450";
  vector<TH1D*> jet1_pt;
  jet1_pt = Get1DHists(inputFiles, "jet1_pt", P_jet1_pt, my_cut);


  //Plot1DHists(jet1_pt, leg_names, "jet1_pt"); 

  //vector<TH1D*> met_met;
  //met_met = Get1DHists(inputFiles, "met_met", P_met_met, my_cut);
  //Plot1DHists(met_met, leg_names, "met_met"); 
   
}
