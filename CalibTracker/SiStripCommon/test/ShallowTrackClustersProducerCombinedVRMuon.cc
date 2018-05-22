#include "CalibTracker/SiStripCommon/interface/ShallowTrackClustersProducerCombinedVR.h"
#include "FWCore/Utilities/interface/isFinite.h"

#include "RecoMuon/TrackingTools/interface/MuonServiceProxy.h"

#include "DataFormats/Common/interface/Ref.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"


#include <Geometry/CSCGeometry/interface/CSCLayer.h>
#include <DataFormats/MuonDetId/interface/CSCDetId.h>
#include <DataFormats/CSCRecHit/interface/CSCRecHit2D.h>
#include <DataFormats/CSCRecHit/interface/CSCRangeMapAccessor.h>

#include "CommonTools/Statistics/interface/ChiSquaredProbability.h"
#include "DataFormats/MuonReco/interface/MuonCocktails.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtra.h"
#include "DataFormats/MuonReco/interface/MuonTimeExtraMap.h"

#include "Geometry/Records/interface/GlobalTrackingGeometryRecord.h"
#include "Geometry/CommonDetUnit/interface/GlobalTrackingGeometry.h"

#include "DataFormats/TrackingRecHit/interface/TrackingRecHitFwd.h"
#include "DataFormats/TrackReco/interface/TrackExtra.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "CalibTracker/SiStripCommon/interface/ShallowTools.h"


#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "TrackingTools/TrackFitters/interface/TrajectoryStateCombiner.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit1D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripRecHit2D.h"
#include "DataFormats/TrackerRecHit2D/interface/SiStripMatchedRecHit2D.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "CondFormats/SiStripObjects/interface/SiStripLorentzAngle.h"
#include "CondFormats/DataRecord/interface/SiStripLorentzAngleRcd.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetUnit.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "boost/foreach.hpp"
#include "RecoLocalTracker/SiStripClusterizer/interface/SiStripClusterInfo.h"
#include "DataFormats/TrackerCommon/interface/TrackerTopology.h"
#include "Geometry/Records/interface/TrackerTopologyRcd.h"
#include "DataFormats/SiStripDigi/interface/SiStripProcessedRawDigi.h"
#include "FWCore/Common/interface/TriggerNames.h"

#include "DataFormats/MuonDetId/interface/DTLayerId.h"
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
#include "DataFormats/MuonDetId/interface/DTWireId.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTSuperLayer.h"
#include "Geometry/DTGeometry/src/DTTopology.cc"

#include "DataFormats/DTRecHit/interface/DTSLRecSegment2D.h"
#include "RecoLocalMuon/DTSegment/src/DTSegmentUpdator.h"
#include "RecoLocalMuon/DTSegment/src/DTSegmentCleaner.h"
#include "RecoLocalMuon/DTSegment/src/DTHitPairForFit.h"
#include "RecoLocalMuon/DTSegment/src/DTSegmentCand.h"
#include "Geometry/Records/interface/DTRecoGeometryRcd.h"

#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "CalibTracker/Records/interface/SiStripDependentRecords.h"
#include <map>
#include <iostream>
#include <fstream>

#include "TMath.h"

using namespace std;


  //ofstream myfile2;

