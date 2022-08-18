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

//////////////////////////////////////////////////////
//            Add b-tagging scale factors           //
//       Currently the hybrid WP is turned off      //
//////////////////////////////////////////////////////

void MiniTree::AddBtag(std::string bTagWPNames) {
    std::stringstream ss(bTagWPNames);
    std::string thisWPString;

    // Split list of WPs by commas, and make vector placeholders //
    while (std::getline(ss, thisWPString, ',')) {
      m_bTagWPs.push_back( thisWPString );
      /*if (thisWPString.find("Fixed") != std::string::npos)
        m_bTagIsFixed.push_back(true);
      else
        m_bTagIsFixed.push_back(false);

      std::string thisNum = thisWPString.substr( thisWPString.find_last_of('_')+1, thisWPString.size() );
      std::string thisTagger = thisWPString.substr( 0, thisWPString.find_first_of('_')-1);
      
      m_bTagWPNums.push_back(thisNum);
      m_bTaggers.push_back(thisTagger);
      */ 
     std::vector<float>  tmpVec;
     m_weight_btag.push_back( tmpVec );
    }  

    /*
    sort( m_bTagWPNums.begin(), m_bTagWPNums.end() );
    m_bTagWPNums.erase( unique( m_bTagWPNums.begin(), m_bTagWPNums.end() ), m_bTagWPNums.end() );
    sort( m_bTaggers.begin(), m_bTaggers.end() );
    m_bTaggers.erase( unique( m_bTaggers.begin(), m_bTaggers.end() ), m_bTaggers.end() );
    */

    // Connect vector placeholders to WPs //
    for(unsigned int iB=0; iB < m_bTagWPs.size(); ++iB){
     /* for (unsigned int iN=0; iN < m_bTagWPNums.size(); ++iN) {
        std::string baseBTagType = "";
        if (m_bTagIsFixed.at(iB))
          baseBTagType = "fix_";
        else
          baseBTagType = "flt_";

     */
      std::string thisBTagName = "";
      thisBTagName = "weight_btag_"+m_bTagWPs.at(iB);
      m_tree->Branch(thisBTagName.c_str(), &(m_weight_btag.at(iB)) );  
    }
  
    m_tree->Branch("systSF_btag_names",      &m_systSF_btag_names    );
}

//////////////////////////////////////////////////////
//          Fill  b-tagging scale factors           //
//       Currently the hybrid WP is turned off      //
//////////////////////////////////////////////////////

void MiniTree::FillBtag( const xAOD::EventInfo* eventInfo ) {
  this->ClearBtag();

  // Find and fill relevant varaibles for all WPs //
  for( unsigned int iB=0; iB < m_bTagWPs.size(); ++iB){
    /*
    std::string baseBTagType = "";
    if (m_bTagIsFixed.at(iB))
      baseBTagType = "MV2c10_FixedCutBEff_";
    else
      baseBTagType = "FlatBEff_";
    */
    std::string thisBTagName = "";
    thisBTagName = "weight_BTag_"+m_bTagWPs.at(iB);
    if( eventInfo->isAvailable< std::vector< float > >( thisBTagName.c_str() ) )
      m_weight_btag.at(iB) = eventInfo->auxdecor< std::vector< float > >( thisBTagName.c_str() );
  }

  // get vector of string giving the syst names of the upstream algo from TStore
  // (rememeber: 1st element is a blank string: nominal case!)
  if( m_firstEvent){
    std::vector< std::string >* systNames(nullptr);
    if( m_store->contains<std::vector<std::string> >( "BJetEfficiency_Algo_DL1r_FixedCutBEff_85" )){
      HelperFunctions::retrieve(systNames, "BJetEfficiency_Algo_DL1r_FixedCutBEff_85", 0, m_store); //.isSuccess()
      std::cout << " Using " <<  systNames->size() << " systematics from BJetEfficiency_Algo_DL1r_FixedCutBEff_85 " << std::endl;
    }else if( m_store->contains<std::vector<std::string> >( "BJetEfficiency_Algo_DL1r_FixedCutBEff_77" )){
      HelperFunctions::retrieve(systNames, "BJetEfficiency_Algo_DL1r_FixedCutBEff_77", 0, m_store); //.isSuccess()
      std::cout << " Using " << systNames->size() << " systematics from BJetEfficiency_Algo_DL1r_FixedCutBEff_77 " << std::endl;
    } else {
      std::cout << " No b-tagging systematics found !!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    }

    m_systSF_btag_names = *systNames;
    if( m_systSF_btag_names.size() > 0 && m_systSF_btag_names.at(0).size() == 0)
      m_systSF_btag_names.at(0) = "Nominal";

    m_firstEvent = false;
  }
}

//////////////////////////////////////////////////////
//         Clear  b-tagging scale factors           //
//       Currently the hybrid WP is turned off      //
//////////////////////////////////////////////////////

void MiniTree::ClearBtag() {
  for( unsigned int iB=0; iB < m_bTagWPs.size(); ++iB){
    m_weight_btag.at(iB).clear();
  }
  m_systSF_btag_names.clear();
}
