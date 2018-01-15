#include "CalibTracker/SiStripCommon/interface/ShallowSimTracksProducer.h"
#include "CalibTracker/SiStripCommon/interface/ShallowTools.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
//#include "DataFormats/RecoCandidate/interface/TrackAssociation.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CommonTools/Utils/interface/TFileDirectory.h"



ShallowSimTracksProducer::ShallowSimTracksProducer(const edm::ParameterSet& conf) 
  : Prefix( conf.getParameter<std::string>("Prefix") ),
    Suffix( conf.getParameter<std::string>("Suffix") ),
    RootFile( conf.getParameter<std::string>("filename") ),
    trackingParticles_token_(consumes<TrackingParticleCollection>(conf.getParameter<edm::InputTag>("TrackingParticles")))
 //   associator_token_( consumes<reco::TrackToTrackingParticleAssociator>(conf.getParameter<edm::InputTag>("Associator"))),
 //   tracks_token_(consumes<edm::View<reco::Track> >(conf.getParameter<edm::InputTag>("Tracks")))
{
  produces <std::vector<unsigned> >     ( Prefix + "multi"      + Suffix );
  produces <std::vector<int> >          ( Prefix + "type"      + Suffix );
  produces <std::vector<float> >        ( Prefix + "charge"    + Suffix );
  produces <std::vector<float> >        ( Prefix + "momentum"  + Suffix );
  produces <std::vector<float> >        ( Prefix + "pt"        + Suffix );
  produces <std::vector<double> >       ( Prefix + "theta"     + Suffix );
  produces <std::vector<double> >       ( Prefix + "phi"       + Suffix );
  produces <std::vector<double> >       ( Prefix + "eta"       + Suffix );
  produces <std::vector<double> >       ( Prefix + "qoverp"    + Suffix );
  //edm::Service<TFileService> fs_;
  modHits = new TProfile( "hitsinmodules", "hitsinmodules", 20000, 0, 20000); //y-range?

   TString file1 = TString(RootFile);

    TFile* f1 = NULL;
    TTree* t1 = NULL;
    f1 = TFile::Open(file1, "overwrite");
    if(f1==NULL)
        throw std::runtime_error("File 1 address not set");

    t1 = dynamic_cast<TTree*>(f1->Get("sEventTree"));

    if(t1==NULL)
         throw std::runtime_error("Tree 1 address not set");


    t1->SetBranchAddress("moduleKeyOUT", &moduleKeyOUT );
    t1->SetBranchAddress("moduleValueOUT", &moduleValueOUT );

   for(uint32_t b=0; b<t1->GetEntries(); b++)
   {
       moduleKeyOUT = 0;
       moduleValueOUT = 0;
       t1->GetEntry(b);
       //get map in loop over event in branch
       if( moduleKeyOUT != 0) //Key = detId
           moduleOrder.insert(pair<uint32_t,uint32_t>(moduleKeyOUT, moduleValueOUT));

   }
   cout << " map size " << moduleOrder.size() << endl;
}


