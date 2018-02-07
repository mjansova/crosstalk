from CalibTracker.SiStripCommon.MinBias_13TeV_pythia8_TuneCUETP8M1_cfi_GEN_SIM_2016 import * #good name
import sys
process.FEVTDEBUGoutput.fileName = cms.untracked.string(sys.argv[2] + "step1.root")

print(sys.argv[2])

