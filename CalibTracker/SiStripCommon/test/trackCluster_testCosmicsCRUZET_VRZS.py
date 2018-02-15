from CalibTracker.SiStripCommon.shallowTree_test_template_cruzet import *
process.TFileService.fileName = 'bla2.root'
import sys


#process.source.fileNames = cms.untracked.vstring('file:step3CRUZET.root') #0T gen
#process.source.fileNames = cms.untracked.vstring('file:CRUZETVR/step3HICMN_RAW2DIGI_L1Reco_RECO.root') #0T gen
#process.source.fileNames = cms.untracked.vstring('file:CTcruzet_0.805step3.root') #0T gen
#process.source.fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/46EABE1D-5663-E711-B53F-02163E0142C5.root')
#process.source.fileNames = cms.untracked.vstring('root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/170926_111331/0000/merged/merged_1.root') #VR CRUZET Sep 2017


process.source.fileNames = cms.untracked.vstring(
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_1.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_2.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_3.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_4.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_5.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_6.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_7.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_8.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_9.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_10.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_11.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_12.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_13.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_14.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_15.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_16.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_17.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_18.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_19.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_20.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_21.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_22.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_23.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_24.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_25.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_26.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_27.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_28.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_29.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_30.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_31.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_32.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_33.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_34.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_35.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_36.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_37.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_38.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_39.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_40.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171208_100034/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_41.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_1.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_2.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_3.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_4.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_5.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_6.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_7.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_8.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_9.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_10.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_11.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_12.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_13.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_14.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_15.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_16.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_17.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_18.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_19.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_20.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_21.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_22.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_23.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_24.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_25.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_26.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_27.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_28.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_29.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_30.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_31.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_32.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_33.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_34.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_35.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_36.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_37.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_38.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_39.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_40.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_TIMING/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171208_100101/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_muTiming_41.root',
)

'''
process.source.fileNames = cms.untracked.vstring(
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_1.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_2.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_3.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_4.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_5.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_6.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_7.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_8.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_9.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_10.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_11.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_12.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_13.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_14.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_15.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_16.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_17.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_18.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_19.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_20.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_21.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_22.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_23.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_24.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_25.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_26.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_27.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_28.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_29.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_30.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_31.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_32.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_33.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_34.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_35.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_36.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_37.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_38.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_39.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_40.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw1/Run2017D_v1_RAW/171013_141134/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_41.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_1.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_2.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_3.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_4.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_5.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_6.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_7.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_8.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_9.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_10.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_11.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_12.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_13.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_14.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_15.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_16.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_17.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_18.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_19.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_20.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_21.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_22.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_23.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_24.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_25.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_26.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_27.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_28.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_29.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_30.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_31.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_32.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_33.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_34.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_35.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_36.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_37.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_38.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_39.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_40.root',
'root://sbgse1.in2p3.fr//dpm/in2p3.fr/home/cms/phedex/store/user/mjansova/simu/CRUZET_VR_RECO_CT/ParkingCosmicsVirginRaw2/Run2017D_v1_RAW/171013_141155/0000/step3HICMN_RAW2DIGI_L1Reco_RECO_41.root'
)#VR CRUZET Sep2017 with onwn clustering
'''
#process.source.fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/46EABE1D-5663-E711-B53F-02163E0142C5.root','root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/3E480F3B-5663-E711-8B9E-02163E011BB7.root','root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/F093373D-5663-E711-874A-02163E0137FA.root','root://cms-xrd-global.cern.ch//store/data/Run2017B/Cosmics/RECO/PromptReco-v1/000/298/211/00000/F429C916-5663-E711-AC80-02163E01A493.root') #2017 runB data RUN IT
inputStr = sys.argv[2]
found = inputStr.find("root")

if found > 0:
    process.source.fileNames = cms.untracked.vstring("file:"+inputStr)
    process.TFileService.fileName = 'test_shallowTrackCRUZET_2017testsVRZS.root' + inputStr
    print(input)
else:
    process.TFileService.fileName = 'test_shallowTrackCRUZET_2017testsVRZS.root'


#process.source.fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/CosmicFall16PhaseIDR/TKCosmics_38T/GEN-SIM-RECO/DECO_90X_upgrade2017cosmics_realistic_deco_v18-v1/00000/0A229457-9122-E711-8E68-0CC47A78A4A6.root') #3.8 cosmics MC 28300ev

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Commissioning2017/Cosmics/RECO/PromptReco-v1/000/293/492/00000/1A059B34-6135-E711-8D9D-02163E011D9A.root')

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Commissioning2017/MinimumBias/RECO/PromptReco-v1/000/293/492/00000/7A3E3E7F-6B35-E711-8D8E-02163E011E08.root')

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/relval/CMSSW_9_0_0/RelValCosmics_UP17/GEN-SIM-RECO/90X_upgrade2017cosmics_realistic_deco_v18_resub-v1/00000/461E2891-7614-E711-A90B-0025905B858A.root')

#fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Commissioning2017/MinimumBias/RECO/PromptReco-v1/000/293/492/00000/7A3E3E7F-6B35-E711-8D8E-02163E011E08.root')



process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
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
