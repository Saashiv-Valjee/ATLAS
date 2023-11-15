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

inputFile = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit_toy.root")

inputFileBkg = ROOT.TFile("FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.root")


RootDataHist = inputFile.Get("toyHist").Clone()

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
	check_bkg = check_bkg + RootDataHist.GetBinContent(i)
binsnum_bkg = RootBkgHist.GetNbinsX()
binEdge_bkg.append(RootBkgHist.GetBinLowEdge(RootBkgHist.GetNbinsX()) + RootBkgHist.GetBinWidth(RootBkgHist.GetNbinsX()))

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
print(np.array_equal(binWeight_data,binWeight_bkg))

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
plt.savefig("results/PFN/SR/1D/hist_v8p1_PFNv6_SR_toy.png", bbox_inches="tight")
plt.close(F)
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
print(f"time={end - begin}")
print("")

# Print bump
hunter.print_bump_info()
hunter.print_bump_true(data = data[0], bkg = bkg[0])
print("")
# Get and save tomography plot
hunter.plot_tomography(bkg = bkg, is_hist = True, filename="results/PFN/SR/1D/tomography_v8p1_PFNv6_SR_toy.png")

# Get and save bump plot
hunter.plot_bump(data = data, bkg = bkg, is_hist = True, filename="results/PFN/SR/1D/bump_v8p1_PFNv6_SR_toy.png")

# Get and save statistics plot
hunter.plot_stat(show_Pval=True, filename="results/PFN/SR/1D/BH_statistics_v8p1_PFNv6_SR_toy.png")
