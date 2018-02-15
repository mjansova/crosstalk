
m SimGeneral.MixingModule.SiStripSimParameters_cfi import SiStripSimBlock


import sys
value = map(float, sys.argv[3:])

SiStripSimBlock.electronPerAdcDec = cms.double(value[0])
#TIB
SiStripSimBlock.CouplingConstantDecIB1  = cms.vdouble(value[1], value[2], value[3])
SiStripSimBlock.CouplingConstantDecIB2  = cms.vdouble(value[4], value[5], value[6])
#TOB
SiStripSimBlock.CouplingConstantDecOB1  = cms.vdouble(value[7], value[8], value[9])
SiStripSimBlock.CouplingConstantDecOB2  = cms.vdouble(value[10], value[11], value[12])


from CalibTracker.SiStripCommon.step3_RAW2DIGI_L1Reco_RECO_2017CosCRUZET import * #good name

process.source.fileNames = cms.untracked.vstring("file:"+ sys.argv[2] + ".root") 

process.RECOSIMoutput.fileName = cms.untracked.string(sys.argv[2] + "step3.root")

print(sys.argv[2])

