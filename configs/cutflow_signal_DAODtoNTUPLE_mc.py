# this config is for MC Signal DAODs

import os, sys
import ROOT
from xAODAnaHelpers import Config
sys.path.append('../configs')
#from configHelpers import getJetCalibratorDict, getJetSelectorDict, getJetSelectorDictHLT

msglevel = "info"
#msglevel = "verbose"
#msglevel = "debug"

c = Config()

isMC = True
runLRSysts = False
runSRSysts = False
outTree = True

DSID="312808"#note, this is not true, but I don't think our prw files are on cvmfs for svj schan. 
year = 2017
lumicalcfile = ""
prwfile = ""
if year == 2015 or year == 2016:
	lumicalcfile = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data15_13TeV/20170619/PHYS_StandardGRL_All_Good_25ns_276262-284484_OflLumi-13TeV-008.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data16_13TeV/20180129/PHYS_StandardGRL_All_Good_25ns_297730-311481_OflLumi-13TeV-009.root"
	prwfile = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/PileupReweighting/share/DSID" + DSID[:3] + "xxx/pileup_mc16a_dsid" + DSID + "_FS.root"
elif year == 2017:
	lumicalcfile = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.lumicalc.OflLumi-13TeV-010.root"
	prwfile = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/PileupReweighting/share/DSID" + DSID[:3] + "xxx/pileup_mc16d_dsid" + DSID + "_FS.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
elif year == 2018:
	lumicalcfile = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190318/ilumicalc_histograms_None_348885-364292_OflLumi-13TeV-010.root"
	prwfile = "/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/PileupReweighting/share/DSID" + DSID[:3] + "xxx/pileup_mc16e_dsid" + DSID + "_FS.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190318/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root"
else:
	sys.exit("Unrecognised year " + str(year) + "! Exiting ...")

doRaw = True 
doCleaning = True
doCalibration = False
doTruthReclustering = False #True
doReclustering = False #True
storeTruthJets = True
storeMuons = False 

if not isMC:
	doTruthReclustering = False
	storeTruthJets = False

doSmallR = True
#JetContainerName = ["AntiKt4LCTopoJets", "AntiKt4EMPFlowJets", "AntiKt4EMTopoJets"]
#JetBranchName = ["a4_topojets", "a4_flowjets", "a4_topojets"]
JetContainerName = "AntiKt4EMPFlowJets"
JetBranchName = "a4_pflowjets"
doLargeR = True
#FatJetContainerName = ["AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets", "AntiKt10UFOCSSKJets"]#, "AntiKtVR30RmaxRmin02TrackGhostTagJets", "AntiKtVR30RmaxRmin02TrackJets"]
#FatJetBranchName = ["a10_lctopojets", "a10_ufojets"]#, "avr_ghostjets", "avr_trackjets"]
FatJetContainerName = "AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets"
FatJetBranchName = "a10_lctopojets"

#The JES uncertainty reducion scheme to be used for small-R jets. Possible values are: GR, SR1, SR2, SR3, SR4
ReductionScheme = "GR"

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%% BasicEventSelection %%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

c.algorithm("BasicEventSelection",	{
	"m_name"			:	"myBaseEventSel",
	"m_msgLevel"			:	msglevel,
	"m_truthLevelOnly"		:	False,
	    
	# GRL, LumiCalc, PURW Tool, see https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/ExtendedPileupReweighting
	"m_applyGRLCut"			:	True,
	"m_GRLxml"			:	"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data15_13TeV/20170619/physics_25ns_21.0.19.xml,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data16_13TeV/20180129/physics_25ns_21.0.19.xml,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.xml,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190318/physics_25ns_Triggerno17e33prim.xml",
	"m_lumiCalcFileNames"		:	lumicalcfile,
	"m_PRWFileNames"		:	prwfile,
	#"m_PRWFileNames"		:	"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data17_13TeV/20180619/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root,/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/GoodRunsLists/data18_13TeV/20190318/physics_25ns_Triggerno17e33prim.actualMu.OflLumi-13TeV-010.root",
	"m_doPUreweighting"		:	False,
	#"m_autoconfigPRW"		:	True,
	"m_doPUreweightingSys"		:	True,
	# turn on vertex and event cleaning cuts
	"m_vertexContainerName"		:	"PrimaryVertices",
	"m_applyPrimaryVertexCut"	:	True,
	"m_PVNTrack"			:	2,
	"m_applyEventCleaningCut"	:	True,
	"m_applyCoreFlagsCut"		:	True,
	"m_applyJetCleaningEventFlag"	:	True,

	#trigger decisions
	"m_storeTrigDecisions"		:	True,
	#"m_storePassHLT"		:	True,
	"m_applyTriggerCut"		:	False,
	#"m_triggerSelection"		:	".+", 
	#"m_triggerSelection"		:	"(HLT|L1)_((ht|HT)|[1-9]?0?(j|J)[0-9])+.*",  # only jet and HT ones
	"m_triggerSelection"		:	"HLT_j460+.*",
})

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%% Setting up storage to tree & systs. %%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

