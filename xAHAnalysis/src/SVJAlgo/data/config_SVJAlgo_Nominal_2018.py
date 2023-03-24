import ROOT
from xAODAnaHelpers import Config
import shlex
import argparse
import sys
import os

sys.path.insert(0, os.environ['WorkDir_DIR']+"/data/SVJAlgo/")

parser = argparse.ArgumentParser(description='Test for extra options')

# object controls
parser.add_argument('--doFatJet', dest='doFatJet', action="store_true", default=False)

opt = parser.parse_args(shlex.split(args.extra_options))

c = Config()

#%%%%%%%%%%%%%%%%%%%%%%%%%% BasicEventSelection %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("BasicEventSelection",    { 
  "m_name"                      : "BasicEventSelect",
  #-------------------------- GRL --------------------------------------#
  "m_GRLxml"                    : 'GoodRunsLists/data18_13TeV/20190318/data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml,GoodRunsLists/data17_13TeV/20180619/data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml,GoodRunsLists/data15_13TeV/20170619/data15_13TeV.periodAllYear_DetStatus-v89-pro21-02_Unknown_PHYS_StandardGRL_All_Good_25ns.xml,GoodRunsLists/data16_13TeV/20180129/data16_13TeV.periodAllYear_DetStatus-v89-pro21-01_DQDefects-00-02-04_PHYS_StandardGRL_All_Good_25ns.xml',
  #-------------------------- PRW --------------------------------------#
  #"m_doPUreweighting"           : False,
  #"m_lumiCalcFileNames"         : "",
  #"m_autoconfigPRW"             : False,
  #"m_PRWFileNames"              : "",
  #-------------------------- Derivation -------------------------------#
  "m_derivationName"            : "PHYS",
  # -------------------------- Trigger ----------------------------------#
   "m_triggerSelection"          : "HLT_j380 || HLT_j360 || HLT_j225_gsc380_boffperf_split || HLT_j225_gsc420_boffperf_split",
   "m_storePassHLT"              : True,
   "m_storeTrigDecisions"        : True,
   "m_storePassL1"               : True,
   "m_storeTrigKeys"             : False,
   "m_applyTriggerCut"           : True,
  # ---------------------------- Cuts ----------------------------------#
  "m_checkDuplicatesData"       : True,
  "m_applyGRLCut"               : True,
  "m_applyEventCleaningCut"     : True,
  "m_applyJetCleaningEventFlag" : True,
  "m_applyCoreFlagsCut"	        : True,
  "m_vertexContainerName"       : "PrimaryVertices",
  "m_applyPrimaryVertexCut"     : True,
  "m_PVNTrack"                  : 2,
  #---------------------------- Other ---------------------------------#
  "m_useMetaData"               : False,
  "m_msgLevel"                  : "Error",
})

#%%%%%%%%%%%%%%%%%%%%%%%%%% JetCalibrator %%%%%%%%%%%%%%%%%%%%%%%%%%#

# Small-r jet

