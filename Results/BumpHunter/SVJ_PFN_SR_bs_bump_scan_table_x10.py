# Here we test pyBumpHunter.
# The result can be compared to what can be obtained with the original C++ version.
# We will use histograms ranging between 0 and 20 with 60 even bins.

import os,sys
import matplotlib
matplotlib.use("Agg")
from datetime import datetime  # # Used to compute the execution time

import matplotlib.pyplot as plt
import uproot  # # Used to read data from a root file
import pyBumpHunter as BH
import ROOT
import numpy as np
import json
#open a root file and convert the inputs to np histograms

significance = []
startNum = 515487
endNum = 515527
inputFileBkg = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.root")

RootBkgHist = inputFileBkg.Get("bkgHist").Clone()


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


for num in range(startNum, endNum):
	inputFile = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_{}_SR_x10.root".format(num))
#	inputFile = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_515504_SR.root")
	RootDataHist = inputFile.Get("dataHist").Clone()
	print("Background number: ", RootBkgHist.Integral())
	print("Data number: ", RootDataHist.Integral())
	binCenter_data = []
	binWeight_data = []
	binEdge_data = []
	binContent_data = []
	data = []
	for i in range(1, RootDataHist.GetNbinsX() + 1):
		binCenter_data.append(RootDataHist.GetBinCenter(i))
		binWeight_data.append(RootDataHist.GetBinContent(i))
		data.append(RootDataHist.GetBinContent(i))
		binEdge_data.append(RootDataHist.GetBinLowEdge(i))
	binsnum_data = RootDataHist.GetNbinsX()
	binEdge_data.append(RootDataHist.GetBinLowEdge(RootDataHist.GetNbinsX()) + RootDataHist.GetBinWidth(RootDataHist.GetNbinsX()))

	#BKG
	hist_bkg, bins_bkg = np.histogram(binCenter_bkg, bins=binEdge_bkg, weights=binWeight_bkg)
	bkg = np.histogram(binCenter_bkg, bins=binEdge_bkg, weights=binWeight_bkg)
	#Data
	hist_data, bins_data = np.histogram(binCenter_data, bins=binEdge_data, weights=binWeight_data)
	data = np.histogram(binCenter_data, bins=binEdge_data, weights=binWeight_data)
	# Position of the bump in the data

	# Range for the histograms (same that the one used with C++ BumpHunter)
	rang = [1200, 5000]
	# Plot the 2 distributions
	F = plt.figure(figsize=(12, 8))
	plt.title("Bkg-only distribution")
	plt.hist(
		x = binCenter_data,
		weights = binWeight_data,
		bins=binCenter_data,
		histtype="bar",
		alpha = 0.5,
		range=rang,
		color = "red",
		label=("data"),
		linewidth=2,
	)
	plt.hist(
		x = binCenter_bkg,
		weights = binWeight_bkg,
		bins=binCenter_bkg,
		histtype="bar",
		alpha = 0.5,
		range=rang,
		color = "blue",
		label=("background"),
		linewidth=2,
	)
	plt.legend()
	plt.savefig("results/PFN/SR/1D/hist_v9p1_PFNv6_SR_bs_{}_x10.png".format(num), bbox_inches="tight")
	plt.close(F)

#for num in range(1,30):
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
	# Call the bump_scan method
	print("####bump_scan call####")
	begin = datetime.now()
	hunter.bump_scan(data = data[0], bkg = bkg[0],is_hist = True)
	end = datetime.now()
	significance.append(hunter.significance)
	print(f"time={end - begin}")
	print("")

	# Print bump
	hunter.print_bump_info()
	hunter.print_bump_true(data = data[0], bkg = bkg[0])
	print("")

	# Get and save tomography plot
	hunter.plot_tomography(bkg = bkg, is_hist = True, filename="results/PFN/SR/1D/tomography_v9p1_PFNv6_SR_bs_{}_x10.png".format(num))
	# Get and save bump plot
	hunter.plot_bump(data = data, bkg = bkg, is_hist = True, filename="results/PFN/SR/1D/bump_v9p1_PFNv6_SR_bs_{}_x10.png".format(num))

	# Get and save statistics plot
	hunter.plot_stat(show_Pval=True, filename="results/PFN/SR/1D/BH_statistics_v9p1_PFNv6_SR_bs_{}_x10.png".format(num))
	del inputFile
	del RootDataHist

print(significance)
plot_dir  = "results/PFN/table/"
title = "BumpHunter Sensitivity"
sic_vals ={}
for i in range(startNum, endNum):
    sic_vals.update({str(i):{"bumpHunterSensitivity":significance[i-515487]}})
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
		else: img = ax.imshow(values, vmin = 0.)
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
	plt.savefig(plot_dir+'table_'+title+'_SR_BH_x10.png')
	print("Saved grid plot for", title)
do_grid_plots(sic_vals, title)
'''
for num in range(0,29):
	print("initial bin width: {}GeV".format((num+1)*50),significance[num])
'''
