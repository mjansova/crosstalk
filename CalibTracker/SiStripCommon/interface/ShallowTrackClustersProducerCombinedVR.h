#ifndef SHALLOW_TRACKCLUSTERS_PRODUCER_COMBINED_VR
#define SHALLOW_TRACKCLUSTERS_PRODUCER_COMBINED_VR

#include "FWCore/Framework/interface/EDProducer.h"

#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/TrackExtraFwd.h"
#include "DataFormats/TrackReco/interface/TrackToTrackMap.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"

#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "TrackingTools/PatternTools/interface/TrajTrackAssociation.h"
#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/Common/interface/DetSetVectorNew.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "DataFormats/SiStripCluster/interface/SiStripCluster.h"
#include "DataFormats/SiStripDigi/interface/SiStripRawDigi.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"

#include "TROOT.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TList.h"
#include "TString.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "THStack.h"

class SiStripClusterInfo;
class SiStripProcessedRawDigi;
class TrackerTopology;
class SiStripLorentzAngle;
class MuonServiceProxy;
class DTGeometry;

class ShallowTrackClustersProducerCombinedVR : public edm::EDProducer {
public:
  explicit ShallowTrackClustersProducerCombinedVR(const edm::ParameterSet&);
private:
  const edm::EDGetTokenT<edm::View<reco::Track> > tracks_token_;
  const edm::EDGetTokenT<TrajTrackAssociationCollection> association_token_;
  const edm::EDGetTokenT< edmNew::DetSetVector<SiStripCluster> > clusters_token_;
  edm::EDGetTokenT<std::vector<reco::Vertex> >          theVertexToken_;
  edm::EDGetTokenT<reco::MuonTimeExtraMap> CombinedTimeTokens_;
  edm::EDGetTokenT<reco::MuonTimeExtraMap> DtTimeTokens_;
  edm::EDGetTokenT<reco::MuonTimeExtraMap> CscTimeTokens_;
  edm::EDGetTokenT<std::vector<reco::Muon> > MuonTokens_;
  edm::EDGetTokenT<edm::DetSetVector<SiStripProcessedRawDigi> > theDigisToken_;
  edm::EDGetTokenT<edm::DetSetVector<SiStripRawDigi> > theRawDigisToken_;
  edm::EDGetTokenT<edm::DetSetVector<SiStripProcessedRawDigi> >  theCMNToken_;
  edm::EDGetTokenT<edm::DetSetVector<SiStripDigi> >  srcZSdigi_;
  edm::EDGetTokenT<edm::TriggerResults> theTriggerToken_;
  std::string Suffix;
  std::string Prefix;
  int32_t lowBound;
  int32_t highBound;
  std::string filename;
  edm::ESHandle<SiStripLorentzAngle> lorentzAngleHandle;
  const std::string lorentzAngleName;
  bool isData;

  edm::Handle<std::vector<reco::Muon> > MuCollection;
  edm::Handle<reco::MuonTimeExtraMap> timeMap1;
  edm::Handle<reco::MuonTimeExtraMap> timeMap2;
  edm::Handle<reco::MuonTimeExtraMap> timeMap3;

  edm::Service<TFileService> fs_;
  TH1F* h1RawDigis_ = NULL;
  TH1F* h1CMN_ = NULL;
  TH1F* h1Processed_ = NULL;
  TH1F* h1Cluster_ = NULL;
  TH1F* h1CTCluster_ = NULL;
  TH1F* h1ClusterDiff_ = NULL;
  TH1F* h1ZSdigis_ = NULL;

  void produce( edm::Event &, const edm::EventSetup & );
  bool trackFilter(const reco::Track* trk);

  struct moduleVars {
    moduleVars(uint32_t, const TrackerTopology*);
    int subdetid, side, layerwheel, stringringrod, petal, stereo;
    uint32_t module;
  };

  struct NearDigis { 
    NearDigis(const SiStripClusterInfo&);
    NearDigis(const SiStripClusterInfo&, const edm::DetSetVector<SiStripProcessedRawDigi>&);
    float max, left, right, first, last, Lleft, Rright; 
    float etaX() const {return ((left+right)/max)/2.;}
    float eta()  const {return right>left ? max/(max+right) : left/(left+max);}
    float etaasymm() const {return right>left ? (right-max)/(right+max) : (max-left)/(max+left);}
    float outsideasymm() const {return (last-first)/(last+first);}
  };
};
#endif
