//./crossTalkMeasurementSameClusters test_shallowTrackCRUZET_2017VRNewClusteringTimingMuonTimingTests3.root crossTalkMeasurementPrecise

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
   //data always first
    

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



       TProfile*  chargeIB1Prof=  new TProfile("chargeIB1Prof", "chargeIB1Prof" , 200, -100, 100, 0, 500 ) ;
       TProfile*  chargeIB2Prof=  new TProfile("chargeIB2Prof", "chargeIB2Prof" , 200, -100, 100, 0, 500 ) ;
       TProfile*  chargeOB2Prof=  new TProfile("chargeOB2Prof", "chargeOB2Prof" , 200, -100, 100, 0, 500 ) ;
       TProfile*  chargeOB1Prof=  new TProfile("chargeOB1Prof", "chargeOB1Prof" , 200, -100, 100, 0, 500 ) ;

       uint8_t TIDoffset = 3;
       uint8_t TECoffset = 6;

       vector<string> canvases;
       bool boolIB1 = false;
       bool boolIB2 = false;
       bool boolOB2 = false;
       bool boolOB1 = false;
       float chargeIB1 = 0;
       float chargeIB2 = 0;
       float chargeOB2 = 0;
       float chargeOB1 = 0;

       for(uint32_t m = 0; m<subCTstripCharge.size()/5; m++) //@MJ@ TODO nr of clusters in here, correct variables
       {
           int32_t clusterStart = m*5;
           int32_t prevclusterStart = (m-1)*5;


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

               if(prevclusterStart >=0 && subCTCmbtimeVtxr.at(clusterStart)== subCTCmbtimeVtxr.at(prevclusterStart))
               { 
                   if(subtsosrhglobalphi.at(m)>0)
                   {

		       if(subCTstripChargeSubdetid.at(clusterStart) == 3 ) //TIB
		       {
			   if(subCTstripChargeLayerwheel.at(clusterStart)>0 && subCTstripChargeLayerwheel.at(clusterStart)<3)
			   {
                               boolIB1 = true;
                               chargeIB1 = subCTstripChargeTotCharge.at(clusterStart);
			   }
			   else
			   {
                               boolIB2 = true;
                               chargeIB2 = subCTstripChargeTotCharge.at(clusterStart);
			   }

		       }
		       if(subCTstripChargeSubdetid.at(clusterStart) == 5 ) //TOB
		       {
			   if(subCTstripChargeLayerwheel.at(clusterStart)>0 && subCTstripChargeLayerwheel.at(clusterStart)<5)
			   {
                               boolOB2 = true;
                               chargeOB2 = subCTstripChargeTotCharge.at(clusterStart);
			   }
			   else
			   {
                               boolOB1 = true;
                               chargeOB1 = subCTstripChargeTotCharge.at(clusterStart);
			   }

		       }
                   }

                }
                else
                {
                    if( /*boolIB1 && */  boolIB2 && boolOB1 && /*boolOB2 &&*/ prevclusterStart >=0 )
                    {
                        //chargeIB1Prof->Fill(subCTCmbtimeVtxr.at(prevclusterStart), chargeIB1 );
                        chargeIB2Prof->Fill(subCTCmbtimeVtxr.at(prevclusterStart), chargeIB2 );
                        //chargeOB2Prof->Fill(subCTCmbtimeVtxr.at(prevclusterStart), chargeOB2 );
                        chargeOB1Prof->Fill(subCTCmbtimeVtxr.at(prevclusterStart), chargeOB1 );

                    }
                    boolIB1 = false;
                    boolIB2 = false;
                    boolOB2 = false;
                    boolOB1 = false;
                }

/*               if(subCTstripCharge.at(clusterStart+1) != -333)
                   narrowTrackSharing1Data.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
               if(subCTstripCharge.at(clusterStart+3) != -333)
                   narrowTrackSharing1Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
               if(subCTstripCharge.at(clusterStart) != -333)
                   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
               if(subCTstripCharge.at(clusterStart+4) != -333)
                   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));

*/

       }

  }

//////////////////////filling
//     
//

       TCanvas* cn = new TCanvas("cn","cn");
       chargeOB1Prof->GetXaxis()->SetTitle("outin");
       chargeOB1Prof->GetYaxis()->SetTitle(" averagecluster charge");
       chargeOB1Prof->SetMaximum(300);
       chargeIB1Prof->SetLineColor(5) ;
       chargeIB2Prof->SetLineColor(2) ;
       chargeOB2Prof->SetLineColor(8) ;
       chargeOB1Prof->SetLineColor(4) ;
       chargeOB1Prof->Draw(" e") ;
       chargeIB1Prof->Draw("same  e") ;
       chargeIB2Prof->Draw("same  e") ;
       chargeOB2Prof->Draw("same  e") ;
       cn->SaveAs(("output/"+(string)dir+"/chargeForSameClusters.root").c_str());
       cn->SaveAs(("output/"+(string)dir+"/chargeForSameClusters.eps").c_str());


    //cout << "in here 7"  << endl;

   return 0;
}
