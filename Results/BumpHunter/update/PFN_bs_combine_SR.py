import os,sys
import ROOT
import numpy as np
startNum = int(sys.argv[1])
endNum = int(sys.argv[2])
inputFile_bkg = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.root")
RootBkgHist = inputFile_bkg.Get("bkgHist").Clone()
#RootBkgSet = inputFile_data.Get("ds").Clone()
#num = RootBkgSet.numEntries()
for signal in range(startNum, endNum):
	inputFile_sig = ROOT.TFile("FILE/PFN/SR/v8p1_PFNv6_{}_SR.root".format(signal))
	RootSigHist = inputFile_sig.Get("sigHist").Clone()
	scale = 10
	RootSigHist.Scale(scale)
	nbins = 76
	xmin = 1200
	xmax = 5000
	x0 = 2000
	RootDataHist = RootSigHist + RootBkgHist
	RootDataHist.SetName("dataHist")
	RootDataHist.SetTitle("dataHist")
	print(RootDataHist.Integral())
	
#	RootSigSet = inputFile_sig.Get("ds").Clone()	

	f = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_{}_SR_x10.root".format(signal),"RECREATE")
	RootDataHist.Write("dataHist")
	f.Close()
