from ROOT import *
import os,shutil,math,glob
from array import array

datapaths=[]
datadir="testRunSignal/data-tree/"
paths=[] 
for f in os.listdir(datadir):
  paths=paths+glob.glob(datadir+"/*.root")
for f in paths:
  datapaths.append(f)

bins=[730.0, 755.0, 781.0, 807.0, 834.0, 861.0, 889.0, 917.0, 946.0, 976.0, 1006.0, 1037.0, 1068.0, 1100.0, 1133.0, 1166.0, 1200.0, 1234.0, 1269.0, 1305.0, 1341.0, 1378.0, 1416.0, 1454.0, 1493.0, 1533.0, 1573.0, 1614.0, 1656.0, 1698.0, 1741.0, 1785.0, 1830.0, 1875.0, 1921.0, 1968.0, 2016.0, 2065.0, 2114.0, 2164.0, 2215.0, 2267.0, 2320.0, 2374.0, 2429.0, 2485.0, 2542.0, 2600.0, 2659.0, 2719.0, 2780.0, 2842.0, 2905.0, 2969.0, 3034.0, 3100.0, 3167.0, 3235.0, 3305.0, 3376.0, 3448.0, 3521.0, 3596.0, 3672.0]

treeNames = ["JET_EtaIntercalibration_NonClosure__1up", "JET_EtaIntercalibration_NonClosure__1down", "JET_GroupedNP_1__1up", "JET_GroupedNP_1__1down", "JET_GroupedNP_2__1up", "JET_GroupedNP_2__1down", "JET_GroupedNP_3__1up", "JET_GroupedNP_3__1down", "JET_JER_DataVsMC__1up", "JET_JER_DataVsMC__1down", "JET_JER_EffectiveNP_1__1up", "JET_JER_EffectiveNP_1__1down", "JET_JER_EffectiveNP_2__1up", "JET_JER_EffectiveNP_2__1down", "JET_JER_EffectiveNP_3__1up", "JET_JER_EffectiveNP_3__1down", "JET_JER_EffectiveNP_4__1up", "JET_JER_EffectiveNP_4__1down", "JET_JER_EffectiveNP_5__1up", "JET_JER_EffectiveNP_5__1down", "JET_JER_EffectiveNP_6__1up", "JET_JER_EffectiveNP_6__1down", "JET_JER_EffectiveNP_7restTerm__1up", "JET_JER_EffectiveNP_7restTerm__1down"]

bTagSysDic = {
 "0":      "Nominal",
 "1":      "FT_TEFF_Eigen_B_0__1down",
 "2":      "FT_TEFF_Eigen_B_0__1up",
 "3":      "FT_TEFF_Eigen_B_1__1down",
 "4":      "FT_TEFF_Eigen_B_1__1up",
 "5":      "FT_TEFF_Eigen_B_2__1down",
 "6":      "FT_TEFF_Eigen_B_2__1up",
 "7":      "FT_TEFF_Eigen_B_3__1down",
 "8":      "FT_TEFF_Eigen_B_3__1up",
 "9":      "FT_TEFF_Eigen_B_4__1down",
 "10":     "FT_TEFF_Eigen_B_4__1up",
 "11":     "FT_TEFF_Eigen_B_5__1down",
 "12":     "FT_TEFF_Eigen_B_5__1up",
 "13":     "FT_TEFF_Eigen_B_6__1down",
 "14":     "FT_TEFF_Eigen_B_6__1up",
 "15":     "FT_TEFF_Eigen_B_7__1down",
 "16":     "FT_TEFF_Eigen_B_7__1up",
 "17":     "FT_TEFF_Eigen_B_8__1down",
 "18":     "FT_TEFF_Eigen_B_8__1up",
 "19":     "FT_TEFF_Eigen_C_0__1down",
 "20":     "FT_TEFF_Eigen_C_0__1up",
 "21":     "FT_TEFF_Eigen_C_1__1down",
 "22":     "FT_TEFF_Eigen_C_1__1up",
 "23":     "FT_TEFF_Eigen_C_2__1down",
 "24":     "FT_TEFF_Eigen_C_2__1up",
 "25":     "FT_TEFF_Eigen_C_3__1down",
 "26":     "FT_TEFF_Eigen_C_3__1up",
 "27":     "FT_TEFF_Eigen_Light_0__1down",
 "28":     "FT_TEFF_Eigen_Light_0__1up",
 "29":     "FT_TEFF_Eigen_Light_1__1down",
 "30":     "FT_TEFF_Eigen_Light_1__1up",
 "31":     "FT_TEFF_Eigen_Light_2__1down",
 "32":     "FT_TEFF_Eigen_Light_2__1up",
 "33":     "FT_TEFF_Eigen_Light_3__1down",
 "34":     "FT_TEFF_Eigen_Light_3__1up",
 "35":     "FT_TEFF_Eigen_Light_4__1down",
 "36":     "FT_TEFF_Eigen_Light_4__1up",
 "37":     "FT_TEFF_extrapolation__1down",
 "38":     "FT_TEFF_extrapolation__1up",
 "39":     "FT_TEFF_extrapolation_from_charm__1down",
 "40":     "FT_TEFF_extrapolation_from_charm__1up",
}

