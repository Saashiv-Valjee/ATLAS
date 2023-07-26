loglevel=info
extra=""
#extra="--inputList"

# this  has to be somewhere you can write
parentsubmitdir="/afs/cern.ch/work/e/ebusch/public/SVJ/ana-exot-2021-19/xAHAnalysis/run/"

## Signal
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/mc20_13TeV.515499.MGPy8EG_SVJSChan2j_2000_2.deriv.DAOD_PHYS.e8461_s3995_r13167_p5440/DAOD_PHYS.31295849._000001.pool.root.1"
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/mc20_13TeV.515501.MGPy8EG_SVJSChan2j_2000_6.deriv.DAOD_PHYS.e8461_s3995_r13167_p5440/DAOD_PHYS.31295968._000001.pool.root.1"
#configFile=../src/SVJAlgo/data/config_SVJAlgo_MC.py

## Emerging jets
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/mc21_13p6TeV.801925.Py8EG_Zprime2EJs_Ld1p6_rho3p2_pi0p8_Zp600_l1.deriv.DAOD_PHYS.e8453_s3873_r13829_p5440/DAOD_PHYS.31233085._000001.pool.root.1"
#configFile=../src/SVJAlgo/data/config_SVJAlgo_signal.py

## Multijet
infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/mc20_13TeV.364704.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ4WithSW.deriv.DAOD_PHYS.e7142_s3681_r13145_p5440/DAOD_PHYS.31204919._000037.pool.root.1"
configFile=../src/SVJAlgo/data/config_SVJAlgo_MC.py

## Z+jets
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/mc20_13TeV.700325.Sh_2211_Zmumu_maxHTpTV2_CVetoBVeto.deriv.DAOD_PHYS.e8351_s3681_r13144_p5440/DAOD_PHYS.31209885._000061.pool.root.1"
#configFile=../src/SVJAlgo/data/config_SVJAlgo_MC.py

## Data
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/data18_13TeV.00348618.physics_Main.deriv.DAOD_PHYS.r13286_p4910_p5440/DAOD_PHYS.31130202._000295.pool.root.1"
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/data18_13TeV.00349114.physics_Main.deriv.DAOD_PHYS.r13286_p4910_p5440/DAOD_PHYS.31140513._000131.pool.root.1"
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/data16_13TeV.00297730.physics_Main.deriv.DAOD_PHYS.r13286_p4910_p5440/DAOD_PHYS.31139769._000073.pool.root.1"
#configFile=../src/SVJAlgo/data/config_SVJAlgo_data.py

## JETM2
#infile="/eos/atlas/atlascerngroupdisk/phys-exotics/jdm/svjets-schannel/DAODs/mc20_13TeV.364704.Pythia8EvtGen_A14NNPDF23LO_jetjet_JZ4WithSW.deriv.DAOD_JETM2.e7142_s3681_r13145_p5548/DAOD_JETM2.32404148._000230.pool.root.1"
#configFile=../src/SVJAlgo/data/config_SVJAlgo_MC.py

nevents=10000
submitdir=QCD_to_TTREE_${nevents}

echo "xAH_run.py --files ${infile} --nevents $nevents --config $configFile --extraOptions="" --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct "
xAH_run.py --files ${infile} --nevents $nevents --config $configFile --extraOptions="" --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct 

# test command for using rucio with file list
#filelisttxt="/afs/cern.ch/user/m/mamerl/TLAWork/inputlisttest.txt"
#echo "xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct"
#xAH_run.py --files ${filelisttxt} --inputList --inputRucio --nevents $nevents --config $configFile --submitDir ${parentsubmitdir}/$submitdir --log-level $loglevel $extra --force direct

#The large-R jets are not used by default. To turn it on you should do:

#xAH_run.py --config ../ana-exot-2021-19/SVJAlgo/data/config_SVJAlgo_ZJets.py --files /eos/user/b/biliu/mc20_13TeV/DAOD_PHYS.28690183._000001.pool.root.1 --extraOptions="--doFatJet" --isMC --submitDir test direct
