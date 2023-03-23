#ifndef SVJAlgo_SVJAlgorithm_H
#define SVJAlgo_SVJAlgorithm_H

// Framework include(s)
#include <EventLoop/StatusCode.h>
#include <EventLoop/Algorithm.h>

//algorithm wrapper
#include "xAODAnaHelpers/Algorithm.h"

// Infrastructure include(s):
#include "xAODRootAccess/Init.h"
#include "xAODRootAccess/TEvent.h"
#include "xAODRootAccess/TStore.h"

#ifndef __CINT__
  #include "xAODJet/JetContainer.h"
  #include "xAODTruth/TruthParticleContainer.h"
  #include "xAODEventInfo/EventInfo.h"
  #include <xAODAnaHelpers/JetHists.h>
  #include "SVJAlgo/MiniTree.h"
#endif

// ROOT include(s):
#include "TH1D.h"

#include <sstream>

class SVJAlgorithm : public xAH::Algorithm
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
  public:

    //configuration variables
    std::string m_inJetContainerName;      // input Jet container name
    std::string m_inFatJetContainerName;   // input Fat Jet container name
    std::string m_inTruthParticlesContainerName;   // input Truth Particles container name
    std::string m_inEleContainerName;   // input Electron container name
    std::string m_inMuContainerName;    // input Muon container name
    std::string m_inMetContainerName;   // input MET container name
    std::string m_inputAlgo;          // input algo for when running systs
    std::string m_inputFatAlgo;       // input algo for when running systs
    std::string m_allJetContainerName;// input container name
    std::string m_allJetInputAlgo;    // input algo for when running systs
    bool m_isMC;                      // Is MC
    bool m_useCutFlow;                // true will write out cutflow histograms
    bool m_writeTree;                 // true will write out a TTree
    std::string m_MCPileupCheckContainer; // Name of truth container for MC Pileup Check
    bool m_doLepVeto;                 //Apply lepton veto or not
    bool m_useMCPileupCheck;          // determined by name of MCPileupCheckContainer
    float m_leadingJetPtCut;          // Leading jet Pt cut
    float m_subleadingJetPtCut;          // Leading jet Pt cut
    uint m_jetMultiplicity;          // Leading jet Pt cut
    float m_yStarCut;                 // yStar Cut
    bool m_truthLevelOnly;            // truthLevelOnly info
    bool m_reclusterJets;            // recluster jet
    float m_metCut;                  // MET cut
    std::string m_eventDetailStr;     // event info add to tree
    std::string m_trigDetailStr;      // trigger info add to tree
    std::string m_jetDetailStr;       // jet info add to tree
    std::string m_jetDetailStrSyst;   // jetsyst info add to tree
    std::string m_metDetailStr;       // met info add to tree
    std::string m_fatJetDetailStr;    // dat jet info add to tree
    std::string m_truthParticlesDetailStr;    // dat jet info add to tree

  private:
    int m_eventCounter;     //!

    TH1D* m_cutflowHist;    //!
    TH1D* m_cutflowHistW;   //!
    float m_mcEventWeight;  //!

    std::stringstream m_ss; //!

    std::string m_treeStream;

    void passCut(std::string label);
#ifndef __CINT__
    std::map< std::string, JetHists*> m_jetHists; //!
    std::map< std::string, MiniTree* > m_myTrees; //!
#endif // not __CINT__

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
public:

  // this is a standard constructor
  SVJAlgorithm ();

  // these are the functions inherited from Algorithm
  virtual EL::StatusCode setupJob (EL::Job& job);
  virtual EL::StatusCode fileExecute ();
  virtual EL::StatusCode histInitialize ();
  virtual EL::StatusCode changeInput (bool firstFile);
  virtual EL::StatusCode initialize ();
  virtual EL::StatusCode execute ();
  virtual EL::StatusCode postExecute ();
  virtual EL::StatusCode finalize ();
  virtual EL::StatusCode histFinalize ();

  // these are the functions not inherited from Algorithm
  virtual EL::StatusCode configure ();
#ifndef __CINT__
  bool executeAnalysis( const xAOD::EventInfo* eventInfo,
      const xAOD::JetContainer* signalJets,
      const xAOD::JetContainer* fatJets,
      const xAOD::JetContainer* truthJets,
      const xAOD::ElectronContainer* electrons,
      const xAOD::MuonContainer* muons,
      const xAOD::VertexContainer* vertices,
      const xAOD::MissingETContainer* met,
      const xAOD::TruthParticleContainer* truthParticles,
      bool count,
      std::string systName = "");
#endif // not __CINT__
  void AddTree( std::string );
  void AddHists( std::string );

  // this is needed to distribute the algorithm to the workers
  ClassDef(SVJAlgorithm, 1);
};

#endif
