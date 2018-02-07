from CalibTracker.SiStripCommon.step2_DIGI_L1_DIGI2RAW_HLT_2016 import * 

process.GlobalTag.toGet = cms.VPSet(
  cms.PSet(record = cms.string("SiStripApvGainSimRcd"),
           tag = cms.string("myTag"),
           connect = cms.string("sqlite_file:/opt/sbg/data/data6/cms/mjansova/CMSSW_9_2_0/src/CalibTracker/SiStripCommon/test/dbConditions/G1_run284078.db")
          ),
  cms.PSet(record = cms.string("SiStripApvGainRcd"),
           tag = cms.string("myTag"),
           connect = cms.string("sqlite_file:/opt/sbg/data/data6/cms/mjansova/CMSSW_9_2_0/src/CalibTracker/SiStripCommon/test/dbConditions/G1_run284078.db")
          ),
  cms.PSet(record = cms.string("SiStripApvGain2Rcd"),
           tag = cms.string("myTag"),
           connect = cms.string("sqlite_file:/opt/sbg/data/data6/cms/mjansova/CMSSW_9_2_0/src/CalibTracker/SiStripCommon/test/dbConditions/G2_run284078.db")
          ),
  cms.PSet(record = cms.string("SiStripNoisesRcd"),
           tag = cms.string("myTag"),
           connect = cms.string("sqlite_file:/opt/sbg/data/data6/cms/mjansova/CMSSW_9_2_0/src/CalibTracker/SiStripCommon/test/dbConditions/Noise_run284078.db")
          ),
  cms.PSet(record = cms.string("SiStripBadChannelRcd"),
           tag = cms.string("myTag"),
           connect = cms.string("sqlite_file:/opt/sbg/data/data6/cms/mjansova/CMSSW_9_2_0/src/CalibTracker/SiStripCommon/test/dbConditions/BadChannel_run284078.db")
          ),
  cms.PSet(record = cms.string("SiStripBadFiberRcd"),
           tag = cms.string("myTag"),
           connect = cms.string("sqlite_file:/opt/sbg/data/data6/cms/mjansova/CMSSW_9_2_0/src/CalibTracker/SiStripCommon/test/dbConditions/BadFiber_run284078.db")
          )
)

import sys
#process.source.fileNames = cms.untracked.vstring(sys.argv[3] + "step1.root")
process.FEVTDEBUGHLToutput.fileName = sys.argv[2] + ".root" 


