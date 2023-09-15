# Here we test pyBumpHunter.
# The result can be compared to what can be obtained with the original C++ version.
# We will use histograms ranging between 0 and 20 with 60 even bins.
import gc
import os,sys
import matplotlib
matplotlib.use("Agg")
import json
from datetime import datetime  # # Used to compute the execution time

import matplotlib.pyplot as plt
import uproot  # # Used to read data from a root file
import pyBumpHunter as BH
import ROOT
import numpy as np

significance = []
begin = datetime.now()

startNum = 515487
endNum = 515527

#open a root file and convert the inputs to np histograms
inputFileBkg = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.root")

RootBkgHist = inputFileBkg.Get("bkgHist").Clone()

print(RootBkgHist.Integral())
rang = [1200, 5000]

binCenter_bkg = []
binWeight_bkg = []
binEdge_bkg = []
binContent_bkg = []
hist_hist = []
check_bkg = 0.
bkg= []

for i in range(1, RootBkgHist.GetNbinsX() + 1):
	binCenter_bkg.append(RootBkgHist.GetBinCenter(i))
	binWeight_bkg.append(RootBkgHist.GetBinContent(i))
	binEdge_bkg.append(RootBkgHist.GetBinLowEdge(i))
	check_bkg = check_bkg + RootBkgHist.GetBinContent(i)
binsnum_bkg = RootBkgHist.GetNbinsX()
binEdge_bkg.append(RootBkgHist.GetBinLowEdge(RootBkgHist.GetNbinsX()) + RootBkgHist.GetBinWidth(RootBkgHist.GetNbinsX()))

hist_bkg, bins_bkg = np.histogram(binCenter_bkg, bins=binEdge_bkg, weights=binWeight_bkg)
bkg = np.histogram(binCenter_bkg, bins=binEdge_bkg, weights=binWeight_bkg)

for num in range(startNum,endNum):
	inputFileSig = ROOT.TFile("FILE/PFN/SR/v8p1_PFNv6_{}_SR.root".format(num))
	RootSigHist = inputFileSig.Get("sigHist").Clone()
	expSigNum = RootSigHist.Integral()
	print(RootSigHist.Integral())
	binCenter_sig = []
	binWeight_sig = []
	binContent_sig = []
	binEdge_sig = []
	for i in range(1, RootSigHist.GetNbinsX() + 1):
		binCenter_sig.append(RootSigHist.GetBinCenter(i))
		binWeight_sig.append(RootSigHist.GetBinContent(i))
		binContent_sig.append(RootSigHist.GetBinContent(i))
		binEdge_sig.append(RootSigHist.GetBinLowEdge(i))
	binEdge_sig.append(RootSigHist.GetBinLowEdge(RootSigHist.GetNbinsX()) + RootSigHist.GetBinWidth(RootSigHist.GetNbinsX()))
	binsnum_sig = RootSigHist.GetNbinsX()

	#Sig
	hist_sig, bins_sig = np.histogram(binCenter_sig, bins=binEdge_sig, weights=binWeight_sig)

	signal = np.histogram(binCenter_sig, bins=binEdge_sig, weights=binWeight_sig)
	print("signal: ",num)

	# Create a BumpHunter1D class instance
	hunter = BH.BumpHunter1D(
		rang=rang,
		width_min=2,
		width_max=30,
		width_step=1,
		scan_step=1,
		npe=10000,
		nworker=1,
		seed=666,
		bins = binEdge_bkg,
	)
	hunter.sigma_limit = 0.01
	hunter.str_min = 0  # if str_scale='log', the real starting value is 10**str_min
	hunter.str_scale = "log"
	hunter.signal_exp = expSigNum# Correspond the the real number of signal events generated when making the data
	print("####singal_inject call####")
	begin = datetime.now()
	#hunter.signal_inject(hist_sig, hist_bkg, is_hist=True)
	hunter.signal_inject(signal[0], bkg[0], is_hist=True)
	end = datetime.now()
	print(f"time={end - begin}")
	print("")
	significance.append(hunter.significance)
	# Get and save the injection plot
	hunter.plot_inject(filename=("results/PFN/SR/1D/v8p1_PFNv6_{}_SR.png".format(num),"results/PFN/SR/1D/v8p1_PFNv6_{}_SR_log.png".format(num)))
	'''
	print("BUMP POSITION")
	print(bkg[1][hunter.min_loc_ar[0]])
	print(bkg[1][hunter.min_loc_ar[0]+hunter.min_width_ar[0]])

	dataHist  = hunter.data_inject
#	print(dataHist)
	hunter.bump_scan(data = dataHist, bkg = bkg[0],is_hist = True,do_pseudo = True)
	hunter.print_bump_info()
	hunter.print_bump_true(data = dataHist, bkg = bkg[0])
	print("")
	hunter.plot_tomography(bkg = bkg, is_hist = True, filename="results/PFN/SR/1D/tomography_v9p1_PFNv6_SR_bs_{}_SI.png".format(num))
	datatmp = [dataHist,bkg[1]]
	hunter.plot_bump(data = datatmp, bkg = bkg, is_hist = True, filename="results/PFN/SR/1D/bump_v9p1_PFNv6_SR_bs_{}_SI.png".format(num))
	hunter.plot_stat(show_Pval=True, filename="results/PFN/SR/1D/BH_statistics_v9p1_PFNv6_SR_bs_{}_SI.png".format(num))
	'''
	del inputFileSig
