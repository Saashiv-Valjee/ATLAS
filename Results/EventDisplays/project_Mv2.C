
#include "ATLASSTYLE/AtlasStyle.C"

#include "ATLASSTYLE/AtlasUtils.C"
#include "ATLASSTYLE/AtlasLabels.C"

#include "project_Hv2.h"

#include <sstream>
#include <string>
#include <iostream>

template <typename Type> std::string to_str(const Type & t) // FUNCTION FOR TURNING FLOATS TO STRINGS
{
  std::ostringstream os;
  os << t;
  return os.str ();
}

int nM = 2;
int nr = 2;
int nsamples = nM*nr;

TString masses[2] = {"1500","750"};
TString rinv[2] = {"8","3"};

int COLOR[4] = {810,860,800,870};

const TString ptc = to_str(PTMIN);

const int ntypes = 5;

int m = 0;
int r = 0;

TH1D* Norm (TH1D* Hist){
  int nbins = Hist->GetNbinsX();
  float binsum = 0;

  for(int b = 0; b < nbins; b++){
    binsum += Hist->GetBinContent(b+1);
  }
  for(int b = 0; b < nbins; b++){
    Hist->SetBinContent(b+1,(Hist->GetBinContent(b+1))/(binsum));
  }
  return Hist;
}


void DRAW1D(TCanvas* cn, int CD, TLegend* L, TH1D* Hist[nsamples], int nbins, TString X, bool NORM){
 
  cn->cd(CD);
  TString Y;
  float Max = 0;
  for(int c = 0; c < nsamples; c++){
    Hist[c] = (TH1D*)(Hist[c]->Rebin(nbins));
    if(NORM){Norm(Hist[c]);}
    Max = std::max((double)(Hist[c]->GetMaximum()*1.25),(double)Max);
  }
  for(int c = 0; c < nsamples; c++){
    Hist[c]->SetStats(false);
    Hist[c]->Draw("SAME");
    Hist[c]->SetLineColor(COLOR[c]);
    Hist[c]->SetLineWidth(2);
    Hist[c]->SetMaximum(Max);
    Hist[c]->GetXaxis()->SetTitle(X);
    if(!NORM){ Y = "No. Entries";}
    else{Y = "A.U.";}
    Hist[c]->GetYaxis()->SetTitle(Y);
    L->SetBorderSize(0);
    L->SetFillStyle(0);
    L->Draw();
  }

}

void DRAW2D(TCanvas* cn, int CD, TH2D* Hist, int nbinsx, int nbinsy, TString X, TString Y,int sample){

  int  m = 0;
  int  r = 0;
  if(sample == 1) r = 1;
  if(sample == 2) m = 1;
  if(sample == 3){
    m = 1;
    r = 1;
  }

  cn->cd(CD);

  Hist = (TH2D*)(Hist->RebinX(nbinsx));
  Hist = (TH2D*)(Hist->RebinY(nbinsy));

  Hist->SetStats(false);
  Hist->Draw("COLZ");
  Hist->GetXaxis()->SetTitle(X);
  Hist->GetYaxis()->SetTitle(Y);
  Hist->SetTitle(((TString)Hist->GetTitle())+" || Z"+masses[m]+"r"+rinv[r]+" & P_{t} > "+ptc);
}

// void DRAWPROFILE(TCanvas* cn, int CD, TLegend* L, TH2D* Hist, TString prof, int Max, int colour, int nbinsx, int nbinsy, TString X, TString Y, TString T){

//   cn->cd(CD);


//   Hist = (TH2D*)(Hist->RebinX(nbinsx));
//   Hist = (TH2D*)(Hist->RebinY(nbinsy));

//   TH1D* PHist;

//   if(prof == "X" || prof == "x"){PHist = (TH1D*)(Hist->ProfileX());}
//   else if(prof == "Y" || prof == "y"){PHist = (TH1D*)(Hist->ProfileY());}
//   else{cout << "WRONG PROFILE AXIS" << endl; terminate();}

//   PHist->SetStats(false);
//   PHist->Draw("SAME HIST");
//   PHist->SetLineWidth(2);
//   PHist->SetLineColor(colour);
//   PHist->GetXaxis()->SetTitle(X);
//   PHist->GetYaxis()->SetTitle(Y);
//   PHist->SetTitle(T);
// }


