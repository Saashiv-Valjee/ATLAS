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
doCalibration = True
storeTruthJets = False
storeMuons = False 

if not isMC:
	doTruthReclustering = False
	storeTruthJets = False

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%% Setting Up Jet Parameters  %%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

doSmallR = True
jetContainerNames = ["AntiKt4EMPFlowJets"]
jetBranchNames = ["a4_pflowjets"]
jetDetailStrs = ["kinematic constituent cleanLight"]
calibJetContainerNames = []
selectJetContainerNames = []
DefaultJetDetailStrs = jetDetailStrs[0]
#calibJetContainerName = "AntiKt4EMPFlowJets"

doLargeR = True
#fatJetContainerNames = ["AntiKt10UFOCSSKSoftDropBeta100Zcut10"]
fatJetContainerNames = ["AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets"]
#fatJetContainerNames = ["AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets", "AntiKt10UFOCSSKSoftDropBeta100Zcut10"]
#fatJetBranchNames = ["a10_ufojets"]
fatJetBranchNames = ["a10_lctopojets"]
#fatJetBranchNames = ["a10_lctopojets", "a10_ufojets"]
fatJetDetailStrs = ["kinematic substructure"]
calibFatJetContainerNames = []
selectFatJetContainerNames = []
DefaultFatJetDetailStrs = fatJetDetailStrs[0]
#calibFatJetContainerName = "AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets"

DefaultTruthDetailStrs = "type dressed origin children parents"

#The JES uncertainty reducion scheme to be used for small-R jets. Possible values are: GR, SR1, SR2, SR3, SR4
ReductionScheme = "GR"

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%% Setting up systematics %%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

systName = "Nominal"
systVal = 0
uncertConfig = ""

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%% Basic Event Selection %%%%%%%%%%%%%%%%%%%%%%%%#
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
	"m_doPUreweighting"		:	False,
	#"m_autoconfigPRW"		:	True,
	"m_doPUreweightingSys"		:	False,

	# turn on vertex and event cleaning cuts
	"m_vertexContainerName"		:	"PrimaryVertices",
	"m_applyPrimaryVertexCut"	:	True,
	"m_PVNTrack"			:	2,
	"m_applyEventCleaningCut"	:	True,
	"m_applyCoreFlagsCut"		:	True,
	"m_applyJetCleaningEventFlag"	:	True,

	#trigger decisions
	"m_storeTrigDecisions"		:	True,
	"m_storePassHLT"		:	True,
	"m_applyTriggerCut"		:	False,
	#"m_triggerSelection"		:	".+", 
	#"m_triggerSelection"		:	"(HLT|L1)_((ht|HT)|[1-9]?0?(j|J)[0-9])+.*",  # only jet and HT ones
	"m_triggerSelection"		:	"HLT_xe110_pufit_xe70_L1XE50",
})



#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%% Perform Jet Calibration %%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