c.algorithm("JetCalibrator",     {
  "m_name"                      : "JetCalibrate",
  #----------------------- Container Flow ----------------------------#
  "m_inContainerName"           : "AntiKt4EMPFlowJets",
  "m_jetAlgo"                   : "AntiKt4EMPFlow",
  "m_outContainerName"          : "Jets_Calibrate",
  "m_outputAlgo"                : "JetCalibrator_Syst",
  "m_sort"                      : True,
  #"m_redoJVT"                   : False,
  #----------------------- Systematics ----------------------------#
  "m_systName"                  : 'Nominal',
  "m_systVal"                   : 0,
  #----------------------- Calibration ----------------------------#
  #"m_calibConfigAFII"           : "JES_MC16Recommendation_AFII_PFlow_Apr2019_Rel21.config",        # recommendation as of May 11 2020
  "m_calibConfigFullSim"        : "PreRec_R22_PFlow_ResPU_EtaJES_GSC_February23_230215.config",   # recommendation as of Feb 15 2023
  "m_calibConfigData"           : "PreRec_R22_PFlow_ResPU_EtaJES_GSC_February23_230215.config",   # recommendation as of Feb 15 2023
  "m_calibSequence"             : "JetArea_Residual_EtaJES_GSC_Insitu",                           # recommendation as of Feb 15 2023
  "m_forceInsitu"               : False, # For data
  "m_forceSmear"                : False, # For MC
  #----------------------- JES/JER Uncertainty ----------------------------#
  "m_uncertConfig"              : "rel21/Summer2019/R4_SR_Scenario1_SimpleJER.config",  # recommendation as of May 11 2020
  "m_uncertMCType"              : "MC16",
  #----------------------- Cleaning ----------------------------#
  # Turn it off for the moment, need to add it back
  "m_doCleaning"                : False,
  "m_jetCleanCutLevel"          : "LooseBad",
  "m_jetCleanUgly"              : False,
  "m_saveAllCleanDecisions"     : False,
  "m_cleanParent"               : False,
  #----------------------- Other ----------------------------#
  "m_msgLevel"                  : "Info",

})


#%%%%%%%%%%%%%%%%%%%%%%%%%% JetSelector %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("JetSelector",     {
  "m_name"                      : "JetSelect",
  #----------------------- Container Flow ----------------------------#
  "m_inContainerName"           : "Jets_Calibrate",
  "m_outContainerName"          : "Jets_Selected",
  "m_inputAlgo"                 : "JetCalibrator_Syst",
  "m_outputAlgo"                : "JetSelector_Syst",
  "m_decorateSelectedObjects"   : True,
  "m_createSelectedContainer"   : True,
  #----------------------- Selections ----------------------------#
  "m_cleanJets"                 : True,
  "m_pass_min"                  : 2,
  "m_pT_min"                    : 20e3,
  "m_eta_max"                   : 4.5,
  "m_useCutFlow"		: True,
  #----------------------- JVT ----------------------------#
  "m_doJVT"                     : False, # JVT is a pileup cut
  "m_pt_max_JVT"                : 60e3,
  "m_eta_max_JVT"               : 2.4,
  "m_JVTCut"                    : 0.2,
  #----------------------- B-tagging ----------------------------#
  "m_doBTagCut"                 : False,
  "m_corrFileName"              : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/xAODBTaggingEfficiency/13TeV/2021-22-13TeV-MC16-CDI-2021-12-02_v2.root",
  "m_taggerName"                : "DL1dv00",
  "m_jetAuthor"                 : "AntiKt4EMPFlowJets",
  "m_b_pt_min"                  : 25e3,
  "m_b_eta_max"                 : 2.5,
  #----------------------- Other ----------------------------#
  "m_msgLevel"                  : "Info",
})


#%%%%%%%%%%%%%%%%%%%%%%%%% Muon Calibrator %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("MuonCalibrator",	 {
  "m_name"                      : "MuonCalibrate",
  #----------------------- Container Flow ----------------------------#
  "m_inContainerName"           : "Muons",
  "m_outContainerName"          : "Muons_Calibrate",
  #----------------------- Systematics ----------------------------#
  "m_systName"                  : "Nominal",
  "m_systVal"                   : 0,
  "m_outputAlgoSystNames"       : "MuonCalibrator_Syst",
  #----------------------- Other ----------------------------#
  "m_sort"                      : True,
  "m_forceDataCalib"		: True,
  "m_calibrationMode"           : "correctData_IDMS",
  "m_msgLevel"                  : "Info"
})

#%%%%%%%%%%%%%%%%%%%%%%%%% Muon Selector %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("MuonSelector", {
    "m_name"                    : "MuonSelector",
    "m_inContainerName"         : "Muons_Calibrate",
    "m_outContainerName"        : "Muons_Selected",
    "m_createSelectedContainer" : True,
    "m_pT_min"                  : 20000.,
    "m_eta_max"                 : 2.5,
    "m_d0sig_max"               : 3,
    "m_z0sintheta_max"          : 0.5,
    "m_muonQualityStr"          : "Medium",
    "m_doIsolation"             : True,
    "m_MinIsoWPCut"             : "PflowTight_VarRad",
    "m_IsoWPList"               : "PflowTight_VarRad",
    "m_inputAlgoSystNames"      : "MuonCalibrator_Syst",
    "m_outputAlgoSystNames"     : "MuonSelector_Syst",
    "m_systName"                : "Nominal",
    "m_systVal"                 : 0,
    "m_removeEventBadMuon"      : False
})


