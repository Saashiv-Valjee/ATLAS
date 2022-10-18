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
  "m_applyGRLCut"               : False, 
  "m_GRLxml"                    : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data17_13TeV/20180619/data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_JetHLT_Normal2017.xml",
  "m_derivationName"            : "PHYS",
  "m_useMetaData"               : False,
  "m_storePassHLT"              : True,
  "m_storeTrigDecisions"        : True,
  "m_storePassL1"	        : True,
  "m_storeTrigKeys" 	        : False,
  "m_applyTriggerCut"           : False,
  "m_doPUreweighting"           : False,
  "m_autoconfigPRW"             : False,
  "m_PRWFileNames"              : "",
  "m_lumiCalcFileNames"         : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/ilumicalc_histograms_None_276262-284154.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/ilumicalc_histograms_None_297730-299243.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/ilumicalc_histograms_None_325713-338349_OflLumi-13TeV-001.root",
  "m_autoconfigPRW"             : False,
  "m_triggerSelection"          : ".*",
  "m_checkDuplicatesData"       : False,
  "m_applyEventCleaningCut"     : True,
  "m_applyCoreFlagsCut"	        : True,
  "m_vertexContainerName"       : "PrimaryVertices",
  "m_applyPrimaryVertexCut"     : True, 
  "m_PVNTrack"		        : 2,
  "m_msgLevel"                  : "Info",
  "m_applyJetCleaningEventFlag" : True,
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
  "m_redoJVT"                   : False,
  #----------------------- Systematics ----------------------------#
  "m_systName"                  : 'Nominal',
  "m_systVal"                   : 0,
  #----------------------- Calibration ----------------------------#
  "m_calibConfigAFII"           : "JES_MC16Recommendation_AFII_PFlow_Apr2019_Rel21.config",        # recommendation as of May 11 2020
  "m_calibConfigFullSim"        : "JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config",# recommendation as of May 11 2020
  "m_calibConfigData"           : "JES_MC16Recommendation_AFII_PFlow_Apr2019_Rel21.config",        # recommendation as of May 11 2020
  "m_calibSequence"             : "JetArea_Residual_EtaJES_GSC_Smear",                                    # recommendation as of May 11 2020
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

# large-r jet
if opt.doFatJet:
  c.algorithm("JetCalibrator",     {
    "m_name"                      : "FatJetCalibrate",
    #----------------------- Container Flow ----------------------------#
    "m_inContainerName"           : "AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets",
    "m_jetAlgo"                   : "AntiKt10LCTopoTrimmedPtFrac5SmallR20",
    "m_outContainerName"          : "FatJets_Calibrate",
    "m_outputAlgo"                : "FatJetCalibrator_Syst",
    "m_sort"                      : True,
    "m_redoJVT"                   : False,
    #----------------------- Systematics ----------------------------#
    "m_systName"                  : 'Nominal',
    "m_systVal"                   : 0,
    #----------------------- Calibration ----------------------------#
    "m_calibConfigFullSim"        : "JES_MC16recommendation_FatJet_Trimmed_JMS_comb_17Oct2018.config",
    "m_calibConfigData"           : "JES_MC16recommendation_FatJet_Trimmed_JMS_comb_March2021.config",
    "m_calibSequence"             : "EtaJES_JMS",                                    # recommendation as of May 11 2020
    "m_forceInsitu"               : False, # For data
    "m_forceSmear"                : False, # For MC
    #----------------------- JES/JER Uncertainty ----------------------------#
    "m_uncertConfig"              : "rel21/Winter2021/R10_CategoryJES_FullJER_FullJMS.config",  # recommendation as of May 11 2020
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
  "m_cleanJets"                 : False,
  "m_pass_min"                  : 1,
  "m_pT_min"                    : 25e3,
  "m_eta_max"                   : 5,
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

#%%%%%%%%%%%%%%%%%%%%%%%%%% MetConstructor %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("METConstructor",     {
  "m_name": "METConstructor",
  "m_inputJets": "Jets_Selected",
  "m_inputElectrons": "Electrons",
  "m_inputMuons": "Muons",
  "m_calculateSignificance": True,
  "m_significanceTreatPUJets": False, #disable signifiance for PU jets as it requires fjvt decorations which are not available
  "m_msgLevel"                : "Info",
  "m_coreName": "MET_Core_AntiKt4EMPFlow",
  "m_mapName": "METAssoc_AntiKt4EMPFlow",
  "m_outputContainer": "METOutput_NewRefFinal",
})

inFatJetContainerName = ""
inputFatAlgo = ""
fatJetDetailStr = ""
if opt.doFatJet:
      inFatJetContainerName = "FatJets_Calibrate",
      inputFatAlgo = "FatJetCalibrator_Syst",
      fatJetDetailStr = "kinematic substructure constituent constituentAll scales area"
##%%%%%%%%%%%%%%%%%%%%%%%%%% DijetResonanceAlgo %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("SVJAlgorithm",     {
    "m_name"                    : "ResonanceAlgo",
    #----------------------- Container Flow ----------------------------#
    "m_inJetContainerName"      : "Jets_Selected",
    "m_inputAlgo"               : "JetSelector_Syst",
    "m_inMetContainerName"      : "METOutput_NewRefFinal",
    "m_inFatJetContainerName"   : inFatJetContainerName,
    "m_inputFatAlgo"            : inputFatAlgo,
    #----------------------- Selections ----------------------------#
    "m_leadingJetPtCut"         : 100e3,
    "m_subleadingJetPtCut"      : 50e3,
    "m_jetMultiplicity"         : 2,
    "m_metCut"      : 500e3,
    #----------------------- Output ----------------------------#
    "m_doBtag"                  : False,
    "m_reclusterJets"           : False,
    "m_eventDetailStr"          : "truth pileup", #shapeEM
    "m_jetDetailStr"            : "kinematic rapidity truth",
    "m_fatJetDetailStr"	        : fatJetDetailStr,
    "m_metDetailStr"            : "metClus sigClus",
    "m_jetDetailStrSyst"        : "kinematic rapidity truth",
    "m_trigDetailStr"           : "basic menuKeys passTriggers",
    #----------------------- Other ----------------------------#
    "m_writeTree"               : True,
    #"m_MCPileupCheckContainer"  : "AntiKt4TruthJets",
    "m_MCPileupCheckContainer"  : "None",
#    "m_truthLevelOnly"          : False , #Protection when running on truth xAOD.
    "m_msgLevel"                : "Info",
})

