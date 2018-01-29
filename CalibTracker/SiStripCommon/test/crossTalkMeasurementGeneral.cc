//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017tests2.root combinatonOfHits bottom muBottom


#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream> 
#include <cmath>
#include <exception>
#include <ctime>
#include <cmath>

#include "TNtuple.h"
#include "TROOT.h"
#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TF1.h"
#include "TF2.h"
#include "TCanvas.h"
#include "TFitResult.h"
#include "TPaveText.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TObject.h"
#include "TObjArray.h"
#include "THStack.h"
#include "TStyle.h"
#include "TROOT.h"
#include "THashList.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TMath.h"
#include "TLegend.h"
#include "TProfile.h"

using namespace std;

int main(int argc, char *argv[]){

 //gStyle->SetOptStat(0);
 //gROOT->ForceStyle();
 
 TH1::SetDefaultSumw2();
    if(argc != 5)
        throw std::runtime_error("Bad number of arguments!");
    
    TString file1 = argv[1];
    TString dir = argv[2];
    TString part = argv[3]; //top/bottom
    TString muTrack = argv[4]; //muTop/muBottom

    float narrowness = 0.5;

    int  hem = 0; 
    if(part == "top")
        hem = 1;
    else if(part == "bottom")
        hem = -1;
    else
        throw std::runtime_error("Incorrect specification top/bottom");

    TFile* f1 = NULL;
    TTree* t1 = NULL;
    f1 = TFile::Open(file1); 
    if(f1==NULL)
        throw std::runtime_error("File 1 address not set");
    t1 = dynamic_cast<TTree*>(f1->Get("testTree/tree"));
    if(t1==NULL)
        throw std::runtime_error("Tree 1 address not set");


       vector<float>* CTstripChargeSubdetid = 0;
       vector<float>* CTstripCharge = 0;
       vector<float>* CTstripChargeLayerwheel = 0;
       //vector<float>* CTstripChargeStripNr = 0;
       vector<float>* CTstripChargeTotWidth = 0;
       vector<float>* CTstripChargeTotCharge = 0;
       vector<float>* CTstripChargeLocalTrackPhi = 0;
       //vector<float>* CTstripChargeGlobalTrackPhi = 0;
       vector<float>* CTstripChargeLocalTrackTheta = 0;
       //vector<float>* CTstripChargeGlobalTrackTheta = 0;
       //vector<unsigned>* CTstripChargeDetid = 0;
       //vector<float>* CTstripChargeLocalX = 0;
       //vector<float>* CTstripChargeLocalY = 0;
       //vector<float>* CTstripChargetrackPt = 0;
       vector<float>* CTstripChargelocalpitch = 0;
       vector<float>* CTstripChargesensorThickness = 0;
       vector<float>* CTCmbtimeVtx = 0;
       vector<float>* CTCmbtimeVtxr = 0;
       vector<float>* CTCmbtimeVtxErr = 0;
       vector<float>* CTCmbtimeVtxrErr = 0;
       vector<float>* CTMuontrackDirection = 0;
       //vector<float>* CTstripChargeBdotY = 0;
       //unsigned int  nroftracks;
       //unsigned int  nrofevents;
       vector<float>* tsosrhglobalphi = 0;
       vector<uint32_t>* clusterdetid = 0;
       vector<float>* CTMuonCombinedFreeInverseBeta = 0;
       vector<uint32_t>* CTnrOfMuHits = 0;
       vector<uint32_t>* CTsectorsOfDT = 0;
       vector<float>* CTstripChargeTotChargeRescaled = 0;
       vector<float>* CTMuOrigin = 0;
       vector<float>* CTtof = 0;



       vector<float> subCTstripChargeSubdetid;
       vector<float> subCTstripCharge;
       vector<float> subCTstripChargeLayerwheel;
       //vector<float> subCTstripChargeStripNr;
       vector<float> subCTstripChargeTotWidth;
       vector<float> subCTstripChargeTotCharge;
       vector<float> subCTstripChargeLocalTrackPhi;
       //vector<float> subCTstripChargeGlobalTrackPhi;
       vector<float> subCTstripChargeLocalTrackTheta;
       //vector<float> subCTstripChargeGlobalTrackTheta;
       //vector<unsigned> subCTstripChargeDetid;
       //vector<float> subCTstripChargeLocalX;
       //vector<float> subCTstripChargeLocalY;
       //vector<float> subCTstripChargetrackPt;
       vector<float> subCTstripChargelocalpitch;
       vector<float> subCTstripChargesensorThickness;
       vector<float> subCTCmbtimeVtx;
       vector<float> subCTCmbtimeVtxr;
       vector<float> subCTCmbtimeVtxErr;
       vector<float> subCTCmbtimeVtxrErr;
       vector<float> subCTMuontrackDirection;
       //vector<float> subCTstripChargeBdotY;
       //vector<unsigned int>  subnroftracks;
       //vector<unsigned int>  subnrofevents;
       vector<float> subtsosrhglobalphi;
       vector<uint32_t> subclusterdetid;
       vector<float>  subCTMuonCombinedFreeInverseBeta ;
       vector<uint32_t> subCTnrOfMuHits;
       vector<uint32_t> subCTsectorsOfDT;
       vector<float>  subCTstripChargeTotChargeRescaled;
       vector<float>  subCTMuOrigin;
       vector<float>  subCTtof;

       vector<float>*  CTinnerXtop = 0; //this is bit unfortunate, it is not top anymore
       vector<float>*  CTinnerYtop = 0;
       vector<float>*  CTinnerZtop = 0;
       vector<float>*  CTinnerVZtop = 0;
       vector<float>*  CTouterXtop = 0;
       vector<float>*  CTouterYtop = 0;
       vector<float>*  CTouterZtop = 0;
       vector<float>*  CTouterEtatop = 0;

       vector<float>  subCTinnerXtop;
       vector<float>  subCTinnerYtop;
       vector<float>  subCTinnerZtop ;
       vector<float>  subCTinnerVZtop ;
       vector<float>  subCTouterXtop;
       vector<float>  subCTouterYtop;
       vector<float>  subCTouterZtop;
       vector<float>  subCTouterEtatop;

       float bx;
       vector<float> bxPerStrip;

       t1->SetBranchAddress("CTstripChargeSubdetid",  &CTstripChargeSubdetid );
       t1->SetBranchAddress("CTstripCharge",  &CTstripCharge );
       t1->SetBranchAddress("CTstripChargeLayerwheel",  &CTstripChargeLayerwheel );
       //t1->SetBranchAddress("CTstripChargeStripNr",  &CTstripChargeStripNr );
       t1->SetBranchAddress("CTstripChargeTotWidth",  &CTstripChargeTotWidth );
       t1->SetBranchAddress("CTstripChargeTotCharge",  &CTstripChargeTotCharge );
       t1->SetBranchAddress("CTstripChargeLocalTrackPhi",  &CTstripChargeLocalTrackPhi );
       //t1->SetBranchAddress("CTstripChargeGlobalTrackPhi",  &CTstripChargeGlobalTrackPhi );
       t1->SetBranchAddress("CTstripChargeLocalTrackTheta",  &CTstripChargeLocalTrackTheta );
       //t1->SetBranchAddress("CTstripChargeGlobalTrackTheta",  &CTstripChargeGlobalTrackTheta );
       //t1->SetBranchAddress("CTstripChargeDetid",  &CTstripChargeDetid );
       //t1->SetBranchAddress("CTstripChargeLocalX",  &CTstripChargeLocalX );
       //t1->SetBranchAddress("CTstripChargeLocalY",  &CTstripChargeLocalY );
       //t1->SetBranchAddress("CTstripChargetrackPt",  &CTstripChargetrackPt );
       t1->SetBranchAddress("CTstripChargelocalpitch",  &CTstripChargelocalpitch );
       t1->SetBranchAddress("CTstripChargesensorThickness",  &CTstripChargesensorThickness );
       t1->SetBranchAddress("CTCmbtimeVtx",  &CTCmbtimeVtx );
       t1->SetBranchAddress("CTCmbtimeVtxr",  &CTCmbtimeVtxr );
       t1->SetBranchAddress("CTCmbtimeVtxErr",  &CTCmbtimeVtxErr );
       t1->SetBranchAddress("CTCmbtimeVtxrErr",  &CTCmbtimeVtxrErr );
       t1->SetBranchAddress("CTMuontrackDirection",  &CTMuontrackDirection );
       //t1->SetBranchAddress("CTstripChargeBdotY",  &CTstripChargeBdotY );
       //t1->SetBranchAddress("nroftracks",  &nroftracks );
       //t1->SetBranchAddress("nrofevents",  &nrofevents );
       t1->SetBranchAddress("tsosrhglobalphi",  &tsosrhglobalphi );
       t1->SetBranchAddress("clusterdetid",  &clusterdetid );
       //t1->SetBranchAddress("bx",  &bx );
       t1->SetBranchAddress("CTMuonCombinedFreeInverseBeta",  &CTMuonCombinedFreeInverseBeta );
       t1->SetBranchAddress("CTnrOfMuHits",  &CTnrOfMuHits );
       t1->SetBranchAddress("CTsectorsOfDT",  &CTsectorsOfDT );

       t1->SetBranchAddress("CTinnerXtop",  &CTinnerXtop );
       t1->SetBranchAddress("CTinnerYtop",  &CTinnerYtop );
       t1->SetBranchAddress("CTinnerZtop",  &CTinnerZtop );
       t1->SetBranchAddress("CTinnerVZtop",  &CTinnerVZtop );
       t1->SetBranchAddress("CTouterXtop",  &CTouterXtop );
       t1->SetBranchAddress("CTouterYtop",  &CTouterYtop );
       t1->SetBranchAddress("CTouterZtop",  &CTouterZtop );
       t1->SetBranchAddress("CTouterEtatop",  &CTouterEtatop );
       t1->SetBranchAddress("CTstripChargeTotChargeRescaled",  &CTstripChargeTotChargeRescaled );
       t1->SetBranchAddress("CTMuOrigin",  &CTMuOrigin );
       t1->SetBranchAddress("CTtof",  &CTtof );

   ///adata always first
    

   uint32_t evCount=0;
   vector<uint32_t> eventCount;
   
   cout << "in here a" << endl;
   Int_t nentries = (Int_t)t1->GetEntries();

   cout << "in here b" << endl;
   ///fill variables from tree 1
   for (Int_t e=0; e<nentries; e++) 
   {
       t1->GetEntry(e);
          
   cout << "in here b1" << endl;
           //per cluster
           //subnroftracks.push_back(nroftracks);
           //subnrofevents.push_back(nrofevents);
           //perstrip
           uint32_t upStrip = CTstripChargeSubdetid->size();
   cout << "in here b2" << endl;
           for(uint32_t k=0; k<upStrip;k++)
           {
               if( true)
               {
                   if(true ) //@MJ@ TODO trigger
                   {
   cout << "in here b3" << endl;
                       subCTstripChargeSubdetid.push_back(CTstripChargeSubdetid->at(k));
                       subCTstripCharge.push_back(CTstripCharge->at(k));
                       subCTstripChargeLayerwheel.push_back(CTstripChargeLayerwheel->at(k));
                       //subCTstripChargeStripNr.push_back(CTstripChargeStripNr->at(k));
                       subCTstripChargeTotWidth.push_back(CTstripChargeTotWidth->at(k));
                       subCTstripChargeTotCharge.push_back(CTstripChargeTotCharge->at(k));
                       subCTstripChargeLocalTrackPhi.push_back(CTstripChargeLocalTrackPhi->at(k));
                       //subCTstripChargeGlobalTrackPhi.push_back(CTstripChargeGlobalTrackPhi->at(k));
                       subCTstripChargeLocalTrackTheta.push_back(CTstripChargeLocalTrackTheta->at(k));
                       //subCTstripChargeGlobalTrackTheta.push_back(CTstripChargeGlobalTrackTheta->at(k));
                       //subCTstripChargeDetid.push_back(CTstripChargeDetid->at(k));
                       //subCTstripChargeLocalX.push_back(CTstripChargeLocalX->at(k));
                       //subCTstripChargeLocalY.push_back(CTstripChargeLocalY->at(k));
                       //subCTstripChargetrackPt.push_back(CTstripChargetrackPt->at(k));
                       subCTstripChargelocalpitch.push_back(CTstripChargelocalpitch->at(k));
                       subCTstripChargesensorThickness.push_back(CTstripChargesensorThickness->at(k));
                       subCTCmbtimeVtx.push_back(CTCmbtimeVtx->at(k));
                       subCTCmbtimeVtxr.push_back(CTCmbtimeVtxr->at(k));
                       subCTCmbtimeVtxErr.push_back(CTCmbtimeVtxErr->at(k));
                       subCTCmbtimeVtxrErr.push_back(CTCmbtimeVtxrErr->at(k));
                       subCTMuontrackDirection.push_back(CTMuontrackDirection->at(k));
                       //subCTstripChargeBdotY.push_back(CTstripChargeBdotY->at(k));
                       //bxPerStrip.push_back(bx);
                       eventCount.push_back(e);
                       subCTMuonCombinedFreeInverseBeta.push_back(CTMuonCombinedFreeInverseBeta->at(k)) ;
                       subCTnrOfMuHits.push_back(CTnrOfMuHits->at(k));
                       subCTsectorsOfDT.push_back(CTsectorsOfDT->at(k));
                       subCTinnerXtop.push_back(CTinnerXtop->at(k));
                       subCTinnerYtop.push_back(CTinnerYtop->at(k));
                       subCTinnerZtop.push_back(CTinnerZtop->at(k));
                       subCTinnerVZtop.push_back(CTinnerVZtop->at(k));
                       subCTouterXtop.push_back(CTouterXtop->at(k));
                       subCTouterYtop.push_back(CTouterYtop->at(k));
                       subCTouterZtop.push_back(CTouterZtop->at(k));
                       subCTouterEtatop.push_back(CTouterEtatop->at(k));

                       subCTstripChargeTotChargeRescaled.push_back(CTstripChargeTotChargeRescaled->at(k));
                       subCTtof.push_back(CTtof->at(k));
                       cout << "in here workaround 1" << endl;
                       //@MJ@ TODO temporary workaround
                       if( (k+2 > CTMuOrigin->size() ) || (CTMuOrigin->size()==0 && k==0) ) //finish this
                       {
                           subCTMuOrigin.push_back(3);
                           cout << "why are you making so many mistakes?! " << endl;
                       }
                       else
                       { 
                           cout << " k " << k << " size " << CTMuOrigin->size()<< endl;
                           subCTMuOrigin.push_back(CTMuOrigin->at(k));
                       }
                       cout << "in here workaround 2" << endl;
                   }
               }
           }
   cout << "in here c 1" << endl;
           
           for(uint32_t j=0; j<tsosrhglobalphi->size() ;j++)//@MJ@ TODO just temporaray
           {
               cout << " size 1 " <<  tsosrhglobalphi->size() << " size 2 " << clusterdetid->size()<< " j " << j << endl;
               subtsosrhglobalphi.push_back(tsosrhglobalphi->at(j));
               subclusterdetid.push_back(clusterdetid->at(j));
           }
   }

   cout << "in here c" << endl;


       //F
       vector<TH1F*> narrowTrackSharing1Data;
       vector<TH1F*> narrowTrackSharing2Data;

       vector<TH1F*> narrowTrackSharing1Data5to5;
       vector<TH1F*> narrowTrackSharing2Data5to5;
       vector<TH1F*> narrowTrackSharing1Datainfto5;
       vector<TH1F*> narrowTrackSharing2Datainfto5;
       vector<TH1F*> narrowTrackSharing1Data25to35;
       vector<TH1F*> narrowTrackSharing2Data25to35;
       vector<TH1F*> narrowTrackSharing1Data35toinf;
       vector<TH1F*> narrowTrackSharing2Data35toinf;
       vector<TH1F*> narrowTrackSharing1Data10to20;
       vector<TH1F*> narrowTrackSharing2Data10to20;


       vector<TH1F*> narrowTrackSharing1DataSmallZ;
       vector<TCanvas*> narrowTrackSharing1DataSmallZCan;

       vector<TH1F*> timingError;
       vector<TCanvas*> timingErrorCan;

       vector<TH1F*> timingDirection;
       vector<TCanvas*> timingDirectionCan;

       vector<TProfile*> width;
       vector<TProfile*> charge;
       vector<TProfile*> chargePerUnit;


       vector<TProfile*> chargeCenter;
       vector<TProfile*> chargeEdge;
       vector<TCanvas*> chargeCenterCan;
       vector<TCanvas*> chargeEdgeCan;
       vector<TH1F*> innerZ;
       vector<TCanvas*> innerZCan;
       vector<TH1F*> innerVZ;
       vector<TCanvas*> innerVZCan;


       vector<TProfile*> timeVsVz;
       vector<TCanvas*> timeVsVzCan;

       vector<TH2F*> vnrOfHitsVsError;
       vector<TH2F*> nrOfSectorsVsError;
       vector<TH2F*> chargeVsFreeInverseBeta;

       vector<TCanvas*> vnrOfHitsVsErrorCan;
       vector<TCanvas*> nrOfSectorsVsErrorCan;
       vector<TCanvas*> chargeVsFreeInverseBetaCan;

       vector<TCanvas*> narrowTrackSharing1DataCan;
       vector<TCanvas*> narrowTrackSharing2DataCan;

       vector<TCanvas*> narrowTrackSharing1Data5to5Can;
       vector<TCanvas*> narrowTrackSharing2Data5to5Can;
       vector<TCanvas*> narrowTrackSharing1Datainfto5Can;
       vector<TCanvas*> narrowTrackSharing2Datainfto5Can;
       vector<TCanvas*> narrowTrackSharing1Data25to35Can;
       vector<TCanvas*> narrowTrackSharing2Data25to35Can;
       vector<TCanvas*> narrowTrackSharing2Data35toinfCan;
       vector<TCanvas*> narrowTrackSharing1Data35toinfCan;
       vector<TCanvas*> narrowTrackSharing1Data10to20Can;
       vector<TCanvas*> narrowTrackSharing2Data10to20Can;

       vector<TCanvas*> widthCan;

       vector<TCanvas*> chargeCan;
       vector<TCanvas*> chargePerUnitCan;

       vector<TProfile*> etaOneaAsVz;
       etaOneaAsVz.resize(20, NULL);
       vector<TCanvas*> etaOneaAsVzCan;
       etaOneaAsVzCan.resize(20, NULL);

       timeVsVz.resize(20, NULL);
       timeVsVzCan.resize(20, NULL);

       vector<TProfile*> etaOneaAsTime;
       etaOneaAsTime.resize(20, NULL);
       vector<TCanvas*> etaOneaAsTimeCan;
       etaOneaAsTimeCan.resize(20, NULL);


       chargeCenter.resize(20, NULL);
       chargeEdge.resize(20, NULL);
       chargeCenterCan.resize(20, NULL);
       chargeEdgeCan.resize(20, NULL);


       innerZ.resize(20, NULL);
       innerZCan.resize(20, NULL);
       innerVZ.resize(20, NULL);
       innerVZCan.resize(20, NULL);


       narrowTrackSharing1Data.resize(20, NULL);
       narrowTrackSharing2Data.resize(20, NULL);
       narrowTrackSharing1DataCan.resize(20, NULL);
       narrowTrackSharing2DataCan.resize(20, NULL);

       narrowTrackSharing1Data5to5.resize(20, NULL);
       narrowTrackSharing2Data5to5.resize(20, NULL);
       narrowTrackSharing1Datainfto5.resize(20, NULL);
       narrowTrackSharing2Datainfto5.resize(20, NULL);
       narrowTrackSharing1Data25to35.resize(20, NULL);
       narrowTrackSharing2Data25to35.resize(20, NULL);
       narrowTrackSharing1Data35toinf.resize(20, NULL);
       narrowTrackSharing2Data35toinf.resize(20, NULL);
       narrowTrackSharing1Data10to20.resize(20, NULL);
       narrowTrackSharing2Data10to20.resize(20, NULL);

       narrowTrackSharing1Data5to5Can.resize(20, NULL);
       narrowTrackSharing2Data5to5Can.resize(20, NULL);
       narrowTrackSharing1Datainfto5Can.resize(20, NULL);
       narrowTrackSharing2Datainfto5Can.resize(20, NULL);
       narrowTrackSharing1Data25to35Can.resize(20, NULL);
       narrowTrackSharing2Data25to35Can.resize(20, NULL);
       narrowTrackSharing1Data35toinfCan.resize(20, NULL);
       narrowTrackSharing2Data35toinfCan.resize(20, NULL);
       narrowTrackSharing1Data10to20Can.resize(20, NULL);
       narrowTrackSharing2Data10to20Can.resize(20, NULL);

       width.resize(20, NULL);
       charge.resize(20, NULL);
       chargePerUnit.resize(20, NULL);
       widthCan.resize(20, NULL);
       chargeCan.resize(20, NULL);
       chargePerUnitCan.resize(20, NULL);


       vnrOfHitsVsError.resize(20, NULL);
       nrOfSectorsVsError.resize(20, NULL);
       chargeVsFreeInverseBeta.resize(20, NULL);

       vnrOfHitsVsErrorCan.resize(20, NULL);
       nrOfSectorsVsErrorCan.resize(20, NULL);
       chargeVsFreeInverseBetaCan.resize(20, NULL);


       timingError.resize(20, NULL);
       timingErrorCan.resize(20, NULL);

       timingDirection.resize(20, NULL);
       timingDirectionCan.resize(20, NULL);



       narrowTrackSharing1DataSmallZ.resize(20, NULL);
       narrowTrackSharing1DataSmallZCan.resize(20, NULL);

       TProfile*  chargeThroughTracker=  new TProfile("chargeThroughTracker", "chargeThroughTracker" , 25, 0, 25, 0, 500 ) ;
       TProfile*  widthThroughTracker=  new TProfile("widthThroughTracker", "widthThroughTracker" , 25, 0, 25, 0, 15 ) ;
       TH1F*  chargeThroughTrackerTIBtop=  new TH1F("chargeThroughTrackerTIBtop", "chargeThroughTrackerTIBtop",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTIBbottom=  new TH1F("chargeThroughTrackerTIBbottom", "chargeThroughTrackerTIBbottom",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTOBtop=  new TH1F("chargeThroughTrackerTOBtop", "chargeThroughTrackerTOBtop",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTOBbottom=  new TH1F("chargeThroughTrackerTOBbottom", "chargeThroughTrackerTOBbottom",  500, 0, 1000 ) ;

       //joint plots for layers
       TProfile*  chargePerUnitLayers =  new TProfile("chargePerUnitLayers", "chargePerUnitLayers" , 200, -100, 100 ) ;
       TProfile*  timeVsVzLayers =  new TProfile("timeVsVzLayers", "timeVsVzLayers" , 30, -150, 150 ) ;
       TCanvas*  chargePerUnitLayersCan =  new TCanvas("chargePerUnitLayers", "chargePerUnitLayers" ) ;
       TCanvas*  timeVsVzLayersCan =  new TCanvas("timeVsVzLayers", "timeVsVzLayers" ) ;

       uint8_t TIDoffset = 3;
       uint8_t TECoffset = 6;

       vector<string> canvases;

       for(uint32_t m = 0; m<subCTstripCharge.size()/5; m++) //@MJ@ TODO nr of clusters in here, correct variables
       {
           int32_t clusterStart = m*5;


           int32_t partPos = -1;
           string  parName;
           uint32_t TOBtop = 7;
           uint32_t TIBtop = 11;
           uint32_t TIBbottom = 10;
           uint32_t TOBbottom = 14;

   cout << "in here d" << endl;
           //is the cluster narrow?           
           if( abs(tan(subCTstripChargeLocalTrackTheta.at(clusterStart))*cos(subCTstripChargeLocalTrackPhi.at(clusterStart))) < narrowness*(subCTstripChargelocalpitch.at(clusterStart)/subCTstripChargesensorThickness.at(clusterStart)) )
           {
   cout << "in here 1" << endl;

               if(subCTstripChargeSubdetid.at(clusterStart) == 3 ) //TIB
               {
                   if(subtsosrhglobalphi.at(m)>0 ) //top
                   {
                       chargeThroughTracker->Fill( TIBtop - subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                       chargeThroughTrackerTIBtop->Fill( subCTstripChargeTotCharge.at(clusterStart));
                       widthThroughTracker->Fill( TIBtop - subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                   }
                   if(subtsosrhglobalphi.at(m)<0  ) //top
                   {
                       chargeThroughTracker->Fill( TIBbottom + subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                       chargeThroughTrackerTIBbottom->Fill( subCTstripChargeTotCharge.at(clusterStart));
                       widthThroughTracker->Fill( TIBbottom + subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                   }

                   if(subCTstripChargeLayerwheel.at(clusterStart)>0 && subCTstripChargeLayerwheel.at(clusterStart)<3)
                   {
                       partPos = 0;
                       parName = "TIB1";
                   }
                   else
                   {
                       partPos = 1;
                       parName = "TIB2";

                   }

               }
               if(subCTstripChargeSubdetid.at(clusterStart) == 5 ) //TOB
               {
                   if(subtsosrhglobalphi.at(m)>0   ) //top
                   {
                       chargeThroughTracker->Fill( TOBtop - subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                       chargeThroughTrackerTOBtop->Fill( subCTstripChargeTotCharge.at(clusterStart));
                       widthThroughTracker->Fill( TOBtop - subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                   }
                   if(subtsosrhglobalphi.at(m)<0  ) //top
                   {
                       chargeThroughTracker->Fill( TOBbottom + subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                       chargeThroughTrackerTOBbottom->Fill( subCTstripChargeTotCharge.at(clusterStart));
                       widthThroughTracker->Fill( TOBbottom + subCTstripChargeLayerwheel.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                   }
                   if(subCTstripChargeLayerwheel.at(clusterStart)>0 && subCTstripChargeLayerwheel.at(clusterStart)<5)
                   {
                       partPos = 2;
                       parName = "TOB2";
                   }
                   else
                   {
                       partPos = 3;
                       parName = "TOB1";
                   }

               }
               if(subCTstripChargeSubdetid.at(clusterStart) == 4 ) //TID
               {
                       //cout << "TID filling bin " << TIDoffset + subCTstripChargeLayerwheel.at(clusterStart) << endl;
                       partPos = TIDoffset + subCTstripChargeLayerwheel.at(clusterStart);
                       parName = "TID"+to_string(partPos);
               }
               if(subCTstripChargeSubdetid.at(clusterStart) == 6 ) //TEC
               {
                       //cout << "TEC filling bin " << TECoffset + subCTstripChargeLayerwheel.at(clusterStart) << " for layer " << subCTstripChargeLayerwheel.at(clusterStart) << endl;
                       partPos = TECoffset + subCTstripChargeLayerwheel.at(clusterStart);
                       parName = "TEC"+to_string(partPos);
               }


   cout << "in here 2" << endl;
                   if(narrowTrackSharing1Data.at(partPos) == NULL)
                   {
                       narrowTrackSharing1Data.at(partPos) = new TH1F( ("narrowTrackSharing1"+ parName).c_str() , ("narrowTrackSharing1"+parName).c_str() , 200, -1, 1 );
                       narrowTrackSharing1DataCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing1"+ parName).c_str() , ("cnarrowTrackSharing1"+parName).c_str()  );
                       canvases.push_back(parName);
   cout << "in here 2.1" << endl;
                   }
                   if(narrowTrackSharing2Data.at(partPos) == NULL)
                   {
                       narrowTrackSharing2Data.at(partPos) = new TH1F( ("narrowTrackSharing2"+ parName).c_str() , ("narrowTrackSharing2"+parName).c_str() , 200, -1, 1 );
                       narrowTrackSharing2DataCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing2"+ parName).c_str() , ("cnarrowTrackSharing2"+parName).c_str());
   cout << "in here 2.2" << endl;
                   }

                   if(width.at(partPos) == NULL)
                   {
		       width.at(partPos) =  new TProfile(("width"+ parName).c_str(), ("width"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;

		       charge.at(partPos)=  new TProfile(("charge"+ parName).c_str(), ("charge"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargePerUnit.at(partPos)=  new TProfile(("chargePerUnit"+ parName).c_str(), ("chargePerUnit"+ parName).c_str() , 200, -100, 100 ) ;

		       etaOneaAsVz.at(partPos) =  new TProfile(("etaOneaAsVz"+ parName).c_str(), ("etaOneaAsVz"+ parName).c_str() , 100, -150, 150, 0, 1000 ) ;
		       etaOneaAsTime.at(partPos) =  new TProfile(("etaOneaAsTime"+ parName).c_str(), ("etaOneaAsTime"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;

		       timeVsVz.at(partPos) =  new TProfile(("timeVsVz"+ parName).c_str(), ("timeVsVz"+ parName).c_str() , 25, -150, 150) ;

   cout << "in here 2.3" << endl;
		       chargeCenter.at(partPos) =  new TProfile(("chargeCenter"+ parName).c_str(), ("chargeCenter"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeEdge.at(partPos) =  new TProfile(("chargeEdge"+ parName).c_str(), ("chargeEdge"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeCenterCan.at(partPos) =   new TCanvas( ("chargeCenterCan"+ parName).c_str(), ("chargeCenterCan"+ parName).c_str()) ;
		       chargeEdgeCan.at(partPos) =   new TCanvas( ("chargeEdgeCan"+ parName).c_str(), ("chargeEdgeCan"+ parName).c_str()) ;

		       innerZ.at(partPos) =  new TH1F(("innerZ"+ parName).c_str(), ("innerZ"+ parName).c_str() , 300, -300, 300 ) ;
		       innerZCan.at(partPos) =   new TCanvas( ("innerZ"+ parName).c_str(), ("innerZ"+ parName).c_str()) ;
		       innerVZ.at(partPos) =  new TH1F(("innerVZ"+ parName).c_str(), ("innerVZ"+ parName).c_str() , 300, -300, 300 ) ;
		       innerVZCan.at(partPos) =   new TCanvas( ("innerVZ"+ parName).c_str(), ("innerVZ"+ parName).c_str()) ;

   cout << "in here 2.4" << endl;
                       vnrOfHitsVsError.at(partPos) = new TH2F( ("vnrOfHitsVsError"+ parName).c_str(),("vnrOfHitsVsError"+ parName).c_str() , 40, 0, 20, 100 , 0, 60);
                       nrOfSectorsVsError.at(partPos) = new TH2F( ("nrOfSectorsVsError"+ parName).c_str(),("nrOfSectorsVsError"+ parName).c_str() , 10, 0, 10, 10 , 0, 10);
                       chargeVsFreeInverseBeta.at(partPos) = new TH2F( ("chargeVsFreeInverseBeta"+ parName).c_str(),("chargeVsFreeInverseBeta"+ parName).c_str() , 60, -20, 20, 100 , 0, 1000);



                       vnrOfHitsVsErrorCan.at(partPos) = new TCanvas( ("vnrOfHitsVsErrorCan"+ parName).c_str(),("vnrOfHitsVsErrorCan"+ parName).c_str());
                       nrOfSectorsVsErrorCan.at(partPos) = new TCanvas( ("nrOfSectorsVsErrorCan"+ parName).c_str(),("nrOfSectorsVsErrorCan"+ parName).c_str() );
                       chargeVsFreeInverseBetaCan.at(partPos) = new TCanvas( ("chargeVsFreeInverseBetaCan"+ parName).c_str(),("chargeVsFreeInverseBetaCan"+ parName).c_str() );


   cout << "in here 2.5" << endl;
		       widthCan.at(partPos) =   new TCanvas( ("width"+ parName).c_str(), ("width"+ parName).c_str()) ;

		       chargeCan.at(partPos)=   new TCanvas( ("charge"+ parName).c_str(), ("charge"+ parName).c_str()) ;
		       chargePerUnitCan.at(partPos)=   new TCanvas( ("chargePerUnit"+ parName).c_str(), ("chargePerUnit"+ parName).c_str()) ;


		       etaOneaAsVzCan.at(partPos) =   new TCanvas( ("etaOneaAsVzCan"+ parName).c_str(), ("etaOneaAsVzCan"+ parName).c_str()) ;
		       etaOneaAsTimeCan.at(partPos) =   new TCanvas( ("etaOneaAsTimeCan"+ parName).c_str(), ("etaOneaAsTimeCan"+ parName).c_str()) ;

   cout << "in here 2.6" << endl;

		       timeVsVzCan.at(partPos) =   new TCanvas( ("timeVsVzCan"+ parName).c_str(), ("timeVsVzCan"+ parName).c_str()) ;

                       timingError.at(partPos) = new TH1F( ("timingError"+ parName).c_str() , ("timingError"+parName).c_str() , 100, -100, 100 );
                       timingErrorCan.at(partPos) = new TCanvas( ("timingError"+ parName).c_str() , ("timingError"+parName).c_str() ) ;
                       

                       timingDirection.at(partPos) = new TH1F( ("timingDirection"+ parName).c_str() , ("timingDirection"+parName).c_str() , 4, -2, 2 );
                       timingDirectionCan.at(partPos) = new TCanvas( ("timingDirection"+ parName).c_str() , ("timingDirection"+parName).c_str() ) ;

   cout << "in here 2.7" << endl;
                       narrowTrackSharing1Data5to5.at(partPos) = new TH1F( ("narrowTrack5to5Sharing1"+ parName).c_str() , ("narrowTrack5to5Sharing1"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing2Data5to5.at(partPos) = new TH1F( ("narrowTrack5to5Sharing2"+ parName).c_str() , ("narrowTrack5to5Sharing2"+parName).c_str() , 200, -1, 1 )  ;
                       narrowTrackSharing1Datainfto5.at(partPos) = new TH1F( ("narrowTrackinfto5Sharing1"+ parName).c_str() , ("narrowTrackinfto5Sharing1"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing2Datainfto5.at(partPos) = new TH1F( ("narrowTrackinfto5Sharing2"+ parName).c_str() , ("narrowTrackinfto5Sharing2"+parName).c_str() , 200, -1, 1 )  ;
                       narrowTrackSharing1Data25to35.at(partPos) = new TH1F( ("narrowTracki25to35Sharing1"+ parName).c_str() , ("narrowTrack25to35Sharing1"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing2Data25to35.at(partPos) = new TH1F( ("narrowTrack25to35Sharing2"+ parName).c_str() , ("narrowTrack25to35Sharing2"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing1Data35toinf.at(partPos) = new TH1F( ("narrowTrack35toinfSharing1"+ parName).c_str() , ("narrowTrack35toinfSharing1"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing2Data35toinf.at(partPos) = new TH1F( ("narrowTrack35toinfSharing2"+ parName).c_str() , ("narrowTrack35toinfSharing2"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing1Data10to20.at(partPos) = new TH1F( ("narrowTrack10to20Sharing1"+ parName).c_str() , ("narrowTrack10to20Sharing1"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing2Data10to20.at(partPos) = new TH1F( ("narrowTrack0to20Sharing2"+ parName).c_str() , ("narrowTrack10to20Sharing2"+parName).c_str() , 200, -1, 1 ) ;

   cout << "in here 2.8" << endl;
                       narrowTrackSharing1Data5to5Can.at(partPos) = new TCanvas( ("narrowTrack5to5Sharing1"+ parName).c_str() , ("narrowTrack5to5Sharing1"+parName).c_str() ) ;
                       narrowTrackSharing2Data5to5Can.at(partPos) = new TCanvas( ("narrowTrack5to5Sharing2"+ parName).c_str() , ("narrowTrack5to5Sharing2"+parName).c_str()  )  ;
                       narrowTrackSharing1Datainfto5Can.at(partPos) = new TCanvas( ("narrowTrackinfto5Sharing1"+ parName).c_str() , ("narrowTrackinfto5Sharing1"+parName).c_str() ) ;
                       narrowTrackSharing2Datainfto5Can.at(partPos) = new TCanvas( ("narrowTrackinfto5Sharing2"+ parName).c_str() , ("narrowTrackinfto5Sharing2"+parName).c_str()  )  ;
                       narrowTrackSharing1Data35toinfCan.at(partPos) = new TCanvas( ("narrowTrack35toinfSharing1"+ parName).c_str() , ("narrowTrack35toinfSharing1"+parName).c_str()  ) ;
                       narrowTrackSharing2Data35toinfCan.at(partPos) = new TCanvas( ("narrowTrack35toinfSharing2"+ parName).c_str() , ("narrowTrack35toinfSharing2"+parName).c_str()  ) ;
                       narrowTrackSharing1Data10to20Can.at(partPos) = new TCanvas( ("narrowTrack10to20Sharing1"+ parName).c_str() , ("narrowTrack10to20Sharing1"+parName).c_str()  ) ;
                       narrowTrackSharing2Data10to20Can.at(partPos) = new TCanvas( ("narrowTrack0to20Sharing2"+ parName).c_str() , ("narrowTrack10to20Sharing2"+parName).c_str()  ) ;
                       narrowTrackSharing1Data25to35Can.at(partPos) = new TCanvas( ("narrowTracki25to35Sharing1"+ parName).c_str() , ("narrowTrack25to35Sharing1"+parName).c_str()  ) ;
                       narrowTrackSharing2Data25to35Can.at(partPos) = new TCanvas( ("narrowTrack25to35Sharing2"+ parName).c_str() , ("narrowTrack25to35Sharing2"+parName).c_str()  ) ;


                       narrowTrackSharing1DataSmallZCan.at(partPos) = new TCanvas( ("narrowlargeerrSmallZSharing1"+ parName).c_str() , ("narrowlargeerrSmallZSharing1"+parName).c_str() ) ;
                       narrowTrackSharing1DataSmallZ.at(partPos) = new TH1F( ("narrowlargeerrSmallZSharing1"+ parName).c_str() , ("narrowlargeerrSmallZSharing1"+parName).c_str() , 200, -1, 1 ) ;
                       cout << "in here f" << endl;
                   }

                   
   cout << "in here 3" << endl;
                   float time = 0;
                   float timeErr = 0;
                   float tofCorr = 0;
                   float zCorr = 0;

                   if(subCTMuOrigin.at(clusterStart) ==1)
                   {
                       time  = subCTCmbtimeVtxr.at(clusterStart); 
                       timeErr  = subCTCmbtimeVtxrErr.at(clusterStart);
                       if( hem == 1 )
                       {
                           tofCorr = 2* subCTtof.at(clusterStart) ;
                           time+=tofCorr;
                           zCorr = (-0.00665253*subCTinnerVZtop.at(clusterStart) )+ ( 0.00036609*TMath::Power(subCTinnerVZtop.at(clusterStart),2)) ;
                           time-=zCorr;
                           //p0                        =      5.03401   +/-   0.0393454   
                           //p1                        =  -0.00665253   +/-   0.000622806 
                           //p2                        =   0.00036609   +/-   9.22906e-06 
                       }
                       else if( hem == -1)
                       {
                           tofCorr = 0 ;
                           zCorr = (-0.00149803*subCTinnerVZtop.at(clusterStart) )+ ( 0.000140307*TMath::Power(subCTinnerVZtop.at(clusterStart),2)) ;
                           time-=zCorr;
                           //p0                        =    0.0838322   +/-   0.0228075   
                           //p1                        =  -0.00149803   +/-   0.000368792 
                           //p2                        =  0.000140307   +/-   5.45244e-06
                       }
                       else
                           throw std::runtime_error("Muon origin unknown 1");
                   }
                   else if(subCTMuOrigin.at(clusterStart) ==2)
                   {
                       time  = subCTCmbtimeVtx.at(clusterStart); 
                       timeErr  = subCTCmbtimeVtxErr.at(clusterStart); 
                       if( hem ==1)
                       {
                           tofCorr = subCTtof.at(clusterStart) ;
                           time+=tofCorr;
                           zCorr = (0.001777738*subCTinnerVZtop.at(clusterStart) )+ (0.000103351*TMath::Power(subCTinnerVZtop.at(clusterStart),2)) ;
                           time-=zCorr;
                           //p0                        =     -3.77326   +/-   0.035138    
                           //p1                        =   0.00177773   +/-   0.000565477 
                           //p2                        =  0.000103351   +/-   7.75679e-06
                       }
                       else if(hem == -1)
                       {
                           tofCorr = 0;
                           zCorr = (0.0055762*subCTinnerVZtop.at(clusterStart) ) ;
                           time-=zCorr;
                           //p0                        =     -6.02424   +/-   0.025917    
                           //p1                        =    0.0055762   +/-   0.000652371
                           //interestingly, it is more pol1, than pol 2
                       }
                       else
                           throw std::runtime_error("Muon origin unknown 1");
                   }
                   else if(subCTMuOrigin.at(clusterStart) ==3)
                   {
                       cout << "not ready for both top and bottom hits ";
                       continue;
                   }
                   else
                       throw std::runtime_error("Muon origin unknown");

                   if( (muTrack == "muTop" && subCTMuOrigin.at(clusterStart) ==1) ||  (muTrack == "muBottom" && subCTMuOrigin.at(clusterStart) ==2) ) //if(subclusterlayerwheel.at(m) == 3)
                   {
		       if(subCTstripCharge.at(clusterStart+1) != -333)
			   narrowTrackSharing1Data.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
		       if(subCTstripCharge.at(clusterStart+3) != -333)
			   narrowTrackSharing1Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
		       if(subCTstripCharge.at(clusterStart) != -333)
			   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
		       if(subCTstripCharge.at(clusterStart+4) != -333)
			   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                       //cout << "partition name " << parName << " event count " << eventCount.at(clusterStart) << "layer " << subCTstripChargeLayerwheel.at(clusterStart) << " detid " << subclusterdetid.at(m) << endl;
                       if( (hem == 1 && subtsosrhglobalphi.at(m)>0 ) || (hem == -1 && subtsosrhglobalphi.at(m)<0 )) //top
                       {
                           timingDirection.at(partPos)->Fill(subCTMuontrackDirection.at(clusterStart));
                           vnrOfHitsVsError.at(partPos)->Fill(timeErr, subCTnrOfMuHits.at(clusterStart));
                           nrOfSectorsVsError.at(partPos)->Fill( timeErr, subCTsectorsOfDT.at(clusterStart));
                           chargeVsFreeInverseBeta.at(partPos)->Fill( subCTMuonCombinedFreeInverseBeta.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart) );
                           width.at(partPos)->Fill(time , subCTstripChargeTotWidth.at(clusterStart));
                           timingError.at(partPos)->Fill(timeErr);

                           charge.at(partPos)->Fill(time, subCTstripChargeTotCharge.at(clusterStart));
                           chargePerUnit.at(partPos)->Fill(time, subCTstripChargeTotChargeRescaled.at(clusterStart));
                           chargePerUnitLayers->Fill(time, subCTstripChargeTotChargeRescaled.at(clusterStart)) ;
                           if(time > -20 && time < 20) //avoid mixing!
                           {
                               timeVsVz.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), time );
                               timeVsVzLayers->Fill(  subCTinnerVZtop.at(clusterStart), time) ;
                           }

                           innerZ.at(partPos)->Fill( subCTinnerZtop.at(clusterStart) );
                           innerVZ.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart) );
                           if(subCTinnerVZtop.at(clusterStart)> -50 && subCTinnerVZtop.at(clusterStart)<50)
                           {
		               chargeCenter.at(partPos)->Fill( time  , subCTstripChargeTotCharge.at(clusterStart) );
                           }
                           if(subCTinnerVZtop.at(clusterStart)< -50 || subCTinnerVZtop.at(clusterStart)>50)
		               chargeEdge.at(partPos)->Fill( time , subCTstripChargeTotCharge.at(clusterStart) ) ;
 
                               if(subCTstripCharge.at(clusterStart+1) != -333)
                               {
                                   if(  time > -20 &&  time< 20)
                                       etaOneaAsVz.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), (float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTinnerVZtop.at(clusterStart)> -20 && subCTinnerVZtop.at(clusterStart)<20)
                                       etaOneaAsTime.at(partPos)->Fill(   time, (float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2)); //@MJ@ attention in out time
                                   if(time>-5 && time<=5)
                                       narrowTrackSharing1Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=25 && time<35)
                                       narrowTrackSharing1Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=10 && time<=20)
                                       narrowTrackSharing1Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if( time<=-5)
                                       narrowTrackSharing1Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=35)
                                       narrowTrackSharing1Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
				   if(subCTinnerVZtop.at(clusterStart)> -50 && subCTinnerVZtop.at(clusterStart)<50)
                                       narrowTrackSharing1DataSmallZ.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
   cout << "in here h" << endl;
                               }
                               if(subCTstripCharge.at(clusterStart+3) != -333)
                               {
                                   if(  time > -20 &&  time< 20)
                                       etaOneaAsVz.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTinnerVZtop.at(clusterStart)> -20 && subCTinnerVZtop.at(clusterStart)<20)
                                       etaOneaAsTime.at(partPos)->Fill(  time, (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));


                                   if( time>-5 && time<=5)
                                       narrowTrackSharing1Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=25 && time<35)
                                       narrowTrackSharing1Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=10 && time<=20)
                                       narrowTrackSharing1Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if( time<=-5)
                                       narrowTrackSharing1Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=35)
                                       narrowTrackSharing1Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
				   if(subCTinnerVZtop.at(clusterStart)> -50 && subCTinnerVZtop.at(clusterStart)<50)
                                       narrowTrackSharing1DataSmallZ.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   }
                               }
                               if(subCTstripCharge.at(clusterStart) != -333)
                               {
                                   if( time>-5 && time<=5)
                                       narrowTrackSharing2Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=25 && time<35)
                                       narrowTrackSharing2Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=10 && time<=20)
                                       narrowTrackSharing2Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if( time<=-5)
                                       narrowTrackSharing2Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=35)
                                       narrowTrackSharing2Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                               }
                               if(subCTstripCharge.at(clusterStart+4) != -333)
                               {
                                   if( time>-5 && time<=5)
                                       narrowTrackSharing2Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=25 && time<35)
                                       narrowTrackSharing2Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=10 && time<=20)
                                       narrowTrackSharing2Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if( time<=-5 )
                                       narrowTrackSharing2Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if( time>=35)
                                       narrowTrackSharing2Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                               }
                       }

                       else
                       {
                           cout << "weird" << endl;
                       }
                 
           }

       }

       TH1F* dummyCTplot = new TH1F("dummyCTplot", "dummyCTplot" , 5, 0, 5 );
       dummyCTplot->SetBinContent(1,1);
       dummyCTplot->SetBinContent(2,2);
       dummyCTplot->SetBinContent(3,3);
       dummyCTplot->SetBinContent(4,2);
       dummyCTplot->SetBinContent(5,1);
       dummyCTplot->SetFillStyle(1001);
       dummyCTplot->SetFillColor(kGray+2);
       dummyCTplot->SetTitle("");
       dummyCTplot->SetMaximum(1.5*(dummyCTplot->GetMaximum()));
       
       

//////////////////////filling
//     
//
       for(uint32_t c= 0; c<canvases.size(); c++ )
       {
           if(narrowTrackSharing1Data.at(c)==NULL || narrowTrackSharing2Data.at(c) == NULL)
               break;

       narrowTrackSharing1Data.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing2Data.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing2Data.at(c)->SetMarkerColor(kBlack);

       narrowTrackSharing1Data.at(c)->SetTitle("");
       narrowTrackSharing2Data.at(c)->SetTitle("");

       narrowTrackSharing1Data.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2Data.at(c)->GetXaxis()->SetTitle("#eta #pm 2");

       narrowTrackSharing1Data.at(c)->SetMaximum(2.0*  narrowTrackSharing1Data.at(c)->GetMaximum());
       narrowTrackSharing2Data.at(c)->SetMaximum(1.5*  narrowTrackSharing2Data.at(c)->GetMaximum());


       narrowTrackSharing1DataCan.at(c)->cd();
       narrowTrackSharing1Data.at(c)->DrawNormalized(""); 
       narrowTrackSharing1DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());


       narrowTrackSharing2DataCan.at(c)->cd();
       narrowTrackSharing2Data.at(c)->DrawNormalized(""); 
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName() + ".root").c_str());
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing1Data5to5.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data5to5.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1DataSmallZ.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1DataSmallZ.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Datainfto5.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Datainfto5.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data25to35.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data25to35.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data35toinf.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data35toinf.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data10to20.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data10to20.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data5to5.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing1DataSmallZ.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2Data5to5.at(c)->GetXaxis()->SetTitle("#eta #pm 2");
       narrowTrackSharing1Datainfto5.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2Datainfto5.at(c)->GetXaxis()->SetTitle("#eta #pm 2");
       narrowTrackSharing1Data25to35.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2Data25to35.at(c)->GetXaxis()->SetTitle("#eta #pm 2");
       narrowTrackSharing1Data35toinf.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2Data35toinf.at(c)->GetXaxis()->SetTitle("#eta #pm 2");
       narrowTrackSharing1Data10to20.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2Data10to20.at(c)->GetXaxis()->SetTitle("#eta #pm 2");
       
       narrowTrackSharing1Data5to5Can.at(c)->cd();
       narrowTrackSharing1Data5to5.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data5to5.at(c)->GetName()+(string)part+(string)muTrack+ (string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data5to5.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing1Datainfto5Can.at(c)->cd();
       narrowTrackSharing1Datainfto5.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Datainfto5.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Datainfto5.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing1Data25to35Can.at(c)->cd();
       narrowTrackSharing1Data25to35.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data25to35.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data25to35.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing1Data35toinfCan.at(c)->cd();
       narrowTrackSharing1Data35toinf.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data35toinf.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data35toinf.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing1Data10to20Can.at(c)->cd();
       narrowTrackSharing1Data10to20.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data10to20.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data10to20.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       
       narrowTrackSharing2Data5to5Can.at(c)->cd();
       narrowTrackSharing2Data5to5.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data5to5.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing2Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data5to5.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing2Datainfto5Can.at(c)->cd();
       narrowTrackSharing2Datainfto5.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Datainfto5.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing2Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Datainfto5.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing2Data25to35Can.at(c)->cd();
       narrowTrackSharing2Data25to35.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data25to35.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing2Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data25to35.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing2Data35toinfCan.at(c)->cd();
       narrowTrackSharing2Data35toinf.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data35toinf.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing2Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data35toinf.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing2Data10to20Can.at(c)->cd();
       narrowTrackSharing2Data10to20.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data10to20.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing2Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data10to20.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       narrowTrackSharing2DataCan.at(c)->cd();
       narrowTrackSharing2Data.at(c)->DrawNormalized(""); 
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName() + ".root").c_str());
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       
       widthCan.at(c)->cd();
       width.at(c)->GetXaxis()->SetTitle("time");
       width.at(c)->GetYaxis()->SetTitle("cluster width");
       width.at(c)->Draw("");
       widthCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ width.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       widthCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ width.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       chargeCan.at(c)->cd();
       charge.at(c)->GetXaxis()->SetTitle("time");
       charge.at(c)->GetYaxis()->SetTitle("cluster charge");
       charge.at(c)->Draw("");
       chargeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ charge.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       chargeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ charge.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       chargePerUnitCan.at(c)->cd();
       chargePerUnit.at(c)->GetXaxis()->SetTitle("time");
       chargePerUnit.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargePerUnit.at(c)->Draw("");
       chargePerUnitCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnit.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       chargePerUnitCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnit.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       timingErrorCan.at(c)->cd();
       timingError.at(c)->GetXaxis()->SetTitle("time");
       timingError.at(c)->SetTitle("");
       timingError.at(c)->DrawNormalized("hist"); 
       timingErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingError.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timingErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingError.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       timingDirectionCan.at(c)->cd();
       timingDirection.at(c)->GetXaxis()->SetTitle("direction");
       timingDirection.at(c)->SetTitle("");
       timingDirection.at(c)->Draw("hist"); 
       timingDirectionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingDirection.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timingDirectionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingDirection.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());


       TCanvas* cvs = new TCanvas("chargeThroughTrackerc", "chargeThroughTrackerc");
       chargeThroughTracker->GetXaxis()->SetTitle("layer from top to bottom");
       chargeThroughTracker->SetTitle("");
       chargeThroughTracker->Draw("hist e"); 
       cvs->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTracker"+ ".root").c_str());
       cvs->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTracker" + ".eps").c_str());

       TCanvas* cvs2 = new TCanvas("widthThroughTrackerc", "widthThroughTrackerc");
       widthThroughTracker->GetXaxis()->SetTitle("layer from top to bottom");
       widthThroughTracker->SetTitle("");
       widthThroughTracker->Draw("hist e"); 
       cvs2->SaveAs(("output/"+(string)dir+"/"+ "widthThroughTracker"+ ".root").c_str());
       cvs2->SaveAs(("output/"+(string)dir+"/"+ "widthThroughTracker" + ".eps").c_str());


       TCanvas* ch1 = new TCanvas("chargeThroughTrackerTOBbottom", "chargeThroughTrackerTOBbottom");
       chargeThroughTrackerTOBbottom->GetXaxis()->SetTitle("cluster charge");
       chargeThroughTrackerTOBbottom->SetTitle("");
       chargeThroughTrackerTOBbottom->Draw("hist e"); 
       ch1->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTOBbottom"+ ".root").c_str());
       ch1->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTOBbottom" + ".eps").c_str());

       TCanvas* ch2 = new TCanvas("chargeThroughTrackerTOBtop", "chargeThroughTrackerTOBtop");
       chargeThroughTrackerTOBtop->GetXaxis()->SetTitle("cluster charge");
       chargeThroughTrackerTOBtop->SetTitle("");
       chargeThroughTrackerTOBtop->Draw("hist e"); 
       ch2->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTOBtop"+ ".root").c_str());
       ch2->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTOBtop" + ".eps").c_str());


       TCanvas* ch3 = new TCanvas("chargeThroughTrackerTIBtop", "chargeThroughTrackerTIBtop");
       chargeThroughTrackerTIBtop->GetXaxis()->SetTitle("cluster charge");
       chargeThroughTrackerTIBtop->SetTitle("");
       chargeThroughTrackerTIBtop->Draw("hist e"); 
       ch3->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTIBtop"+ ".root").c_str());
       ch3->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTIBtop" + ".eps").c_str());


       TCanvas* ch4 = new TCanvas("chargeThroughTrackerTIBbottom", "chargeThroughTrackerTIBbottom");
       chargeThroughTrackerTIBbottom->GetXaxis()->SetTitle("cluster charge");
       chargeThroughTrackerTIBbottom->SetTitle("");
       chargeThroughTrackerTIBbottom->Draw("hist e"); 
       ch4->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTIBbottom"+ ".root").c_str());
       ch4->SaveAs(("output/"+(string)dir+"/"+ "chargeThroughTrackerTIBbottom" + ".eps").c_str());

       vnrOfHitsVsErrorCan.at(c)->cd();
       vnrOfHitsVsError.at(c)->GetXaxis()->SetTitle(" error");
       vnrOfHitsVsError.at(c)->GetYaxis()->SetTitle("nr of Muon hits");
       vnrOfHitsVsError.at(c)->SetTitle("");
       vnrOfHitsVsError.at(c)->Draw("colz"); 
       vnrOfHitsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ vnrOfHitsVsError.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       vnrOfHitsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ vnrOfHitsVsError.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       nrOfSectorsVsErrorCan.at(c)->cd();
       nrOfSectorsVsError.at(c)->GetXaxis()->SetTitle(" error");
       nrOfSectorsVsError.at(c)->GetYaxis()->SetTitle("nr of hitted Muon sectors");
       nrOfSectorsVsError.at(c)->SetTitle("");
       nrOfSectorsVsError.at(c)->Draw("colz"); 
       nrOfSectorsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nrOfSectorsVsError.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       nrOfSectorsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nrOfSectorsVsError.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       chargeVsFreeInverseBetaCan.at(c)->cd();
       chargeVsFreeInverseBeta.at(c)->GetXaxis()->SetTitle("free inverse beta");
       chargeVsFreeInverseBeta.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeVsFreeInverseBeta.at(c)->SetTitle("");
       chargeVsFreeInverseBeta.at(c)->Draw("colz"); 
       chargeVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsFreeInverseBeta.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       chargeVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsFreeInverseBeta.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());



       narrowTrackSharing1DataSmallZCan.at(c)->cd();
       narrowTrackSharing1DataSmallZ.at(c)->DrawNormalized(""); 
       narrowTrackSharing1DataSmallZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataSmallZ.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1DataSmallZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataSmallZ.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       etaOneaAsVzCan.at(c)->cd();
       etaOneaAsVz.at(c)->GetXaxis()->SetTitle("vz");
       etaOneaAsVz.at(c)->GetYaxis()->SetTitle("eta #pm 1");
       etaOneaAsVz.at(c)->Draw("");
       etaOneaAsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


       timeVsVzCan.at(c)->cd();
       timeVsVz.at(c)->GetXaxis()->SetTitle("vz");
       timeVsVz.at(c)->GetYaxis()->SetTitle("time");
       timeVsVz.at(c)->Draw("");
       timeVsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       timeVsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       etaOneaAsTimeCan.at(c)->cd();
       etaOneaAsTime.at(c)->GetXaxis()->SetTitle("inOut");
       etaOneaAsTime.at(c)->GetYaxis()->SetTitle("eta #pm 1");
       etaOneaAsTime.at(c)->Draw("");
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


/*           TF1 *fb = new TF1("fb","TMath::Landau(x,[0],[1],0)",0,1000);
           fb->SetParameters(130,21);
	   chargeVsLE.at(c)->FitSlicesY(fb);
	   chargeVsLE_1.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsLE.at(c)->GetName()+(string)part+(string)muTrack+ "_0").c_str());
	   chargeVsLE_2.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsLE.at(c)->GetName()+(string)part+(string)muTrack+ "_1").c_str());
	   //chargeVsLE_3.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsLE.at(c)->GetName()+(string)part+(string)muTrack+ "_2").c_str());
*/

       chargeCenterCan.at(c)->cd();
       chargeCenter.at(c)->GetXaxis()->SetTitle("outIn time");
       chargeCenter.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeCenter.at(c)->SetTitle("");
       chargeCenter.at(c)->SetLineColor(kBlue);
       chargeEdge.at(c)->SetLineColor(kRed);
       chargeCenter.at(c)->Draw(""); 
       //chargeEdge.at(c)->Draw("same"); 
       chargeCenterCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeCenter.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       chargeCenterCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeCenter.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());


       innerZCan.at(c)->cd();
       innerZ.at(c)->GetXaxis()->SetTitle("z");
       innerZ.at(c)->SetTitle("");
       innerZ.at(c)->Draw("hist"); 
       innerZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerZ.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       innerZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerZ.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       innerVZCan.at(c)->cd();
       innerVZ.at(c)->GetXaxis()->SetTitle("vz");
       innerVZ.at(c)->SetTitle("");
       innerVZ.at(c)->Draw("hist"); 
       innerVZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVZ.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       innerVZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVZ.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());


       }


      /////////////////////////////////////////////////////


       TCanvas c35("dummyCTplot","dummyCTplot");
       dummyCTplot->Draw("hist"); 
       c35.SaveAs(("output/"+(string)dir+"/"+  "dummyCTplot.root").c_str());
       c35.SaveAs(("output/"+(string)dir+"/"+  "dummyCTplot.eps").c_str());

       timeVsVzLayersCan->cd();
       timeVsVzLayers->GetXaxis()->SetTitle("time");
       timeVsVzLayers->GetYaxis()->SetTitle(" rescaled cluster charge");
       timeVsVzLayers->SetTitle("");
       timeVsVzLayers->Draw(""); 
       timeVsVzLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVzLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timeVsVzLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVzLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       chargePerUnitLayersCan->cd();
       chargePerUnitLayers->GetXaxis()->SetTitle("time");
       chargePerUnitLayers->GetYaxis()->SetTitle(" rescaled cluster charge");
       chargePerUnitLayers->SetTitle("");
       chargePerUnitLayers->Draw(""); 
       chargePerUnitLayersCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       chargePerUnitLayersCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

    //cout << "in here 7"  << endl;

   return 0;
}
