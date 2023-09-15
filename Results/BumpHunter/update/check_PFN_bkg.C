{
	double x0 = 1500;
	double xmin = 1200;
	double xmax = 5000;
	double nbins = 100;
	double weight = 0;
	double mT_tmp =0.;
	RooRealVar mT("mT","mT",x0,xmin,xmax,"GeV");
	TString file_path="FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR.root";
	TFile file(file_path.Data());
	TH1F *hist = new TH1F();
	hist = file.Get<TH1F>("dataHist");
	hist->GetXaxis()->SetTitle("m_{T}(GeV)");
	hist->GetYaxis()->SetTitle("Arbitrary Unit");
	hist->GetYaxis()->SetTitleOffset(1.5);
	hist->SetMarkerStyle(kFullCircle);
	TPaveText *txt = new TPaveText(0.65, 0.65, 0.86, 0.86, "ndc");
	txt->SetBorderSize(0);
	txt->SetTextAlign(12);
	txt->SetFillColor(kWhite);
	txt->AddText(Form("Weighted Events: %d",int(hist->Integral())));
	gStyle->SetOptStat(0);
	TCanvas cv_log("cv_log","cv_log",800,600);
	hist->SetTitle("v9p1_PFNv6_totalBkgALL_skim0 SR log plot");
	hist->Draw("E0");
	gPad->SetLogy(1);
	txt->Draw();
	cv_log.Print("results/PFN/check/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_log.png");

	TCanvas cv("cv","cv",800,600);
	hist->SetTitle("v9p1_PFNv6_totalBkgALL_skim0 SR plot");
	gPad->SetLogy(0);
	gStyle->SetOptStat(0);
	hist->Draw("E0");
	txt->Draw();
	cv.Print("results/PFN/check/SR/v9p1_PFNv6_totalBkgALL_skim0_SR.png");
	delete txt;
	delete hist;
}
