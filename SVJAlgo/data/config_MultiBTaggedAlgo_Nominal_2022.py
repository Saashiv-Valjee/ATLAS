import ROOT
from xAODAnaHelpers import Config
import shlex
import argparse
import sys
import os

sys.path.insert(0, os.environ['WorkDir_DIR']+"/data/MultiBTaggedAlgo/")

parser = argparse.ArgumentParser(description='Test for extra options')

# object controls
parser.add_argument('--doFatJet', dest='doFatJet', action="store_true", default=False)

opt = parser.parse_args(shlex.split(args.extra_options))

c = Config()

#%%%%%%%%%%%%%%%%%%%%%%%%%% BasicEventSelection %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("BasicEventSelection",    { 
  "m_name"                      : "BasicEventSelect",
  "m_applyGRLCut"               : False, 
  "m_GRLxml"                    : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190318/data18_13TeV.periodAllYear_DetStatus-v102-pro22-04_Unknown_PHYS_StandardGRL_All_Good_25ns_Triggerno17e33prim.xml",
  "m_derivationName"            : "PHYS",
  "m_useMetaData"               : False,
  "m_storePassHLT"              : False,
  "m_storeTrigDecisions"        : False,
  "m_storePassL1"	        : False,
  "m_storeTrigKeys" 	        : False,
  "m_applyTriggerCut"           : False,
  "m_doPUreweighting"           : False,
  "m_PRWFileNames"              : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361023.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361024.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361025.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361026.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361027.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361028.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361029.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361030.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361031.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/PRW_AUTOCONFIG/files/pileup_mc16d_dsid361032.root",
  "m_lumiCalcFileNames"         : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/ilumicalc_histograms_None_276262-284154.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/ilumicalc_histograms_None_297730-299243.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/ilumicalc_histograms_None_325713-338349_OflLumi-13TeV-001.root,ilumicalc_histograms_None_348885-364292_OflLumi-13TeV-001.root",
  "m_autoconfigPRW"             : False,
  "m_triggerSelection"          : "",
  "m_checkDuplicatesData"       : False,
  "m_applyEventCleaningCut"     : True,
  "m_applyIsBadBatmanFlag"      : True,
  "m_applyJetCleaningEventFlag"     : True,
  "m_applyCoreFlagsCut"	        : True,
  "m_vertexContainerName"       : "PrimaryVertices",
  "m_applyPrimaryVertexCut"     : True, 
  "m_PVNTrack"		        : 2,
  "m_msgLevel"                  : "Info",
})

#%%%%%%%%%%%%%%%%%%%%%%%%%% JetCalibrator %%%%%%%%%%%%%%%%%%%%%%%%%%#

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
  "m_calibSequence"             : "JetArea_Residual_EtaJES_GSC",                                    # recommendation as of May 11 2020
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
  "m_pT_min"                    : 20e3,
  "m_eta_max"                   : 2.5,
  #----------------------- JVT ----------------------------#
  "m_doJVT"                     : False, # JVT is a pileup cut
  "m_pt_max_JVT"                : 60e3,
  "m_eta_max_JVT"               : 2.4,
  "m_JVTCut"                    : 0.2,
  #----------------------- B-tagging ----------------------------#
  "m_doBTagCut"                 : False,
  "m_corrFileName"              : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/xAODBTaggingEfficiency/13TeV/2021-22-13TeV-MC16-CDI-2021-12-02_v2.root",
  "m_taggerName"                : "DL1r",
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

#%%%%%%%%%%%%%%%%%%%%%%%%%% BJetEfficiencyCorrector %%%%%%%%%%%%%%%%%%%%%%%%%%#
bJetWPs = ["FixedCutBEff_60", "FixedCutBEff_70", "FixedCutBEff_77", "FixedCutBEff_85"]
#bJetWPs = ["FixedCutBEff_85"]
taggers = ["DL1dv00","DL1r"]

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
      inFatJetContainerName = "FatJets_Calibrate",
      inputFatAlgo = "FatJetCalibrator_Syst",
      fatJetDetailStr = "kinematic substructure constituent constituentAll scales area"
##%%%%%%%%%%%%%%%%%%%%%%%%%% DijetResonanceAlgo %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("ResonanceAlgorithm",     {
    "m_name"                    : "ResonanceAlgo",
    #----------------------- Container Flow ----------------------------#
    "m_inJetContainerName"      : "Jets_Selected",
    "m_inputAlgo"               : "JetSelector_Syst",
    "m_inMetContainerName"      : "METOutput_NewRefFinal",
    "m_inFatJetContainerName"   : inFatJetContainerName,
    "m_inputFatAlgo"            : inputFatAlgo,
    #----------------------- Selections ----------------------------#
    "m_leadingJetPtCut"         : 20e3,
    "m_subleadingJetPtCut"      : 0e3,
    "m_jetMultiplicity"         : 1,
    #----------------------- Output ----------------------------#
    "m_doBtag"                  : False,
    "m_reclusterJets"           : False,
    "m_eventDetailStr"          : "truth pileup", #shapeEM
    "m_jetDetailStr"            : "kinematic rapidity jetBTag_DL1dv00_FixedCutBEff_85 jetBTag_DL1dv00_FixedCutBEff_77 jetBTag_DL1dv00_FixedCutBEff_70 jetBTag_DL1dv00_FixedCutBEff_60 jetBTag_DL1r_FixedCutBEff_85 jetBTag_DL1r_FixedCutBEff_77 jetBTag_DL1r_FixedCutBEff_70 jetBTag_DL1r_FixedCutBEff_60 truth JVT flavorTag",
    "m_fatJetDetailStr"	        : fatJetDetailStr,
    "m_metDetailStr"            : "metClus sigClus",
    "m_jetDetailStrSyst"        : "kinematic rapidity truth JVT",
    "m_trigDetailStr"           : "basic menuKeys passTriggers",
    #----------------------- Other ----------------------------#
    "m_writeTree"               : True,
    #"m_MCPileupCheckContainer"  : "AntiKt4TruthJets",
    "m_MCPileupCheckContainer"  : "None",
#    "m_truthLevelOnly"          : False , #Protection when running on truth xAOD.
    "m_msgLevel"                : "Info",
})

