#include <EventLoop/Job.h>
#include <EventLoop/Worker.h>
#include "EventLoop/OutputStream.h"
#include "AthContainers/ConstDataVector.h"

#include "xAODTracking/VertexContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODTruth/TruthParticleContainer.h"
#include <SVJAlgo/SVJAlgorithm.h>
#include <xAODAnaHelpers/HelperFunctions.h>

#include "TFile.h"
#include "TEnv.h"
#include "TSystem.h"
#include "TLorentzVector.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// this is needed to distribute the algorithm to the workers
ClassImp(SVJAlgorithm)

SVJAlgorithm :: SVJAlgorithm () :
  m_cutflowHist(0),
  m_cutflowHistW(0),
  m_treeStream("tree")
{

////////////////////////////////////////////////////////////////////////////
// Here you put any code for the base initialization of variables,        //
// e.g. initialize all pointers to 0.  Note that you should only put      //
// the most basic initialization here, since this method will be          //
// called on both the submission and the worker node.  Most of your       //
// initialization code will go into histInitialize() and                  //
// initialize().                                                          //
////////////////////////////////////////////////////////////////////////////

  ANA_MSG_INFO("SVJAlgorithm() : Calling constructor");

  m_inJetContainerName       = "";
  m_inEleContainerName       = "";
  m_inMuContainerName        = "";
  m_inFatJetContainerName    = "";
  m_inMetContainerName       = "";
  m_inTruthParticlesContainerName       = "";
  m_inputAlgo                = "";
  m_inputFatAlgo             = "";
  m_msgLevel                 = MSG::INFO;
  m_useCutFlow               = true;
  m_writeTree                = true;
  m_MCPileupCheckContainer   = "AntiKt4TruthJets";
  m_leadingJetPtCut          = 100;
  m_subleadingJetPtCut       = 25;
  m_metCut                   = -1;
  m_jetMultiplicity          = 2;
  m_yStarCut                 = -1; 
  m_doLepVeto                = false;
  m_reclusterJets            = false;
  m_truthLevelOnly           = false;
  m_eventDetailStr           = "truth pileup";
  m_trigDetailStr            = "";
  m_jetDetailStr             = "kinematic energy truth";
  m_jetDetailStrSyst         = "kinematic energy";
  m_metDetailStr             = "metClus sigClus";
  m_fatJetDetailStr          = "kinematic substructure";
}

