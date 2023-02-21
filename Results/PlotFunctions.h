#include <vector>
#include <string>
//#include <map>

#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TPad.h"
#include "THStack.h"
#include "TLegend.h"
#include "TString.h"
#include <iostream>
#include <iomanip>

#include <algorithm>

#include "TGraphAsymmErrors.h"
#include <cmath>

#include "TLatex.h"

// -------------------------------------------------------------------------------------
void SetStyle(){
	gStyle->SetOptStat(0);
	gStyle->SetPaintTextFormat(".2f");
	//gStyle->SetLegendBorderSize(2);
	//gStyle->SetPaintTextSize(1);

	//gStyle->SetGridStyle(3);
	//gStyle->SetGridWidth(1);
	gStyle->SetGridColor(kGray+1);

	gStyle->SetCanvasColor(-1);
	gStyle->SetPadColor(-1);
	gStyle->SetFrameFillColor(-1);
	gStyle->SetHistFillColor(-1);
	gStyle->SetTitleFillColor(-1);
	gStyle->SetFillColor(-1);
	gStyle->SetFillStyle(4000);
	gStyle->SetStatStyle(0);
	gStyle->SetTitleStyle(0);
	gStyle->SetCanvasBorderSize(0);
	gStyle->SetFrameBorderSize(0);
	gStyle->SetLegendBorderSize(0);
	gStyle->SetStatBorderSize(0);
	gStyle->SetTitleBorderSize(0);
}

// -------------------------------------------------------------------------------------
void StampATLAS( const std::string & text = "Internal", float lumi=140., float x=0.14, float y=0.84, float textsize=0.045) {
  // Usage:  StampATLAS("Internal", 126.5, 0.12, 0.75);
  
  textsize = 0.045;
  TLatex atlas;
  atlas.SetNDC();
  atlas.SetTextFont(72);
  atlas.SetTextColor(1);
  atlas.SetTextSize(textsize);
  atlas.DrawLatex( x, y, "ATLAS" );

  TLatex plottype;
  plottype.SetNDC();
  plottype.SetTextFont(42);
  plottype.SetTextColor(1);
  plottype.SetTextSize(textsize);
  plottype.DrawLatex( x+0.11, y, text.c_str() ); //x+0.1, y, text.c_str() );

  TLatex energylumi;
  energylumi.SetNDC();
  energylumi.SetTextFont(42);
  energylumi.SetTextColor(1);
  energylumi.SetTextSize(textsize*0.75);
  energylumi.DrawLatex( x, y-.04, "#sqrt{s} = 13 TeV" );
  //energylumi.DrawLatex( x, y-.08, Form("L = %.1f fb^{-1}", lumi) );
  //energylumi.DrawLatex( x+.01, y-.2, "SF = #frac{N_{SR}}{N_{CR}} = 0.88" );
}

// -------------------------------------------------------------------------------------
TH1F* GetCDF( TH1F* h ){
	// Cumulative Distribution Function. Returns the fraction of events to the right of
	// the x-axis value
	// TODO: @Elena -- you found an indexing bug here?

	TH1F* h_cdf = (TH1F*)h->Clone();
	h_cdf->Reset();
	double integral = h->Integral();
	int NBins = h->GetNbinsX()+1;
	for( int i=1; i<=NBins; i++ ){
		//integral += h->GetBinContent(i);
		double integral_temp = h->Integral(i, NBins); //integral;
		h_cdf->SetBinContent(i, integral_temp);
	}
	return h_cdf;
}

// -------------------------------------------------------------------------------------
TH1F* GetReverseCDF( TH1F* h ){
	// Reverse Cumulative Distribution Function. Returns the fraction of events to the 
	// left of the x-axis value

	TH1F* h_cdf = (TH1F*)h->Clone();
	h_cdf->Reset();
	double integral = h->Integral();
	int NBins = h->GetNbinsX()+1;
	for( int i=1; i<NBins; i++ ){
		//integral += h->GetBinContent(i);
		double integral_temp = h->Integral(1, i); //integral;
		h_cdf->SetBinContent(i, integral_temp);
	}
	return h_cdf;
}


// -------------------------------------------------------------------------------------
TH1F* GetSqrtTH1( TH1F* h ){

	TH1F *h_sqrt = (TH1F*)h->Clone();
	h_sqrt->Reset(); 
	for (int bin=1; bin<h->GetNbinsX()+1; bin++){
		double bin_content  	= h->GetBinContent(bin);
		double sqrt_bin_content = sqrt( bin_content );
		double error = 0.5*(sqrt_bin_content / bin_content)*h->GetBinError(bin);
		h_sqrt->SetBinContent(bin, sqrt_bin_content);
		h_sqrt->SetBinError(bin, error);
	}
	return h_sqrt;
}