ShallowTrackClustersProducerCombinedVR::ShallowTrackClustersProducerCombinedVR(const edm::ParameterSet& iConfig)
  :  tracks_token_(consumes<edm::View<reco::Track> >(iConfig.getParameter<edm::InputTag>("Tracks"))),
     association_token_(consumes<TrajTrackAssociationCollection>(iConfig.getParameter<edm::InputTag>("Tracks"))),
     clusters_token_( consumes< edmNew::DetSetVector<SiStripCluster> >( iConfig.getParameter<edm::InputTag>("Clusters") ) ),
     theVertexToken_(consumes<std::vector<reco::Vertex> >          (iConfig.getParameter<edm::InputTag>("vertices"))),
     CombinedTimeTokens_(consumes<reco::MuonTimeExtraMap>          (iConfig.getParameter<edm::InputTag>("CombinedTiming"))),
     DtTimeTokens_(consumes<reco::MuonTimeExtraMap>          (iConfig.getParameter<edm::InputTag>("DtTiming"))),
     CscTimeTokens_(consumes<reco::MuonTimeExtraMap>          (iConfig.getParameter<edm::InputTag>("CscTiming"))),
     MuonTokens_(consumes<std::vector<reco::Muon> >          (iConfig.getParameter<edm::InputTag>("Muons"))),
     theDigisToken_    (consumes<edm::DetSetVector<SiStripProcessedRawDigi> > (edm::InputTag("siStripProcessedRawDigis", ""))),
     //theRawDigisToken_    (consumes<edm::DetSetVector<SiStripRawDigi> > (edm::InputTag("siStripDigis", "VirginRaw"))),
     //theRawDigisToken_    (consumes<edm::DetSetVector<SiStripRawDigi> > (edm::InputTag("siStripZeroSuppression", "VirginRaw"))),
     theRawDigisToken_    (consumes<edm::DetSetVector<SiStripRawDigi> > (edm::InputTag("siStripZeroSuppression", "PEDSUBADCVirginRaw"))),
     theCMNToken_    (consumes<edm::DetSetVector<SiStripProcessedRawDigi> > (edm::InputTag("siStripZeroSuppression", "APVCMVirginRaw"))),
     srcZSdigi_    (consumes<edm::DetSetVector<SiStripDigi> > (edm::InputTag("siStripZeroSuppression", "VirginRaw"))),
     //srcZSdigi_    (consumes<edm::DetSetVector<SiStripDigi> > (edm::InputTag("siStripDigis", "ZeroSuppressed"))), //"siStripDigis"              "ZeroSuppressed"
     //theTriggerToken_    (consumes<edm::TriggerResults > (edm::InputTag("TriggerResults","","HLT"))),
     Suffix       ( iConfig.getParameter<std::string>("Suffix")    ),
     Prefix       ( iConfig.getParameter<std::string>("Prefix") ),
     //lorentzAngleName(iConfig.getParameter<std::string>("LorentzAngle")),
     isData       ( iConfig.getParameter<bool>("isData") )
     //lowBound       ( iConfig.getParameter<int32_t>("lowBound") ),
     //highBound       ( iConfig.getParameter<int32_t>("highBound") ),
     //filename       ( iConfig.getParameter<std::string>("filename") )
{

  //cout << "constructor fine " << endl;
  produces<std::vector<int> > ( Suffix + "clusterIdx"    ); //link: on trk cluster --> general cluster info 
  produces<std::vector<int> > ( Suffix + "onTrkClusterIdx" ); //link: general cluster info --> on track cluster
	produces <std::vector<int> > ( Suffix + "onTrkClustersBegin"  ); //link: track --> onTrkInfo (range)
	produces <std::vector<int> > ( Suffix + "onTrkClustersEnd" ); //link: track --> onTrkInfo (range)
  produces <std::vector<int> > ( Suffix + "trackindex" ); //link: on trk cluster --> track index

  produces <std::vector<unsigned int> > ( Suffix + "trackmulti"   );
  produces <std::vector<float> >        ( Suffix + "localtheta"   );  
  produces <std::vector<float> >        ( Suffix + "localeta"   );  
  produces <std::vector<float> >        ( Suffix + "localphi"     );  
  produces <std::vector<float> >        ( Suffix + "localpitch"   );  
  produces <std::vector<float> >        ( Suffix + "localx"       );  
  produces <std::vector<float> >        ( Suffix + "localy"       );  
  produces <std::vector<float> >        ( Suffix + "localz"       );  
  produces <std::vector<float> >        ( Suffix + "strip"        );  
  produces <std::vector<float> >        ( Suffix + "globaltheta"  );  
  produces <std::vector<float> >        ( Suffix + "globaleta"  );  
  produces <std::vector<float> >        ( Suffix + "globalphi"    );
  produces <std::vector<float> >        ( Suffix + "globalx"      );
  produces <std::vector<float> >        ( Suffix + "globaly"      );
  produces <std::vector<float> >        ( Suffix + "globalz"      );
  produces <std::vector<float> >        ( Suffix + "transverseCurvature"      );
  produces <std::vector<float> >        ( Suffix + "trackPt"      );
  produces <std::vector<float> >        ( Suffix + "trackEta"      );
  produces <std::vector<float> >        ( Suffix + "insidistance" );
  produces <std::vector<float> >        ( Suffix + "covered"      );
  produces <std::vector<float> >        ( Suffix + "projwidth"    );
  produces <std::vector<float> >        ( Suffix + "BdotX"        );
  produces <std::vector<float> >        ( Suffix + "BdotY"        );
  produces <std::vector<float> >        ( Suffix + "BdotZ"        );
  produces <std::vector<float> >        ( Suffix + "BdotMag"        );

  produces <std::vector<float> >        ( Suffix + "rhlocalx"      );   
  produces <std::vector<float> >        ( Suffix + "rhlocaly"      );   
  produces <std::vector<float> >        ( Suffix + "rhlocalxerr"   );   
  produces <std::vector<float> >        ( Suffix + "rhlocalyerr"   );   
  produces <std::vector<float> >        ( Suffix + "rhglobalx"     );   
  produces <std::vector<float> >        ( Suffix + "rhglobaly"     );   
  produces <std::vector<float> >        ( Suffix + "rhglobalz"     );
  produces <std::vector<float> >        ( Suffix + "rhglobaltheta"     );
  produces <std::vector<float> >        ( Suffix + "rhglobalphi"     );
  produces <std::vector<float> >        ( Suffix + "rhstrip"       );   
  produces <std::vector<float> >        ( Suffix + "rhmerr"        );   

  produces <std::vector<float> >        ( Suffix + "ubstrip"       );   
  produces <std::vector<float> >        ( Suffix + "ubmerr"        );   

  produces <std::vector<float> >       ( Suffix + "driftx"         );
  produces <std::vector<float> >       ( Suffix + "drifty"         );
  produces <std::vector<float> >       ( Suffix + "driftz"         );
  produces <std::vector<float> >       ( Suffix + "globalZofunitlocalY"  );            


  produces <std::vector<float> >    ( Prefix + "lorentzAngle"       );
  produces <std::vector<unsigned> >    ( Prefix + "number"       );
  produces <std::vector<unsigned> >    ( Prefix + "width"        );
  produces <std::vector<float> >       ( Prefix + "variance"     );
  produces <std::vector<float> >       ( Prefix + "barystrip"    );
  produces <std::vector<float> >       ( Prefix + "middlestrip"  );
  produces <std::vector<unsigned> >    ( Prefix + "charge"       );
  produces <std::vector<float> >       ( Prefix + "noise"        );
  produces <std::vector<float> >       ( Prefix + "ston"         );
  produces <std::vector<unsigned> >    ( Prefix + "seedstrip"    );
  produces <std::vector<unsigned> >    ( Prefix + "seedindex"    );
  produces <std::vector<unsigned> >    ( Prefix + "seedcharge"   );
  produces <std::vector<float> >       ( Prefix + "seednoise"    );
  produces <std::vector<float> >       ( Prefix + "seednoisepure"    );
  produces <std::vector<float> >       ( Prefix + "seedgain"     );
  produces <std::vector<unsigned> >    ( Prefix + "qualityisbad" );

  produces <std::vector<float> >       ( Prefix + "rawchargeC"   );
  produces <std::vector<float> >       ( Prefix + "rawchargeL"   );
  produces <std::vector<float> >       ( Prefix + "rawchargeR"   );
  produces <std::vector<float> >       ( Prefix + "rawchargeLL"   );
  produces <std::vector<float> >       ( Prefix + "rawchargeRR"   );
  produces <std::vector<float> >       ( Prefix + "eta"          );
  produces <std::vector<float> >       ( Prefix + "foldedeta"    );
  produces <std::vector<float> >       ( Prefix + "etaX"         );
  produces <std::vector<float> >       ( Prefix + "etaasymm"     );
  produces <std::vector<float> >       ( Prefix + "outsideasymm");
  produces <std::vector<float> >       ( Prefix + "neweta");
  produces <std::vector<float> >       ( Prefix + "newetaerr");

  produces <std::vector<unsigned> >    ( Prefix + "detid"         );
  produces <std::vector<int> >         ( Prefix + "subdetid"      );
  produces <std::vector<int> >         ( Prefix + "module"        );
  produces <std::vector<int> >         ( Prefix + "side"          );
  produces <std::vector<int> >         ( Prefix + "layerwheel"    );
  produces <std::vector<int> >         ( Prefix + "stringringrod" );
  produces <std::vector<int> >         ( Prefix + "petal"         );
  produces <std::vector<int> >         ( Prefix + "stereo"        );
  produces <std::vector<float> >         ( Prefix + "stripLength"        );
  produces <std::vector<float> >         ( Prefix + "sensorThickness"        );
  produces <std::vector<float> >         ( Prefix + "stripCharge"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeTotCharge"        );
  produces <std::vector<unsigned> >         ( Prefix + "stripChargeTotWidth"        );
  produces <std::vector<int> >         ( Prefix + "stripChargeStripNr"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeLocalTrackPhi"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeGlobalTrackPhi"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeLocalTrackTheta"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeGlobalTrackTheta"        );
  produces <std::vector<int> >         ( Prefix + "stripChargeSubdetid"        );
  produces <std::vector<int> >         ( Prefix + "stripChargeLayerwheel"        );
  produces <std::vector<unsigned> >         ( Prefix + "stripChargeDetid"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeLocalX"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeLocalY"        );
  produces <std::vector<float> >         ( Prefix + "stripChargetrackPt"        );
  produces <std::vector<float> >         ( Prefix + "stripChargelocalpitch"        );
  produces <std::vector<float> >         ( Prefix + "stripChargesensorThickness"        );
  produces <std::vector<float> >         ( Prefix + "stripChargeBdotY"        );
  produces <std::vector<float> >         ( "CTstripCharge"        );
  produces <std::vector<float> >         ( "CTstripChargeLocalTrackPhi"        );
  produces <std::vector<float> >         ( "CTstripChargeLocalTrackTheta"        );
  produces <std::vector<float> >         ( "CTstripChargeSubdetid"        );
  produces <std::vector<float> >         ( "CTstripChargeLayerwheel"        );
  produces <std::vector<float> >         ( "CTstripChargelocalpitch"        );
  produces <std::vector<float> >         ( "CTstripChargesensorThickness"        );
  produces <std::vector<float> >         ( "CTstripChargeTotCharge"        );
  produces <std::vector<float> >         ( "CTstripChargeTotChargeRescaled"        );
  produces <std::vector<float> >         ( "CTstripChargeTotWidth"        );
  produces <std::vector<float> >         ( "CTCmbtimeVtxr"        );
  produces <std::vector<float> >         ( "CTCmbtimeVtxrErr"        );
  produces <std::vector<float> >         ( "CTCombinedTimeOutInInOutDiffErr"        );
  produces <std::vector<float> >         ( "CTCombinedTimeOutInInOutDiff"        );
  produces <std::vector<float> >         ( "CTDttimeVtxr"        );
  produces <std::vector<float> >         ( "CTDttimeVtxrErr"        );
  produces <std::vector<float> >         ( "CTCsctimeVtxr"        );
  produces <std::vector<float> >         ( "CTCsctimeVtxrErr"        );
  produces <std::vector<float> >         ( "CTCmbtimeVtx"        );
  produces <std::vector<float> >         ( "CTCmbtimeVtxErr"        );
  produces <std::vector<float> >         ( "CTDttimeVtx"        );
  produces <std::vector<float> >         ( "CTDttimeVtxErr"        );
  produces <std::vector<float> >         ( "CTCsctimeVtx"        );
  produces <std::vector<float> >         ( "CTCsctimeVtxErr"        );

  produces <std::vector<float> >         ( "CTCombinedTimeTop"        );
  produces <std::vector<float> >         ( "CTCombinedTimeBottom"        );

  produces <std::vector<float> >         ( "CTMuontrackDirection"        );
  produces <std::vector<float> >         ( "CTDTMuontrackDirection"        );
  produces <std::vector<float> >         ( "CTMuonCombinedInverseBeta"        );
  produces <std::vector<float> >         ( "CTMuonCombinedFreeInverseBeta"        );
  produces <std::vector<float> >         ( "CTDTFreeInverseBeta"        );
  //produces <std::vector<float> >         ( "CTMuontrackPhi"        );
  produces <std::vector<float> >         ( "CTCombinedTimeForInOut"        );
  produces <std::vector<float> >         ( "CTCombinedTimeForOutIn"        );

  produces <std::vector<float> >    (   "CTDTlayer0"        );
  produces <std::vector<float> >    (   "CTDTlayer1"        );
  produces <std::vector<float> >    (  "CTDTlayer2"        );
  produces <std::vector<float> >    (   "CTDTlayer3"        );
  produces <std::vector<float> >    (   "CTDTlayer4"        );
  produces <std::vector<float> >    (   "CTnrOfMuHits"        );
  produces <std::vector<float> >    (   "CTsectorsOfDT"        );

  produces <std::vector<float> >    (   "CTMuOrigin"        );

  produces <std::vector<float> >        ( "PU"       );
  produces <std::vector<unsigned int> > ( "bx"       );
  produces <std::vector<unsigned int> > ( "run"       );


  produces <std::vector<float> >         ( "muonsDTMuontrackDirection"        );
  produces <std::vector<float> >         ( "muonsDTMuontrackSector"        );

  produces <std::vector<float> >         ( "muonsDTMuontrackInOut"        );
  produces <std::vector<float> >         ( "muonsDTMuontrackOutIn"        );

  produces <unsigned int>               ( "nroftracks"       );
  produces <unsigned int>               ( "nrofmuons"       );
  produces <unsigned int>               ( "nrofevents"       );



  produces <std::vector<float> >               ( "muonsDTMuontrackInOutTop"       );
  produces <std::vector<float> >              ( "muonsDTMuontrackInOutErrTop"       );
  produces <std::vector<float> >              ( "muonsDTMuontrackOutInTop"       );
  produces <std::vector<float> >              ( "muonsDTMuontrackOutInErrTop"       );
  produces <std::vector<float> >              ( "innerXtop"       );
  produces <std::vector<float> >              ( "innerYtop"       );
  produces <std::vector<float> >              ( "innerZtop"       );
  produces <std::vector<float> >              ( "innerVZtop"       );
  produces <std::vector<float> >              ( "innerVX"       );
  produces <std::vector<float> >              ( "innerVY"       );
  produces <std::vector<float> >              ( "Etatop"       );
  produces <std::vector<float> >              ( "outerXtop"       );
  produces <std::vector<float> >              ( "outerYtop"       );
  produces <std::vector<float> >              ( "outerZtop"       );
  produces <std::vector<float> >              ( "outerEtatop"       );
  produces <std::vector<float> >              ( "muonsDTMuontrackLastWheel"       );
  produces <std::vector<float> >              ( "muonsDTFreeInverseBeta"       );

  produces <std::vector<float> >              ( "CTouterXtop"       );
  produces <std::vector<float> >              ( "CTouterYtop"       );
  produces <std::vector<float> >              ( "CTouterZtop"       );
  produces <std::vector<float> >              ( "CTouterEtatop"       );
  produces <std::vector<float> >              ( "CTinnerXtop"       );
  produces <std::vector<float> >              ( "CTinnerYtop"       );
  produces <std::vector<float> >              ( "CTinnerZtop"       );
  produces <std::vector<float> >              ( "CTinnerVZtop"       );
  produces <std::vector<float> >              ( "CTinnerVX"       );
  produces <std::vector<float> >              ( "CTinnerVY"       );
  produces <std::vector<float> >              ( "CTEtatop"       );
  produces <std::vector<float> >              ( "CTglobalX"       );
  produces <std::vector<float> >              ( "CTglobalY"       );
  produces <std::vector<float> >              ( "CTglobalZ"       );
  produces <std::vector<float> >              ( "CTlocalX"       );
  produces <std::vector<float> >              ( "CTlocalY"       );
  produces <std::vector<float> >              ( "CTlocalZ"       );
  produces <std::vector<float> >              ( "CTtof"       );
  produces <std::vector<float> >              ( "CTtofImproved"       );
  produces <std::vector<float> >              ( "CTmuonsDTMuontrackLastWheel"       );


  produces <std::vector<float> >              ( "tzeroMinTimeInOut"       );
  produces <std::vector<float> >              ( "tzeroMinTimeOutIn"       );


  produces <std::vector<float> >              ( "muOrigin"       );
  produces <std::vector<float> >              ( "muTimeDifference"       );
  produces <std::vector<float> >              ( "nrOfMus"       );

/*  produces <bool>              ("passHLTL1SingleMu3v1" ); 
  produces <bool>              ( "passHLTL1SingleMu5v1" ); 
  produces <bool>              ("passHLTL1SingleMu7v1" );
  produces <bool>              ("passHLTL1SingleMuCosmicsv1" );
  produces <bool>              ("passHLTL1SingleMuOpenDTv2" );
  produces <bool>              ( "passHLTL1SingleMuOpenv2" );
*/
  //
}

void ShallowTrackClustersProducerCombinedVR::
produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  shallow::CLUSTERMAP clustermap = shallow::make_cluster_map(iEvent, clusters_token_);
  edm::Handle<edm::View<reco::Track> > tracks;	             iEvent.getByToken(tracks_token_, tracks);	  
  //edm::Handle<edm::TriggerResults> trigResults; iEvent.getByToken(theTriggerToken_,trigResults);


  int size = clustermap.size();
  //cout << "track size " << tracks->size() << "clustermap size " << size <<  endl;

	//links
  auto clusterIdx        = std::make_unique<std::vector<int>>(); //link: on trk cluster --> general cluster info 
  auto onTrkClusterIdx   = std::make_unique<std::vector<int>>(size,   -1); //link: general cluster info --> on track cluster
  auto onTrkClustersBegin = std::make_unique<std::vector<int>>( tracks->size(), -1 ); //link: track --> on trk cluster
  auto onTrkClustersEnd   = std::make_unique<std::vector<int>>( tracks->size(), -1 ); //link: track --> on trk cluster
  auto trackindex    = std::make_unique<std::vector<int>>(); //link: on track cluster --> track
	clusterIdx->reserve(size);
	trackindex->reserve(size);
	
  auto  trackmulti   = std::make_unique<std::vector<unsigned int>>(); trackmulti  ->reserve(size);
  auto  localtheta   = std::make_unique<std::vector<float>>(); localtheta  ->reserve(size);
  auto  localeta   = std::make_unique<std::vector<float>>(); localeta  ->reserve(size);
  auto  localphi     = std::make_unique<std::vector<float>>(); localphi    ->reserve(size);
  auto  localpitch   = std::make_unique<std::vector<float>>(); localpitch  ->reserve(size);
  auto  localx       = std::make_unique<std::vector<float>>(); localx      ->reserve(size);
  auto  localy       = std::make_unique<std::vector<float>>(); localy      ->reserve(size);
  auto  localz       = std::make_unique<std::vector<float>>(); localz      ->reserve(size);
  auto  strip        = std::make_unique<std::vector<float>>(); strip       ->reserve(size);
  auto  globaltheta  = std::make_unique<std::vector<float>>(); globaltheta ->reserve(size);
  auto  globaleta  = std::make_unique<std::vector<float>>(); globaleta ->reserve(size);
  auto  globalphi    = std::make_unique<std::vector<float>>(); globalphi   ->reserve(size);
  auto  globalx      = std::make_unique<std::vector<float>>(); globalx     ->reserve(size);
  auto  globaly      = std::make_unique<std::vector<float>>(); globaly     ->reserve(size);
  auto  globalz      = std::make_unique<std::vector<float>>(); globalz     ->reserve(size);
  auto  transverseCurvature      = std::make_unique<std::vector<float>>(); transverseCurvature     ->reserve(size);
  auto  trackPt            = std::make_unique<std::vector<float>>(); trackPt     ->reserve(size);
  auto  trackEta            = std::make_unique<std::vector<float>>(); trackEta     ->reserve(size);
  auto  insidistance = std::make_unique<std::vector<float>>(); insidistance->reserve(size);
  auto  projwidth    = std::make_unique<std::vector<float>>(); projwidth   ->reserve(size);
  auto  BdotX        = std::make_unique<std::vector<float>>(); BdotX       ->reserve(size);
  auto  BdotY        = std::make_unique<std::vector<float>>(); BdotY       ->reserve(size);
  auto  BdotZ        = std::make_unique<std::vector<float>>(); BdotZ       ->reserve(size);
  auto  BdotMag        = std::make_unique<std::vector<float>>(); BdotMag       ->reserve(size);
  auto  covered      = std::make_unique<std::vector<float>>(); covered     ->reserve(size);
  auto  rhlocalx     = std::make_unique<std::vector<float>>(); rhlocalx   ->reserve(size);
  auto  rhlocaly     = std::make_unique<std::vector<float>>(); rhlocaly   ->reserve(size);  
  auto  rhlocalxerr  = std::make_unique<std::vector<float>>(); rhlocalxerr->reserve(size);  
  auto  rhlocalyerr  = std::make_unique<std::vector<float>>(); rhlocalyerr->reserve(size);    
  auto  rhglobalx    = std::make_unique<std::vector<float>>(); rhglobalx  ->reserve(size);  
  auto  rhglobaly    = std::make_unique<std::vector<float>>(); rhglobaly  ->reserve(size);  
  auto  rhglobalz    = std::make_unique<std::vector<float>>(); rhglobalz  ->reserve(size);  
  auto  rhglobaltheta    = std::make_unique<std::vector<float>>(); rhglobaltheta  ->reserve(size);  
  auto  rhglobalphi    = std::make_unique<std::vector<float>>(); rhglobalphi  ->reserve(size);  
  auto  rhstrip      = std::make_unique<std::vector<float>>(); rhstrip    ->reserve(size);  
  auto  rhmerr       = std::make_unique<std::vector<float>>(); rhmerr     ->reserve(size);  
  auto  ubstrip      = std::make_unique<std::vector<float>>(); ubstrip    ->reserve(size);  
  auto  ubmerr       = std::make_unique<std::vector<float>>(); ubmerr     ->reserve(size);  
  auto  driftx       = std::make_unique<std::vector<float>>(); driftx     ->reserve(size);
  auto  drifty       = std::make_unique<std::vector<float>>(); drifty     ->reserve(size);
  auto  driftz       = std::make_unique<std::vector<float>>(); driftz     ->reserve(size);
  auto  globalZofunitlocalY = std::make_unique<std::vector<float>>(); globalZofunitlocalY->reserve(size);


  auto       lorentzAngle         = std::make_unique<std::vector<float>>();
  auto       number        = std::make_unique<std::vector<unsigned>>(7,0);
  auto       width         = std::make_unique<std::vector<unsigned>>();
  auto       variance      = std::make_unique<std::vector<float>>();
  auto       barystrip     = std::make_unique<std::vector<float>>();
  auto       middlestrip   = std::make_unique<std::vector<float>>();
  auto       charge        = std::make_unique<std::vector<unsigned>>();
  auto       noise         = std::make_unique<std::vector<float>>();
  auto       ston          = std::make_unique<std::vector<float>>();
  auto       seedstrip     = std::make_unique<std::vector<unsigned>>();
  auto       seedindex     = std::make_unique<std::vector<unsigned>>();
  auto       seedcharge    = std::make_unique<std::vector<unsigned>>();
  auto       seednoise     = std::make_unique<std::vector<float>>();
  auto       seednoisepure     = std::make_unique<std::vector<float>>();
  auto       seedgain      = std::make_unique<std::vector<float>>();
  auto       qualityisbad  = std::make_unique<std::vector<unsigned>>();

  auto       rawchargeC    = std::make_unique<std::vector<float>>();
  auto       rawchargeL    = std::make_unique<std::vector<float>>();
  auto       rawchargeR    = std::make_unique<std::vector<float>>();
  auto       rawchargeLL   = std::make_unique<std::vector<float>>();
  auto       rawchargeRR   = std::make_unique<std::vector<float>>();
  auto       etaX          = std::make_unique<std::vector<float>>();
  auto       eta           = std::make_unique<std::vector<float>>();
  auto       foldedeta     = std::make_unique<std::vector<float>>();
  auto       etaasymm      = std::make_unique<std::vector<float>>();
  auto       outsideasymm  = std::make_unique<std::vector<float>>();
  auto       neweta        = std::make_unique<std::vector<float>>();
  auto       newetaerr     = std::make_unique<std::vector<float>>();

  auto       detid         = std::make_unique<std::vector<unsigned>>();
  auto       subdetid      = std::make_unique<std::vector<int>>();
  auto       side          = std::make_unique<std::vector<int>>();
  auto       module        = std::make_unique<std::vector<int>>();
  auto       layerwheel    = std::make_unique<std::vector<int>>();
  auto       stringringrod = std::make_unique<std::vector<int>>();
  auto       petal         = std::make_unique<std::vector<int>>();
  auto       stereo        = std::make_unique<std::vector<int>>();
  auto       stripLength   = std::make_unique<std::vector<float>>();
  auto       sensorThickness     = std::make_unique<std::vector<float>>();
  auto       stripCharge     = std::make_unique<std::vector<float>>();
  auto       stripChargeTotCharge     = std::make_unique<std::vector<float>>();
  auto       stripChargeTotWidth     = std::make_unique<std::vector<unsigned>>();
  auto       stripChargeStripNr     = std::make_unique<std::vector<int>>();
  auto       stripChargeLocalTrackPhi     = std::make_unique<std::vector<float>>();
  auto       stripChargeGlobalTrackPhi     = std::make_unique<std::vector<float>>();
  auto       stripChargeLocalTrackTheta     = std::make_unique<std::vector<float>>();
  auto       stripChargeGlobalTrackTheta     = std::make_unique<std::vector<float>>();
  auto       stripChargeSubdetid     = std::make_unique<std::vector<int>>();
  auto       stripChargeLayerwheel     = std::make_unique<std::vector<int>>();
  auto       stripChargeDetid     = std::make_unique<std::vector<unsigned>>();
  auto       stripChargeLocalX     = std::make_unique<std::vector<float>>();
  auto       stripChargeLocalY     = std::make_unique<std::vector<float>>();
  auto       stripChargetrackPt     = std::make_unique<std::vector<float>>();
  auto       stripChargelocalpitch    = std::make_unique<std::vector<float>>();
  auto       stripChargesensorThickness    = std::make_unique<std::vector<float>>();
  auto       stripChargeBdotY   = std::make_unique<std::vector<float>>();
  auto       CTstripCharge   = std::make_unique<std::vector<float>>();
  auto       CTstripChargeLocalTrackPhi   = std::make_unique<std::vector<float>>();
  auto       CTstripChargeLocalTrackTheta   = std::make_unique<std::vector<float>>();
  auto       CTstripChargeSubdetid   = std::make_unique<std::vector<float>>();
  auto       CTstripChargeLayerwheel   = std::make_unique<std::vector<float>>();
  auto       CTstripChargelocalpitch   = std::make_unique<std::vector<float>>();
  auto       CTstripChargesensorThickness   = std::make_unique<std::vector<float>>();
  auto       CTstripChargeTotCharge   = std::make_unique<std::vector<float>>();
  auto       CTstripChargeTotChargeRescaled   = std::make_unique<std::vector<float>>();
  auto       CTstripChargeTotWidth   = std::make_unique<std::vector<float>>();

  auto       CTCmbtimeVtxr  = std::make_unique<std::vector<float>>();
  auto       CTCmbtimeVtxrErr  = std::make_unique<std::vector<float>>();
  auto       CTDttimeVtxr = std::make_unique<std::vector<float>>();
  auto       CTDttimeVtxrErr   = std::make_unique<std::vector<float>>();
  auto       CTCsctimeVtxr   = std::make_unique<std::vector<float>>();
  auto       CTCsctimeVtxrErr   = std::make_unique<std::vector<float>>();

  auto       CTCmbtimeVtx  = std::make_unique<std::vector<float>>();
  auto       CTCmbtimeVtxErr  = std::make_unique<std::vector<float>>();
  auto       CTDttimeVtx = std::make_unique<std::vector<float>>();
  auto       CTDttimeVtxErr   = std::make_unique<std::vector<float>>();
  auto       CTCsctimeVtx   = std::make_unique<std::vector<float>>();
  auto       CTCsctimeVtxErr   = std::make_unique<std::vector<float>>();

  auto       CTCombinedTimeTop   = std::make_unique<std::vector<float>>();
  auto       CTCombinedTimeBottom   = std::make_unique<std::vector<float>>();
  auto       CTMuontrackDirection   = std::make_unique<std::vector<float>>();
  auto       CTDTMuontrackDirection   = std::make_unique<std::vector<float>>();
  auto        CTMuonCombinedInverseBeta  = std::make_unique<std::vector<float>>();
  auto        CTMuonCombinedFreeInverseBeta  = std::make_unique<std::vector<float>>();
  auto        CTDTFreeInverseBeta  = std::make_unique<std::vector<float>>();
  //auto       CTMuontrackPhi   = std::make_unique<std::vector<float>>();
  auto       CTCombinedTimeForInOut   = std::make_unique<std::vector<float>>();
  auto       CTCombinedTimeForOutIn   = std::make_unique<std::vector<float>>();
  auto       CTCombinedTimeOutInInOutDiff   = std::make_unique<std::vector<float>>();
  auto       CTCombinedTimeOutInInOutDiffErr   = std::make_unique<std::vector<float>>();

  auto  CTDTlayer0 = std::make_unique<std::vector<float>>();
  auto  CTDTlayer1 = std::make_unique<std::vector<float>>();
  auto  CTDTlayer2 = std::make_unique<std::vector<float>>();
  auto  CTDTlayer3 = std::make_unique<std::vector<float>>();
  auto  CTDTlayer4 = std::make_unique<std::vector<float>>();
  auto  CTnrOfMuHits = std::make_unique<std::vector<float>>();
  auto   CTsectorsOfDT= std::make_unique<std::vector<float>>();


  auto  CTMuOrigin  = std::make_unique<std::vector<float>>();

  auto         muonsDTMuontrackDirection = std::make_unique<std::vector<float>>();
  auto         muonsDTMuontrackSector= std::make_unique<std::vector<float>>();

  auto         muonsDTMuontrackInOut= std::make_unique<std::vector<float>>();
  auto         muonsDTMuontrackOutIn= std::make_unique<std::vector<float>>();

  auto       PU      = std::make_unique<std::vector<float>>();
  auto bx            = std::make_unique<std::vector<unsigned int>>();
  auto run            = std::make_unique<std::vector<unsigned int>>();
  auto nroftracks            = std::make_unique<unsigned int>();
  auto nrofmuons            = std::make_unique<unsigned int>();
  auto nrofevents            = std::make_unique<unsigned int>();

  auto muonsDTMuontrackInOutTop = std::make_unique<std::vector<float>>(); 
  auto muonsDTFreeInverseBeta = std::make_unique<std::vector<float>>(); 
    auto               muonsDTMuontrackOutInTop = std::make_unique<std::vector<float>>() ;
    auto               muonsDTMuontrackInOutErrTop = std::make_unique<std::vector<float>>(); 
    auto               muonsDTMuontrackOutInErrTop = std::make_unique<std::vector<float>>() ;
    auto               innerXtop =  std::make_unique<std::vector<float>>();
  auto                 innerYtop =  std::make_unique<std::vector<float>>();
  auto                 innerZtop =  std::make_unique<std::vector<float>>();
  auto                 innerVZtop =  std::make_unique<std::vector<float>>();
  auto                 innerVX =  std::make_unique<std::vector<float>>();
  auto                 innerVY =  std::make_unique<std::vector<float>>();
  auto                 Etatop =  std::make_unique<std::vector<float>>();
  auto                 outerXtop =  std::make_unique<std::vector<float>>();
  auto                 outerYtop =  std::make_unique<std::vector<float>>();
  auto                 outerZtop =  std::make_unique<std::vector<float>>();
  auto                 outerEtatop =  std::make_unique<std::vector<float>>();
  auto                  muonsDTMuontrackLastWheel=  std::make_unique<std::vector<float>>();

    auto               CTinnerXtop =  std::make_unique<std::vector<float>>();
  auto                 CTinnerYtop =  std::make_unique<std::vector<float>>();
  auto                 CTinnerZtop =  std::make_unique<std::vector<float>>();
  auto                 CTinnerVZtop =  std::make_unique<std::vector<float>>();
  auto                 CTinnerVY =  std::make_unique<std::vector<float>>();
  auto                 CTinnerVX =  std::make_unique<std::vector<float>>();
  auto                 CTEtatop =  std::make_unique<std::vector<float>>();
  auto                 CTglobalX =  std::make_unique<std::vector<float>>();
  auto                 CTglobalY =  std::make_unique<std::vector<float>>();
  auto                 CTglobalZ =  std::make_unique<std::vector<float>>();
  auto                 CTlocalX =  std::make_unique<std::vector<float>>();
  auto                 CTlocalY =  std::make_unique<std::vector<float>>();
  auto                 CTlocalZ =  std::make_unique<std::vector<float>>();
  auto                 CTtof =  std::make_unique<std::vector<float>>();
  auto                 CTtofImproved =  std::make_unique<std::vector<float>>();
  auto                 CTouterXtop =  std::make_unique<std::vector<float>>();
  auto                 CTouterYtop =  std::make_unique<std::vector<float>>();
  auto                 CTouterZtop =  std::make_unique<std::vector<float>>();
  auto                 CTouterEtatop =  std::make_unique<std::vector<float>>();
  auto                 CTmuonsDTMuontrackLastWheel=  std::make_unique<std::vector<float>>();



  auto                 tzeroMinTimeInOut=  std::make_unique<std::vector<float>>();
  auto                 tzeroMinTimeOutIn=  std::make_unique<std::vector<float>>();

  auto                 muOrigin =  std::make_unique<std::vector<float>>();
  auto                 muTimeDifference =  std::make_unique<std::vector<float>>();
  auto                 nrOfMus=  std::make_unique<std::vector<float>>();

/*  auto passHLTL1SingleMu3v1 = std::make_unique<bool>(); 
  auto passHLTL1SingleMu5v1 =  std::make_unique<bool>(); 
  auto passHLTL1SingleMu7v1 =   std::make_unique<bool>();
  auto passHLTL1SingleMuCosmicsv1 =   std::make_unique<bool>();
  auto passHLTL1SingleMuOpenDTv2 =   std::make_unique<bool>();
  auto passHLTL1SingleMuOpenv2 =    std::make_unique<bool>();
*/
  edm::ESHandle<TrackerGeometry> theTrackerGeometry;         iSetup.get<TrackerDigiGeometryRecord>().get( theTrackerGeometry );  
  edm::ESHandle<MagneticField> magfield;		     iSetup.get<IdealMagneticFieldRecord>().get(magfield);
  edm::ESHandle<SiStripLorentzAngle> SiStripLorentzAngle;    iSetup.get<SiStripLorentzAngleDepRcd>().get(SiStripLorentzAngle);
  //edm::ESHandle<DTGeometry> theDTGeometry;                   iSetup.get<MuonGeometryRecord>().get( theDTGeometry );  

  edm::Handle<TrajTrackAssociationCollection> associations;  iEvent.getByToken(association_token_, associations);

    edm::Handle<edm::DetSetVector<SiStripProcessedRawDigi> > rawProcessedDigis;
    iEvent.getByToken(theDigisToken_,rawProcessedDigis);

   edm::Handle< edm::DetSetVector<SiStripRawDigi> > moduleRawDigi;
   iEvent.getByToken(theRawDigisToken_,moduleRawDigi);


  edm::Handle<std::vector<reco::Vertex> > vtx;
  iEvent.getByToken(theVertexToken_, vtx); 

  edm::ESHandle<TrackerTopology> tTopoHandle;
  iSetup.get<TrackerTopologyRcd>().get(tTopoHandle);
  const TrackerTopology* const tTopo = tTopoHandle.product();

  edm::Handle<edm::DetSetVector<SiStripProcessedRawDigi> > moduleCM;
  iEvent.getByToken(theCMNToken_,moduleCM);

  edm::Handle< edm::DetSetVector<SiStripDigi> > moduleZSdigi;
  iEvent.getByToken(srcZSdigi_,moduleZSdigi);

  iEvent.getByToken(MuonTokens_,MuCollection);

 
  iEvent.getByToken(CombinedTimeTokens_,timeMap1);
  const reco::MuonTimeExtraMap & timeMapCmb = *timeMap1;
  iEvent.getByToken(DtTimeTokens_,timeMap2);
  const reco::MuonTimeExtraMap & timeMapDT = *timeMap2;
  iEvent.getByToken(CscTimeTokens_,timeMap3);
  const reco::MuonTimeExtraMap & timeMapCSC = *timeMap3;


/*  const edm::TriggerNames& trigNames = iEvent.triggerNames(*trigResults);
  *passHLTL1SingleMu3v1 =trigResults->accept(trigNames.triggerIndex("HLT_L1SingleMu3_v1")); 
  *passHLTL1SingleMu5v1 =trigResults->accept(trigNames.triggerIndex("HLT_L1SingleMu5_v1"));  
  *passHLTL1SingleMu7v1 =trigResults->accept(trigNames.triggerIndex("HLT_L1SingleMu7_v1"));  
  *passHLTL1SingleMuCosmicsv1 =trigResults->accept(trigNames.triggerIndex("HLT_L1SingleMuCosmics_v1"));  
  *passHLTL1SingleMuOpenDTv2 =trigResults->accept(trigNames.triggerIndex("HLT_L1SingleMuOpen_DT_v2"));  
  *passHLTL1SingleMuOpenv2 =trigResults->accept(trigNames.triggerIndex("HLT_L1SingleMuOpen_v2"));  
*/

  cout << "correct file" << endl;
  TrajectoryStateCombiner combiner;

	size_t ontrk_cluster_idx=0;
  std::map<size_t, std::vector<size_t> > mapping; //cluster idx --> on trk cluster idx (multiple)

      //ITERATING thorough value map
      /*for( reco::MuonTimeExtraMap::const_iterator timeIt = timeMapCmb.begin(); timeIt!= timeMapCmb.end(); timeIt++)
      {
          reco::MuonTimeExtraMap::container::const_iterator timeIt2 = timeIt.begin();
          for(;timeIt2!= timeIt.end(); timeIt2++)
          {
          float ftex = timeIt2->direction(); 
          float ttex = timeIt2->timeAtIpOutIn(); 
          cout << "values in the map" << ftex << "time " << ttex << std::endl;
          }
      }*/

  //if(iEvent.id().run() == 303357) TODO
  if(true)
  {


  float PU_=0;
  PU_=vtx->size();

  *nrofevents = 1;
  PU->push_back(PU_);
  bx->push_back(iEvent.bunchCrossing());
  run->push_back(iEvent.id().run()   );
  *nroftracks = 0;
  *nrofmuons = 0;


//track loop
  for( TrajTrackAssociationCollection::const_iterator association = associations->begin(); 
       association != associations->end(); association++) {
    const Trajectory*  traj  = association->key.get();
    const reco::Track* track = association->val.get();
		int trk_idx = shallow::findTrackIndex(tracks, track); 
		size_t trk_strt_idx = ontrk_cluster_idx;

 

cout << "before good track " << endl;

    bool isGoodTrack = trackFilter(track);
    if(!isGoodTrack)
        continue;

  uint32_t globalCounter = 0;
  vector<uint32_t> trackerTrack;
  bool isB =false;
  bool isT =false;
  bool muFound = false;
  vector<int> muType;
  vector<float> timeOfMu;       
  vector <float> vzOfMu;       
  for (uint32_t mmu=0; mmu<MuCollection->size(); mmu++)
  {
      isB = false; 
      isT = false; 

      const reco::TrackRef muT = MuCollection->at(mmu).outerTrack();
      if(muT.isNull())
          continue;
      float timeZero = MuCollection->at(mmu).t0();
      reco::MuonRef muTR(MuCollection, mmu);
      if(muTR.isNull())
          continue;
      reco::MuonTimeExtra bestTime = timeMapDT[muTR];
      cout << "muon " << mmu << " time in out " <<  bestTime.timeAtIpInOut() << " vz  " << muT->vz() << " t0 " << timeZero << endl;
      
      trackingRecHit_iterator  muHit2= muT->recHitsBegin();
      for(  ; muHit2 !=  muT->recHitsEnd(); muHit2++)
      {
             if( static_cast<int>((*muHit2)->geographicalId().det()) ==2  && static_cast<int>((*muHit2)->geographicalId().subdetId()) == static_cast<int>(MuonSubdetId::DT))
             {
                 DTChamberId DTchamber2((*muHit2)->geographicalId());
                 if(  (DTchamber2.sector()>6 && DTchamber2.sector()<13) || (DTchamber2.sector() == 14)  )
                 {
                     isB = true;
                     cout << "bottom ";
                 }
                 if( (DTchamber2.sector()>0 && DTchamber2.sector()<7) || (DTchamber2.sector() == 13)  )
                 {
                     isT = true;
                     cout << "top ";
                 }
             }
       }
       cout << endl;
       if( isT == true && isB == false)
           muType.push_back(1);
       else if( isT == false && isB == true)
           muType.push_back(2);
       
       timeOfMu.push_back(bestTime.timeAtIpInOut());       
       vzOfMu.push_back(muT->vz());       

         
      //if(MuCollection->at(mmu).isTrackerMuon() && MuCollection->at(mmu).isGlobalMuon() )
      //if(/*MuCollection->at(mmu).isTrackerMuon() &&*/ MuCollection->at(mmu).isStandAloneMuon() )
      if(MuCollection->at(mmu).isTrackerMuon() && MuCollection->at(mmu).isGlobalMuon() )
      {
          // (*nrofmuons)++;
          //cout << "global muon" << MuCollection->at(mu).isGlobalMuon() << endl;
          muFound = true;
          trackerTrack.push_back(mmu);
          globalCounter++; 
          break;
      }
  }

  cout << "number of global tracks " << globalCounter << endl;
     

       nrOfMus->push_back(muType.size());
       if(muType.size()==2) 
       {
            if(vzOfMu.at(0) > vzOfMu.at(1)-5 && vzOfMu.at(0) < vzOfMu.at(1)+5)
            {
                //cout << "after z cut " << endl;
                if(muType.at(0) == 1 && muType.at(1) == 2 )
                {
                    muTimeDifference->push_back(timeOfMu.at(0)-timeOfMu.at(1) );
                    cout << "top bottom tracks" << endl;
                }
                else if(muType.at(0) == 2 && muType.at(1) == 1 )
                {
                    muTimeDifference->push_back(timeOfMu.at(1)-timeOfMu.at(0) );
                    cout << "bottom top tracks" << endl;
                }

            }
       }

       muType.clear();
       timeOfMu.clear();       
       vzOfMu.clear();       
 
 
      if(!muFound) //no tacker muon
          continue;

//muon loop
  for(uint32_t l=0; l<trackerTrack.size(); l++ )
  {
      reco::MuonRef muonR(MuCollection, trackerTrack.at(l)); //@MJ@ TODO - for now first track but I must deal with that!!
      reco::MuonTimeExtra timec = timeMapCmb[muonR];
      reco::MuonTimeExtra timedt = timeMapDT[muonR];
      reco::MuonTimeExtra timecsc = timeMapCSC[muonR];


     //just a test
     //const reco::Track* bestMu = muonR->bestTrack();
     //reco::TrackRef  bestMu = muonR->globalTrack();

     reco::TrackRef  bestMu = muonR->innerTrack();
     if(bestMu.isNull())
         continue;
     cout << "inner global detid " << bestMu->innerDetId() << " inner local det id " << track->innerDetId() << endl;
     cout << "outer global detid " << bestMu->outerDetId() << " outer local det id " << track->outerDetId() << endl;
     if( !(bestMu->innerDetId() == track->innerDetId()) )
         continue;
     if( !(bestMu->outerDetId() == track->outerDetId()) )
         continue;

     //muon hits
     //reco::TrackRef muTrack = muonR->standAloneMuon();
     bool topTrack = false;
     bool bottomTrack = false;
     bool topMu = false;
     bool bottomMu = false;
     bool bothMu = false;
     bool DTlayer0 = false;
     bool DTlayer1 = false;
     bool DTlayer2 = false;
     bool DTlayer3 = false;
     bool DTlayer4 = false;
     uint32_t nrOfMuHits = 0;
     std::vector<uint32_t> sectorsOfDT;

     reco::TrackRef muTrack = muonR->globalTrack();
     //reco::TrackRef muTrack = muonR->standAloneMuon();
     if(!muTrack.isNull())
     {

         trackingRecHit_iterator  muHit= muTrack->recHitsBegin();
         DTChamberId lastDTchamber;
         
         for(  ; muHit !=  muTrack->recHitsEnd(); muHit++)
         {
             //save size of the hits
             //booleans for layer 1,2,3,4
             //booleans for layer 0 -full SL
             if( static_cast<int>((*muHit)->geographicalId().det()) ==2  && static_cast<int>((*muHit)->geographicalId().subdetId()) == static_cast<int>(MuonSubdetId::DT))
             {
                 DTChamberId DTchamber((*muHit)->geographicalId());
                 lastDTchamber =DTchamber;
                 DTLayerId DTLayer((*muHit)->geographicalId());
                 muonsDTMuontrackInOut->push_back(timeMapDT[muonR].timeAtIpInOut());
                 muonsDTMuontrackOutIn->push_back(timeMapDT[muonR].timeAtIpOutIn());
                 muonsDTMuontrackSector->push_back( DTchamber.sector() );
                 nrOfMuHits++; //it is probably not completely correct
                 if(std::find(sectorsOfDT.begin(), sectorsOfDT.end(), DTchamber.sector()) == sectorsOfDT.end())
                     sectorsOfDT.push_back(DTchamber.sector());
                 //if( !( (DTchamber.sector()>1 && DTchamber.sector()<7) || (DTchamber.sector() == 13) ) )
                 if(  (DTchamber.sector()>6 && DTchamber.sector()<13) || (DTchamber.sector() == 14)  )
                     bottomTrack = true;
                 if( (DTchamber.sector()>0 && DTchamber.sector()<7) || (DTchamber.sector() == 13)  )
                     topTrack = true;

                 

                 if(DTLayer.layer() == 0)
                     DTlayer0=true;
                 if(DTLayer.layer() == 1)
                     DTlayer1=true;
                 if(DTLayer.layer() == 2)
                     DTlayer2=true;
                 if(DTLayer.layer() == 3)
                     DTlayer3=true;
                 if(DTLayer.layer() == 4)
                     DTlayer4=true;
             }
         }


                 if( topTrack == true && bottomTrack == false)
                 {
                     muOrigin->push_back(1);
                     topMu = true;
                     cout << "top mu " << endl;
                 }
                 else if( topTrack == false && bottomTrack == true)
                 {
                     muOrigin->push_back(2);
                     bottomMu = true;
                     cout << "bottom mu " << endl;
                 }
                 else if( topTrack == true && bottomTrack == true)
                 {
                     muOrigin->push_back(3);
                     bothMu = true;
                 }
                 else
                 {
                     muOrigin->push_back(4);
                 }
            
             //if(true)
             if(abs(muTrack->eta())<1)
             {
              //cout << "nr of hits standalone " << muTrackSA->recHitsSize() << " nr of time measurements in DT " << timeMapDT[muonR].timeAtIpInOutHIT().size() << " nr of time measurements combined " << timeMapCmb[muonR].timeAtIpInOutHIT().size() << endl;
              //cout << "nr of hits combined " << muonR->combinedMuon()->recHitsSize() << " nr of time measurements in DT " << timeMapDT[muonR].timeAtIpInOutHIT().size() << " nr of time measurements combined " << timeMapCmb[muonR].timeAtIpInOutHIT().size() << endl;
              //cout << "nr of hits global  " << muTrack->recHitsSize() << " nr of time measurements in DT " << timeMapDT[muonR].timeAtIpInOutHIT().size() << " nr of time measurements combined " << timeMapCmb[muonR].timeAtIpInOutHIT().size() << endl;
             //if(muTrackSA->recHitsSize() != timeMapDT[muonR].timeAtIpInOutHIT().size())
	     //     cout << "hit and time sizes not the same!! " << endl;

			 muonsDTMuontrackInOutTop->push_back(timeMapDT[muonR].timeAtIpInOut()); 
			 muonsDTMuontrackOutInTop->push_back(timeMapDT[muonR].timeAtIpOutIn()) ;
			 muonsDTMuontrackInOutErrTop->push_back(timeMapDT[muonR].timeAtIpInOutErr()); 
			 muonsDTMuontrackOutInErrTop->push_back(timeMapDT[muonR].timeAtIpOutInErr()) ;
                         muonsDTMuontrackDirection->push_back(static_cast<int>(timeMapDT[muonR].direction()));
			 innerXtop->push_back( muTrack->innerPosition().x());
			 innerYtop->push_back( muTrack->innerPosition().y());
			 innerZtop->push_back( muTrack->innerPosition().z());
			 outerXtop->push_back( muTrack->outerPosition().x());
			 outerYtop->push_back( muTrack->outerPosition().y());
			 outerZtop->push_back( muTrack->outerPosition().z());
			 outerEtatop->push_back( muTrack->outerEta());
			 muonsDTMuontrackLastWheel->push_back( lastDTchamber.wheel() );
			 innerVZtop->push_back( muTrack->vz());
			 innerVX->push_back( muTrack->vx());
			 innerVY->push_back( muTrack->vy());
			 Etatop->push_back( muTrack->eta());
		         muonsDTFreeInverseBeta->push_back(timeMapDT[muonR].freeInverseBeta());
			 for(uint32_t tzero = 0; tzero< timeMapDT[muonR].timeAtIpInOutHIT().size(); tzero++)
			 {
			     tzeroMinTimeInOut->push_back(timeMapDT[muonR].timeAtIpInOutHIT().at(tzero) - timeMapDT[muonR].timeAtIpInOut() );
			     tzeroMinTimeOutIn->push_back(timeMapDT[muonR].timeAtIpOutInHIT().at(tzero) - timeMapDT[muonR].timeAtIpOutIn() );
			 }

	       }
    }

   //if(topTrack == false) //@MJ@ TODO not forget to remove that
   //      continue;

  
   if(muTrack.isNull()) //only global muons
       continue;

cout << " after good track " << endl;
    
     int trackDirection = static_cast<int>(timeMapCmb[muonR].direction());
     int DTtrackDirection = static_cast<int>(timeMapDT[muonR].direction());

      (*nroftracks)++;

    BOOST_FOREACH( const TrajectoryMeasurement measurement, traj->measurements() ) {
      const TrajectoryStateOnSurface tsos = measurement.updatedState();
      const TrajectoryStateOnSurface unbiased = combiner(measurement.forwardPredictedState(), measurement.backwardPredictedState());

      const TrackingRecHit*         hit        = measurement.recHit()->hit();
      const SiStripRecHit1D*        hit1D      = dynamic_cast<const SiStripRecHit1D*>(hit);
      const SiStripRecHit2D*        hit2D      = dynamic_cast<const SiStripRecHit2D*>(hit);
      const SiStripMatchedRecHit2D* matchedhit = dynamic_cast<const SiStripMatchedRecHit2D*>(hit);

      for(unsigned h=0; h<2; h++) { //loop over possible Hit options (1D, 2D)
				const SiStripCluster* cluster_ptr;
				if(!matchedhit && h==1) continue; 
				else if( matchedhit && h==0) cluster_ptr = &matchedhit->monoCluster(); 
				else if( matchedhit && h==1) cluster_ptr = &matchedhit->stereoCluster(); 
				else if(hit2D) cluster_ptr = (hit2D->cluster()).get(); 
				else if(hit1D) cluster_ptr = (hit1D->cluster()).get(); 
				else continue;

				shallow::CLUSTERMAP::const_iterator cluster = clustermap.find( std::make_pair( hit->geographicalId().rawId(), cluster_ptr->firstStrip() ));
				if(cluster == clustermap.end() ) throw cms::Exception("Logic Error") << "Cluster not found: this could be a configuration error" << std::endl;
	
				unsigned i = cluster->second;

                                uint32_t id = hit->geographicalId();//@MJ@ detID here!!
				DetId modId(id);
                                const moduleVars moduleV(id, tTopo);
                                //std::cout << "before cluster info "  << std::endl;
                                const SiStripClusterInfo info(*cluster_ptr, iSetup, id);
                                //std::cout << "after cluster info "  << std::endl;
                                const NearDigis digis = rawProcessedDigis.isValid() ? NearDigis(info, *rawProcessedDigis) : NearDigis(info);
                                

				//find if cluster was already assigned to a previous track
				auto already_visited = mapping.find(i);
				int nassociations = 1;
				if(already_visited != mapping.end()) {
					nassociations += already_visited->second.size();
					for(size_t idx : already_visited->second) {
						trackmulti->at(idx)++;
					}
					already_visited->second.push_back(ontrk_cluster_idx);
				}
				else { //otherwise store this 
					std::vector<size_t> single = {ontrk_cluster_idx};
					mapping.insert( std::make_pair(i, single) );
				}

                                //@MJ@ TODO raw digis code
                                /*cout << "in here 1" << endl;
                                edm::DetSetVector<SiStripRawDigi>::const_iterator itRawDigis2 = moduleRawDigi->find(modId);
                                for (; itRawDigis2 != moduleRawDigi->end(); ++itRawDigis2) 
                                {
                                    cout << "available detId: " << itRawDigis2->id << endl;
                                }*/
      
                                //cout << "detsetvector rawdigis size " <<  moduleRawDigi->size() << endl ; 
                                //h1Cluster_ = new TH1F(("Cluster" + std::to_string(id)).c_str() , ("Cluster" + std::to_string(id)).c_str(), 900, 0, 900); //MJ@ TODO + eventnr@
                                //h1ClusterDiff_ = new TH1F(("ClusterDiff" + std::to_string(id)).c_str() , ("ClusterDiff" + std::to_string(id)).c_str(), 900, 0, 900); //MJ@ TODO + eventnr@
                                //h1CTCluster_ = new TH1F(("CTCluster" + std::to_string(id)).c_str() , ("CTCluster" + std::to_string(id)).c_str(), 910, -10, 900); //MJ@ TODO + eventnr@
                                std::vector<float> vRawDigis;
                                std::vector<float> vCMN;
                                edm::DetSetVector<SiStripRawDigi>::const_iterator itRawDigis = moduleRawDigi->find(modId);
                                edm::DetSetVector<SiStripProcessedRawDigi>::const_iterator itCMNDigis = moduleCM->find(modId);
                                //edm::DetSetVector<SiStripDigi>::const_iterator itZSdigis = moduleZSdigi->find(modId);
                                //cout << "in here 2" << endl;
                                if(itRawDigis != moduleRawDigi->end())
                                {
                                //cout << "in here 3" << endl;
                                    //h1RawDigis_ = new TH1F(("rawdigis" + std::to_string(id)).c_str() , ("rawdigis" + std::to_string(id)).c_str(), 900, 0, 900); //MJ@ TODO + eventnr@
                                    //h1CMN_ = new TH1F(("CMN" + std::to_string(id)).c_str() , ("CMN" + std::to_string(id)).c_str(), 900, 0, 900); //MJ@ TODO + eventnr@
                                    //h1Processed_ = new TH1F(("Processed" + std::to_string(id)).c_str() , ("Processed" + std::to_string(id)).c_str(), 900, 0, 900); //MJ@ TODO + eventnr@
                                    //h1ZSdigis_ = new TH1F(("ZS" + std::to_string(id)).c_str() , ("ZS" + std::to_string(id)).c_str(), 900, 0, 900); //MJ@ TODO + eventnr@
                                    edm::DetSet<SiStripRawDigi>::const_iterator itRaw = itRawDigis->begin();
                                    edm::DetSet<SiStripProcessedRawDigi>::const_iterator itCMN = itCMNDigis->begin();
                                    uint32_t rawstrip=0;
                                //cout << "in here 4" << endl;
                                    for(;itRaw != itRawDigis->end(); ++itRaw, ++rawstrip)
                                    {
                                //cout << "in here 5" << endl;
                                        //h1RawDigis_->Fill(rawstrip,itRaw->adc());
                                        vRawDigis.push_back(itRaw->adc());
                                        if(rawstrip!=0 && rawstrip%128==0)
                                            itCMN++;
                                        if(itCMN != itCMNDigis->end())
                                        { 
                                            //h1CMN_->Fill(rawstrip,itCMN->adc());
                                            vCMN.push_back(itCMN->adc());
                                            //h1Processed_->Fill(rawstrip,itRaw->adc()-itCMN->adc());
                                        }
                                    }
                                        //for( edm::DetSet<SiStripDigi>::const_iterator ZSdigis = itZSdigis->begin(); ZSdigis != itZSdigis->end(); ++ZSdigis) {
                                        //     //h1ZSdigis_->SetBinContent(ZSdigis->strip()+1, ZSdigis->adc());
                                        //     continue;
                                        //}

                                    /*h1RawDigis_->SetXTitle("strip#");
                                    h1RawDigis_->SetYTitle("ADC");
                                    h1RawDigis_->SetMaximum(1024.);
                                    h1RawDigis_->SetMinimum(-300.);
                                    h1RawDigis_->SetLineWidth(2);
                                    h1RawDigis_->Write();
                                    h1CMN_->SetXTitle("strip#");
                                    h1CMN_->SetYTitle("ADC");
                                    h1CMN_->SetMaximum(1024.);
                                    h1CMN_->SetMinimum(-300.);
                                    h1CMN_->SetLineWidth(2);
                                    h1CMN_->Write();
                                    h1Processed_->Write();
                                    h1ZSdigis_->Write();*/
                                }
                                else
                                {
                                    cout << "no digis found for given module!!!" << endl;
                                }

                                //cout << "in here done" << endl;
				const StripGeomDetUnit* theStripDet = dynamic_cast<const StripGeomDetUnit*>( theTrackerGeometry->idToDet( hit->geographicalId() ) );
				LocalVector drift = shallow::drift( theStripDet, *magfield, *SiStripLorentzAngle);
				
				if(nassociations == 1) onTrkClusterIdx->at(i) = ontrk_cluster_idx; //link: general cluster info --> on track cluster
				clusterIdx->push_back(  i );  //link: on trk cluster --> general cluster info
//if(PU_>lowBound && PU_<highBound)
//{
      (number->at(0))++;
      (number->at(moduleV.subdetid))++;
                     
                      float langle = (SiStripLorentzAngle.isValid()) ? SiStripLorentzAngle->getLorentzAngle(id) : 0.;
                      lorentzAngle->push_back(langle);
                      width->push_back(        cluster_ptr->amplitudes().size()                              );
		      barystrip->push_back(    cluster_ptr->barycenter()                                     );
		      variance->push_back(     info.variance()                                         );
		      middlestrip->push_back(  info.firstStrip() + info.width()/2.0                    );
		      charge->push_back(       info.charge()                                           );
		      noise->push_back(        info.noiseRescaledByGain()                              );
		      ston->push_back(         info.signalOverNoise()                                  );
		      seedstrip->push_back(    info.maxStrip()                                         );
		      seedindex->push_back(    info.maxIndex()                                         );
		      seedcharge->push_back(   info.maxCharge()                                        );
		      seednoise->push_back(    info.stripNoisesRescaledByGain().at(info.maxIndex())   );
		      seednoisepure->push_back(     info.stripNoises().at(info.maxIndex())                  );
		      seedgain->push_back(     info.stripGains().at(info.maxIndex())                  );
		      qualityisbad->push_back( info.IsAnythingBad()                                    );
	 
      rawchargeC->push_back(   digis.max            );
      rawchargeL->push_back(   digis.left           );
      rawchargeR->push_back(   digis.right          );
      rawchargeLL->push_back(  digis.Lleft          );
      rawchargeRR->push_back(  digis.Rright         );
      etaX->push_back(         digis.etaX()         );
      eta->push_back(          digis.eta()          );
      etaasymm->push_back(     digis.etaasymm()     );
      outsideasymm->push_back( digis.outsideasymm() );
      neweta->push_back(       (digis.last-digis.first)/info.charge() );
      newetaerr->push_back(    (sqrt(digis.last+digis.first))/pow(info.charge(),1.5) );



      detid->push_back(            id                 );
      subdetid->push_back(         moduleV.subdetid      );
      side->push_back(             moduleV.side          );
      module->push_back(           moduleV.module        );
      layerwheel->push_back(       moduleV.layerwheel    );
      stringringrod->push_back(    moduleV.stringringrod );
      petal->push_back(            moduleV.petal         );
      stereo->push_back(           moduleV.stereo        );


      stripLength->push_back(           theStripDet->specificTopology().stripLength() );
      sensorThickness->push_back(             theStripDet->specificSurface().bounds().thickness() );


      uint32_t strips=0;
      std::map<float,int> chargeStrip;
      for( auto itAmpl = cluster_ptr->amplitudes().begin(); itAmpl != cluster_ptr->amplitudes().end(); ++itAmpl){
          stripCharge->push_back(*itAmpl);//@MJ@ 
          stripChargeTotCharge->push_back(info.charge());
          stripChargeTotWidth->push_back(cluster_ptr->amplitudes().size());
          stripChargeStripNr->push_back(info.firstStrip() + strips);
          stripChargeLocalTrackPhi->push_back(  (theStripDet->toLocal(tsos.globalDirection())).phi());
          stripChargeGlobalTrackPhi->push_back(  tsos.globalDirection().phi());
          stripChargeLocalTrackTheta->push_back(  (theStripDet->toLocal(tsos.globalDirection())).theta());
          stripChargeGlobalTrackTheta->push_back(  tsos.globalDirection().theta());
          stripChargeSubdetid->push_back(moduleV.subdetid);
          stripChargeLayerwheel->push_back(moduleV.layerwheel);
          stripChargeDetid->push_back(id); //@MJ@ TODO define
          stripChargeLocalX->push_back((theStripDet->toLocal(tsos.globalPosition())).x());
          stripChargeLocalY->push_back((theStripDet->toLocal(tsos.globalPosition())).y());
          stripChargetrackPt->push_back(   track->pt() );                         
          stripChargelocalpitch->push_back(  (theStripDet->specificTopology()).localPitch(theStripDet->toLocal(tsos.globalPosition())) ); 
          stripChargesensorThickness->push_back(             theStripDet->specificSurface().bounds().thickness() );
	  stripChargeBdotY->push_back(       (theStripDet->surface()).toLocal( magfield->inTesla(theStripDet->surface().position())).y() );
          //h1Cluster_->Fill(info.firstStrip()+strips,*itAmpl);
          //float adcVal = h1Processed_->GetBinContent(info.firstStrip()+strips+2);
          //h1ClusterDiff_->Fill(info.firstStrip()+strips,adcVal-(*itAmpl));

          chargeStrip.insert(make_pair(*itAmpl,info.firstStrip() +strips)) ;

          ++strips; 
      }
      //h1Cluster_->Write();
      //h1ClusterDiff_->Write();

      int baryStrip = chargeStrip.rbegin()->second;
      cout << "barystrip  position" << baryStrip << "value " << chargeStrip.rbegin()->first << endl;

      for(int32_t x=-2; x<3; x++)
      {
          if(isData)
          {
		  if( baryStrip+x < 0 || (int)baryStrip+x > (int) (vRawDigis.size()-1) )
		  {
		      CTstripCharge->push_back(-333);
		      //h1CTCluster_->Fill(baryStrip+x, -333 );
		  }
		  else
		  {
		      CTstripCharge->push_back(vRawDigis.at(baryStrip+x) - vCMN.at(baryStrip+x));
		      //h1CTCluster_->Fill(baryStrip+x, vRawDigis.at(baryStrip+x) - vCMN.at(baryStrip+x) );
		      cout << "strip nr  " << baryStrip+x << " value " << vRawDigis.at(baryStrip+x) - vCMN.at(baryStrip+x) << endl;
		  }
           }
           else
           {
		   bool stripFound = false;
		   for(std::map<float,int>::iterator it=chargeStrip.begin(); it!=chargeStrip.end(); it++)
		   {
		       if(it->second == baryStrip+x)
		       {
			   CTstripCharge->push_back(it->first);
			   stripFound = true;                  
		           cout << " ZS strip nr  " << baryStrip+x << " value " << it->first  << endl;
		       }
		   }
		   if(!stripFound)
                   {
		       CTstripCharge->push_back(-333);
                       
		       cout << " ZS strip nr  " << baryStrip+x << " value " << -333  << endl;
                   }
           }
     
              CTstripChargeLocalTrackPhi->push_back(  (theStripDet->toLocal(tsos.globalDirection())).phi());
              CTstripChargeLocalTrackTheta->push_back(  (theStripDet->toLocal(tsos.globalDirection())).theta());
              CTstripChargeSubdetid->push_back(moduleV.subdetid);
              CTstripChargeLayerwheel->push_back(moduleV.layerwheel);
              CTstripChargelocalpitch->push_back(  (theStripDet->specificTopology()).localPitch(theStripDet->toLocal(tsos.globalPosition())) ); 
              CTstripChargesensorThickness->push_back(             theStripDet->specificSurface().bounds().thickness() );
              CTstripChargeTotCharge->push_back(info.charge());
              CTstripChargeTotWidth->push_back(cluster_ptr->amplitudes().size());

              CTCmbtimeVtxr->push_back(timedt.timeAtIpOutIn());
              CTCmbtimeVtxrErr->push_back(timedt.timeAtIpOutInErr());
              CTDttimeVtxr->push_back(timedt.timeAtIpOutIn());
              CTDttimeVtxrErr->push_back(timedt.timeAtIpOutInErr());
              //CTCsctimeVtxr->push_back(timecsc.timeAtIpOutIn());
              //CTCsctimeVtxrErr->push_back(timecsc.timeAtIpOutInErr());
              CTCsctimeVtxr->push_back(timecsc.timeAtIpOutIn() );
              CTCsctimeVtxrErr->push_back(timecsc.timeAtIpOutInErr()  );

              CTCmbtimeVtx->push_back(timedt.timeAtIpInOut());
              CTCmbtimeVtxErr->push_back(timedt.timeAtIpInOutErr());
              CTDttimeVtx->push_back(timedt.timeAtIpInOut());
              CTDttimeVtxErr->push_back(timedt.timeAtIpInOutErr());
              CTCsctimeVtx->push_back(timecsc.timeAtIpInOut() );
              CTCsctimeVtxErr->push_back(timecsc.timeAtIpInOutErr() );

              CTCombinedTimeOutInInOutDiff->push_back(timedt.timeAtIpOutIn() - timedt.timeAtIpInOut() );
              CTCombinedTimeOutInInOutDiffErr->push_back(timedt.timeAtIpOutInErr() - timedt.timeAtIpInOutErr() );

              CTMuontrackDirection->push_back(trackDirection);
              CTDTMuontrackDirection->push_back(DTtrackDirection);

              CTDTlayer0->push_back(DTlayer0);
              CTDTlayer1->push_back(DTlayer1);
              CTDTlayer2->push_back(DTlayer2);
              CTDTlayer3->push_back(DTlayer3);
              CTDTlayer4->push_back(DTlayer4);
              CTnrOfMuHits->push_back(nrOfMuHits);
              CTsectorsOfDT->push_back(sectorsOfDT.size());

              CTMuonCombinedInverseBeta->push_back(timedt.inverseBeta());
              CTMuonCombinedFreeInverseBeta->push_back(timedt.freeInverseBeta());
              CTDTFreeInverseBeta->push_back(timedt.freeInverseBeta());
              //CTMuontrackPhi->push_back((*glbTrack).phi());

              if(topMu == true)
                  CTMuOrigin->push_back(1);
              else if(bottomMu == true)
                  CTMuOrigin->push_back(2);
              else if(bothMu == true)
                  CTMuOrigin->push_back(3);
              else
                  CTMuOrigin->push_back(4);

              float rescaledCharge =    info.charge()/ (theStripDet->specificSurface().bounds().thickness() / TMath::Abs(TMath::Cos(theStripDet->toLocal(tsos.globalDirection()).theta())) );
              CTstripChargeTotChargeRescaled->push_back( rescaledCharge);
              

              if(outerXtop->size() != 0)
              {
                 CTouterXtop->push_back(outerXtop->at(0));
                 CTouterYtop->push_back( outerYtop->at(0));
                 CTouterZtop->push_back( outerZtop->at(0));
                 CTouterEtatop->push_back(outerEtatop->at(0) );
                 CTmuonsDTMuontrackLastWheel->push_back( muonsDTMuontrackLastWheel->at(0) );
              }
              CTinnerXtop->push_back( track->innerPosition().x());
              CTinnerYtop->push_back( track->innerPosition().y());
              CTinnerZtop->push_back( track->innerPosition().z());
              CTinnerVZtop->push_back( track->vz());
              CTinnerVX->push_back( track->vx());
              CTinnerVY->push_back( track->vy());
              CTEtatop->push_back( track->eta());
              CTglobalX->push_back( tsos.globalPosition().x());
              CTglobalY->push_back( tsos.globalPosition().y());
              CTglobalZ->push_back( tsos.globalPosition().z());


              CTlocalX->push_back( (theStripDet->toLocal(tsos.globalPosition())).x()  );
              CTlocalY->push_back( (theStripDet->toLocal(tsos.globalPosition())).y() );
              CTlocalZ->push_back( (theStripDet->toLocal(tsos.globalPosition())).z() );

              float xterm =  TMath::Power(tsos.globalPosition().x() - track->vx(), 2);
              float yterm =  TMath::Power(tsos.globalPosition().y() - track->vy(), 2);
              float zterm =  TMath::Power(tsos.globalPosition().z() - track->vz(), 2);
              float distance = TMath::Sqrt(xterm + yterm+ zterm  )/ 100.0;
              float timeInSecImproved =  distance/(299792458.0);
              float timeInNsImproved = timeInSecImproved*TMath::Power(10,9);
              

              float radius = TMath::Sqrt( TMath::Power(tsos.globalPosition().x(), 2 ) + TMath::Power(tsos.globalPosition().y(), 2) ) / 100.0;
              float timeInSec =  radius/(299792458.0);
              float timeInNs = timeInSec*TMath::Power(10,9);
 
              //std::cout << " radius " << radius << " time in s " << timeInSec << "time in ns " << timeInNs  << " x-pos " << tsos.globalPosition().x() << " y-pos " << tsos.globalPosition().y() <<  endl;
              CTtof->push_back(timeInNs);
              CTtofImproved->push_back(timeInNsImproved);

		if(theStripDet->toGlobal(hit->localPosition()).phi() > 0)
		{
		    CTCombinedTimeTop->push_back(timedt.timeAtIpOutIn());
		}
		else
		{
		    CTCombinedTimeBottom->push_back(timedt.timeAtIpOutIn());
		}

		if( trackDirection == 1)
		{
		    CTCombinedTimeForInOut->push_back(timedt.timeAtIpInOut());
		}
		else if( trackDirection == -1 )
		{
		    CTCombinedTimeForOutIn->push_back(timedt.timeAtIpOutIn());
		}
		else
		{

		}

      } 
      //h1CTCluster_->Write();



      chargeStrip.clear();
      vCMN.clear();
      vRawDigis.clear();

      //timing



				trackmulti->push_back(  nassociations );
				trackindex->push_back(  trk_idx );
				localtheta->push_back(  (theStripDet->toLocal(tsos.globalDirection())).theta() ); 
				localeta->push_back(  (theStripDet->toLocal(tsos.globalDirection())).eta() ); 
				localphi->push_back(    (theStripDet->toLocal(tsos.globalDirection())).phi() );   
				localpitch->push_back(  (theStripDet->specificTopology()).localPitch(theStripDet->toLocal(tsos.globalPosition())) ); 
				localx->push_back(      (theStripDet->toLocal(tsos.globalPosition())).x() );    
				localy->push_back(      (theStripDet->toLocal(tsos.globalPosition())).y() );    
				localz->push_back(      (theStripDet->toLocal(tsos.globalPosition())).z() );    
				strip->push_back(       (theStripDet->specificTopology()).strip(theStripDet->toLocal(tsos.globalPosition())) );
				globaltheta->push_back( tsos.globalDirection().theta() );                       
				globaleta->push_back( tsos.globalDirection().eta() );                       
				globalphi->push_back(   tsos.globalDirection().phi() );                         
				globalx->push_back(     tsos.globalPosition().x() );                            
				globaly->push_back(     tsos.globalPosition().y() );                            
				globalz->push_back(     tsos.globalPosition().z() );                            
				transverseCurvature->push_back(     tsos.transverseCurvature() );      

                                //cout << "track pt" << track->pt() << endl;                      
                                trackPt->push_back(   track->pt() );                         
                                trackEta->push_back(   track->eta() );                         
				insidistance->push_back(1./fabs(cos(localtheta->at(ontrk_cluster_idx))) );                      
				projwidth->push_back(   tan(localtheta->at(ontrk_cluster_idx))*cos(localphi->at(ontrk_cluster_idx)) );         
				BdotX->push_back(       (theStripDet->surface()).toLocal( magfield->inTesla(theStripDet->surface().position())).x() );
				BdotY->push_back(       (theStripDet->surface()).toLocal( magfield->inTesla(theStripDet->surface().position())).y() );
				BdotZ->push_back(       (theStripDet->surface()).toLocal( magfield->inTesla(theStripDet->surface().position())).z() );
				BdotMag->push_back(       (theStripDet->surface()).toLocal( magfield->inTesla(theStripDet->surface().position())).mag() );
				covered->push_back(     drift.z()/localpitch->at(ontrk_cluster_idx) * fabs(projwidth->at(ontrk_cluster_idx) - drift.x()/drift.z()) );
				rhlocalx->push_back(    hit->localPosition().x() );
				rhlocaly->push_back(    hit->localPosition().y() );
				rhlocalxerr->push_back( sqrt(hit->localPositionError().xx()) );
				rhlocalyerr->push_back( sqrt(hit->localPositionError().yy()) );
				rhglobalx->push_back(   theStripDet->toGlobal(hit->localPosition()).x() );
				rhglobaly->push_back(   theStripDet->toGlobal(hit->localPosition()).y() );
				rhglobalz->push_back(   theStripDet->toGlobal(hit->localPosition()).z() );
				rhglobaltheta->push_back(   theStripDet->toGlobal(hit->localPosition()).theta() );
				rhglobalphi->push_back(   theStripDet->toGlobal(hit->localPosition()).phi() );
				rhstrip->push_back(     theStripDet->specificTopology().strip(hit->localPosition()) );
				rhmerr->push_back(      sqrt(theStripDet->specificTopology().measurementError(hit->localPosition(), hit->localPositionError()).uu()) );
				ubstrip->push_back(     theStripDet->specificTopology().strip(unbiased.localPosition()) );
				ubmerr->push_back(      sqrt(theStripDet->specificTopology().measurementError(unbiased.localPosition(), unbiased.localError().positionError()).uu()) );
				driftx->push_back(      drift.x() );
				drifty->push_back(      drift.y() );
				driftz->push_back(      drift.z() );
				globalZofunitlocalY->push_back( (theStripDet->toGlobal(LocalVector(0,1,0))).z() );


                                //globalMomentum(), transverseCurvature //http://cmsdoxygen.web.cern.ch/cmsdoxygen/CMSSW_9_2_0/doc/html/dc/d78/TrajectoryStateOnSurface_8h_source.html
                                //http://cmsdoxygen.web.cern.ch/cmsdoxygen/CMSSW_9_2_0/doc/html/d6/d85/PV3DBase_8h_source.html
            				
				ontrk_cluster_idx++;
      } //for(unsigned h=0; h<2; h++) { //loop over possible Hit options (1D, 2D)
    } //BOOST_FOREACH( const TrajectoryMeasurement measurement, traj->measurements() )

		onTrkClustersBegin->at(trk_idx) = trk_strt_idx;
		onTrkClustersEnd->at(trk_idx)   = ontrk_cluster_idx;

  } //for(TrajTrackAssociationCollection::const_iterator association = associations->begin();


   //beforePut:
}

}

  iEvent.put(std::move(clusterIdx        ), Suffix + "clusterIdx"  );
  iEvent.put(std::move(onTrkClusterIdx   ), Suffix + "onTrkClusterIdx"  );
  iEvent.put(std::move(onTrkClustersBegin), Suffix + "onTrkClustersBegin"  );
  iEvent.put(std::move(onTrkClustersEnd  ), Suffix + "onTrkClustersEnd"  );
  iEvent.put(std::move(trackindex),  Suffix + "trackindex"   );

  iEvent.put(std::move(trackmulti),  Suffix + "trackmulti"   );
  iEvent.put(std::move(localtheta),  Suffix + "localtheta"   );
  iEvent.put(std::move(localeta),  Suffix + "localeta"   );
  iEvent.put(std::move(localphi),    Suffix + "localphi"     );
  iEvent.put(std::move(localpitch),  Suffix + "localpitch"   );
  iEvent.put(std::move(localx),      Suffix + "localx"       );
  iEvent.put(std::move(localy),      Suffix + "localy"       );
  iEvent.put(std::move(localz),      Suffix + "localz"       );
  iEvent.put(std::move(strip),       Suffix + "strip"        );
  iEvent.put(std::move(globaltheta), Suffix + "globaltheta"  );
  iEvent.put(std::move(globaleta), Suffix + "globaleta"  );
  iEvent.put(std::move(globalphi),   Suffix + "globalphi"    );
  iEvent.put(std::move(globalx),     Suffix + "globalx"      );
  iEvent.put(std::move(globaly),     Suffix + "globaly"      );
  iEvent.put(std::move(globalz),     Suffix + "globalz"      );  
  iEvent.put(std::move(transverseCurvature),     Suffix + "transverseCurvature"      );  
  iEvent.put(std::move(trackPt),     Suffix + "trackPt"      );  
  iEvent.put(std::move(trackEta),     Suffix + "trackEta"      );  
  iEvent.put(std::move(insidistance),Suffix + "insidistance" );
  iEvent.put(std::move(covered),     Suffix + "covered"      );
  iEvent.put(std::move(projwidth),   Suffix + "projwidth"    );
  iEvent.put(std::move(BdotX),       Suffix + "BdotX"        );
  iEvent.put(std::move(BdotY),       Suffix + "BdotY"        );
  iEvent.put(std::move(BdotZ),       Suffix + "BdotZ"        );
  iEvent.put(std::move(BdotMag),       Suffix + "BdotMag"        );
  iEvent.put(std::move(rhlocalx),    Suffix + "rhlocalx"     );   
  iEvent.put(std::move(rhlocaly),    Suffix + "rhlocaly"     );   
  iEvent.put(std::move(rhlocalxerr), Suffix + "rhlocalxerr"  );   
  iEvent.put(std::move(rhlocalyerr), Suffix + "rhlocalyerr"  );   
  iEvent.put(std::move(rhglobalx),   Suffix + "rhglobalx"    );   
  iEvent.put(std::move(rhglobaly),   Suffix + "rhglobaly"    );   
  iEvent.put(std::move(rhglobalz),   Suffix + "rhglobalz"    );   
  iEvent.put(std::move(rhglobalphi),   Suffix + "rhglobalphi"    );   
  iEvent.put(std::move(rhglobaltheta),   Suffix + "rhglobaltheta"    );   
  iEvent.put(std::move(rhstrip),     Suffix + "rhstrip"      );   
  iEvent.put(std::move(rhmerr),      Suffix + "rhmerr"       );   
  iEvent.put(std::move(ubstrip),     Suffix + "ubstrip"      );   
  iEvent.put(std::move(ubmerr),      Suffix + "ubmerr"       );   
  iEvent.put(std::move(driftx),      Suffix + "driftx"       );
  iEvent.put(std::move(drifty),      Suffix + "drifty"       );
  iEvent.put(std::move(driftz),      Suffix + "driftz"       );
  iEvent.put(std::move(globalZofunitlocalY), Suffix + "globalZofunitlocalY"  );


  iEvent.put(std::move(lorentzAngle),      Prefix + "lorentzAngle"       );
  iEvent.put(std::move(number),      Prefix + "number"       );
  iEvent.put(std::move(width),       Prefix + "width"        );
  iEvent.put(std::move(variance),    Prefix + "variance"     );
  iEvent.put(std::move(barystrip),   Prefix + "barystrip"    );
  iEvent.put(std::move(middlestrip), Prefix + "middlestrip"  );
  iEvent.put(std::move(charge),      Prefix + "charge"       );
  iEvent.put(std::move(noise),       Prefix + "noise"        );
  iEvent.put(std::move(ston),        Prefix + "ston"         );
  iEvent.put(std::move(seedstrip),   Prefix + "seedstrip"    );
  iEvent.put(std::move(seedindex),   Prefix + "seedindex"    );
  iEvent.put(std::move(seedcharge),  Prefix + "seedcharge"   );
  iEvent.put(std::move(seednoise),   Prefix + "seednoise"    );
  iEvent.put(std::move(seednoisepure),   Prefix + "seednoisepure"    );
  iEvent.put(std::move(seedgain),    Prefix + "seedgain"     );
  iEvent.put(std::move(qualityisbad),Prefix + "qualityisbad" );

  iEvent.put(std::move(rawchargeC),  Prefix + "rawchargeC"   );
  iEvent.put(std::move(rawchargeL),  Prefix + "rawchargeL"   );
  iEvent.put(std::move(rawchargeR),  Prefix + "rawchargeR"   );
  iEvent.put(std::move(rawchargeLL), Prefix + "rawchargeLL"  );
  iEvent.put(std::move(rawchargeRR), Prefix + "rawchargeRR"  );
  iEvent.put(std::move(etaX),        Prefix + "etaX"         );
  iEvent.put(std::move(eta),         Prefix + "eta"          );
  iEvent.put(std::move(foldedeta),   Prefix + "foldedeta"    );
  iEvent.put(std::move(etaasymm),    Prefix + "etaasymm"     );
  iEvent.put(std::move(outsideasymm),Prefix + "outsideasymm" );
  iEvent.put(std::move(neweta),      Prefix + "neweta"       );
  iEvent.put(std::move(newetaerr),   Prefix + "newetaerr"    );

  iEvent.put(std::move(detid),        Prefix + "detid"         );
  iEvent.put(std::move(subdetid),     Prefix + "subdetid"      );
  iEvent.put(std::move(module),       Prefix + "module"        );
  iEvent.put(std::move(side),         Prefix + "side"          );
  iEvent.put(std::move(layerwheel),   Prefix + "layerwheel"    );
  iEvent.put(std::move(stringringrod),Prefix + "stringringrod" );
  iEvent.put(std::move(petal),        Prefix + "petal"         );
  iEvent.put(std::move(stereo),       Prefix + "stereo"        );
  iEvent.put(std::move(stripLength),       Prefix + "stripLength"        );
  iEvent.put(std::move(sensorThickness),       Prefix + "sensorThickness"        );
  iEvent.put(std::move(stripCharge),       Prefix + "stripCharge"        );
  iEvent.put(std::move(stripChargeTotCharge),       Prefix + "stripChargeTotCharge"        );
  iEvent.put(std::move(stripChargeTotWidth),       Prefix + "stripChargeTotWidth"        );
  iEvent.put(std::move(stripChargeStripNr),       Prefix + "stripChargeStripNr"        );
  iEvent.put(std::move(stripChargeLocalTrackPhi),       Prefix + "stripChargeLocalTrackPhi"        );
  iEvent.put(std::move(stripChargeGlobalTrackPhi),       Prefix + "stripChargeGlobalTrackPhi"        );
  iEvent.put(std::move(stripChargeLocalTrackTheta),       Prefix + "stripChargeLocalTrackTheta"        );
  iEvent.put(std::move(stripChargeGlobalTrackTheta),       Prefix + "stripChargeGlobalTrackTheta"        );
  iEvent.put(std::move(stripChargeSubdetid),     Prefix + "stripChargeSubdetid"      );
  iEvent.put(std::move(stripChargeLayerwheel),   Prefix + "stripChargeLayerwheel"    );
  iEvent.put(std::move(stripChargeDetid),   Prefix + "stripChargeDetid"    );
  iEvent.put(std::move(stripChargeLocalX),   Prefix + "stripChargeLocalX"    );
  iEvent.put(std::move(stripChargeLocalY),   Prefix + "stripChargeLocalY"    );
  iEvent.put(std::move(stripChargetrackPt),   Prefix + "stripChargetrackPt"    );
  iEvent.put(std::move(stripChargelocalpitch),   Prefix + "stripChargelocalpitch"    );
  iEvent.put(std::move(stripChargesensorThickness),   Prefix + "stripChargesensorThickness"    );
  iEvent.put(std::move(stripChargeBdotY),   Prefix + "stripChargeBdotY"    );
  iEvent.put(std::move(CTstripCharge),       "CTstripCharge"        );
  iEvent.put(std::move(CTstripChargeLocalTrackPhi),       "CTstripChargeLocalTrackPhi"        );
  iEvent.put(std::move(CTstripChargeLocalTrackTheta),       "CTstripChargeLocalTrackTheta"        );
  iEvent.put(std::move(CTstripChargeSubdetid),       "CTstripChargeSubdetid"        );
  iEvent.put(std::move(CTstripChargeLayerwheel),       "CTstripChargeLayerwheel"        );
  iEvent.put(std::move(CTstripChargelocalpitch),       "CTstripChargelocalpitch"        );
  iEvent.put(std::move(CTstripChargesensorThickness),       "CTstripChargesensorThickness"        );
  iEvent.put(std::move(CTstripChargeTotCharge),       "CTstripChargeTotCharge"        );
  iEvent.put(std::move(CTstripChargeTotChargeRescaled),       "CTstripChargeTotChargeRescaled"        );
  iEvent.put(std::move(CTstripChargeTotWidth),       "CTstripChargeTotWidth"        );
  iEvent.put(std::move(PU),       "PU"        );
  iEvent.put(std::move(bx),       "bx"        );
  iEvent.put(std::move(run),       "run"        );
  iEvent.put(std::move(nroftracks),       "nroftracks"        );
  iEvent.put(std::move(nrofmuons),       "nrofmuons"        );
  iEvent.put(std::move(nrofevents),       "nrofevents"        );
  iEvent.put(std::move(CTCmbtimeVtxr),       "CTCmbtimeVtxr"        );
  iEvent.put(std::move(CTCmbtimeVtxrErr),       "CTCmbtimeVtxrErr"        );
  iEvent.put(std::move(CTCombinedTimeOutInInOutDiff),       "CTCombinedTimeOutInInOutDiff"        );
  iEvent.put(std::move(CTCombinedTimeOutInInOutDiffErr),       "CTCombinedTimeOutInInOutDiffErr"        );
  iEvent.put(std::move(CTDttimeVtxr),       "CTDttimeVtxr"        );
  iEvent.put(std::move(CTDttimeVtxrErr),       "CTDttimeVtxrErr"        );
  iEvent.put(std::move(CTCsctimeVtxr),       "CTCsctimeVtxr"        );
  iEvent.put(std::move(CTCsctimeVtxrErr),       "CTCsctimeVtxrErr"        );

  iEvent.put(std::move(CTCmbtimeVtx),       "CTCmbtimeVtx"        );
  iEvent.put(std::move(CTCmbtimeVtxErr),       "CTCmbtimeVtxErr"        );
  iEvent.put(std::move(CTDttimeVtx),       "CTDttimeVtx"        );
  iEvent.put(std::move(CTDttimeVtxErr),       "CTDttimeVtxErr"        );
  iEvent.put(std::move(CTCsctimeVtx),       "CTCsctimeVtx"        );
  iEvent.put(std::move(CTCsctimeVtxErr),       "CTCsctimeVtxErr"        );

  iEvent.put(std::move(CTCombinedTimeTop),       "CTCombinedTimeTop"        );
  iEvent.put(std::move(CTCombinedTimeBottom),       "CTCombinedTimeBottom"        );
  iEvent.put(std::move(CTMuontrackDirection),       "CTMuontrackDirection"        );
  iEvent.put(std::move(CTDTMuontrackDirection),       "CTDTMuontrackDirection"        );
  iEvent.put(std::move(CTMuonCombinedInverseBeta),       "CTMuonCombinedInverseBeta"        );
  iEvent.put(std::move(CTMuonCombinedFreeInverseBeta),       "CTMuonCombinedFreeInverseBeta"        );
  iEvent.put(std::move(CTDTFreeInverseBeta),       "CTDTFreeInverseBeta"        );
  //iEvent.put(std::move(CTMuontrackPhi),       "CTMuontrackPhi"        );
  iEvent.put(std::move(CTCombinedTimeForInOut),       "CTCombinedTimeForInOut"        );
  iEvent.put(std::move(CTCombinedTimeForOutIn),       "CTCombinedTimeForOutIn"        );

  iEvent.put(std::move(CTDTlayer0),       "CTDTlayer0"        );
  iEvent.put(std::move(CTDTlayer1),       "CTDTlayer1"        );
  iEvent.put(std::move(CTDTlayer2),       "CTDTlayer2"        );
  iEvent.put(std::move(CTDTlayer3),       "CTDTlayer3"        );
  iEvent.put(std::move(CTDTlayer4),       "CTDTlayer4"        );
  iEvent.put(std::move(CTnrOfMuHits),       "CTnrOfMuHits"        );
  iEvent.put(std::move(CTsectorsOfDT),       "CTsectorsOfDT"        );


  iEvent.put(std::move(CTMuOrigin),       "CTMuOrigin"        );

  iEvent.put(std::move(muonsDTMuontrackDirection),       "muonsDTMuontrackDirection"        );
  iEvent.put(std::move(muonsDTMuontrackSector),       "muonsDTMuontrackSector"        );

  iEvent.put(std::move(muonsDTMuontrackInOut),       "muonsDTMuontrackInOut"        );
  iEvent.put(std::move(muonsDTMuontrackOutIn),       "muonsDTMuontrackOutIn"        );

  iEvent.put(std::move(muonsDTMuontrackInOutTop),       "muonsDTMuontrackInOutTop"        );
  iEvent.put(std::move(muonsDTMuontrackOutInTop),       "muonsDTMuontrackOutInTop"        );
  iEvent.put(std::move(muonsDTMuontrackInOutErrTop),       "muonsDTMuontrackInOutErrTop"        );
  iEvent.put(std::move(muonsDTMuontrackOutInErrTop),       "muonsDTMuontrackOutInErrTop"        );
  iEvent.put(std::move(innerXtop),       "innerXtop"        );
  iEvent.put(std::move(innerYtop),       "innerYtop"        );
  iEvent.put(std::move(innerZtop),       "innerZtop"        );
  iEvent.put(std::move(innerVZtop),       "innerVZtop"        );
  iEvent.put(std::move(innerVX),       "innerVX"        );
  iEvent.put(std::move(innerVY),       "innerVY"        );
  iEvent.put(std::move(Etatop),       "Etatop"        );
  iEvent.put(std::move(outerXtop),       "outerXtop"        );
  iEvent.put(std::move(outerYtop),       "outerYtop"        );
  iEvent.put(std::move(outerZtop),       "outerZtop"        );
  iEvent.put(std::move(outerEtatop),       "outerEtatop"        );
  iEvent.put(std::move(muonsDTMuontrackLastWheel),       "muonsDTMuontrackLastWheel"        );
  iEvent.put(std::move(muonsDTFreeInverseBeta),       "muonsDTFreeInverseBeta"        );


  iEvent.put(std::move(CTouterXtop),       "CTouterXtop"        );
  iEvent.put(std::move(CTouterYtop),       "CTouterYtop"        );
  iEvent.put(std::move(CTouterZtop),       "CTouterZtop"        );
  iEvent.put(std::move(CTouterEtatop),       "CTouterEtatop"        );
  iEvent.put(std::move(CTmuonsDTMuontrackLastWheel),       "CTmuonsDTMuontrackLastWheel"        );
  iEvent.put(std::move(CTinnerXtop),       "CTinnerXtop"        );
  iEvent.put(std::move(CTinnerYtop),       "CTinnerYtop"        );
  iEvent.put(std::move(CTinnerZtop),       "CTinnerZtop"        );
  iEvent.put(std::move(CTinnerVZtop),       "CTinnerVZtop"        );
  iEvent.put(std::move(CTinnerVX),       "CTinnerVX"        );
  iEvent.put(std::move(CTinnerVY),       "CTinnerVY"        );
  iEvent.put(std::move(CTEtatop),       "CTEtatop"        );
  iEvent.put(std::move(CTglobalX),       "CTglobalX"        );
  iEvent.put(std::move(CTglobalY),       "CTglobalY"        );
  iEvent.put(std::move(CTglobalZ),       "CTglobalZ"        );
  iEvent.put(std::move(CTtof),       "CTtof"        );
  iEvent.put(std::move(CTtofImproved),       "CTtofImproved"        );
  iEvent.put(std::move(CTlocalX),       "CTlocalX"        );
  iEvent.put(std::move(CTlocalY),       "CTlocalY"        );
  iEvent.put(std::move(CTlocalZ),       "CTlocalZ"        );

  //just for tests
  iEvent.put(std::move(tzeroMinTimeInOut),       "tzeroMinTimeInOut"        );
  iEvent.put(std::move(tzeroMinTimeOutIn),       "tzeroMinTimeOutIn"        );

  iEvent.put(std::move(muOrigin),       "muOrigin"        );
  iEvent.put(std::move(muTimeDifference),       "muTimeDifference"        );
  iEvent.put(std::move(nrOfMus),       "nrOfMus"        );

  /*iEvent.put(std::move(passHLTL1SingleMu3v1), "passHLTL1SingleMu3v1" ); 
  iEvent.put(std::move(passHLTL1SingleMu5v1), "passHLTL1SingleMu5v1" ); 
  iEvent.put(std::move(passHLTL1SingleMu7v1), "passHLTL1SingleMu7v1" );
  iEvent.put(std::move(passHLTL1SingleMuCosmicsv1), "passHLTL1SingleMuCosmicsv1" );
  iEvent.put(std::move(passHLTL1SingleMuOpenDTv2), "passHLTL1SingleMuOpenDTv2" );
  iEvent.put(std::move(passHLTL1SingleMuOpenv2), "passHLTL1SingleMuOpenv2" );
*/

    //sdRawDigis_.cd();
    
    //delete h1RawDigis_;
    //h1RawDigis_ = NULL;
}