EL::StatusCode  SVJAlgorithm :: configure ()
{
  ANA_MSG_INFO("configure() : Configuring SVJAlgorithm Interface.");

  if( m_MCPileupCheckContainer == "None" ) {
    m_useMCPileupCheck = false;
  }

  ANA_MSG_INFO("configure() : SVJAlgorithm Interface succesfully configured! \n");

  if( m_inJetContainerName.empty() ) {
    ANA_MSG_ERROR("configure() : Input Jet Container string is empty!");
    return EL::StatusCode::FAILURE;
  }

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode SVJAlgorithm :: setupJob (EL::Job& job)
{

  ////////////////////////////////////////////////////////////////////////
  // Here you put code that sets up the job on the submission object    //
  // so that it is ready to work with your algorithm, e.g. you can      //
  // request the D3PDReader service or add output files.  Any code you  //
  // put here could instead also go into the submission script.  The    //
  // sole advantage of putting it here is that it gets automatically    //
  // activated/deactivated when you add/remove the algorithm from your  //
  // job, which may or may not be of value to you.                      //
  ////////////////////////////////////////////////////////////////////////
  
  job.useXAOD();
  xAOD::Init( "SVJAlgorithm" ).ignore(); // call before opening first file

  EL::OutputStream outForTree( m_treeStream );
  job.outputAdd (outForTree);
  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SVJAlgorithm :: histInitialize ()
{
  ////////////////////////////////////////////////////////////////////////
  // Here you do everything that needs to be done at the very           //
  // beginning on each worker node, e.g. create histograms and output   //
  // trees.  This method gets called before any input files are         //
  // connected.                                                         //
  ////////////////////////////////////////////////////////////////////////
  
  ANA_MSG_INFO("histInitialize() : Calling histInitialize \n");

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SVJAlgorithm :: fileExecute ()
{
  ////////////////////////////////////////////////////////////////////////
  // Here you do everything that needs to be done exactly once for every//
  // single file, e.g. collect a list of all lumi-blocks processed      //
  ////////////////////////////////////////////////////////////////////////
  
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode SVJAlgorithm :: changeInput (bool /*firstFile*/)
{
  ////////////////////////////////////////////////////////////////////////
  // Here you do everything you need to do when we change input files,  //
  // e.g. resetting branch addresses on trees.  If you are using        //
  // D3PDReader or a similar service this method is not needed.         //
  ////////////////////////////////////////////////////////////////////////
  
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode SVJAlgorithm :: initialize ()
{
  ////////////////////////////////////////////////////////////////////////
  // Here you do everything that you need to do after the first input   //
  // file has been connected and before the first event is processed,   //
  // e.g. create additional histograms based on which variables are     //
  // available in the input files.  You can also create all of your     //
  // histograms and trees in here, but be aware that this method        //
  // doesn't get called if no events are processed.  So any objects     // 
  // you create here won't be available in the output if you have no    //
  // input events.                                                      //
  ////////////////////////////////////////////////////////////////////////

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();
  m_eventCounter = -1;

  const xAOD::EventInfo* eventInfo(nullptr);
  ANA_CHECK (HelperFunctions::retrieve(eventInfo, "EventInfo", m_event, m_store));

  if ( this->configure() == EL::StatusCode::FAILURE ) {
    ANA_MSG_ERROR("initialize() : Failed to properly configure. Exiting." );
    return EL::StatusCode::FAILURE;
  }

  if( m_truthLevelOnly ) { m_isMC = true; }
  else {
    m_isMC = ( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) ) ? true : false;
  }

  if(m_useCutFlow) {

    TFile *file = wk()->getOutputFile ("cutflow");
    m_cutflowHist  = (TH1D*)file->Get("cutflow");
    m_cutflowHistW = (TH1D*)file->Get("cutflow_weighted");
      
  }

  // Setting up tools ... let's set up the DeadTileCorrectionTool
  // We'll use it to mark jets in dead modules
  ANA_CHECK( ASG_MAKE_ANA_TOOL(m_JetTileCorrectionTool_handle, CP::JetTileCorrectionTool));
  ANA_CHECK( m_JetTileCorrectionTool_handle.setProperty("OutputLevel", msg().level()));
  //ANA_CHECK( m_JetTileCorrectionTool_handle.setProperty("isMC", !m_isData));
  //ANA_CHECK( m_JetTileCorrectionTool_handle.setProperty("isMC", true));
  ANA_CHECK( m_JetTileCorrectionTool_handle.retrieve());
  ANA_MSG_DEBUG("Retrieved tool: " << m_JetTileCorrectionTool_handle);

  ANA_MSG_INFO("initialize() : Succesfully initialized! \n");
  return EL::StatusCode::SUCCESS;
}

void SVJAlgorithm::AddTree( std::string name ) {

  std::string treeName("outTree");
  
  //Append systematic variation to the tree name, being empty refers to the
  // nominal case  
  treeName += name; 
  TTree * outTree = new TTree(treeName.c_str(),treeName.c_str());
  if( !outTree ) {
    ANA_MSG_ERROR("AddTree() : Failed to get output tree!");
  }
  TFile* treeFile = wk()->getOutputFile( m_treeStream );
  outTree->SetDirectory( treeFile );

  MiniTree* miniTree = new MiniTree(m_event, outTree, treeFile, m_store); 
  // only limited information available in truth xAODs
  if( m_truthLevelOnly ) {
    miniTree->AddEvent("truth");
    miniTree->AddJets("kinematic");
  } else { // reconstructed xAOD
    miniTree->AddEvent( m_eventDetailStr );
    miniTree->AddTrigger( m_trigDetailStr );
    //Fixme need to add syst strs for Met and FatJet
    if( !name.empty() ) { // save limited information for systematic variations
      miniTree->AddJets( m_jetDetailStrSyst );
      if (m_inMetContainerName != "" ) miniTree->AddMET( m_metDetailStr);
      if (m_inFatJetContainerName != "") miniTree->AddFatJets(m_fatJetDetailStr);
      if (m_inTruthParticlesContainerName != "") miniTree->AddTruthParts(m_truthParticlesDetailStr);
    } else {
      miniTree->AddJets( m_jetDetailStr );
      if (m_inMetContainerName != "" ) miniTree->AddMET( m_metDetailStr);
      if (m_inFatJetContainerName != "" ) miniTree->AddFatJets(m_fatJetDetailStr);
      if (m_inTruthParticlesContainerName != "" ) miniTree->AddTruthParts(m_truthParticlesDetailStr);
    }
  }
  m_myTrees[name] = miniTree;
}

void SVJAlgorithm::AddHists( std::string name ) {

  std::string jhName("highPtJets");
  jhName += name; 

}


EL::StatusCode SVJAlgorithm :: execute ()
{
  ////////////////////////////////////////////////////////////////////////
  // Here you do everything that needs to be done on every single       //
  // events, e.g. read input variables, apply cuts, and fill            //
  // histograms and trees.  This is where most of your actual analysis  //
  // code will go.                                                      //
  ////////////////////////////////////////////////////////////////////////
  
  ANA_MSG_DEBUG("execute(): Applying selection");
  ++m_eventCounter;

  //std::cout << "Event number = " << m_eventCounter << std::endl;
  /////////////////////////////////////////////////////////////////////
  //                      Retrieve containers                        //
  /////////////////////////////////////////////////////////////////////

  ANA_MSG_DEBUG("execute() : Get Containers");
  const xAOD::EventInfo* eventInfo(nullptr);
  ANA_CHECK (HelperFunctions::retrieve(eventInfo, "EventInfo", m_event, m_store));

  SG::AuxElement::ConstAccessor<float> NPVAccessor("NPV");
  const xAOD::VertexContainer* vertices = 0;
  if(!m_truthLevelOnly) {
    ANA_CHECK (HelperFunctions::retrieve(vertices, "PrimaryVertices", m_event, m_store));
  }
  if(!m_truthLevelOnly && !NPVAccessor.isAvailable( *eventInfo )) { // NPV might already be available
    eventInfo->auxdecor< float >( "NPV" ) = HelperFunctions::countPrimaryVertices(vertices, 2);
  }

  const xAOD::JetContainer* truthJets = 0;
  if(m_useMCPileupCheck && m_isMC){
    ANA_CHECK (HelperFunctions::retrieve(truthJets, m_MCPileupCheckContainer, m_event, m_store));
  }

  const xAOD::TruthParticleContainer* truthParticles(nullptr);
  if (m_inTruthParticlesContainerName != "") ANA_CHECK (HelperFunctions::retrieve(truthParticles, m_inTruthParticlesContainerName, m_event, m_store, msg()));

  //Set this first, as m_mcEventWeight is needed by passCut()
  if(m_isMC)
    m_mcEventWeight = eventInfo->mcEventWeight();
  else
    m_mcEventWeight = 1;

  ////////////////////////////////////////////////////////////////////
  //                 Loop over all the systematics                  //
  ////////////////////////////////////////////////////////////////////

  ANA_MSG_DEBUG("execute() : Systematic Loop");

  //Did any collection pass the cuts?
  bool pass(false);
  bool doCutflow(m_useCutFlow); // will only stay true for nominal
  const xAOD::JetContainer* signalJets = 0;
  const xAOD::MissingETContainer* met = 0;
  const xAOD::JetContainer* fatJets = 0;
  const xAOD::JetContainer* EMtopoJets = 0;
  const xAOD::ElectronContainer* electrons = 0;
  const xAOD::MuonContainer* muons = 0;

  ANA_CHECK (HelperFunctions::retrieve(EMtopoJets, "AntiKt4EMTopoJets", m_event, m_store));

  // If input comes from xAOD, or just running one collection,
  // then get the one collection and be done with it
  if( m_inputAlgo == "" || m_truthLevelOnly ) {
    ANA_CHECK (HelperFunctions::retrieve(signalJets, m_inJetContainerName, m_event, m_store));
    if(!m_truthLevelOnly && m_inMetContainerName != "") { 
      ANA_CHECK (HelperFunctions::retrieve(met, m_inMetContainerName, m_event, m_store)); 
    }
    if(m_doLepVeto){
      ANA_CHECK (HelperFunctions::retrieve(electrons, m_inEleContainerName, m_event, m_store));
      ANA_CHECK (HelperFunctions::retrieve(muons, m_inMuContainerName, m_event, m_store));
    }

    // executeAnalysis
    pass = this->executeAnalysis( eventInfo, signalJets, fatJets, truthJets, EMtopoJets, electrons, muons, vertices, met, truthParticles, doCutflow, "" );

  }
  else { 
    // Get the list of systematics to run over
    // Practically, maybe we should run over small-R and large-R jet systematics separately?
    std::vector<std::string>* systNames = 0;
    if ( m_store->contains< std::vector<std::string> >( m_inputAlgo ) ) {
      if(!m_store->retrieve( systNames, m_inputAlgo ).isSuccess()) {
        ANA_MSG_INFO("execute() : Cannot find vector from "<<m_inputAlgo.c_str());
        return StatusCode::FAILURE;
      }
    }
    // Commented out to surpress # of lines in log
    //ANA_MSG_INFO("execute() : Found vector from "<<m_inputAlgo.c_str());

    // loop over systematics
    bool saveContainerNames(false);
    std::vector< std::string >* vecOutContainerNames = 0;
    if(saveContainerNames) { vecOutContainerNames = new std::vector< std::string >; }
    // shoudl only doCutflow for the nominal
    bool passOne(false);
    std::string inContainerName("");
    std::string inFatContainerName("");
    for( auto systName : *systNames ) {
      ANA_MSG_DEBUG("execute() : Systematic Loop"<<systName);
      inContainerName = m_inJetContainerName+systName;
      inFatContainerName = m_inFatJetContainerName+systName;
      ANA_CHECK (HelperFunctions::retrieve(signalJets, inContainerName, m_event, m_store));
      if (m_inFatJetContainerName != "") ANA_CHECK (HelperFunctions::retrieve(fatJets, inFatContainerName, m_event, m_store));
      if (m_inMetContainerName != "") ANA_CHECK (HelperFunctions::retrieve(met, m_inMetContainerName, m_event, m_store)); 
  
      if(m_doLepVeto){
	ANA_CHECK (HelperFunctions::retrieve(electrons, m_inEleContainerName, m_event, m_store));
	ANA_CHECK (HelperFunctions::retrieve(muons, m_inMuContainerName, m_event, m_store));
      }
      
      // allign with Dijet naming conventions
      if( systName.empty() ) { doCutflow = m_useCutFlow; } // only doCutflow for nominal
      else { doCutflow = false; }
      passOne = this->executeAnalysis( eventInfo, signalJets, fatJets, truthJets, EMtopoJets, electrons, muons, vertices, met, truthParticles, doCutflow, systName );
      // save the string if passing the selection
      if( saveContainerNames && passOne ) { vecOutContainerNames->push_back( systName ); }
      // the final decision - if at least one passes keep going!
      pass = pass || passOne;

    }

    // save list of systs that should be considered down stream
    if( saveContainerNames ) {
      ANA_CHECK (m_store->record( vecOutContainerNames, m_name));
    }
  }

  if(!pass) {
    wk()->skipEvent();
  }

  return EL::StatusCode::SUCCESS;

}

  
//////////////////////////////////////////////////////////
// A sub-module called by the execute method            //
// Here is where the real actions are taken             //
//////////////////////////////////////////////////////////

bool SVJAlgorithm :: executeAnalysis ( const xAOD::EventInfo* eventInfo,
    const xAOD::JetContainer* signalJets,
    const xAOD::JetContainer* fatJets,
    const xAOD::JetContainer* truthJets,
    const xAOD::JetContainer* EMtopoJets,
    const xAOD::ElectronContainer* electrons,
    const xAOD::MuonContainer* muons,
    const xAOD::VertexContainer* vertices,
    const xAOD::MissingETContainer* met,
    const xAOD::TruthParticleContainer* truthParticles,
    bool doCutflow,
    std::string systName) {
  
  /////////////////////////////////////////////////////
  // The cutflow is filled by a hacky but simple way //
  // Need to call passCut after each cut is applied  //
  // in an order corresponding to how the bin labels //
  // are defined in the cutflow histogram            //
  /////////////////////////////////////////////////////

  //Trigger Efficiency
  // not needed  - trigger already saved
  //if(doCutflow) passCut();

  //Adding tight jet cleaning based on EMtopoJets
  bool passAll = true;
  bool bothJetsGoodTile = true;
  TLorentzVector vPF, vEMtopo;
  for(int ijet = 0; ijet < signalJets->size(); ijet++){
    if(ijet > 1) continue;
    const xAOD::Jet* sigjet = signalJets->at(ijet);
    vPF.SetPtEtaPhiE(sigjet->pt(), sigjet->eta(), sigjet->phi(), sigjet->e());

    //bool goodTile = true;
    int tile_status = -1;
    JTC::TS j_status = m_JetTileCorrectionTool_handle->getTileStatus(*sigjet);
    //std::cout << sigjet->phi() << std::endl;
    if(j_status==JTC::TS::GOOD) tile_status = 0; 
    if(j_status==JTC::TS::EDGE) tile_status = 1; 
    if(j_status==JTC::TS::CORE) tile_status = 2;
    //std::cout << tile_status << std::endl; 
    bool goodTile = tile_status == 0;
    bothJetsGoodTile = bothJetsGoodTile && goodTile;

    float dR = 999.0;
    int closestJet = -1;
    for(int itopo = 0; itopo < EMtopoJets->size(); itopo++){
      const xAOD::Jet* EMtopojet = EMtopoJets->at(itopo);
      vEMtopo.SetPtEtaPhiE(EMtopojet->pt(), EMtopojet->eta(), EMtopojet->phi(), EMtopojet->e());
      float temp_dR = vPF.DeltaR(vEMtopo);
      if(dR > temp_dR){
	dR = temp_dR;
	closestJet = itopo;
      }
    }
    const xAOD::Jet* closestEMtopojet = EMtopoJets->at(closestJet);

    // tight cleaning
    bool passTight = true;
    if(closestEMtopojet->isAvailable<char>("DFCommonJets_jetClean_TightBad")){
      if(closestEMtopojet->auxdataConst<char>("DFCommonJets_jetClean_TightBad")<1){
	passTight = false;
      }
    }
    passAll = passTight && passAll;
  }
  if(!passAll){
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  if(!bothJetsGoodTile){
    std::cout << "rejecting event for bad tile" << std::endl;
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  if(doCutflow) passCut("JetTileCorrection");

  // Jet multiplicity
  if (signalJets->size() < m_jetMultiplicity) {
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  if(doCutflow) passCut("JetMultiplicity");

  // Leading jet pT and eta
  if( signalJets->at(0)->pt() < m_leadingJetPtCut ) {
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  if(doCutflow) passCut("LeadingJetPt");

  if( fabs(signalJets->at(0)->eta()) >= m_leadingJetEtaCut ) {
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  if(doCutflow) passCut("LeadingJetEta");
  
  // Subleading jet eta
  if( fabs(signalJets->at(1)->eta()) >= m_subleadingJetEtaCut ) {
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  if(doCutflow) passCut("SubleadingJetEta");

  // mcCleaning selection
  // for lower slices this cut prevents the leading jets from being pileup jets
  if(m_useMCPileupCheck && m_isMC && signalJets->size() > 1) {
    float pTAvg = ( signalJets->at(0)->pt() + signalJets->at(1)->pt() ) /2.0;
    if( truthJets->size() == 0 || (pTAvg / truthJets->at(0)->pt() > 1.4) ){
      wk()->skipEvent();  return EL::StatusCode::SUCCESS;
    }
    if(doCutflow) passCut("mcCleaning"); 
  }

  // yStar Selection
  if( m_yStarCut > 0 && signalJets->size() > 1 ) {
    if(fabs(signalJets->at(0)->rapidity() - signalJets->at(1)->rapidity())/2.0 >= m_yStarCut){
      wk()->skipEvent();  return EL::StatusCode::SUCCESS;
    } 
    if(doCutflow) passCut("y*"); 
  }
  
  // MET Selection
  if (m_inMetContainerName != "" && m_metCut >= 0) {
    const xAOD::MissingET* final_clus = *met->find("FinalClus");
    if(final_clus->met() < m_metCut*1000) {
      wk()->skipEvent();  return EL::StatusCode::SUCCESS; 
    }
    if(doCutflow) passCut("METSelection");
  }

  if(electrons->size() > 0 && muons->size() > 0){
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  if(doCutflow) passCut("LeptonVeto");

 
  /*
  //Trying to add jet cleaning
  for(int ijet = 0; ijet < signalJets->size(); ijet++){
    const xAOD::Jet* sigjet = signalJets->at(ijet);
 
    bool passTight=true;
    float fracSamplingMax;
    fracSamplingMax = -999;
    std::vector<float> sumpttrk_vec;
    sumpttrk_vec.clear();
    sigjet->getAttribute(xAOD::JetAttribute::SumPtTrkPt500, sumpttrk_vec);
    sigjet->getAttribute(xAOD::JetAttribute::FracSamplingMax, fracSamplingMax);
    std::cout << "fracSamplingMax = " << fracSamplingMax << std::endl;
    float sumpttrk;
    if (sumpttrk_vec.size() > 0) {
      sumpttrk = sumpttrk_vec[0]; //assuming you are using the default PV selection
    } else {
      sumpttrk = 0;
    }
    if (fabs(sigjet->eta())<2.4 && fracSamplingMax>0 && (sumpttrk/sigjet->pt())/fracSamplingMax<0.1) passTight=false;

    std::cout << "For the " << ijet << "th jet, passTight is = " << passTight << std::endl;

  }
  */
  ANA_MSG_DEBUG("Event # "<< m_eventCounter);

  std::cout << "Event number in executeAnalysis = " << m_eventCounter << std::endl;
  //////////////////////
  //  Fill the tree   //
  //////////////////////
  
  if(m_writeTree){
    if (m_myTrees.find( systName ) == m_myTrees.end() ) { AddTree(systName); }
    if(eventInfo) { m_myTrees[systName]->FillEvent(eventInfo, m_event); }
    if( m_truthLevelOnly ) {
      if(signalJets)  { m_myTrees[systName]->FillJets( signalJets, -1 ); }
    } else {
      m_myTrees[systName]->FillTrigger( eventInfo );
      if(signalJets)  m_myTrees[systName]->FillJets( signalJets, HelperFunctions::getPrimaryVertexLocation( vertices )  );
      if(met) m_myTrees[systName]->FillMET(met);
      if(fatJets) m_myTrees[systName]->FillFatJets( fatJets, HelperFunctions::getPrimaryVertexLocation( vertices ));
      if(truthParticles) m_myTrees[systName]->FillTruth(truthParticles);
    }
    m_myTrees[systName]->Fill();
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////
//Easy method for automatically filling cutflow and incrementing counter //
///////////////////////////////////////////////////////////////////////////

void SVJAlgorithm::passCut(std::string label) {

  int newbin = m_cutflowHist->GetXaxis()->FindBin(label.c_str());
  int newbin_w = m_cutflowHistW->GetXaxis()->FindBin(label.c_str());
  m_cutflowHist->Fill(newbin, 1);
  m_cutflowHistW->Fill(newbin_w, m_mcEventWeight);
}

EL::StatusCode SVJAlgorithm :: postExecute ()
{
  ///////////////////////////////////////////////////////////////////////
  // Here you do everything that needs to be done after the main event //
  // processing.  This is typically very rare, particularly in user    //
  // code.  It is mainly used in implementing the NTupleSvc.           //
  ///////////////////////////////////////////////////////////////////////
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode SVJAlgorithm :: finalize ()
{
  ///////////////////////////////////////////////////////////////////////
  // This method is the mirror image of initialize(), meaning it gets  //
  // called after the last event has been processed on the worker node // 
  // and allows you to finish up any objects you created in            //
  // initialize() before they are written to disk.  This is actually   //
  // fairly rare, since this happens separately for each worker node.  //
  // Most of the time you want to do your post-processing on the       //
  // submission node after all your histogram outputs have been        //
  // merged.  This is different from histFinalize() in that it only    //
  // gets called on worker nodes that processed input events.          //
  ///////////////////////////////////////////////////////////////////////

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode SVJAlgorithm :: histFinalize ()
{
  ///////////////////////////////////////////////////////////////////////
  // This method is the mirror image of histInitialize(), meaning it   //
  // gets called after the last event has been processed on the worker //
  // node and allows you to finish up any objects you created in       //
  // histInitialize() before they are written to disk.  This is        //
  // actually fairly rare, since this happens separately for each      //
  // worker node.  Most of the time you want to do your                //
  // post-processing on the submission node after all your histogram   //
  // outputs have been merged.  This is different from finalize() in   //
  // that it gets called on all worker nodes regardless of whether     //
  // they processed input events.                                      //
  ///////////////////////////////////////////////////////////////////////
  
  if( m_writeTree ) {
    std::string thisName;
    TFile * treeFile = wk()->getOutputFile( m_treeStream );
    if(m_useCutFlow) {
      TH1F* thisCutflowHist = (TH1F*) m_cutflowHist->Clone();
      thisName = thisCutflowHist->GetName();
      thisCutflowHist->SetName( (thisName).c_str() );
      thisCutflowHist->SetDirectory( treeFile );

      TH1F* thisCutflowHistW = (TH1F*) m_cutflowHistW->Clone();
      thisName = thisCutflowHistW->GetName();
      thisCutflowHistW->SetName( (thisName).c_str() );
      thisCutflowHistW->SetDirectory( treeFile );
    }
    // Get MetaData_EventCount histogram
    TFile* metaDataFile = wk()->getOutputFile( "metadata" );
    TH1D* metaDataHist = (TH1D*) metaDataFile->Get("MetaData_EventCount");
    TH1D* thisMetaDataHist = (TH1D*) metaDataHist->Clone();
    thisMetaDataHist->SetDirectory( treeFile );
  }

  return EL::StatusCode::SUCCESS;
}
