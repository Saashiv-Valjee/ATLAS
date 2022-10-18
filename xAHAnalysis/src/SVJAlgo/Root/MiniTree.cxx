#include "xAODMuon/MuonContainer.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODJet/JetContainer.h"
#include "xAODEventInfo/EventInfo.h"
#include "xAODAnaHelpers/HelperFunctions.h"

#include "SVJAlgo/MiniTree.h"

MiniTree :: MiniTree(xAOD::TEvent * event, TTree* tree, TFile* file, xAOD::TStore* store /* = 0 */) :
  HelpTreeBase(event, tree, file, 1e3)
{
  Info("MiniTree", "Creating output TTree");
  tree->SetAutoSave(1000000000);
  m_firstEvent = true;
  m_store = store;
}

MiniTree :: ~MiniTree()
{
}
/////////////////////////////////////////////////////
//        Add user defined event variables         //
/////////////////////////////////////////////////////

void MiniTree::AddEventUser(const std::string detailStr)
{
}

/////////////////////////////////////////////////////
//        Add user defined jet variables           //
/////////////////////////////////////////////////////

void MiniTree::AddJetsUser(const std::string detailStr, const std::string jetName)
{
}

/////////////////////////////////////////////////////
//     Clear user defined event variables          //
/////////////////////////////////////////////////////

void MiniTree::ClearEventUser() {
}

/////////////////////////////////////////////////////
//      Clear user defined jet variables           //
/////////////////////////////////////////////////////

void MiniTree::ClearJetsUser(const std::string jetName) {
}

/////////////////////////////////////////////////////
//       Fill user defined event variables         //
/////////////////////////////////////////////////////

void MiniTree::FillEventUser( const xAOD::EventInfo* eventInfo ) {
}

/////////////////////////////////////////////////////
//       Fill user defined jet variables           //
/////////////////////////////////////////////////////

void MiniTree::FillJetsUser( const xAOD::Jet* jet, const std::string jetName ) {

}

