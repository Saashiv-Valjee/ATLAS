#include <EventLoop/Job.h>
#include <EventLoop/Worker.h>
#include "EventLoop/OutputStream.h"
#include "AthContainers/ConstDataVector.h"

#include "xAODTracking/VertexContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODMissingET/MissingETContainer.h"
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
  m_inFatJetContainerName    = "";
  m_inMetContainerName       = "";
  m_inputAlgo                = "";
  m_inputFatAlgo             = "";
  m_msgLevel                 = MSG::INFO;
  m_useCutFlow               = true;
  m_writeTree                = true;
  m_MCPileupCheckContainer   = "AntiKt4TruthJets";
  m_leadingJetPtCut          = 100;
  m_subleadingJetPtCut       = 25;
  m_metCut                   = 100;
  m_jetMultiplicity          = 2;
  m_yStarCut                 = -1; 
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
    
    // This algorithm only applies selections after the trigger is applied.
    // Here find the first bin that need to be filled: TriggerEfficiency 
    m_cutflowFirst = m_cutflowHist->GetXaxis()->FindBin("TriggerEfficiency");
    m_cutflowHistW->GetXaxis()->FindBin("TriggerEfficiency");
    
    m_cutflowHist->GetXaxis()->FindBin("AddJetSelect");
    m_cutflowHistW->GetXaxis()->FindBin("AddJetSelect");

    if(m_useMCPileupCheck && m_isMC){
      m_cutflowHist->GetXaxis()->FindBin("mcCleaning");
      m_cutflowHistW->GetXaxis()->FindBin("mcCleaning");
    }

    m_cutflowHist->GetXaxis()->FindBin("y*");
    m_cutflowHistW->GetXaxis()->FindBin("y*");
  
  }

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
      miniTree->AddMET( m_metDetailStr);
      if (m_inFatJetContainerName != "") miniTree->AddFatJets(m_fatJetDetailStr);
    } else {
      miniTree->AddJets( m_jetDetailStr );
      miniTree->AddMET( m_metDetailStr);
      if (m_inFatJetContainerName != "" ) miniTree->AddFatJets(m_fatJetDetailStr);
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

  m_iCutflow = m_cutflowFirst;

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

  // If input comes from xAOD, or just running one collection,
  // then get the one collection and be done with it
  if( m_inputAlgo == "" || m_truthLevelOnly ) {
    ANA_CHECK (HelperFunctions::retrieve(signalJets, m_inJetContainerName, m_event, m_store));
    if(!m_truthLevelOnly) { 
      ANA_CHECK (HelperFunctions::retrieve(met, m_inMetContainerName, m_event, m_store)); 
    }
    // executeAnalysis
    pass = this->executeAnalysis( eventInfo, signalJets, fatJets, truthJets, vertices, met, doCutflow, "" );

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
    ANA_MSG_INFO("execute() : Found vector from "<<m_inputAlgo.c_str());

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
      ANA_CHECK (HelperFunctions::retrieve(met, m_inMetContainerName, m_event, m_store)); 
      
      // allign with Dijet naming conventions
      if( systName.empty() ) { doCutflow = m_useCutFlow; } // only doCutflow for nominal
      else { doCutflow = false; }
      passOne = this->executeAnalysis( eventInfo, signalJets, fatJets, truthJets, vertices, met, doCutflow, systName );
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
    const xAOD::VertexContainer* vertices,
    const xAOD::MissingETContainer* met,
    bool doCutflow,
    std::string systName) {
  
  /////////////////////////////////////////////////////
  // The cutflow is filled by a hacky but simple way //
  // Need to call passCut after each cut is applied  //
  // in an order corresponding to how the bin labels //
  // are defined in the cutflow histogram            //
  /////////////////////////////////////////////////////

  //Trigger Efficiency
  if(doCutflow) passCut();
 
  //Apply leading jet pT selection and jet multiplicity selection
  if (signalJets->size() < m_jetMultiplicity) {
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }

  if (m_jetMultiplicity >= 1) {
    if( signalJets->at(0)->pt() < m_leadingJetPtCut ) {
      wk()->skipEvent();  return EL::StatusCode::SUCCESS;
    }
  }
  
  if (m_jetMultiplicity >= 2) {
    if( signalJets->at(1)->pt() < m_subleadingJetPtCut ) {
      wk()->skipEvent();  return EL::StatusCode::SUCCESS;
    }
  }
  
  if(doCutflow) passCut(); 

  // mcCleaning selection
  // for lower slices this cut prevents the leading jets from being pileup jets
  if(m_useMCPileupCheck && m_isMC && signalJets->size() > 1) {
    float pTAvg = ( signalJets->at(0)->pt() + signalJets->at(1)->pt() ) /2.0;
    if( truthJets->size() == 0 || (pTAvg / truthJets->at(0)->pt() > 1.4) ){
      wk()->skipEvent();  return EL::StatusCode::SUCCESS;
    }
    if(doCutflow) passCut(); 
  }

  // yStar Selection
  if( m_yStarCut > 0 && signalJets->size() > 1 ) {
    if(fabs(signalJets->at(0)->rapidity() - signalJets->at(1)->rapidity())/2.0 < m_yStarCut){
      if(doCutflow) passCut(); 
    }else{
      wk()->skipEvent();  return EL::StatusCode::SUCCESS;
    }
  }
  else if( m_yStarCut > 0){
    wk()->skipEvent();  return EL::StatusCode::SUCCESS;
  }
  //Turn the cut off by setting m_yStarCut to a negative value 0
  else if ( m_yStarCut <= 0){
    if(doCutflow) passCut();
  }
  
  // MET Selection
  const xAOD::MissingET* final_clus = *met->find("FinalClus");
  if(final_clus->sumet() < m_metCut) {
    wk()->skipEvent();  return EL::StatusCode::SUCCESS; 
  }
  if(doCutflow) passCut();

  ANA_MSG_DEBUG("Event # "<< m_eventCounter);

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
    }
    m_myTrees[systName]->Fill();
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////
//Easy method for automatically filling cutflow and incrementing counter //
///////////////////////////////////////////////////////////////////////////

void SVJAlgorithm::passCut() {
  m_cutflowHist->Fill(m_iCutflow, 1);
  m_cutflowHistW->Fill(m_iCutflow, m_mcEventWeight);
  m_iCutflow++;
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