DefaultJetDetailStrs = "kinematic constituent cleanLight truth" #truth_details trackPV energy
DefaultFatJetDetailStrs = "kinematic substructure constituent"
DefaultTruthDetailStrs = "type dressed origin children parents"

jetContainerNames = []
jetBranchNames = []
jetDetailStrs = []

fatJetContainerNames = []
fatJetBranchNames = []
fatJetDetailStrs = []

systName = "Nominal"
systVal = 0
uncertConfig = ""

if doRaw:
	if doSmallR:
		jetContainerNames.append(JetContainerName)
		jetBranchNames.append(JetBranchName)
		jetDetailStrs.append(DefaultJetDetailStrs) 

	if doLargeR:
		fatJetContainerNames.append(FatJetContainerName)
		fatJetBranchNames.append(FatJetBranchName)
		fatJetDetailStrs.append(DefaultFatJetDetailStrs)


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%% Perform Jet Calibration %%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

calibJetContainerName = JetContainerName
calibFatJetContainerName = FatJetContainerName

if doCalibration: 
	if doSmallR:
		if runSRSysts:
			if ReductionScheme == "GR":
				uncertConfig = "rel21/Summer2019/R4_GlobalReduction_SimpleJER.config"
			else: #StrongReduction
				uncertConfig = "rel21/Summer2019/R4_SR_Scenario" + ReductionScheme[2] + "_simpleJER.config"
			systName = "All"
			systVal = 1
		calibConfigFullSim = ""
		calibConfigData = ""
		calibSequence = "JetArea_Residual_EtaJES_GSC"
		if isMC:
			calibConfigFullSim = "JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config"
			calibSequence += "_Smear"
		else:
			calibConfigData = "JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config"
			calibSequence += "_Insitu"

		outJetContainerName = JetContainerName + "_cal" + str(year)
		calibJetContainerName = outJetContainerName
		c.algorithm("JetCalibrator",	{
			"m_name"			:	"JetCalibrator::" + JetContainerName + str(year),
			"m_msgLevel"			:	msglevel,
			#----------------------- Container Flow ----------------------------#
			"m_inContainerName"		:	JetContainerName,
			"m_jetAlgo"			:	JetContainerName.replace("Jets",""),
			"m_outContainerName"		:	outJetContainerName,
			"m_outputAlgo"			:	outJetContainerName + "_Algo",
			"m_sort"			:	True,
			"m_redoJVT" 			:	False,
			#----------------------- Systematics ----------------------------#
			"m_systName"			:	systName,
			"m_systVal"			:	systVal,
			"m_writeSystToMetadata"		:	runSRSysts,
	    		#"m_systValVectorString"	:	"0.5,1,1.5,2,2.5,3.0",
			#----------------------- Calibration ----------------------------#
			"m_calibConfigData"		:	calibConfigData,
			"m_calibConfigFullSim"		:	calibConfigFullSim,
			"m_calibSequence"		:	calibSequence,
			"m_uncertConfig"		:	uncertConfig,
			#----------------------- Cleaning ----------------------------#
			"m_doCleaning"			:	doCleaning,
			"m_jetCleanCutLevel"		:	"LooseBad",
			"m_jetCleanUgly"		:	False,
			"m_saveAllCleanDecisions"	:	False,
			"m_cleanParent"			:	False,
		})

		
		jetContainerNames.append(outJetContainerName)
		jetBranchNames.append("a4jetCalib")
		jetDetailStrs.append(DefaultJetDetailStrs)

	if doLargeR:
		if runLRSysts:
			uncertConfig = "rel21/Summer2019/R10_GlobalReduction.config" #no StrongReduction exists for large-R jets
			systName = "All"
			systVal = 1
		calibConfigData = ""
		calibConfigFullSim = ""
		calibSequence = "EtaJES_JMS"
		if isMC:
			calibConfigFullSim = "JES_MC16recommendation_FatJet_Trimmed_JMS_comb_17Oct2018.config"
		else:
			calibConfigData = "JES_MC16recommendation_FatJet_Trimmed_JMS_comb_3April2019.config"
			calibSequence += "_Insitu_InsituCombinedMass"
		outFatJetContainerName = FatJetContainerName + "_cal" + str(year)
		calibFatJetContainerName = outFatJetContainerName
		c.algorithm("JetCalibrator",	{
			"m_name"			:	"JetCalibrator::" + FatJetContainerName + str(year),
			"m_msgLevel"			:	msglevel,
			#----------------------- Container Flow ----------------------------#
			"m_inContainerName"		:	FatJetContainerName,
			"m_jetAlgo"			:	FatJetContainerName.replace("Jets",""),
			"m_outContainerName"		:	outFatJetContainerName,
			"m_outputAlgo"			:	outFatJetContainerName + "_Algo",
			"m_sort"			:	True,
			"m_redoJVT" 			:	False,
			#----------------------- Systematics ----------------------------#
			"m_systName"			:	systName,
			"m_systVal"			:	systVal,
			"m_writeSystToMetadata"		:	runLRSysts,
	    		#"m_systValVectorString"	:	"0.5,1,1.5,2,2.5,3.0",
			#----------------------- Calibration ----------------------------#
			"m_calibConfigData"		:	calibConfigData,
			"m_calibConfigFullSim"		:	calibConfigFullSim,
			"m_calibSequence"		:	calibSequence,
			"m_uncertConfig"		:	uncertConfig,
			#----------------------- Cleaning ----------------------------#
			"m_doCleaning"			:	False,
			"m_jetCleanCutLevel"		:	"LooseBad",
			"m_jetCleanUgly"		:	False,
			"m_saveAllCleanDecisions"	:	False,
			"m_cleanParent"			:	False,
		})

		fatJetContainerNames.append(outFatJetContainerName)
		fatJetBranchNames.append("a10jetCalib")
		fatJetDetailStrs.append(DefaultFatJetDetailStrs)
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%% Jet Selector %%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
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
  "m_taggerName"                : "DL1r",
  "m_jetAuthor"                 : "AntiKt4EMPFlowJets",
  "m_b_pt_min"                  : 25e3,
  "m_b_eta_max"                 : 2.5,
  #----------------------- Other ----------------------------#
  "m_msgLevel"                  : "Info",
})


