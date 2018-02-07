from CalibTracker.SiStripCommon.step3_RAW2DIGI_L1Reco_RECO_2016 import * #good name


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

process.source.fileNames = cms.untracked.vstring("file:"+ sys.argv[2] + ".root") 

process.RECOSIMoutput.fileName = cms.untracked.string(sys.argv[2] + "step3.root")

print(sys.argv[2])

