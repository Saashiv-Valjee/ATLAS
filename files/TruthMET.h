#ifndef xAODAnaHelpers_TruthMET_H
#define xAODAnaHelpers_TruthMET_H

#include <TTree.h>
#include <TLorentzVector.h>

#include <vector>
#include <string>

#include <xAODAnaHelpers/HelperClasses.h>
#include <xAODAnaHelpers/HelperFunctions.h>

#include <xAODMissingET/MissingETContainer.h>
#include "xAODMissingET/MissingET.h"

namespace xAH {

    class TruthMET
    {
    public:
      TruthMET(const std::string& name = "TruthMET", const std::string& detailStr = "", float units = 1e3);
      virtual ~TruthMET();

      virtual void setTree    (TTree *tree);
      virtual void setBranches(TTree *tree);
      virtual void clear();
      virtual void FillTruthMET(const xAOD::MissingETContainer* TruthMet);//, const std::string& truthMetName); 
      template <typename T_BR>
	void connectBranch(TTree *tree, std::string name, T_BR *variable);
      template <typename T_BR>
	void setBranch(TTree *tree, std::string name, T_BR *variable, std::string type);

      std::string m_name;
      HelperClasses::METInfoSwitch m_infoSwitch;
      bool m_debug;
      float m_units;



    // truth
    float m_TruthMET_met;
    float m_TruthMET_px;
    float m_TruthMET_py;
    float m_TruthMET_phi;
    float m_TruthMET_sumet;
    };


   template <typename T_BR> void TruthMET::connectBranch(TTree *tree, std::string name, T_BR *variable)
      {
	tree->SetBranchStatus  ((m_name + name).c_str()  , 1);
      	tree->SetBranchAddress ((m_name + name).c_str()  , variable);
    }
  template <typename T_BR> void TruthMET::setBranch(TTree *tree, std::string name, T_BR *variable, std::string type)
    {
      if (!type.empty()) 
      {
        tree->Branch((m_name + name).c_str(), variable, (m_name + name + "/" + type).c_str());
      } 
      else 
      {
        tree->Branch((m_name + name).c_str(), variable);
      }
    }

}

#endif // xAODAnaHelpers_TruthMET_H