if doCalibration: 
	if doSmallR:
		#Assumiung PFlow jets - must change if using EMTopo
		calibConfigFullSim = ""
		calibConfigData = ""
		calibSequence = ""
		for jetContainerName,jetBranchName in zip(jetContainerNames,jetBranchNames): 
			calibSequence = "JetArea_Residual_EtaJES_GSC"
			if isMC:
				calibConfigFullSim = "JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config"
				calibSequence += "_Smear"
			else:
				calibConfigData = "JES_MC16Recommendation_Consolidated_PFlow_Apr2019_Rel21.config"
				calibSequence += "_Insitu"
			calJetContainerName = jetContainerName + "_cal"
			outJetContainerName = jetContainerName + "_sel"
			c.algorithm("JetCalibrator",	{
				"m_name"			:	"JetCalibrator::" + jetContainerName,
				"m_msgLevel"			:	msglevel,
				#----------------------- Container Flow ----------------------------#
				"m_inContainerName"		:	jetContainerName,
				"m_jetAlgo"			:	jetContainerName.replace("Jets",""),
				"m_outContainerName"		:	calJetContainerName,
				"m_outputAlgo"			:	calJetContainerName + "_Algo",
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
				"m_doCleaning"			:	False,
				"m_jetCleanCutLevel"		:	"LooseBad",
				"m_jetCleanUgly"		:	False,
				"m_saveAllCleanDecisions"	:	False,
				"m_cleanParent"			:	False,
			})

			
			calibJetContainerNames.append(calJetContainerName)
			#jetBranchNames.append("a4jetCalib")
			#jetDetailStrs.append(DefaultJetDetailStrs)

			c.algorithm("JetSelector", 	{
				"m_name"                      : "JetSelector::" + jetContainerName,
				#----------------------- Container Flow ----------------------------#
				"m_inContainerName"           : calJetContainerName,
				"m_outContainerName"          : outJetContainerName,
				"m_inputAlgo"                 : calJetContainerName + "_Algo",
				"m_outputAlgo"                : "JetSelector_Syst",
				"m_decorateSelectedObjects"   : True,
				"m_createSelectedContainer"   : True,
				#----------------------- Selections ----------------------------#
				"m_cleanJets"                 : False,
				"m_pass_min"                  : 2,
				"m_pT_min"                    : 20e3,
				"m_eta_max"                   : 4.5,
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
				"m_msgLevel"                  : msglevel,
	
			})
			selectJetContainerNames.append(outJetContainerName)
	

	if doLargeR:
		calibConfigData = ""
		calibConfigFullSim = ""
		calibSequence = "EtaJES_JMS"
		for fatJetContainerName,fatJetBranchName in zip(fatJetContainerNames,fatJetBranchNames): 
	 		if isMC and fatJetContainerName == "AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets":
				calibConfigFullSim = "JES_MC16recommendation_FatJet_Trimmed_JMS_comb_17Oct2018.config"
			if isMC and fatJetContainerName == "AntiKt10UFOCSSKSoftDropBeta100Zcut10":
				calibConfigFullSim = "JES_MC16recommendation_R10_UFO_CSSK_SoftDrop_JMS_01April2020.config"
			if not isMC and fatJetContainerName == "AntiKt10LCTopoTrimmedPtFrac5SmallR20Jets":
				calibConfigData = "JES_MC16recommendation_FatJet_Trimmed_JMS_comb_March2021.config"
				calibSequence += "_Insitu_InsituCombinedMass"
			calFatJetContainerName = fatJetContainerName + "_cal"				
			outFatJetContainerName = fatJetContainerName + "_sel"				
			c.algorithm("JetCalibrator",	{
				"m_name"			:	"JetCalibrator::" + fatJetContainerName,
				"m_msgLevel"			:	msglevel,
				#----------------------- Container Flow ----------------------------#
				"m_inContainerName"		:	fatJetContainerName,
				"m_jetAlgo"			:	fatJetContainerName.replace("Jets",""),
				"m_outContainerName"		:	calFatJetContainerName,
				"m_outputAlgo"			:	calFatJetContainerName + "_Algo",
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
				#----------------------- Truth ----------------------------#	
				"m_useLargeRTruthLabelingTool"  :	False,
				#----------------------- Cleaning ----------------------------#
				"m_doCleaning"			:	False,
				"m_jetCleanCutLevel"		:	"LooseBad",
				"m_jetCleanUgly"		:	False,
				"m_saveAllCleanDecisions"	:	False,
				"m_cleanParent"			:	False,
			})
	
			calibFatJetContainerNames.append(calFatJetContainerName)
			#fatJetBranchNames.append("a10jetCalib")


			c.algorithm("JetSelector", 	{
				"m_name"                      : "JetSelector::" + fatJetContainerName,
				#----------------------- Container Flow ----------------------------#
				"m_inContainerName"           : calFatJetContainerName,
				"m_outContainerName"          : outFatJetContainerName,
				"m_inputAlgo"                 : calFatJetContainerName + "_Algo",
				"m_outputAlgo"                : "FatJetSelector_Syst",
				"m_decorateSelectedObjects"   : True,
				"m_createSelectedContainer"   : True,
				#----------------------- Selections ----------------------------#
				"m_cleanJets"                 : False,
				"m_pass_min"                  : 0,
				"m_pT_min"                    : 200e3,
				"m_pT_max"                    : 3000e3,
				"m_mass_min"		      : 40e3,
				"m_mass_max"		      : 600e3,
				"m_eta_max"                   : 2.0,
				"m_msgLevel"                  : msglevel,
	
			})
			selectFatJetContainerNames.append(outFatJetContainerName)
	

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%% Perform MET Container Creation %%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

metJetContainerName = "AntiKt4EMPFlowJets"
metInputJets = "AntiKt4EMPFlowJets_cal"
jetAlgo = metJetContainerName.replace("Jets", "")
metContainerName = "MET"
metDetailStr = "metClus"
c.algorithm("METConstructor", 	{
	"m_name"	         :    "met",
	"m_msgLevel"             :    msglevel,
	"m_inputJets"		 :    metInputJets,
    	#"m_referenceMETContainer":    "MET_Reference_"+jetAlgo,
    	"m_mapName"              :    "METAssoc_"+jetAlgo,
   	"m_coreName"             :    "MET_Core_"+jetAlgo,
    	"m_doPFlow"              :    True,
    	"m_outputContainer"      :    metContainerName,
    	"m_inputMuons"           :    "Muons",
    	"m_inputElectrons"       :    "Electrons",
    	"m_doJVTCut"             :    True,
    	"m_dofJVTCut"            :    False,
    	"m_calculateSignificance":    False,
} )	

#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%% Save to outTree and/or mini-xAOD %%%%%%%%%%%%%%%%%%%#
#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#

jetContainerName = " ".join(selectJetContainerNames)
jetBranchName = " ".join(jetBranchNames)
jetDetailStr = "|".join(jetDetailStrs)

fatJetContainerName = " ".join(selectFatJetContainerNames)
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
		"m_evtDetailStr"		:	"",
		"m_trigDetailStr"		:	"",
		
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
		"m_METDetailStr"		:	metDetailStr					

		#"m_truthParticlesContainerName" :	"TruthBSM",
		#"m_truthParticlesBranchName"	:	"truthBSM",
                #"m_truthParticlesDetailStr"     :       DefaultTruthDetailStrs,

		#"m_truthMetContainerName"	:	"MET_Truth",
                #"m_truthMetDetailStr"	        :	"TruthMET", 
		#"m_truthMetBranchName"		:	"TruthMET"
})



