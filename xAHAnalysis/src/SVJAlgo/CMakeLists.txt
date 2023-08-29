################################################################################
# Package: DijetResonanceAlgo
################################################################################

# Declare the package name:
atlas_subdir( SVJAlgo )

find_package( ROOT COMPONENTS Core RIO Hist Tree )

# build a dictionary for the library
atlas_add_root_dictionary ( SVJAlgoLib SVJAlgoDictSource
                            ROOT_HEADERS SVJAlgo/*.h Root/LinkDef.h
                            EXTERNAL_PACKAGES ROOT )

# Component(s) in the package:
atlas_add_library( SVJAlgoLib SVJAlgo/*.h Root/*.h Root/*.cxx ${SVJAlgoDictSource}
  PUBLIC_HEADERS SVJAlgo
  INCLUDE_DIRS ${ROOT_INCLUDE_DIRS}
  LINK_LIBRARIES ${ROOT_LIBRARIES}
  AsgTools
  EventLoop
  xAODAnaHelpersLib
  xAODEgamma
  xAODEventInfo
  xAODJet
  xAODMissingET
  xAODMuon
  xAODRootAccess
  JetTileCorrectionLib ) 

# Install files from the package:
atlas_install_scripts( scripts/*.py )
atlas_install_data( data/*.py data/*.xml data/*.txt data/*.root)
