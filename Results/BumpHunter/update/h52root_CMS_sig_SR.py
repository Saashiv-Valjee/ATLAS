import h5py
import os,sys
import uproot
import numpy as np
import optparse
import ROOT

signal = sys.argv[1]

inputpath = '/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1/v8p1_CMSskim1_{}.hdf5'.format(signal)
#resource: /eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1

outputpath = 'FILE/CMS/SR/v8p1_CMSskim1_{}_SR.root'.format(signal)

parser = optparse.OptionParser()

parser.add_option('-i','--inputFile',   dest='inputFile', help='Specify the path to the input file.', default=inputpath)
parser.add_option('-o','--outputFile',   dest='outputFile', help='Specify the path to the output file.', default=outputpath)


parser.add_option('-j','--jet2_Width',  dest='jet2_Width', help='Specify the anomalyn jet2_Width to cut on.', default = 0.05)
parser.add_option('-r','--rT',   dest='rT', help='Specify the anomaly score to cut on.', default=0.25)
parser.add_option('-p','--dphi_min',   dest='dphi_min', help='Specify the anomaly score to cut on.', default=0.8)
parser.add_option('-d','--deltaY_12',   dest='deltaY_12', help='Specify the anomaly score to cut on.', default=1.5)


(arguments, args) = parser.parse_args()
if not arguments.inputFile or not arguments.outputFile:
	print("No input or output given! Aborting")
	sys.exit(0)


inputFile = h5py.File(arguments.inputFile,'r')
x0 = 2000.
xmin = 1200.
xmax = 5000.
tmp = 0.
nbins = 76
scale = 1.

mtHist =  ROOT.TH1F("sigHist","sigHist",nbins,xmin,xmax)

mtData = inputFile['data']["mT_jj"]
jet2_WidthData = inputFile['data']['jet2_Width']
weightData = inputFile['data']["weight"]

rTData = inputFile['data']['rT']
dphi_minData = inputFile['data']['dphi_min']
deltaY_12Data = inputFile['data']['deltaY_12']


'''
print(weightData.max())
print(weightData.min())
'''
weightmin = weightData.min()*scale-1
weightmax = weightData.max()*scale+1
'''
print(weightmin)
print(weightmax)
'''
mT = ROOT.RooRealVar("mT","mT",x0, xmin, xmax, "GeV")
weight = ROOT.RooRealVar("weight", "weight", 1.,weightmin,weightmax)
mtDataSet = ROOT.RooDataSet("ds","ds",ROOT.RooArgSet(mT,weight),ROOT.RooFit.WeightVar("weight"))

#Signal Region
num = 0
for i in range(0, len(mtData)):
	if (mtData[i]>xmin) and (mtData[i]<xmax) and (jet2_WidthData[i] > arguments.jet2_Width) and (rTData[i] > arguments.rT) and (dphi_minData[i] < arguments.dphi_min) and (deltaY_12Data[i] < arguments.deltaY_12):
		num = num + 1
		tmp = tmp + weightData[i]
		mtHist.Fill(mtData[i],weightData[i]*scale)
		mT.setVal(mtData[i])
		weight.setVal(weightData[i]*scale)
		mtDataSet.add(ROOT.RooArgSet(mT),weightData[i]*scale)
outputFile = ROOT.TFile(arguments.outputFile, "RECREATE")
outputFile.cd()
print("signal: ", signal, 'weight: ',tmp, "# of Entries: ",num)
mtHist.Write()
mtDataSet.Write()
outputFile.Close()
inputFile.close()
