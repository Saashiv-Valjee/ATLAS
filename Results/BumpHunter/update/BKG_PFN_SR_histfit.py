import matplotlib
import os,sys
matplotlib.use("Agg")
from datetime import datetime
import matplotlib.pyplot as plt
import uproot
#import pyBumpHunter as BH
import ROOT
from ROOT import TH1F, TF1
import numpy as np

xmin = 1200.
xmax = 5000.
x0 = 2000.
#ROOT.gRandom.SetSeed(0)
inputFile = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR.root")
x = ROOT.RooRealVar("x","x",x0,xmin,xmax,"GeV")
tplHist = inputFile.Get("dataHist").Clone()
bkgShape = TF1("bkgShape","TMath::Power(1-x/13000.,[0])*TMath::Power(x/13000.,[1]+[2]*TMath::Log(x/13000.)+[3]*TMath::Power(TMath::Log(x/13000.),2))",xmin,xmax)

bkgShape.SetParameter(0,1)
bkgShape.SetParameter(1,10)
bkgShape.SetParameter(2,-1.)
bkgShape.SetParameter(3,0.)
bkgShape.SetParNames("l1","l2","l3","l4")                     
bkgShape.SetParNames("p1","p2","p3","p4")

fitResult = tplHist.Fit("bkgShape","R S")
result = tplHist.GetFunction("bkgShape")
chi2 = result.GetChisquare()

fit = TF1("bkgfunc","TMath::Power(1-x/13000.,[0])*TMath::Power(x/13000.,[1]+[2]*TMath::Log(x/13000.)+[3]*TMath::Power(TMath::Log(x/13000.),2))",xmin,xmax)

fit.SetParameter(0,fitResult.Parameter(0))
fit.SetParameter(1,fitResult.Parameter(1))
fit.SetParameter(2,fitResult.Parameter(2))
fit.SetParameter(3,fitResult.Parameter(3))


xbins = tplHist.GetNbinsX()

bkgHist = TH1F("bkgHist","bkgHist",xbins,xmin,xmax)
bkgNum = int(tplHist.Integral())
scale = 100
bkgHist.FillRandom("bkgfunc",bkgNum*scale)
bkgHist.Scale(1/scale)

ROOT.gStyle.SetOptStat(0)
bkgHist.SetMarkerStyle(ROOT.kFullCircle)
tplHist.SetMarkerStyle(ROOT.kFullSquare)
bkgHist.SetMarkerColor(ROOT.kGreen)
tplHist.SetMarkerColor(ROOT.kBlue)
binwidth = int((xmax - xmin) / xbins)
YTitle = "Events/({:d}GeV)".format(binwidth)
tplHist.GetXaxis().SetTitle("m_{T,JJ}(GeV)")
tplHist.GetYaxis().SetTitle(YTitle)
tplHist.GetYaxis().SetTitleOffset(1.5)

txt = ROOT.TPaveText(0.3,0.65,0.5,0.86,"ndc")
txt.SetBorderSize(0)
txt.SetFillColor(ROOT.kWhite)
numFloat = 4
dof = 0
check  = 0.
for i in range(0, xbins):
	check = check + tplHist.GetBinContent(i)
	if (abs(tplHist.GetBinContent(i)) > 0.):
		 dof = dof + 1
dof = dof - numFloat
chistr = "#chi^{{2}}/#nu: {:.1f}/{}".format(chi2,dof)
txt.AddText(chistr)
legend =ROOT.TLegend(.25,.2,.45,.4)
legend.AddEntry(tplHist,"tplHist")
legend.AddEntry(bkgHist,"bkgHist")
legend.AddEntry(fit,"function")

cv_log = ROOT.TCanvas("cv_log", "Background Template Log")
ROOT.gPad.SetLogy(1)
tplHist.SetTitle("v9p1_PFNv6_totalBkgALL_skim0 SR fit log plot")
tplHist.Draw("E0")
bkgHist.Draw("E0 SAME")
fit.Draw("SAME")
txt.Draw()
legend.Draw()
cv_log.Print("results/PFN/histfit/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit_log.png")

cv = ROOT.TCanvas("cv", "Background Template")
ROOT.gPad.SetLogy(0)
tplHist.SetTitle("v9p1_PFNv6_totalBkgALL_skim0 SR fit plot")
tplHist.Draw("E0")
bkgHist.Draw("E0 SAME")
fit.Draw("SAME")
txt.Draw()
legend.Draw()
cv.Print("results/PFN/histfit/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.png")

f = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.root","RECREATE")
bkgHist.Write()
f.Close()


ROOT.gRandom.SetSeed(0)
toyHist = TH1F("toyHist","toyHist",xbins,xmin,xmax)
scale = 100
toyHist.FillRandom("bkgfunc",bkgNum*scale)
toyHist.Scale(1/scale)

fToy = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit_toy.root","RECREATE")
toyHist.Write()
f.Close()