#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%% Perform Jet Reclustering %%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
if doTruthReclustering:
	outputTruthJetContainer = "R10rcAKT4TruthJets"
	c.algorithm("JetReclusteringAlgo",	{
		"m_name"		:	"JetReclusteringAlgo::AntiKt4TruthDressedWZJets",
		"m_inputJetContainer"	:	"AntiKt4TruthDressedWZJets",
		"m_outputJetContainer"	:	outputTruthJetContainer,
		"m_ptMin_input"		:	20.0,
		"m_rc_alg"		:	"AntiKt",
		"m_radius"		:	1.5,
		"m_ptMin_rc"		:	50.0,
		"m_trim_ptFrac"		:	0.00,
	})
	fatJetContainerNames.append(outputTruthJetContainer)
	fatJetBranchNames.append("truth_a15rcjet")
	fatJetDetailStrs.append(DefaultFatJetDetailStrs)

if doReclustering and doSmallR:
	inputRCJetContainer = calibJetContainerName
	outputJetContainer = "R10rcAKT4Jets"
	c.algorithm("JetReclusteringAlgo",	{
		"m_name"		:	"JetReclusteringAlgo::AntiKt4EMPFlowJets",
		"m_inputJetContainer"	:	inputRCJetContainer,
		"m_outputJetContainer"	:	outputJetContainer,
		"m_ptMin_input"		:	20.0,
		"m_rc_alg"		:	"AntiKt",
		"m_radius"		:	1.5,
		"m_ptMin_rc"		:	50.0,
		"m_trim_ptFrac"		:	0.00, #don't groom the RC jets!
	})
	fatJetContainerNames.append(outputJetContainer)
	fatJetBranchNames.append("a15_pflowjets_reclus")
	fatJetDetailStrs.append(DefaultFatJetDetailStrs)

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%% Perform MET Container Creation %%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