bool ShallowTrackClustersProducerCombinedVR::trackFilter(const reco::Track* trk)
{
  //if (trk->pt() < 0.8) return false;
  //if (trk->p()  < 2.0) return false;
  //cout << "nr of hits on the track " << trk->hitPattern().numberOfValidTrackerHits() << " chi2 " << trk->normalizedChi2() << " pt " << trk->pt() << " p " << trk->p() << endl;
  bool result = true;
  if (trk->hitPattern().numberOfValidTrackerHits()  <= 6) result=false;
  if (trk->normalizedChi2() > 10.0) result=false;
  //check PV compatibility ??
  if(!result)
      cout << "false nr of hits on the track " << trk->hitPattern().numberOfValidTrackerHits() << " chi2 " << trk->normalizedChi2() << endl;
  
  return result;
}


ShallowTrackClustersProducerCombinedVR::NearDigis::
NearDigis(const SiStripClusterInfo& info) {
  max =  info.maxCharge();
  left =           info.maxIndex()    > uint16_t(0)                ? info.stripCharges()[info.maxIndex()-1]      : 0 ;
  Lleft =          info.maxIndex()    > uint16_t(1)                ? info.stripCharges()[info.maxIndex()-2]      : 0 ;
  right=  unsigned(info.maxIndex()+1) < info.stripCharges().size() ? info.stripCharges()[info.maxIndex()+1]      : 0 ;
  Rright= unsigned(info.maxIndex()+2) < info.stripCharges().size() ? info.stripCharges()[info.maxIndex()+2]      : 0 ;
  first = info.stripCharges()[0];
  last =  info.stripCharges()[info.width()-1];
}

