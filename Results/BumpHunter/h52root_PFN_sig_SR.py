import h5py
import os,sys
import uproot
import numpy as np
import optparse
import ROOT

signal = sys.argv[1]

inputpath = '/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1/v8p1_PFNv6_{}.hdf5'.format(signal)
#resource: /eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1

outputpath = 'FILE/PFN/SR/v8p1_PFNv6_{}_SR.root'.format(signal)

parser = optparse.OptionParser()

parser.add_option('-i','--inputFile',   dest='inputFile', help='Specify the path to the input file.', default=inputpath)
parser.add_option('-o','--outputFile',   dest='outputFile', help='Specify the path to the output file.', default=outputpath)

parser.add_option('-s','--score',   dest='score', help='Specify the anomaly score to cut on.', default=0.6)
parser.add_option('-j','--jet2_Width',	dest='jet2_Width', help='Specify the anomalyn jet2_Width to cut on.', default = 0.05)


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
scoreData = inputFile['data']['score']
jet2_WidthData = inputFile['data']['jet2_Width']
weightData = inputFile['data']["weight"]

'''
print(weightData.max())
print(weightData.min())
'''

#Signal Region
num = 0
for i in range(0, len(mtData)):
	if (mtData[i]>xmin) and (mtData[i]<xmax) and (scoreData[i]>arguments.score) and (jet2_WidthData[i] > arguments.jet2_Width):
		num = num + 1
		tmp = tmp + weightData[i]
		mtHist.Fill(mtData[i],weightData[i]*scale)

outputFile = ROOT.TFile(arguments.outputFile, "RECREATE")
outputFile.cd()
print("signal: ", signal, 'weight: ',tmp, "# of Entries: ",num)
mtHist.Write()
outputFile.Close()
inputFile.close()