// -------------------------------------------------------------------------------------
string GetLegendNames( string filetag  ){
  cout <<"PlotFunctions::GetLegendNames()"<<endl;
  map<string, string> filetag_legend;
  filetag_legend["508547"] = "1500 GeV, 0.8";
  filetag_legend["508548"] = "1500 GeV, 0.3";
  filetag_legend["508549"] = "750 GeV, 0.8";
  filetag_legend["508550"] = "750 GeV, 0.3";
  filetag_legend["515479"] = "500 GeV, 0.2";
  filetag_legend["515480"] = "500 GeV, 0.4";
  filetag_legend["515481"] = "500 GeV, 0.6";
  filetag_legend["515482"] = "500 GeV, 0.8";
  filetag_legend["515487"] = "1000 GeV, 0.2";
  filetag_legend["515488"] = "1000 GeV, 0.4";
  filetag_legend["515489"] = "1000 GeV, 0.6";
  filetag_legend["515490"] = "1000 GeV, 0.8";
  filetag_legend["515491"] = "1250 GeV, 0.2";
  filetag_legend["515492"] = "1250 GeV, 0.4";
  filetag_legend["515493"] = "1250 GeV, 0.6";
  filetag_legend["515494"] = "1250 GeV, 0.8";
  filetag_legend["515495"] = "1500 GeV, 0.2";
  filetag_legend["515496"] = "1500 GeV, 0.4";
  filetag_legend["515497"] = "1500 GeV, 0.6";
  filetag_legend["515498"] = "1500 GeV, 0.8";
  filetag_legend["515499"] = "2000 GeV, 0.2";
  filetag_legend["515500"] = "2000 GeV, 0.4";
  filetag_legend["515501"] = "2000 GeV, 0.6";
  filetag_legend["515502"] = "2000 GeV, 0.8";
  filetag_legend["515503"] = "2500 GeV, 0.2";
  filetag_legend["515504"] = "2500 GeV, 0.4";
  filetag_legend["515505"] = "2500 GeV, 0.6";
  filetag_legend["515506"] = "2500 GeV, 0.8";
  filetag_legend["515507"] = "3000 GeV, 0.2";
  filetag_legend["515508"] = "3000 GeV, 0.4";
  filetag_legend["515509"] = "3000 GeV, 0.6";
  filetag_legend["515510"] = "3000 GeV, 0.8";
  filetag_legend["515511"] = "3500 GeV, 0.2";
  filetag_legend["515512"] = "3500 GeV, 0.4";
  filetag_legend["515513"] = "3500 GeV, 0.6";
  filetag_legend["515514"] = "3500 GeV, 0.8";
  filetag_legend["515515"] = "4000 GeV, 0.2";
  filetag_legend["515516"] = "4000 GeV, 0.4";
  filetag_legend["515517"] = "4000 GeV, 0.6";
  filetag_legend["515518"] = "4000 GeV, 0.8";
  filetag_legend["515519"] = "5000 GeV, 0.2";
  filetag_legend["515520"] = "5000 GeV, 0.4";
  filetag_legend["515521"] = "5000 GeV, 0.6";
  filetag_legend["515522"] = "5000 GeV, 0.8";
  filetag_legend["515523"] = "6000 GeV, 0.2";
  filetag_legend["515524"] = "6000 GeV, 0.4";
  filetag_legend["515525"] = "6000 GeV, 0.6";
  filetag_legend["515526"] = "6000 GeV, 0.8";
  filetag_legend["364702"] = "JZ2";
  filetag_legend["364703"] = "JZ3";
  filetag_legend["364704"] = "JZ4";
  filetag_legend["364705"] = "JZ5";
  filetag_legend["364706"] = "JZ6";
  filetag_legend["364707"] = "JZ7";
  filetag_legend["364708"] = "JZ8";
  filetag_legend["364709"] = "JZ9";
  filetag_legend["364710"] = "JZ10";
  filetag_legend["364711"] = "JZ11";
  filetag_legend["364712"] = "JZ12";
  filetag_legend["QCDbkg"] = "QCD";
  filetag_legend["QCDtest.mc20e"] = "QCD";
  filetag_legend["singlt"] = "Single top";
  filetag_legend["dibson"] = "Diboson";
  filetag_legend["ttbarr"] = "ttbar";
  filetag_legend["inclut"] = "Inclusive top";
  filetag_legend["lepttp"] = "Lepton top";
  filetag_legend["WpJets"] = "W+jets";
  filetag_legend["ZpJets"] = "Z+jets";

  if (filetag_legend.find(filetag) == filetag_legend.end()){
	cout << "No better legend name found for filetag " << filetag << "; using filetag." << endl;
	return filetag;
  }
  return filetag_legend[filetag];
}