#%%%%%%%%%%%%%%%%%%%%%%%%% Electron Calibrator %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("ElectronCalibrator",	 {
  "m_name"                      : "ElectronCalibrate",
  #----------------------- Container Flow ----------------------------#
  "m_inContainerName"           : "Electrons",
  "m_outContainerName"          : "Electrons_Calibrate",
  #----------------------- Systematics ----------------------------#
  "m_systName"                  : "Nominal",
  "m_systVal"                   : 0,
  "m_esModel"			: "es2022_R22_PRE",
  "m_decorrelationModel"	: "1NP_v1",
  "m_outputAlgoSystNames"       : "ElectronCalibrator_Syst",
  #----------------------- Other ----------------------------#
  "m_sort"                      : True,
  "m_msgLevel"                  : "Info"
})

#%%%%%%%%%%%%%%%%%%%%%%%%% Electron Selector %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("ElectronSelector", {
    "m_name"                      : "ElectronSelector",
    "m_inContainerName"           : "Electrons_Calibrate",
    "m_outContainerName"          : "Electrons_Selected",
    "m_createSelectedContainer"   : True,
    "m_pT_min"                    : 20000.,
    "m_eta_max"                   : 2.47,
    "m_d0sig_max"                 : 5,
    "m_z0sintheta_max"            : 0.5,
    "m_readIDFlagsFromDerivation" : True,
    "m_IsoWPList"                 : "Tight_VarRad",
    "m_MinIsoWPCut"               : "Tight_VarRad",
    "m_doOQCut"                   : True,
    "m_vetoCrack"                 : True,
    "m_doLHPID"                   : True,
    "m_doLHPIDcut"                : True,
    "m_LHOperatingPoint"          : "Tight",
    "m_inputAlgoSystNames"        : "ElectronCalibrator_Syst",
    "m_outputAlgoSystNames"       : "ElectronSelector_Syst",
    "m_systName"                  : "Nominal",
    "m_systVal"                   : 0,
})

#%%%%%%%%%%%%%%%%%%%%%%%%%% Overlap Removal %%%%%%%%%%%%%%%%%%%%%%%%%%#
#Note: OR must not be applied to the containers passed to METmaker.
c.algorithm("OverlapRemover", {
    "m_name"                       : "OverlapRemover",
    "m_useCutFlow"                 : False,
    "m_decorateSelectedObjects"    : True,
    "m_inContainerName_Jets"       : "Jets_Selected",
    "m_inContainerName_Electrons"  : "Electrons_Selected",
    "m_inContainerName_Muons"      : "Muons_Selected",
    "m_inputAlgoJets"              : "JetSelector_Syst",
    "m_inputAlgoMuons"             : "MuonSelector_Syst",
    "m_inputAlgoElectrons"         : "ElectronSelector_Syst",
    "m_outContainerName_Jets"      : "Jets_PassedOR",
    "m_outContainerName_Electrons" : "Electrons_PassedOR",
    "m_outContainerName_Muons"     : "Muons_PassedOR",
    "m_outputAlgoSystNames"        : "OverlapRemovalAlgo_Syst",
})


