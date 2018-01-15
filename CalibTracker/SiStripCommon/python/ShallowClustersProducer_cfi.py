import FWCore.ParameterSet.Config as cms

shallowClusters = cms.EDProducer("ShallowClustersProducer",
                                 Clusters=cms.InputTag("siStripClusters"),
                                 lumiScalers = cms.InputTag("scalersRawToDigi"),
                                 vertices=cms.InputTag("offlinePrimaryVertices"),
                                 Prefix=cms.string("cluster"),
                                 Sufix=cms.string("Tracking"),
                                 )

