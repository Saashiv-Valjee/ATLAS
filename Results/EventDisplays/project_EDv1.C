
#include "ATLASSTYLE/AtlasStyle.C"

#include "ATLASSTYLE/AtlasUtils.C"
#include "ATLASSTYLE/AtlasLabels.C"

#include "project_Hv2.h"

#include <sstream>
#include <string>
#include <iostream>

template <typename Type> std::string to_str(const Type & t)
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

const TString ptc = PTMIN;


const int eventmax = NOEVENTPIC;
const int eventdif = EVENTPICDIF;

const int nbsmvars = NBSMVARS;
const int njetvars = NJETVARS;

const int ntypes = 5;

void project_EDv1(){


  SetAtlasStyle();

  TCanvas* C[eventmax];
  TPad* P[eventmax];
  TPad* P1[eventmax];
  TPad* P2[eventmax];
  TLegend* L[eventmax];

  TString VecVars[nbsmvars] = {"PT","ETA","PHI","E","ST","ID","USE"};
  TString JetVecVars[njetvars] = {"PT","ETA","PHI","E","MATCH"};

  TString TYPENAMES[ntypes] = {"Z'","Dark Quark","Visible Dark Hadron","Invisible Dark Hadron","Other"};


  for(int j = 0; j < 1; j++){

    int m = 0;
    int r = 0;
    if(j == 1) r = 1;
    if(j == 2) m = 1;
    if(j == 3){
      m = 1;
      r = 1;
    }

    
    TString filenames[eventmax];



    TString ipname = "Z"+masses[m]+"r"+rinv[r]+".root"; // OPENS THE FILES
    cout << ipname << endl;
    TFile *f = new TFile(ipname,"READ");
    if (!f){
      cout<<"couldn't open "<<ipname<<endl;
    }
  
    vector<float> *V[nsamples][eventmax][nbsmvars];
    vector<float> *JETV[nsamples][eventmax][njetvars];
    vector<float> *LJETV[nsamples][eventmax][njetvars];
    vector<int> *EVENTV[nsamples][eventmax];
    vector<float> *METV[nsamples][eventmax];
    vector<int> *LSQV[nsamples][eventmax][2];
    vector<float> *LSPTSV[nsamples][eventmax][3];

    for(int e = 0; e < eventmax; e++){ // LOOPS OVER TEH EVENTS THEN THE BSM TYPES AND THEN THE VARIABLE TYPES AND ASSIGNES THEM TO TO A VECTOR
      
      for(int v = 0; v < nbsmvars; v++){
	TString VNAME = "EVENTVECTORE"+std::to_string(e)+"BSMV"+VecVars[v];

	f->GetObject(VNAME,V[j][e][v]);
	if(!V[j][e][v]){f->Map("extended forComp"); cout << "Couldn't Find: " << VNAME << endl; terminate();}
      }
      for(int v = 0; v < njetvars; v++){
	TString JETVNAME = "EVENTVECTORE"+std::to_string(e)+"JETV"+JetVecVars[v];
	  
	f->GetObject(JETVNAME,JETV[j][e][v]);
	if(!JETV[j][e][v]){f->Map("extended forComp"); cout << "Couldn't Find: " << JETVNAME << endl; terminate();}
      }
      for(int v = 0; v < njetvars; v++){
	TString JETVNAME = "EVENTVECTORE"+std::to_string(e)+"LJETV"+JetVecVars[v];
	  
	f->GetObject(JETVNAME,LJETV[j][e][v]);
	if(!LJETV[j][e][v]){f->Map("extended forComp"); cout << "Couldn't Find: " << JETVNAME << endl; terminate();}
      }
      
      TString EVENTNAME = "EVENTVECTOR"+std::to_string(e);
      f->GetObject(EVENTNAME,EVENTV[j][e]);
      if(!EVENTV[j][e]){f->Map("extended forComp"); cout << "Couldn't Find: " << EVENTNAME << endl; terminate();}
      
      EVENTNAME = "EVENTMETVECTOR"+std::to_string(e);
      f->GetObject(EVENTNAME,METV[j][e]);
      if(!METV[j][e]){f->Map("extended forComp"); cout << "Couldn't Find: " << EVENTNAME << endl; terminate();}
      
      EVENTNAME = "EVENTVECTOR"+std::to_string(e)+"LQ";
      f->GetObject(EVENTNAME,LSQV[j][e][0]);
      if(!LSQV[j][e][0]){f->Map("extended forComp"); cout << "Couldn't Find: " << EVENTNAME << endl; terminate();}
      
      EVENTNAME = "EVENTVECTOR"+std::to_string(e)+"SLQ";
      f->GetObject(EVENTNAME,LSQV[j][e][1]);
      if(!LSQV[j][e][1]){f->Map("extended forComp"); cout << "Couldn't Find: " << EVENTNAME << endl; terminate();}
      
      EVENTNAME = "EVENTVECTOR"+std::to_string(e)+"LSQPT";
      f->GetObject(EVENTNAME,LSPTSV[j][e][0]);
      //if(!LSPTSV[j][e][1]){f->Map("extended forComp"); cout << "Couldn't Find: " << EVENTNAME << endl; terminate();}      

      EVENTNAME = "EVENTVECTOR"+std::to_string(e)+"LSJPT";
      f->GetObject(EVENTNAME,LSPTSV[j][e][1]);
      if(!LSPTSV[j][e][1]){f->Map("extended forComp"); cout << "Couldn't Find: " << EVENTNAME << endl; terminate();}      

      EVENTNAME = "EVENTVECTOR"+std::to_string(e)+"LSLJPT";
      f->GetObject(EVENTNAME,LSPTSV[j][e][2]);
      if(!LSPTSV[j][e][1]){f->Map("extended forComp"); cout << "Couldn't Find: " << EVENTNAME << endl; terminate();}      

    }
    for(int e = 0; e < eventmax; e++){ // STARTS LOOPING OVER ALL THE EVENTS


      int BN[2];
      BN[0] = LSQV[j][e][0]->at(0);
      BN[1] = LSQV[j][e][1]->at(0);
      float BPT[2] = {LSPTSV[j][e][0]->at(0), LSPTSV[j][e][0]->at(1)};
      float JPT[2] = {LSPTSV[j][e][1]->at(0), LSPTSV[j][e][1]->at(1)};
      float LJPT[2] = {LSPTSV[j][e][2]->at(0), LSPTSV[j][e][2]->at(1)};
      int event = EVENTV[j][e]->at(0);
      float metphi = METV[j][e]->at(0);
      float metmet = METV[j][e]->at(1);


      C[e] = new TCanvas((const TString)std::to_string(e),(const TString)("E"+std::to_string(event)+"P"+std::to_string(e)),800,600);

      P1[e] = new TPad((const TString)("P1"+std::to_string(e)),(const TString)("P1"+std::to_string(e)),0,0,0.75,1);
      P1[e]->Draw();

      C[e]->cd(0);
      P1[e]->cd(0);
      auto frame = P1[e]->DrawFrame(-TMath::Pi(),-4.5,TMath::Pi(),4.5,";\\phi;\\eta");



      int Jlen = JETV[j][e][0]->size(); 
      int LJlen = LJETV[j][e][0]->size();  

      vector<float> *JETVPHI = JETV[j][e][2];
      vector<float> *JETVETA = JETV[j][e][1];
      vector<float> *JETVPT = JETV[j][e][0];

      vector<float> *LJETVPHI = LJETV[j][e][2];
      vector<float> *LJETVETA = LJETV[j][e][1];
      vector<float> *LJETVPT = LJETV[j][e][0];

      vector<float> *BSMVPHI = V[j][e][2];
      vector<float> *BSMVETA = V[j][e][1];
      vector<float> *BSMVPT = V[j][e][0];
      vector<float> *BSMVE = V[j][e][3];
      vector<float> *BSMVS = V[j][e][4];
      vector<float> *BSMVID = V[j][e][5];
      vector<float> *BSMVUSE = V[j][e][6];

      TLine *METL = new TLine(metphi,-4.5,metphi,4.5);
      METL->SetLineColor(kRed);
      METL->SetLineStyle(2);
      METL->DrawClone();
    
      int LC = 1;
      int FS = 0;
      int FC = 1;
      int LS = 1;

      float jetr = 0.4;
      float ljetr = 1;


      vector<float> theta;
      vector<float> beta;
      vector<float> rotate;
      vector<float> rotateb;
      vector<int> cross;
      vector<int> crossb;
      float jetphi = 0;
      float jeteta = 0;
      vector<float> cornerdist;
      for(int je = 0; je < Jlen; je++){ // CALCULATES INTERSECTIONS FOR ALL JET RADII WITHE EDGES
	jetphi = JETVPHI->at(je);
	jeteta = JETVETA->at(je);
	theta.push_back(0);
	beta.push_back(0);
	rotate.push_back(0);
	rotateb.push_back(0);
	cross.push_back(-1);
	crossb.push_back(-1);
	cornerdist.push_back(100);
	for(int s = 0;  s < 4; s++){
	  int A = s %2;
	  float root = 0;
	  float rootb = 0;
	  float cdist = std::sqrt((jeteta - (4.5*(2*(s/2)-1)))*(jeteta - (4.5*(2*(s/2)-1)))+(jetphi - TMath::Pi()*(1-2*(((s+1)/2)%2)))*(jetphi - TMath::Pi()*(1-2*(((s+1)/2)%2))));// DISTANCE TO A CORNER
	  if(cdist < cornerdist.at(je)){cornerdist.at(je) = cdist;}// GETS SMALLEST CORNER DISTANCE
	  if(A == 0){ // CHECKS LEFT OR RIGHT INTERSECTION
	    root = jetr*jetr - (jetphi-(1-s)*TMath::Pi())*(jetphi-(1-s)*TMath::Pi()); 
	    if(root > 0){
	      cross.at(je) = s;
	      theta.at(je) = asin((double)((double)std::sqrt(root)/(double)jetr))* (double)((double)360/(double)(2*TMath::Pi()));
	      rotate.at(je) = theta.at(je);
	      if(s == 2){rotate.at(je) = 180+theta.at(je);}
	    }
	  }
	  if(A == 1){ // CHECKS UP OR DOWN INTERSECTION
	    rootb = jetr*jetr - (jeteta+(2-s)*4.5)*(jeteta+(2-s)*4.5);
	    if(rootb > 0){
	      crossb.at(je) = s;
	      beta.at(je) = asin((double)((double)std::sqrt(rootb)/(double)jetr))* (double)((double)360/(double)(2*TMath::Pi()));
	      rotateb.at(je) = 270 + beta.at(je);
	      if(s == 3){rotateb.at(je) = 90 + beta.at(je);}
	    }
	  }
	}
      }


      vector<float> ltheta;
      vector<float>lbeta;
      vector<float> lrotate;
      vector<float> lrotateb;
      vector<int> lcross;
      vector<int> lcrossb;
      float ljetphi = 0;
      float ljeteta = 0;
      vector<float> lcornerdist;

      for(int je = 0; je < LJlen; je++){
	ljetphi = LJETVPHI->at(je);
	ljeteta = LJETVETA->at(je);
	ltheta.push_back(0);
	lbeta.push_back(0);
	lrotate.push_back(0);
	lrotateb.push_back(0);
	lcross.push_back(-1);
	lcrossb.push_back(-1);
	lcornerdist.push_back(100);
	for(int s = 0;  s < 4; s++){
	  int A = s %2;
	  float lroot = 0;
	  float lrootb = 0;
	  float lcdist = std::sqrt((ljeteta - (4.5*(2*(s/2)-1)))*(ljeteta - (4.5*(2*(s/2)-1)))+(ljetphi - TMath::Pi()*(1-2*(((s+1)/2)%2)))*(ljetphi - TMath::Pi()*(1-2*(((s+1)/2)%2))));// DISTANCE TO A CORNER
	  if(lcdist < lcornerdist.at(je)){lcornerdist.at(je) = lcdist;}// GETS SMALLEST CORNER DISTANCE
	  if(A == 0){
	    lroot = ljetr*ljetr - (ljetphi-(1-s)*TMath::Pi())*(ljetphi-(1-s)*TMath::Pi()); 
	    if(lroot > 0){
	      lcross.at(je) = s;
	      ltheta.at(je) = asin((double)(std::sqrt(lroot)/(double)ljetr))* (double)((double)360/(double)(2*TMath::Pi()));
	      lrotate.at(je) = ltheta.at(je);
	      if(s == 2){lrotate.at(je) = 180+ltheta.at(je);}
            }
	  }
	  if(A == 1){ // CHECKS UP OR DOWN INTERSECTION
	    lrootb = ljetr*ljetr - (ljeteta+(2-s)*4.5)*(ljeteta+(2-s)*4.5);
	    if(lrootb > 0){
	      lcrossb.at(je) = s;
	      lbeta.at(je) = asin((double)((double)std::sqrt(lrootb)/(double)ljetr))* (double)((double)360/(double)(2*TMath::Pi()));
	      lrotateb.at(je) = 270 + lbeta.at(je);
	      if(s == 3){lrotateb.at(je) = 90 + lbeta.at(je);}
	    }
	  }
	}
      }
      float thet, bet, rott, rotb, ph, et;

      for(int je = 0; je < LJlen; je++){ // LOOPS OVER ALL LARGE JETS AND DRAWS RADII EDGES
        
	thet = ltheta.at(je); bet = lbeta.at(je); 
	rott = lrotate.at(je); rotb = lrotateb.at(je);
	ph = LJETVPHI->at(je); et = LJETVETA->at(je);
	
        TEllipse* LJARC;
	LJARC = new TEllipse(ph,et,ljetr);
	
	if(lcross.at(je) != -1 || lcrossb.at(je) != -1){ // Checks if it crosses any border
	  int narc = 0; // NUMBER OF ADDITIONAL ARCS REQUIRED TO BE DRAWN
	  TEllipse* CLJARC[2];
	  
	  if(lcross.at(je) != -1 && lcrossb.at(je) == -1){ // CROSSES RIGHT OR LEFT ONLY
	    LJARC = new TEllipse(ph,et,ljetr,ljetr,0,360-2*thet,rott);
	    CLJARC[0] = new TEllipse(ph-(2-lcross.at(je)*2)*TMath::Pi(),et,ljetr,ljetr,0,2*thet,360-rott); 
	    narc = 1;
	  }
	  
	  if(lcross.at(je) == -1 && lcrossb.at(je) != -1){ // CROSSES BOTTOM OR TOP ONLY
	    LJARC = new TEllipse(ph,et,ljetr,ljetr,0,360-2*bet,rotb);
	  }

	  if(lcross.at(je) != -1 && lcrossb.at(je) != -1){ // CROSSES TWO EDGES
	    float rotatey;
	    float rotateyr;
	    float rotatey2;
	    int cn = 10*lcross.at(je)+lcrossb.at(je); // 1 -> BR| 20+1 -> BL| 23 -> TL| 3 -> TR
	    if(cn == 1){
	      rotatey = thet; 
	      if(90-thet-bet <= 0){
		rotateyr = 270 + bet;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 360-thet;
		rotatey2 = 270 + bet;
	      }
	    }
	    if(cn == (20+1)){
	      rotatey = 270+bet+1.5; 
	      if(90-thet-bet <= 0){
		rotateyr = 180-thet-1;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 180-thet;
		rotatey2 = 180+thet;
	      }
	    }
	    if(cn == 23){
	      rotatey = 180+thet+1.5; 
	      if(90-thet-bet <= 0){
		rotateyr = 90+bet-1;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 180-thet;
		rotatey2 = 90 + bet;
	      }
	    }
	    if(cn == 3){
	      rotatey = 90+bet; 
	      if(90-thet-bet <= 0){
		rotateyr = 360-thet;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 360-thet;
		rotatey2 = thet;
	      }
	    }
	    LJARC = new TEllipse(ph,et,ljetr,ljetr,0,270-bet-thet,rotatey);

	    if(rotatey2 == -1){ // CORNER IS WITHIN THE CONE
	      CLJARC[0] = new TEllipse(ph-(2-cross.at(je)*2)*TMath::Pi(),et,ljetr,ljetr,0,90+thet-bet,rotateyr);
	      narc = 1;
	    }
	    else{
	      CLJARC[0] = new TEllipse(ph-(2-cross.at(je)*2)*TMath::Pi(),et,ljetr,ljetr,0,90-bet+thet,rotateyr); 
	      CLJARC[1] = new TEllipse(ph,et,ljetr,ljetr,0,90-thet-bet,rotatey2);
	      narc = 2;
	    }
	  }
	


	  LC = 40; FS = 0; FC = 38; int MST = 26; int MSI = 1;
	  for(int p = 0; p < narc; p++){
	    CLJARC[p]->SetNoEdges();
	    CLJARC[p]->SetLineColor(LC);
	    CLJARC[p]->SetLineStyle(2);
	    CLJARC[p]->SetFillStyle(FS);
	    CLJARC[p]->SetFillColor(FC);
	    CLJARC[p]->SetLineWidth(2);
	    CLJARC[p]->DrawClone("SAME");
	  }

	} 

        LC = 40; FS = 0; FC = 38; int MST = 26; int MSI = 1;
	LJARC->SetNoEdges();
	LJARC->SetLineColor(LC);
	LJARC->SetFillStyle(FS);
	LJARC->SetFillColor(FC);
	LJARC->SetLineWidth(2);
	LJARC->SetLineStyle(2);
	LJARC->DrawClone("SAME"); 
      }

      for(int je = 0; je < Jlen; je++){ // LOOPS OVER ALL JETS AND DRAWS VECTOR POSITIONS AND RADII EDGES

	thet = theta.at(je); bet = beta.at(je); 
	rott = rotate.at(je); rotb = rotateb.at(je);
	ph = JETVPHI->at(je); et = JETVETA->at(je);
	
	TEllipse* JARC;
	JARC = new TEllipse(ph,et,jetr);
        TGraph* FRAMEJ = new TGraph(1,&JETVPHI->at(je),&JETVETA->at(je));
	FRAMEJ->GetXaxis()->SetLimits(-TMath::Pi(),TMath::Pi());
	FRAMEJ->GetYaxis()->SetLimits(-4.5,4.5);

	
	if(cross.at(je) != -1 || crossb.at(je) != -1){ // Checks if it crosses any border
	  int narc = 0; // NUMBER OF ADDITIONAL ARCS REQUIRED TO BE DRAWN
	  TEllipse* CJARC[2];
	  
	  if(cross.at(je) != -1 && crossb.at(je) == -1){ // CROSSES RIGHT OR LEFT ONLY
	    JARC = new TEllipse(ph,et,jetr,jetr,0,360-2*thet,rott);
	    CJARC[0] = new TEllipse(ph-(2-cross.at(je)*2)*TMath::Pi(),et,jetr,jetr,0,2*thet,360-rott); 
	    narc = 1;
	  }
	  
	  if(cross.at(je) == -1 && crossb.at(je) != -1){ // CROSSES BOTTOM OR TOP ONLY
	    JARC = new TEllipse(ph,et,jetr,jetr,0,360-2*bet,rotb);
	  }

	  if(cross.at(je) != -1 && crossb.at(je) != -1){ // CROSSES TWO EDGES
	    float rotatey;
	    float rotateyr;
	    float rotatey2;
	    int cn = 10*cross.at(je)+crossb.at(je); // 1 -> BR| 20+1 -> BL| 23 -> TL| 3 -> TR
	    if(cn == 1){
	      rotatey = thet; 
	      if(90-thet-bet <= 0){
		rotateyr = 270 + bet;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 360-thet;
		rotatey2 = 270 + bet;
	      }
	    }
	    if(cn == (20+1)){
	      rotatey = 270+bet+1.5; 
	      if(90-thet-bet <= 0){
		rotateyr = 180-thet-1;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 180-thet;
		rotatey2 = 180+thet;
	      }
	    }
	    if(cn == 23){
	      rotatey = 180+thet+1.5; 
	      if(90-thet-bet <= 0){
		rotateyr = 90+bet-1;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 180-thet;
		rotatey2 = 90 + bet;
	      }
	    }
	    if(cn == 3){
	      rotatey = 90+bet; 
	      if(90-thet-bet <= 0){
		rotateyr = 360-thet;
		rotatey2 = -1;
	      }
	      else{
		rotateyr = 360-thet;
		rotatey2 = thet;
	      }
	    }
	    JARC = new TEllipse(ph,et,jetr,jetr,0,270-bet-thet,rotatey);

	    if(rotatey2 == -1){ // CORNER IS WITHIN THE CONE
	      CJARC[0] = new TEllipse(ph-(2-cross.at(je)*2)*TMath::Pi(),et,jetr,jetr,0,90+thet-bet,rotateyr);
	      narc = 1;
	    }
	    else{
	      CJARC[0] = new TEllipse(ph-(2-cross.at(je)*2)*TMath::Pi(),et,jetr,jetr,0,90-bet+thet,rotateyr); 
	      CJARC[1] = new TEllipse(ph,et,jetr,jetr,0,90-thet-bet,rotatey2);
	      narc = 2;
	    }
	  }
	  

	  LC = 1; FS = 0; FC = 1;LS = 1;
	  int MST = 23;
	  double MSI = 1;
	  if(je == 0 || je == 1){LS = 2;LC = 1; FS = 0; FC = 38; MST = 32; MSI = 1;}
	  for(int p = 0; p < narc; p++){
	    CJARC[p]->SetNoEdges();
	    CJARC[p]->SetLineColor(LC);
	    CJARC[p]->SetLineStyle(LS);
	    CJARC[p]->SetFillStyle(FS);
	    CJARC[p]->SetFillColor(FC);
	    CJARC[p]->SetLineWidth(2);
	    CJARC[p]->DrawClone("SAME");
	  }

        }

	LC = 1; FS = 0; FC = 1; LS = 1;
	int MST = 23;
	double MSI = 1;
	if(je == 0 || je == 1){LS = 2;LC = 1; FS = 0; FC = 38; MST = 32; MSI = 1;}
	JARC->SetNoEdges();
	JARC->SetLineColor(LC);
	JARC->SetFillStyle(FS);
	JARC->SetFillColor(FC);
	JARC->SetLineWidth(2);
	JARC->SetLineStyle(LS);
	JARC->DrawClone("SAME");
	
	
	FRAMEJ->SetMarkerStyle(MST);
	FRAMEJ->SetMarkerSize(1.3*MSI*((float)std::sqrt(JETVPT->at(je))/(float)10));
	FRAMEJ->SetMarkerColor(1);
	FRAMEJ->DrawClone("SAME P");	  
      }	  
  
      int nbsm = BSMVPT->size(); // SORTS THE BSM VECTORS INTO DESCENDING PT 
      float temppt = 0;
      int tempn = 0;
      for(int i = 0; i < nbsm;i++){
	temppt = 0;
	tempn = 0;
	for(int l = 1; l < nbsm - i; l++){
	  if(BSMVPT->at(l) < temppt){tempn = l;}
	}
	BSMVPT->push_back(BSMVPT->at(tempn));
	BSMVPT->erase(BSMVPT->begin()+tempn);
	BSMVPHI->push_back(BSMVPHI->at(tempn));
	BSMVPHI->erase(BSMVPHI->begin()+tempn);
	BSMVETA->push_back(BSMVETA->at(tempn));
	BSMVETA->erase(BSMVETA->begin()+tempn);
	BSMVE->push_back(BSMVE->at(tempn));
	BSMVE->erase(BSMVE->begin()+tempn);
	BSMVS->push_back(BSMVS->at(tempn));
	BSMVS->erase(BSMVS->begin()+tempn);
	BSMVID->push_back(BSMVID->at(tempn));
	BSMVID->erase(BSMVID->begin()+tempn);
	BSMVUSE->push_back(BSMVUSE->at(tempn));
	BSMVUSE->erase(BSMVUSE->begin()+tempn);
      }

      int style[5] = {42,24,20,20,5};
      double size[5] = {1,1,1,1,1};
      int color[5] = {1,1,3,2,12};
      int qcount = 0;
      int i = 0;
      for(int p = 0; p < nbsm; p++){ // LOOPS OVER ALL BSM AND DRAWS INTO THE CANVAS
	if(BSMVID->at(p) == 5000001){i = 0;}
	else if(std::abs(BSMVID->at(p)) == 4900101 && BSMVS->at(p) == 23 && qcount < 2){i = 1; qcount++;}
	else if(std::abs(BSMVID->at(p)) == 4900111 || std::abs(BSMVID->at(p)) == 4900113){i = 2; if(BSMVUSE->at(p) == 0){i = 3;}}
	else if(std::abs(BSMVID->at(p)) == 4900211 || std::abs(BSMVID->at(p)) == 4900213){i = 3;}
	else{i = 4;}

	TGraph* FRAME = new TGraph(1,&BSMVPHI->at(p),&BSMVETA->at(p));
	FRAME->GetXaxis()->SetLimits(-TMath::Pi(),TMath::Pi());
	FRAME->GetYaxis()->SetLimits(-4.5,4.5);

	float fst = style[i];
	float fsi = size[i];
	float fcl = color[i];
	
	FRAME->SetMarkerStyle(fst);
	FRAME->SetMarkerSize(1.3*fsi*((float)std::sqrt(BSMVPT->at(p))/(float)10));	  
	FRAME->SetMarkerColor(fcl);
	if(i != 4){FRAME->Draw("SAME P");}

      }
      

      C[e]->cd(0);

      P2[e] = new TPad((const TString)("P2"+std::to_string(e)),(const TString)("P2"+std::to_string(e)),0.75,0,1,1);
      P2[e]->Divide(1,2);
      P2[e]->Draw();
      

      P2[e]->cd(1);
      
      const int LN = 9;
      TString LNAMES[LN] = {"Z'","Dark Quarks","Visible Dark Hadron","Invisible Dark Hadron", "Jet","Leading/Subleading Jets","Large Jet Cones","MET","Other"};
      int LCL[LN] = {1,1,3,2,1,1,40,46,14};
      int LST[LN] = {42,24,20,20,23,32,2,2,5};
      int LSI[LN] = {1,1,1,1,1,1,2,2,1};
 
      L[e] = new TLegend(0,0,1,1); 

      for(int l = 0; l < LN-1; l++){
	if(l != 7 && l != 6){
	  TH2D* TEMPH = new TH2D((const TString)("TEMPH"+LNAMES[l]+std::to_string(e)),"",1,0,1,1,0,1);
	  TEMPH->SetMarkerColor(LCL[l]);
	  TEMPH->SetMarkerStyle(LST[l]);
	  TEMPH->SetMarkerSize(1.3*LSI[l]);
	  L[e]->AddEntry(TEMPH,LNAMES[l],"P");
	  if(l == 5){
	    TArc* TEMPARC[2];
	    for(int t = 0; t < 2; t++){
	      TEMPARC[t] = new TArc(0,0,0.4);
	      TEMPARC[t]->SetLineColor(1);
	      TEMPARC[t]->SetLineStyle(t+1);
	      TEMPARC[t]->SetFillStyle(0);
	      TEMPARC[t]->SetLineWidth(2);
	      if(t == 1){L[e]->AddEntry(TEMPARC[t],"Leading/Subleading Jet Cones","L");}
	      else{L[e]->AddEntry(TEMPARC[t],"Jet Cones","L");}
	    }
	  }
	}
	else{
	  TLine *TEMPL = new TLine(0,0,1,1);
	  TEMPL->SetLineColor(LCL[l]);
	  TEMPL->SetLineStyle(LST[l]);
	  TEMPL->SetLineWidth(LSI[l]);
	  if(l!=1){L[e]->AddEntry(TEMPL,LNAMES[l],"L");}
	}
      }

      L[e]->SetBorderSize(0);
      L[e]->SetTextFont(42);
      L[e]->SetTextSize(0.05);
      L[e]->SetFillStyle(0);
      L[e]->SetHeader((const TString)("Z"+masses[m]+"r"+rinv[r]+"   Event:"+std::to_string(event)));
     
      L[e]->Draw();


      P2[e]->cd(2);
      
      const int ntext = 5;
      TString TNAMES[ntext] = {"MET","Leading Jet Pt","Subleading Jet Pt","Leading Dark Quark Pt","Subleading Dark Quark Pt"};
      float TVALS[ntext] = {metmet, JPT[0], JPT[1], BPT[0], BPT[1]};
      string TVNAMES[ntext];
      for(int t = 0; t < ntext; t++){
	TVNAMES[t] = to_str(TVALS[t]);
      }
      TText * TEXT[ntext];
      TText * TEXT2[ntext];
      for(int t = 0; t < ntext; t++){
	TEXT[t] = new TText(0, 0.9-0.06*(2*t), TNAMES[t]+" [GeV] :");
	TEXT[t]->SetTextAlign(11);
	//TEXT[t]->SetTextFont(52);
	TEXT[t]->SetTextSize(0.06);
	TEXT[t]->Draw("SAME");	
	TEXT2[t] = new TText(0, 0.9-0.06*(2*t+1)+0.015,(const TString)("  " + TVNAMES[t]));
	TEXT2[t]->SetTextAlign(11);
	//TEXT2[t]->SetTextFont(52);
	TEXT2[t]->SetTextSize(0.06);
	TEXT2[t]->Draw("SAME");
      }

      filenames[e] = "EVENTDISPLAYS/EVENT"+std::to_string(e)+"Z"+masses[m]+"r"+rinv[r];


      C[e]->Print(filenames[e]+".pdf");
      // C[e]->Print(filenames[e]+".png");
      // C[e]->Print(filenames[e]+".eps");
      
    }

  }


}
      