void ShallowSimTracksProducer::
produce(edm::Event& event, const edm::EventSetup& setup) {

  //edm::Handle<edm::View<reco::Track> >                     tracks ;   event.getByToken(tracks_token_, tracks);
  edm::Handle<TrackingParticleCollection>       trackingParticles ;   event.getByToken(trackingParticles_token_, trackingParticles );  
  //edm::Handle<reco::TrackToTrackingParticleAssociator> associator ;   event.getByToken(associator_token_, associator);

  const  std::vector<TrackingParticle> *tpcs = trackingParticles.product();
  

  unsigned size =tpcs->size();
  auto   multi        = std::make_unique<std::vector<unsigned>>(size,    0);
  auto   type         = std::make_unique<std::vector<int>>     (size,    0);
  auto   charge       = std::make_unique<std::vector<float>>   (size,    0);
  auto   momentum     = std::make_unique<std::vector<float>>   (size,   -1);
  auto   pt           = std::make_unique<std::vector<float>>   (size,   -1);
  auto   theta        = std::make_unique<std::vector<double>>  (size,-1000);
  auto   phi          = std::make_unique<std::vector<double>>  (size,-1000);
  auto   eta          = std::make_unique<std::vector<double>>  (size,-1000);
  auto   dxy          = std::make_unique<std::vector<double>>  (size,-1000);
  auto   dsz          = std::make_unique<std::vector<double>>  (size,-1000);
  auto   qoverp       = std::make_unique<std::vector<double>>  (size,-1000);



   std::map< uint32_t, uint32_t > oneEventTracks;
   for (std::map< uint32_t, uint32_t >::iterator it0=moduleOrder.begin(); it0!=moduleOrder.end(); ++it0)
   { 
       cout << "used modules " << it0->first << "its alias " << it0->second <<  endl; 
       oneEventTracks.insert(pair<uint32_t,uint32_t>(it0->second, 0));
   }

   
 // reco::RecoToSimCollection associations = associator->associateRecoToSim( tracks, trackingParticles);
  
  //for( reco::RecoToSimCollection::const_iterator association = associations.begin(); 
  //     association != associations.end(); association++) {
  for( uint32_t i=0; i<tpcs->size(); i++) {

      const TrackingParticle tparticle = tpcs->at(i);
      if(abs(tparticle.pdgId()) < 50)
          continue;


      const std::vector<SimTrack> ttracks = tparticle.g4Tracks();
      std::vector<uint32_t> shits = tparticle.tkHitDetU();

      std::cout<< "pdg " << tparticle.pdgId() << " nr of sim tracks  " << ttracks.size() << " nr of sim hits " << shits.size()  << std::endl;

      for(uint32_t h=0; h<shits.size(); h++)
      {
          std::map<uint32_t,uint32_t>::iterator it = moduleOrder.find( shits.at(h)  );
          if(it != moduleOrder.end() )
          {
              uint32_t moduleValue = it->second;
              cout << "module " << moduleValue << "track " << i << " hit " << h <<  endl; 
              std::map<uint32_t,uint32_t>::iterator it2 = oneEventTracks.find( moduleValue  );
              (it2->second)++;
          }

      }

      multi->at(i) = 1;
      type->at(i)  = tparticle.pdgId();
      charge->at(i)= tparticle.charge();
      momentum->at(i)=tparticle.p() ;
      pt->at(i) = tparticle.pt()    ;
      theta->at(i) = tparticle.theta() ;
      phi->at(i)   = tparticle.phi()   ;
      eta->at(i)   = tparticle.eta()   ;
      qoverp->at(i)= tparticle.charge()/tparticle.p();

    }
  //}
 
  for (std::map< uint32_t, uint32_t >::iterator it3=oneEventTracks.begin(); it3!=oneEventTracks.end(); ++it3)
  {
      cout << "filling into profile x-axis" << it3->first << " y=axis  "<< it3->second << endl;
      modHits->Fill( it3->first, it3->second ); 
  }

  event.put(std::move(multi   ), Prefix + "multi"     + Suffix );
  event.put(std::move(type    ), Prefix + "type"      + Suffix );
  event.put(std::move(charge  ), Prefix + "charge"    + Suffix );
  event.put(std::move(momentum), Prefix + "momentum"  + Suffix );
  event.put(std::move(pt      ), Prefix + "pt"        + Suffix );
  event.put(std::move(theta   ), Prefix + "theta"     + Suffix );
  event.put(std::move(phi     ), Prefix + "phi"       + Suffix );
  event.put(std::move(eta     ), Prefix + "eta"       + Suffix );
  event.put(std::move(qoverp  ), Prefix + "qoverp"    + Suffix );
  
}



void ShallowSimTracksProducer::beginJob( ) 
{


}

void ShallowSimTracksProducer::endJob( ) 
{
    //f1->Close();
    TFile* f2 = NULL;
    f2 = new TFile( (TString)RootFile+"Tracking.root" ,"recreate");
    cout << "f2 " << f2 << endl;
    //f2->Write("hitsinmodules");
    modHits->Write();

}