print datapaths
print "Number of files: ",len(datapaths)

outFile = TFile.Open('signal.root','RECREATE')

for item in treeNames:
  histitle=item
  hist = TH1F( histitle, histitle, len(bins)-1, array('f', bins) )
  hist.SetName(histitle)
  for File in datapaths:
    f=TFile(File)
    t=f.Get("outTree" + item)
    N=t.GetEntries()
    for j in range(0,N):
      t.GetEntry(j)
      selected = []
      for jetNum in range(0, t.njet):
        if t.jet_Jvt[jetNum]<0.59: 
          continue
        if (t.jet_pt[jetNum]<60 and abs(t.jet_eta[jetNum])<=2.5 and abs(t.jet_eta[jetNum]) > 2.4 ):
          if t.jet_Jvt[jetNum]<0.11: 
            continue
        if t.jet_pt[jetNum]<25:
          continue
        selected.append(jetNum)  

      if len(selected) < 4:
        continue

      if t.jet_pt[selected[0]]>=250 and t.jet_pt[selected[1]]>=250 and t.jet_pt[selected[2]]>=120 and (abs(t.jet_rapidity[selected[0]]-t.jet_rapidity[selected[1]])/2)<=0.8 and abs(t.jet_eta[selected[0]])<=2.4 and abs(t.jet_eta[selected[1]])<=2.4 and abs(t.jet_eta[selected[2]])<=2.4 and abs(t.jet_eta[selected[3]])<=4.5 and t.jet_DL1r[selected[0]]>0.821614146233 and t.jet_DL1r[selected[1]]>0.821614146233 and (t.jet_DL1r[selected[2]]>0.821614146233 or t.jet_DL1r[selected[3]]>0.821614146233):
        jet_1=TLorentzVector() 
        jet_2=TLorentzVector() 
        jet_1.SetPtEtaPhiE(t.jet_pt[selected[0]],t.jet_eta[selected[0]],t.jet_phi[selected[0]],t.jet_E[selected[0]])
        jet_2.SetPtEtaPhiE(t.jet_pt[selected[1]],t.jet_eta[selected[1]],t.jet_phi[selected[1]],t.jet_E[selected[1]])
        hist.Fill((jet_1+jet_2).M(), t.mcEventWeight)
  outFile.cd()
  hist.Write(hist.GetName(),TObject.kOverwrite)

for i in range(0, len(bTagSysDic)):
  histitle=bTagSysDic[str(i)]
  hist = TH1F( histitle, histitle, len(bins)-1, array('f', bins) )
  hist.SetName(histitle)
  for File in datapaths:
    f=TFile(File)
    t=f.Get("outTree")
    N=t.GetEntries()
    for j in range(0,N):
      t.GetEntry(j)
      weight = t.mcEventWeight * t.weight_btag_DL1r_FixedCutBEff_77[i]
      selected = []
      for jetNum in range(0, t.njet):
        if t.jet_Jvt[jetNum]<0.59: 
          continue
        if (t.jet_pt[jetNum]<60 and abs(t.jet_eta[jetNum])<=2.5 and abs(t.jet_eta[jetNum]) > 2.4 ):
          if t.jet_Jvt[jetNum]<0.11: 
            continue
        if t.jet_pt[jetNum]<25:
          continue
        selected.append(jetNum)  

      if len(selected) < 4:
        continue

      if t.jet_pt[selected[0]]>=250 and t.jet_pt[selected[1]]>=250 and t.jet_pt[selected[2]]>=120 and (abs(t.jet_rapidity[selected[0]]-t.jet_rapidity[selected[1]])/2)<=0.8 and abs(t.jet_eta[selected[0]])<=2.4 and abs(t.jet_eta[selected[1]])<=2.4 and abs(t.jet_eta[selected[2]])<=2.4 and abs(t.jet_eta[selected[3]])<=4.5 and t.jet_DL1r[selected[0]]>0.821614146233 and t.jet_DL1r[selected[1]]>0.821614146233 and (t.jet_DL1r[selected[2]]>0.821614146233 or t.jet_DL1r[selected[3]]>0.821614146233):
        jet_1=TLorentzVector() 
        jet_2=TLorentzVector() 
        jet_1.SetPtEtaPhiE(t.jet_pt[selected[0]],t.jet_eta[selected[0]],t.jet_phi[selected[0]],t.jet_E[selected[0]])
        jet_2.SetPtEtaPhiE(t.jet_pt[selected[1]],t.jet_eta[selected[1]],t.jet_phi[selected[1]],t.jet_E[selected[1]])
        hist.Fill((jet_1+jet_2).M(), weight)
  outFile.cd()
  hist.Write(hist.GetName(),TObject.kOverwrite)

outFile.Close()  
print "All jobs are done. "


















