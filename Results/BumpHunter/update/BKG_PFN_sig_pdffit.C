{
	#include "TMath.h"
	using namespace RooFit;
    //using namespace RooStats;

//Read Files
	double x0 = 0;
    double xmin = 1200;
    double xmax = 5000;
	double weight = 0;
	double mT_jj = 0;
/*
    RooRealVar mT("mT","mT",x0,xmin,xmax,"GeV");
//	RooRealVar weight_var("weight_var","weight_var",0,0,60);
	TString file_path="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1/user.ebusch.QCDskim.root";
	TFile file(file_path.Data());
	TTree *tree = file.Get<TTree>("PostSel");
	int nEntries = tree->GetEntries();
	tree->SetBranchAddress("weight",&weight);
	tree->SetBranchAddress("mT_jj",&mT_jj);
	RooDataSet ds("ds", "data", RooArgSet(mT_jj_var,weight_var),WeightVar("weight_var"));

	for (int i = 0; i < nEntries; i++){
		tree->GetEntry(i);
		if (mT_jj>1000&&mT_jj<6000){
			mT_jj_var.setVal(mT_jj); 
			weight_var.setVal(weight);
			ds.add(RooArgSet(mT_jj_var), weight);
		}
	}
	
	TFile *output;
	output = TFile::Open("FILE/dataset.root","recreate");
	ds.Write();
	output->Close();
*/
	TString dataset_path ="FILE/PFN/SR/v8p1_PFNv6_515504_SR.root";
	TFile file_dataset(dataset_path.Data());
	RooDataSet* ds = file_dataset.Get<RooDataSet>("ds");
//Design P.D.F
	RooRealVar mT("mT","mT",x0,xmin,xmax,"GeV");
    RooRealVar p1("p1","p1",5.20211,-10,10);
    RooRealVar p2("p2","p2",-4.36238,-10,10);
    RooRealVar p3("p3","p3",5.29696e-01,-10,10);
    RooRealVar p4("p4","p4",2.36368e-01,-10,10);
	RooGenericPdf bkgpdf("bkgpdf","bkgpdf","TMath::Power(1-(mT/13000.),p1)*TMath::Power(mT/13000.,p2+p3*TMath::Log(mT/13000.)+p4*TMath::Power(TMath::Log(mT/13000.),2))",RooArgSet(mT,p1,p2,p3,p4));
	RooRealVar mean("mean", "mean", 2000.,0., 5000.);
	RooRealVar sigma("sigma", "sigma",750, 0., 5000.);
	RooGaussModel sigpdf("sigpdf", "sigpdf", mT, mean, sigma);
	RooRealVar nsig("nsig", "nsig",1000,-1e2, 1e4);
    RooRealVar nbkg("nbkg", "", 124543,-1e2, 1e7);
//	RooAddPdf datapdf("datapdf", "", RooArgSet(bkgpdf, sigpdf), RooArgSet(nbkg,nsig));
	RooAddPdf datapdf("datapdf", "", RooArgSet(sigpdf), RooArgSet(nsig));
//	RooAddPdf datapdf("datapdf", "", RooArgSet(bkgpdf), RooArgSet(nbkg));
//Fit the data
	RooFitResult *fitRes = datapdf.fitTo(*ds, RooFit::Extended(1), RooFit::Minos(0), RooFit::Save());
	double minNll = -(fitRes->minNll());
//Draw the result
	TCanvas* cv = new TCanvas("cv", "", 800, 600);
	RooPlot *frame = mT.frame();
	frame->SetTitle("v9p1_PFNv6_totalBkgALL_skim0_515504_SR");
	frame->GetYaxis()->SetTitleOffset(1.5);
	ds->plotOn(frame);
	datapdf.plotOn(frame,Name("Total fit"));
//	datapdf.plotOn(frame, Name("Background"),RooFit::Components(bkgpdf), RooFit::LineStyle(kDashed), RooFit::LineColor(kBlue));
	datapdf.plotOn(frame, Name("Signal"),RooFit::Components(sigpdf), RooFit::LineStyle(kDashed), RooFit::LineColor(kMagenta));
	frame->Draw();
//Calculate Chisquare
	int nbin_empty = 0;
	RooHist* hpull = frame->pullHist(frame->getObject(0)->GetName(), frame->getObject(1)->GetName());
	RooHist* h1 = (RooHist*)frame->getObject(0);
	for (int i=0;i<hpull->GetN();i++){
		if (fabs(h1->GetY()[i])<1e-5) nbin_empty++;
	}
	int dof = hpull->GetN() - fitRes->floatParsFinal().getSize()-nbin_empty;
	double chisq = frame->chiSquare(frame->getObject(1)->GetName(),frame->getObject(0)->GetName(), fitRes->floatParsFinal().getSize());

	TPaveText *txt = new TPaveText(0.65, 0.5, 0.86, 0.86, "ndc");
	txt->SetBorderSize(0);
	txt->SetTextAlign(12);
	txt->SetFillColor(kWhite);
	txt->AddText(Form("#chi^{2}/#nu: %.1f/%d", (chisq*dof),dof));
//	if (!nbkg.hasAsymError()) txt->AddText(Form("N_{bkg}: %d #pm %d", nbkg.getVal(), nbkg.getError()));
//	txt->AddText(Form("N_{bkg}: %.0f #pm %.0f", nbkg.getVal(), nbkg.getError()));
	txt->AddText(Form("N_{sig}: %.0f #pm %.0f", nsig.getVal(), nsig.getError()));
//	else txt->AddText(Form("N_{bkg}: %.1f_{#minus %.1f}^{#plus %.1f}", nbkg.getVal(), fabs(nbkg.getAsymErrorLo()),nbkg.getAsymErrorHi()));
	RooArgList fp(fitRes->floatParsFinal());
	TIterator*it = fp.createIterator();
	RooRealVar* v = NULL;
	while (v= (RooRealVar*)it->Next()){
		TString vn = v->GetName();
		if (vn != "nbkg" and vn != "nsig"){
		txt->AddText(Form("%s = %.3f #pm %.5f",v->GetTitle(),v->getVal(),v->getError()));}
	}
	TLegend leg(.55,.2,.7,.4,"");
	leg.SetBorderSize(0);
	leg.SetFillColor(0);
	leg.AddEntry("Total fit","Total fit");
	leg.AddEntry("Signal","Signal");
	leg.AddEntry("Background","Background");
	leg.Draw();
	txt->Draw();
/*
	nsig.setVal(0); nsig.setConstant(1);
	mean.setConstant(1);sigma.setConstant(1);
	RooFitResult* res2 = datapdf.fitTo(*ds, RooFit::Save(), RooFit::Minos(0));
	minNll += res2->minNll();
	txt->AddText(Form("significance: %.1f",sqrt(2*minNll)));
	txt->Draw();
*/
	cv->Print("results/PFN/pdffit/v8p1_PFNv6_515504_SR_pdffit.png");
}
