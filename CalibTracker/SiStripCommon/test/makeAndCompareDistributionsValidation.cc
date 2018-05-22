//./makeAndCompareDistributionsValidation test_shallowTrackCRUZET_Data2017Validation.root test_shallowTrackCRUZET_MC2017Validation.root TOB 0 5 yes CRUZETtunedXTALKValidation
//./makeAndCompareDistributionsValidation test_shallowTrackAndCluster_CollDataValidation.root test_shallowTrackAndCluster_CollMCValidation.rootColl2017ePerADCdefstep3.root  TOB 0 5 yes ColltunedXTALKValidation
//./makeAndCompareDistributionsValidation test_shallowTrackAndCluster_CollDataValidation.root test_shallowTrackAndCluster_CollDataValidation.rootrunG.root  TOB 0 5 yes DataRelValRECOcomp

//
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

 gStyle->SetOptStat(0);
 gROOT->ForceStyle();
 TH1::SetDefaultSumw2();
    if(argc != 8)
        throw std::runtime_error("Bad number of arguments!");
    
    TString file1 = argv[1];
    TString file2 = argv[2];
    TString subDet = argv[3];
    TString slayerCutDown = argv[4];
    TString slayerCutUp = argv[5];
    TString norm = argv[6];
    TString dir = argv[7];

    int layerCutDown = slayerCutDown.Atoi();
    int layerCutUp = slayerCutUp.Atoi();
    float narrowness = 0.5;

    uint16_t sdId = 0;

    if(subDet == "TIB")
        sdId = 3;
    else if(subDet == "TID")
        sdId = 4;
    else if(subDet == "TOB")
        sdId = 5;
    else if(subDet == "TEC")
        sdId = 6;
    else
        throw std::runtime_error("Wrong partition entered");

    TFile* f1 = NULL;
    TTree* t1 = NULL;
    f1 = TFile::Open(file1); 
    TFile* f2 = NULL;
    TTree* t2 = NULL;
    f2 = TFile::Open(file2); 
    if(f1==NULL)
        throw std::runtime_error("File 1 address not set");
    t1 = dynamic_cast<TTree*>(f1->Get("testTree/tree"));
    if(t1==NULL)
        throw std::runtime_error("Tree 1 address not set");

    if(f2==NULL)
        throw std::runtime_error("File 2 address not set");
    t2 = dynamic_cast<TTree*>(f2->Get("testTree/tree"));
    if(t2==NULL)
        throw std::runtime_error("Tree 2 address not set");

       vector<float>* partition = 0;
       vector<float>* partition2 = 0;
       vector<float>* clustercharge = 0;
       vector<float>* clustercharge2 =0;
       vector<float>* clusterwidth = 0;
       vector<float>* clusterwidth2 = 0;
       vector<float>* clusterlayerwheel = 0;
       vector<float>* clusterlayerwheel2 = 0;
       vector<float>* clusterstripChargeSubdetid = 0;
       vector<float>* clusterstripChargeSubdetid2 = 0;
       vector<float>* clusterstripCharge = 0;
       vector<float>* clusterstripCharge2 = 0;
       vector<float>* clusterstripChargeLayerwheel = 0;
       vector<float>* clusterstripChargeLayerwheel2 = 0;
       vector<float>* clusterstripChargeStripNr = 0;
       vector<float>* clusterstripChargeStripNr2 = 0;
       vector<float>* clusterstripChargeTotWidth = 0;
       vector<float>* clusterstripChargeTotWidth2 = 0;
       vector<float>* clusterstripChargeTotCharge = 0;
       vector<float>* clusterstripChargeTotCharge2 = 0;
       vector<float>* clusterstripChargeLocalTrackPhi = 0;
       vector<float>* clusterstripChargeLocalTrackPhi2 = 0;
       vector<float>* clusterstripChargeGlobalTrackPhi = 0;
       vector<float>* clusterstripChargeGlobalTrackPhi2 = 0;
       vector<float>* clusterstripChargeLocalTrackTheta = 0;
       vector<float>* clusterstripChargeLocalTrackTheta2 = 0;
       vector<float>* clusterstripChargeGlobalTrackTheta = 0;
       vector<float>* clusterstripChargeGlobalTrackTheta2 = 0;
       vector<unsigned>* clusterstripChargeDetid = 0;
       vector<unsigned>* clusterstripChargeDetid2 = 0;
       vector<float>* clusterstripChargeLocalX = 0;
       vector<float>* clusterstripChargeLocalX2 = 0;
       vector<float>* clusterstripChargeLocalY = 0;
       vector<float>* clusterstripChargeLocalY2 = 0;
       vector<float>* tsostrackPt = 0;
       vector<float>* tsostrackPt2 = 0;
       vector<float>* clusterstripChargetrackPt = 0;
       vector<float>* clusterstripChargetrackPt2 = 0;
       vector<float>* tsoslocalphi = 0;
       vector<float>* tsoslocalphi2 = 0;
       vector<float>* tsoslocaltheta = 0;
       vector<float>* tsoslocaltheta2 = 0;
       vector<float>* tsoslocalpitch = 0;
       vector<float>* tsoslocalpitch2 = 0;
       vector<float>* clustersensorThickness = 0;
       vector<float>* clustersensorThickness2 = 0;
       vector<float>* tsosBdotY = 0;
       vector<float>* tsosBdotY2 = 0;
       vector<float>* clusterstripChargelocalpitch = 0;
       vector<float>* clusterstripChargelocalpitch2  = 0;
       vector<float>* clusterstripChargesensorThickness = 0;
       vector<float>* clusterstripChargesensorThickness2  = 0;
       vector<float>* clusterstripChargeBdotY = 0;
       vector<float>* clusterstripChargeBdotY2  = 0;
       vector<float>* tsosrhglobalphi = 0;
       vector<float>* tsosrhglobalphi2 = 0;
       //vector<float>* CTCmbtimeVtxr = 0;
       //vector<float>* CTCmbtimeVtxr2 = 0;

       vector<float> subpartition;
       vector<float> subpartition2;
       vector<float> subclustercharge;
       vector<float> subclustercharge2;
       vector<float> subclusterwidth;
       vector<float> subclusterwidth2;
       vector<float> subclusterlayerwheel;
       vector<float> subclusterlayerwheel2;
       vector<float> subclusterstripChargeSubdetid;
       vector<float> subclusterstripChargeSubdetid2;
       vector<float> subclusterstripCharge;
       vector<float> subclusterstripCharge2;
       vector<float> subclusterstripChargeLayerwheel;
       vector<float> subclusterstripChargeLayerwheel2;
       vector<float> subclusterstripChargeStripNr;
       vector<float> subclusterstripChargeStripNr2;
       vector<float> subclusterstripChargeTotWidth;
       vector<float> subclusterstripChargeTotWidth2;
       vector<float> subclusterstripChargeTotCharge;
       vector<float> subclusterstripChargeTotCharge2;
       vector<float> subclusterstripChargeLocalTrackPhi;
       vector<float> subclusterstripChargeLocalTrackPhi2;
       vector<float> subclusterstripChargeGlobalTrackPhi;
       vector<float> subclusterstripChargeGlobalTrackPhi2;
       vector<float> subclusterstripChargeLocalTrackTheta;
       vector<float> subclusterstripChargeLocalTrackTheta2;
       vector<float> subclusterstripChargeGlobalTrackTheta;
       vector<float> subclusterstripChargeGlobalTrackTheta2;
       vector<unsigned> subclusterstripChargeDetid;
       vector<unsigned> subclusterstripChargeDetid2;
       vector<float> subclusterstripChargeLocalX;
       vector<float> subclusterstripChargeLocalX2;
       vector<float> subclusterstripChargeLocalY;
       vector<float> subclusterstripChargeLocalY2;
       vector<float> subtsostrackPt;
       vector<float> subtsostrackPt2;
       vector<float> subclusterstripChargetrackPt;
       vector<float> subclusterstripChargetrackPt2;
       vector<float> subtsoslocalphi;
       vector<float> subtsoslocalphi2;
       vector<float> subtsoslocaltheta;
       vector<float> subtsoslocaltheta2;
       vector<float> subtsoslocalpitch;
       vector<float> subtsoslocalpitch2;
       vector<float> subclustersensorThickness;
       vector<float> subclustersensorThickness2;
       vector<float> subtsosBdotY;
       vector<float> subtsosBdotY2;
       vector<float> subclusterstripChargelocalpitch;
       vector<float> subclusterstripChargelocalpitch2;
       vector<float> subclusterstripChargesensorThickness;
       vector<float> subclusterstripChargesensorThickness2;
       vector<float> subclusterstripChargeBdotY;
       vector<float> subclusterstripChargeBdotY2;
       vector<float> subtsosrhglobalphi;
       vector<float> subtsosrhglobalphi2;
       //vector<float> subCTCmbtimeVtxr;
       //vector<float> subCTCmbtimeVtxr2;


       t1->SetBranchAddress("clustersubdetid",  &partition );
       t1->SetBranchAddress("clustercharge",  &clustercharge );
       t1->SetBranchAddress("clusterwidth",  &clusterwidth );
       t1->SetBranchAddress("clusterlayerwheel",  &clusterlayerwheel );
       t1->SetBranchAddress("clusterstripChargeSubdetid",  &clusterstripChargeSubdetid );
       t1->SetBranchAddress("clusterstripCharge",  &clusterstripCharge );
       t1->SetBranchAddress("clusterstripChargeLayerwheel",  &clusterstripChargeLayerwheel );
       t1->SetBranchAddress("clusterstripChargeStripNr",  &clusterstripChargeStripNr );
       t1->SetBranchAddress("clusterstripChargeTotWidth",  &clusterstripChargeTotWidth );
       //t1->SetBranchAddress("clusterstripChargeTotCharge",  &clusterstripChargeTotWidth ); //@MJ@ TODO just for now -> switched values
       t1->SetBranchAddress("clusterstripChargeTotCharge",  &clusterstripChargeTotCharge );
       t1->SetBranchAddress("clusterstripChargeLocalTrackPhi",  &clusterstripChargeLocalTrackPhi );
       t1->SetBranchAddress("clusterstripChargeGlobalTrackPhi",  &clusterstripChargeGlobalTrackPhi );
       t1->SetBranchAddress("clusterstripChargeLocalTrackTheta",  &clusterstripChargeLocalTrackTheta );
       t1->SetBranchAddress("clusterstripChargeGlobalTrackTheta",  &clusterstripChargeGlobalTrackTheta );
       t1->SetBranchAddress("clusterstripChargeDetid",  &clusterstripChargeDetid );
       t1->SetBranchAddress("clusterstripChargeLocalX",  &clusterstripChargeLocalX );
       t1->SetBranchAddress("clusterstripChargeLocalY",  &clusterstripChargeLocalY );
       t1->SetBranchAddress("clusterstripChargetrackPt",  &clusterstripChargetrackPt );
       t1->SetBranchAddress("tsostrackPt",  &tsostrackPt );
       t1->SetBranchAddress("tsoslocalphi",  &tsoslocalphi );
       t1->SetBranchAddress("tsoslocaltheta",  &tsoslocaltheta );
       t1->SetBranchAddress("tsoslocalpitch",  &tsoslocalpitch );
       t1->SetBranchAddress("clustersensorThickness",  &clustersensorThickness );
       t1->SetBranchAddress("tsosBdotY",  &tsosBdotY );
       t1->SetBranchAddress("clusterstripChargelocalpitch",  &clusterstripChargelocalpitch );
       t1->SetBranchAddress("clusterstripChargesensorThickness",  &clusterstripChargesensorThickness );
       t1->SetBranchAddress("clusterstripChargeBdotY",  &clusterstripChargeBdotY );
       t1->SetBranchAddress("tsosrhglobalphi",  &tsosrhglobalphi );
       //t1->SetBranchAddress("CTCmbtimeVtxr",  &CTCmbtimeVtxr );

       t2->SetBranchAddress("clustersubdetid",  &partition2 );
       t2->SetBranchAddress("clustercharge",  &clustercharge2 );
       t2->SetBranchAddress("clusterwidth",  &clusterwidth2 );
       t2->SetBranchAddress("clusterlayerwheel",  &clusterlayerwheel2 );
       t2->SetBranchAddress("clusterstripChargeSubdetid",  &clusterstripChargeSubdetid2 );
       t2->SetBranchAddress("clusterstripCharge",  &clusterstripCharge2 );
       t2->SetBranchAddress("clusterstripChargeLayerwheel",  &clusterstripChargeLayerwheel2 );
       t2->SetBranchAddress("clusterstripChargeStripNr",  &clusterstripChargeStripNr2 );
       t2->SetBranchAddress("clusterstripChargeTotWidth",  &clusterstripChargeTotWidth2 );
       //t2->SetBranchAddress("clusterstripChargeTotCharge",  &clusterstripChargeTotWidth2 ); //@MJ@ TODO just for now -> switched values
       t2->SetBranchAddress("clusterstripChargeTotCharge",  &clusterstripChargeTotCharge2 );
       t2->SetBranchAddress("clusterstripChargeLocalTrackPhi",  &clusterstripChargeLocalTrackPhi2 );
       t2->SetBranchAddress("clusterstripChargeGlobalTrackPhi",  &clusterstripChargeGlobalTrackPhi2 );
       t2->SetBranchAddress("clusterstripChargeLocalTrackTheta",  &clusterstripChargeLocalTrackTheta2 );
       t2->SetBranchAddress("clusterstripChargeGlobalTrackTheta",  &clusterstripChargeGlobalTrackTheta2 );
       t2->SetBranchAddress("clusterstripChargeDetid",  &clusterstripChargeDetid2 );
       t2->SetBranchAddress("clusterstripChargeLocalX",  &clusterstripChargeLocalX2 );
       t2->SetBranchAddress("clusterstripChargeLocalY",  &clusterstripChargeLocalY2 );
       t2->SetBranchAddress("clusterstripChargetrackPt",  &clusterstripChargetrackPt2 );
       t2->SetBranchAddress("tsostrackPt",  &tsostrackPt2 );
       t2->SetBranchAddress("tsoslocalphi",  &tsoslocalphi2 );
       t2->SetBranchAddress("tsoslocaltheta",  &tsoslocaltheta2 );
       t2->SetBranchAddress("tsoslocalpitch",  &tsoslocalpitch2 );
       t2->SetBranchAddress("clustersensorThickness",  &clustersensorThickness2 );
       t2->SetBranchAddress("tsosBdotY",  &tsosBdotY2 );
       t2->SetBranchAddress("clusterstripChargelocalpitch",  &clusterstripChargelocalpitch2 );
       t2->SetBranchAddress("clusterstripChargesensorThickness",  &clusterstripChargesensorThickness2 );
       t2->SetBranchAddress("clusterstripChargeBdotY",  &clusterstripChargeBdotY2 );
       t2->SetBranchAddress("tsosrhglobalphi",  &tsosrhglobalphi2 );
       //t2->SetBranchAddress("CTCmbtimeVtxr",  &CTCmbtimeVtxr2 );

   //data always first
    

   uint32_t evCount=0;
   
   cout << "in here a" << endl;
   Int_t nentries = (Int_t)t1->GetEntries();
   Int_t nentriesT2 = (Int_t)t2->GetEntries();
   cout << "entries " << nentries << "enstries 2" << nentriesT2 << endl;

   cout << "in here b" << endl;
   ///fill variables from tree 1
   for (Int_t e=0; e<nentries; e++) 
   {
       t1->GetEntry(e);
          
           //per cluster
           uint32_t up = partition->size();
           for(uint32_t k=0; k<up;k++)
           {
               if( partition->at(k) == sdId )
               {
                   if(clusterlayerwheel->at(k) > layerCutDown && clusterlayerwheel->at(k) < layerCutUp )
                   {
                       subpartition.push_back(partition->at(k));
                       subclustercharge.push_back(clustercharge->at(k));
                       subclusterwidth.push_back(clusterwidth->at(k));
                       subclusterlayerwheel.push_back(clusterlayerwheel->at(k));
                       subtsostrackPt.push_back(tsostrackPt->at(k));
                       subtsoslocalphi.push_back(tsoslocalphi->at(k));
                       subtsoslocaltheta.push_back(tsoslocaltheta->at(k));
                       subtsoslocalpitch.push_back(tsoslocalpitch->at(k));
                       subclustersensorThickness.push_back(clustersensorThickness->at(k));
                       subtsosBdotY.push_back(tsosBdotY->at(k));
                       subtsosrhglobalphi.push_back(tsosrhglobalphi->at(k));
                       //subCTCmbtimeVtxr.push_back(CTCmbtimeVtxr->at(k));
                   }
               }
           }
           //perstrip
           uint32_t upStrip = clusterstripChargeSubdetid->size();
           for(uint32_t k=0; k<upStrip;k++)
           {
               if( clusterstripChargeSubdetid->at(k) == sdId)
               {
                   if(clusterstripChargeLayerwheel->at(k) > layerCutDown && clusterstripChargeLayerwheel->at(k) < layerCutUp )
                   {
                       subclusterstripChargeSubdetid.push_back(clusterstripChargeSubdetid->at(k));
                       subclusterstripCharge.push_back(clusterstripCharge->at(k));
                       subclusterstripChargeLayerwheel.push_back(clusterstripChargeLayerwheel->at(k));
                       subclusterstripChargeStripNr.push_back(clusterstripChargeStripNr->at(k));
                       subclusterstripChargeTotWidth.push_back(clusterstripChargeTotWidth->at(k));
                       subclusterstripChargeTotCharge.push_back(clusterstripChargeTotCharge->at(k));
                       subclusterstripChargeLocalTrackPhi.push_back(clusterstripChargeLocalTrackPhi->at(k));
                       subclusterstripChargeGlobalTrackPhi.push_back(clusterstripChargeGlobalTrackPhi->at(k));
                       subclusterstripChargeLocalTrackTheta.push_back(clusterstripChargeLocalTrackTheta->at(k));
                       subclusterstripChargeGlobalTrackTheta.push_back(clusterstripChargeGlobalTrackTheta->at(k));
                       subclusterstripChargeDetid.push_back(clusterstripChargeDetid->at(k));
                       subclusterstripChargeLocalX.push_back(clusterstripChargeLocalX->at(k));
                       subclusterstripChargeLocalY.push_back(clusterstripChargeLocalY->at(k));
                       subclusterstripChargetrackPt.push_back(clusterstripChargetrackPt->at(k));
                       subclusterstripChargelocalpitch.push_back(clusterstripChargelocalpitch->at(k));
                       subclusterstripChargesensorThickness.push_back(clusterstripChargesensorThickness->at(k));
                       subclusterstripChargeBdotY.push_back(clusterstripChargeBdotY->at(k));
                   }
               }
           }


   }

   //fill variables from tree 2
   //for (Int_t e=0; e<58; e++) //test_shallowTrackClusterRunHMedPU.root  test_shallowTrackCluster900MC.root
   for (Int_t e=0; e<nentriesT2; e++) 
   {
       t2->GetEntry(e);

          //per cluster 
           uint32_t up = partition2->size();
           for(uint32_t k=0; k<up;k++)
           {

               if( partition2->at(k) == sdId)
               {
                   if(clusterlayerwheel2->at(k) > layerCutDown && clusterlayerwheel2->at(k) < layerCutUp )
                   {
                       subpartition2.push_back(partition2->at(k));
                       subclustercharge2.push_back(clustercharge2->at(k));
                       subclusterwidth2.push_back(clusterwidth2->at(k));
                       subclusterlayerwheel2.push_back(clusterlayerwheel2->at(k));
                       subtsostrackPt2.push_back(tsostrackPt2->at(k));
                       subtsoslocalphi2.push_back(tsoslocalphi2->at(k));
                       subtsoslocaltheta2.push_back(tsoslocaltheta2->at(k));
                       subtsoslocalpitch2.push_back(tsoslocalpitch2->at(k));
                       subclustersensorThickness2.push_back(clustersensorThickness2->at(k));
                       subtsosBdotY2.push_back(tsosBdotY2->at(k));
                       subtsosrhglobalphi2.push_back(tsosrhglobalphi2->at(k));
                       //subCTCmbtimeVtxr2.push_back(CTCmbtimeVtxr2->at(k));
                   }
               }
           }
           //perstrip
           uint32_t upStrip = clusterstripChargeSubdetid2->size();
           for(uint32_t k=0; k<upStrip;k++)
           {
               if( clusterstripChargeSubdetid2->at(k) == sdId)
               {
                   if(clusterstripChargeLayerwheel2->at(k) > layerCutDown && clusterstripChargeLayerwheel2->at(k) < layerCutUp )
                   {
                       subclusterstripChargeSubdetid2.push_back(clusterstripChargeSubdetid2->at(k));
                       subclusterstripCharge2.push_back(clusterstripCharge2->at(k));
                       subclusterstripChargeLayerwheel2.push_back(clusterstripChargeLayerwheel2->at(k));
                       subclusterstripChargeStripNr2.push_back(clusterstripChargeStripNr2->at(k));
                       subclusterstripChargeTotWidth2.push_back(clusterstripChargeTotWidth2->at(k));
                       subclusterstripChargeTotCharge2.push_back(clusterstripChargeTotCharge2->at(k));
                       subclusterstripChargeLocalTrackPhi2.push_back(clusterstripChargeLocalTrackPhi2->at(k));
                       subclusterstripChargeGlobalTrackPhi2.push_back(clusterstripChargeGlobalTrackPhi2->at(k));
                       subclusterstripChargeLocalTrackTheta2.push_back(clusterstripChargeLocalTrackTheta2->at(k));
                       subclusterstripChargeGlobalTrackTheta2.push_back(clusterstripChargeGlobalTrackTheta2->at(k));
                       subclusterstripChargeDetid2.push_back(clusterstripChargeDetid2->at(k));
                       subclusterstripChargeLocalX2.push_back(clusterstripChargeLocalX2->at(k));
                       subclusterstripChargeLocalY2.push_back(clusterstripChargeLocalY2->at(k));
                       subclusterstripChargetrackPt2.push_back(clusterstripChargetrackPt2->at(k));
                       subclusterstripChargelocalpitch2.push_back(clusterstripChargelocalpitch2->at(k));
                       subclusterstripChargesensorThickness2.push_back(clusterstripChargesensorThickness2->at(k));
                       subclusterstripChargeBdotY2.push_back(clusterstripChargeBdotY2->at(k));
                   }
               }
           }

   }



       TH1F* chargeForAllWidthsData = new TH1F("chargeForAllWidths", "chargeForAllWidths" , 100, 0, 1000 );
       TH1F* chargeForAllWidthsMC = new TH1F("chargeForAllWidthsMC", "chargeForAllWidthsMC" , 100, 0, 1000 );
       TH1F* chargeForWidth1Data = new TH1F("chargeForWidth1Data", "chargeForWidth1Data" , 100, 0, 1000 );
       TH1F* chargeForWidth1MC = new TH1F("chargeForWidth1MC", "chargeForWidth1MC" , 100, 0, 1000 );
       TH1F* chargeForWidth2Data = new TH1F("chargeForWidth2Data", "chargeForWidth2Data" , 100, 0, 1000 );
       TH1F* chargeForWidth2MC = new TH1F("chargeForWidth2MC", "chargeForWidth2MC" , 100, 0, 1000 );
       TH1F* chargeForWidth3Data = new TH1F("chargeForWidth3Data", "chargeForWidth3Data" , 100, 0, 1000 );
       TH1F* chargeForWidth3MC = new TH1F("chargeForWidth3MC", "chargeForWidth3MC" , 100, 0, 1000 );
       TH1F* chargeForWidthLargerThan3Data = new TH1F("chargeForWidthLargerThan3Data", "chargeForWidthLargerThan3Data" , 100, 0, 1000 );
       TH1F* chargeForWidthLargerThan3MC = new TH1F("chargeForWidthLargerThan3MC", "chargeForWidthLargerThan3MC" , 100, 0, 1000 );
 
       TH1F* chargeForLargePtData = new TH1F("chargeForLargePtData", "chargeForLargePtData" , 100, 0, 1000 );
       TH1F* chargeForLargePtMC = new TH1F("chargeForLargePtMC", "chargeForLargePtMC" , 100, 0, 1000 );
       TH1F* chargeForSmallPtData = new TH1F("chargeForSmallPtData", "chargeForSmallPtData" , 100, 0, 1000 );
       TH1F* chargeForSmallPtMC = new TH1F("chargeForSmallPtMC", "chargeForSmallPtMC" , 100, 0, 1000 );
       TH1F* widthForLargePtData = new TH1F("widthForLargePtData", "widthForLargePtData" , 15, 0, 15 );
       TH1F* widthForLargePtMC = new TH1F("widthForLargePtMC", "widthForLargePtMC" , 15, 0, 15 );
       TH1F* widthForSmallPtData = new TH1F("widthForSmallPtData", "widthForSmallPtData" , 15, 0, 15 );
       TH1F* widthForSmallPtMC = new TH1F("widthForSmallPtMC", "widthForSmallPtMC" , 15, 0, 15 );

       TProfile* clusterWidthAsFceTanPhiData = new TProfile("clusterWidthAsFceTanPhiData", "clusterWidthAsFceTanPhiData" , 1000, -15,15, 0, 30 );
       TProfile* clusterWidthAsFceTanThetaData = new TProfile("clusterWidthAsFceTanThetaData", "clusterWidthAsFceTanThetaData" , 50, -4, 4, 0, 30 );

       TProfile* clusterWidthAsFceTanPhiMC = new TProfile("clusterWidthAsFceTanPhiMC", "clusterWidthAsFceTanPhiMC" , 1000, -15, 15, 0, 30 );
       TProfile* clusterWidthAsFceTanThetaMC = new TProfile("clusterWidthAsFceTanThetaMC", "clusterWidthAsFceTanThetaMC" , 50, -4, 4, 0, 30 );

       TProfile* clusterWidthAsFceTanThetaLorData = new TProfile("clusterWidthAsFceTanThetaLorData", "clusterWidthAsFceTanThetaLorData" , 50, -1, 1, 0, 30 );
       TProfile* clusterWidthAsFceTanThetaLorMC = new TProfile("clusterWidthAsFceTanTheatLorMC", "clusterWidthAsFceTanThetaLorMC" , 50, -1, 1, 0, 30 );

       TH1F* clusterWidthAsFceTanThetaLorAssymetryData = new TH1F("clusterWidthAsFceTanThetaLorAssymetryData", "clusterWidthAsFceTanThetaLorAssymetryData" , 50, 0, 2);
       TH1F* clusterWidthAsFceTanThetaLorAssymetryMC = new TH1F("clusterWidthAsFceTanTheatLorAssymetryMC", "clusterWidthAsFceTanThetaLorAssymetryMC" ,  50, 0, 2 );


       TH1F* tanThetaLorForWidth1Data = new TH1F("tanThetaLorForWidth1Data", "tanThetaLorForWidth1Data" , 100, -2, 2 );
       TH1F* tanThetaLorForWidth1MC = new TH1F("tanThetaLorForWidth1MC", "tanThetaLorForWidth1MC" , 100, -2, 2 );

       
       TH2F* chargeVsWidthData = new TH2F("chargeVsWidthData", "chargeVsWidthData" , 150, 0, 1500, 20, 0 , 20 );
       TH2F* chargeVsWidthMC = new TH2F("chargeVsWidthMC", "chargeVsWidthMC" , 150, 0, 1500, 20, 0 , 20 );

       TH1F* narrowTrackClusterWidthData = new TH1F("narrowTrackClusterWidthData","narrowTrackClusterWidthData", 10, 0, 10);         
       TH1F* narrowTrackClusterWidthMC = new TH1F("narrowTrackClusterWidthMC","narrowTrackClusterWidthMC", 10, 0, 10);         

       
       TH1F* clusterWidthForTopModules = new TH1F("clusterWidthForTopModules","clusterWidthForTopModules", 10, 0, 10);         
       TH1F* clusterWidthForBottomModules = new TH1F("clusterWidthForBottomModules","clusterWidthForBottomModules", 10, 0, 10);         
       TH1F* nrclusterWidthForTopModules = new TH1F("nrclusterWidthForTopModules","nrclusterWidthForTopModules", 4, 0, 4);         
       TH1F* nrclusterWidthForBottomModules = new TH1F("nrclusterWidthForBottomModules","nrclusterWidthForBottomModules", 4, 0, 4);         
       TH1F* chargeclusterWidthForTopModules = new TH1F("chargeclusterWidthForTopModules","chargeclusterWidthForTopModules", 50, 0, 500);         
       TH1F* chargeclusterWidthForBottomModules = new TH1F("chargeclusterWidthForBottomModules","chargeclusterWidthForBottomModules", 50, 0, 500);         
       
       TProfile* clusterWidthAsFceOfTimingTop = new TProfile("clusterWidthAsFceOfTimingTop", "clusterWidthAsFceOfTimingTop" , 200, -100, 100, 0, 10 );
       TProfile* clusterWidthAsFceOfTimingBottom = new TProfile("clusterWidthAsFceOfTimingBottom", "clusterWidthAsFceOfTimingBottom" , 200, -100, 100, 0, 10 );
       TProfile* clusterChargeAsFceOfTimingTop = new TProfile("clusterChargeAsFceOfTimingTop", "clusterChargeAsFceOfTimingTop" , 200, -100, 100, 0, 1000 );
       TProfile* clusterChargeAsFceOfTimingBottom = new TProfile("clusterChargeAsFceOfTimingBottom", "clusterChargeAsFceOfTimingBottom" , 200, -100, 100, 0, 1000 );

    cout << "in here 2"  << endl;
       for(uint32_t m = 0; m<subclustercharge.size(); m++)
       {
           chargeForAllWidthsData->Fill(subclustercharge.at(m));
           chargeVsWidthData->Fill(subclustercharge.at(m), subclusterwidth.at(m));
           

 
           int factor = subtsosBdotY.at(m) > 0 ? 1 : -1;

           if( abs(tan(subtsoslocaltheta.at(m))*cos(subtsoslocalphi.at(m))) < narrowness*(subtsoslocalpitch.at(m)/subclustersensorThickness.at(m)) )
           {
               narrowTrackClusterWidthData->Fill(subclusterwidth.at(m));         
               if(subtsosrhglobalphi.at(m)>0)
               {
                   clusterWidthForTopModules->Fill(subclusterwidth.at(m));
                   chargeclusterWidthForTopModules->Fill(subclustercharge.at(m));
                   nrclusterWidthForTopModules->Fill(1);
                   /*(if(subclusterlayerwheel.at(m) == 3)
                   {
                       clusterWidthAsFceOfTimingTop->Fill( subCTCmbtimeVtxr.at(m),subclusterwidth.at(m));
                       clusterChargeAsFceOfTimingTop->Fill(subCTCmbtimeVtxr.at(m) ,subclustercharge.at(m));
                  }*/

               }
           }

           if(subclusterlayerwheel.at(m) == 3)
           {
               clusterWidthAsFceTanPhiData->Fill(tan(subtsoslocalphi.at(m)), subclusterwidth.at(m));
               clusterWidthAsFceTanThetaData->Fill(factor*tan(subtsoslocaltheta.at(m)), subclusterwidth.at(m));
               clusterWidthAsFceTanThetaLorData->Fill(factor*tan(subtsoslocaltheta.at(m))*cos(subtsoslocalphi.at(m)), subclusterwidth.at(m));
           }
           
           if(subclusterwidth.at(m) == 1)
           {
              chargeForWidth1Data->Fill(subclustercharge.at(m));
               if(subclusterlayerwheel.at(m) == 3)
               {
                  tanThetaLorForWidth1Data->Fill(factor*tan(subtsoslocaltheta.at(m))*cos(subtsoslocalphi.at(m)));
               }
           }
           if(subclusterwidth.at(m) == 2)
              chargeForWidth2Data->Fill(subclustercharge.at(m));
           if(subclusterwidth.at(m) == 3)
              chargeForWidth3Data->Fill(subclustercharge.at(m));
           if(subclusterwidth.at(m) > 3)
              chargeForWidthLargerThan3Data->Fill(subclustercharge.at(m));
           if(subtsostrackPt.at(m)>2.5)
           {
               chargeForLargePtData->Fill(subclustercharge.at(m));
               widthForLargePtData->Fill(subclusterwidth.at(m));
           }
           if(subtsostrackPt.at(m)<=2.5)
           {
               chargeForSmallPtData->Fill(subclustercharge.at(m));
               widthForSmallPtData->Fill(subclusterwidth.at(m));
           }
         
       }
       uint32_t NBinsProf = clusterWidthAsFceTanThetaLorData->GetNbinsX()/2;
       for(uint32_t x =0;  x<NBinsProf; x++)
       {
           double xvalue = clusterWidthAsFceTanThetaLorData->GetBinCenter(x+1);
           double yvalueLow = clusterWidthAsFceTanThetaLorData->GetBinContent(x+1);
           cout << "min LA value " << xvalue << " width  " << yvalueLow << endl;
           int binx = clusterWidthAsFceTanThetaLorData->FindBin(abs(xvalue));
           double yvalueUp = clusterWidthAsFceTanThetaLorData->GetBinContent(binx);
           cout << "plus LA value " << yvalueUp << " at bin " << binx << endl;
           double absValueDiff = yvalueUp - yvalueLow;
           cout << "width difference " << absValueDiff << endl;
           int binxDiff = clusterWidthAsFceTanThetaLorAssymetryData->FindBin(abs(xvalue) );
           cout << " bin to fill " << binxDiff << " with value " << absValueDiff << endl;
           clusterWidthAsFceTanThetaLorAssymetryData->SetBinContent(binxDiff, absValueDiff );
       }
   
    cout << "in here 3"  << endl;
       for(uint32_t m = 0; m<subclustercharge2.size(); m++)
       {
           chargeForAllWidthsMC->Fill(subclustercharge2.at(m));
           chargeVsWidthMC->Fill(subclustercharge2.at(m), subclusterwidth2.at(m));
           
           int factor = subtsosBdotY2.at(m) > 0 ? 1 : -1;

           if( abs(tan(subtsoslocaltheta2.at(m))*cos(subtsoslocalphi2.at(m))) < narrowness*(subtsoslocalpitch2.at(m)/subclustersensorThickness2.at(m)) )
           {
               narrowTrackClusterWidthMC->Fill(subclusterwidth2.at(m));         
               if(subtsosrhglobalphi2.at(m)<0)
               {
                   clusterWidthForBottomModules->Fill(subclusterwidth2.at(m));
                   chargeclusterWidthForBottomModules->Fill(subclustercharge2.at(m));
                   nrclusterWidthForBottomModules->Fill(2);
                   /*if(subclusterlayerwheel2.at(m) == 3)
                   {
                       clusterWidthAsFceOfTimingBottom->Fill( subCTCmbtimeVtxr2.at(m),subclusterwidth2.at(m));
                       clusterChargeAsFceOfTimingBottom->Fill(subCTCmbtimeVtxr2.at(m) ,subclustercharge2.at(m));
                  }*/
               }
           }

           if(subclusterlayerwheel2.at(m) == 3)
           {
               clusterWidthAsFceTanPhiMC->Fill(tan(subtsoslocalphi2.at(m)), subclusterwidth2.at(m));
               clusterWidthAsFceTanThetaMC->Fill(factor*tan(subtsoslocaltheta2.at(m)), subclusterwidth2.at(m));
               clusterWidthAsFceTanThetaLorMC->Fill(factor*tan(subtsoslocaltheta2.at(m))*cos(subtsoslocalphi2.at(m)), subclusterwidth2.at(m));
           }

           if(subclusterwidth2.at(m) == 1)
           {
              chargeForWidth1MC->Fill(subclustercharge2.at(m));
              if(subclusterlayerwheel2.at(m) == 3)
              {
                  tanThetaLorForWidth1MC->Fill(factor*tan(subtsoslocaltheta2.at(m))*cos(subtsoslocalphi2.at(m)));
              }
           }
           if(subclusterwidth2.at(m) == 2)
              chargeForWidth2MC->Fill(subclustercharge2.at(m));
           if(subclusterwidth2.at(m) == 3)
              chargeForWidth3MC->Fill(subclustercharge2.at(m));
           if(subclusterwidth2.at(m) > 3)
              chargeForWidthLargerThan3MC->Fill(subclustercharge2.at(m));
           if(subtsostrackPt2.at(m)>2.5)
           {
               chargeForLargePtMC->Fill(subclustercharge2.at(m));
               widthForLargePtMC->Fill(subclusterwidth2.at(m));
           }
           if(subtsostrackPt2.at(m)<=2.5)
           {
               chargeForSmallPtMC->Fill(subclustercharge2.at(m));
               widthForSmallPtMC->Fill(subclusterwidth2.at(m));
           }
       }
    cout << "in here 4"  << endl;
       uint32_t NBinsProf2 = clusterWidthAsFceTanThetaLorMC->GetNbinsX()/2;
       for(uint32_t x =0;  x<NBinsProf2; x++)
       {
           double xvalue = clusterWidthAsFceTanThetaLorMC->GetBinCenter(x+1);
           double yvalueLow = clusterWidthAsFceTanThetaLorMC->GetBinContent(x+1);
           int binx = clusterWidthAsFceTanThetaLorMC->FindBin(abs(xvalue));
           double yvalueUp = clusterWidthAsFceTanThetaLorMC->GetBinContent(binx);
           double absValueDiff = yvalueUp - yvalueLow;
           int binxDiff = clusterWidthAsFceTanThetaLorAssymetryMC->FindBin(abs(xvalue) );
           clusterWidthAsFceTanThetaLorAssymetryMC->SetBinContent(binxDiff, absValueDiff );
           //double absValueDiff2 = clusterWidthAsFceTanThetaLorMC->GetBinContent(NBinsProf2-x)-clusterWidthAsFceTanThetaLorMC->GetBinContent(x+1);
           //clusterWidthAsFceTanThetaLorAssymetryMC->SetBinContent(NBinsProf2-x, absValueDiff2 );
       }

       TH1F* chargePerStripData = new TH1F("chargePerStripiData", "chargePerStripData" , 300, 0, 300 );
       TH1F* chargePerStripMC = new TH1F("chargePerStripMC", "chargePerStripMC" , 300, 0, 300 );

       vector<float> stripChargeVec;
       vector<float> stripChargeVec2;
       TH1F* narrowTrackSharing1Data = new TH1F("narrowTrackSharing1Data", "narrowTrackSharing1Data" , 100, 0, 1 );
       TH1F* narrowTrackSharing1MC = new TH1F("narrowTrackSharing1MC", "narrowTrackSharing1MC" , 100, 0, 1 );
       TH1F* narrowTrackSharing2Data = new TH1F("narrowTrackSharing2Data", "narrowTrackSharing2Data" , 100, 0, 1 );
       TH1F* narrowTrackSharing2MC = new TH1F("narrowTrackSharing2MC", "narrowTrackSharing2MC" , 100, 0, 1 );

       for(uint32_t m = 0; m<subclusterstripCharge.size(); m++)
       {
           chargePerStripData->Fill(subclusterstripCharge.at(m));
           
           if( abs(tan(subclusterstripChargeLocalTrackTheta.at(m))*cos(subclusterstripChargeLocalTrackPhi.at(m))) < narrowness*(subclusterstripChargelocalpitch.at(m)/subclusterstripChargesensorThickness.at(m)) )
           {
               cout << "after good track selection" << endl;
               stripChargeVec.push_back(subclusterstripCharge.at(m));
               cout << "width " << subclusterstripChargeTotWidth.at(m) << " size of vector " << stripChargeVec.size() << endl;
               if(subclusterstripChargeTotWidth.at(m) == stripChargeVec.size())
               {
                   cout << " to fill " << endl; 
                   float maxVal = 0;
                   int indexVal = -1;
                   for( uint32_t s =0; s<stripChargeVec.size(); s++)
                   {
                       if(stripChargeVec.at(s) > maxVal)
                       {
                           maxVal = stripChargeVec.at(s);
                           indexVal = s;
                       }

                   }
                   if(indexVal-1>=0)
                   {
                       narrowTrackSharing1Data->Fill((float)stripChargeVec.at(indexVal-1)/maxVal);
                       cout << " filled with " << (float)stripChargeVec.at(indexVal-1)/maxVal << endl;
                   }
                   if(indexVal+1<stripChargeVec.size())
                       narrowTrackSharing1Data->Fill((float)stripChargeVec.at(indexVal+1)/maxVal);
                   if(indexVal-2>=0)
                       narrowTrackSharing2Data->Fill((float)stripChargeVec.at(indexVal-2)/maxVal);
                   if(indexVal+2<stripChargeVec.size())
                       narrowTrackSharing2Data->Fill((float)stripChargeVec.at(indexVal+2)/maxVal);

                   stripChargeVec.clear();
               }
           }

       }
       for(uint32_t m = 0; m<subclusterstripCharge2.size(); m++)
       {
           chargePerStripMC->Fill(subclusterstripCharge2.at(m));

           if( abs(tan(subclusterstripChargeLocalTrackTheta2.at(m))*cos(subclusterstripChargeLocalTrackPhi2.at(m))) < narrowness*(subclusterstripChargelocalpitch2.at(m)/subclusterstripChargesensorThickness2.at(m)) )
           {
               stripChargeVec2.push_back(subclusterstripCharge2.at(m));
               if(subclusterstripChargeTotWidth2.at(m) == stripChargeVec2.size())
               {
                   float maxVal = 0;
                   int indexVal = -1;
                   for( uint32_t s =0; s<stripChargeVec2.size(); s++)
                   {
                       if(stripChargeVec2.at(s) > maxVal)
                       {
                           maxVal = stripChargeVec2.at(s);
                           indexVal = s;
                       }

                   }
                   if(indexVal-1>=0)
                       narrowTrackSharing1MC->Fill((float)stripChargeVec2.at(indexVal-1)/maxVal);
                   if(indexVal+1<stripChargeVec2.size())
                       narrowTrackSharing1MC->Fill((float)stripChargeVec2.at(indexVal+1)/maxVal);
                   if(indexVal-2>=0)
                       narrowTrackSharing2MC->Fill((float)stripChargeVec2.at(indexVal-2)/maxVal);
                   if(indexVal+2<stripChargeVec2.size())
                       narrowTrackSharing2MC->Fill((float)stripChargeVec2.at(indexVal+2)/maxVal);

                   stripChargeVec2.clear();
               }
           }
       }


       ////distributions per strip
       TProfile* leadingStripProfileData = new TProfile("leadingcluschargeData", "leadingcluschargeData", 550, 0, 550, 0, 300);
       TH1D* leadingStripSumData = new TH1D("leadingclusSumData", "leadingclusSumData", 800, 0, 800);
       float lstripNr = 0; 
       float lstripCh = 0; 
       float lClusWidth = 0 ; 
       float lClusCharge = 0 ; 
       uint32_t stripCounter = 0; 
       bool clusterEnd = true;  
       vector<double> stripChargeSum;
       stripChargeSum.resize(512,0);


       TH1F* stripChargeSharingData = new TH1F("stripChargeSharingData", "stripChargeSharingData", 100, 0, 1 );
       TH1F* stripChargeSharingEtaData = new TH1F("stripChargeSharingEtaData", "stripChargeSharingEtaData", 100, 0, 1 );
       int32_t indexToSkip = -1;

       vector<float> stripChargeSharing3Vec;
       TH1F* stripChargeSharing3Data = new TH1F("stripChargeSharing3Data", "stripChargeSharing3Data", 100, 0, 1 );


       TProfile* clusterStripCahrgeAsFceTanPhiData = new TProfile("clusterStripCahrgeAsFceTanPhiData", "clusterStripCahrgeAsFceTanPhiData" , 1000, -15,15, 0, 300 );
       TProfile* clusterStripCahrgeAsFceTanThetaData = new TProfile("clusterStripCahrgeAsFceTanThetaData", "clusterStripCahrgeAsFceTanThetaData" , 50, -4, 4, 0, 300 );

       TProfile* clusterStripCahrgeAsFceTanPhiMC = new TProfile("clusterStripCahrgeAsFceTanPhiMC", "clusterStripCahrgeAsFceTanPhiMC" , 1000, -15, 15, 0, 300 );
       TProfile* clusterStripCahrgeAsFceTanThetaMC = new TProfile("clusterStripCahrgeAsFceTanThetaMC", "clusterStripCahrgeAsFceTanThetaMC" , 50, -4, 4, 0, 300 );


       TProfile* clusterStripCahrgeAsFceTanThetaLorData = new TProfile("clusterStripCahrgeAsFceTanThetaLorData", "clusterStripCahrgeAsFceTanThetaLorData" , 50, -2, 2, 0, 300 );
       TProfile* clusterStripCahrgeAsFceTanThetaLorMC = new TProfile("clusterStripCahrgeAsFceTanThetaLorMC", "clusterStripCahrgeAsFceTanThetaLorMC" , 50, -2, 2, 0, 300 );

       vector<float> clusterVector;
       TProfile* clusterShapeData = new TProfile("clusterShapeData", "clusterShapeData", 40, -20, 20, 0, 300);
       TProfile* clusterShapeMT8Data = new TProfile("clusterShapeMT8Data", "clusterShapeMT8Data", 40, -20, 20, 0, 300);
       TProfile* clusterShapeLT7Data = new TProfile("clusterShapeML7Data", "clusterShapeLT7Data", 40, -20, 20, 0, 300);
       TProfile* clusterShape2Data = new TProfile("clusterShape2Data", "clusterShape2Data", 40, -20, 20, 0, 300);
       TProfile* clusterShape3Data = new TProfile("clusterShape3Data", "clusterShape3Data", 40, -20, 20, 0, 300);
       TProfile* clusterShape5Data = new TProfile("clusterShape5Data", "clusterShape5Data", 40, -20, 20, 0, 300);

       TProfile* clusterShapeMC = new TProfile("clusterShapeMC", "clusterShapeMC", 40, -20, 20, 0, 300);
       TProfile* clusterShapeMT8MC = new TProfile("clusterShapeMT8MC", "clusterShapeMT8MC", 40, -20, 20, 0, 300);
       TProfile* clusterShapeLT7MC = new TProfile("clusterShapeLT7MC", "clusterShapeLT7MC", 40, -20, 20, 0, 300);
       TProfile* clusterShape2MC = new TProfile("clusterShape2MC", "clusterShape2MC", 40, -20, 20, 0, 300);
       TProfile* clusterShape3MC = new TProfile("clusterShape3MC", "clusterShape3MC", 40, -20, 20, 0, 300);
       TProfile* clusterShape5MC = new TProfile("clusterShape5MC", "clusterShape5MC", 40, -20, 20, 0, 300);

       TProfile* clusterShapeDataPositive = new TProfile("clusterShapeDataPositive", "clusterShapeDataPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeDataPositiveChandi = new TProfile("clusterShapeDataPositiveChandi", "clusterShapeDataPositiveChandi", 40, 0, 40, 0, 300);//missing "S"
       TProfile* clusterShapeMT8DataPositive = new TProfile("clusterShapeMT8DataPositive", "clusterShapeMT8DataPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeLT7DataPositive = new TProfile("clusterShapeML7DataPositive", "clusterShapeLT7DataPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape2DataPositive = new TProfile("clusterShape2DataPositive", "clusterShape2DataPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape3DataPositive = new TProfile("clusterShape3DataPositive", "clusterShape3DataPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape5DataPositive = new TProfile("clusterShape5DataPositive", "clusterShape5DataPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape6DataPositive = new TProfile("clusterShape6DataPositive", "clusterShape6DataPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape7DataPositive = new TProfile("clusterShape7DataPositive", "clusterShape7DataPositive", 40, 0, 40, 0, 300, "S");

       TProfile* clusterShapeMCPositive = new TProfile("clusterShapeMCPositive", "clusterShapeMCPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeMCPositiveChandi = new TProfile("clusterShapeMCPositiveChandi", "clusterShapeMCPositiveChandi", 40, 0, 40, 0, 300);
       TProfile* clusterShapeMT8MCPositive = new TProfile("clusterShapeMT8MCPositive", "clusterShapeMT8MCPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeLT7MCPositive = new TProfile("clusterShapeLT7MCPositive", "clusterShapeLT7MCPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape2MCPositive = new TProfile("clusterShape2MCPositive", "clusterShape2MCPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape3MCPositive = new TProfile("clusterShape3MCPositive", "clusterShape3MCPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape5MCPositive = new TProfile("clusterShape5MCPositive", "clusterShape5MCPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape6MCPositive = new TProfile("clusterShape6MCPositive", "clusterShape6MCPositive", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape7MCPositive = new TProfile("clusterShape7MCPositive", "clusterShape7MCPositive", 40, 0, 40, 0, 300, "S");

       TProfile* clusterShapeDataNegative = new TProfile("clusterShapeDataNegative", "clusterShapeDataNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeDataNegativeChandi = new TProfile("clusterShapeDataNegativeChandi", "clusterShapeDataNegativeChandi", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeDataNegativeChandiCorr = new TProfile("clusterShapeDataNegativeChandiCorr", "clusterShapeDataNegativeChandiCorr", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeMT8DataNegative = new TProfile("clusterShapeMT8DataNegative", "clusterShapeMT8DataNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeLT7DataNegative = new TProfile("clusterShapeML7DataNegative", "clusterShapeLT7DataNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape2DataNegative = new TProfile("clusterShape2DataNegative", "clusterShape2DataNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape3DataNegative = new TProfile("clusterShape3DataNegative", "clusterShape3DataNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape5DataNegative = new TProfile("clusterShape5DataNegative", "clusterShape5DataNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape6DataNegative = new TProfile("clusterShape6DataNegative", "clusterShape6DataNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape7DataNegative = new TProfile("clusterShape7DataNegative", "clusterShape7DataNegative", 40, 0, 40, 0, 300, "S");

       TProfile* clusterShapeMCNegative = new TProfile("clusterShapeMCNegative", "clusterShapeMCNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeMCNegativeChandi = new TProfile("clusterShapeMCNegativeChandi", "clusterShapeMCNegativeChandi", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeMCNegativeChandiCorr = new TProfile("clusterShapeMCNegativeChandiCorr", "clusterShapeMCNegativeChandiCorr", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeMT8MCNegative = new TProfile("clusterShapeMT8MCNegative", "clusterShapeMT8MCNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShapeLT7MCNegative = new TProfile("clusterShapeLT7MCNegative", "clusterShapeLT7MCNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape2MCNegative = new TProfile("clusterShape2MCNegative", "clusterShape2MCNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape3MCNegative = new TProfile("clusterShape3MCNegative", "clusterShape3MCNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape5MCNegative = new TProfile("clusterShape5MCNegative", "clusterShape5MCNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape6MCNegative = new TProfile("clusterShape6MCNegative", "clusterShape6MCNegative", 40, 0, 40, 0, 300, "S");
       TProfile* clusterShape7MCNegative = new TProfile("clusterShape7MCNegative", "clusterShape7MCNegative", 40, 0, 40, 0, 300, "S");


       TH1F* clusterChargeWOSaturationData = new TH1F("clusterChargeWOSaturationData", "clusterChargeWOSaturationData", 100, 0, 1000 );
       TH1F* clusterWidthWOSaturationData = new TH1F("clusterWidthWOSaturationData", "clusterWidthWOSaturationData", 15, 0, 15 );
       TH1F* clusterChargePerStripWOSaturationData = new TH1F("clusterChargePerStripWOSaturationData", "clusterChargePerStripWOSaturationData", 300, 0, 300 );

       TH1F* clusterChargeWOSaturationMC = new TH1F("clusterChargeWOSaturationMC", "clusterChargeWOSaturationMC", 100, 0, 1000 );
       TH1F* clusterWidthWOSaturationMC = new TH1F("clusterWidthWOSaturationMC", "clusterWidthWOSaturationMC", 15, 0, 15 );
       TH1F* clusterChargePerStripWOSaturationMC = new TH1F("clusterChargePerStripWOSaturationMC", "clusterChargePerStripWOSaturationMC", 300, 0, 300 );

       for(uint32_t m = 0; m<subclusterstripChargeLayerwheel.size(); m++)
       {
           if(subclusterstripChargeLayerwheel.at(m) == 3) //@MJ@ TODO normally 1
           {
               if(lClusWidth==0 || clusterEnd==true )
               {
                   lstripNr = subclusterstripChargeStripNr.at(m);
                   lstripCh = subclusterstripCharge.at(m);
                   lClusWidth = subclusterstripChargeTotWidth.at(m);
                   lClusCharge = subclusterstripChargeTotCharge.at(m);
                   //cout << "cluster inital charge " << lstripCh << " for cluster width " << lClusWidth << "  m " << m << endl;
                   stripCounter = 1; 
                   clusterVector.clear();
               }
     
               if(stripCounter <= lClusWidth)
               {
                   clusterEnd = false;
                   if(lstripCh<subclusterstripCharge.at(m))
                   {
                       lstripNr = subclusterstripChargeStripNr.at(m);
                       lstripCh = subclusterstripCharge.at(m);
                   //cout << "cluster charge changed to " << lstripCh << " m " << m << endl;
                   }
                   clusterVector.push_back(subclusterstripCharge.at(m)) ;

               
                   if(stripCounter == lClusWidth)
                   {
                       //cout << "cluster charge final into profile " << lstripCh << " m " << m << endl;
                       leadingStripProfileData->Fill(lstripNr, lstripCh);
                       clusterStripCahrgeAsFceTanPhiData->Fill(tan(subclusterstripChargeLocalTrackPhi.at(m)), lstripCh);
                       clusterStripCahrgeAsFceTanThetaData->Fill(tan(subclusterstripChargeLocalTrackTheta.at(m)), lstripCh);
                       clusterStripCahrgeAsFceTanThetaLorData->Fill(tan(subclusterstripChargeLocalTrackTheta.at(m))*cos(subclusterstripChargeLocalTrackPhi.at(m)) , lstripCh);
                       double prev = stripChargeSum.at(lstripNr);
                       stripChargeSum.at(lstripNr) = prev+lstripCh;
                       float maxChrg = 0;
                       int32_t maxChrgCtr = -1;
                       for(uint32_t ch=0; ch<clusterVector.size();ch++)
                       {
                           if(maxChrg < clusterVector.at(ch))
                           {
                               maxChrg = clusterVector.at(ch);
                               maxChrgCtr = ch;
                           }
                       }
                       if(maxChrg < 253)
                       {
                           clusterWidthWOSaturationData->Fill(lClusWidth);
                           clusterChargeWOSaturationData->Fill(lClusCharge);
                       }
                       for(uint32_t ch=0; ch<clusterVector.size();ch++)
                       {
                           
                           if(maxChrg < 253)
                               clusterChargePerStripWOSaturationData->Fill(clusterVector.at(ch));
                           int32_t positionValue = ch-(maxChrgCtr);
                           //cout << "charge position " << positionValue << " chareg " << clusterVector.at(ch) << endl;
                           clusterShapeData->Fill( positionValue ,clusterVector.at(ch) );
                           if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                               clusterShapeDataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                           if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                               clusterShapeDataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           if(lClusWidth>3)
                           {
                           if(subclusterstripChargeLocalTrackTheta.at(m)> TMath::Pi()*(3.0/4.0) && subclusterstripChargeLocalTrackTheta.at(m)< TMath::Pi())
                               clusterShapeDataNegativeChandi->Fill( ch+1 ,clusterVector.at(ch) );
                           if(subclusterstripChargeLocalTrackTheta.at(m)> TMath::Pi()/2 && subclusterstripChargeLocalTrackTheta.at(m)< TMath::Pi()*(3.0/4.0))
                               clusterShapeDataNegativeChandiCorr->Fill( ch+1 ,clusterVector.at(ch) );
                           if(subclusterstripChargeLocalTrackTheta.at(m)> TMath::Pi()/4 && subclusterstripChargeLocalTrackTheta.at(m)< TMath::Pi()/2)
                               clusterShapeDataPositiveChandi->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                           if(lClusWidth>8)
                           {
                               clusterShapeMT8Data->Fill( positionValue ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                                   clusterShapeMT8DataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                                   clusterShapeMT8DataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                           if(lClusWidth<7)
                           {
                               clusterShapeLT7Data->Fill( positionValue ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                                   clusterShapeLT7DataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                                   clusterShapeLT7DataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                           if(lClusWidth==2)
                           {
                               clusterShape2Data->Fill( positionValue ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                                   clusterShape2DataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                                   clusterShape2DataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                           if(lClusWidth==3)
                           {
                               clusterShape3Data->Fill( positionValue ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                                   clusterShape3DataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                                   clusterShape3DataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                           if(lClusWidth==5)
                           {
                               clusterShape5Data->Fill( positionValue ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                                   clusterShape5DataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                                   clusterShape5DataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                           if(lClusWidth==6)
                           {
                               if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                                   clusterShape6DataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                                   clusterShape6DataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                           if(lClusWidth==7)
                           {
                               if( subclusterstripChargeLocalTrackPhi.at(m)>= 0)
                                   clusterShape7DataPositive->Fill( ch+1 ,clusterVector.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi.at(m)< 0)
                                   clusterShape7DataNegative->Fill( ch+1 ,clusterVector.at(ch) );
                           }
                       }
                       clusterVector.clear();
                       clusterEnd =true;
                   }
                   stripCounter++;
               }
           }

           if(subclusterstripChargeTotWidth.at(m) == 2)
           {
               if(m != indexToSkip )
               {
                   float strip1 = subclusterstripCharge.at(m);
                   float strip2 = subclusterstripCharge.at(m+1);
                   float sratio = strip1 > strip2 ? strip2/strip1 : strip1/strip2;
                   float sratioEta = strip1 > strip2 ? strip1/(strip1+strip2) : strip2/(strip1+strip2);
                   stripChargeSharingData->Fill(sratio);
                   stripChargeSharingEtaData->Fill(sratioEta);
                   indexToSkip = m+1;
               }

           }
           if(subclusterstripChargeTotWidth.at(m) == 3)
           {
               stripChargeSharing3Vec.push_back(subclusterstripCharge.at(m));
               if( stripChargeSharing3Vec.size() == 3  )
               {
                   float sharingVal = ( stripChargeSharing3Vec.at(0) + stripChargeSharing3Vec.at(2) )/ subclusterstripChargeTotCharge.at(m)  ;
                   if(stripChargeSharing3Vec.at(1) > stripChargeSharing3Vec.at(0) && stripChargeSharing3Vec.at(1) > stripChargeSharing3Vec.at(2)  )
                        stripChargeSharing3Data->Fill(sharingVal);

                   stripChargeSharing3Vec.clear();
               }

           }
           
       }
       TProfile* leadingStripProfileMC = new TProfile("leadingcluschargeMC", "leadingcluschargeMC", 800, 0, 800, 0, 300);
       TH1D* leadingStripSumMC = new TH1D("leadingclusSumMC", "leadingclusSumMC", 800, 0, 800);
       float lstripNr2 = 0; 
       float lstripCh2 = 0; 
       float lClusWidth2 = 0 ; 
       float lClusCharge2 = 0 ; 
       uint32_t stripCounter2 = 0; 
       bool clusterEnd2 = true;  
       vector<double> stripChargeSum2;
       stripChargeSum2.resize(512,0);
       TH1F* stripChargeSharingMC = new TH1F("stripChargeSharingMC", "stripChargeSharingMC", 100, 0, 1 );
       TH1F* stripChargeSharingEtaMC = new TH1F("stripChargeSharingEtaMC", "stripChargeSharingEtaMC", 100, 0, 1 );
       int32_t indexToSkip2 = -1;

       vector<float> stripChargeSharing3Vec2;
       TH1F* stripChargeSharing3MC = new TH1F("stripChargeSharing3MC", "stripChargeSharing3MC", 100, 0, 1 );

       vector<float> clusterVector2;
       for(uint32_t m = 0; m<subclusterstripChargeLayerwheel2.size(); m++)
       {
           if(subclusterstripChargeLayerwheel2.at(m) == 3) //@MJ@ TODO 1 normally
           {
               if(lClusWidth2==0 || clusterEnd2==true )
               {
                   lstripNr2 = subclusterstripChargeStripNr2.at(m);
                   lstripCh2 = subclusterstripCharge2.at(m);
                   lClusWidth2 = subclusterstripChargeTotWidth2.at(m);
                   lClusCharge2 = subclusterstripChargeTotCharge2.at(m);
                   stripCounter2 = 1;
                   clusterVector2.clear();
               }
     
               if(stripCounter2 <= lClusWidth2)
               {
                   clusterEnd2 = false;
                   if(lstripCh2<subclusterstripCharge2.at(m))
                   {
                       lstripNr2 = subclusterstripChargeStripNr2.at(m);
                       lstripCh2 = subclusterstripCharge2.at(m);
                   }
                   clusterVector2.push_back(subclusterstripCharge2.at(m)); 

               
                   if(stripCounter2 == lClusWidth2)
                   {
                       leadingStripProfileMC->Fill(lstripNr2, lstripCh2);
                       clusterStripCahrgeAsFceTanPhiMC->Fill(tan(subclusterstripChargeLocalTrackPhi2.at(m)), lstripCh2);
                       clusterStripCahrgeAsFceTanThetaMC->Fill(tan(subclusterstripChargeLocalTrackTheta2.at(m)), lstripCh2);
                       clusterStripCahrgeAsFceTanThetaLorMC->Fill(tan(subclusterstripChargeLocalTrackTheta2.at(m))*cos(subclusterstripChargeLocalTrackPhi2.at(m)), lstripCh2);
                       double prev2 = stripChargeSum2.at(lstripNr2);
                       stripChargeSum2.at(lstripNr2) = prev2+lstripCh2; 
                       float maxChrg = 0;
                       int32_t maxChrgCtr = -1;
                       for(uint32_t ch=0; ch<clusterVector2.size();ch++)
                       {
                           if(maxChrg < clusterVector2.at(ch))
                           {
                               maxChrg = clusterVector2.at(ch);
                               maxChrgCtr = ch;
                           }
                       }
                       if(maxChrg < 253)
                       {
                           clusterWidthWOSaturationMC->Fill(lClusWidth2);
                           clusterChargeWOSaturationMC->Fill(lClusCharge2);
                       }
                       for(uint32_t ch=0; ch<clusterVector2.size();ch++)
                       {
                           if(maxChrg < 253)
                               clusterChargePerStripWOSaturationMC->Fill(clusterVector2.at(ch));
                           int32_t positionValue = ch-(maxChrgCtr);
                           clusterShapeMC->Fill(positionValue,clusterVector2.at(ch) );
                           if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                               clusterShapeMCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                           if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                               clusterShapeMCNegative->Fill( ch+1 ,clusterVector2.at(ch) );

                           if(lClusWidth2>3)
                           {
                           if(subclusterstripChargeLocalTrackTheta2.at(m)> TMath::Pi()*(3.0/4.0) && subclusterstripChargeLocalTrackTheta2.at(m)< TMath::Pi())
                               clusterShapeMCNegativeChandi->Fill( ch+1 ,clusterVector2.at(ch) );
                           if(subclusterstripChargeLocalTrackTheta2.at(m)> TMath::Pi()/2 && subclusterstripChargeLocalTrackTheta2.at(m)< TMath::Pi()*(3.0/4.0))
                               clusterShapeMCNegativeChandiCorr->Fill( ch+1 ,clusterVector2.at(ch) );
                           if(subclusterstripChargeLocalTrackTheta2.at(m)> TMath::Pi()/4 && subclusterstripChargeLocalTrackTheta2.at(m)< TMath::Pi()/2)
                               clusterShapeMCPositiveChandi->Fill( ch+1 ,clusterVector2.at(ch) );
                           }
                           if(lClusWidth2>8)
                           {
                               clusterShapeMT8MC->Fill( positionValue ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                                   clusterShapeMT8MCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                                   clusterShapeMT8MCNegative->Fill( ch+1 ,clusterVector2.at(ch) );

                           }
                           if(lClusWidth2<7)
                           {
                               clusterShapeLT7MC->Fill( positionValue ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                                   clusterShapeLT7MCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                                   clusterShapeLT7MCNegative->Fill( ch+1 ,clusterVector2.at(ch) );
                           }
                           if(lClusWidth2==2)
                           {
                               clusterShape2MC->Fill( positionValue ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                                   clusterShape2MCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                                   clusterShape2MCNegative->Fill( ch+1 ,clusterVector2.at(ch) );
                           }
                           if(lClusWidth2==3)
                           {
                               clusterShape3MC->Fill( positionValue ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                                   clusterShape3MCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                                   clusterShape3MCNegative->Fill( ch+1 ,clusterVector2.at(ch) );
                           }
                           if(lClusWidth2==5)
                           {
                               clusterShape5MC->Fill( positionValue ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                                   clusterShape5MCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                                   clusterShape5MCNegative->Fill( ch+1 ,clusterVector2.at(ch) );
                           }
                           if(lClusWidth2==6)
                           {
                               if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                                   clusterShape6MCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                                   clusterShape6MCNegative->Fill( ch+1 ,clusterVector2.at(ch) );
                           }
                           if(lClusWidth2==7)
                           {
                               if( subclusterstripChargeLocalTrackPhi2.at(m)>= 0)
                                   clusterShape7MCPositive->Fill( ch+1 ,clusterVector2.at(ch) );
                               if( subclusterstripChargeLocalTrackPhi2.at(m)< 0)
                                   clusterShape7MCNegative->Fill( ch+1 ,clusterVector2.at(ch) );
                           }
                       }
                       clusterVector2.clear();
                       clusterEnd2 =true;
                   }
                   stripCounter2++;
               }
           }
           if(subclusterstripChargeTotWidth2.at(m) == 2)
           {
               if(m != indexToSkip2 )
               {
                   float strip1 = subclusterstripCharge2.at(m);
                   float strip2 = subclusterstripCharge2.at(m+1);
                   float sratio = strip1 > strip2 ? strip2/strip1 : strip1/strip2;
                   float sratioEta = strip1 > strip2 ? strip1/(strip1+strip2) : strip2/(strip1+strip2);
                   stripChargeSharingMC->Fill(sratio);
                   stripChargeSharingEtaMC->Fill(sratioEta);
                   indexToSkip2 = m+1;
               }

           }
           if(subclusterstripChargeTotWidth2.at(m) == 3)
           {
               stripChargeSharing3Vec2.push_back(subclusterstripCharge2.at(m));
               if( stripChargeSharing3Vec2.size() == 3  )
               {
                   float sharingVal = ( stripChargeSharing3Vec2.at(0) + stripChargeSharing3Vec2.at(2) )/ subclusterstripChargeTotCharge2.at(m)  ;
                   if(stripChargeSharing3Vec2.at(1) > stripChargeSharing3Vec2.at(0) && stripChargeSharing3Vec2.at(1) > stripChargeSharing3Vec2.at(2)  )
                        stripChargeSharing3MC->Fill(sharingVal);

                   stripChargeSharing3Vec2.clear();
               }

           }
           
       }
      
       for(uint32_t s=0; s<stripChargeSum.size(); s++)
       {
           //cout << "charge on strip s data"<< stripChargeSum.at(s) << " mc " << stripChargeSum2.at(s) << endl;
           leadingStripSumData->SetBinContent(s+1,stripChargeSum.at(s));
           leadingStripSumMC->SetBinContent(s+1,stripChargeSum2.at(s));

       }


        
       TH1F* widthTOBl6Data = new TH1F("widthTOBl6", "widthTOBl6" , 15, 0, 15 );
       TH1F* widthTOBl5Data = new TH1F("widthTOBl5", "widthTOBl5" , 15, 0, 15 );
       TH1F* widthTOBl4Data = new TH1F("widthTOBl4", "widthTOBl4" , 15, 0, 15 );
       TH1F* widthTOBl1Data = new TH1F("widthTOBl1", "widthTOBl1" , 15, 0, 15 );

       for(uint32_t m = 0; m<subclusterwidth.size(); m++)
       {
             
           if(subclusterlayerwheel.at(m) == 1)
           {
               widthTOBl1Data->Fill(subclusterwidth.at(m));
               //cout << "filled l1" << " width " << subclusterwidth.at(m) << endl;
           }
           if(subclusterlayerwheel.at(m) == 5)
           {
               widthTOBl5Data->Fill(subclusterwidth.at(m));
               //cout << "filled l5 width " << subclusterwidth.at(m) << endl;
           }
           if(subclusterlayerwheel.at(m) == 6)
           {
               widthTOBl6Data->Fill(subclusterwidth.at(m));
               //cout << "filled l6 width " << subclusterwidth.at(m) << endl;
           }
           if(subclusterlayerwheel.at(m) == 4)
           {
               widthTOBl4Data->Fill(subclusterwidth.at(m));
               //cout << "filled l4 width " << subclusterwidth.at(m) << endl;
           }
       }
       double norm1 = widthTOBl1Data->Integral();
       widthTOBl1Data->Scale(1/norm1);
       widthTOBl1Data->SetLineColor(kRed);
       double norm2 = widthTOBl5Data->Integral();
       widthTOBl5Data->Scale(1/norm2);
       widthTOBl5Data->SetLineColor(kRed);
       double norm5 = widthTOBl4Data->Integral();
       widthTOBl4Data->Scale(1/norm5);
       widthTOBl4Data->SetLineColor(kGreen);
       double norm7 = widthTOBl6Data->Integral();
       widthTOBl6Data->Scale(1/norm7);
       widthTOBl6Data->SetLineColor(kViolet);
       
       TH1F* widthTOBl6MC = new TH1F("widthTOBl6MC", "widthTOBl6MC" , 15, 0, 15 );
       TH1F* widthTOBl5MC = new TH1F("widthTOBl5MC", "widthTOBl5MC" , 15, 0, 15 );
       TH1F* widthTOBl4MC = new TH1F("widthTOBl4MC", "widthTOBl4MC" , 15, 0, 15 );
       TH1F* widthTOBl1MC = new TH1F("widthTOBl1MC", "widthTOBl1MC" , 15, 0, 15 );

       for(uint32_t m = 0; m<subclusterwidth2.size(); m++)
       {
           if(subclusterlayerwheel2.at(m) == 1)
           {
               widthTOBl1MC->Fill(subclusterwidth2.at(m));
               //cout << "filled l1 MC width " << subclusterwidth2.at(m) << endl;
           }
           if(subclusterlayerwheel2.at(m) == 5)
           {
               widthTOBl5MC->Fill(subclusterwidth2.at(m));
               //cout << "filled l5 MC width " << subclusterwidth2.at(m) << endl;
           }
           if(subclusterlayerwheel2.at(m) == 6)
           {
               widthTOBl6MC->Fill(subclusterwidth2.at(m));
               //cout << "filled l6 MC width " << subclusterwidth2.at(m) << endl;
           }
           if(subclusterlayerwheel2.at(m) == 4)
           {
               widthTOBl4MC->Fill(subclusterwidth2.at(m));
               //cout << "filled l4 MC width " << subclusterwidth2.at(m) << endl;
           }
       }
       double norm3 = widthTOBl1MC->Integral();
       widthTOBl1MC->Scale(1/norm3);
       double norm4 = widthTOBl5MC->Integral();
       widthTOBl5MC->Scale(1/norm4);
       double norm6 = widthTOBl4MC->Integral();
       widthTOBl4MC->Scale(1/norm6);
       double norm8 = widthTOBl6MC->Integral();
       widthTOBl6MC->Scale(1/norm8);

       widthTOBl1Data->Divide(widthTOBl1MC);
       widthTOBl5Data->Divide(widthTOBl5MC);
       widthTOBl4Data->Divide(widthTOBl4MC);
       widthTOBl6Data->Divide(widthTOBl6MC);


//@MJ@ TODO what is the theta range?!
//
       TProfile* chargeOnChannelFcePositioniStr60Data  = new TProfile("chargeOnChannelFcePositionStr60Data", "chargeOnChannelFcePositionStr60Data" ,10000, -6,6, 0, 300 ); //@MJ@ TODO check range of x
       TProfile* chargeOnChannelFcePositioniStr250Data  = new TProfile("chargeOnChannelFcePositionStr250Data", "chargeOnChannelFcePositionStr250Data" , 10000 , -6 ,6,  0, 300 );
       TProfile* chargeOnChannelFcePositioniStr270Data  = new TProfile("chargeOnChannelFcePositionStr270Data", "chargeOnChannelFcePositionStr270Data" , 10000, -6, 6, 0, 300 );

       unsigned chosenDet = 0;
       for(uint32_t m = 0; m<subclusterstripChargeDetid.size(); m++)
       {
           //if( (chosenDet == 0 || chosenDet==subclusterstripChargeDetid.at(m)) && ( subclusterstripChargetrackPt.at(m)> 2.5 )) //@MJ@ TODO too strong, no stats
           if( subclusterstripChargeLayerwheel.at(m) == 3 && subclusterstripChargetrackPt.at(m)> 2.5 ) //@MJ@ TODO check if phi s ok 
           {
               if(chosenDet==0)
                  chosenDet = subclusterstripChargeDetid.at(m);

               if( subclusterstripChargeStripNr.at(m) ==60)
                  chargeOnChannelFcePositioniStr60Data->Fill(subclusterstripChargeLocalX.at(m), subclusterstripCharge.at(m)); 
               if( subclusterstripChargeStripNr.at(m) ==250)
                  chargeOnChannelFcePositioniStr250Data->Fill(subclusterstripChargeLocalX.at(m), subclusterstripCharge.at(m)); 
               if( subclusterstripChargeStripNr.at(m) ==270)
                  chargeOnChannelFcePositioniStr270Data->Fill(subclusterstripChargeLocalX.at(m), subclusterstripCharge.at(m)); 
           }

       }

       TProfile* chargeOnChannelFcePositioniStr60MC  = new TProfile("chargeOnChannelFcePositionStr60MC", "chargeOnChannelFcePositionStr60MC" ,10000, -6,6, 0, 300 ); //@MJ@ TODO check range of x
       TProfile* chargeOnChannelFcePositioniStr250MC  = new TProfile("chargeOnChannelFcePositionStr250MC", "chargeOnChannelFcePositionStr250MC" , 10000 , -6 ,6,  0, 300 );
       TProfile* chargeOnChannelFcePositioniStr270MC  = new TProfile("chargeOnChannelFcePositionStr270MC", "chargeOnChannelFcePositionStr270MC" , 10000, -6, 6, 0, 300 );

       unsigned chosenDet2 = 0;
       for(uint32_t m = 0; m<subclusterstripChargeDetid2.size(); m++)
       {
           //if( (chosenDet2 == 0 || chosenDet2==subclusterstripChargeDetid2.at(m)) && ( subclusterstripChargetrackPt2.at(m)> 2.5  )) //@MJ@ TODO check if phi s ok 
           if( subclusterstripChargeLayerwheel2.at(m)==3 &&  subclusterstripChargetrackPt2.at(m)> 2.5  ) //@MJ@ TODO check if phi s ok 
           {
               if(chosenDet2==0)
                  chosenDet2 = subclusterstripChargeDetid2.at(m);

               if( subclusterstripChargeStripNr2.at(m) ==60)
                  chargeOnChannelFcePositioniStr60MC->Fill(subclusterstripChargeLocalX2.at(m), subclusterstripCharge2.at(m)); 
               if( subclusterstripChargeStripNr2.at(m) ==250)
                  chargeOnChannelFcePositioniStr250MC->Fill(subclusterstripChargeLocalX2.at(m), subclusterstripCharge2.at(m)); 
               if( subclusterstripChargeStripNr2.at(m) ==270)
                  chargeOnChannelFcePositioniStr270MC->Fill(subclusterstripChargeLocalX2.at(m), subclusterstripCharge2.at(m)); 
           }

       }



       TH1F* chargePerStripForAllWidthsData = new TH1F("chargePerStripForAllWidths", "chargePerStripForAllWidths" , 300, 0, 300 );
       TH1F* chargePerStripForAllWidthsMC = new TH1F("chargePerStripForAllWidthsMC", "chargePerStripForAllWidthsMC" , 300, 0, 300 );
       TH1F* chargePerStripForWidth1Data = new TH1F("chargePerStripForWidth1Data", "chargePerStripForWidth1Data" , 100, 0, 300 );
       TH1F* chargePerStripForWidth1MC = new TH1F("chargePerStripForWidth1MC", "chargePerStripForWidth1MC" , 100, 0, 300 );
       TH1F* chargePerStripForWidth2Data = new TH1F("chargePerStripForWidth2Data", "chargePerStripForWidth2Data" , 150, 0, 300 );
       TH1F* chargePerStripForWidth2MC = new TH1F("chargePerStripForWidth2MC", "chargePerStripForWidth2MC" , 150, 0, 300 );
       TH1F* chargePerStripForWidth3Data = new TH1F("chargePerStripForWidth3Data", "chargePerStripForWidth3Data" , 300, 0, 300 );
       TH1F* chargePerStripForWidth3MC = new TH1F("chargePerStripForWidth3MC", "chargePerStripForWidth3MC" , 300, 0, 300 );
       TH1F* chargePerStripForWidthLargerThan3Data = new TH1F("chargePerStripForWidthLargerThan3Data", "chargePerStripForWidthLargerThan3Data" , 300, 0, 300 );
       TH1F* chargePerStripForWidthLargerThan3MC = new TH1F("chargePerStripForWidthLargerThan3MC", "chargePerStripForWidthLargerThan3MC" , 300, 0, 300 );
 
       TH1F* chargePerStripForLargePtData = new TH1F("chargePerStripForLargePtData", "chargePerStripForLargePtData" , 300, 0, 300 );
       TH1F* chargePerStripForLargePtMC = new TH1F("chargePerStripForLargePtMC", "chargePerStripForLargePtMC" , 300, 0, 300 );
       TH1F* chargePerStripForSmallPtData = new TH1F("chargePerStripForSmallPtData", "chargePerStripForSmallPtData" , 300, 0, 300 );
       TH1F* chargePerStripForSmallPtMC = new TH1F("chargePerStripForSmallPtMC", "chargePerStripForSmallPtMC" , 300, 0, 300 );

       TH2F* chargePerStripVsLocalPhiData = new TH2F("chargePerStripVsLocalPhiData", "chargePerStripVsLocalPhiData" , 300, 0, 300, 100, -3.2 , 3.2 );
       TH2F* chargePerStripVsLocalPhiMC = new TH2F("chargePerStripVsLocalPhiMC", "chargePerStripVsLocalPhiMC" , 300, 0, 300, 100, -3.2 , 3.3 );

       for(uint32_t m = 0; m<subclusterstripCharge.size(); m++)
       {
           chargePerStripForAllWidthsData->Fill(subclusterstripCharge.at(m));
           chargePerStripVsLocalPhiData->Fill(subclusterstripCharge.at(m),subclusterstripChargeLocalTrackPhi.at(m) );
           
           if(subclusterstripChargeTotWidth.at(m) == 1)
              chargePerStripForWidth1Data->Fill(subclusterstripCharge.at(m));
           if(subclusterstripChargeTotWidth.at(m) == 2)
              chargePerStripForWidth2Data->Fill(subclusterstripCharge.at(m));
           if(subclusterstripChargeTotWidth.at(m) == 3)
              chargePerStripForWidth3Data->Fill(subclusterstripCharge.at(m));
           if(subclusterstripChargeTotWidth.at(m) > 3)
              chargePerStripForWidthLargerThan3Data->Fill(subclusterstripCharge.at(m));
           if(subclusterstripChargetrackPt.at(m)>2.5)
           {
               chargePerStripForLargePtData->Fill(subclusterstripCharge.at(m));
           }
           if(subclusterstripChargetrackPt.at(m)<=2.5)
           {
               chargePerStripForSmallPtData->Fill(subclusterstripCharge.at(m));
           }

         
       }
    //cout << "in here 3"  << endl;
       for(uint32_t m = 0; m<subclusterstripCharge2.size(); m++)
       {
           chargePerStripForAllWidthsMC->Fill(subclusterstripCharge2.at(m));
           chargePerStripVsLocalPhiMC->Fill(subclusterstripCharge2.at(m),subclusterstripChargeLocalTrackPhi2.at(m) );
           if(subclusterstripChargeTotWidth2.at(m) == 1)
              chargePerStripForWidth1MC->Fill(subclusterstripCharge2.at(m));
           if(subclusterstripChargeTotWidth2.at(m) == 2)
              chargePerStripForWidth2MC->Fill(subclusterstripCharge2.at(m));
           if(subclusterstripChargeTotWidth2.at(m) == 3)
              chargePerStripForWidth3MC->Fill(subclusterstripCharge2.at(m));
           if(subclusterstripChargeTotWidth2.at(m) > 3)
              chargePerStripForWidthLargerThan3MC->Fill(subclusterstripCharge2.at(m));
           if(subclusterstripChargetrackPt2.at(m)>2.5)
           {
               chargePerStripForLargePtMC->Fill(subclusterstripCharge2.at(m));
           }
           if(subclusterstripChargetrackPt2.at(m)<=2.5)
           {
               chargePerStripForSmallPtMC->Fill(subclusterstripCharge2.at(m));
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
       chargeForAllWidthsData->SetMarkerStyle(kFullCircle);
       chargeForAllWidthsMC->SetMarkerColor(kBlack);
       chargeForWidth1Data->SetMarkerStyle(kFullCircle);
       chargeForWidth1Data->SetMarkerColor(kBlack);
       chargeForWidth2Data->SetMarkerStyle(kFullCircle);
       chargeForWidth2Data->SetMarkerColor(kBlack);
       chargeForWidth3Data->SetMarkerStyle(kFullCircle);
       chargeForWidth3Data->SetMarkerColor(kBlack);
       chargeForWidthLargerThan3Data->SetMarkerStyle(kFullCircle);
       chargeForWidthLargerThan3Data->SetMarkerColor(kBlack);
       chargePerStripData->SetMarkerStyle(kFullCircle);
       chargePerStripData->SetMarkerColor(kBlack);
       leadingStripProfileData->SetMarkerStyle(kFullCircle);
       leadingStripProfileData->SetMarkerColor(kBlack);
       leadingStripSumData->SetMarkerStyle(kFullCircle);
       leadingStripSumData->SetMarkerColor(kBlack);
       chargeOnChannelFcePositioniStr60Data->SetMarkerStyle(kFullCircle);
       chargeOnChannelFcePositioniStr60Data->SetMarkerColor(kBlack);
       chargeOnChannelFcePositioniStr250Data->SetMarkerStyle(kFullCircle);
       chargeOnChannelFcePositioniStr250Data->SetMarkerColor(kBlack);
       chargeOnChannelFcePositioniStr270Data->SetMarkerStyle(kFullCircle);
       chargeOnChannelFcePositioniStr270Data->SetMarkerColor(kBlack);
       stripChargeSharingData->SetMarkerStyle(kFullCircle);
       stripChargeSharingData->SetMarkerColor(kBlack);
       stripChargeSharing3Data->SetMarkerStyle(kFullCircle);
       stripChargeSharing3Data->SetMarkerColor(kBlack);
       stripChargeSharingEtaData->SetMarkerStyle(kFullCircle);
       stripChargeSharingEtaData->SetMarkerColor(kBlack);
       chargeForLargePtData->SetMarkerStyle(kFullCircle);
       chargeForLargePtData->SetMarkerColor(kBlack);
       chargeForSmallPtData->SetMarkerStyle(kFullCircle);
       chargeForSmallPtData->SetMarkerColor(kBlack);
       widthForLargePtData->SetMarkerStyle(kFullCircle);
       widthForLargePtData->SetMarkerColor(kBlack);
       widthForSmallPtData->SetMarkerStyle(kFullCircle);
       widthForSmallPtData->SetMarkerColor(kBlack);
       chargePerStripForAllWidthsData->SetMarkerStyle(kFullCircle);
       chargePerStripForAllWidthsMC->SetMarkerColor(kBlack);
       chargePerStripForWidth1Data->SetMarkerStyle(kFullCircle);
       chargePerStripForWidth1Data->SetMarkerColor(kBlack);
       chargePerStripForWidth2Data->SetMarkerStyle(kFullCircle);
       chargePerStripForWidth2Data->SetMarkerColor(kBlack);
       chargePerStripForWidth3Data->SetMarkerStyle(kFullCircle);
       chargePerStripForWidth3Data->SetMarkerColor(kBlack);
       chargePerStripForWidthLargerThan3Data->SetMarkerStyle(kFullCircle);
       chargePerStripForWidthLargerThan3Data->SetMarkerColor(kBlack);
       chargePerStripForLargePtData->SetMarkerStyle(kFullCircle);
       chargePerStripForLargePtData->SetMarkerColor(kBlack);
       clusterWidthAsFceTanPhiData->SetMarkerStyle(kFullCircle);
       clusterWidthAsFceTanPhiData->SetMarkerColor(kBlack);
       clusterWidthAsFceTanThetaData->SetMarkerStyle(kFullCircle);
       clusterWidthAsFceTanThetaData->SetMarkerColor(kBlack);
       clusterWidthAsFceTanThetaLorData->SetMarkerStyle(kFullCircle);
       clusterWidthAsFceTanThetaLorData->SetMarkerColor(kBlack);
       clusterWidthAsFceTanThetaLorAssymetryData->SetMarkerStyle(kFullCircle);
       clusterWidthAsFceTanThetaLorAssymetryData->SetMarkerColor(kBlack);
       tanThetaLorForWidth1MC->SetMarkerStyle(kFullCircle);
       tanThetaLorForWidth1MC->SetMarkerColor(kBlack);
       clusterStripCahrgeAsFceTanPhiData->SetMarkerStyle(kFullCircle);
       clusterStripCahrgeAsFceTanPhiData->SetMarkerColor(kBlack);
       clusterStripCahrgeAsFceTanThetaData->SetMarkerStyle(kFullCircle);
       clusterStripCahrgeAsFceTanThetaData->SetMarkerColor(kBlack);
       clusterStripCahrgeAsFceTanThetaLorData->SetMarkerStyle(kFullCircle);
       clusterStripCahrgeAsFceTanThetaLorData->SetMarkerColor(kBlack);
       clusterShapeData->SetMarkerStyle(kFullCircle);
       clusterShapeData->SetMarkerColor(kBlack);
       clusterShapeMT8Data->SetMarkerStyle(kFullCircle);
       clusterShapeMT8Data->SetMarkerColor(kBlack);
       clusterShapeLT7Data->SetMarkerStyle(kFullCircle);
       clusterShapeLT7Data->SetMarkerColor(kBlack);
       clusterShape2Data->SetMarkerStyle(kFullCircle);
       clusterShape2Data->SetMarkerColor(kBlack);
       clusterShape3Data->SetMarkerStyle(kFullCircle);
       clusterShape3Data->SetMarkerColor(kBlack);
       clusterShape5Data->SetMarkerStyle(kFullCircle);
       clusterShape5Data->SetMarkerColor(kBlack);
       clusterShapeDataPositive->SetMarkerStyle(kFullCircle);
       clusterShapeDataPositive->SetMarkerColor(kPink);
       clusterShapeMT8DataPositive->SetMarkerStyle(kFullCircle);
       clusterShapeMT8DataPositive->SetMarkerColor(kPink);
       clusterShapeLT7DataPositive->SetMarkerStyle(kFullCircle);
       clusterShapeLT7DataPositive->SetMarkerColor(kPink);
       clusterShape2DataPositive->SetMarkerStyle(kFullCircle);
       clusterShape2DataPositive->SetMarkerColor(kPink);
       clusterShape3DataPositive->SetMarkerStyle(kFullCircle);
       clusterShape3DataPositive->SetMarkerColor(kPink);
       clusterShape5DataPositive->SetMarkerStyle(kFullCircle);
       clusterShape5DataPositive->SetMarkerColor(kPink);
       clusterShape6DataPositive->SetMarkerStyle(kFullCircle);
       clusterShape6DataPositive->SetMarkerColor(kPink);
       clusterShape7DataPositive->SetMarkerStyle(kFullCircle);
       clusterShape7DataPositive->SetMarkerColor(kPink);
       clusterShapeDataNegative->SetMarkerStyle(kFullCircle);
       clusterShapeDataNegative->SetMarkerColor(kRed+3);
       clusterShapeMT8DataNegative->SetMarkerStyle(kFullCircle);
       clusterShapeMT8DataNegative->SetMarkerColor(kRed+3);
       clusterShapeLT7DataNegative->SetMarkerStyle(kFullCircle);
       clusterShapeLT7DataNegative->SetMarkerColor(kRed+3);
       clusterShape2DataNegative->SetMarkerStyle(kFullCircle);
       clusterShape2DataNegative->SetMarkerColor(kRed+3);
       clusterShape3DataNegative->SetMarkerStyle(kFullCircle);
       clusterShape3DataNegative->SetMarkerColor(kRed+3);
       clusterShape5DataNegative->SetMarkerStyle(kFullCircle);
       clusterShape5DataNegative->SetMarkerColor(kRed+3);
       clusterShape6DataNegative->SetMarkerStyle(kFullCircle);
       clusterShape6DataNegative->SetMarkerColor(kRed+3);
       clusterShape7DataNegative->SetMarkerStyle(kFullCircle);
       clusterShape7DataNegative->SetMarkerColor(kRed+3);
       clusterShapeDataNegativeChandi->SetMarkerStyle(kFullCircle);
       clusterShapeDataNegativeChandi->SetMarkerColor(kRed+3);
       clusterShapeDataNegativeChandiCorr->SetMarkerStyle(kFullCircle);
       clusterShapeDataNegativeChandiCorr->SetMarkerColor(kRed+3);
       clusterShapeDataPositiveChandi->SetMarkerStyle(kFullCircle);
       clusterShapeDataPositiveChandi->SetMarkerColor(kRed+3);
       clusterChargeWOSaturationData->SetMarkerStyle(kFullCircle);
       clusterChargeWOSaturationData->SetMarkerColor(kBlack);
       clusterWidthWOSaturationData->SetMarkerStyle(kFullCircle);
       clusterWidthWOSaturationData->SetMarkerColor(kBlack);
       clusterChargePerStripWOSaturationData->SetMarkerStyle(kFullCircle);
       clusterChargePerStripWOSaturationData->SetMarkerColor(kBlack);
       narrowTrackClusterWidthData->SetMarkerStyle(kFullCircle); 
       narrowTrackClusterWidthData->SetMarkerColor(kBlack); 
       narrowTrackSharing1Data->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data->SetMarkerColor(kBlack);
       narrowTrackSharing2Data->SetMarkerStyle(kFullCircle);
       narrowTrackSharing2Data->SetMarkerColor(kBlack);

       chargeForAllWidthsMC->SetTitle("");
       clusterWidthForBottomModules->SetTitle("");
       clusterWidthForTopModules->SetTitle("");
       nrclusterWidthForBottomModules->SetTitle("");
       nrclusterWidthForTopModules->SetTitle("");
       chargeclusterWidthForBottomModules->SetTitle("");
       chargeclusterWidthForTopModules->SetTitle("");
       clusterWidthAsFceOfTimingTop->SetTitle("");
       clusterChargeAsFceOfTimingTop->SetTitle("");
       clusterWidthAsFceOfTimingBottom->SetTitle("");
       clusterChargeAsFceOfTimingBottom->SetTitle("");
       chargeForWidth1Data->SetTitle("");
       chargeForWidth2Data->SetTitle("");
       chargeForWidth3Data->SetTitle("");
       chargeForWidthLargerThan3Data->SetTitle("");
       chargePerStripData->SetTitle("");
       leadingStripProfileData->SetTitle("");
       leadingStripSumData->SetTitle("");
       stripChargeSharingData->SetTitle("");
       stripChargeSharingEtaData->SetTitle("");
       stripChargeSharing3Data->SetTitle("");
       chargeForLargePtData->SetTitle("");
       chargeForSmallPtData->SetTitle("");
       widthForLargePtData->SetTitle("");
       widthForSmallPtData->SetTitle("");
       chargePerStripForAllWidthsMC->SetTitle("");
       chargePerStripForWidth1Data->SetTitle("");
       chargePerStripForWidth2Data->SetTitle("");
       chargePerStripForWidth3Data->SetTitle("");
       chargePerStripForWidthLargerThan3Data->SetTitle("");
       chargePerStripForLargePtData->SetTitle("");
       clusterWidthAsFceTanPhiData->SetTitle("");
       clusterWidthAsFceTanThetaData->SetTitle("");
       clusterStripCahrgeAsFceTanPhiData->SetTitle("");
       clusterStripCahrgeAsFceTanThetaData->SetTitle("");
       clusterWidthAsFceTanThetaLorData->SetTitle("");
       clusterWidthAsFceTanThetaLorAssymetryData->SetTitle("");
       clusterStripCahrgeAsFceTanThetaLorData->SetTitle("");
       tanThetaLorForWidth1MC->SetTitle("");
       clusterShapeData->SetTitle("");
       clusterShapeMT8Data->SetTitle("");
       clusterShapeLT7Data->SetTitle("");
       clusterShape2Data->SetTitle("");
       clusterShape3Data->SetTitle("");
       clusterShape5Data->SetTitle("");
       clusterShapeDataPositive->SetTitle("");
       clusterShapeMT8DataPositive->SetTitle("");
       clusterShapeLT7DataPositive->SetTitle("");
       clusterShape2DataPositive->SetTitle("");
       clusterShape3DataPositive->SetTitle("");
       clusterShape5DataPositive->SetTitle("");
       clusterShape6DataPositive->SetTitle("");
       clusterShape7DataPositive->SetTitle("");
       clusterShapeDataNegative->SetTitle("");
       clusterShapeDataNegativeChandi->SetTitle("");
       clusterShapeDataNegativeChandiCorr->SetTitle("");
       clusterShapeDataPositiveChandi->SetTitle("");
       clusterShapeMT8DataNegative->SetTitle("");
       clusterShapeLT7DataNegative->SetTitle("");
       clusterShape2DataNegative->SetTitle("");
       clusterShape3DataNegative->SetTitle("");
       clusterShape5DataNegative->SetTitle("");
       clusterChargeWOSaturationData->SetTitle("");
       clusterWidthWOSaturationData->SetTitle("");
       clusterChargePerStripWOSaturationData->SetTitle("");
       narrowTrackClusterWidthData->SetTitle(""); 
       narrowTrackSharing1Data->SetTitle("");
       narrowTrackSharing2Data->SetTitle("");

       chargeForAllWidthsMC->GetXaxis()->SetTitle("cluster charge");
       clusterWidthForTopModules->GetXaxis()->SetTitle("cluster width");
       chargeclusterWidthForTopModules->GetXaxis()->SetTitle("cluster charge");
       clusterWidthAsFceOfTimingTop->GetXaxis()->SetTitle("cluster width");
       clusterChargeAsFceOfTimingTop->GetXaxis()->SetTitle("cluster charge");
       clusterWidthAsFceOfTimingBottom->GetXaxis()->SetTitle("cluster width");
       clusterChargeAsFceOfTimingBottom->GetXaxis()->SetTitle("cluster charge");
       chargeForWidth1Data->GetXaxis()->SetTitle("cluster charge (cluster width=1)");
       chargeForWidth2Data->GetXaxis()->SetTitle("cluster charge (cluster width=2)");
       chargeForWidth3Data->GetXaxis()->SetTitle("cluster charge (cluster width=3)");
       chargeForWidthLargerThan3Data->GetXaxis()->SetTitle("cluster charge (cluster width>3)");
       chargePerStripData->GetXaxis()->SetTitle("charge of strip in cluster");
       leadingStripProfileData->GetXaxis()->SetTitle("strip number");
       leadingStripProfileData->GetYaxis()->SetTitle("charge of leading strip in cluster");
       leadingStripSumData->GetXaxis()->SetTitle("");
       stripChargeSharingData->GetXaxis()->SetTitle("chare of subleading/leading strip (cluster width==2)");
       stripChargeSharingEtaData->GetXaxis()->SetTitle("chare of leading/(leading+subleading) strip (cluster width==2)");
       stripChargeSharing3Data->GetXaxis()->SetTitle("chare of subleading/leading strip (cluster width==3)");
       chargeForLargePtData->GetXaxis()->SetTitle("");
       chargeForSmallPtData->GetXaxis()->SetTitle("");
       widthForLargePtData->GetXaxis()->SetTitle("");
       widthForSmallPtData->GetXaxis()->SetTitle("");
       chargePerStripForAllWidthsMC->GetXaxis()->SetTitle("charge of strip in cluster");
       chargePerStripForWidth1Data->GetXaxis()->SetTitle("charge of strip in cluster (cluster width=1)");
       chargePerStripForWidth2Data->GetXaxis()->SetTitle("charge of strip in cluster (cluster width=2)");
       chargePerStripForWidth3Data->GetXaxis()->SetTitle("charge of strip in cluster (cluster width=3)");
       chargePerStripForWidthLargerThan3Data->GetXaxis()->SetTitle("charge of strip in cluster (cluster width>3)");
       chargePerStripForLargePtData->GetXaxis()->SetTitle("");
       clusterWidthAsFceTanPhiData->GetXaxis()->SetTitle("");
       clusterWidthAsFceTanThetaData->GetXaxis()->SetTitle("tan(#Theta)");
       clusterWidthAsFceTanThetaData->GetYaxis()->SetTitle("cluster width");
       clusterWidthAsFceTanThetaLorData->GetXaxis()->SetTitle("tan(#Theta_Lorentz)");
       clusterWidthAsFceTanThetaLorData->GetYaxis()->SetTitle("cluster width");
       clusterWidthAsFceTanThetaLorAssymetryData->GetXaxis()->SetTitle("abs(tan(#Theta_Lorentz))");
       clusterWidthAsFceTanThetaLorAssymetryData->GetYaxis()->SetTitle("cluster width");
       tanThetaLorForWidth1MC->GetXaxis()->SetTitle("tan(#Theta_Lotentz)");
       clusterStripCahrgeAsFceTanThetaData->GetXaxis()->SetTitle("tan(#Theta)");
       clusterStripCahrgeAsFceTanThetaData->GetYaxis()->SetTitle(" charge of leading strip in cluster");
       clusterStripCahrgeAsFceTanThetaLorData->GetXaxis()->SetTitle("tan(#Theta_Lorentz)");
       clusterStripCahrgeAsFceTanThetaLorData->GetYaxis()->SetTitle(" charge of leading strip in cluster");
       clusterShapeData->GetXaxis()->SetTitle("cluster strip");
       clusterShapeData->GetYaxis()->SetTitle("charge of strip in cluster");
       clusterShapeMT8Data->GetXaxis()->SetTitle("cluster strip (cluster width>7)");
       clusterShapeMT8Data->GetYaxis()->SetTitle("charge of strip in cluster");
       clusterShapeLT7Data->GetXaxis()->SetTitle("cluster strip (cluster width<7)");
       clusterShapeLT7Data->GetYaxis()->SetTitle("charge of strip in cluster");
       clusterShape2Data->GetXaxis()->SetTitle("cluster strip (cluster width=2)");
       clusterShape2Data->GetYaxis()->SetTitle("charge of strip in cluster");
       clusterShape3Data->GetXaxis()->SetTitle("cluster strip (cluster width=3)");
       clusterShape3Data->GetYaxis()->SetTitle("charge of strip in cluster");
       clusterShape5Data->GetXaxis()->SetTitle("cluster strip (cluster width=5)");
       clusterShape5Data->GetYaxis()->SetTitle("charge of strip in cluster");
       narrowTrackSharing1Data->GetXaxis()->SetTitle("#eta #pm 1");
       narrowTrackSharing2Data->GetXaxis()->SetTitle("#eta #pm 2");

       chargeForAllWidthsData->SetMaximum(1.5*  (chargeForAllWidthsData->GetMaximum()));
       clusterWidthForTopModules->SetMaximum(1.5* (clusterWidthForTopModules->GetMaximum()));
       chargeForWidth1Data->SetMaximum(2* chargeForWidth1Data->GetMaximum()  );
       tanThetaLorForWidth1Data->SetMaximum(2* tanThetaLorForWidth1Data->GetMaximum()  );
       chargeForWidth2Data->SetMaximum(1.5* chargeForWidth2Data->GetMaximum() );
       chargeForWidth3Data->SetMaximum(1.5* chargeForWidth3Data->GetMaximum() );
       chargeForWidthLargerThan3Data->SetMaximum(1.5*  chargeForWidthLargerThan3Data->GetMaximum());
       chargePerStripData->SetMaximum(1.5*  chargePerStripData->GetMaximum());
       //leadingStripProfileData->SetMaximum(1.5*  leadingStripProfileData->GetMaximum());
       leadingStripSumData->SetMaximum(1.5*  leadingStripSumData->GetMaximum());
       chargeOnChannelFcePositioniStr60Data->SetMaximum(2*  chargeOnChannelFcePositioniStr60Data->GetMaximum()); //DO NOT NORMALIZE->TProfile
       chargeOnChannelFcePositioniStr250Data->SetMaximum(2*  chargeOnChannelFcePositioniStr250Data->GetMaximum());
       chargeOnChannelFcePositioniStr270Data->SetMaximum(2*  chargeOnChannelFcePositioniStr270Data->GetMaximum());
       stripChargeSharingData->SetMaximum(1.5*  stripChargeSharingData->GetMaximum());
       stripChargeSharingEtaData->SetMaximum(1.5*  stripChargeSharingEtaData->GetMaximum());
       stripChargeSharing3Data->SetMaximum(1.5*  stripChargeSharing3Data->GetMaximum());
       chargeForLargePtData->SetMaximum(1.5*  chargeForLargePtData->GetMaximum());
       chargeForSmallPtData->SetMaximum(1.5*  chargeForSmallPtData->GetMaximum());
       widthForLargePtData->SetMaximum(1.5*  widthForLargePtData->GetMaximum());
       widthForSmallPtData->SetMaximum(1.5*  widthForSmallPtData->GetMaximum());
       chargePerStripForAllWidthsData->SetMaximum(1.5*  (chargePerStripForAllWidthsData->GetMaximum()));
       chargePerStripForWidth1Data->SetMaximum(2* chargePerStripForWidth1Data->GetMaximum()  );
       chargePerStripForWidth2Data->SetMaximum(1.5* chargePerStripForWidth2Data->GetMaximum() );
       chargePerStripForWidth3Data->SetMaximum(1.5* chargePerStripForWidth3Data->GetMaximum() );
       chargePerStripForWidthLargerThan3Data->SetMaximum(1.5*  chargePerStripForWidthLargerThan3Data->GetMaximum());
       chargePerStripForLargePtData->SetMaximum(1.5*  chargePerStripForLargePtData->GetMaximum());
       chargePerStripForSmallPtData->SetMaximum(1.5*  chargePerStripForSmallPtData->GetMaximum());
       clusterChargeWOSaturationData->SetMaximum(1.5*  clusterChargeWOSaturationData->GetMaximum());
       clusterWidthWOSaturationData->SetMaximum(1.5*  clusterWidthWOSaturationData->GetMaximum());
       clusterChargePerStripWOSaturationData->SetMaximum(1.5*  clusterChargePerStripWOSaturationData->GetMaximum());
       narrowTrackClusterWidthData->SetMaximum(1.5*  narrowTrackClusterWidthData->GetMaximum());
       clusterWidthAsFceTanThetaData->SetMaximum(1.5*  clusterWidthAsFceTanThetaData->GetMaximum());
       clusterWidthAsFceTanThetaLorData->SetMaximum(1.5*  clusterWidthAsFceTanThetaLorData->GetMaximum());
       narrowTrackSharing1Data->SetMaximum(2.0*  narrowTrackSharing1Data->GetMaximum());
       narrowTrackSharing2Data->SetMaximum(1.5*  narrowTrackSharing2Data->GetMaximum());

       clusterShapeDataPositive->SetMaximum(1.5*  clusterShapeDataPositive->GetMaximum());
       clusterShapeMT8DataPositive->SetMaximum(1.5*  clusterShapeMT8DataPositive->GetMaximum());
       clusterShapeLT7DataPositive->SetMaximum(1.5*  clusterShapeLT7DataPositive->GetMaximum());
       clusterShape2DataPositive->SetMaximum(1.5*  clusterShape2DataPositive->GetMaximum());
       clusterShape3DataPositive->SetMaximum(1.5*  clusterShape3DataPositive->GetMaximum());
       clusterShape5DataPositive->SetMaximum(1.5*  clusterShape5DataPositive->GetMaximum());
       clusterShape6DataPositive->SetMaximum(1.5*  clusterShape6DataPositive->GetMaximum());
       clusterShape7DataPositive->SetMaximum(1.5*  clusterShape7DataPositive->GetMaximum());

       chargeForAllWidthsMC->SetLineColor(kRed);
       clusterWidthForTopModules->SetLineColor(kBlue);
       clusterWidthForBottomModules->SetLineColor(kRed);
       nrclusterWidthForTopModules->SetLineColor(kBlue);
       nrclusterWidthForBottomModules->SetLineColor(kRed);
       chargeclusterWidthForTopModules->SetLineColor(kBlue);
       chargeclusterWidthForBottomModules->SetLineColor(kRed);
       chargeForWidth1MC->SetLineColor(kRed);
       chargeForWidth2MC->SetLineColor(kRed);
       chargeForWidth3MC->SetLineColor(kRed);
       chargeForWidthLargerThan3MC->SetLineColor(kRed);
       chargePerStripMC->SetLineColor(kRed);
       leadingStripProfileMC->SetLineColor(kRed);
       leadingStripSumMC->SetLineColor(kRed);
       chargeOnChannelFcePositioniStr60MC->SetLineColor(kRed);
       chargeOnChannelFcePositioniStr250MC->SetLineColor(kGreen);
       chargeOnChannelFcePositioniStr270MC->SetLineColor(kRed);
       stripChargeSharingMC->SetLineColor(kRed);
       stripChargeSharingEtaMC->SetLineColor(kRed);
       stripChargeSharing3MC->SetLineColor(kRed);
       chargeForLargePtMC->SetLineColor(kRed);
       chargeForSmallPtMC->SetLineColor(kRed);
       widthForLargePtMC->SetLineColor(kRed);
       widthForSmallPtMC->SetLineColor(kRed);
       chargePerStripForAllWidthsMC->SetLineColor(kRed);
       chargePerStripForWidth1MC->SetLineColor(kRed);
       chargePerStripForWidth2MC->SetLineColor(kRed);
       chargePerStripForWidth3MC->SetLineColor(kRed);
       chargePerStripForWidthLargerThan3MC->SetLineColor(kRed);
       chargePerStripForLargePtMC->SetLineColor(kRed);
       chargePerStripForSmallPtMC->SetLineColor(kRed);
       clusterWidthAsFceTanPhiMC->SetLineColor(kRed);
       clusterWidthAsFceTanThetaMC->SetLineColor(kRed);
       clusterWidthAsFceTanThetaLorMC->SetLineColor(kRed);
       clusterWidthAsFceTanThetaLorAssymetryMC->SetLineColor(kRed);
       clusterStripCahrgeAsFceTanPhiMC->SetLineColor(kRed);
       clusterStripCahrgeAsFceTanThetaMC->SetLineColor(kRed);
       clusterStripCahrgeAsFceTanThetaLorMC->SetLineColor(kRed);
       tanThetaLorForWidth1MC->SetLineColor(kRed);
       clusterShapeMC->SetLineColor(kRed);
       clusterShapeMT8MC->SetLineColor(kRed);
       clusterShapeLT7MC->SetLineColor(kRed);
       clusterShape2MC->SetLineColor(kRed);
       clusterShape3MC->SetLineColor(kRed);
       clusterShape5MC->SetLineColor(kRed);
       clusterShapeMCPositive->SetLineColor(kRed);
       clusterShapeMCPositiveChandi->SetLineColor(kRed);
       clusterShapeMCNegativeChandi->SetLineColor(kRed);
       clusterShapeMCNegativeChandiCorr->SetLineColor(kRed);
       clusterShapeMT8MCPositive->SetLineColor(kRed);
       clusterShapeLT7MCPositive->SetLineColor(kRed);
       clusterShape2MCPositive->SetLineColor(kRed);
       clusterShape3MCPositive->SetLineColor(kRed);
       clusterShape5MCPositive->SetLineColor(kRed);
       clusterShape6MCPositive->SetLineColor(kRed);
       clusterShape7MCPositive->SetLineColor(kRed);
       clusterShapeMCNegative->SetLineColor(kCyan);
       clusterShapeMT8MCNegative->SetLineColor(kCyan);
       clusterShapeLT7MCNegative->SetLineColor(kCyan);
       clusterShape2MCNegative->SetLineColor(kCyan);
       clusterShape3MCNegative->SetLineColor(kCyan);
       clusterShape5MCNegative->SetLineColor(kCyan);
       clusterShape6MCNegative->SetLineColor(kCyan);
       clusterShape7MCNegative->SetLineColor(kCyan);
       clusterChargeWOSaturationMC->SetLineColor(kRed);
       clusterWidthWOSaturationMC->SetLineColor(kRed);
       clusterChargePerStripWOSaturationMC->SetLineColor(kRed);
       narrowTrackClusterWidthMC->SetLineColor(kRed);
       narrowTrackSharing1MC->SetLineColor(kRed);
       narrowTrackSharing2MC->SetLineColor(kRed);


       //can
       TCanvas c0("chargeForAllWidths","chargeForAllWidths");
       chargeForAllWidthsData->DrawNormalized("P");
       chargeForAllWidthsMC->DrawNormalized("same hist e"); 
       c0.SaveAs(("output/"+(string)dir+"/"+(string)subDet + "chargeForAllWidths.root").c_str());
       c0.SaveAs(("output/"+(string)dir+"/"+(string)subDet + "chargeForAllWidths.eps").c_str());

       TCanvas c("chargeForWidth1","chargeForWidth1");
       chargeForWidth1Data->DrawNormalized("P");
       chargeForWidth1MC->DrawNormalized("same hist e"); 
       c.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth1.root").c_str());
       c.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth1.eps").c_str());

       TCanvas clor("tanThetaLorForWidth1","tanThetaLorForWidth1");
       tanThetaLorForWidth1Data->DrawNormalized("P");
       tanThetaLorForWidth1MC->DrawNormalized("same hist e"); 
       clor.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"tanThetaLorForWidth1.root").c_str());
       clor.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"tanThetaLorForWidth1.eps").c_str());

       TCanvas cm("chargeForWidth1DataWidth2MC","chargeForWidth1DataWidth2MC");
       chargeForWidth1Data->DrawNormalized("P");
       chargeForWidth2MC->DrawNormalized("same hist e"); 
       cm.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth1DataWidth2MC.root").c_str());
       cm.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth1DataWidth2MC.eps").c_str());

       TCanvas c2("chargeForWidth2","chargeForWidth2");
       chargeForWidth2Data->DrawNormalized("P");
       chargeForWidth2MC->DrawNormalized("same hist e"); 
       c2.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth2.root").c_str());
       c2.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth2.eps").c_str());


       TCanvas c3("chargeForWidth3","chargeForWidth3");
       chargeForWidth3Data->DrawNormalized("P");
       chargeForWidth3MC->DrawNormalized("same hist e"); 
       c3.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth3.root").c_str());
       c3.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargeForWidth3.eps").c_str());

       TCanvas cLargerThan3("chargeForWidthLargerThan3","chargeForWidthLargerThan3");
       chargeForWidthLargerThan3Data->DrawNormalized("P");
       chargeForWidthLargerThan3MC->DrawNormalized("same hist e"); 
       cLargerThan3.SaveAs(("output/"+(string)dir+"/" +(string)subDet+ "chargeForWidthLargerThan3.root").c_str());
       cLargerThan3.SaveAs(("output/"+(string)dir+"/" +(string)subDet+ "chargeForWidthLargerThan3.eps").c_str());


       TCanvas c4("chargePerStrip","chargePerStrip");
       chargePerStripData->DrawNormalized("P");
       chargePerStripMC->DrawNormalized("same hist e"); 
       c4.SaveAs(("output/"+(string)dir+ "/" +(string)subDet+ "chargePerStrip.root").c_str());
       c4.SaveAs(("output/"+(string)dir+ "/" +(string)subDet+ "chargePerStrip.eps").c_str());

       TCanvas c5("leadingStripProfile","leadingStripProfile");
       leadingStripProfileData->Draw("P");
       leadingStripProfileMC->Draw("same hist e"); 
       c5.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "leadingStripProfile.root").c_str());
       c5.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "leadingStripProfile.eps").c_str());

       TCanvas c6("leadingStripSum","leadingStripSum");
       leadingStripSumData->Draw("P");
       leadingStripSumMC->Draw("same hist e"); 
       c6.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "leadingStripSum.root").c_str());
       c6.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "leadingStripSum.eps").c_str());

       TCanvas c7("CTtob1to5","CTtob1to5");
       widthTOBl5Data->SetTitle(""); 
       widthTOBl5Data->GetXaxis()->SetTitle("data/MC ratio for cluster width"); 
       widthTOBl5Data->Draw(""); 
       widthTOBl1Data->Draw("same hist e");
       widthTOBl4Data->Draw("same hist e");
       widthTOBl6Data->Draw("same hist e");
       c7.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "CTtob1to5.root").c_str());
       c7.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "CTtob1to5.eps").c_str());

       TCanvas c8("chargeOnChannel","chargeOnChannel");
       chargeOnChannelFcePositioniStr60Data->Draw("");
       chargeOnChannelFcePositioniStr250Data->Draw("same hist e");
       chargeOnChannelFcePositioniStr270Data->Draw("same hist e");
       chargeOnChannelFcePositioniStr60MC->Draw("same hist e");
       chargeOnChannelFcePositioniStr250MC->Draw("same hist e");
       chargeOnChannelFcePositioniStr270MC->Draw("same hist e");
       c8.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeOnChannelFcePosition.root").c_str());
       c8.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeOnChannelFcePosition.eps").c_str());

       TCanvas c9("stripChargeSharing","stripChargeSharing");
       stripChargeSharingData->DrawNormalized("P"); 
       stripChargeSharingMC->DrawNormalized("same hist e");
       c9.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "StripChargeSharing.root").c_str());
       c9.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "StripChargeSharing.eps").c_str());

       TCanvas c9eta("stripChargeSharingEta","stripChargeSharingEta");
       stripChargeSharingEtaData->DrawNormalized("P"); 
       stripChargeSharingEtaMC->DrawNormalized("same hist e");
       c9eta.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "StripChargeSharingEta.root").c_str());
       c9eta.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "StripChargeSharingEta.eps").c_str());

       TCanvas c9b("stripChargeSharing3","stripChargeSharing3");
       stripChargeSharing3Data->DrawNormalized("P"); 
       stripChargeSharing3MC->DrawNormalized("same hist e");
       c9b.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "StripChargeSharing3.root").c_str());
       c9b.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "StripChargeSharing3.eps").c_str());

       TCanvas c10("chargeForLargePt","chargeForLargePt");
       chargeForLargePtData->DrawNormalized("P"); 
       chargeForLargePtMC->DrawNormalized("same hist e");
       c10.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeForLargePt.root").c_str());
       c10.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeForLargePt.eps").c_str());

       TCanvas c11("chargeForSmallPt","chargeForSmallPt");
       chargeForSmallPtData->DrawNormalized("P"); 
       chargeForSmallPtMC->DrawNormalized("same hist e");
       c11.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeForSmallPt.root").c_str());
       c11.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeForSmallPt.eps").c_str());


       TCanvas c12("widthForLargePt","widthForLargePt");
       widthForLargePtData->DrawNormalized("P"); 
       widthForLargePtMC->DrawNormalized("same hist e");
       cout << "LARGE PT: data mean " << widthForLargePtData->GetMean() << " data std dev " << widthForLargePtData->GetStdDev() << "mc mean " << widthForLargePtMC->GetMean() <<" mc std dev " << widthForLargePtMC->GetStdDev() << endl; 
       c12.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "widthForLargePt.root").c_str());
       c12.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "widthForLargePt.eps").c_str());

       TCanvas c13("widthForSmallPt","widthForSmallPt");
       widthForSmallPtData->DrawNormalized("P"); 
       widthForSmallPtMC->DrawNormalized("same hist e");
       cout << "SMALL PT: data mean " << widthForSmallPtData->GetMean() << " data std dev " << widthForSmallPtData->GetStdDev() << "mc mean " << widthForSmallPtMC->GetMean() <<" mc std dev " << widthForSmallPtMC->GetStdDev() << endl; 
       c13.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "widthForSmallPt.root").c_str());
       c13.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "widthForSmallPt.eps").c_str());

       TCanvas c0s("chargePerStripForAllWidths","chargePerStripForAllWidths");
       chargePerStripForAllWidthsData->DrawNormalized("P");
       chargePerStripForAllWidthsMC->DrawNormalized("same hist e"); 
       c0s.SaveAs(("output/"+(string)dir+"/"+(string)subDet + "chargePerStripForAllWidths.root").c_str());
       c0s.SaveAs(("output/"+(string)dir+"/"+(string)subDet + "chargePerStripForAllWidths.eps").c_str());

       TCanvas cs("chargePerStripForWidth1","chargePerStripForWidth1");
       chargePerStripForWidth1Data->DrawNormalized("P");
       chargePerStripForWidth1MC->DrawNormalized("same hist e"); 
       cs.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargePerStripForWidth1.root").c_str());
       cs.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargePerStripForWidth1.eps").c_str());


       TCanvas c2s("chargePerStripForWidth2","chargePerStripForWidth2");
       chargePerStripForWidth2Data->DrawNormalized("P");
       chargePerStripForWidth2MC->DrawNormalized("same hist e"); 
       c2s.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargePerStripForWidth2.root").c_str());
       c2s.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargePerStripForWidth2.eps").c_str());


       TCanvas c3s("chargePerStripForWidth3","chargePerStripForWidth3");
       chargePerStripForWidth3Data->DrawNormalized("P");
       chargePerStripForWidth3MC->DrawNormalized("same hist e"); 
       c3s.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargePerStripForWidth3.root").c_str());
       c3s.SaveAs(("output/"+(string)dir+"/" +(string)subDet+"chargePerStripForWidth3.eps").c_str());

       TCanvas cLargerThan3s("chargePerStripForWidthLargerThan3","chargePerStripForWidthLargerThan3");
       chargePerStripForWidthLargerThan3Data->DrawNormalized("P");
       chargePerStripForWidthLargerThan3MC->DrawNormalized("same hist e"); 
       cLargerThan3s.SaveAs(("output/"+(string)dir+"/" +(string)subDet+ "chargePerStripForWidthLargerThan3.root").c_str());
       cLargerThan3s.SaveAs(("output/"+(string)dir+"/" +(string)subDet+ "chargePerStripForWidthLargerThan3.eps").c_str());
       
       TCanvas c10s("chargePerStripForLargePt","chargePerStripForLargePt");
       chargePerStripForLargePtData->DrawNormalized("P"); 
       chargePerStripForLargePtMC->DrawNormalized("same hist e");
       c10s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripForLargePt.root").c_str());
       c10s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripForLargePt.eps").c_str());

       TCanvas c11s("chargePerStripForSmallPt","chargePerStripForSmallPt");
       chargePerStripForSmallPtData->DrawNormalized("P"); 
       chargePerStripForSmallPtMC->DrawNormalized("same hist e");
       c11s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripForSmallPt.root").c_str());
       c11s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripForSmallPt.eps").c_str());

       TCanvas c12s("chargePerStripVsLocalPhiData","chargePerStripVsLocalPhiData");
       chargePerStripVsLocalPhiData->Draw("colz"); 
       c12s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripVsLocalPhiData.root").c_str());
       c12s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripVsLocalPhiData.eps").c_str());

       TCanvas c13s("chargePerStripVsLocalPhiMC","chargePerStripVsLocalPhiMC");
       chargePerStripVsLocalPhiMC->Draw("colz"); 
       c13s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripVsLocalPhiMC.root").c_str());
       c13s.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargePerStripVsLocalPhiMC.eps").c_str());

       TCanvas c15("clusterWidthAsFceTanPhi","clusterWidthAsFceTanPhi");
       clusterWidthAsFceTanPhiData->Draw("P"); 
       clusterWidthAsFceTanPhiMC->Draw("same hist e");
       c15.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanPhi.root").c_str());
       c15.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanPhi.eps").c_str());

       TCanvas c14("clusterWidthAsFceTanTheta","clusterWidthAsFceTanTheta");
       TPad pad1("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad2("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad1.Draw();
       pad2.Draw();

       pad1.cd();
       clusterWidthAsFceTanThetaData->Draw("P"); 
       clusterWidthAsFceTanThetaMC->Draw("same hist e");
       pad2.cd();
       TProfile* clusterWidthAsFceTanThetaDiv = (TProfile*) clusterWidthAsFceTanThetaMC->Clone();
       clusterWidthAsFceTanThetaDiv->Divide( clusterWidthAsFceTanThetaData);
       clusterWidthAsFceTanThetaDiv->SetLineColor(kRed);
       clusterWidthAsFceTanThetaDiv->SetMaximum(2);
       clusterWidthAsFceTanThetaDiv->SetMinimum(0);
       clusterWidthAsFceTanThetaDiv->Draw("hist");
       c14.Update();
       c14.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanTheta.root").c_str());
       c14.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanTheta.eps").c_str());

       TCanvas c14l("clusterWidthAsFceTanThetaLor","clusterWidthAsFceTanThetaLor");
       TPad pad1Lor("pad1Lor", "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad2Lor("pad2Lor", "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad1Lor.Draw();
       pad2Lor.Draw();

       pad1Lor.cd();
       clusterWidthAsFceTanThetaLorData->Draw("P"); 
       clusterWidthAsFceTanThetaLorMC->Draw("same hist e");
       pad2Lor.cd();
       TProfile* clusterWidthAsFceTanThetaDivLor = (TProfile*) clusterWidthAsFceTanThetaLorMC->Clone();
       clusterWidthAsFceTanThetaDivLor->Divide( clusterWidthAsFceTanThetaLorData);
       clusterWidthAsFceTanThetaDivLor->SetLineColor(kRed);
       clusterWidthAsFceTanThetaDivLor->SetMaximum(2);
       clusterWidthAsFceTanThetaDivLor->SetMinimum(0);
       clusterWidthAsFceTanThetaDivLor->Draw("hist");
       c14l.Update();
       c14l.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanThetaLor.root").c_str());
       c14l.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanThetaLor.eps").c_str());


       TCanvas c14ass("clusterWidthAsFceTanThetaLorAssymetry","clusterWidthAsFceTanLorTheta");
       clusterWidthAsFceTanThetaLorAssymetryData->Draw("P"); 
       clusterWidthAsFceTanThetaLorAssymetryMC->Draw("same hist e");
       c14ass.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanThetaLorAssymetry.root").c_str());
       c14ass.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceTanThetaLorAssymetr.eps").c_str());


       TCanvas c16("clusterStripCahrgeAsFceTanPhi","clusterStripCahrgeAsFceTanPhi");
       clusterStripCahrgeAsFceTanPhiData->Draw("P"); 
       clusterStripCahrgeAsFceTanPhiMC->Draw("same hist e");
       c16.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterStripCahrgeAsFceTanPhi.root").c_str());
       c16.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterStripCahrgeAsFceTanPhi.eps").c_str());

       TCanvas c17("clusterStripCahrgeAsFceTanTheta","clusterStripCahrgeAsFceTanTheta");
       TPad pad1b("pad1b", "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad2b("pad2b", "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad1b.Draw();
       pad2b.Draw();

       pad1b.cd();
       clusterStripCahrgeAsFceTanThetaData->Draw("P"); 
       clusterStripCahrgeAsFceTanThetaMC->Draw("same hist e");
       pad2b.cd();
       TH1F* clusterStripCahrgeAsFceTanThetaDiv = (TH1F*) clusterStripCahrgeAsFceTanThetaMC->Clone();
       clusterStripCahrgeAsFceTanThetaDiv->Divide(clusterStripCahrgeAsFceTanThetaData);
       clusterStripCahrgeAsFceTanThetaDiv->SetLineColor(kRed);
       clusterStripCahrgeAsFceTanThetaDiv->SetMaximum(2);
       clusterStripCahrgeAsFceTanThetaDiv->SetMinimum(0);
       clusterStripCahrgeAsFceTanThetaDiv->Draw("hist");
       c17.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterStripCahrgeAsFceTanTheta.root").c_str());
       c17.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterStripCahrgeAsFceTanTheta.eps").c_str());

       TCanvas c17Lor("clusterStripCahrgeAsFceTanThetaLor","clusterStripCahrgeAsFceTanThetaLor");
       TPad pad1bLor("pad1bLor", "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad2bLor("pad2bLor", "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad1bLor.Draw();
       pad2bLor.Draw();

       pad1bLor.cd();
       clusterStripCahrgeAsFceTanThetaLorData->Draw("P"); 
       clusterStripCahrgeAsFceTanThetaLorMC->Draw("same hist e");
       pad2bLor.cd();
       TH1F* clusterStripCahrgeAsFceTanThetaDivLor = (TH1F*) clusterStripCahrgeAsFceTanThetaLorMC->Clone();
       clusterStripCahrgeAsFceTanThetaDivLor->Divide(clusterStripCahrgeAsFceTanThetaLorData);
       clusterStripCahrgeAsFceTanThetaDivLor->SetLineColor(kRed);
       clusterStripCahrgeAsFceTanThetaDivLor->SetMaximum(2);
       clusterStripCahrgeAsFceTanThetaDivLor->SetMinimum(0);
       clusterStripCahrgeAsFceTanThetaDivLor->Draw("hist");
       c17Lor.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterStripCahrgeAsFceTanThetaLor.root").c_str());
       c17Lor.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterStripCahrgeAsFceTanThetaLor.eps").c_str());

       TCanvas c18("clusterShape","clusterShape");
       clusterShapeData->Draw("P"); 
       clusterShapeMC->Draw("same hist e");
       c18.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape.root").c_str());
       c18.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape.eps").c_str());

       TCanvas c19("clusterShapeMT8","clusterShapeMT8");
       clusterShapeMT8Data->Draw("P"); 
       clusterShapeMT8MC->Draw("same hist e");
       c19.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeMT8.root").c_str());
       c19.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeMT8.eps").c_str());

       TCanvas c20("clusterShapeLT7","clusterShapeLT7");
       clusterShapeLT7Data->Draw("P"); 
       clusterShapeLT7MC->Draw("same hist e");
       c20.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeLT7.root").c_str());
       c20.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeLT7.eps").c_str());

       TCanvas c21("clusterShape2","clusterShape2");
       clusterShape2Data->Draw("P"); 
       clusterShape2MC->Draw("same hist e");
       c21.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape2.root").c_str());
       c21.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape2.eps").c_str());

       TCanvas c22("clusterShape3","clusterShape3");
       clusterShape3Data->Draw("P"); 
       clusterShape3MC->Draw("same hist e");
       c22.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape3.root").c_str());
       c22.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape3.eps").c_str());

       TCanvas c23("clusterShape5","clusterShape5");
       clusterShape5Data->Draw("P"); 
       clusterShape5MC->Draw("same hist e");
       c23.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape5.root").c_str());
       c23.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape5.eps").c_str());
       

       TCanvas c18Positive("clusterShapePositive","clusterShapePositive");
       clusterShapeDataPositive->DrawNormalized("P"); 
       clusterShapeMCPositive->DrawNormalized("same hist e");
       clusterShapeDataNegative->DrawNormalized("P same hist e"); 
       clusterShapeMCNegative->DrawNormalized("same hist e");
       c18Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapePositive.root").c_str());
       c18Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapePositive.eps").c_str());

       TCanvas c19Positive("clusterShapeMT8Positive","clusterShapeMT8Positive");
       clusterShapeMT8DataPositive->DrawNormalized("P"); 
       clusterShapeMT8MCPositive->DrawNormalized("same hist e");
       clusterShapeMT8DataNegative->DrawNormalized("P same hist e"); 
       clusterShapeMT8MCNegative->DrawNormalized("same hist e");
       c19Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeMT8Positive.root").c_str());
       c19Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeMT8Positive.eps").c_str());

       TCanvas c20Positive("clusterShapeLT7Positive","clusterShapeLT7Positive");
       clusterShapeLT7DataPositive->DrawNormalized("P"); 
       clusterShapeLT7MCPositive->DrawNormalized("same hist e");
       clusterShapeLT7DataNegative->DrawNormalized("P same hist e"); 
       clusterShapeLT7MCNegative->DrawNormalized("same hist e");
       c20Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeLT7Positive.root").c_str());
       c20Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeLT7Positive.eps").c_str());

       TCanvas c21Positive("clusterShape2Positive","clusterShape2Positive");
       clusterShape2DataPositive->DrawNormalized("P"); 
       clusterShape2MCPositive->DrawNormalized("same hist e");
       clusterShape2DataNegative->DrawNormalized("P same hist e"); 
       clusterShape2MCNegative->DrawNormalized("same hist e");
       c21Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape2Positive.root").c_str());
       c21Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape2Positive.eps").c_str());

       TCanvas c22Positive("clusterShape3Positive","clusterShape3Positive");
       clusterShape3DataPositive->DrawNormalized("P"); 
       clusterShape3MCPositive->DrawNormalized("same hist e");
       clusterShape3DataNegative->DrawNormalized("P same hist e"); 
       clusterShape3MCNegative->DrawNormalized("same hist e");
       c22Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape3Positive.root").c_str());
       c22Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape3Positive.eps").c_str());

       TCanvas c23Positive("clusterShape5Positive","clusterShape5Positive");
       clusterShape5DataPositive->DrawNormalized("P"); 
       clusterShape5MCPositive->DrawNormalized("same hist e");
       clusterShape5DataNegative->DrawNormalized("P same hist e"); 
       clusterShape5MCNegative->DrawNormalized("same hist e");
       c23Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape5Positive.root").c_str());
       c23Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape5Positive.eps").c_str());
       
       TCanvas c24Positive("clusterShape6Positive","clusterShape6Positive");
       clusterShape6DataPositive->DrawNormalized("P"); 
       clusterShape6MCPositive->DrawNormalized("same hist e");
       clusterShape6DataNegative->DrawNormalized("P same hist e"); 
       clusterShape6MCNegative->DrawNormalized("same hist e");
       c24Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape6Positive.root").c_str());
       c24Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape6Positive.eps").c_str());
       

       TCanvas c25Positive("clusterShape7Positive","clusterShape7Positive");
       clusterShape7DataPositive->DrawNormalized("P"); 
       clusterShape7MCPositive->DrawNormalized("same hist e");
       clusterShape7DataNegative->DrawNormalized("P same hist e"); 
       clusterShape7MCNegative->DrawNormalized("same hist e");
       c25Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape7Positive.root").c_str());
       c25Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShape7Positive.eps").c_str());
       


       TCanvas c30("clusterChargeWOSaturation","clusterChargeWOSaturation");
       clusterChargeWOSaturationData->DrawNormalized("P"); 
       clusterChargeWOSaturationMC->DrawNormalized("same hist e");
       c30.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargeWOSaturation.root").c_str());
       c30.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargeWOSaturation.eps").c_str());

       TCanvas c31("clusterWidthWOSaturation","clusterWidthWOSaturation");
       clusterWidthWOSaturationData->DrawNormalized("P"); 
       clusterWidthWOSaturationMC->DrawNormalized("same hist e");
       c31.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthWOSaturation.root").c_str());
       c31.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthWOSaturation.eps").c_str());

       TCanvas c32("clusterChargePerStripWOSaturation","clusterChargePerStripWOSaturation");
       clusterChargePerStripWOSaturationData->DrawNormalized("P"); 
       clusterChargePerStripWOSaturationMC->DrawNormalized("same hist e");
       c32.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargePerStripWOSaturation.root").c_str());
       c32.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargePerStripWOSaturation.eps").c_str());

       TCanvas c33("chargeVsWidthData","chargeVsWidthData");
       chargeVsWidthData->Draw("colz"); 
       c33.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeVsWidthData.root").c_str());
       c33.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeVsWidthData.eps").c_str());

       TCanvas c34("chargeVsWidthMC","chargeVsWidthMC");
       chargeVsWidthMC->Draw("colz"); 
       c34.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeVsWidthMC.root").c_str());
       c34.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeVsWidthMC.eps").c_str());

       TCanvas c36("narrowTrackClusterWidth","narrowTrackClusterWidth");
       narrowTrackClusterWidthData->DrawNormalized(""); 
       narrowTrackClusterWidthMC->DrawNormalized(" same hist e"); 
       c36.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "narrowTrackClusterWidth.root").c_str());
       c36.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "narrowTrackClusterWidth.eps").c_str());

       TCanvas c37("narrowTrackSharing1","narrowTrackSharing1");
       narrowTrackSharing1Data->DrawNormalized(""); 
       narrowTrackSharing1MC->DrawNormalized(" same hist e"); 
       c37.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "narrowTrackSharing1.root").c_str());
       c37.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "narrowTrackSharing1.eps").c_str());

       TCanvas c38("narrowTrackSharing2","narrowTrackSharing2");
       narrowTrackSharing2Data->DrawNormalized(""); 
       narrowTrackSharing2MC->DrawNormalized(" same hist e"); 
       c38.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "narrowTrackSharing2.root").c_str());
       c38.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "narrowTrackSharing2.eps").c_str());

       TCanvas c39Positive("clusterShapeChandiPositive","clusterShapeChandiPositive");
       clusterShapeDataPositiveChandi->DrawNormalized("P"); 
       clusterShapeMCPositiveChandi->DrawNormalized("same hist e");
       c39Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapePositiveChandi.root").c_str());
       c39Positive.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapePositiveChandi.eps").c_str());

       TCanvas c39Negative("clusterShapeChandiNegaive","clusterShapeChandiNegative");
       clusterShapeDataNegativeChandi->DrawNormalized("P"); 
       clusterShapeMCNegativeChandi->DrawNormalized("same hist e");
       c39Negative.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeNegativeChandi.root").c_str());
       c39Negative.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeNegativeChandi.eps").c_str());

       TCanvas c39NegativeCorr("clusterShapeChandiNegaiveCorr","clusterShapeChandiNegativeCorr");
       clusterShapeDataNegativeChandiCorr->DrawNormalized("P"); 
       clusterShapeMCNegativeChandiCorr->DrawNormalized("same hist e");
       c39NegativeCorr.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeNegativeChandiCorr.root").c_str());
       c39NegativeCorr.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterShapeNegativeChandiCorr.eps").c_str());


       TCanvas c40("clusterWidthForTopBotModules","clusterWidthForTopBotModules");
       clusterWidthForTopModules->DrawNormalized("hist e");
       clusterWidthForBottomModules->DrawNormalized("same hist e");
       c40.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthForTopBotModules.root").c_str());
       c40.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthForTopBotModules.eps").c_str());

       TCanvas c41("nrclusterWidthForTopBotModules","nrclusterWidthForTopBotModules");
       nrclusterWidthForTopModules->Draw("hist");
       nrclusterWidthForBottomModules->Draw("same hist");
       c41.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "nrclusterWidthForTopBotModules.root").c_str());
       c41.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "nrclusterWidthForTopBotModules.eps").c_str());

       TCanvas c42("chargeclusterWidthForTopBotModules","chargeclusterWidthForTopBotModules");
       chargeclusterWidthForTopModules->DrawNormalized("hist e");
       chargeclusterWidthForBottomModules->DrawNormalized("same hist e");
       c42.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeclusterWidthForTopBotModules.root").c_str());
       c42.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "chargeclusterWidthForTopBotModules.eps").c_str());

       TCanvas c43("clusterWidthAsFceOfTimingTop","clusterWidthAsFceOfTimingTop");
       clusterWidthAsFceOfTimingTop->Draw();
       c43.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceOfTimingTop.root").c_str());
       c43.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceOfTimingTop.eps").c_str());

       TCanvas c44("clusterChargeAsFceOfTimingTop","clusterChargeAsFceOfTimingTop");
       clusterChargeAsFceOfTimingTop->Draw();
       c44.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargeAsFceOfTimingTop.root").c_str());
       c44.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargeAsFceOfTimingTop.eps").c_str());

       TCanvas c43b("clusterWidthAsFceOfTimingBottom","clusterWidthAsFceOfTimingBottom");
       clusterWidthAsFceOfTimingBottom->Draw();
       c43b.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceOfTimingBottom.root").c_str());
       c43b.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterWidthAsFceOfTimingBottom.eps").c_str());

       TCanvas c44b("clusterChargeAsFceOfTimingBottom","clusterChargeAsFceOfTimingBottom");
       clusterChargeAsFceOfTimingBottom->Draw();
       c44b.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargeAsFceOfTimingBottom.root").c_str());
       c44b.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "clusterChargeAsFceOfTimingBottom.eps").c_str());


      /////////////////////////////////////////////////////



       TCanvas c35("dummyCTplot","dummyCTplot");
       dummyCTplot->Draw("hist"); 
       c35.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "dummyCTplot.root").c_str());
       c35.SaveAs(("output/"+(string)dir+"/"+ (string)subDet+ "dummyCTplot.eps").c_str());

    //cout << "in here 7"  << endl;

   return 0;
}