void project_Mv2(){


  const int n1DHists = 39;
  const int n2DHists = 2;
  const int nPHists = 0;

  int nC1 = n1DHists/4+1;

  // SetAtlasStyle();

  TCanvas* C1D[nC1];
  TLegend* L1D = new TLegend(0.65,0.55,0.85,0.85);
  TH1D* HISTS1D[n1DHists][nsamples];
  TString HISTNAMES1D[n1DHists] = {"DPHIMATCH0","DPHIMATCH1","DPHIJETS0","DPHIJETS1",
				   "DPHIJETS2","DPHIMIN0","DPHIMIN1","VDHPT0",
				   "VDHPT1","JETPTCATCH0","JETPTCATCH1","LMAXVDHDR",
				   "SLMAXVDHDR","LNUSEFULDH","SLNUSEFULDH","JPT0",
				   "JPT1","QPT0","QPT1","NUSEFUL",
				   "NVDH","NIDH","U_VRAT","I_VRAT",
				   "I_ARAT","U_ARAT","DMNC","QMATCHES0",
				   "QMATCHES1","PTBALPT","PTBALMET","QPTRAT",
				   "DMRATI","DMRATA","NMISS","CATCHRAT0",
				   "CATCHRAT1","CATCHRATJ0","CATCHRATJ1"
  };
  TString HISTXAXIS1D[n1DHists] = {"\\Delta\\Phi","\\Delta\\Phi","\\Delta\\Phi","\\Delta\\Phi",
				   "\\Delta\\Phi","\\Delta\\Phi_{min}","\\Delta\\Phi_{min}","p_{T}",
				   "p_{T}","P_{t}","P_{t}","\\Delta R",
				   "\\Delta R","NO. Hadrons","NO. Hadrons","P_{t}",
				   "P_{t}","P_{t}","P_{t}","NO. Dark Hadrons",
				   "NO. Dark Hadrons","NO. Dark Hadrons","Ratio",
				   "Ratio",
				   "Ratio","Ratio","NO.Children","NO. Jets","NO.Jets",
				   "P_{t} bal","P_{t} bal","Ratio","Ratio",
				   "Ratio","NO. Particles",
				   "Ratio","Ratio",
				   "Ratio","Ratio",
  };
  int HISTNBINS1D[n1DHists] = {30,30,30,30,
			       30,30,30,30,
			       30,30,30,30,
			       30,10,10,30,
			       30,30,30,16,
			       16,16,16,16,
			       16,16,5,5,
			       5,30,30,30,30,
			       30,20,
			       30,30,
			       30,30
};

  TCanvas* C2D[n2DHists];
  TH2D* HISTS2D[n2DHists][nsamples];
  TString HISTNAMES2D[n1DHists] = {"MATCHDPHICORR","JETPTCORR"};
  TString HISTXAXIS2D[n2DHists] = {"\\Delta\\Phi_{Leading}","Leading p_{t} [GeV]"};
  TString HISTYAXIS2D[n2DHists] = {"\\Delta\\Phi_{Subleading}","Subleading p_{t} [GeV]"};
  int HISTNBINSXY2D[n2DHists][2] = {{30,30},{30,30}};
  


  bool DRAW_NORM = true;
  bool DRAW_1D = true;
  bool DRAW_2D = false;

  for(int j = 0; j < nsamples; j++){

    m = 0;
    r = 0;
    if(j == 1) r = 1;
    if(j == 2) m = 1;
    if(j == 3){
      m = 1;
      r = 1;
    }


    TString ipname = "Z"+masses[m]+"r"+rinv[r]+".root"; // OPENS THE FILES
    cout << ipname << endl;
    TFile *f = new TFile(ipname,"READ");
    if (!f){
      cout<<"couldn't open "<<ipname<<endl;
    }

    for(int h1 = 0; h1 < n1DHists; h1++){
      TString H1NAME = HISTNAMES1D[h1]+(TString)std::to_string(j);
      f->GetObject(H1NAME,HISTS1D[h1][j]);
      if(!HISTS1D[h1][j]){f->Map("extended forComp"); cout << "Couldn't Find: " << H1NAME << endl; terminate();}
    }

    for(int h2 = 0; h2 < n2DHists; h2++){
      TString H2NAME = HISTNAMES2D[h2]+(TString)std::to_string(j);
      f->GetObject(H2NAME,HISTS2D[h2][j]);
      if(!HISTS2D[h2][j]){f->Map("extended forComp"); cout << "Couldn't Find: " << H2NAME << endl; terminate();}
    }
  }

    if(DRAW_1D){
      
      for(int j = 0; j < nsamples; j++){
	int m = 0;
	int r = 0;
	if(j == 1) r = 1;
	if(j == 2) m = 1;
	if(j == 3){
	  m = 1;
	  r = 1;
	}
	TH1D* TEMP1DHIST = new TH1D((const TString)("TEMP1DHIST"+to_string(j)),"",1,0,1);
	TEMP1DHIST->SetLineColor(COLOR[j]);
	L1D->AddEntry(TEMP1DHIST,"Z"+masses[m]+"r"+rinv[r],"L");
      }
      L1D->SetBorderSize(1);
      for(int h1 = 0;  h1 < n1DHists; h1++){
	int hdiv = h1/4;
	if(h1%4 == 0){
	  C1D[hdiv] = new TCanvas((const TString)("C1D"+std::to_string(hdiv)),(const TString)("1D#"+std::to_string(hdiv)),800,600);
	  if(n1DHists-h1 == 1){;}
	  else if(n1DHists-h1 == 2){C1D[hdiv]->Divide(2,1,0.02,0.02);}
	  else if(n1DHists-h1 > 2){C1D[hdiv]->Divide(2,2,0.02,0.02);}
	}
	DRAW1D(C1D[hdiv],h1%4+1,L1D,HISTS1D[h1],5040/HISTNBINS1D[h1],HISTXAXIS1D[h1],DRAW_NORM);
      }
    }

    if(DRAW_2D){
      for(int h2 = 0; h2 < n2DHists; h2++){
        
	C2D[h2] = new TCanvas((const TString)("C2D"+std::to_string(h2)),(const TString)("2D#"+std::to_string(h2)),800,600);
	C2D[h2]->Divide(2,2,0.02,0.02);

	for(int j = 0; j < nsamples; j++){
	  int m = 0;
	  int r = 0;
	  if(j == 1) r = 1;
	  if(j == 2) m = 1;
	  if(j == 3){
	    m = 1;
	    r = 1;
	  }
	  
	  DRAW2D(C2D[h2],j+1,HISTS2D[h2][j],5040/HISTNBINSXY2D[h2][0],5040/HISTNBINSXY2D[h2][0],HISTXAXIS2D[h2],HISTYAXIS2D[h2],j);
	  
	}
      
      }
    }


}


