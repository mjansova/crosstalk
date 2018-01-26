//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRdigis.root crossTalkMeasurement //small stats
//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRNewClusteringTimingTestFULL.root crossTalkMeasurement
//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRNewClusteringTimingTest.root crossTalkMeasurement
//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRNewClusteringTimingTestOnlyGlobalTracks.root crossTalkMeasurement
//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRNewClusteringTimingTestOnlyGlobalTracks.root crossTalkMeasurementNar0.1
//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRNewClusteringTimingMuonTimingTests3.root crossTalkMeasurementPrecise
//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRNewClusteringTimingMuonTimingTestsZOffsetPlusCT.root crossTalkMeasurementPrecise
//./crossTalkMeasurement test_shallowTrackCRUZET_2017VRNewClusteringTimingMuonTimingTestsZOffsetPlusCTvzPlusEta.root crossTalkMeasurementPrecise
//./crossTalkMeasurement test_shallowTrackCRUZET_2017testCorrectMuonTiming.root crossTalkMeasurementBetterTiming
//./crossTalkMeasurement test_shallowTrackCRUZET_2017ZSampl.root crossTalkMeasurementZS
//./crossTalkMeasurement test_shallowTrackCRUZET_2017testCorrectMuonTimingTopBot.root newTimingAllHits
//./crossTalkMeasurement test_shallowTrackCRUZET_2017testCorrectMuonTimingBottomOnly.root newTimingBottomHits
//ttomHits


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
    if(argc != 3)
        throw std::runtime_error("Bad number of arguments!");
    
    TString file1 = argv[1];
    TString dir = argv[2];
//    TString part = argv[3]; //top/bottom

    float narrowness = 0.5;


