#include <iostream>

#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>

#include "xAODAnaHelpers/TruthMET.h"
#include "xAODMissingET/MissingETContainer.h"
#include "xAODMissingET/MissingET.h"
#include "xAODAnaHelpers/HelperClasses.h"


using namespace xAH;

TruthMET::TruthMET(const std::string& name, const std::string& detailStr, float units)
  : m_name(name), m_infoSwitch(detailStr), m_debug(false), m_units(units)
{
}

TruthMET::~TruthMET()
{
  if(m_debug) std::cout << " Deleting TruthMET "  << std::endl;
}

void TruthMET::setTree(TTree *tree)
{
  connectBranch<float>(tree,"MET_Truth",      &m_TruthMET_met);
  connectBranch<float>(tree,"MET_TruthPx",    &m_TruthMET_px);
  connectBranch<float>(tree,"MET_TruthPy",    &m_TruthMET_py);
  connectBranch<float>(tree,"MET_TruthSumEt", &m_TruthMET_sumet);
  connectBranch<float>(tree,"MET_TruthPhi",   &m_TruthMET_phi);
}

void TruthMET::setBranches(TTree *tree)
{
  setBranch(tree,"MET_Truth",      &m_TruthMET_met, "F");
  setBranch(tree,"MET_TruthPx",    &m_TruthMET_px, "F");
  setBranch(tree,"MET_TruthPy",    &m_TruthMET_py, "F");
  setBranch(tree,"MET_TruthSumEt", &m_TruthMET_sumet, "F");
  setBranch(tree,"MET_TruthPhi",   &m_TruthMET_phi, "F");
  return;
}

void TruthMET::clear()
{
  m_TruthMET_met = -999;
  m_TruthMET_px = -999;
  m_TruthMET_py = -999;
  m_TruthMET_sumet = -999;
  m_TruthMET_phi = -999;
  return;
}

void TruthMET::FillTruthMET(const xAOD::MissingETContainer* met) 
{
  const xAOD::MissingET* non_int = (*met)["NonInt"];    
  m_TruthMET_met   = non_int->met() / m_units;
  m_TruthMET_px    = non_int->mpx() / m_units;
  m_TruthMET_py    = non_int->mpy() / m_units;
  m_TruthMET_sumet = non_int->sumet() / m_units;
  m_TruthMET_phi   = non_int->phi();
}


