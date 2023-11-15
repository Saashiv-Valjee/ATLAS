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
#import pyBumpHunter as BH
import ROOT
import numpy as np

significance_PFN = [0.1850370189157764, 0.3329129418188543, 0.40456131384608157, 0.418748426459625, 0.21752400698234517, 0.3010190081071385, 0.3204859228743067, 0.25464150404674546, 0.26812903127971355, 0.34166900533109756, 0.26631061320409494, 0.1967796202184669, 0.19601298830223432, 0.2182940629559168, 0.1753558876651384, 0.10597775716289194, 0.12515606339348176, 0.13476206488943726, 0.0903614371292588, 0.07124847744177844, 0.08708996732542452, 0.08809647252220675, 0.06923822116766862, 0.04664018984972224, 0.06421378651468006, 0.0674794767003114, 0.05090653259904658, 0.05316555488880454, 0.05316555488880454, 0.042374695865204634, 0.03384594262165147, 0.03409675013052506, 0.016043109130585573, 0.02883021851774065, 0.029331756209256883, 0.01704589771498901, 0.030836414058675342, 0.04212380922073046, 0.014288267319718518, 0.03384594262165147]
significance_CMS = [0.06521853970954372, 0.1822328423863417, 0.2751513003775951, 0.31021166554591967, 0.06823319845380023, 0.12060993411930736, 0.15274420400321673, 0.16492883009491788, 0.1489412391253356, 0.20342866086162797, 0.14742065918693903, 0.09766287001317407, 0.13273874487280113, 0.13273874487280113, 0.10522156413190162, 0.060697654093910605, 0.10068565393169764, 0.10597775716289194, 0.0752698620998299, 0.05969318454768027, 0.06823319845380023, 0.08381942934025638, 0.05969318454768027, 0.045385548179409145, 0.03284273371844666, 0.03961508598957968, 0.026322636310952642, 0.02983330127899372, 0.011781425432630896, 0.011029388020358915, 0.013786892263084419, 0.011029388020358915, 0.02080651581056588, 0.013034836136889385, 0.018800819591187814, 0.024316690467047535, 0.011781425432630896, 0.020054370352950636, 0.024065954281736284, 0.0401168101849681]

#open a root file and convert the inputs to np histograms
plot_dir  = "results/table/"
title = "BumpHunter Sensitivity"
sic_vals ={}
significance_cmp = [0 for i in range(0, 40)] 
for i in range(0, 40):
	significance_cmp[i] = significance_PFN[i] / significance_CMS[i]
	sic_vals.update({str(i+515487):{"bumpHunterSensitivity":significance_cmp[i]}})
#print(significance_cmp)
print(sic_vals)
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
	plt.savefig(plot_dir+'table_'+title+'_SR_PFN_CMS.png')
	print("Saved grid plot for", title)
do_grid_plots(sic_vals, title)
