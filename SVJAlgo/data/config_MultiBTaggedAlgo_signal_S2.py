import ROOT
from xAODAnaHelpers import Config

c = Config()

#%%%%%%%%%%%%%%%%%%%%%%%%%% BasicEventSelection %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("BasicEventSelection",    { 
  "m_name"                      : "BasicEventSelect",
  "m_applyGRLCut"               : False, 
  "m_GRLxml"                    : "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data17_13TeV/20180619/data17_13TeV.periodAllYear_DetStatus-v99-pro22-01_Unknown_PHYS_StandardGRL_All_Good_25ns_JetHLT_Normal2017.xml",
  "m_derivationName"            : "EXOT2",
  "m_useMetaData"               : False,
  "m_storePassHLT"              : True,
  "m_storeTrigDecisions"        : True,
  "m_storePassL1"	        : True,
  "m_storeTrigKeys" 	        : False,
  "m_applyTriggerCut"           : False,
  "m_doPUreweighting"           : False,
  "m_PRWFileNames"              : "$WorkDir_DIR/data/MultiBTaggedAlgo/ZPrime_mc16d.root,$WorkDir_DIR/data/MultiBTaggedAlgo/ZPrime_NewSamples_mc16d.root,$WorkDir_DIR/data/MultiBTaggedAlgo/ZPrime_mc163.root,$WorkDir_DIR/data/MultiBTaggedAlgo/ZPrime_NewSamples_mc16e.root",
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
c.algorithm("JetCalibrator",     {
  "m_name"                      : "JetCalibrate",
  #----------------------- Container Flow ----------------------------#
  "m_inContainerName"           : "AntiKt4EMTopoJets",
  "m_jetAlgo"                   : "AntiKt4EMTopo",
  "m_outContainerName"          : "AntiKt4EMTopoJets_Calib",
  "m_outputAlgo"                : "AntiKt4EMTopoJets_Calib_Algo",
  "m_sort"                      : True,
  "m_redoJVT"                   : True,
  #----------------------- Systematics ----------------------------#
  "m_systName"                :   "All",                 ## For MC
  "m_systVal"                   : 1,                     ## For MC
  #"m_systName"                  : "Nominal",            ## if running systematics, the name of the systematic
  #"m_systVal"                   : 0,                    ## if running systematics, the value set the systematic to
  #----------------------- Calibration ----------------------------#
  "m_overrideCalibArea"         : "00-04-82",
  "m_calibConfigAFII"           : "JES_MC16Recommendation_AFII_EMTopo_April2018_rel21.config",
  "m_calibConfigFullSim"        : "JES_data2017_2016_2015_Consolidated_EMTopo_2018_Rel21.config",
  "m_calibConfigData"           : "JES_data2017_2016_2015_Consolidated_EMTopo_2018_Rel21.config",
  "m_calibSequence"             : "JetArea_Residual_EtaJES_GSC_Smear",
  "m_forceInsitu"               : True,
  #----------------------- Jet Uncertainties Tool ----------------------------#
#  "m_uncertMCType"              : "MC16",
  "m_uncertConfig"              : "rel21/Summer2018/R4_StrongReduction_Scenario2_SimpleJER.config",
  "m_overrideUncertCalibArea"   : "CalibArea-06",
  #----------------------- Cleaning ----------------------------#
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
  "m_inContainerName"           : "AntiKt4EMTopoJets_Calib",
  "m_outContainerName"          : "SignalJets",
  "m_inputAlgo"                 : "AntiKt4EMTopoJets_Calib_Algo",
  "m_outputAlgo"                : "SignalJets_Algo",
  "m_decorateSelectedObjects"   : True,
  "m_createSelectedContainer"   : True,
  #----------------------- Selections ----------------------------#
  "m_cleanJets"                 : True,
  "m_pass_min"                  : 1,
  "m_pT_min"                    : 25e3,
  "m_eta_max"                   : 5,
  #----------------------- JVT ----------------------------#
  "m_doJVT"                     : False, # JVT is a pileup cut
  "m_pt_max_JVT"                : 120e3,
  "m_eta_max_JVT"               : 2.5,
  "m_JVTCut"                    : 0.59,
  #----------------------- B-tagging ----------------------------#
  "m_doBTagCut"                 : False,
  #----------------------- Other ----------------------------#
  "m_msgLevel"                  : "Info",
})

#%%%%%%%%%%%%%%%%%%%%%%%%%% BJetEfficiencyCorrector %%%%%%%%%%%%%%%%%%%%%%%%%%#

c.algorithm("BJetEfficiencyCorrector",     {
  "m_name"                    : "DL1r_FixedCutBEff_77",
  #----------------------- Container Flow ----------------------------#
  "m_inContainerName"         : "SignalJets",
  "m_jetAuthor"               : "AntiKt4EMTopoJets",
  "m_decor"                   : "BTag",
  "m_outputSystName"          : "BJetEfficiency_Algo",
  #----------------------- B-tag Options ----------------------------#
  "m_corrFileName"            : "$WorkDir_DIR/data/MultiBTaggedAlgo/2017-21-13TeV-MC16-CDI_smooth_retagging_bhad_detector.root",
  "m_taggerName"              : "DL1r",
  "m_operatingPt"             : "FixedCutBEff_77",
  "m_coneFlavourLabel"        : True,
  "m_useDevelopmentFile"      : True,
  "m_systName"                :   "All",                 ## For MC
  #----------------------- Other ----------------------------#
  "m_msgLevel"                : "Info"
})


##%%%%%%%%%%%%%%%%%%%%%%%%%% DijetResonanceAlgo %%%%%%%%%%%%%%%%%%%%%%%%%%#
c.algorithm("ResonanceAlgorithm",     {
    "m_name"                    : "ResonanceAlgo",
    #----------------------- Container Flow ----------------------------#
    "m_inJetContainerName"      : "SignalJets",
    "m_inputAlgo"               : "SignalJets_Algo",
    "m_allJetContainerName"     : "AntiKt4EMTopoJets_Calib",
    "m_allJetInputAlgo"         : "AntiKt4EMTopoJets_Calib_Algo",
    #----------------------- Selections ----------------------------#
    "m_leadingJetPtCut"         : 250,
    "m_subleadingJetPtCut"      : 250,
    "m_jetMultiplicity"         : 4,
    #----------------------- Output ----------------------------#
    "m_doBtag"                  : True,
    "m_bTagWPNames"             : "DL1r_FixedCutBEff_77",
    "m_eventDetailStr"          : "truth pileup", #shapeEM
    "m_jetDetailStr"            : "kinematic rapidity truth flavorTag JVT jetBTag_DL1r_FixedCutBEff_77 sfFTagFix",
    "m_jetDetailStrSyst"        : "kinematic rapidity truth flavorTag JVT jetBTag_DL1r_FixedCutBEff_77 sfFTagFix",
    "m_trigDetailStr"           : "basic menuKeys passTriggers",
    #----------------------- Other ----------------------------#
    "m_writeTree"               : True,
    "m_MCPileupCheckContainer"  : "AntiKt4TruthJets",
#    "m_MCPileupCheckContainer"  : "None",
#    "m_truthLevelOnly"          : False , #Protection when running on truth xAOD.
    "m_msgLevel"                : "Info",
    "m_yStarCut"                : 0.8,
})


