initial commit for BumpHunter in the context of the Summer Student project by Zhiyuan Huang

***BH sensitivity table by signal injection***

source setup.sh		#To activate BH under python3.9.12
source mkdir.sh		#To make directories that we need

python3 h52root_PFN_bkg_SR.py		#Transfer the 
/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v9/v9.1/v9p1_PFNv6_totalBkgALL_skim0.hdf5
into FILE/PFN/SR/v9p1_PFNv6_totalBkgALL_skim0_SR.root

source h52root_signal.sh		#Transfer the /eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/v8/v8.1/v8p1_PFNv6_i.hdf5 into FILE/PFN/SR/v8p1_PFNv6_i_SR.root (i from 515487 to 515526)

root -b check_PFN_bkg.C		#Draw the distribution of v9p1_PFNv6_totalBkgALL_skim0_SR.root and save in results/PFN/check/SR/ directory 

root -b check_PFN_sig.C		#Draw the distribution of v8p1_PFNv6_i_SR.root and save in results/PFN/check/SR/ directory (i from 515487 to 515526)

python3 BKG_PFN_SR_histfit.py		#Use TH1.fitto() to fit the v9p1_PFNv6_totalBkgALL_skim0_SR.root and generate two files one(v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.root) is for signal injection and BH. The other one (v9p1_PFNv6_totalBkgALL_skim0_SR_histfit.root) is for background-only check.

python3 SVJ_PFN_SR_signal_injection.py 515487 515526		#Use signal injection to calculate the sensitivity and generate the sensitivity table

 