metJetContainerName = "AntiKt4EMPFlowJets"
jetAlgo = metJetContainerName.replace("Jets", "")
metContainerName = "MET"
metDetailStr = "metTrk"
c.algorithm("METConstructor", 	{
	"m_name"	         :    "met",
	"m_msgLevel"             :    msglevel,
    	"m_referenceMETContainer":    "MET_Reference_"+jetAlgo,
    	"m_mapName"              :    "METAssoc_"+jetAlgo,
   	"m_coreName"             :    "MET_Core_"+jetAlgo,
    	"m_doPFlow"              :    True,
    	"m_outputContainer"      :    metContainerName,
    	"m_inputMuons"           :    "Muons",
    	"m_inputElectrons"       :    "Electrons",
    	"m_inputJets"            :    calibJetContainerName, #after running calibration on PFlowJets
    	"m_doJVTCut"             :    True,
    	"m_dofJVTCut"            :    False,
    	"m_calculateSignificance":    False,
} )	

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%% Save to outTree and/or mini-xAOD %%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

jetContainerName = " ".join(jetContainerNames)
jetBranchName = " ".join(jetBranchNames)
jetDetailStr = "|".join(jetDetailStrs)

fatJetContainerName = " ".join(fatJetContainerNames)
fatJetBranchName = " ".join(fatJetBranchNames)
fatJetDetailStr = "|".join(fatJetDetailStrs)

truthJetContainerName = ""
truthJetBranchName = ""
truthJetDetailStr = ""
truthFatJetContainerName = ""
truthFatJetBranchName = ""
truthFatJetDetailStr = ""
jetSystsVec = ""
fatJetSystsVec = ""
muContainerName = ""
muDetailStr = ""

if runSRSysts and doSmallR:
	jetSystsVec = outJetContainerName + "_Algo"
if runLRSysts and doLargeR: 
	fatJetSystsVec = outFatJetContainerName + "_Algo"

if storeTruthJets:
	truthJetContainerName = "AntiKt4TruthDressedWZJets" 
	truthJetBranchName = "a4_truth"
	truthJetDetailStr = DefaultTruthDetailStrs
	truthFatJetContainerName = "AntiKt10TruthTrimmedPtFrac5SmallR20Jets"
	truthFatJetBranchName = "a10_truth"
	truthFatJetDetailStr = DefaultFatJetDetailStrs

if storeMuons: 
	muContainerName = "Muons"
	muDetailStr = "kinematic"


if outTree:
	c.algorithm("TreeAlgo",	{
		"m_name"			:	"outTree",
		"m_msgLevel"			:	msglevel,
		
		# event and trigger
		"m_evtDetailStr"		:	"eventCleaning pileup weightsSys pileupsys",
		"m_trigDetailStr"		:	"basic passTriggers",
		
		#fat and truth jets
                "m_jetContainerName"            :       jetContainerName,
                "m_jetBranchName"               :       jetBranchName,
                "m_jetDetailStr"                :       jetDetailStr,
		"m_jetSystsVec"			:	jetSystsVec,

		"m_fatJetContainerName"		:	fatJetContainerName,
		"m_fatJetBranchName"		:	fatJetBranchName,
		"m_fatJetDetailStr"		:	fatJetDetailStr,
		"m_fatJetSystsVec"		:	fatJetSystsVec,

		"m_muContainerName"		:	muContainerName,
		"m_muDetailStr"			:	muDetailStr,

		"m_truthJetContainerName" 	:	truthJetContainerName,
		"m_truthJetBranchName"		:	truthJetBranchName,
		"m_truthJetDetailStr"		:	truthJetDetailStr,
		"m_truthFatJetContainerName" 	:	truthFatJetContainerName,
		"m_truthFatJetBranchName"	:	truthFatJetBranchName,
		"m_truthFatJetDetailStr"	:	truthFatJetDetailStr,
		"m_METContainerName"		:	metContainerName, 
		"m_METDetailStr"		:	metDetailStr,					

		"m_truthParticlesContainerName" :	"TruthBSM",
		"m_truthParticlesBranchName"	:	"truthBSM",
                "m_truthParticlesDetailStr"     :       DefaultTruthDetailStrs,

		"m_truthMetContainerName"	:	"MET_Truth",
                "m_truthMetDetailStr"	        :	"TruthMET", 
		#"m_truthMetBranchName"		:	"TruthMET"
})

