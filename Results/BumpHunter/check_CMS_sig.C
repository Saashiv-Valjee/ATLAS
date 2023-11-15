{
	double x0 = 1500;
	double xmin = 1200;
	double xmax = 5000;
	double nbins = 100;
	double weight = 0;
	double mT_tmp =0.;
	RooRealVar mT("mT","mT",x0,xmin,xmax,"GeV");
for (int i = 515487; i < 515527; i++){
	TString file_path=Form("FILE/CMS/SR/v8p1_CMSskim1_%d_SR.root",i);
	TFile file(file_path.Data());
	TH1F *hist = new TH1F();
	hist = file.Get<TH1F>("sigHist");

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
	hist->SetTitle(Form("v8p1_CMSskim1_%d SR log plot",i));
	hist->Draw("E0");
	gPad->SetLogy(1);
	txt->Draw();
	cv_log.Print(Form("results/CMS/check/SR/v8p1_CMSskim1_%d_SR_log.png",i));

	TCanvas cv("cv","cv",800,600);
	hist->SetTitle(Form("v8p1_CMSskim1_%d SR plot",i));
	gPad->SetLogy(0);
	gStyle->SetOptStat(0);
	hist->Draw("E0");
	txt->Draw();
	cv.Print(Form("results/CMS/check/SR/v8p1_CMSskim1_%d_SR.png",i));
	delete txt;
	delete hist;
}

}