#%%%%%%%%%%%%%%%%%%%%%%%%%% MetConstructor %%%%%%%%%%%%%%%%%%%%%%%%%%#
#Note: OR must not be applied to the containers passed to METmaker.
c.algorithm("METConstructor",     {
  "m_name"			: "METConstructor",
  "m_inputJets"			: "Jets_Selected",
  "m_inputElectrons"		: "Electrons_Selected",
  "m_inputMuons"		: "Muons_Selected",
  "m_calculateSignificance"	: True,
  "m_significanceTreatPUJets"	: False, #disable signifiance for PU jets as it requires fjvt decorations which are not available
  "m_msgLevel"                	: "Info",
  "m_coreName"			: "MET_Core_AntiKt4EMPFlow",
  "m_mapName"			: "METAssoc_AntiKt4EMPFlow",
  "m_doPFlow"			: True, 
  "m_outputContainer"		: "METOutput_NewRefFinal",
})

#%%%%%%%%%%%%%%%%%%%%%%%%%% BJetEfficiencyCorrector %%%%%%%%%%%%%%%%%%%%%%%%%%#
bJetWPs = ["FixedCutBEff_60", "FixedCutBEff_70", "FixedCutBEff_77", "FixedCutBEff_85"]
taggers = ["DL1dv00"]

for tagger in taggers:
  for bJetWP in bJetWPs:
    name = tagger + "_" + bJetWP
    c.algorithm("BJetEfficiencyCorrector",     {
      "m_name"                    : name,
      #----------------------- Container Flow ----------------------------#
      "m_inContainerName"         : "Jets_Selected",
      "m_jetAuthor"               : "AntiKt4EMPFlowJets",
      "m_decor"                   : "BTag",
      "m_outputSystName"          : "BJetEfficiency_Algo",
      #----------------------- B-tag Options ----------------------------#
      "m_corrFileName"            : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/xAODBTaggingEfficiency/13TeV/2021-22-13TeV-MC16-CDI-2021-12-02_v2.root",
      "m_taggerName"              : tagger,
      "m_operatingPt"             : bJetWP,
      "m_coneFlavourLabel"        : True,
      "m_useDevelopmentFile"      : False,
      #----------------------- Other ----------------------------#
      "m_msgLevel"                : "Info"
  })

inFatJetContainerName = ""
inputFatAlgo = ""
fatJetDetailStr = ""
if opt.doFatJet:
      inFatJetContainerName = "FatJets_Selected"
      inputFatAlgo = "FatJetSelector_Syst"
      fatJetDetailStr = "kinematic substructure truth"
##%%%%%%%%%%%%%%%%%%%%%%%%%% SVJAlgo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("SVJAlgorithm",    		 {
    "m_name"                    	: "ResonanceAlgo",
    #----------------------- Container Flow ----------------------------#
    "m_inJetContainerName"      	: "Jets_PassedOR",
    "m_inEleContainerName"              : "Electrons_PassedOR", 
    "m_inMuContainerName"               : "Muons_PassedOR", 
    "m_inputAlgo"               	: "JetSelector_Syst",
    "m_inMetContainerName"      	: "METOutput_NewRefFinal",
    "m_inFatJetContainerName"   	: inFatJetContainerName,
    "m_inputFatAlgo"            	: inputFatAlgo,
    #----------------------- Selections ----------------------------#
    "m_leadingJetPtCut"         	: 450e3,
    "m_subleadingJetPtCut"      	: 50e3,
    "m_leadingJetEtaCut"         	: 2.1,
    "m_subleadingJetEtaCut"      	: 2.1,
    "m_metCut"                  	: -1,
    "m_jetMultiplicity"         	: 2,
    "m_yStarCut"			: 1.4,
    #----------------------- Lepton Veto ----------------------------#
    "m_doLepVeto"                       : True,
    #----------------------- Output ----------------------------#
    "m_reclusterJets"           	: False,
    "m_eventDetailStr"          	: "",
    "m_jetDetailStr"            	: "kinematic trackPV flavorTag energy",
    "m_fatJetDetailStr"	        	: fatJetDetailStr,
    "m_metDetailStr"            	: "metClus",
    "m_jetDetailStrSyst"        	: "kinematic",
    "m_trigDetailStr"           	: "basic passTriggers",
    #----------------------- Other ----------------------------#
    "m_writeTree"               : True,
    "m_msgLevel"                : "Info",
})