ShallowTrackClustersProducerCombinedVR::NearDigis::
NearDigis(const SiStripClusterInfo& info, const edm::DetSetVector<SiStripProcessedRawDigi>& rawProcessedDigis) {
  edm::DetSetVector<SiStripProcessedRawDigi>::const_iterator digiframe = rawProcessedDigis.find(info.detId());
  if( digiframe != rawProcessedDigis.end()) {
    max =                                                            digiframe->data.at(info.maxStrip()).adc()       ;
    left =            info.maxStrip()    > uint16_t(0)             ? digiframe->data.at(info.maxStrip()-1).adc() : 0 ;
    Lleft =           info.maxStrip()    > uint16_t(1)             ? digiframe->data.at(info.maxStrip()-2).adc() : 0 ;
    right =  unsigned(info.maxStrip()+1) < digiframe->data.size()  ? digiframe->data.at(info.maxStrip()+1).adc() : 0 ;
    Rright = unsigned(info.maxStrip()+2) < digiframe->data.size()  ? digiframe->data.at(info.maxStrip()+2).adc() : 0 ;
    first = digiframe->data.at(info.firstStrip()).adc();
    last = digiframe->data.at(info.firstStrip()+info.width() - 1).adc();
  } else {
    *this = NearDigis(info);
  }
}