/*    if(subDet == "TIB")
        sdId = 3;
    else if(subDet == "TID")
        sdId = 4;
    else if(subDet == "TOB")
        sdId = 5;
    else if(subDet == "TEC")
        sdId = 6;
    else
        throw std::runtime_error("Wrong partition entered");
*/
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

       vector<float>*  CTinnerXtop = 0;
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
          
           //per cluster
           //subnroftracks.push_back(nroftracks);
           //subnrofevents.push_back(nrofevents);
           //perstrip
           uint32_t upStrip = CTstripChargeSubdetid->size();
           for(uint32_t k=0; k<upStrip;k++)
           {
               if( true)
               {
                   if(true ) //@MJ@ TODO trigger
                   {
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

                   }
               }
           }
           for(uint32_t j=0; j<tsosrhglobalphi->size() ;j++)//@MJ@ TODO just temporaray
           {
               subtsosrhglobalphi.push_back(tsosrhglobalphi->at(j));
               subclusterdetid.push_back(clusterdetid->at(j));
           }
   }

   cout << "in here c" << endl;


       //F
       vector<TH1F*> narrowTrackSharing1Data;
       vector<TH1F*> narrowTrackSharing2Data;
       vector<TH1F*> narrowTrackSharing1DataBot;
       vector<TH1F*> narrowTrackSharing2DataBot;

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

       vector<TH1F*> narrowTrackSharing1DataSmallError;
       vector<TH1F*> narrowTrackSharing1DataLargeError;
       vector<TCanvas*> narrowTrackSharing1DataSmallErrorCan;
       vector<TCanvas*> narrowTrackSharing1DataLargeErrorCan;

       vector<TH1F*> narrowTrackSharing1DataLargeErrorSmallZ;
       vector<TCanvas*> narrowTrackSharing1DataLargeErrorSmallZCan;

       vector<TH1F*> timingErrorTop;
       vector<TH1F*> timingErrorTopInOut;
       vector<TCanvas*> timingErrorTopCan;
       vector<TCanvas*> timingErrorTopInOutCan;

       vector<TH1F*> timingDirectionTop;
       vector<TH1F*> timingDirectionTopInOut;
       vector<TCanvas*> timingDirectionTopCan;
       vector<TCanvas*> timingDirectionTopInOutCan;

       vector<TProfile*> widthTopInOutOnly;
       vector<TProfile*> widthBottomInOutOnly;
       vector<TProfile*> widthTopOutIn;
       vector<TProfile*> widthBottomOutIn;

       vector<TProfile*> chargeTopInOutOnly;
       vector<TProfile*> chargeBottomInOutOnly;
       vector<TProfile*> chargeTopOutIn;
       vector<TProfile*> chargeBottomOutIn;


       vector<TProfile*> chargeCenterOutIn;
       vector<TProfile*> chargeBottomCenterInOut;
       vector<TCanvas*> chargeBottomCenterInOutCan;
       vector<TProfile*> chargeEdgeOutIn;
       vector<TCanvas*> chargeCenterOutInCan;
       vector<TCanvas*> chargeEdgeOutInCan;
       vector<TH1F*> innerZ;
       vector<TCanvas*> innerZCan;
       vector<TH1F*> innerVZ;
       vector<TCanvas*> innerVZCan;


       vector<TH2F*> vnrOfHitsVsError;
       vector<TH2F*> nrOfSectorsVsError;
       vector<TH2F*> chargeVsFreeInverseBeta;
       vector<TH2F*> chargeVsOutIn;
       vector<TH2F*> chargeVsOutInErr;
       vector<TH2F*> chargeVsOutInLE;
       vector<TH2F*> chargeVsOutInErrLE;
       vector<TH2F*> outInErrVsFreeInverseBeta;
       vector<TH2F*> outInErrVsOutIn;
       vector<TH2F*> outInVsFreeInverseBeta;


       vector<TH2F*> timeVsVz210ADC;
       vector<TProfile*> timeVsVz210ADCLow;
       vector<TProfile*> timeVsVz210ADCHigh;

       vector<TCanvas*> vnrOfHitsVsErrorCan;
       vector<TCanvas*> nrOfSectorsVsErrorCan;
       vector<TCanvas*> chargeVsFreeInverseBetaCan;
       vector<TCanvas*> chargeVsOutInCan;
       vector<TCanvas*> chargeVsOutInErrCan;
       vector<TCanvas*> chargeVsOutInCanLE;
       vector<TCanvas*> chargeVsOutInErrCanLE;
       vector<TCanvas*> outInErrVsFreeInverseBetaCan;
       vector<TCanvas*> outInErrVsOutInCan;
       vector<TCanvas*> outInVsFreeInverseBetaCan;


       vector<TCanvas*> timeVsVz210ADCCan;
       vector<TCanvas*> timeVsVz210ADCCanLow;
       vector<TCanvas*> timeVsVz210ADCCanHigh;

       vector<TH1D*> chargeVsOutInLE_1;
       vector<TH1D*> chargeVsOutInLE_2;
       vector<TH1D*> chargeVsOutInLE_3;
       vector<TCanvas*> chargeVsOutInLE_1Can;
       vector<TCanvas*> chargeVsOutInLE_2Can;
       vector<TCanvas*> chargeVsOutInLE_3Can;

       vector<TCanvas*> narrowTrackSharing1DataCan;
       vector<TCanvas*> narrowTrackSharing2DataCan;
       vector<TCanvas*> narrowTrackSharing1DataBotCan;
       vector<TCanvas*> narrowTrackSharing2DataBotCan;

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

       vector<TCanvas*> widthTopInOutOnlyCan;
       vector<TCanvas*> widthBottomInOutOnlyCan;
       vector<TCanvas*> widthTopOutInCan;
       vector<TCanvas*> widthBottomOutInCan;

       vector<TCanvas*> chargeTopInOutOnlyCan;
       vector<TCanvas*> chargeBottomInOutOnlyCan;
       vector<TCanvas*> chargeTopOutInCan;
       vector<TCanvas*> chargeBottomOutInCan;


       vector<TProfile*> widthTopOutInOnly;
       vector<TProfile*> widthBottomOutInOnly;
       vector<TProfile*> chargeTopOutInOnly;
       vector<TProfile*> chargeBottomOutInOnly;
       vector<TCanvas*> widthTopOutInOnlyCan;
       vector<TCanvas*> widthBottomOutInOnlyCan;
       vector<TCanvas*> chargeTopOutInOnlyCan;
       vector<TCanvas*> chargeBottomOutInOnlyCan;

       vector<TProfile*> chargeTopOutInOnlySE;
       vector<TCanvas*> chargeTopOutInOnlyCanSE;
       vector<TProfile*> chargeTopOutInOnlyLE;
       vector<TCanvas*> chargeTopOutInOnlyCanLE;
       chargeTopOutInOnlySE.resize(20, NULL);
       chargeTopOutInOnlyLE.resize(20, NULL);
       chargeTopOutInOnlyCanSE.resize(20, NULL);
       chargeTopOutInOnlyCanLE.resize(20, NULL);


       vector<TProfile*> etaOneaAsVzTop;
       etaOneaAsVzTop.resize(20, NULL);
       vector<TCanvas*> etaOneaAsVzTopCan;
       etaOneaAsVzTopCan.resize(20, NULL);

       vector<TProfile*> etaOneaAsTimeTop;
       etaOneaAsTimeTop.resize(20, NULL);
       vector<TCanvas*> etaOneaAsTimeTopCan;
       etaOneaAsTimeTopCan.resize(20, NULL);

       vector<TProfile*> etaOneaAsVzBot;
       etaOneaAsVzBot.resize(20, NULL);
       vector<TCanvas*> etaOneaAsVzBotCan;
       etaOneaAsVzBotCan.resize(20, NULL);

       vector<TProfile*> etaOneaAsTimeBot;
       etaOneaAsTimeBot.resize(20, NULL);
       vector<TCanvas*> etaOneaAsTimeBotCan;
       etaOneaAsTimeBotCan.resize(20, NULL);



       chargeCenterOutIn.resize(20, NULL);
       chargeEdgeOutIn.resize(20, NULL);
       chargeCenterOutInCan.resize(20, NULL);
       chargeEdgeOutInCan.resize(20, NULL);

       chargeBottomCenterInOut.resize(20, NULL);
       chargeBottomCenterInOutCan.resize(20, NULL);

       innerZ.resize(20, NULL);
       innerZCan.resize(20, NULL);
       innerVZ.resize(20, NULL);
       innerVZCan.resize(20, NULL);


       narrowTrackSharing1Data.resize(20, NULL);
       narrowTrackSharing2Data.resize(20, NULL);
       narrowTrackSharing1DataCan.resize(20, NULL);
       narrowTrackSharing2DataCan.resize(20, NULL);

       narrowTrackSharing1DataBot.resize(20, NULL);
       narrowTrackSharing2DataBot.resize(20, NULL);
       narrowTrackSharing1DataBotCan.resize(20, NULL);
       narrowTrackSharing2DataBotCan.resize(20, NULL);


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

       widthTopInOutOnly.resize(20, NULL);
       widthBottomInOutOnly.resize(20, NULL);
       widthTopOutInOnly.resize(20, NULL);
       widthBottomOutInOnly.resize(20, NULL);
       widthTopOutIn.resize(20, NULL);
       widthBottomOutIn.resize(20, NULL);

       chargeTopInOutOnly.resize(20, NULL);
       chargeBottomInOutOnly.resize(20, NULL);
       chargeTopOutInOnly.resize(20, NULL);
       chargeBottomOutInOnly.resize(20, NULL);
       chargeTopOutIn.resize(20, NULL);
       chargeBottomOutIn.resize(20, NULL);


       widthTopInOutOnlyCan.resize(20, NULL);
       widthBottomInOutOnlyCan.resize(20, NULL);
       widthTopOutInOnlyCan.resize(20, NULL);
       widthBottomOutInOnlyCan.resize(20, NULL);
       widthTopOutInCan.resize(20, NULL);
       widthBottomOutInCan.resize(20, NULL);

       chargeTopInOutOnlyCan.resize(20, NULL);
       chargeBottomInOutOnlyCan.resize(20, NULL);
       chargeTopOutInOnlyCan.resize(20, NULL);
       chargeBottomOutInOnlyCan.resize(20, NULL);
       chargeTopOutInCan.resize(20, NULL);
       chargeBottomOutInCan.resize(20, NULL);


       vnrOfHitsVsError.resize(20, NULL);
       nrOfSectorsVsError.resize(20, NULL);
       chargeVsFreeInverseBeta.resize(20, NULL);
       chargeVsOutIn.resize(20, NULL);
       chargeVsOutInErr.resize(20, NULL);
       chargeVsOutInLE.resize(20, NULL);
       chargeVsOutInErrLE.resize(20, NULL);
       outInErrVsFreeInverseBeta.resize(20, NULL);
       outInErrVsOutIn.resize(20, NULL);
       outInVsFreeInverseBeta.resize(20, NULL);
       timeVsVz210ADC.resize(20, NULL);
       timeVsVz210ADCLow.resize(20, NULL);
       timeVsVz210ADCHigh.resize(20, NULL);
       vnrOfHitsVsErrorCan.resize(20, NULL);
       nrOfSectorsVsErrorCan.resize(20, NULL);
       chargeVsFreeInverseBetaCan.resize(20, NULL);
       chargeVsOutInCan.resize(20, NULL);
       chargeVsOutInErrCan.resize(20, NULL);
       chargeVsOutInCanLE.resize(20, NULL);
       chargeVsOutInErrCanLE.resize(20, NULL);
       outInErrVsFreeInverseBetaCan.resize(20, NULL);
       outInErrVsOutInCan.resize(20, NULL);
       outInVsFreeInverseBetaCan.resize(20, NULL);
       timeVsVz210ADCCan.resize(20, NULL);
       timeVsVz210ADCCanLow.resize(20, NULL);
       timeVsVz210ADCCanHigh.resize(20, NULL);


       chargeVsOutInLE_1.resize(20, NULL);
       chargeVsOutInLE_2.resize(20, NULL);
       chargeVsOutInLE_3.resize(20, NULL);
       chargeVsOutInLE_1Can.resize(20, NULL);
       chargeVsOutInLE_2Can.resize(20, NULL);
       chargeVsOutInLE_3Can.resize(20, NULL);


       timingErrorTop.resize(20, NULL);
       timingErrorTopInOut.resize(20, NULL);
       timingErrorTopCan.resize(20, NULL);
       timingErrorTopInOutCan.resize(20, NULL);

       timingDirectionTop.resize(20, NULL);
       timingDirectionTopInOut.resize(20, NULL);
       timingDirectionTopCan.resize(20, NULL);
       timingDirectionTopInOutCan.resize(20, NULL);


       narrowTrackSharing1DataSmallError.resize(20, NULL);
       narrowTrackSharing1DataLargeError.resize(20, NULL);
       narrowTrackSharing1DataSmallErrorCan.resize(20, NULL);
       narrowTrackSharing1DataLargeErrorCan.resize(20, NULL);

       narrowTrackSharing1DataLargeErrorSmallZ.resize(20, NULL);
       narrowTrackSharing1DataLargeErrorSmallZCan.resize(20, NULL);

       TProfile*  chargeThroughTracker=  new TProfile("chargeThroughTracker", "chargeThroughTracker" , 25, 0, 25, 0, 500 ) ;
       TProfile*  widthThroughTracker=  new TProfile("widthThroughTracker", "widthThroughTracker" , 25, 0, 25, 0, 15 ) ;
       TH1F*  chargeThroughTrackerTIBtop=  new TH1F("chargeThroughTrackerTIBtop", "chargeThroughTrackerTIBtop",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTIBbottom=  new TH1F("chargeThroughTrackerTIBbottom", "chargeThroughTrackerTIBbottom",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTOBtop=  new TH1F("chargeThroughTrackerTOBtop", "chargeThroughTrackerTOBtop",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTOBbottom=  new TH1F("chargeThroughTrackerTOBbottom", "chargeThroughTrackerTOBbottom",  500, 0, 1000 ) ;
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


               {
                   if(narrowTrackSharing1Data.at(partPos) == NULL)
                   {
                       narrowTrackSharing1Data.at(partPos) = new TH1F( ("narrowTrackSharing1"+ parName).c_str() , ("narrowTrackSharing1"+parName).c_str() , 200, -1, 1 );
                       narrowTrackSharing1DataCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing1"+ parName).c_str() , ("cnarrowTrackSharing1"+parName).c_str()  );
                       narrowTrackSharing1DataBot.at(partPos) = new TH1F( ("narrowTrackSharing1Bot"+ parName).c_str() , ("narrowTrackSharing1Bot"+parName).c_str() , 200, -1, 1 );
                       narrowTrackSharing1DataBotCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing1Bot"+ parName).c_str() , ("cnarrowTrackSharing1Bot"+parName).c_str()  );
                       canvases.push_back(parName);
                   }
                   if(narrowTrackSharing2Data.at(partPos) == NULL)
                   {
                       narrowTrackSharing2Data.at(partPos) = new TH1F( ("narrowTrackSharing2"+ parName).c_str() , ("narrowTrackSharing2"+parName).c_str() , 200, -1, 1 );
                       narrowTrackSharing2DataCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing2"+ parName).c_str() , ("cnarrowTrackSharing2"+parName).c_str());
                       narrowTrackSharing2DataBot.at(partPos) = new TH1F( ("narrowTrackSharing2Bot"+ parName).c_str() , ("narrowTrackSharing2Bot"+parName).c_str() , 200, -1, 1 );
                       narrowTrackSharing2DataBotCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing2Bot"+ parName).c_str() , ("cnarrowTrackSharing2Bot"+parName).c_str());
                   }
                   //@MJ@ TODO create histogram if not done yet
               if(subCTstripCharge.at(clusterStart+1) != -333)
                   narrowTrackSharing1Data.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
               if(subCTstripCharge.at(clusterStart+3) != -333)
                   narrowTrackSharing1Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
               if(subCTstripCharge.at(clusterStart) != -333)
                   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
               if(subCTstripCharge.at(clusterStart+4) != -333)
                   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));


                   if(widthTopInOutOnly.at(partPos) == NULL)
                   {
		       widthTopInOutOnly.at(partPos) =  new TProfile(("widthTopInOutOnly"+ parName).c_str(), ("widthTopInOutOnly"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;
		       widthBottomInOutOnly.at(partPos) = new TProfile(("widthBottomInOutOnly"+ parName).c_str(), ("widthBottomInOutOnly"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;
		       widthTopOutInOnly.at(partPos) =  new TProfile(("widthTopOutInOnly"+ parName).c_str(), ("widthTopOutInOnly"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;
		       widthBottomOutInOnly.at(partPos) = new TProfile(("widthBottomOutInOnly"+ parName).c_str(), ("widthBottomOutInOnly"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;
		       widthTopOutIn.at(partPos) =  new TProfile(("widthTopOutIn"+ parName).c_str(), ("widthTopOutIn"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;
		       widthBottomOutIn.at(partPos) =  new TProfile(("widthBottomOutIn"+ parName).c_str(), ("widthBottomOutIn"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;

		       chargeTopInOutOnly.at(partPos) =  new TProfile(("chargeTopInOutOnly"+ parName).c_str(), ("chargeTopInOutOnly"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeBottomInOutOnly.at(partPos) =  new TProfile(("chargeBottomInOutOnly"+ parName).c_str(), ("chargeBottomInOutOnly"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeTopOutInOnly.at(partPos) =  new TProfile(("chargeTopOutInOnly"+ parName).c_str(), ("chargeTopOutInOnly"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeBottomOutInOnly.at(partPos) =  new TProfile(("chargeBottomOutInOnly"+ parName).c_str(), ("chargeBottomOutInOnly"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeTopOutIn.at(partPos)=  new TProfile(("chargeTopOutIn"+ parName).c_str(), ("chargeTopOutIn"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeBottomOutIn.at(partPos) =  new TProfile(("chargeBottomOutIn"+ parName).c_str(), ("chargeBottomOutIn"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;

		       chargeTopOutInOnlySE.at(partPos) =  new TProfile(("chargeTopOutInOnlySE"+ parName).c_str(), ("chargeTopOutInOnlySE"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeTopOutInOnlyLE.at(partPos) =  new TProfile(("chargeTopOutInOnlyLE"+ parName).c_str(), ("chargeTopOutInOnlyLE"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;

		       etaOneaAsVzTop.at(partPos) =  new TProfile(("etaOneaAsVzTop"+ parName).c_str(), ("etaOneaAsVzTop"+ parName).c_str() , 100, -150, 150, 0, 1000 ) ;
		       etaOneaAsTimeTop.at(partPos) =  new TProfile(("etaOneaAsTimeTop"+ parName).c_str(), ("etaOneaAsTimeTop"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;

		       etaOneaAsVzBot.at(partPos) =  new TProfile(("etaOneaAsVzBot"+ parName).c_str(), ("etaOneaAsVzBot"+ parName).c_str() , 100, -150, 150, 0, 1000 ) ;
		       etaOneaAsTimeBot.at(partPos) =  new TProfile(("etaOneaAsTimeBot"+ parName).c_str(), ("etaOneaAsTimeBot"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;

		       chargeCenterOutIn.at(partPos) =  new TProfile(("chargeCenterOutIn"+ parName).c_str(), ("chargeCenterOutIn"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeEdgeOutIn.at(partPos) =  new TProfile(("chargeEdgeOutIn"+ parName).c_str(), ("chargeEdgeOutIn"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeCenterOutInCan.at(partPos) =   new TCanvas( ("chargeCenterOutInCan"+ parName).c_str(), ("chargeCenterOutInCan"+ parName).c_str()) ;
		       chargeEdgeOutInCan.at(partPos) =   new TCanvas( ("chargeEdgeOutInCan"+ parName).c_str(), ("chargeEdgeOutInCan"+ parName).c_str()) ;

		       chargeBottomCenterInOut.at(partPos) =  new TProfile(("chargeBottomCenterInOut"+ parName).c_str(), ("chargeBottomCenterInOut"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeBottomCenterInOutCan.at(partPos) =   new TCanvas( ("chargeBottomCenterInOutCan"+ parName).c_str(), ("chargeBottomCenterInOutCan"+ parName).c_str()) ;

		       innerZ.at(partPos) =  new TH1F(("innerZ"+ parName).c_str(), ("innerZ"+ parName).c_str() , 300, -300, 300 ) ;
		       innerZCan.at(partPos) =   new TCanvas( ("innerZ"+ parName).c_str(), ("innerZ"+ parName).c_str()) ;
		       innerVZ.at(partPos) =  new TH1F(("innerVZ"+ parName).c_str(), ("innerVZ"+ parName).c_str() , 300, -300, 300 ) ;
		       innerVZCan.at(partPos) =   new TCanvas( ("innerVZ"+ parName).c_str(), ("innerVZ"+ parName).c_str()) ;

                       vnrOfHitsVsError.at(partPos) = new TH2F( ("vnrOfHitsVsError"+ parName).c_str(),("vnrOfHitsVsError"+ parName).c_str() , 40, 0, 20, 100 , 0, 60);
                       nrOfSectorsVsError.at(partPos) = new TH2F( ("nrOfSectorsVsError"+ parName).c_str(),("nrOfSectorsVsError"+ parName).c_str() , 10, 0, 10, 10 , 0, 10);
                       chargeVsFreeInverseBeta.at(partPos) = new TH2F( ("chargeVsFreeInverseBeta"+ parName).c_str(),("chargeVsFreeInverseBeta"+ parName).c_str() , 60, -20, 20, 100 , 0, 1000);
                       chargeVsOutIn.at(partPos) = new TH2F( ("chargeVsOutIn"+ parName).c_str(),("chargeVsOutIn"+ parName).c_str() , 200, -100, 100, 100 , 0, 1000);
                       chargeVsOutInErr.at(partPos) = new TH2F( ("chargeVsOutInErr"+ parName).c_str(),("chargeVsOutInErr"+ parName).c_str() , 40, 0, 20, 100 , 0, 1000);
                       chargeVsOutInLE.at(partPos) = new TH2F( ("chargeVsOutInLE"+ parName).c_str(),("chargeVsOutInLE"+ parName).c_str() , 200, -100, 100, 100 , 0, 1000);
                       chargeVsOutInErrLE.at(partPos) = new TH2F( ("chargeVsOutInErrLE"+ parName).c_str(),("chargeVsOutInErrLE"+ parName).c_str() , 40, 0, 20, 100 , 0, 1000);
                       outInErrVsFreeInverseBeta.at(partPos) = new TH2F( ("outInErrVsFreeInverseBeta"+ parName).c_str(),("outInErrVsFreeInverseBeta"+ parName).c_str() , 20, -10, 10, 10 , 0, 10);
                       outInErrVsOutIn.at(partPos) = new TH2F( ("outInErrVsOutIn"+ parName).c_str(),("outInErrVsOutIn"+ parName).c_str() , 120, -70, 50, 10 , 0, 10);
                       outInVsFreeInverseBeta.at(partPos) = new TH2F( ("outInVsFreeInverseBeta"+ parName).c_str(),("outInVsFreeInverseBeta"+ parName).c_str() , 20, -10, 10, 120 , -70, 50);
                       timeVsVz210ADC.at(partPos) = new TH2F( ("timeVsVz210ADC"+ parName).c_str(),("timeVsVz210ADC"+ parName).c_str() ,100 , -150, 150, 160 , -80, 80);
                       timeVsVz210ADCLow.at(partPos) = new TProfile( ("timeVsVz210ADCLow"+ parName).c_str(),("timeVsVz210ADCLow"+ parName).c_str() ,50 , -150, 150);
                       timeVsVz210ADCHigh.at(partPos) = new TProfile( ("timeVsVz210ADCHigh"+ parName).c_str(),("timeVsVz210ADCHigh"+ parName).c_str() ,100 , -150, 150);


		       chargeVsOutInLE_1.at(partPos) = new TH1D();
		       chargeVsOutInLE_2.at(partPos) = new TH1D();
		       chargeVsOutInLE_3.at(partPos) = new TH1D();
		       chargeVsOutInLE_1Can.at(partPos) = new TCanvas( ("chargeVsOutInCanLE_1"+ parName).c_str(),("chargeVsOutInCanLE_1"+ parName).c_str() );
		       chargeVsOutInLE_2Can.at(partPos) = new TCanvas( ("chargeVsOutInCanLE_2"+ parName).c_str(),("chargeVsOutInCanLE_2"+ parName).c_str() ) ;
		       chargeVsOutInLE_3Can.at(partPos) = new TCanvas( ("chargeVsOutInCanLE_3"+ parName).c_str(),("chargeVsOutInCanLE_3"+ parName).c_str() ) ;


                       vnrOfHitsVsErrorCan.at(partPos) = new TCanvas( ("vnrOfHitsVsErrorCan"+ parName).c_str(),("vnrOfHitsVsErrorCan"+ parName).c_str());
                       nrOfSectorsVsErrorCan.at(partPos) = new TCanvas( ("nrOfSectorsVsErrorCan"+ parName).c_str(),("nrOfSectorsVsErrorCan"+ parName).c_str() );
                       chargeVsFreeInverseBetaCan.at(partPos) = new TCanvas( ("chargeVsFreeInverseBetaCan"+ parName).c_str(),("chargeVsFreeInverseBetaCan"+ parName).c_str() );
                       chargeVsOutInCan.at(partPos) = new TCanvas( ("chargeVsOutInCan"+ parName).c_str(),("chargeVsOutInCan"+ parName).c_str() );
                       chargeVsOutInErrCan.at(partPos) = new TCanvas( ("chargeVsOutInErrCan"+ parName).c_str(),("chargeVsOutInErrCan"+ parName).c_str() );
                       chargeVsOutInCanLE.at(partPos) = new TCanvas( ("chargeVsOutInCanLE"+ parName).c_str(),("chargeVsOutInCanLE"+ parName).c_str() );
                       chargeVsOutInErrCanLE.at(partPos) = new TCanvas( ("chargeVsOutInErrCanLE"+ parName).c_str(),("chargeVsOutInErrCanLE"+ parName).c_str() );
                       outInErrVsFreeInverseBetaCan.at(partPos) = new TCanvas( ("outInErrVsFreeInverseBetaCan"+ parName).c_str(),("outInErrVsFreeInverseBetaCan"+ parName).c_str() );
                       outInErrVsOutInCan.at(partPos) = new TCanvas( ("outInErrVsOutInCan"+ parName).c_str(),("outInErrVsOutInCan"+ parName).c_str() );
                       outInVsFreeInverseBetaCan.at(partPos) = new TCanvas( ("outInVsFreeInverseBetaCan"+ parName).c_str(),("outInVsFreeInverseBetaCan"+ parName).c_str() );
                       timeVsVz210ADCCan.at(partPos) = new TCanvas( ("timeVsVz210ADCCan"+ parName).c_str(),("timeVsVz210ADCCan"+ parName).c_str() );
                       timeVsVz210ADCCanLow.at(partPos) = new TCanvas( ("timeVsVz210ADCCanLow"+ parName).c_str(),("timeVsVz210ADCCanLow"+ parName).c_str() );
                       timeVsVz210ADCCanHigh.at(partPos) = new TCanvas( ("timeVsVz210ADCCanHigh"+ parName).c_str(),("timeVsVz210ADCCanHigh"+ parName).c_str() );


		       widthTopInOutOnlyCan.at(partPos) =   new TCanvas( ("widthTopInOutOnly"+ parName).c_str(), ("widthTopInOutOnly"+ parName).c_str()) ;
		       widthBottomInOutOnlyCan.at(partPos) = new TCanvas( ("widthBottomInOutOnly"+ parName).c_str(), ("widthBottomInOutOnly"+ parName).c_str()) ;
		       widthTopOutInOnlyCan.at(partPos) =   new TCanvas( ("widthTopOutInOnly"+ parName).c_str(), ("widthTopOutInOnly"+ parName).c_str()) ;
		       widthBottomOutInOnlyCan.at(partPos) = new TCanvas( ("widthBottomOutInOnly"+ parName).c_str(), ("widthBottomOutInOnly"+ parName).c_str()) ;
		       widthTopOutInCan.at(partPos) =   new TCanvas( ("widthTopOutIn"+ parName).c_str(), ("widthTopOutIn"+ parName).c_str()) ;
		       widthBottomOutInCan.at(partPos) =   new TCanvas( ("widthBottomOutIn"+ parName).c_str(), ("widthBottomOutIn"+ parName).c_str()) ;

		       chargeTopInOutOnlyCan.at(partPos) =   new TCanvas( ("chargeTopInOutOnly"+ parName).c_str(), ("chargeTopInOutOnly"+ parName).c_str()) ;
		       chargeBottomInOutOnlyCan.at(partPos) =  new TCanvas( ("chargeBottomInOutOnly"+ parName).c_str(), ("chargeBottomInOutOnly"+ parName).c_str()) ;
		       chargeTopOutInOnlyCan.at(partPos) =   new TCanvas( ("chargeTopOutInOnly"+ parName).c_str(), ("chargeTopOutInOnly"+ parName).c_str()) ;
		       chargeBottomOutInOnlyCan.at(partPos) =  new TCanvas( ("chargeBottomOutInOnly"+ parName).c_str(), ("chargeBottomOutInOnly"+ parName).c_str()) ;
		       chargeTopOutInCan.at(partPos)=   new TCanvas( ("chargeTopOutIn"+ parName).c_str(), ("chargeTopOutIn"+ parName).c_str()) ;
		       chargeBottomOutInCan.at(partPos) = new TCanvas( ("chargeBottomOutIn"+ parName).c_str(), ("chargeBottomOutIn"+ parName).c_str()) ;


   cout << "in here iii" << endl;
		       chargeTopOutInOnlyCanSE.at(partPos) =   new TCanvas( ("chargeTopOutInOnlySE"+ parName).c_str(), ("chargeTopOutInOnlySE"+ parName).c_str()) ;
		       chargeTopOutInOnlyCanLE.at(partPos) =   new TCanvas( ("chargeTopOutInOnlyLE"+ parName).c_str(), ("chargeTopOutInOnlyLE"+ parName).c_str()) ;
   cout << "in here iv" << endl;
		       etaOneaAsVzTopCan.at(partPos) =   new TCanvas( ("etaOneaAsVzTopCan"+ parName).c_str(), ("etaOneaAsVzTopCan"+ parName).c_str()) ;
		       etaOneaAsTimeTopCan.at(partPos) =   new TCanvas( ("etaOneaAsTimeTopCan"+ parName).c_str(), ("etaOneaAsTimeTopCan"+ parName).c_str()) ;


		       etaOneaAsVzBotCan.at(partPos) =   new TCanvas( ("etaOneaAsVzBotCan"+ parName).c_str(), ("etaOneaAsVzBotCan"+ parName).c_str()) ;
		       etaOneaAsTimeBotCan.at(partPos) =   new TCanvas( ("etaOneaAsTimeBotCan"+ parName).c_str(), ("etaOneaAsTimeBotCan"+ parName).c_str()) ;

                       timingErrorTop.at(partPos) = new TH1F( ("timingErrorTop"+ parName).c_str() , ("timingErrorTop"+parName).c_str() , 100, -100, 100 );
                       timingErrorTopInOut.at(partPos)  = new TH1F( ("timingErrorTopInOut"+ parName).c_str() , ("timingErrorTopInOut"+parName).c_str() , 100, -100, 100 );
                       timingErrorTopCan.at(partPos) = new TCanvas( ("timingErrorTop"+ parName).c_str() , ("timingErrorTop"+parName).c_str() ) ;
                       timingErrorTopInOutCan.at(partPos) = new TCanvas( ("timingErrorTopInOut"+ parName).c_str() , ("timingErrorTopInOut"+parName).c_str()  ) ;

                       timingDirectionTop.at(partPos) = new TH1F( ("timingDirectionTop"+ parName).c_str() , ("timingDirectionTop"+parName).c_str() , 4, -2, 2 );
                       timingDirectionTopInOut.at(partPos)  = new TH1F( ("timingDirectionTopInOut"+ parName).c_str() , ("timingDirectionTopInOut"+parName).c_str() , 4, -2, 2 );
                       timingDirectionTopCan.at(partPos) = new TCanvas( ("timingDirectionTop"+ parName).c_str() , ("timingDirectionTop"+parName).c_str() ) ;
                       timingDirectionTopInOutCan.at(partPos) = new TCanvas( ("timingDirectionTopInOut"+ parName).c_str() , ("timingDirectionTopInOut"+parName).c_str()  ) ;

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

                       narrowTrackSharing1DataSmallErrorCan.at(partPos) = new TCanvas( ("narrowsmallerrSharing1"+ parName).c_str() , ("narrowsmallerrSharing1"+parName).c_str() ) ;
                       narrowTrackSharing1DataSmallError.at(partPos) = new TH1F( ("narrowsmallerrSharing1"+ parName).c_str() , ("narrowsmallerrSharing1"+parName).c_str() , 200, -1, 1 ) ;
                       narrowTrackSharing1DataLargeErrorCan.at(partPos) = new TCanvas( ("narrowlargeerrSharing1"+ parName).c_str() , ("narrowlargeerrSharing1"+parName).c_str() ) ;
                       narrowTrackSharing1DataLargeError.at(partPos) = new TH1F( ("narrowlargeerrSharing1"+ parName).c_str() , ("narrowlargeerrSharing1"+parName).c_str() , 200, -1, 1 ) ;

                       narrowTrackSharing1DataLargeErrorSmallZCan.at(partPos) = new TCanvas( ("narrowlargeerrSmallZSharing1"+ parName).c_str() , ("narrowlargeerrSmallZSharing1"+parName).c_str() ) ;
                       narrowTrackSharing1DataLargeErrorSmallZ.at(partPos) = new TH1F( ("narrowlargeerrSmallZSharing1"+ parName).c_str() , ("narrowlargeerrSmallZSharing1"+parName).c_str() , 200, -1, 1 ) ;
   cout << "in here f" << endl;
                   }

                   if(true) //if(subclusterlayerwheel.at(m) == 3)
                   {
                       cout << "partition name " << parName << " event count " << eventCount.at(clusterStart) << "layer " << subCTstripChargeLayerwheel.at(clusterStart) << " detid " << subclusterdetid.at(m) << endl;
                       if(subtsosrhglobalphi.at(m)>0) //top
                       {
                           widthTopOutInOnly.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                           chargeTopOutInOnly.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                           timingDirectionTop.at(partPos)->Fill(subCTMuontrackDirection.at(clusterStart));
                           vnrOfHitsVsError.at(partPos)->Fill(subCTCmbtimeVtxrErr.at(clusterStart), subCTnrOfMuHits.at(clusterStart));
                           nrOfSectorsVsError.at(partPos)->Fill( subCTCmbtimeVtxrErr.at(clusterStart), subCTsectorsOfDT.at(clusterStart));
                           chargeVsFreeInverseBeta.at(partPos)->Fill( subCTMuonCombinedFreeInverseBeta.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart) );
                           chargeVsOutIn.at(partPos)->Fill( subCTCmbtimeVtxr.at(clusterStart) , subCTstripChargeTotCharge.at(clusterStart) );
                           chargeVsOutInErr.at(partPos)->Fill( subCTCmbtimeVtxrErr.at(clusterStart) , subCTstripChargeTotCharge.at(clusterStart) );
                           outInErrVsFreeInverseBeta.at(partPos)->Fill( subCTMuonCombinedFreeInverseBeta.at(clusterStart), subCTCmbtimeVtxrErr.at(clusterStart) );
                           outInErrVsOutIn.at(partPos)->Fill( subCTCmbtimeVtxr.at(clusterStart), subCTCmbtimeVtxrErr.at(clusterStart) );
                           outInVsFreeInverseBeta.at(partPos)->Fill( subCTMuonCombinedFreeInverseBeta.at(clusterStart), subCTCmbtimeVtxr.at(clusterStart) );
                           widthTopInOutOnly.at(partPos)->Fill(subCTCmbtimeVtx.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                           chargeTopInOutOnly.at(partPos)->Fill(subCTCmbtimeVtx.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
   cout << "in here g" << endl;
                               chargeTopOutInOnlyLE.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                               chargeVsOutInErrLE.at(partPos)->Fill( subCTCmbtimeVtxrErr.at(clusterStart) , subCTstripChargeTotCharge.at(clusterStart) );
                               innerZ.at(partPos)->Fill( subCTinnerZtop.at(clusterStart) );
                               innerVZ.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart) );
                               if( subCTstripChargeTotCharge.at(clusterStart) > 0)
                               {
                                   timeVsVz210ADC.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), subCTCmbtimeVtxr.at(clusterStart) );
                                   if(  subCTCmbtimeVtxr.at(clusterStart) > -20 &&  subCTCmbtimeVtxr.at(clusterStart)< 20)
                                       timeVsVz210ADCLow.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), subCTCmbtimeVtxr.at(clusterStart) );
                                   if(  subCTCmbtimeVtxr.at(clusterStart) > -35 &&  subCTCmbtimeVtxr.at(clusterStart)< 70)
                                       timeVsVz210ADCHigh.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), subCTCmbtimeVtxr.at(clusterStart) );
                               }
                               if(subCTinnerVZtop.at(clusterStart)> -5 && subCTinnerVZtop.at(clusterStart)<5)
                               {
		                   chargeCenterOutIn.at(partPos)->Fill( subCTCmbtimeVtxr.at(clusterStart) , subCTstripChargeTotCharge.at(clusterStart) );
                                   chargeVsOutInLE.at(partPos)->Fill( subCTCmbtimeVtxr.at(clusterStart) , subCTstripChargeTotCharge.at(clusterStart) );
                               }
                               if(subCTinnerVZtop.at(clusterStart)< -50 || subCTinnerVZtop.at(clusterStart)>50)
		                   chargeEdgeOutIn.at(partPos)->Fill( subCTCmbtimeVtxr.at(clusterStart) , subCTstripChargeTotCharge.at(clusterStart) ) ;
                           if(subCTMuontrackDirection.at(clusterStart) > 0) //inOut
                           {
                               cout << "top Out In "  << endl;
                               timingErrorTopInOut.at(partPos)->Fill(subCTCmbtimeVtx.at(clusterStart));
               


                               if(subCTstripCharge.at(clusterStart+1) != -333)
                               {
                                   if(  subCTCmbtimeVtxr.at(clusterStart) > -20 &&  subCTCmbtimeVtxr.at(clusterStart)< 20)
                                       etaOneaAsVzTop.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), (float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTinnerVZtop.at(clusterStart)> -20 && subCTinnerVZtop.at(clusterStart)<20)
                                       etaOneaAsTimeTop.at(partPos)->Fill(   subCTCmbtimeVtx.at(clusterStart), (float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2)); //@MJ@ attention in out time
                                   if(subCTCmbtimeVtxr.at(clusterStart)>-5 && subCTCmbtimeVtxr.at(clusterStart)<=5)
                                       narrowTrackSharing1Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=25 && subCTCmbtimeVtxr.at(clusterStart)<35)
                                       narrowTrackSharing1Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=10 && subCTCmbtimeVtxr.at(clusterStart)<=20)
                                       narrowTrackSharing1Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)<=-5)
                                       narrowTrackSharing1Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=35)
                                       narrowTrackSharing1Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxrErr.at(clusterStart)<2.5)
                                       narrowTrackSharing1DataSmallError.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxrErr.at(clusterStart)>2.5 && (subCTCmbtimeVtxr.at(clusterStart) > -10 && subCTCmbtimeVtxr.at(clusterStart) < -6 ) )
                                   {
                                       narrowTrackSharing1DataLargeError.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
				       if(subCTinnerVZtop.at(clusterStart)> -50 && subCTinnerVZtop.at(clusterStart)<50)
                                           narrowTrackSharing1DataLargeErrorSmallZ.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   }
   cout << "in here h" << endl;
                               }
                               if(subCTstripCharge.at(clusterStart+3) != -333)
                               {
                                   if(  subCTCmbtimeVtxr.at(clusterStart) > -20 &&  subCTCmbtimeVtxr.at(clusterStart)< 20)
                                       etaOneaAsVzTop.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTinnerVZtop.at(clusterStart)> -20 && subCTinnerVZtop.at(clusterStart)<20)
                                       etaOneaAsTimeTop.at(partPos)->Fill(   subCTCmbtimeVtx.at(clusterStart), (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));


                                   if(subCTCmbtimeVtxr.at(clusterStart)>-5 && subCTCmbtimeVtxr.at(clusterStart)<=5)
                                       narrowTrackSharing1Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=25 && subCTCmbtimeVtxr.at(clusterStart)<35)
                                       narrowTrackSharing1Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=10 && subCTCmbtimeVtxr.at(clusterStart)<=20)
                                       narrowTrackSharing1Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)<=-5)
                                       narrowTrackSharing1Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=35)
                                       narrowTrackSharing1Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxrErr.at(clusterStart)<2.5)
                                       narrowTrackSharing1DataSmallError.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxrErr.at(clusterStart)>2.5 && (subCTCmbtimeVtxr.at(clusterStart) > -10 && subCTCmbtimeVtxr.at(clusterStart) < -6 ) )
                                   {
                                       narrowTrackSharing1DataLargeError.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
				       if(subCTinnerVZtop.at(clusterStart)> -50 && subCTinnerVZtop.at(clusterStart)<50)
                                           narrowTrackSharing1DataLargeErrorSmallZ.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   }
                               }
                               if(subCTstripCharge.at(clusterStart) != -333)
                               {
                                   if(subCTCmbtimeVtxr.at(clusterStart)>-5 && subCTCmbtimeVtxr.at(clusterStart)<=5)
                                       narrowTrackSharing2Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=25 && subCTCmbtimeVtxr.at(clusterStart)<35)
                                       narrowTrackSharing2Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=10 && subCTCmbtimeVtxr.at(clusterStart)<=20)
                                       narrowTrackSharing2Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)<=-5)
                                       narrowTrackSharing2Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=35)
                                       narrowTrackSharing2Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                               }
                               if(subCTstripCharge.at(clusterStart+4) != -333)
                               {
                                   if(subCTCmbtimeVtxr.at(clusterStart)>-5 && subCTCmbtimeVtxr.at(clusterStart)<=5)
                                       narrowTrackSharing2Data5to5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=25 && subCTCmbtimeVtxr.at(clusterStart)<35)
                                       narrowTrackSharing2Data25to35.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=10 && subCTCmbtimeVtxr.at(clusterStart)<=20)
                                       narrowTrackSharing2Data10to20.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)<=-5 )
                                       narrowTrackSharing2Datainfto5.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTCmbtimeVtxr.at(clusterStart)>=35)
                                       narrowTrackSharing2Data35toinf.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                               }
                           }
                           else if(subCTMuontrackDirection.at(clusterStart) < 0)
                           {
                               cout << "top Out In "  << endl;
                               widthTopOutIn.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                               chargeTopOutIn.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                               timingErrorTop.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart));
                           }
                           else
                               cout << "direction undefined" << endl;
                       }
                       else if(subtsosrhglobalphi.at(m)<0)
                       {
                           widthBottomOutInOnly.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                           chargeBottomOutInOnly.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                           widthBottomInOutOnly.at(partPos)->Fill(subCTCmbtimeVtx.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                           chargeBottomInOutOnly.at(partPos)->Fill(subCTCmbtimeVtx.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                           //if(subCTinnerVZtop.at(clusterStart)> -20 && subCTinnerVZtop.at(clusterStart)<20)
                           //{
                               //if( subCTCmbtimeVtx.at(clusterStart)> -3 && subCTCmbtimeVtx.at(clusterStart)<3)
                               if( true)
                               {
			       if(subCTstripCharge.at(clusterStart+1) != -333)
                               {
				   narrowTrackSharing1DataBot.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   etaOneaAsVzBot.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), (float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTinnerVZtop.at(clusterStart)> -20 && subCTinnerVZtop.at(clusterStart)<20)
                                       etaOneaAsTimeBot.at(partPos)->Fill(   subCTCmbtimeVtx.at(clusterStart), (float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));

                               }
			       if(subCTstripCharge.at(clusterStart+3) != -333)
                               {
				   narrowTrackSharing1DataBot.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   etaOneaAsVzBot.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                   if(subCTinnerVZtop.at(clusterStart)> -20 && subCTinnerVZtop.at(clusterStart)<20)
                                       etaOneaAsTimeBot.at(partPos)->Fill(   subCTCmbtimeVtx.at(clusterStart), (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                               }
			       if(subCTstripCharge.at(clusterStart) != -333)
				   narrowTrackSharing2DataBot.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart+4) != -333)
				   narrowTrackSharing2DataBot.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                               }
		               chargeBottomCenterInOut.at(partPos)->Fill(subCTCmbtimeVtx.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart)) ;
                           //}
                           if(subCTMuontrackDirection.at(clusterStart) > 0)
                           {
                               cout << "bottom In Out "  << endl;
                           }
                           else if(subCTMuontrackDirection.at(clusterStart) < 0)
                           {
                               cout << "bottom Out In "  << endl;
                               widthBottomOutIn.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotWidth.at(clusterStart));
                               chargeBottomOutIn.at(partPos)->Fill(subCTCmbtimeVtxr.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart));
                           }
                           else
                               cout << "direction undefined" << endl;

                       }
                       else
                       {
                           cout << "weird" << endl;
                       }
                   }
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
       narrowTrackSharing1DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data.at(c)->GetName()+ ".eps").c_str());


       narrowTrackSharing2DataCan.at(c)->cd();
       narrowTrackSharing2Data.at(c)->DrawNormalized(""); 
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName() + ".root").c_str());
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName()+ ".eps").c_str());



       narrowTrackSharing1DataBot.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1DataBot.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing2DataBot.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing2DataBot.at(c)->SetMarkerColor(kBlack);

       narrowTrackSharing1DataBot.at(c)->SetTitle("");
       narrowTrackSharing2DataBot.at(c)->SetTitle("");

       narrowTrackSharing1DataBot.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2DataBot.at(c)->GetXaxis()->SetTitle("#eta #pm 2");

       narrowTrackSharing1DataBot.at(c)->SetMaximum(2.0*  narrowTrackSharing1DataBot.at(c)->GetMaximum());
       narrowTrackSharing2DataBot.at(c)->SetMaximum(1.5*  narrowTrackSharing2DataBot.at(c)->GetMaximum());


       narrowTrackSharing1DataBotCan.at(c)->cd();
       narrowTrackSharing1DataBot.at(c)->DrawNormalized(""); 
       narrowTrackSharing1DataBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataBot.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1DataBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataBot.at(c)->GetName()+ ".eps").c_str());


       narrowTrackSharing2DataBotCan.at(c)->cd();
       narrowTrackSharing2DataBot.at(c)->DrawNormalized(""); 
       narrowTrackSharing2DataBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2DataBot.at(c)->GetName() + ".root").c_str());
       narrowTrackSharing2DataBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2DataBot.at(c)->GetName()+ ".eps").c_str());



       //c37.SaveAs(("output/"+(string)dir+"/"+  "narrowTrackSharing1.eps").c_str());
       //
       //
       narrowTrackSharing1Data5to5.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data5to5.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1DataSmallError.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1DataSmallError.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1DataLargeError.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1DataLargeError.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1DataLargeErrorSmallZ.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1DataLargeErrorSmallZ.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Datainfto5.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Datainfto5.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data25to35.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data25to35.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data35toinf.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data35toinf.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data10to20.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data10to20.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing1Data5to5.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing1DataSmallError.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing1DataLargeError.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing1DataLargeErrorSmallZ.at(c)->GetXaxis()->SetTitle("#eta #pm 1");
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
       narrowTrackSharing1Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data5to5.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data5to5.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing1Datainfto5Can.at(c)->cd();
       narrowTrackSharing1Datainfto5.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Datainfto5.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Datainfto5.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing1Data25to35Can.at(c)->cd();
       narrowTrackSharing1Data25to35.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data25to35.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data25to35.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing1Data35toinfCan.at(c)->cd();
       narrowTrackSharing1Data35toinf.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data35toinf.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data35toinf.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing1Data10to20Can.at(c)->cd();
       narrowTrackSharing1Data10to20.at(c)->DrawNormalized(""); 
       narrowTrackSharing1Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data10to20.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data10to20.at(c)->GetName()+ ".eps").c_str());
       
       narrowTrackSharing2Data5to5Can.at(c)->cd();
       narrowTrackSharing2Data5to5.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data5to5.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing2Data5to5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data5to5.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing2Datainfto5Can.at(c)->cd();
       narrowTrackSharing2Datainfto5.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Datainfto5.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing2Datainfto5Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Datainfto5.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing2Data25to35Can.at(c)->cd();
       narrowTrackSharing2Data25to35.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data25to35.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing2Data25to35Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data25to35.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing2Data35toinfCan.at(c)->cd();
       narrowTrackSharing2Data35toinf.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data35toinf.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing2Data35toinfCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data35toinf.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing2Data10to20Can.at(c)->cd();
       narrowTrackSharing2Data10to20.at(c)->DrawNormalized(""); 
       narrowTrackSharing2Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data10to20.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing2Data10to20Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data10to20.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing2DataCan.at(c)->cd();
       narrowTrackSharing2Data.at(c)->DrawNormalized(""); 
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName() + ".root").c_str());
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName()+ ".eps").c_str());
       
       widthTopInOutOnlyCan.at(c)->cd();
       widthTopInOutOnly.at(c)->GetXaxis()->SetTitle("time");
       widthTopInOutOnly.at(c)->GetYaxis()->SetTitle("cluster width");
       widthTopInOutOnly.at(c)->Draw("");
       widthTopInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthTopInOutOnly.at(c)->GetName()+ ".eps").c_str());
       widthTopInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthTopInOutOnly.at(c)->GetName()+ ".root").c_str());

       widthTopOutInOnlyCan.at(c)->cd();
       widthTopOutInOnly.at(c)->GetXaxis()->SetTitle("time");
       widthTopOutInOnly.at(c)->GetYaxis()->SetTitle("cluster width");
       widthTopOutInOnly.at(c)->Draw("");
       widthTopOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthTopOutInOnly.at(c)->GetName()+ ".eps").c_str());
       widthTopOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthTopOutInOnly.at(c)->GetName()+ ".root").c_str());

       widthTopOutInCan.at(c)->cd();
       widthTopOutIn.at(c)->GetXaxis()->SetTitle("time");
       widthTopOutIn.at(c)->GetYaxis()->SetTitle("cluster width");
       widthTopOutIn.at(c)->Draw("");
       widthTopOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthTopOutIn.at(c)->GetName()+ ".eps").c_str());
       widthTopOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthTopOutIn.at(c)->GetName()+ ".root").c_str());

       widthBottomInOutOnlyCan.at(c)->cd();
       widthBottomInOutOnly.at(c)->Draw("");
       widthBottomInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthBottomInOutOnly.at(c)->GetName()+ ".eps").c_str());
       widthBottomInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthBottomInOutOnly.at(c)->GetName()+ ".root").c_str());

       widthBottomOutInOnlyCan.at(c)->cd();
       widthBottomOutInOnly.at(c)->Draw("");
       widthBottomOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthBottomOutInOnly.at(c)->GetName()+ ".eps").c_str());
       widthBottomOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthBottomOutInOnly.at(c)->GetName()+ ".root").c_str());

       widthBottomOutInCan.at(c)->cd();
       widthBottomOutIn.at(c)->Draw("");
       widthBottomOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthBottomOutIn.at(c)->GetName()+ ".eps").c_str());
       widthBottomOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthBottomOutIn.at(c)->GetName()+ ".root").c_str());

       chargeTopInOutOnlyCan.at(c)->cd();
       chargeTopInOutOnly.at(c)->GetXaxis()->SetTitle("time");
       chargeTopInOutOnly.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeTopInOutOnly.at(c)->Draw("");
       chargeTopInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopInOutOnly.at(c)->GetName()+ ".eps").c_str());
       chargeTopInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopInOutOnly.at(c)->GetName()+ ".root").c_str());

       chargeTopOutInOnlyCan.at(c)->cd();
       chargeTopOutInOnly.at(c)->GetXaxis()->SetTitle("time");
       chargeTopOutInOnly.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeTopOutInOnly.at(c)->Draw("");
       chargeTopOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutInOnly.at(c)->GetName()+ ".eps").c_str());
       chargeTopOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutInOnly.at(c)->GetName()+ ".root").c_str());

       chargeTopOutInCan.at(c)->cd();
       chargeTopOutIn.at(c)->GetXaxis()->SetTitle("time");
       chargeTopOutIn.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeTopOutIn.at(c)->Draw("");
       chargeTopOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutIn.at(c)->GetName()+ ".eps").c_str());
       chargeTopOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutIn.at(c)->GetName()+ ".root").c_str());

       chargeBottomInOutOnlyCan.at(c)->cd();
       chargeBottomInOutOnly.at(c)->Draw("");
       chargeBottomInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomInOutOnly.at(c)->GetName()+ ".eps").c_str());
       chargeBottomInOutOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomInOutOnly.at(c)->GetName()+ ".root").c_str());

       chargeBottomOutInOnlyCan.at(c)->cd();
       chargeBottomOutInOnly.at(c)->Draw("");
       chargeBottomOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomOutInOnly.at(c)->GetName()+ ".eps").c_str());
       chargeBottomOutInOnlyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomOutInOnly.at(c)->GetName()+ ".root").c_str());

       chargeBottomOutInCan.at(c)->cd();
       chargeBottomOutIn.at(c)->Draw("");
       chargeBottomOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomOutIn.at(c)->GetName()+ ".eps").c_str());
       chargeBottomOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomOutIn.at(c)->GetName()+ ".root").c_str());


       timingErrorTopCan.at(c)->cd();
       timingErrorTop.at(c)->GetXaxis()->SetTitle("time");
       timingErrorTop.at(c)->SetTitle("");
       timingErrorTop.at(c)->DrawNormalized("hist"); 
       timingErrorTopInOut.at(c)->SetLineColor(kRed); 
       timingErrorTopInOut.at(c)->DrawNormalized("same hist"); 
       timingErrorTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingErrorTop.at(c)->GetName()+ ".root").c_str());
       timingErrorTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingErrorTop.at(c)->GetName()+ ".eps").c_str());

       timingDirectionTopCan.at(c)->cd();
       timingDirectionTop.at(c)->GetXaxis()->SetTitle("direction");
       timingDirectionTop.at(c)->SetTitle("");
       timingDirectionTop.at(c)->Draw("hist"); 
       timingDirectionTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingDirectionTop.at(c)->GetName()+ ".root").c_str());
       timingDirectionTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timingDirectionTop.at(c)->GetName()+ ".eps").c_str());


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
       vnrOfHitsVsError.at(c)->GetXaxis()->SetTitle("OutIn error");
       vnrOfHitsVsError.at(c)->GetYaxis()->SetTitle("nr of Muon hits");
       vnrOfHitsVsError.at(c)->SetTitle("");
       vnrOfHitsVsError.at(c)->Draw("colz"); 
       vnrOfHitsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ vnrOfHitsVsError.at(c)->GetName()+ ".root").c_str());
       vnrOfHitsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ vnrOfHitsVsError.at(c)->GetName()+ ".eps").c_str());

       nrOfSectorsVsErrorCan.at(c)->cd();
       nrOfSectorsVsError.at(c)->GetXaxis()->SetTitle("OutIn error");
       nrOfSectorsVsError.at(c)->GetYaxis()->SetTitle("nr of hitted Muon sectors");
       nrOfSectorsVsError.at(c)->SetTitle("");
       nrOfSectorsVsError.at(c)->Draw("colz"); 
       nrOfSectorsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nrOfSectorsVsError.at(c)->GetName()+ ".root").c_str());
       nrOfSectorsVsErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nrOfSectorsVsError.at(c)->GetName()+ ".eps").c_str());

       chargeVsFreeInverseBetaCan.at(c)->cd();
       chargeVsFreeInverseBeta.at(c)->GetXaxis()->SetTitle("free inverse beta");
       chargeVsFreeInverseBeta.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeVsFreeInverseBeta.at(c)->SetTitle("");
       chargeVsFreeInverseBeta.at(c)->Draw("colz"); 
       chargeVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsFreeInverseBeta.at(c)->GetName()+ ".root").c_str());
       chargeVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsFreeInverseBeta.at(c)->GetName()+ ".eps").c_str());


       outInErrVsFreeInverseBetaCan.at(c)->cd();
       outInErrVsFreeInverseBeta.at(c)->GetXaxis()->SetTitle("free inverse beta");
       outInErrVsFreeInverseBeta.at(c)->GetYaxis()->SetTitle("cluster outInErr");
       outInErrVsFreeInverseBeta.at(c)->SetTitle("");
       outInErrVsFreeInverseBeta.at(c)->Draw("colz"); 
       outInErrVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ outInErrVsFreeInverseBeta.at(c)->GetName()+ ".root").c_str());
       outInErrVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ outInErrVsFreeInverseBeta.at(c)->GetName()+ ".eps").c_str());

       outInErrVsOutInCan.at(c)->cd();
       outInErrVsOutIn.at(c)->GetXaxis()->SetTitle("cluster OutIn");
       outInErrVsOutIn.at(c)->GetYaxis()->SetTitle("cluster outInErr");
       outInErrVsOutIn.at(c)->SetTitle("");
       outInErrVsOutIn.at(c)->Draw("colz"); 
       outInErrVsOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ outInErrVsOutIn.at(c)->GetName()+ ".root").c_str());
       outInErrVsOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ outInErrVsOutIn.at(c)->GetName()+ ".eps").c_str());

       outInVsFreeInverseBetaCan.at(c)->cd();
       outInVsFreeInverseBeta.at(c)->GetXaxis()->SetTitle("free inverse beta");
       outInVsFreeInverseBeta.at(c)->GetYaxis()->SetTitle("cluster outIn");
       outInVsFreeInverseBeta.at(c)->SetTitle("");
       outInVsFreeInverseBeta.at(c)->Draw("colz"); 
       cout << outInVsFreeInverseBeta.at(c)->GetName() << " correlation factor" << outInVsFreeInverseBeta.at(c)->GetCorrelationFactor() << endl; 
       outInVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ outInVsFreeInverseBeta.at(c)->GetName()+ ".root").c_str());
       outInVsFreeInverseBetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ outInVsFreeInverseBeta.at(c)->GetName()+ ".eps").c_str());

       timeVsVz210ADCCan.at(c)->cd();
       timeVsVz210ADC.at(c)->GetXaxis()->SetTitle("vz");
       timeVsVz210ADC.at(c)->GetYaxis()->SetTitle("outIn");
       timeVsVz210ADC.at(c)->SetTitle("");
       timeVsVz210ADC.at(c)->Draw("colz"); 
       cout << timeVsVz210ADC.at(c)->GetName() << " correlation factor" << timeVsVz210ADC.at(c)->GetCorrelationFactor() << endl; 
       timeVsVz210ADCCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz210ADC.at(c)->GetName()+ ".root").c_str());
       timeVsVz210ADCCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz210ADC.at(c)->GetName()+ ".eps").c_str());

       timeVsVz210ADCCanLow.at(c)->cd();
       timeVsVz210ADCLow.at(c)->GetXaxis()->SetTitle("vz");
       timeVsVz210ADCLow.at(c)->GetYaxis()->SetTitle("outIn");
       timeVsVz210ADCLow.at(c)->SetTitle("");
       timeVsVz210ADCLow.at(c)->Draw(""); 
       timeVsVz210ADCCanLow.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz210ADCLow.at(c)->GetName()+ ".root").c_str());
       timeVsVz210ADCCanLow.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz210ADCLow.at(c)->GetName()+ ".eps").c_str());


       timeVsVz210ADCCanHigh.at(c)->cd();
       timeVsVz210ADCHigh.at(c)->GetXaxis()->SetTitle("vz");
       timeVsVz210ADCHigh.at(c)->GetYaxis()->SetTitle("outIn");
       timeVsVz210ADCHigh.at(c)->SetTitle("");
       timeVsVz210ADCHigh.at(c)->Draw(""); 
       timeVsVz210ADCCanHigh.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz210ADCHigh.at(c)->GetName()+ ".root").c_str());
       timeVsVz210ADCCanHigh.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz210ADCHigh.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing1DataSmallErrorCan.at(c)->cd();
       narrowTrackSharing1DataSmallError.at(c)->DrawNormalized(""); 
       narrowTrackSharing1DataSmallErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataSmallError.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1DataSmallErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataSmallError.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing1DataLargeErrorCan.at(c)->cd();
       narrowTrackSharing1DataLargeError.at(c)->DrawNormalized(""); 
       narrowTrackSharing1DataLargeErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataLargeError.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1DataLargeErrorCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataLargeError.at(c)->GetName()+ ".eps").c_str());

       narrowTrackSharing1DataLargeErrorSmallZCan.at(c)->cd();
       narrowTrackSharing1DataLargeErrorSmallZ.at(c)->DrawNormalized(""); 
       narrowTrackSharing1DataLargeErrorSmallZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataLargeErrorSmallZ.at(c)->GetName()+ ".root").c_str());
       narrowTrackSharing1DataLargeErrorSmallZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1DataLargeErrorSmallZ.at(c)->GetName()+ ".eps").c_str());

       chargeTopOutInOnlyCanSE.at(c)->cd();
       chargeTopOutInOnlySE.at(c)->GetXaxis()->SetTitle("time");
       chargeTopOutInOnlySE.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeTopOutInOnlySE.at(c)->Draw("");
       chargeTopOutInOnlyCanSE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutInOnlySE.at(c)->GetName()+ ".eps").c_str());
       chargeTopOutInOnlyCanSE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutInOnlySE.at(c)->GetName()+ ".root").c_str());

       etaOneaAsVzTopCan.at(c)->cd();
       etaOneaAsVzTop.at(c)->GetXaxis()->SetTitle("vz");
       etaOneaAsVzTop.at(c)->GetYaxis()->SetTitle("eta #pm 1");
       etaOneaAsVzTop.at(c)->Draw("");
       etaOneaAsVzTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVzTop.at(c)->GetName()+ ".eps").c_str());
       etaOneaAsVzTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVzTop.at(c)->GetName()+ ".root").c_str());


       etaOneaAsTimeTopCan.at(c)->cd();
       etaOneaAsTimeTop.at(c)->GetXaxis()->SetTitle("inOut");
       etaOneaAsTimeTop.at(c)->GetYaxis()->SetTitle("eta #pm 1");
       etaOneaAsTimeTop.at(c)->Draw("");
       etaOneaAsTimeTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeTop.at(c)->GetName()+ ".eps").c_str());
       etaOneaAsTimeTopCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeTop.at(c)->GetName()+ ".root").c_str());

       etaOneaAsVzBotCan.at(c)->cd();
       etaOneaAsVzBot.at(c)->GetXaxis()->SetTitle("vz");
       etaOneaAsVzBot.at(c)->GetYaxis()->SetTitle("eta #pm 1");
       etaOneaAsVzBot.at(c)->Draw("");
       etaOneaAsVzBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVzBot.at(c)->GetName()+ ".eps").c_str());
       etaOneaAsVzBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVzBot.at(c)->GetName()+ ".root").c_str());


       etaOneaAsTimeBotCan.at(c)->cd();
       etaOneaAsTimeBot.at(c)->GetXaxis()->SetTitle("inOut");
       etaOneaAsTimeBot.at(c)->GetYaxis()->SetTitle("eta #pm 1");
       etaOneaAsTimeBot.at(c)->Draw("");
       etaOneaAsTimeBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeBot.at(c)->GetName()+ ".eps").c_str());
       etaOneaAsTimeBotCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeBot.at(c)->GetName()+ ".root").c_str());



       chargeTopOutInOnlyCanLE.at(c)->cd();
       chargeTopOutInOnlyLE.at(c)->GetXaxis()->SetTitle("OutIn time");
       chargeTopOutInOnlyLE.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeTopOutInOnlyLE.at(c)->Draw("");
       chargeTopOutInOnlyCanLE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutInOnlyLE.at(c)->GetName()+ ".eps").c_str());
       chargeTopOutInOnlyCanLE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeTopOutInOnlyLE.at(c)->GetName()+ ".root").c_str());


       chargeVsOutInCan.at(c)->cd();
       chargeVsOutIn.at(c)->GetXaxis()->SetTitle("out in");
       chargeVsOutIn.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeVsOutIn.at(c)->SetTitle("");
       chargeVsOutIn.at(c)->Draw("colz"); 
       chargeVsOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutIn.at(c)->GetName()+ ".root").c_str());
       chargeVsOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutIn.at(c)->GetName()+ ".eps").c_str());


       chargeVsOutInErrCan.at(c)->cd();
       chargeVsOutInErr.at(c)->GetXaxis()->SetTitle("out in err");
       chargeVsOutInErr.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeVsOutInErr.at(c)->SetTitle("");
       chargeVsOutInErr.at(c)->Draw("colz"); 
       chargeVsOutInErrCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInErr.at(c)->GetName()+ ".root").c_str());
       chargeVsOutInErrCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInErr.at(c)->GetName()+ ".eps").c_str());

       chargeVsOutInCanLE.at(c)->cd();
       chargeVsOutInLE.at(c)->GetXaxis()->SetTitle("OutIn time ");
       chargeVsOutInLE.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeVsOutInLE.at(c)->SetTitle("");
       chargeVsOutInLE.at(c)->Draw("colz"); 
       chargeVsOutInCanLE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE.at(c)->GetName()+ ".root").c_str());
       chargeVsOutInCanLE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE.at(c)->GetName()+ ".eps").c_str());


           TF1 *fb = new TF1("fb","TMath::Landau(x,[0],[1],0)",0,1000);
           fb->SetParameters(130,21);
	   chargeVsOutInLE.at(c)->FitSlicesY(fb);
	   chargeVsOutInLE_1.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsOutInLE.at(c)->GetName()+ "_0").c_str());
	   chargeVsOutInLE_2.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsOutInLE.at(c)->GetName()+ "_1").c_str());
	   //chargeVsOutInLE_3.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsOutInLE.at(c)->GetName()+ "_2").c_str());

       chargeVsOutInLE_1Can.at(c)->cd();
       chargeVsOutInLE_1.at(c)->GetXaxis()->SetTitle("OutIn");
       chargeVsOutInLE_1.at(c)->GetYaxis()->SetTitle("par 1");
       chargeVsOutInLE_1.at(c)->SetTitle("");
       chargeVsOutInLE_1.at(c)->Draw("hist"); 
       chargeVsOutInLE_1Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE_1Can.at(c)->GetName()+ ".root").c_str());
       chargeVsOutInLE_1Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE_1Can.at(c)->GetName()+ ".eps").c_str());

       chargeVsOutInLE_2Can.at(c)->cd();
       chargeVsOutInLE_2.at(c)->GetXaxis()->SetTitle("OutIn");
       chargeVsOutInLE_2.at(c)->GetYaxis()->SetTitle("par 2");
       chargeVsOutInLE_2.at(c)->SetTitle("");
       chargeVsOutInLE_2.at(c)->Draw("hist"); 
       chargeVsOutInLE_2Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE_2Can.at(c)->GetName()+ ".root").c_str());
       chargeVsOutInLE_2Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE_2Can.at(c)->GetName()+ ".eps").c_str());


       chargeVsOutInLE_3Can.at(c)->cd();
       chargeVsOutInLE_3.at(c)->GetXaxis()->SetTitle("charge");
       chargeVsOutInLE_3.at(c)->GetYaxis()->SetTitle("fit");
       chargeVsOutInLE_3.at(c)->SetTitle("");
       //chargeVsOutInLE_3.at(c)->Draw("hist"); 
       fb->Draw(""); 
       chargeVsOutInLE_3Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE_3Can.at(c)->GetName()+ "fit.root").c_str());
       chargeVsOutInLE_3Can.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInLE_3Can.at(c)->GetName()+ "fit.eps").c_str());


       chargeVsOutInErrCanLE.at(c)->cd();
       chargeVsOutInErrLE.at(c)->GetXaxis()->SetTitle("OutIn Err");
       chargeVsOutInErrLE.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeVsOutInErrLE.at(c)->SetTitle("");
       chargeVsOutInErrLE.at(c)->Draw("colz"); 
       chargeVsOutInErrCanLE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInErrLE.at(c)->GetName()+ ".root").c_str());
       chargeVsOutInErrCanLE.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeVsOutInErrLE.at(c)->GetName()+ ".eps").c_str());


       chargeCenterOutInCan.at(c)->cd();
       chargeCenterOutIn.at(c)->GetXaxis()->SetTitle("outIn time");
       chargeCenterOutIn.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeCenterOutIn.at(c)->SetTitle("");
       chargeCenterOutIn.at(c)->SetLineColor(kBlue);
       chargeEdgeOutIn.at(c)->SetLineColor(kRed);
       chargeCenterOutIn.at(c)->Draw(""); 
       //chargeEdgeOutIn.at(c)->Draw("same"); 
       chargeCenterOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeCenterOutIn.at(c)->GetName()+ ".root").c_str());
       chargeCenterOutInCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeCenterOutIn.at(c)->GetName()+ ".eps").c_str());

       chargeBottomCenterInOutCan.at(c)->cd();
       chargeBottomCenterInOut.at(c)->GetXaxis()->SetTitle("InOut time");
       chargeBottomCenterInOut.at(c)->GetYaxis()->SetTitle("cluster charge");
       chargeBottomCenterInOut.at(c)->SetTitle("");
       chargeBottomCenterInOut.at(c)->SetLineColor(kBlue);
       chargeEdgeOutIn.at(c)->SetLineColor(kRed);
       chargeBottomCenterInOut.at(c)->Draw(""); 
       //chargeEdgeOutIn.at(c)->Draw("same"); 
       chargeBottomCenterInOutCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomCenterInOut.at(c)->GetName()+ ".root").c_str());
       chargeBottomCenterInOutCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargeBottomCenterInOut.at(c)->GetName()+ ".eps").c_str());


       innerZCan.at(c)->cd();
       innerZ.at(c)->GetXaxis()->SetTitle("z");
       innerZ.at(c)->SetTitle("");
       innerZ.at(c)->Draw("hist"); 
       innerZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerZ.at(c)->GetName()+ ".root").c_str());
       innerZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerZ.at(c)->GetName()+ ".eps").c_str());

       innerVZCan.at(c)->cd();
       innerVZ.at(c)->GetXaxis()->SetTitle("vz");
       innerVZ.at(c)->SetTitle("");
       innerVZ.at(c)->Draw("hist"); 
       innerVZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVZ.at(c)->GetName()+ ".root").c_str());
       innerVZCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVZ.at(c)->GetName()+ ".eps").c_str());


       }


      /////////////////////////////////////////////////////



       TCanvas c35("dummyCTplot","dummyCTplot");
       dummyCTplot->Draw("hist"); 
       c35.SaveAs(("output/"+(string)dir+"/"+  "dummyCTplot.root").c_str());
       c35.SaveAs(("output/"+(string)dir+"/"+  "dummyCTplot.eps").c_str());

    //cout << "in here 7"  << endl;

   return 0;
}
