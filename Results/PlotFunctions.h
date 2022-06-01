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
string GetLegendNames( string filetag  ){

  map<string, string> filetag_legend;
  filetag_legend["508547"] = "1500 GeV, 0.8";
  filetag_legend["508548"] = "1500 GeV, 0.3";
  filetag_legend["508549"] = "750 GeV, 0.8";
  filetag_legend["508550"] = "750 GeV, 0.3";
  filetag_legend["364703.mc16e"] = "JZ3 mc16e";
  filetag_legend["364704.mc16e"] = "JZ4 mc16e";
  filetag_legend["364705.mc16e"] = "JZ5 mc16e";

  return filetag_legend[filetag];
}