ShallowTrackClustersProducerCombinedVR::moduleVars::
moduleVars(uint32_t detid, const TrackerTopology* tTopo) {
  SiStripDetId subdet(detid);
  subdetid = subdet.subDetector();
  if( SiStripDetId::TIB == subdetid ) {
    
    module        = tTopo->tibModule(detid); 
    side          = tTopo->tibIsZMinusSide(detid)?-1:1;  
    layerwheel    = tTopo->tibLayer(detid); 
    stringringrod = tTopo->tibString(detid); 
    stereo        = tTopo->tibIsStereo(detid) ? 1 : 0;
  } else
  if( SiStripDetId::TID == subdetid ) {
    
    module        = tTopo->tidModule(detid); 
    side          = tTopo->tidIsZMinusSide(detid)?-1:1;  
    layerwheel    = tTopo->tidWheel(detid); 
    stringringrod = tTopo->tidRing(detid); 
    stereo        = tTopo->tidIsStereo(detid) ? 1 : 0;
  } else
  if( SiStripDetId::TOB == subdetid ) {
    
    module        = tTopo->tobModule(detid); 
    side          = tTopo->tobIsZMinusSide(detid)?-1:1;  
    layerwheel    = tTopo->tobLayer(detid); 
    stringringrod = tTopo->tobRod(detid); 
    stereo        = tTopo->tobIsStereo(detid) ? 1 : 0;
  } else
  if( SiStripDetId::TEC == subdetid ) {
    
    module        = tTopo->tecModule(detid); 
    side          = tTopo->tecIsZMinusSide(detid)?-1:1;  
    layerwheel    = tTopo->tecWheel(detid); 
    stringringrod = tTopo->tecRing(detid); 
    petal         = tTopo->tecPetalNumber(detid); 
    stereo        = tTopo->tecIsStereo(detid) ? 1 : 0;
  } else {
    module = 0;
    side = 0;
    layerwheel=-1;
    stringringrod = -1;
    petal=-1;
  }
}