print(significance)
plot_dir  = "results/PFN/table/"
title = "BumpHunter Sensitivity"
sic_vals ={}
for i in range(startNum, endNum):
	sic_vals.update({str(i):{"bumpHunterSensitivity":significance[i-515487]}})

#print(sic_vals)
def do_grid_plots(sic_vals, title):
	with open("dsids_grid_locations.json", "r") as f:
		dsid_coords = json.load(f)
	dsids = list(sic_vals.keys())
	vals = list(sic_vals[dsids[0]].keys())
	for val in vals:
		values = np.zeros([4,10])
		for dsid in dsids:
			loc = tuple(dsid_coords[str(dsid)])
			values[loc] = sic_vals[dsid][val]
	make_grid_plot(values, val, title)

def make_grid_plot(values,title,method):
	fig,ax = plt.subplots(1,1)
	if (method.find("compare") != -1): img = ax.imshow(values, cmap='PiYG',norm=colors.LogNorm(vmin=0.1,vmax=10))
	else:
		if (title == "qcdEff"): img = ax.imshow(values,norm=colors.LogNorm(vmin=1e-7,vmax=1e-1))
		elif (title == "sigEff"): img = ax.imshow(values,vmin=-0.1,vmax=0.7)
		elif (title == "sensitivity_Inclusive" or title == "sensitivity_mT"): img = ax.imshow(values, norm=colors.LogNorm(vmin=1e-5,vmax=1.5))
		elif (title == "auc"): img = ax.imshow(values, vmin=0.7, vmax=1)
		elif (title == "sicMax"): img = ax.imshow(values, vmin=-2, vmax=20)
		else: img = ax.imshow(values, vmin = 0.01,vmax = 3.)
	for (j,i),label in np.ndenumerate(values):
		if label == 0.0: continue
		if title == "qcdEff" or title == "sensitivity_Inclusive" or title == "sensitivity_mT": ax.text(i,j,'{0:.1e}'.format(label),ha='center', va='center', fontsize = 'x-small')
		elif title == "score_cut": ax.text(i,j,'{0:.3f}'.format(label),ha='center', va='center', fontsize = 'x-small')
		else: ax.text(i,j,'{0:.2f}'.format(label),ha='center', va='center', fontsize = 'x-small')

	# x-ylabels for grid 
	x_label_list = ['1.0', '1.25', '1.5', '2.0', '2.5', '3.0', '3.5', '4.0', '5.0', '6.0']
	y_label_list = ['0.2', '0.4', '0.6', '0.8']
	ax.set_xticks([0,1,2,3,4,5,6,7,8,9])
	ax.set_xticklabels(x_label_list)
	ax.set_xlabel('Z\' Mass [TeV]')
	ax.set_yticks([0,1,2,3])
	ax.set_yticklabels(y_label_list)
	ax.set_ylabel('$R_{inv}$')


	ax.set_title(method)
	plt.savefig(plot_dir+'table_'+title+'_SR.png')
	print("Saved grid plot for", title)
do_grid_plots(sic_vals, title)
