from CalibTracker.SiStripCommon.shallowTree_test_template_cruzet import *
process.TFileService.fileName = 'bla2.root'
import sys


#process.source.fileNames = cms.untracked.vstring('file:step3CRUZET.root') #0T gen
#process.source.fileNames = cms.untracked.vstring('file:CRUZETVR/step3HICMN_RAW2DIGI_L1Reco_RECO.root') #0T gen
#process.source.fileNames = cms.untracked.vstring('file:CTcruzet_0.805step3.root') #0T gen
#process.source.fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/46EABE1D-5663-E711-B53F-02163E0142C5.root')
#process.source.fileNames = cms.untracked.vstring('root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/170926_111331/0000/merged/merged_1.root') #VR CRUZET Sep 2017

process.source.fileNames = cms.untracked.vstring(
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_1.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_2.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_3.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_4.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_5.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_6.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_7.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_8.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_9.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_10.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_11.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_12.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_13.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_14.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_15.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_16.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_17.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_18.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_19.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_20.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_21.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_22.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_23.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_24.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_25.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_26.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_27.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_28.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_29.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_30.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_31.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_32.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_33.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_34.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_35.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_36.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_37.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_38.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_39.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_40.root',
)
'''
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_41.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_42.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_43.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_44.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_45.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_46.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_47.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_48.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_49.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_50.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_51.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_52.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_53.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_54.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_55.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_56.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_57.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_58.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_59.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_60.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_61.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_62.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_63.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_64.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_65.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_66.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_67.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_68.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_69.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_70.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_71.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_72.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_73.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_74.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_75.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_76.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_77.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_78.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_79.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_80.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_81.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_82.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_83.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_84.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRAFT_ZS_RECO_TIMING/Cosmics/Run2017B_v1_RAW/171214_145114/0000/runCosmicsZS_85.root',
)
'''
#process.source.fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/46EABE1D-5663-E711-B53F-02163E0142C5.root','root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/3E480F3B-5663-E711-8B9E-02163E011BB7.root','root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/F093373D-5663-E711-874A-02163E0137FA.root','root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/F429C916-5663-E711-AC80-02163E01A493.root') #2017 runB data RUN IT
inputStr = sys.argv[2]
found = inputStr.find("root")

if found > 0:
    process.source.fileNames = cms.untracked.vstring("file:"+inputStr)
    process.TFileService.fileName = 'test_shallowTrackCRUZET_2017ZSampltest.root' + inputStr
    print(input)
else:
    process.TFileService.fileName = 'test_shallowTrackCRUZET_2017ZSampltest.root'


#process.source.fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/CosmicFall16PhaseIDR/TKCosmics_38T/GEN-SIM-RECO/DECO_90X_upgrade2017cosmics_realistic_deco_v18-v1/00000/0A229457-9122-E711-8E68-0CC47A78A4A6.root') #3.8 cosmics MC 28300ev

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Commissioning2017/Cosmics/RECO/PromptReco-v1/000/293/492/00000/1A059B34-6135-E711-8D9D-02163E011D9A.root')

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Commissioning2017/MinimumBias/RECO/PromptReco-v1/000/293/492/00000/7A3E3E7F-6B35-E711-8D8E-02163E011E08.root')

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_0_0/RelValCosmics_UP17/GEN-SIM-RECO/90X_upgrade2017cosmics_realistic_deco_v18_resub-v1/00000/461E2891-7614-E711-A90B-0025905B858A.root')

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Commissioning2017/MinimumBias/RECO/PromptReco-v1/000/293/492/00000/7A3E3E7F-6B35-E711-8D8E-02163E011E08.root')



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
    )

#from RecoTracker.TrackProducer.TrackRefitter_cfi import TrackRefitter

process.load('RecoTracker.TrackProducer.TrackRefitters_cff')
process.ShallowTrackClustersCombinedVR = cms.EDProducer("ShallowTrackClustersProducerCombinedVR",
                                      #Tracks=cms.InputTag("generalTracks",""),
                                      Tracks=cms.InputTag("ctfWithMaterialTracksP5",""),
                                      Clusters=cms.InputTag("siStripClusters"),
                                      vertices=cms.InputTag("offlinePrimaryVertices"),
                                      CombinedTiming = cms.InputTag("muonsWitht0Correction","combined"),
                                      DtTiming = cms.InputTag("muonsWitht0Correction","dt"),
                                      CscTiming = cms.InputTag("muonsWitht0Correction","csc"),
                                      Muons = cms.InputTag("muonsWitht0Correction"),
                                      LorentzAngle = cms.string(''),
                                      Prefix=cms.string("cluster"),
                                      Suffix=cms.string("tsos"),
                                      lowBound=cms.int32(0),
                                      highBound=cms.int32(1000),
                                      filename=cms.string("lowPUlogMC.txt"),
                                      isData=cms.bool(False))

#process.load('CalibTracker.SiStripCommon.ShallowTrackClustersProducer_cfi')
#process.tracksRefit = TrackRefitter.clone()

#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_cosmics')
process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Prompt_v9')
#process.GlobalTag = GlobalTag(process.GlobalTag, '90X_dataRun2_Prompt_v3')
#process.GlobalTag = GlobalTag(process.GlobalTag, '92X_dataRun2_Prompt_v4')

#"global_tag": "90X_dataRun2_Prompt_v3" for run 293492 (from 902)
#"global_tag": "90X_dataRun2_Prompt_v2" for data (before 902)
#MC global tag: 90X_upgrade2017_realistic_v20
#

process.TrackRefitter.src = "ctfWithMaterialTracksP5"
#process.TrackRefitter.src = "generalTracks"
process.TrackRefitter.TTRHBuilder = "WithTrackAngle"
process.TrackRefitter.NavigationSchool = ""
process.ShallowTrackClustersCombinedVR.Tracks = 'TrackRefitter'


#process.load('CalibTracker.SiStripCommon.ShallowTrackClustersProducer_cfi')
process.testTree = cms.EDAnalyzer(
   "ShallowTree",
   outputCommands = cms.untracked.vstring(
      'drop *',
      'keep *_ShallowTrackClustersCombinedVR_*_*',
      )
   )


process.p = cms.Path(#process.MeasurementTrackerEvent*
                     process.TrackRefitter*
                     process.ShallowTrackClustersCombinedVR*process.testTree)



#print process.dumpPython() 
