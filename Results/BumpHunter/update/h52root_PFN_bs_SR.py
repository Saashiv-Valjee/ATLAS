import h5py
import os,sys
import uproot
import numpy as np
import optparse
import ROOT

signal = sys.argv[1]

parser = optparse.OptionParser()
parser.add_option('-b','--inputFile_bkg',   dest='inputFile_bkg', help='Specify the path to the input file.', default='/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v9/v9.1/v9p1_PFNv6_totalBkgALL_skim0.hdf5') 
#resource: /eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v9/v9.1

parser.add_option('-n','--inputFile_sig', dest='inputFile_sig', help='Specify the path to the input file.', default='/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1/v8p1_PFNv6_{}.hdf5'.format(signal))

parser.add_option('-o','--outputFile',   dest='outputFile', help='Specify the path to the output file.', default='FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_{}_SR_pdffit.root'.format(signal))
parser.add_option('-s','--score',   dest='score', help='Specify the anomaly score to cut on.', default=0.6)
parser.add_option('-j','--jet2_Width',	dest='jet2_Width', help='Specify the anomalyn jet2_Width to cut on.', default = 0.05)


(arguments, args) = parser.parse_args()
if not arguments.inputFile_sig or not arguments.inputFile_bkg or not arguments.outputFile:
	print("No input or output given! Aborting")
	sys.exit(0)


inputFile_sig = h5py.File(arguments.inputFile_sig,'r')
inputFile_bkg = h5py.File(arguments.inputFile_bkg,'r')

x0 = 2000.
xmin = 1200.
xmax = 5000.
tmp = 0.
nbins = 76
scale_bkg = 5.
scale_sig = 15.

mtHist =  ROOT.TH1F("dataHist","dataHist",nbins,xmin,xmax)

mtData_sig = inputFile_sig['data']["mT_jj"]
scoreData_sig = inputFile_sig['data']['score']
jet2_WidthData_sig = inputFile_sig['data']['jet2_Width']
weightData_sig = inputFile_sig['data']["weight"]

mtData_bkg = inputFile_bkg['data']["mT_jj"]
scoreData_bkg = inputFile_bkg['data']['score']
jet2_WidthData_bkg = inputFile_bkg['data']['jet2_Width']
weightData_bkg = inputFile_bkg['data']["weight"]

weightmin = min([weightData_sig.min()*scale_sig,weightData_bkg.min()*scale_bkg])-1
weightmax = max([weightData_sig.max()*scale_sig,weightData_bkg.max()*scale_bkg])+1
print(weightmin)
print(weightmax)

mT = ROOT.RooRealVar("mT","mT",x0, xmin, xmax, "GeV")
weight = ROOT.RooRealVar("weight", "weight", 1.,weightmin,weightmax)
mtDataSet = ROOT.RooDataSet("ds","ds",ROOT.RooArgSet(mT,weight),ROOT.RooFit.WeightVar("weight"))

#Signal Region
num = 0
for i in range(0, len(mtData_sig)):
	if (mtData_sig[i]>xmin) and (mtData_sig[i]<xmax) and (scoreData_sig[i]>arguments.score) and (jet2_WidthData_sig[i] > arguments.jet2_Width):
		num = num + 1
		tmp = tmp + weightData_sig[i]*scale_sig
		mtHist.Fill(mtData_sig[i],weightData_sig[i]*scale_sig)
		mT.setVal(mtData_sig[i])
		weight.setVal(weightData_sig[i]*scale_sig)
		mtDataSet.add(ROOT.RooArgSet(mT),weightData_sig[i]*scale_sig)

for i in range(0, len(mtData_bkg)):
	if (mtData_bkg[i]>xmin) and (mtData_bkg[i]<xmax) and (scoreData_bkg[i]>arguments.score) and (jet2_WidthData_bkg[i] > arguments.jet2_Width):
		num = num + 1
		tmp = tmp + weightData_bkg[i]*scale_bkg
		mtHist.Fill(mtData_bkg[i],weightData_bkg[i]*scale_bkg)
		mT.setVal(mtData_bkg[i])
		weight.setVal(weightData_bkg[i]*scale_bkg)
		mtDataSet.add(ROOT.RooArgSet(mT),weightData_bkg[i]*scale_bkg)

print(tmp)
print(num)
print(mtDataSet.sumEntries())
outputFile = ROOT.TFile(arguments.outputFile, "RECREATE")
outputFile.cd()
mtHist.Write()
mtDataSet.Write()
outputFile.Close()
inputFile_sig.close()
inputFile_bkg.close()
