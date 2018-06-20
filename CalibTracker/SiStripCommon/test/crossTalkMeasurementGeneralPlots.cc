//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017tests3.root combinatonOfHits bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackAndClusterMuonFromCollision.root collisionHits bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackAndClusterMuonFromCollision.root collisionHitsRaw bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017ZSampltest2.root crossTalkMeasurementZS bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017testsVRZS.root crossTalkVRasZS bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017ZSCRAFT.root crossTalkCRAFTZS bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017testsLatestHopefully.root combinatonOfHitsTanCut bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017lhcSTAMuons.root lhcMu bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017testsLatestHopefully.root combinatonOfHits bottom muTop
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017onlyGoodRun.root combinatonOfHitsOneRun bottom muTop
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017onlyGoodRunMuonColl.root combinatonOfHitsOneRun bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017onlyGoodRunMuonCollBetterGlob.root combinatonOfHitsOneRun bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017BothMuons.root combinatonOfHitsOneRun bottom muBottom
//./crossTalkMeasurementGeneral merged_1.root run2018CRUZET bottom muBottom
//./crossTalkMeasurementGeneral test_shallowTrackCRUZET_2017testi4.root olddata bottom muBottom
//./crossTalkMeasurementGeneral merged_1v2.root newdata bottom muBottom
//./crossTalkMeasurementGeneral merged_1NoOutMatching.root newdatamorestats bottom muBottom
//./crossTalkMeasurementGeneral merged_1NoOutMatching.root newdatamorestatsSmallDist bottom muBottom


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
#include <ctgmath>

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
#include "TLatex.h"
#include "TMinuit.h"
#include "TFitResultPtr.h"

using namespace std;

double eta0Err( double seta1, double seta2 );
double eta1Err( double mean1, double smean1, double mean2, double smean2 );
double eta2Err( double mean1, double smean1, double mean2, double smean2 );
double eta0( double eta1, double eta2 );
double eta1( double mean1, double mean2 );
double eta2( double mean1, double mean2 );

#include "tdrstyle.C"

int main(int argc, char *argv[]){

Modified_tdr_style();
 //gStyle->SetOptStat(1111111111);
 //gStyle->SetOptStat(1111111);
 //gStyle->SetOptStat("kKsSiourRmMen");
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
       vector<float>* CTstripChargeGlobalTrackTheta = 0;
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
       vector<float>* CTstripChargeSeedChargeRescaled = 0;
       vector<float>* CTmuonsIsGlobal = 0;
       vector<float>* CTmuonsIsTracker = 0;
       vector<float>* CTstripChargeTotChargeRescaled = 0;
       vector<float>* CTMuOrigin = 0;
       vector<float>* CTtof = 0;
       vector<float>* CTtofImproved = 0;
       vector<int>* clusterstereo = 0;



       vector<float> subCTstripChargeSubdetid;
       vector<float> subCTstripCharge;
       vector<float> subCTstripChargeLayerwheel;
       //vector<float> subCTstripChargeStripNr;
       vector<float> subCTstripChargeTotWidth;
       vector<float> subCTstripChargeTotCharge;
       vector<float> subCTstripChargeLocalTrackPhi;
       //vector<float> subCTstripChargeGlobalTrackPhi;
       vector<float> subCTstripChargeLocalTrackTheta;
       vector<float> subCTstripChargeGlobalTrackTheta;
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
       vector<float>  subCTstripChargeSeedChargeRescaled;
       vector<float>  subCTmuonsIsGlobal;
       vector<float>  subCTmuonsIsTracker;
       vector<float>  subCTstripChargeTotChargeRescaled;
       vector<float>  subCTMuOrigin;
       vector<float>  subCTtof;
       vector<float>  subCTtofImproved;
       vector<int>    subclusterstereo;

       vector<float>*  CTinnerXtop = 0; //this is bit unfortunate, it is not top anymore
       vector<float>*  CTinnerYtop = 0;
       vector<float>*  CTinnerZtop = 0;
       vector<float>*  CTinnerVZtop = 0;
       vector<float>*  CTinnerVX = 0;
       vector<float>*  CTinnerVY = 0;
       vector<float>*  CTouterXtop = 0;
       vector<float>*  CTouterYtop = 0;
       vector<float>*  CTouterZtop = 0;
       vector<float>*  CTouterEtatop = 0;
       vector<float>*  CTglobalZ = 0;
       vector<float>*  CTglobalX = 0;
       vector<float>*  CTglobalY = 0;
       vector<float>*  CTlocalX = 0;

       vector<float>  subCTinnerXtop;
       vector<float>  subCTinnerYtop;
       vector<float>  subCTinnerZtop ;
       vector<float>  subCTinnerVZtop ;
       vector<float>  subCTinnerVX ;
       vector<float>  subCTinnerVY ;
       vector<float>  subCTouterXtop;
       vector<float>  subCTouterYtop;
       vector<float>  subCTouterZtop;
       vector<float>  subCTouterEtatop;
       vector<float>  subCTglobalX ;
       vector<float>  subCTglobalY ;
       vector<float>  subCTglobalZ ;
       vector<float>  subCTlocalX ;

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
       t1->SetBranchAddress("CTstripChargeGlobalTrackTheta",  &CTstripChargeGlobalTrackTheta );
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
       t1->SetBranchAddress("CTinnerVX",  &CTinnerVX );
       t1->SetBranchAddress("CTinnerVY",  &CTinnerVY );
       t1->SetBranchAddress("CTouterXtop",  &CTouterXtop );
       t1->SetBranchAddress("CTouterYtop",  &CTouterYtop );
       t1->SetBranchAddress("CTouterZtop",  &CTouterZtop );
       t1->SetBranchAddress("CTouterEtatop",  &CTouterEtatop );
       t1->SetBranchAddress("CTstripChargeSeedChargeRescaled",  &CTstripChargeSeedChargeRescaled );
       t1->SetBranchAddress("CTstripChargeTotChargeRescaled",  &CTstripChargeTotChargeRescaled );
       t1->SetBranchAddress("CTmuonsIsGlobal",  &CTmuonsIsGlobal );
       t1->SetBranchAddress("CTmuonsIsTracker",  &CTmuonsIsTracker );
       t1->SetBranchAddress("CTMuOrigin",  &CTMuOrigin );
       t1->SetBranchAddress("CTtof",  &CTtof );
       t1->SetBranchAddress("CTtofImproved",  &CTtofImproved );
       t1->SetBranchAddress("CTglobalX",  &CTglobalX );
       t1->SetBranchAddress("CTglobalY",  &CTglobalY );
       t1->SetBranchAddress("CTglobalZ",  &CTglobalZ );
       t1->SetBranchAddress("CTlocalX",  &CTlocalX );
       t1->SetBranchAddress("clusterstereo",  &clusterstereo );

   ///adata always first
    

   uint32_t evCount=0;
   vector<uint32_t> eventCount;
   
   //cout << "in here a" << endl;
   Int_t nentries = (Int_t)t1->GetEntries();

  // cout << "in here b" << endl;
   ///fill variables from tree 1
   for (Int_t e=0; e<nentries; e++) 
   {
       t1->GetEntry(e);
          
   //cout << "in here b1" << endl;
           //per cluster
           //subnroftracks.push_back(nroftracks);
           //subnrofevents.push_back(nrofevents);
           //perstrip
           uint32_t upStrip = CTstripChargeSubdetid->size();
   //cout << "in here b2" << endl;
           for(uint32_t k=0; k<upStrip;k++)
           {
               if( true)
               {
                   if(true ) //@MJ@ TODO trigger
                   {
   //cout << "in here b3" << endl;
                       subCTstripChargeSubdetid.push_back(CTstripChargeSubdetid->at(k));
                       subCTstripCharge.push_back(CTstripCharge->at(k));
                       subCTstripChargeLayerwheel.push_back(CTstripChargeLayerwheel->at(k));
                       //subCTstripChargeStripNr.push_back(CTstripChargeStripNr->at(k));
                       subCTstripChargeTotWidth.push_back(CTstripChargeTotWidth->at(k));
                       subCTstripChargeTotCharge.push_back(CTstripChargeTotCharge->at(k));
                       subCTstripChargeLocalTrackPhi.push_back(CTstripChargeLocalTrackPhi->at(k));
                       //subCTstripChargeGlobalTrackPhi.push_back(CTstripChargeGlobalTrackPhi->at(k));
                       subCTstripChargeLocalTrackTheta.push_back(CTstripChargeLocalTrackTheta->at(k));
                       subCTstripChargeGlobalTrackTheta.push_back(CTstripChargeGlobalTrackTheta->at(k));
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
                       subCTinnerVX.push_back(CTinnerVX->at(k));
                       subCTinnerVY.push_back(CTinnerVY->at(k));
                       subCTouterXtop.push_back(CTouterXtop->at(k));
                       subCTouterYtop.push_back(CTouterYtop->at(k));
                       subCTouterZtop.push_back(CTouterZtop->at(k));
                       subCTouterEtatop.push_back(CTouterEtatop->at(k));
                       subCTglobalX.push_back(CTglobalX->at(k));
                       subCTglobalY.push_back(CTglobalY->at(k));
                       subCTglobalZ.push_back(CTglobalZ->at(k));
                       subCTlocalX.push_back(CTlocalX->at(k));

                       subCTstripChargeSeedChargeRescaled.push_back(CTstripChargeSeedChargeRescaled->at(k));
                       subCTstripChargeTotChargeRescaled.push_back(CTstripChargeTotChargeRescaled->at(k));
                       subCTmuonsIsGlobal.push_back(CTmuonsIsGlobal->at(k));
                       subCTmuonsIsTracker.push_back(CTmuonsIsTracker->at(k));
                       subCTtof.push_back(CTtof->at(k));
                       subCTtofImproved.push_back(CTtofImproved->at(k));
                       //cout << "in here workaround 1" << endl;
                       //@MJ@ TODO temporary workaround
                       if( (k+2 > CTMuOrigin->size() ) || (CTMuOrigin->size()==0 && k==0) ) //finish this
                       {
                           subCTMuOrigin.push_back(3);
                           //cout << "why are you making so many mistakes?! " << endl;
                       }
                       else
                       { 
                           //cout << " k " << k << " size " << CTMuOrigin->size()<< endl;
                           subCTMuOrigin.push_back(CTMuOrigin->at(k));
                       }
                       //cout << "in here workaround 2" << endl;
                   }
               }
           }
  // cout << "in here c 1" << endl;
           
           for(uint32_t j=0; j<tsosrhglobalphi->size() ;j++)//@MJ@ TODO just temporaray
           {
               //cout << " size 1 " <<  tsosrhglobalphi->size() << " size 2 " << clusterdetid->size()<< " j " << j << endl;
               subtsosrhglobalphi.push_back(tsosrhglobalphi->at(j));
               subclusterdetid.push_back(clusterdetid->at(j));
               subclusterstereo.push_back(clusterstereo->at(j));
           }
   }

 //  cout << "in here c" << endl;


       TFile fE("TreeForE.root", "recreate");
       TTree tE("tE" , "tE");
       float eSubdetid;
       float eLayerWheel;
       float eChn1right;
       float eChn2right;
       float eChn1left;
       float eChn2left;
       float eChSeed;
       float eChTot;
       float eTime;
       tE.Branch("eSubdetid", &eSubdetid);
       tE.Branch("eLayerWheel", &eLayerWheel);
       tE.Branch("eChn1right", &eChn1right);
       tE.Branch("eChn2right", &eChn2right);
       tE.Branch("eChn1left", &eChn1left);
       tE.Branch("eChn2left", &eChn2left);
       tE.Branch("eChSeed", &eChSeed);
       tE.Branch("eChTot", &eChTot);
       tE.Branch("eTime", &eTime);

       

       //F
       vector<TH1F*> narrowTrackSharing1Data;
       vector<TH1F*> narrowTrackSharing2Data;
       vector<TH1F*> narrowTrackSharing1DataUp;
       vector<TH1F*> narrowTrackSharing2DataUp;
       vector<TH1F*> narrowTrackSharing1DataDown;
       vector<TH1F*> narrowTrackSharing2DataDown;


       vector< vector<TH1F*> > narrowTrackSharing1DataEvolution;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL1;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL2;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL3;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL4;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL1;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL2;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL3;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL4;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionDist;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionDist;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolution;
       vector< vector<TCanvas*> > narrowTrackSharing1DataEvolutionCan;
       vector< vector<TCanvas*> > narrowTrackSharing1DataEvolutionDistCan;
       vector< vector<TCanvas*> > narrowTrackSharing2DataEvolutionDistCan;
       vector< vector<TCanvas*> > narrowTrackSharing2DataEvolutionCan;



       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL1m;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL1s;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL2m;
       vector< vector<TH1F*> > narrowTrackSharing1DataEvolutionL2s;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL1m;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL1s;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL2m;
       vector< vector<TH1F*> > narrowTrackSharing2DataEvolutionL2s;


       vector<TH1F*> timingError;
       vector<TCanvas*> timingErrorCan;

       vector<TProfile*> np1Evolution;
       vector<TProfile*> np2Evolution;
       vector<TProfile*> nm1Evolution;
       vector<TProfile*> nm2Evolution;
       vector<TProfile*>  nSeedEvolution;
       vector<TCanvas*> np1EvolutionCan;
       vector<TCanvas*> np2EvolutionCan;
       vector<TCanvas*> nm1EvolutionCan;
       vector<TCanvas*> nm2EvolutionCan;
       vector<TCanvas*>  nSeedEvolutionCan;

       vector<TH1F*> timingDirection;
       vector<TCanvas*> timingDirectionCan;

       vector<TProfile*> width;
       vector<TProfile*> widthAsCosPhi;
       vector<TProfile*> charge;
       vector<TProfile*> chargePerUnit;
       vector<TProfile*> chargePerUnitGlobal;
       vector<TProfile*> chargePerUnitTracker;
       vector<TProfile*> chargePerUnitBeta;
       vector<vector<TProfile*> > chargePerUnitBins;
       vector<TH1F*> chargePerUnitBinsFit;
       //TH1F* chargePerUnitLayersBinsFit;
       //TCanvas* chargePerUnitLayersBinsFitCan;
       vector<TH1F*> chargePerUnitHist;
       vector<TH1F*> thetaSmall;
       vector<TH1F*> thetaLarge;
       vector<TH1F*> timing;
       vector<TH1F*> timingNC;
       vector<TH1F*> beta;
      


       vector<TProfile*> chargeCenter;
       vector<TProfile*> chargeEdge;
       vector<TCanvas*> chargeCenterCan;
       vector<TCanvas*> chargeEdgeCan;
       vector<TH1F*> innerZ;
       vector<TCanvas*> innerZCan;
       vector<TH1F*> innerVZ;
       vector<TCanvas*> innerVZCan;
       vector<TH1F*> innerVX;
       vector<TCanvas*> innerVXCan;
       vector<TH1F*> innerVY;
       vector<TCanvas*> innerVYCan;


       vector<TProfile*> timeVsVz;
       vector<TCanvas*> timeVsVzCan;

       vector<TProfile*> betaVsVx;
       vector<TCanvas*> betaVsVxCan;
       vector<TProfile*> betaVsVy;
       vector<TCanvas*> betaVsVyCan;
       vector<TProfile*> betaVsVz;
       vector<TCanvas*> betaVsVzCan;
       vector<TProfile*> betaVsDist;
       vector<TCanvas*> betaVsDistCan;
       vector<TProfile*> betaVsTime;
       vector<TCanvas*> betaVsTimeCan;

       vector<TH2F*> vnrOfHitsVsError;
       vector<TH2F*> nrOfSectorsVsError;
       vector<TH2F*> chargeVsFreeInverseBeta;

       vector<TCanvas*> vnrOfHitsVsErrorCan;
       vector<TCanvas*> nrOfSectorsVsErrorCan;
       vector<TCanvas*> chargeVsFreeInverseBetaCan;

       vector<TCanvas*> narrowTrackSharing1DataCan;
       vector<TCanvas*> narrowTrackSharing2DataCan;


       vector<TCanvas*> widthCan;
       vector<TCanvas*> widthAsCosPhiCan;

       vector<TCanvas*> chargeCan;
       vector<TCanvas*> timingCan;
       vector<TCanvas*> betaCan;
       vector<TCanvas*> chargePerUnitCan;
       vector<TCanvas*> chargePerUnitHistCan;
       vector<TCanvas*> thetaCan;
       vector<TCanvas*>  chargePerUnitBinsCan;
       vector<TCanvas*>  chargePerUnitBinsFitCan;

       vector<TProfile*> etaOneaAsVz;
       etaOneaAsVz.resize(20, NULL);
       vector<TCanvas*> etaOneaAsVzCan;
       etaOneaAsVzCan.resize(20, NULL);

       timeVsVz.resize(20, NULL);
       timeVsVzCan.resize(20, NULL);

       betaVsVx.resize(20, NULL);
       betaVsVxCan.resize(20, NULL);
       betaVsVy.resize(20, NULL);
       betaVsVyCan.resize(20, NULL);
       betaVsVz.resize(20, NULL);
       betaVsVzCan.resize(20, NULL);
       betaVsDist.resize(20, NULL);
       betaVsDistCan.resize(20, NULL);
       betaVsTime.resize(20, NULL);
       betaVsTimeCan.resize(20, NULL);

       vector<TH1F*> etaOneaAsTime;
       etaOneaAsTime.resize(20, NULL);
       vector<TCanvas*> etaOneaAsTimeCan;
       etaOneaAsTimeCan.resize(20, NULL);

       vector<TH1F*> xtZero;
       xtZero.resize(20, NULL);
       vector<TCanvas*> xtZeroCan;
       xtZeroCan.resize(20, NULL);

       vector<TH1F*> xtOne;
       xtOne.resize(20, NULL);
       vector<TCanvas*> xtOneCan;
       xtOneCan.resize(20, NULL);

       vector<TH1F*> xtTwo;
       xtTwo.resize(20, NULL);
       vector<TCanvas*> xtTwoCan;
       xtTwoCan.resize(20, NULL);

       vector<TH1F*> etaTwoAsTime;
       etaTwoAsTime.resize(20, NULL);
       vector<TCanvas*> etaTwoAsTimeCan;
       etaTwoAsTimeCan.resize(20, NULL);

       vector<vector<TH1F*> >  etaOneaAsTimeLayer;
       etaOneaAsTimeLayer.resize(20);
       vector<TCanvas*> etaOneaAsTimeLayerCan;
       etaOneaAsTimeLayerCan.resize(20, NULL);


       vector<vector<TH1F*> >  etaTwoAsTimeLayer;
       etaTwoAsTimeLayer.resize(20);
       vector<TCanvas*> etaTwoAsTimeLayerCan;
       etaTwoAsTimeLayerCan.resize(20, NULL);


       vector<vector<TH1F*> >  etaOneaAsTimeMonoStereo;
       etaOneaAsTimeMonoStereo.resize(20);
       vector<TCanvas*> etaOneaAsTimeMonoStereoCan;
       etaOneaAsTimeMonoStereoCan.resize(20, NULL);


       vector<vector<TH1F*> >  etaTwoAsTimeMonoStereo;
       etaTwoAsTimeMonoStereo.resize(20);
       vector<TCanvas*> etaTwoAsTimeMonoStereoCan;
       etaTwoAsTimeMonoStereoCan.resize(20, NULL);

       vector<TH1F*> etaOneaAsDist;
       etaOneaAsDist.resize(20, NULL);
       vector<TCanvas*> etaOneaAsDistCan;
       etaOneaAsDistCan.resize(20, NULL);

       vector<TH1F*> etaTwoAsDist;
       etaTwoAsDist.resize(20, NULL);
       vector<TCanvas*> etaTwoAsDistCan;
       etaTwoAsDistCan.resize(20, NULL);


       chargeCenter.resize(20, NULL);
       chargeEdge.resize(20, NULL);
       chargeCenterCan.resize(20, NULL);
       chargeEdgeCan.resize(20, NULL);


       innerZ.resize(20, NULL);
       innerZCan.resize(20, NULL);
       innerVZ.resize(20, NULL);
       innerVZCan.resize(20, NULL);
       innerVX.resize(20, NULL);
       innerVXCan.resize(20, NULL);
       innerVY.resize(20, NULL);
       innerVYCan.resize(20, NULL);


       narrowTrackSharing1Data.resize(20, NULL);
       narrowTrackSharing2Data.resize(20, NULL);
       narrowTrackSharing1DataUp.resize(20, NULL);
       narrowTrackSharing2DataUp.resize(20, NULL);
       narrowTrackSharing1DataDown.resize(20, NULL);
       narrowTrackSharing2DataDown.resize(20, NULL);
       narrowTrackSharing1DataCan.resize(20, NULL);
       narrowTrackSharing2DataCan.resize(20, NULL);




       width.resize(20, NULL);
       widthAsCosPhi.resize(20, NULL);
       charge.resize(20, NULL);
       chargePerUnit.resize(20, NULL);
       chargePerUnitGlobal.resize(20, NULL);
       chargePerUnitTracker.resize(20, NULL);
       chargePerUnitBeta.resize(20, NULL);
       chargePerUnitHist.resize(20, NULL);
       thetaSmall.resize(20, NULL);
       thetaLarge.resize(20, NULL);
       chargePerUnitBins.resize(20);
       chargePerUnitBinsFit.resize(20, NULL);
       widthCan.resize(20, NULL);
       widthAsCosPhiCan.resize(20, NULL);
       chargeCan.resize(20, NULL);
       chargePerUnitCan.resize(20, NULL);
       chargePerUnitHistCan.resize(20, NULL);
       thetaCan.resize(20, NULL);
       chargePerUnitBinsCan.resize(20, NULL);
       chargePerUnitBinsFitCan.resize(20, NULL);


       timing.resize(20, NULL);
       timingNC.resize(20, NULL);
       beta.resize(20, NULL);
       timingCan.resize(20, NULL);
       betaCan.resize(20, NULL);

       np1Evolution.resize(20, NULL);
       np1EvolutionCan.resize(20, NULL);
       np2Evolution.resize(20, NULL);
       np2EvolutionCan.resize(20, NULL);
       nm1Evolution.resize(20, NULL);
       nm1EvolutionCan.resize(20, NULL);
       nm2Evolution.resize(20, NULL);
       nm2EvolutionCan.resize(20, NULL);
       nSeedEvolution.resize(20, NULL);
       nSeedEvolutionCan.resize(20, NULL);

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


       
       narrowTrackSharing1DataEvolution.resize(20);
       narrowTrackSharing1DataEvolutionL1.resize(20);
       narrowTrackSharing1DataEvolutionL2.resize(20);
       narrowTrackSharing1DataEvolutionL3.resize(20);
       narrowTrackSharing1DataEvolutionL4.resize(20);
       narrowTrackSharing2DataEvolutionL1.resize(20);
       narrowTrackSharing2DataEvolutionL2.resize(20);
       narrowTrackSharing2DataEvolutionL3.resize(20);
       narrowTrackSharing2DataEvolutionL4.resize(20);
       narrowTrackSharing1DataEvolutionDist.resize(20);
       narrowTrackSharing2DataEvolutionDist.resize(20);
       narrowTrackSharing2DataEvolution.resize(20);
       narrowTrackSharing1DataEvolutionCan.resize(20);
       narrowTrackSharing1DataEvolutionDistCan.resize(20);
       narrowTrackSharing2DataEvolutionDistCan.resize(20);
       narrowTrackSharing2DataEvolutionCan.resize(20);

       narrowTrackSharing1DataEvolutionL1m.resize(20);
       narrowTrackSharing1DataEvolutionL1s.resize(20);
       narrowTrackSharing1DataEvolutionL2m.resize(20);
       narrowTrackSharing1DataEvolutionL2s.resize(20);
       narrowTrackSharing2DataEvolutionL1m.resize(20);
       narrowTrackSharing2DataEvolutionL1s.resize(20);
       narrowTrackSharing2DataEvolutionL2m.resize(20);
       narrowTrackSharing2DataEvolutionL2s.resize(20);


       TProfile*  chargeThroughTracker=  new TProfile("chargeThroughTracker", "chargeThroughTracker" , 25, 0, 25, 0, 500 ) ;
       TProfile*  widthThroughTracker=  new TProfile("widthThroughTracker", "widthThroughTracker" , 25, 0, 25, 0, 15 ) ;
       TH1F*  chargeThroughTrackerTIBtop=  new TH1F("chargeThroughTrackerTIBtop", "chargeThroughTrackerTIBtop",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTIBbottom=  new TH1F("chargeThroughTrackerTIBbottom", "chargeThroughTrackerTIBbottom",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTOBtop=  new TH1F("chargeThroughTrackerTOBtop", "chargeThroughTrackerTOBtop",  500, 0, 1000 ) ;
       TH1F*  chargeThroughTrackerTOBbottom=  new TH1F("chargeThroughTrackerTOBbottom", "chargeThroughTrackerTOBbottom",  500, 0, 1000 ) ;

       //joint plots for layers
       TProfile*  chargePerUnitLayers =  new TProfile("chargePerUnitLayers", "chargePerUnitLayers" , 30, -15, 15, 1000, 5000 ) ;
       TH1F*  chargePerUnitLayersBinsFit =  new TH1F("chargePerUnitLayerssBinsFit ", "chargePerUnitLayerssBinsFit" , 10000, 0, 100 ) ;
       TCanvas*  chargePerUnitLayersBinsFitCan =  new TCanvas("chargePerUnitLayerssBinsFitCan", "chargePerUnitLayerssBinsFitCan"  ) ;
       TProfile*  chargePerUnitLayersGlobal =  new TProfile("chargePerUnitLayersGlobal", "chargePerUnitLayersGlobal" , 30, -15, 15, 1000, 5000 ) ;
       TProfile*  chargePerUnitLayersTracker =  new TProfile("chargePerUnitLayersTracker", "chargePerUnitLayersTracker" , 30, -15, 15, 1000, 5000 ) ;
       TProfile*  chargePerUnitLayersBeta =  new TProfile("chargePerUnitLayersBeta", "chargePerUnitLayersBeta" , 30, -15, 15, 1000, 5000 ) ;

       vector<TProfile*>  chargePerUnitLayersBins;
       chargePerUnitLayersBins.resize(4,NULL) ;
       for(uint32_t g=0; g<4; g++)
       {
           chargePerUnitLayersBins.at(g) =  new TProfile("chargePerUnitLayersBins", "chargePerUnitLayersBins" , 15, -20, 10 ) ;
       }
       TH1F*  chargePerUnitHistLayers =  new TH1F("chargePerUnitHistLayers", "chargePerUnitHistLayers" , 80, 0, 8000 ) ;
       TProfile*  timeVsVzLayers =  new TProfile("timeVsVzLayers", "timeVsVzLayers" , 30, -150, 150 ) ;
       TProfile*  timeVsVxLayers =  new TProfile("timeVsVxLayers", "timeVsVyLayers" , 50, -50, 50 ) ;
       TProfile*  timeVsVyLayers =  new TProfile("timeVsVyLayers", "timeVsVyLayers" , 50, -50, 50 ) ;
       TProfile*  timeVsDistLayers =  new TProfile("timeVsDistLayers", "timeVsDistLayers" , 15, 0, 150 ) ;
       TH2F*  timeVsDistLayers2D =  new TH2F("timeVsDistLayers2D", "timeVsDistLayers2D" , 15, 0, 150, 50, -30,50 ) ;
       TProfile*  timeVsVzLayersNotZCorr =  new TProfile("timeVsVzLayersNotZCorr", "timeVsVzLayersNotZCorr" , 30, -150, 150 ) ;
       TProfile*  timeVsDistLayersNotDistCorr =  new TProfile("timeVsDistLayersNotDistCorr", "timeVsDistLayersNotDistCorr" , 15, 0, 150 ) ;
       TCanvas*  chargePerUnitLayersCan =  new TCanvas("chargePerUnitLayers", "chargePerUnitLayers" ) ;
       TCanvas*  chargePerUnitLayersBinsCan =  new TCanvas("chargePerUnitLayersBins", "chargePerUnitLayersBins" ) ;
       TCanvas*  chargePerUnitHistLayersCan =  new TCanvas("chargePerUnitHistLayers", "chargePerUnitHistLayers" ) ;
       TCanvas*  timeVsVzLayersCan =  new TCanvas("timeVsVzLayers", "timeVsVzLayers" ) ;
       TCanvas*  timeVsVxLayersCan =  new TCanvas("timeVsVxLayers", "timeVsVxLayers" ) ;
       TCanvas*  timeVsVyLayersCan =  new TCanvas("timeVsVyLayers", "timeVsVyLayers" ) ;
       TCanvas*  timeVsDistLayersCan =  new TCanvas("timeVsDistLayers", "timeVsDistLayers" ) ;
       TCanvas*  timeVsDistLayers2DCan =  new TCanvas("timeVsDistLayers2D", "timeVsDistLayers2D" ) ;
       TCanvas*  timeVsVzLayersNotZCorrCan =  new TCanvas("timeVsVzLayersNotZCorr", "timeVsVzLayersNotZCorr" ) ;
       TCanvas*  timeVsDistLayersNotDistCorrCan =  new TCanvas("timeVsDistLayersNotDistCorr", "timeVsDistLayersNotDistCorr" ) ;

       TH1F*  localTheta =  new TH1F("localTheta", "localTheta" , 100 , 0, 4 ) ;
       TH1F*  localPhi =  new TH1F("localPhi", "localPhi" , 200 , 4, 4 ) ;
       TCanvas*   localThetaCan =  new TCanvas("localThetaCan", "localThetaCan" ) ;
       TCanvas*   localPhiCan =  new TCanvas("localPhiCan", "localPhiCan" ) ;


       TH1F* narrowTrackSharing1DataTot = new TH1F( "narrowTrackSharing1Tot", "narrowTrackSharing1Tot" , 200, -1, 1 );
       TH1F* narrowTrackSharing2DataTot = new TH1F( "narrowTrackSharing2Tot", "narrowTrackSharing2Tot" , 200, -1, 1 );

       TCanvas* narrowTrackSharing1DataTotCan = new TCanvas( "cnarrowTrackSharing1Tot", "cnarrowTrackSharing1Tot" );
       TCanvas* narrowTrackSharing2DataTotCan = new TCanvas( "cnarrowTrackSharing2Tot", "cnarrowTrackSharing2Tot" );


       vector< vector< vector<float> > > timeMedian;
       timeMedian.resize(20);
       vector< vector<float> >  timeMedianLayers;
       timeMedianLayers.resize(4);
       

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
           //if( abs(tan(subCTstripChargeLocalTrackTheta.at(clusterStart))) < narrowness*(subCTstripChargelocalpitch.at(clusterStart)/subCTstripChargesensorThickness.at(clusterStart)) )
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
                       narrowTrackSharing1Data.at(partPos) = new TH1F( ("narrowTrackSharing1"+ parName).c_str() , ("narrowTrackSharing1"+parName).c_str() , 100, -1, 1 );
                       narrowTrackSharing1DataUp.at(partPos) = new TH1F( ("narrowTrackSharing1Up"+ parName).c_str() , ("narrowTrackSharing1Up"+parName).c_str() , 100, -1, 1 );
                       narrowTrackSharing1DataDown.at(partPos) = new TH1F( ("narrowTrackSharing1Down"+ parName).c_str() , ("narrowTrackSharing1Down"+parName).c_str() , 100, -1, 1 );
                       narrowTrackSharing1DataCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing1"+ parName).c_str() , ("cnarrowTrackSharing1"+parName).c_str()  );
                       narrowTrackSharing1DataEvolution.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionL1.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionL2.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionL3.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionL4.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL1.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL2.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL3.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL4.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionDist.at(partPos).resize(200, NULL);
                       narrowTrackSharing2DataEvolutionDist.at(partPos).resize(200, NULL);
                       narrowTrackSharing1DataEvolutionDist.at(partPos).resize(200, NULL);

                       narrowTrackSharing1DataEvolutionL1m.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionL1s.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionL2m.at(partPos).resize(120, NULL);
                       narrowTrackSharing1DataEvolutionL2s.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL1m.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL1s.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL2m.at(partPos).resize(120, NULL);
                       narrowTrackSharing2DataEvolutionL2s.at(partPos).resize(120, NULL);


                       //narrowTrackSharing1DataEvolutionCan.at(partPos).resize(40, NULL);
                       for(uint32_t v=0; v<120; v++)
                       {
                           narrowTrackSharing1DataEvolution.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1Evolution"+ parName).c_str() , ("narrowTrackSharing1Evolution"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing1DataEvolutionL1.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL1"+ parName).c_str() , ("narrowTrackSharing1EvolutionL1"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing1DataEvolutionL2.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL2"+ parName).c_str() , ("narrowTrackSharing1EvolutionL2"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing1DataEvolutionL3.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL3"+ parName).c_str() , ("narrowTrackSharing1EvolutionL3"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing1DataEvolutionL4.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL4"+ parName).c_str() , ("narrowTrackSharing1EvolutionL4"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL1.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL1"+ parName).c_str() , ("narrowTrackSharing2EvolutionL1"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL2.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL2"+ parName).c_str() , ("narrowTrackSharing2EvolutionL2"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL3.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL3"+ parName).c_str() , ("narrowTrackSharing2EvolutionL3"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL4.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL4"+ parName).c_str() , ("narrowTrackSharing2EvolutionL4"+parName).c_str() , 50, -1, 1 );


                           narrowTrackSharing1DataEvolutionL1m.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL1m"+ parName).c_str() , ("narrowTrackSharing1EvolutionL1m"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing1DataEvolutionL1s.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL1s"+ parName).c_str() , ("narrowTrackSharing1EvolutionL1s"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing1DataEvolutionL2m.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL2m"+ parName).c_str() , ("narrowTrackSharing1EvolutionL2m"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing1DataEvolutionL2s.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionL2s"+ parName).c_str() , ("narrowTrackSharing1EvolutionL2s"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL1m.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL1m"+ parName).c_str() , ("narrowTrackSharing2EvolutionL1m"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL1s.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL1s"+ parName).c_str() , ("narrowTrackSharing2EvolutionL1s"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL2m.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL2m"+ parName).c_str() , ("narrowTrackSharing2EvolutionL2m"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionL2s.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionL2s"+ parName).c_str() , ("narrowTrackSharing2EvolutionL2s"+parName).c_str() , 50, -1, 1 );

                           //narrowTrackSharing1DataEvolutionCan.at(partPos).at(v) = new TCanvas( ("cnarrowTrackSharing1Evolution"+ parName).c_str() , ("cnarrowTrackSharing1Evolution"+parName).c_str());
                           //narrowTrackSharing1DataEvolutionCan.at(partPos).at(v)->cd();
                           //cout << "canvas address 1 " << narrowTrackSharing1DataEvolutionCan.at(partPos).at(v) << endl;
                       }                       
                       for(uint32_t v=0; v<200; v++)
                       {
                           narrowTrackSharing1DataEvolutionDist.at(partPos).at(v) = new TH1F( ("narrowTrackSharing1EvolutionDist"+ parName).c_str() , ("narrowTrackSharing1EvolutionDist"+parName).c_str() , 50, -1, 1 );
                           narrowTrackSharing2DataEvolutionDist.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2EvolutionDist"+ parName).c_str() , ("narrowTrackSharing2EvolutionDist"+parName).c_str() , 50, -1, 1 );
                       }                       
                       canvases.push_back(parName);
  // cout << "in here 2.1" << endl;
                   }
                   if(narrowTrackSharing2Data.at(partPos) == NULL)
                   {
                       narrowTrackSharing2Data.at(partPos) = new TH1F( ("narrowTrackSharing2"+ parName).c_str() , ("narrowTrackSharing2"+parName).c_str() , 100, -1, 1 );
 //  cout << "in here 2.1" << endl;
                       narrowTrackSharing2DataUp.at(partPos) = new TH1F( ("narrowTrackSharing2Up"+ parName).c_str() , ("narrowTrackSharing2Up"+parName).c_str() , 100, -1, 1 );
  // cout << "in here 2.1a" << endl;
                       narrowTrackSharing2DataDown.at(partPos) = new TH1F( ("narrowTrackSharing2Down"+ parName).c_str() , ("narrowTrackSharing2Down"+parName).c_str() , 100, -1, 1 );
  // cout << "in here 2.1b" << endl;
                       narrowTrackSharing2DataCan.at(partPos) = new TCanvas( ("cnarrowTrackSharing2"+ parName).c_str() , ("cnarrowTrackSharing2"+parName).c_str());
 //  cout << "in here 2.1c" << endl;
                       narrowTrackSharing2DataEvolution.at(partPos).resize(120, NULL);
 //  cout << "in here 2.1d" << endl;
                       chargePerUnitBins.at(partPos).resize(4, NULL);
 ///  cout << "in here 2.1e" << endl;
                       timeMedian.at(partPos).resize(4);
 //  cout << "in here 2.1f" << endl;
                       etaOneaAsTimeLayer.at(partPos).resize(4, NULL);
  // cout << "in here 2.1g" << endl;
                       etaTwoAsTimeLayer.at(partPos).resize(4, NULL);
 //  cout << "in here 2.1h" << endl;
                       etaOneaAsTimeMonoStereo.at(partPos).resize(4, NULL);
  // cout << "in here 2.1i" << endl;
                       etaTwoAsTimeMonoStereo.at(partPos).resize(4, NULL);
 //  cout << "in here 2.1j" << endl;
                       chargePerUnitBinsCan.at(partPos) =  new TCanvas(("chargePerUnitBins"+ parName).c_str() , ("chargePerUnitBins"+parName).c_str()) ;
 //  cout << "in here 2.1k" << endl;
                       chargePerUnitBinsFitCan.at(partPos) =  new TCanvas(("cchargePerUnitBinsFit"+ parName).c_str() , ("cchargePerUnitBinsFit"+parName).c_str()) ;
 //  cout << "in here 2.1l" << endl;
                       chargePerUnitBinsFit.at(partPos) =  new TH1F(("chargePerUnitBinsFit"+ parName).c_str() , ("chargePerUnitBinsFit"+parName).c_str(), 10000, 0, 100) ;
 //  cout << "in here 2.1m" << endl;

                       for(uint32_t v=0; v<4; v++)
                       {
                           chargePerUnitBins.at(partPos).at(v) = new TProfile( ("chargePerUnitBins"+ parName).c_str() , ("chargePerUnitBins"+parName).c_str() , 10, -20, 10 );
		           etaOneaAsTimeLayer.at(partPos).at(v) =  new TH1F(("etaOneaAsTimeLayer"+ parName).c_str(), ("etaOneaAsTimeLayer"+ parName).c_str() , 120, -60, 60 ) ;
		           etaTwoAsTimeLayer.at(partPos).at(v) =  new TH1F(("etaTwoAsTimeLayer"+ parName).c_str(), ("etaTwoAsTimeLayer"+ parName).c_str() , 120, -60, 60 ) ;
		           etaOneaAsTimeMonoStereo.at(partPos).at(v) =  new TH1F(("etaOneaAsTimeMonoStereo"+ parName).c_str(), ("etaOneaAsTimeMonoStereo"+ parName).c_str() , 120, -60, 60 ) ;
		           etaTwoAsTimeMonoStereo.at(partPos).at(v) =  new TH1F(("etaTwoAsTimeMonoStereo"+ parName).c_str(), ("etaTwoAsTimeMonoStereo"+ parName).c_str() , 120, -60, 60 ) ;
                       }                       
   cout << "in here 2.1" << endl;
                       for(uint32_t v=0; v<120; v++)
                       {
                           narrowTrackSharing2DataEvolution.at(partPos).at(v) = new TH1F( ("narrowTrackSharing2Evolution"+ parName).c_str() , ("narrowTrackSharing2Evolution"+parName).c_str() , 50, -1, 1 );
                           //narrowTrackSharing2DataEvolutionCan.at(partPos).at(v) = new TCanvas( ("cnarrowTrackSharing2Evolution"+ parName).c_str() , ("cnarrowTrackSharing2Evolution"+parName).c_str() );
                       }                       
   cout << "in here 2.2" << endl;
                   }

                   if(width.at(partPos) == NULL)
                   {
		       width.at(partPos) =  new TProfile(("width"+ parName).c_str(), ("width"+ parName).c_str() , 200, -100, 100, 0, 10 ) ;
		       widthAsCosPhi.at(partPos) =  new TProfile(("widthAsCosPhi"+ parName).c_str(), ("widthAsCosPhi"+ parName).c_str() , 10, -1, 1, 0, 10 ) ;

		       charge.at(partPos)=  new TProfile(("charge"+ parName).c_str(), ("charge"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       timing.at(partPos)=  new TH1F(("timing"+ parName).c_str(), ("timing"+ parName).c_str() , 80, -30, 50 ) ;
		       timingNC.at(partPos)=  new TH1F(("timingNC"+ parName).c_str(), ("timingNC"+ parName).c_str() , 80, -30, 50 ) ;

                       np1Evolution.at(partPos) = new TProfile(("np1Evolution"+ parName).c_str(), ("np1Evolution"+ parName).c_str() , 30, -20, 10 ); 
                       np2Evolution.at(partPos) = new TProfile(("np2Evolution"+ parName).c_str(), ("np2Evolution"+ parName).c_str() , 30, -20, 10 ); 
                       nm1Evolution.at(partPos) = new TProfile(("nm1Evolution"+ parName).c_str(), ("nm1Evolution"+ parName).c_str() , 30, -20, 10 ); 
                       nm2Evolution.at(partPos) = new TProfile(("nm2Evolution"+ parName).c_str(), ("nm2Evolution"+ parName).c_str() , 30, -20, 10 ); 
                       nSeedEvolution.at(partPos) = new TProfile(("nSeedEvolution"+ parName).c_str(), ("nSeedEvolution"+ parName).c_str() , 30, -20, 10 ); 

                       np1EvolutionCan.at(partPos) = new TCanvas(("np1EvolutionCan"+ parName).c_str(), ("np1EvolutionCan"+ parName).c_str() ); 
                       np2EvolutionCan.at(partPos) = new TCanvas(("np2EvolutionCan"+ parName).c_str(), ("np2EvolutionCan"+ parName).c_str()  ); 
                       nm1EvolutionCan.at(partPos) = new TCanvas(("nm1EvolutionCan"+ parName).c_str(), ("nm1EvolutionCan"+ parName).c_str() ); 
                       nm2EvolutionCan.at(partPos) = new TCanvas(("nm2EvolutionCan"+ parName).c_str(), ("nm2EvolutionCan"+ parName).c_str()  ); 
                       nSeedEvolutionCan.at(partPos) = new TCanvas(("nSeedEvolutionCan"+ parName).c_str(), ("nSeedEvolutionCan"+ parName).c_str() ); 

		       beta.at(partPos)=  new TH1F(("beta"+ parName).c_str(), ("beta"+ parName).c_str() , 100, -10, 10 ) ;
		       chargePerUnit.at(partPos)=  new TProfile(("chargePerUnit"+ parName).c_str(), ("chargePerUnit"+ parName).c_str() , 15, -20, 10 ) ;
		       chargePerUnitGlobal.at(partPos)=  new TProfile(("chargePerUnitGlobal"+ parName).c_str(), ("chargePerUnitGlobal"+ parName).c_str() , 200, -100, 100 ) ;
		       chargePerUnitTracker.at(partPos)=  new TProfile(("chargePerUnitTracker"+ parName).c_str(), ("chargePerUnitTracker"+ parName).c_str() , 200, -100, 100 ) ;
		       chargePerUnitBeta.at(partPos)=  new TProfile(("chargePerUnitBeta"+ parName).c_str(), ("chargePerUnitBeta"+ parName).c_str() , 200, -100, 100 ) ;
		       chargePerUnitHist.at(partPos)=  new TH1F(("chargePerUnitHist"+ parName).c_str(), ("chargePerUnitHist"+ parName).c_str() , 80, 0, 8000 ) ;
		       thetaSmall.at(partPos)=  new TH1F(("thetaSmall"+ parName).c_str(), ("thetaSmall"+ parName).c_str() , 30, -30, 30 ) ;
		       thetaLarge.at(partPos)=  new TH1F(("thetaLarge"+ parName).c_str(), ("thetaLarge"+ parName).c_str() , 30, -30, 30 ) ;

		       etaOneaAsVz.at(partPos) =  new TProfile(("etaOneaAsVz"+ parName).c_str(), ("etaOneaAsVz"+ parName).c_str() , 100, -150, 150, 0, 1000 ) ;
		       etaOneaAsTime.at(partPos) =  new TH1F(("etaOneaAsTime"+ parName).c_str(), ("etaOneaAsTime"+ parName).c_str() , 120, -60, 60 ) ;
		       xtZero.at(partPos) =  new TH1F(("xtZero"+ parName).c_str(), ("xtZero"+ parName).c_str() , 120, -60, 60 ) ;
		       xtOne.at(partPos) =  new TH1F(("xtOne"+ parName).c_str(), ("xtOne"+ parName).c_str() , 120, -60, 60 ) ;
		       xtTwo.at(partPos) =  new TH1F(("xtTwo"+ parName).c_str(), ("xtTwo"+ parName).c_str() , 120, -60, 60 ) ;
		       etaTwoAsTime.at(partPos) =  new TH1F(("etaTwoAsTime"+ parName).c_str(), ("etaTwoAsTime"+ parName).c_str() , 120, -60, 60 ) ;
		       etaOneaAsDist.at(partPos) =  new TH1F(("etaOneaAsDist"+ parName).c_str(), ("etaOneaAsDist"+ parName).c_str() , 200, -100, 100 ) ;
		       etaTwoAsDist.at(partPos) =  new TH1F(("etaTwoAsDist"+ parName).c_str(), ("etaTwoAsDist"+ parName).c_str() , 200, -100, 100 ) ;

		       timeVsVz.at(partPos) =  new TProfile(("timeVsVz"+ parName).c_str(), ("timeVsVz"+ parName).c_str() , 25, -150, 150) ;
		       betaVsVx.at(partPos) =  new TProfile(("betaVsVx"+ parName).c_str(), ("betaVsVx"+ parName).c_str() , 25, -50, 50) ;
		       betaVsVy.at(partPos) =  new TProfile(("betaVsVy"+ parName).c_str(), ("betaVsVy"+ parName).c_str() , 25, -20, 20) ;
		       betaVsVz.at(partPos) =  new TProfile(("betaVsVz"+ parName).c_str(), ("betaVsVz"+ parName).c_str() , 25, -150, 150) ;
		       betaVsDist.at(partPos) =  new TProfile(("betaVsDist"+ parName).c_str(), ("betaVsDist"+ parName).c_str() , 15, 0, 150, -1, 2) ;
		       betaVsTime.at(partPos) =  new TProfile(("betaVsTime"+ parName).c_str(), ("betaVsTime"+ parName).c_str() , 10, -20, 20, -1, 2) ;

   cout << "in here 2.3" << endl;
		       chargeCenter.at(partPos) =  new TProfile(("chargeCenter"+ parName).c_str(), ("chargeCenter"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeEdge.at(partPos) =  new TProfile(("chargeEdge"+ parName).c_str(), ("chargeEdge"+ parName).c_str() , 200, -100, 100, 0, 1000 ) ;
		       chargeCenterCan.at(partPos) =   new TCanvas( ("chargeCenterCan"+ parName).c_str(), ("chargeCenterCan"+ parName).c_str()) ;
		       chargeEdgeCan.at(partPos) =   new TCanvas( ("chargeEdgeCan"+ parName).c_str(), ("chargeEdgeCan"+ parName).c_str()) ;

		       innerZ.at(partPos) =  new TH1F(("innerZ"+ parName).c_str(), ("innerZ"+ parName).c_str() , 300, -300, 300 ) ;
		       innerZCan.at(partPos) =   new TCanvas( ("innerZ"+ parName).c_str(), ("innerZ"+ parName).c_str()) ;
		       innerVZ.at(partPos) =  new TH1F(("innerVZ"+ parName).c_str(), ("innerVZ"+ parName).c_str() , 300, -300, 300 ) ;
		       innerVZCan.at(partPos) =   new TCanvas( ("innerVZ"+ parName).c_str(), ("innerVZ"+ parName).c_str()) ;
		       innerVX.at(partPos) =  new TH1F(("innerVX"+ parName).c_str(), ("innerVX"+ parName).c_str() , 200, -100, 100 ) ;
		       innerVXCan.at(partPos) =   new TCanvas( ("innerVX"+ parName).c_str(), ("innerVX"+ parName).c_str()) ;
		       innerVY.at(partPos) =  new TH1F(("innerVY"+ parName).c_str(), ("innerVY"+ parName).c_str() , 200, -100, 100 ) ;
		       innerVYCan.at(partPos) =   new TCanvas( ("innerVY"+ parName).c_str(), ("innerVY"+ parName).c_str()) ;

   cout << "in here 2.4" << endl;
                       vnrOfHitsVsError.at(partPos) = new TH2F( ("vnrOfHitsVsError"+ parName).c_str(),("vnrOfHitsVsError"+ parName).c_str() , 40, 0, 20, 100 , 0, 60);
                       nrOfSectorsVsError.at(partPos) = new TH2F( ("nrOfSectorsVsError"+ parName).c_str(),("nrOfSectorsVsError"+ parName).c_str() , 10, 0, 10, 10 , 0, 10);
                       chargeVsFreeInverseBeta.at(partPos) = new TH2F( ("chargeVsFreeInverseBeta"+ parName).c_str(),("chargeVsFreeInverseBeta"+ parName).c_str() , 60, -20, 20, 100 , 0, 1000);



                       vnrOfHitsVsErrorCan.at(partPos) = new TCanvas( ("vnrOfHitsVsErrorCan"+ parName).c_str(),("vnrOfHitsVsErrorCan"+ parName).c_str());
                       nrOfSectorsVsErrorCan.at(partPos) = new TCanvas( ("nrOfSectorsVsErrorCan"+ parName).c_str(),("nrOfSectorsVsErrorCan"+ parName).c_str() );
                       chargeVsFreeInverseBetaCan.at(partPos) = new TCanvas( ("chargeVsFreeInverseBetaCan"+ parName).c_str(),("chargeVsFreeInverseBetaCan"+ parName).c_str() );


   cout << "in here 2.5" << endl;
		       widthCan.at(partPos) =   new TCanvas( ("width"+ parName).c_str(), ("width"+ parName).c_str()) ;
		       widthAsCosPhiCan.at(partPos) =   new TCanvas( ("widthAsCosPhi"+ parName).c_str(), ("widthAsCosPhi"+ parName).c_str()) ;

		       chargeCan.at(partPos)=   new TCanvas( ("charge"+ parName).c_str(), ("charge"+ parName).c_str()) ;
		       timingCan.at(partPos)=   new TCanvas( ("timing"+ parName).c_str(), ("timing"+ parName).c_str()) ;
		       betaCan.at(partPos)=   new TCanvas( ("beta"+ parName).c_str(), ("beta"+ parName).c_str()) ;
		       chargePerUnitCan.at(partPos)=   new TCanvas( ("chargePerUnit"+ parName).c_str(), ("chargePerUnit"+ parName).c_str()) ;
		       chargePerUnitHistCan.at(partPos)=   new TCanvas( ("chargePerUnitHist"+ parName).c_str(), ("chargePerUnitHist"+ parName).c_str()) ;
		       thetaCan.at(partPos)=   new TCanvas( ("theta"+ parName).c_str(), ("theta"+ parName).c_str()) ;


		       etaOneaAsVzCan.at(partPos) =   new TCanvas( ("etaOneaAsVzCan"+ parName).c_str(), ("etaOneaAsVzCan"+ parName).c_str()) ;
		       etaOneaAsTimeCan.at(partPos) =   new TCanvas( ("etaOneaAsTimeCan"+ parName).c_str(), ("etaOneaAsTimeCan"+ parName).c_str()) ;
		       xtZeroCan.at(partPos) =   new TCanvas( ("xtZeroCan"+ parName).c_str(), ("xtZeroCan"+ parName).c_str()) ;
		       xtOneCan.at(partPos) =   new TCanvas( ("xtOneCan"+ parName).c_str(), ("xtOneCan"+ parName).c_str()) ;
		       xtTwoCan.at(partPos) =   new TCanvas( ("xtTwoCan"+ parName).c_str(), ("xtTwoCan"+ parName).c_str()) ;
		       etaTwoAsTimeCan.at(partPos) =   new TCanvas( ("etaTwoAsTimeCan"+ parName).c_str(), ("etaTwoAsTimeCan"+ parName).c_str()) ;
		       etaOneaAsTimeLayerCan.at(partPos) =   new TCanvas( ("etaOneaAsTimeLayerCan"+ parName).c_str(), ("etaOneaAsTimeLayerCan"+ parName).c_str()) ;
		       etaTwoAsTimeLayerCan.at(partPos) =   new TCanvas( ("etaTwoAsTimeLayerCan"+ parName).c_str(), ("etaTwoAsTimeLayerCan"+ parName).c_str()) ;
		       etaOneaAsTimeMonoStereoCan.at(partPos) =   new TCanvas( ("etaOneaAsTimeMonoStereoCan"+ parName).c_str(), ("etaOneaAsTimeMonoStereoCan"+ parName).c_str()) ;
		       etaTwoAsTimeMonoStereoCan.at(partPos) =   new TCanvas( ("etaTwoAsTimeMonoStereoCan"+ parName).c_str(), ("etaTwoAsTimeMonoStereoCan"+ parName).c_str()) ;
		       etaOneaAsDistCan.at(partPos) =   new TCanvas( ("etaOneaAsDistCan"+ parName).c_str(), ("etaOneaAsDistCan"+ parName).c_str()) ;
		       etaTwoAsDistCan.at(partPos) =   new TCanvas( ("etaTwoAsDistCan"+ parName).c_str(), ("etaTwoAsDistCan"+ parName).c_str()) ;

   cout << "in here 2.6" << endl;

		       timeVsVzCan.at(partPos) =   new TCanvas( ("timeVsVzCan"+ parName).c_str(), ("timeVsVzCan"+ parName).c_str()) ;
		       betaVsVxCan.at(partPos) =   new TCanvas( ("betaVsVxCan"+ parName).c_str(), ("betaVsVxCan"+ parName).c_str()) ;
		       betaVsVyCan.at(partPos) =   new TCanvas( ("betaVsVyCan"+ parName).c_str(), ("betaVsVyCan"+ parName).c_str()) ;
		       betaVsVzCan.at(partPos) =   new TCanvas( ("betaVsVzCan"+ parName).c_str(), ("betaVsVzCan"+ parName).c_str()) ;
		       betaVsDistCan.at(partPos) =   new TCanvas( ("betaVsDistCan"+ parName).c_str(), ("betaVsDistCan"+ parName).c_str()) ;
		       betaVsTimeCan.at(partPos) =   new TCanvas( ("betaVsTimeCan"+ parName).c_str(), ("betaVsTimeCan"+ parName).c_str()) ;

                       timingError.at(partPos) = new TH1F( ("timingError"+ parName).c_str() , ("timingError"+parName).c_str() , 50, 0, 2 );
                       timingErrorCan.at(partPos) = new TCanvas( ("timingError"+ parName).c_str() , ("timingError"+parName).c_str() ) ;
                       

                       timingDirection.at(partPos) = new TH1F( ("timingDirection"+ parName).c_str() , ("timingDirection"+parName).c_str() , 4, -2, 2 );
                       timingDirectionCan.at(partPos) = new TCanvas( ("timingDirection"+ parName).c_str() , ("timingDirection"+parName).c_str() ) ;

   cout << "in here 2.7" << endl;
                       cout << "in here f" << endl;
                   }

                   
   cout << "in here 3" << endl;
                   float time = 0;
                   float timeNotZCorr = 0;
                   float timeErr = 0;
                   float tofCorr = 0;
                   float zCorr = 0;
                   float dCorr = 0;
                   float d2Corr = 0;

                   float distVtx = TMath::Sqrt( TMath::Power( subCTinnerVX.at(clusterStart),2 ) + TMath::Power( subCTinnerVY.at(clusterStart),2 ) + TMath::Power( subCTinnerVZtop.at(clusterStart),2 )  );
                   //float distVtx = subCTinnerVZtop.at(clusterStart);
                   float distFromVtx = TMath::Sqrt( TMath::Power( subCTinnerVX.at(clusterStart) -subCTglobalX.at(clusterStart) ,2 ) + TMath::Power( subCTinnerVY.at(clusterStart) - subCTglobalY.at(clusterStart),2 ) + TMath::Power( subCTinnerVZtop.at(clusterStart) - subCTglobalZ.at(clusterStart),2 )  );
                   float distGlobal = TMath::Sqrt( TMath::Power( subCTglobalX.at(clusterStart),2 ) + TMath::Power( subCTglobalY.at(clusterStart),2 ) + TMath::Power( subCTglobalZ.at(clusterStart),2 )  );
                   //float distDiffBot = distGlobal - distFromVtx;
                   double distDiffBotInNs = ((distGlobal - distFromVtx)/29979245800.0) *TMath::Power(10,9) ;
                   double distDiffTopInNs = (distGlobal/29979245800.0) *TMath::Power(10,9) ;
                   cout << "distDiffBotInNs  " << distDiffBotInNs << " distDiffTopInNs " << distDiffTopInNs << endl;
                   //double timeInSecImproved =  distance/299792458.0;
                   //double timeInNsImproved = timeInSecImproved*TMath::Power(10,9);
                   if(subCTMuOrigin.at(clusterStart) ==1)
                   {
                       //time  = subCTCmbtimeVtxr.at(clusterStart); 
                       //timeErr  = subCTCmbtimeVtxrErr.at(clusterStart); 
                       time  = subCTCmbtimeVtx.at(clusterStart); 
                       timeNotZCorr = time;
                       timeErr  = subCTCmbtimeVtxErr.at(clusterStart); 
                       if( hem == 1 ) //@MJ@ TODO -first z-correction and then TOF correction
                       {
                           //tofCorr = 2* subCTtofImproved.at(clusterStart) ;
                           timeNotZCorr = time;
                           //dCorr = 0.0351501*distVtx   ; // dist improved
                           //time-=dCorr;
                           //tofCorr = 2* distDiffTopInNs;
                           //time+=tofCorr;
                           //
                           //Chi2                      =      85.9722
                           //NDf                       =            9
                           //p0                        =    -0.282677   +/-   0.0418127   
                           //p1                        =    0.0351501   +/-   0.00099417
                       }
                       else if( hem == -1)
                       {
                           tofCorr = 0 ;
                           timeNotZCorr = time;
                           //dCorr = 0.0122072*distVtx   ; // dist improved
                           //time-=dCorr;
                           //tofCorr =distDiffBotInNs ;
                           //time-=tofCorr;
                           //
                           //Chi2                      =      38.8445
                           //NDf                       =            8
                           //p0                        =    -0.105947   +/-   0.0383298   
                           //p1                        =    0.0122072   +/-   0.000924563
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
                           //tofCorr = subCTtofImproved.at(clusterStart) ;
                           timeNotZCorr = time;
                           //dCorr = 0.00733513*distVtx   ; // dist improved
                           //time-=dCorr;
                           //tofCorr = distDiffTopInNs;
                           //time+=tofCorr;
                           //
                           //Chi2                      =       229.21
                           //NDf                       =           10
                           //p0                        =     -6.18775   +/-   0.0476985   
                           //p1                        =   0.00733513   +/-   0.000970881
                       }
                       else if(hem == -1)
                       {
                           tofCorr = 0;
                           timeNotZCorr = time;
                           //no correction
                           //tofCorr =distDiffBotInNs ;
                           //time-=tofCorr;
                           //time+=7;
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
                       cout << "you did a mistake again... ";
                       //throw std::runtime_error("Muon origin unknown");

                   //if( !(subCTstripChargeSubdetid.at(clusterStart) == 3 || subCTstripChargeSubdetid.at(clusterStart) == 5))
                   //    continue;

                   //@MJ@ TODO time re-calculation
                   //time -= 0.0666899*distVtx; //all tracks
                   //time -= 0.0897779*distVtx; //not tracker tracks
                   //time -= 0.121289*distVtx; //tracker tracks

                   time -= 0.0482406*distVtx; //all tracks charge everywhere

//p0                        =     -7.85364   +/-   0.438014
//p1                        =    0.0482406   +/-   0.00954462

                   if( ((muTrack == "muTop" && subCTMuOrigin.at(clusterStart) ==1) ||  (muTrack == "muBottom" && subCTMuOrigin.at(clusterStart) ==2)) /*&& distVtx<20*/ ) //if(subclusterlayerwheel.at(m) == 3)

                   {
                       //cout << "partition name " << parName << " event count " << eventCount.at(clusterStart) << "layer " << subCTstripChargeLayerwheel.at(clusterStart) << " detid " << subclusterdetid.at(m) << endl;

                       if( ( (hem == 1 && subtsosrhglobalphi.at(m)>0 ) || (hem == -1 && subtsosrhglobalphi.at(m)<0 )) && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0)// && subCTmuonsIsTracker.at(clusterStart) ==0 ) //top, tracker muon
                       {
                           //if(! (subCTinnerVZtop.at(clusterStart)> -80 && subCTinnerVZtop.at(clusterStart)<80) ) //z/correction
                           //   continue;
                           
                           //if(distVtx > 100)
                           //    continue;

                           //    if( muTrack == "muTop" && subCTMuOrigin.at(clusterStart) ==1 && hem == -1 && subtsosrhglobalphi.at(m)<0)
                           //    {
                           //        if(subCTMuontrackDirection.at(clusterStart) >0 )
                           //            continue;
                           //    }
                           
                           //vnrOfHitsVsError.at(partPos)->Fill(timeErr, subCTnrOfMuHits.at(clusterStart));
                          // nrOfSectorsVsError.at(partPos)->Fill( timeErr, subCTsectorsOfDT.at(clusterStart));
                           //chargeVsFreeInverseBeta.at(partPos)->Fill( subCTMuonCombinedFreeInverseBeta.at(clusterStart), subCTstripChargeTotCharge.at(clusterStart) );
                           //width.at(partPos)->Fill(time , subCTstripChargeTotWidth.at(clusterStart));
                           //widthAsCosPhi.at(partPos)->Fill(  cos(subCTstripChargeLocalTrackPhi.at(clusterStart)) , subCTstripChargeTotWidth.at(clusterStart));
                           charge.at(partPos)->Fill(time, subCTstripChargeTotCharge.at(clusterStart));
                           chargePerUnit.at(partPos)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                           if(subCTmuonsIsGlobal.at(clusterStart) ==1)
                               chargePerUnitGlobal.at(partPos)->Fill(time, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                           if(subCTmuonsIsTracker.at(clusterStart) ==1)
                               chargePerUnitTracker.at(partPos)->Fill(time, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                           if(subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                               chargePerUnitBeta.at(partPos)->Fill(time, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                           chargePerUnitHist.at(partPos)->Fill(subCTstripChargeSeedChargeRescaled.at(clusterStart));
                           float lowT = TMath::Pi()/2;
                           float highT = TMath::Pi()/2;
                           cout << "low T " << lowT << "high T " << highT << " theta " << subCTstripChargeGlobalTrackTheta.at(clusterStart) << endl;

                           if( subCTstripChargeGlobalTrackTheta.at(clusterStart)< lowT && subCTinnerVZtop.at(clusterStart)>0 )
                           { 
                               cout << "filling small theta" << endl;
                               thetaSmall.at(partPos)->Fill(time);
                           }
                           if( subCTstripChargeGlobalTrackTheta.at(clusterStart)> highT && subCTinnerVZtop.at(clusterStart)>0 )
                           { 
                               cout << "filling large theta" << endl;
                               thetaLarge.at(partPos)->Fill(time);
                           }

                           //if( muTrack == "muTop" && subCTMuOrigin.at(clusterStart) ==1 && hem == -1 && subtsosrhglobalphi.at(m)<0)
                           //    chargePerUnitLayers->SetBins(800, -100, 100);
                           chargePerUnitLayers->Fill(time, subCTstripChargeSeedChargeRescaled.at(clusterStart)) ;
                           if(subCTmuonsIsGlobal.at(clusterStart) ==1)
                               chargePerUnitLayersGlobal->Fill(time, subCTstripChargeSeedChargeRescaled.at(clusterStart)) ;
                           if(subCTmuonsIsTracker.at(clusterStart) ==1)
                               chargePerUnitLayersTracker->Fill(time, subCTstripChargeSeedChargeRescaled.at(clusterStart)) ;
                           if(subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                               chargePerUnitLayersBeta->Fill(time, subCTstripChargeSeedChargeRescaled.at(clusterStart)) ;

                           chargePerUnitHistLayers->Fill( subCTstripChargeSeedChargeRescaled.at(clusterStart)) ;
                           if(abs(distVtx)<20 && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                           //if(abs(distVtx)<50 && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                           {
                               chargePerUnitBins.at(partPos).at(0)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               chargePerUnitLayersBins.at(0)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               timeMedian.at(partPos).at(0).push_back(abs(distVtx));
                               timeMedianLayers.at(0).push_back(abs(distVtx));
                           }
                           if( abs(distVtx)>20 && abs(distVtx)<40  && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0  )
                           //if( abs(distVtx)>50 && abs(distVtx)<100  && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0  )
                           {
                               chargePerUnitBins.at(partPos).at(1)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               chargePerUnitLayersBins.at(1)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               timeMedian.at(partPos).at(1).push_back(abs(distVtx));
                               timeMedianLayers.at(1).push_back(abs(distVtx));
                           }
                           if(  abs(distVtx)>40 && abs(distVtx)<60 && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                           //if(  abs(distVtx)>100 && abs(distVtx)<120 && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                           {
                               chargePerUnitBins.at(partPos).at(2)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               chargePerUnitLayersBins.at(2)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               timeMedian.at(partPos).at(2).push_back(abs(distVtx));
                               timeMedianLayers.at(2).push_back(abs(distVtx));
                           }
                           if( abs(distVtx)>60  && abs(distVtx)<80 && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                           //if( abs(distVtx)>120 && subCTMuonCombinedFreeInverseBeta.at(clusterStart)>0 )
                           {
                               //cout << " " << endl;
                               chargePerUnitBins.at(partPos).at(3)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               chargePerUnitLayersBins.at(3)->Fill(timeNotZCorr, subCTstripChargeSeedChargeRescaled.at(clusterStart));
                               timeMedian.at(partPos).at(3).push_back(abs(distVtx));
                               timeMedianLayers.at(3).push_back(abs(distVtx));
                           }
                           //localTheta->Fill(subCTstripChargeLocalTrackTheta.at(clusterStart));
                           //localPhi->Fill(subCTstripChargeLocalTrackPhi.at(clusterStart));
                               timing.at(partPos)->Fill(time);
                               timingNC.at(partPos)->Fill(timeNotZCorr);

                           //Erics histograms + tree
                           float path = subCTstripChargeTotCharge.at(clusterStart)/subCTstripChargeTotChargeRescaled.at(clusterStart);
                           np1Evolution.at(partPos)->Fill(time,(float) subCTstripCharge.at(clusterStart+3)/path );
                           nm1Evolution.at(partPos)->Fill(time,(float) subCTstripCharge.at(clusterStart+1)/path );
                           nm2Evolution.at(partPos)->Fill(time,(float) subCTstripCharge.at(clusterStart)/path );
                           np2Evolution.at(partPos)->Fill(time,(float) subCTstripCharge.at(clusterStart+4)/path );
                           nSeedEvolution.at(partPos)->Fill(time,(float) subCTstripCharge.at(clusterStart+2)/path );
                           
                           eSubdetid = subCTstripChargeSubdetid.at(clusterStart) ;
                           eLayerWheel = subCTstripChargeLayerwheel.at(clusterStart);
                           eChn1right = subCTstripCharge.at(clusterStart+3)/path;
                           eChn2right = subCTstripCharge.at(clusterStart+4)/path;
                           eChn1left = subCTstripCharge.at(clusterStart+1)/path;
                           eChn2left = subCTstripCharge.at(clusterStart)/path;
                           eChSeed = subCTstripCharge.at(clusterStart+2)/path;
                           eChTot = subCTstripChargeTotChargeRescaled.at(clusterStart);
                           eTime =  time;
                           tE.Fill(); 
                  //TODO correct 
                           //distVtx = TMath::Sqrt( TMath::Power( subCTinnerVX.at(clusterStart),2 ) + TMath::Power( subCTinnerVY.at(clusterStart),2 ) + TMath::Power( subCTinnerVZtop.at(clusterStart),2 )  );
                           if(time > -60 && time < 60/* && subCTinnerVZtop.at(clusterStart)> -100 && subCTinnerVZtop.at(clusterStart) < 100*/ ) //avoid mixing!
                           {
                               int upTime = ceil(abs(time));
                               //int upDist = ceil(abs(subCTinnerVZtop.at(clusterStart)));
                               int upDist = floor(abs(distVtx));
                               if(time<0)
                                 upTime = upTime * -1;
                               //if(subCTinnerVZtop.at(clusterStart) <0)                            
                               if(distVtx <0)                            
                                 upDist = upDist * -1;
 
                               int binc = 60+ upTime;
                               int bind = 100+upDist;
                               
                               for(uint32_t n=0; n<4; n++)
                               {
                                   int bint = binc+n;
                                   int binz = bind+n;
                                   if(bint>119)
                                       continue;
                                   if(binz>199)
                                       continue;

                                   cout << "binz " << binz << endl;
                                   if(parName == "TOB2" )
                                   {
                                       cout << " it " << n << "time " <<  time << " uptime " << upTime << " bin " << bint << " seed charge " << subCTstripCharge.at(clusterStart+2) << endl;
                                   }

			               if(subCTstripCharge.at(clusterStart+1) != -333)
                                       {
					   narrowTrackSharing1DataEvolution.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           //if(subCTstripChargeLayerwheel.at(clusterStart) == 3)
                                           if(time > -2 && time < 2 )
					       narrowTrackSharing1DataEvolutionDist.at(partPos).at(binz)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                       }
				       if(subCTstripCharge.at(clusterStart+3) != -333)
                                       {
					   narrowTrackSharing1DataEvolution.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           //if(subCTstripChargeLayerwheel.at(clusterStart) == 3)
                                           if(time > -2 && time < 2 )
					       narrowTrackSharing1DataEvolutionDist.at(partPos).at(binz)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                       }
				       if(subCTstripCharge.at(clusterStart) != -333)
                                       {
					   narrowTrackSharing2DataEvolution.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(time > -2 && time < 2 )
					       narrowTrackSharing2DataEvolutionDist.at(partPos).at(binz)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                       }
				       if(subCTstripCharge.at(clusterStart+4) != -333)
                                       {
					   narrowTrackSharing2DataEvolution.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(time > -2 && time < 2 )
					       narrowTrackSharing2DataEvolutionDist.at(partPos).at(binz)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                       }
                               }

                               for(uint32_t n=0; n<6; n++)
                               {
                                   int bint = binc+n;
                                   int binz = bind+n;
                                   if(bint>119)
                                       continue;
                                   if(binz>199)
                                       continue;


			               if(subCTstripCharge.at(clusterStart+1) != -333)
                                       {
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 )
					       narrowTrackSharing1DataEvolutionL1.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 )
					       narrowTrackSharing1DataEvolutionL2.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 3 )
					       narrowTrackSharing1DataEvolutionL3.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 4 )
					       narrowTrackSharing1DataEvolutionL4.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing1DataEvolutionL1m.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing1DataEvolutionL1s.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing1DataEvolutionL2m.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing1DataEvolutionL2s.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
                                       }
				       if(subCTstripCharge.at(clusterStart+3) != -333)
                                       {
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 )
					       narrowTrackSharing1DataEvolutionL1.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 )
					       narrowTrackSharing1DataEvolutionL2.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 3  )
					       narrowTrackSharing1DataEvolutionL3.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 4  )
					       narrowTrackSharing1DataEvolutionL4.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing1DataEvolutionL1m.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing1DataEvolutionL1s.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing1DataEvolutionL2m.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing1DataEvolutionL2s.at(partPos).at(bint)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
                                       }
				       if(subCTstripCharge.at(clusterStart) != -333)
                                       {
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 )
					       narrowTrackSharing2DataEvolutionL1.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 )
					       narrowTrackSharing2DataEvolutionL2.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 3 )
					       narrowTrackSharing2DataEvolutionL3.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 4 )
					       narrowTrackSharing2DataEvolutionL4.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing2DataEvolutionL1m.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing2DataEvolutionL1s.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing2DataEvolutionL2m.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing2DataEvolutionL2s.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
                                       }
				       if(subCTstripCharge.at(clusterStart+4) != -333)
                                       {
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 )
					       narrowTrackSharing2DataEvolutionL1.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 )
					       narrowTrackSharing2DataEvolutionL2.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 3 )
					       narrowTrackSharing2DataEvolutionL3.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 4 )
					       narrowTrackSharing2DataEvolutionL4.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing2DataEvolutionL1m.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 1 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing2DataEvolutionL1s.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==0 )
					       narrowTrackSharing2DataEvolutionL2m.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                           if(subCTstripChargeLayerwheel.at(clusterStart) == 2 && subclusterstereo.at(m)==1 )
					       narrowTrackSharing2DataEvolutionL2s.at(partPos).at(bint)->Fill((float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                                       }
                                 }
                               }
                               /*timingDirection.at(partPos)->Fill(subCTMuontrackDirection.at(clusterStart));
                               timeVsVz.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), time );
                               betaVsVx.at(partPos)->Fill( subCTinnerVX.at(clusterStart), subCTMuonCombinedFreeInverseBeta.at(clusterStart) );
                               betaVsVy.at(partPos)->Fill( subCTinnerVY.at(clusterStart), subCTMuonCombinedFreeInverseBeta.at(clusterStart) );
                               betaVsVz.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart), subCTMuonCombinedFreeInverseBeta.at(clusterStart));
                               betaVsDist.at(partPos)->Fill( distVtx , subCTMuonCombinedFreeInverseBeta.at(clusterStart) );
                               betaVsTime.at(partPos)->Fill( time , subCTMuonCombinedFreeInverseBeta.at(clusterStart) );
                               timeVsVzLayers->Fill(  subCTinnerVZtop.at(clusterStart), time) ;
                               timeVsVxLayers->Fill(  subCTinnerVX.at(clusterStart), time) ;
                               timeVsVyLayers->Fill(  subCTinnerVY.at(clusterStart), time) ;
                               timeVsDistLayers->Fill(  distVtx , time) ;
                               timeVsDistLayers2D->Fill(  distVtx , time) ;
                               timeVsDistLayersNotDistCorr->Fill(  distVtx , timeNotZCorr ) ;
                               timeVsVzLayersNotZCorr->Fill(  subCTinnerVZtop.at(clusterStart), timeNotZCorr ) ;
                               innerZ.at(partPos)->Fill( subCTinnerZtop.at(clusterStart) );
                               //if(subCTstripChargeLayerwheel.at(clusterStart) == 3)
                               innerVZ.at(partPos)->Fill( subCTinnerVZtop.at(clusterStart) );
                               innerVX.at(partPos)->Fill( subCTinnerVX.at(clusterStart) );
                               innerVY.at(partPos)->Fill( subCTinnerVY.at(clusterStart) );
                               timingError.at(partPos)->Fill(timeErr);*/
                           //}
                           //-7.85364   +/-   0.438014 
                           if(time > -10 && time < -6/* && distVtx<20*/) //avoid mixing!
                           {
			       if(subCTstripCharge.at(clusterStart+1) != -333  )
				   narrowTrackSharing1Data.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart+3) != -333 )
				   narrowTrackSharing1Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart) != -333)
				   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart+4) != -333)
				   narrowTrackSharing2Data.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                               if( (subCTstripCharge.at(clusterStart+4) == 0 || subCTstripCharge.at(clusterStart) == 0 ) && parName == "TOB2" )
                                    cout << " second left " << subCTstripCharge.at(clusterStart) << "first left " << subCTstripCharge.at(clusterStart+1) << " seed " << subCTstripCharge.at(clusterStart+2) << " first right " << subCTstripCharge.at(clusterStart+3) << " second right " << subCTstripCharge.at(clusterStart+4) << endl;

                           }
                           if(time > -10.5 && time < -6.5) //avoid mixing!
                           {
			       if(subCTstripCharge.at(clusterStart+1) != -333  )
				   narrowTrackSharing1DataUp.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart+3) != -333 )
				   narrowTrackSharing1DataUp.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart) != -333)
				   narrowTrackSharing2DataUp.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart+4) != -333)
				   narrowTrackSharing2DataUp.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                               //if( (subCTstripCharge.at(clusterStart+4) == 0 || subCTstripCharge.at(clusterStart) == 0 ) && parName == "TOB2" )
               //                     cout << " second left " << subCTstripCharge.at(clusterStart) << "first left "subCTstripCharge.at(clusterStart+1) << " seed " << subCTstripCharge.at(clusterStart+2) << " first right " << subCTstripCharge.at(clusterStart+3) << " second right " << subCTstripCharge.at(clusterStart+4) << endl;

                           }
                           if(time > -9.5 && time < -5.5) //avoid mixing!
                           {
			       if(subCTstripCharge.at(clusterStart+1) != -333  )
				   narrowTrackSharing1DataDown.at(partPos)->Fill((float) subCTstripCharge.at(clusterStart+1)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart+3) != -333 )
				   narrowTrackSharing1DataDown.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+3)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart) != -333)
				   narrowTrackSharing2DataDown.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart)/subCTstripCharge.at(clusterStart+2));
			       if(subCTstripCharge.at(clusterStart+4) != -333)
				   narrowTrackSharing2DataDown.at(partPos)->Fill( (float) subCTstripCharge.at(clusterStart+4)/subCTstripCharge.at(clusterStart+2));
                               //if( (subCTstripCharge.at(clusterStart+4) == 0 || subCTstripCharge.at(clusterStart) == 0 ) && parName == "TOB2" )
               //                     cout << " second left " << subCTstripCharge.at(clusterStart) << "first left "subCTstripCharge.at(clusterStart+1) << " seed " << subCTstripCharge.at(clusterStart+2) << " first right " << subCTstripCharge.at(clusterStart+3) << " second right " << subCTstripCharge.at(clusterStart+4) << endl;

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
       
       
       tE.Write(); 

//////////////////////filling
//     
//
//

   vector<int> hcolors = {632, 602, 618, 922, 434,  824, 634, 419, 594, 892  };
       for(uint32_t c= 0; c<canvases.size(); c++ )
       {
           if(narrowTrackSharing1Data.at(c)==NULL || narrowTrackSharing2Data.at(c) == NULL)
               break;

       string geometry = ""; 
      std::size_t found = ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TIB1");
      if(found!=std::string::npos)
          geometry = "IB1";
      found =   ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TIB2");
      if(found!=std::string::npos)
          geometry = "IB2";
      found =   ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TOB2");
      if(found!=std::string::npos)
          geometry = "OB2";
      found =   ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TOB1");
      if(found!=std::string::npos)
          geometry = "OB1";



       TLatex text(0.2,0.85, geometry.c_str() );  
       //hists.at(h)->Draw("*H");
       //TLatex text(0.2,0.2, "test");  
       text.SetNDC(kTRUE);
       //text.Draw("same");

      float lowr1 = 0;
      float highr1 = 0;
      float lowr2 = 0;
      float highr2 = 0;

          int gmaxbin = narrowTrackSharing1Data.at(c)->GetMaximumBin();
          float gmax = narrowTrackSharing1Data.at(c)->GetBinCenter(gmaxbin);
          int gmaxbin2 = narrowTrackSharing2Data.at(c)->GetMaximumBin();
          float gmax2 = narrowTrackSharing2Data.at(c)->GetBinCenter(gmaxbin2);
          
          lowr1 = gmax-0.1 ;
          highr1 = gmax+0.1 ;
          lowr2 = gmax2-0.15 ;
          highr2 = gmax2+0.15  ;

       chargePerUnitBinsCan.at(c)->cd();
       float med = 0;
       //for(uint32_t u=0; u<chargePerUnitBins.at(c).size(); u++)
       TLegend legb(0.65,0.75,0.95,0.92);
       for(uint32_t u=0; u<3; u++)
       {
           chargePerUnitBins.at(c).at(u)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
           chargePerUnitBins.at(c).at(u)->GetYaxis()->SetTitle("cluster seed charge over path [ADC/cm]");
           chargePerUnitBins.at(c).at(u)->SetTitle("");
           chargePerUnitBins.at(c).at(u)->SetLineColor(hcolors.at(u+1));
           chargePerUnitBins.at(c).at(u)->SetMarkerColor(hcolors.at(u+1));
           chargePerUnitBins.at(c).at(u)->SetStats(kFALSE);
           cout << "start time emdian " << endl;
           sort(timeMedian.at(c).at(u).begin(), timeMedian.at(c).at(u).end() );
           uint32_t half = floor(timeMedian.at(c).at(u).size()/2) ;
           cout << " size " << timeMedian.at(c).at(u).size() <<  " half  " << half << endl;
           if(half>0)
                med = timeMedian.at(c).at(u).at(half);
           cout << "end time emdian " << endl;
           if(u==0)
               chargePerUnitBins.at(c).at(u)->Draw("");
           else
               chargePerUnitBins.at(c).at(u)->Draw("same e");



       TF1* ffitTime  =new TF1("ft1","gaus", -20, 10); //different range for different geometries
       //ffitTime->SetStats(kFALSE);
       ffitTime->SetLineColor(hcolors.at(u+1));
       chargePerUnitBins.at(c).at(u)->Fit(ffitTime, "RL");
       chargePerUnitBins.at(c).at(u)->SetStats(kFALSE);
       double fitTime = ffitTime->GetParameter(1);
       double fitTimeErr = ffitTime->GetParError(1);
       float whichb = chargePerUnitBinsFit.at(c)->FindBin(med);
       chargePerUnitBinsFit.at(c)->SetBinContent(whichb ,fitTime);
       cout << " median " <<  med <<  " point " << whichb << " fit "<< fitTime << endl;
       chargePerUnitBinsFit.at(c)->SetBinError(whichb ,fitTimeErr);
       }

       legb.AddEntry( chargePerUnitBins.at(c).at(0)  , "dist<30cm"  , "p");
       legb.AddEntry( chargePerUnitBins.at(c).at(1)  , "30cm<dist<60cm"  , "p");
       legb.AddEntry( chargePerUnitBins.at(c).at(2)  , "dist>60cm"  , "p");
       //leg1.AddEntry( chargePerUnitBins.at(3)  , "all dist"  , "p");
       legb.Draw("same");
       text.Draw("same");
       chargePerUnitBinsCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitBins.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       chargePerUnitBinsCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitBins.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       TF1* linTime  =new TF1("fl1","pol1", 0, 100); //different range for different geometries

       TFitResultPtr fitres = chargePerUnitBinsFit.at(c)->Fit( linTime , "RS"); 
       chargePerUnitBinsFit.at(c)->GetYaxis()->SetTitle("time_{IP}^{InOut} [cm]");
       chargePerUnitBinsFit.at(c)->GetXaxis()->SetTitle("track distance to the IP [cm]");
       cout << chargePerUnitBins.at(c).at(0)->GetName() << "fit" << part << muTrack << endl;
       TMatrixDSym cov = fitres->GetCovarianceMatrix();
       double fitp1 = linTime->GetParameter(0);
       double fitp1Err = linTime->GetParError(0);
       double fitp2 = linTime->GetParameter(1);
       double fitp2Err = linTime->GetParError(1);
       //double totalErr = TMath::Sqrt( (fitp1Err*fitp1Err)+(fitp2Err*fitp2Err)+ cov(0,1)  ); 
       double totalErr = fitp1Err; 
       cout << "time correction par1 " << fitp1 << " par1 err  " << fitp1Err << " par2  " << fitp2 << " par2 err " << fitp2Err << " total err " << totalErr << endl;
       cout << "covariance element " << cov(0,1) << endl;
       fitres->PrintCovMatrix(cout);
       chargePerUnitBinsFitCan.at(c)->cd();
       chargePerUnitBinsFit.at(c)->Draw("e");
       chargePerUnitBinsFitCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitBins.at(c).at(0)->GetName()+"fit"+(string)part+(string)muTrack+ ".root").c_str());
       chargePerUnitBinsFitCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitBins.at(c).at(0)->GetName()+"fit"+(string)part+(string)muTrack+ ".eps").c_str());
     /*std::size_t found = ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TIB1");
      if(found!=std::string::npos)
      {
          lowr1 = 0.00 ;
          highr1 = 0.3 ;
          lowr2 = -0.1 ;
          highr2 = 0.2 ;
      }
     found =   ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TIB2");
      if(found!=std::string::npos)
      {
          lowr1 = -0.00 ;
          highr1 = 0.25 ;
          lowr2 = -0.15 ;
          highr2 = 0.20 ;
      }
      found =   ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TOB2");
      if(found!=std::string::npos)
      {
          //lowr1 = -0.05 ;
          //highr1 = 0.25 ;
          //lowr2 = -0.05 ;
          //highr2 = 0.15 ;
          //lowr1 = 0.05 ;
         // highr1 = 0.3 ;
         // lowr2 = -0.05 ;
          //highr2 = 0.15 ;
          int gmaxbin = narrowTrackSharing1Data.at(c)->GetMaximumBin();
          float gmax = narrowTrackSharing1Data.at(c)->GetBinCenter(gmaxbin);
          
          lowr1 = gmax-0.1 ;
          highr1 = gmax+0.1 ;
          lowr2 = -0.2 ;
          highr2 = 0.2 ;
      }
      found =   ((string) narrowTrackSharing1Data.at(c)->GetName()).find("TOB1");
      if(found!=std::string::npos)
      {
          lowr1 = 0.05 ;
          highr1 = 0.3 ;
          lowr2 = -0.05 ;
          highr2 = 0.2 ;
      }*/
       narrowTrackSharing1Data.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing1Data.at(c)->SetMarkerColor(kBlack);
       narrowTrackSharing2Data.at(c)->SetMarkerStyle(kFullCircle);
       narrowTrackSharing2Data.at(c)->SetMarkerColor(kBlack);

       narrowTrackSharing1Data.at(c)->SetTitle("");
       narrowTrackSharing2Data.at(c)->SetTitle("");

       narrowTrackSharing1Data.at(c)->GetXaxis()->SetTitle("#eta_{#pm 1}");
       narrowTrackSharing2Data.at(c)->GetXaxis()->SetTitle("#eta_{#pm 2}");

       //narrowTrackSharing1Data.at(c)->SetMaximum(1.3*  narrowTrackSharing1Data.at(c)->GetMaximum());
       //narrowTrackSharing2Data.at(c)->SetMaximum(1.5*  narrowTrackSharing2Data.at(c)->GetMaximum());


       narrowTrackSharing1DataCan.at(c)->cd();
       TF1* ffit  =new TF1("f1","gaus", lowr1, highr1); //different range for different geometries
       narrowTrackSharing1Data.at(c)->Fit(ffit, "RL");
       double fitMean = ffit->GetParameter(1);
       double fitMeanErr = ffit->GetParError(1);
       double fitChi2 = ffit->GetChisquare(); 
       double fitNdof = ffit->GetNDF();
       double fitProb = TMath::Prob(fitChi2, fitNdof  );
       //gMinuit->mnmatu(1);
       cout << narrowTrackSharing1Data.at(c)->GetName()+(string)part+(string)muTrack << " mean " << fitMean << " +- " << fitMeanErr << " chi2 " << fitChi2 << " ndof " << fitNdof << " prob " << fitProb << endl; 
       cout << " " << endl;
       narrowTrackSharing1Data.at(c)->GetXaxis()->SetRangeUser(-0.2, 0.5);
       narrowTrackSharing1Data.at(c)->GetYaxis()->SetTitle("twice # of clusters");
       narrowTrackSharing1Data.at(c)->Draw(""); 
       text.Draw("same");
       //ffit->Draw("same"); 
       narrowTrackSharing1DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       narrowTrackSharing1DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing1Data.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       


       narrowTrackSharing2DataCan.at(c)->cd();
       TF1* ffit2  =new TF1("f2","gaus", lowr2, highr2);
       narrowTrackSharing2Data.at(c)->Fit(ffit2, "RL");
       double fitMean2 = ffit2->GetParameter(1);
       double fitMeanErr2 = ffit2->GetParError(1);
       double fitChi22 = ffit2->GetChisquare(); 
       double fitNdof2 = ffit2->GetNDF();
       double fitProb2 = TMath::Prob(fitChi22, fitNdof2  );
       cout << narrowTrackSharing2Data.at(c)->GetName()+(string)part+(string)muTrack << " mean " << fitMean2 << " +- " << fitMeanErr2 << " chi2 " << fitChi22 << " ndof " << fitNdof2 << " prob " << fitProb2 << endl; 
       cout << " " << endl;
       //ffit2->SetLineColor(kRed); 
       //ffit2->Draw(""); 
       narrowTrackSharing2Data.at(c)->GetXaxis()->SetRangeUser(-0.2, 0.4);
       narrowTrackSharing2Data.at(c)->GetYaxis()->SetTitle("twice # of clusters");
       narrowTrackSharing2Data.at(c)->Draw("");
       text.Draw("same");
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName()+(string)part+(string)muTrack + ".root").c_str());
       narrowTrackSharing2DataCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ narrowTrackSharing2Data.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());


   double eta1Val = eta1(fitMean, fitMean2);
   double eta1ErrVal = eta1Err(fitMean, fitMeanErr, fitMean2, fitMeanErr2 );
   double eta2Val = eta2(fitMean, fitMean2 );
   double eta2ErrVal = eta2Err( fitMean, fitMeanErr, fitMean2, fitMeanErr2 );

   double eta0Val = eta0( eta1Val, eta2Val );
   double eta0ErrVal = eta0Err( eta1ErrVal , eta2ErrVal );

   cout << "x0 " << eta0Val << " +- " << eta0ErrVal << endl;
   cout << "x1 " << eta1Val << " +- " << eta1ErrVal << endl;
   cout << "x2 " << eta2Val << " +- " << eta2ErrVal << endl;

       narrowTrackSharing1DataUp.at(c)->Fit(ffit, "RL");
       double fitMeanUp = ffit->GetParameter(1);
       double fitMeanErrUp = ffit->GetParError(1);
       double fitChi2Up = ffit->GetChisquare(); 
       double fitNdofUp = ffit->GetNDF();
       double fitProbUp = TMath::Prob(fitChi2Up, fitNdofUp  );
       cout << narrowTrackSharing1DataUp.at(c)->GetName()+(string)part+(string)muTrack << " mean up " << fitMeanUp << " +- " << fitMeanErrUp << " chi2 " << fitChi2Up << " ndof " << fitNdofUp << " prob " << fitProbUp << endl; 
       cout << " " << endl;

       narrowTrackSharing2DataUp.at(c)->Fit(ffit2, "RL");
       double fitMean2Up = ffit2->GetParameter(1);
       double fitMeanErr2Up = ffit2->GetParError(1);
       double fitChi22Up = ffit2->GetChisquare(); 
       double fitNdof2Up = ffit2->GetNDF();
       double fitProb2Up = TMath::Prob(fitChi22Up, fitNdof2Up  );
       cout << narrowTrackSharing2DataUp.at(c)->GetName()+(string)part+(string)muTrack << " mean " << fitMean2Up << " +- " << fitMeanErr2Up << " chi2 " << fitChi22Up << " ndof " << fitNdof2Up << " prob " << fitProb2Up << endl; 
       cout << " " << endl;

   double eta1ValUp = eta1(fitMeanUp, fitMean2Up);
   double eta1ErrValUp = eta1Err(fitMeanUp, fitMeanErrUp, fitMean2Up, fitMeanErr2Up );
   double eta2ValUp = eta2(fitMeanUp, fitMean2Up );
   double eta2ErrValUp = eta2Err( fitMeanUp, fitMeanErrUp, fitMean2Up, fitMeanErr2Up );

   double eta0ValUp = eta0( eta1ValUp, eta2ValUp );
   double eta0ErrValUp = eta0Err( eta1ErrValUp , eta2ErrValUp );

   cout << "x0 up " << eta0ValUp << " +- " << eta0ErrValUp << endl;
   cout << "x1 up " << eta1ValUp << " +- " << eta1ErrValUp << endl;
   cout << "x2 up " << eta2ValUp << " +- " << eta2ErrValUp << endl;

       narrowTrackSharing1DataDown.at(c)->Fit(ffit, "RL");
       double fitMeanDown = ffit->GetParameter(1);
       double fitMeanErrDown = ffit->GetParError(1);
       double fitChi2Down = ffit->GetChisquare(); 
       double fitNdofDown = ffit->GetNDF();
       double fitProbDown = TMath::Prob(fitChi2Down, fitNdofDown  );
       cout << narrowTrackSharing1DataDown.at(c)->GetName()+(string)part+(string)muTrack << " mean up " << fitMeanDown << " +- " << fitMeanErrDown << " chi2 " << fitChi2Down << " ndof " << fitNdofDown << " prob " << fitProbDown << endl; 
       cout << " " << endl;

       narrowTrackSharing2DataDown.at(c)->Fit(ffit2, "RL");
       double fitMean2Down = ffit2->GetParameter(1);
       double fitMeanErr2Down = ffit2->GetParError(1);
       double fitChi22Down = ffit2->GetChisquare(); 
       double fitNdof2Down = ffit2->GetNDF();
       double fitProb2Down = TMath::Prob(fitChi22Down, fitNdof2Down  );
       cout << narrowTrackSharing2DataDown.at(c)->GetName()+(string)part+(string)muTrack << " mean " << fitMean2Down << " +- " << fitMeanErr2Down << " chi2 " << fitChi22Down << " ndof " << fitNdof2Down << " prob " << fitProb2Down << endl; 
       cout << " " << endl;

   double eta1ValDown = eta1(fitMeanDown, fitMean2Down);
   double eta1ErrValDown = eta1Err(fitMeanDown, fitMeanErrDown, fitMean2Down, fitMeanErr2Down );
   double eta2ValDown = eta2(fitMeanDown, fitMean2Down );
   double eta2ErrValDown = eta2Err( fitMeanDown, fitMeanErrDown, fitMean2Down, fitMeanErr2Down );

   double eta0ValDown = eta0( eta1ValDown, eta2ValDown );
   double eta0ErrValDown = eta0Err( eta1ErrValDown , eta2ErrValDown );

   cout << "x0 down " << eta0ValDown << " +- " << eta0ErrValDown << endl;
   cout << "x1 down " << eta1ValDown << " +- " << eta1ErrValDown << endl;
   cout << "x2 down " << eta2ValDown << " +- " << eta2ErrValDown << endl;

   cout << " " << endl;
   cout << "x0 final " << eta0Val << " +- " << TMath::Sqrt( TMath::Power(eta0ErrVal,2) + TMath::Power(abs(eta0ValDown-eta0ValUp)/2 , 2) ) << endl;
   cout << "x1 final " << eta1Val << " +- " << TMath::Sqrt( TMath::Power(eta1ErrVal,2) + TMath::Power(abs(eta1ValDown-eta1ValUp)/2 , 2) ) << endl;
   cout << "x2 final " << eta2Val << " +- " << TMath::Sqrt( TMath::Power(eta2ErrVal,2) + TMath::Power(abs(eta2ValDown-eta2ValUp)/2 , 2) ) << endl;
   
   
/*       widthCan.at(c)->cd();
       width.at(c)->GetXaxis()->SetTitle("time");
       width.at(c)->GetYaxis()->SetTitle("cluster width");
       width.at(c)->Draw("");
       widthCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ width.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       widthCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ width.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       widthAsCosPhiCan.at(c)->cd();
       widthAsCosPhi.at(c)->GetXaxis()->SetTitle("cos(#phi)");
       widthAsCosPhi.at(c)->GetYaxis()->SetTitle("cluster width");
       widthAsCosPhi.at(c)->Draw("");
       widthAsCosPhiCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthAsCosPhi.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       widthAsCosPhiCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ widthAsCosPhi.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       chargeCan.at(c)->cd();
       charge.at(c)->GetXaxis()->SetTitle("time");
       charge.at(c)->GetYaxis()->SetTitle("cluster charge");
       charge.at(c)->Draw("");
       chargeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ charge.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       chargeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ charge.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
*/
       chargePerUnitCan.at(c)->cd();
       chargePerUnit.at(c)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       chargePerUnit.at(c)->GetYaxis()->SetTitle("cluster seed charge over path [ADC/cm]");
       chargePerUnit.at(c)->SetTitle("");
       chargePerUnit.at(c)->SetLineColor(kBlack);
       chargePerUnit.at(c)->SetMarkerColor(kBlack);
       TF1* ffitTime1  =new TF1("ft11","gaus", -20, 10); //different range for different geometries
       ffitTime1->SetLineColor(kRed);
       chargePerUnit.at(c)->Fit(ffitTime1, "RL");
       double fitTime1 = ffitTime1->GetParameter(1);
       double fitTimeErr1 = ffitTime1->GetParError(1);
       chargePerUnit.at(c)->Draw("");
       text.Draw("same");
      /* chargePerUnitGlobal.at(c)->SetLineColor(kGreen);
       chargePerUnitGlobal.at(c)->Draw("same");
       chargePerUnitTracker.at(c)->SetLineColor(kRed);
       chargePerUnitTracker.at(c)->Draw("same");
       chargePerUnitBeta.at(c)->SetLineColor(kBlue);
       chargePerUnitBeta.at(c)->Draw("same");*/
       chargePerUnitCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnit.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       chargePerUnitCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnit.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       chargePerUnitHistCan.at(c)->cd();
       chargePerUnitHist.at(c)->GetXaxis()->SetTitle("cluster charge rescaled");
       chargePerUnitHist.at(c)->Draw("hist");
       chargePerUnitHistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitHist.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       chargePerUnitHistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitHist.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       
       thetaCan.at(c)->cd();
       thetaSmall.at(c)->GetYaxis()->SetTitle("a.u.");
       thetaSmall.at(c)->GetXaxis()->SetTitle("time");
       thetaSmall.at(c)->SetLineColor(kBlack);
       thetaSmall.at(c)->DrawNormalized("hist");
       thetaLarge.at(c)->SetLineColor(kRed);
       thetaLarge.at(c)->DrawNormalized("same hist");
       thetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ thetaSmall.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       thetaCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ thetaSmall.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


       timingCan.at(c)->cd();
       timing.at(c)->GetXaxis()->SetTitle("time");
       timing.at(c)->GetYaxis()->SetTitle("");
       timing.at(c)->SetLineColor(kBlue);
       timingNC.at(c)->SetLineColor(kRed);
       timing.at(c)->Draw("hist");
       timingNC.at(c)->Draw("same hist");
       timingCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timing.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       timingCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timing.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


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

       np1EvolutionCan.at(c)->cd();
       np1Evolution.at(c)->GetXaxis()->SetTitle("time");
       np1Evolution.at(c)->GetYaxis()->SetTitle("1st neighbor on the right ch.");
       np1Evolution.at(c)->Draw("hist e");
       np1EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ np1Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       np1EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ np1Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       np2EvolutionCan.at(c)->cd();
       np2Evolution.at(c)->GetXaxis()->SetTitle("time");
       np2Evolution.at(c)->GetYaxis()->SetTitle("2nd neighbor on the right ch.");
       np2Evolution.at(c)->Draw("hist e");
       np2EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ np2Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       np2EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ np2Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       nm1EvolutionCan.at(c)->cd();
       nm1Evolution.at(c)->GetXaxis()->SetTitle("time");
       nm1Evolution.at(c)->GetYaxis()->SetTitle("1st neighbor on the left ch.");
       nm1Evolution.at(c)->Draw("hist e");
       nm1EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nm1Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       nm1EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nm1Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       nm2EvolutionCan.at(c)->cd();
       nm2Evolution.at(c)->GetXaxis()->SetTitle("time");
       nm2Evolution.at(c)->GetYaxis()->SetTitle("2nd neighbor on the left ch.");
       nm2Evolution.at(c)->Draw("hist e");
       nm2EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nm2Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       nm2EvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nm2Evolution.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       nSeedEvolutionCan.at(c)->cd();
       nSeedEvolution.at(c)->GetXaxis()->SetTitle("time");
       nSeedEvolution.at(c)->GetYaxis()->SetTitle("seed ch.");
       nSeedEvolution.at(c)->Draw("hist e");
       nSeedEvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nSeedEvolution.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       nSeedEvolutionCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ nSeedEvolution.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       /*TCanvas* cvs = new TCanvas("chargeThroughTrackerc", "chargeThroughTrackerc");
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
*/
       etaOneaAsVzCan.at(c)->cd();
       etaOneaAsVz.at(c)->GetXaxis()->SetTitle("vz");
       etaOneaAsVz.at(c)->GetYaxis()->SetTitle("eta #pm 1");
       etaOneaAsVz.at(c)->Draw("");
       etaOneaAsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


       /*timeVsVzCan.at(c)->cd();
       timeVsVz.at(c)->GetXaxis()->SetTitle("vz");
       timeVsVz.at(c)->GetYaxis()->SetTitle("time");
       timeVsVz.at(c)->Draw("");
       timeVsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       timeVsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ timeVsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       betaVsVxCan.at(c)->cd();
       betaVsVx.at(c)->GetXaxis()->SetTitle("vx");
       betaVsVx.at(c)->GetYaxis()->SetTitle("beta");
       betaVsVx.at(c)->Draw("");
       betaVsVxCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsVx.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       betaVsVxCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsVx.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       betaVsVyCan.at(c)->cd();
       betaVsVy.at(c)->GetXaxis()->SetTitle("vy");
       betaVsVy.at(c)->GetYaxis()->SetTitle("beta");
       betaVsVy.at(c)->Draw("");
       betaVsVyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsVy.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       betaVsVyCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsVy.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       betaVsVzCan.at(c)->cd();
       betaVsVz.at(c)->GetXaxis()->SetTitle("vz");
       betaVsVz.at(c)->GetYaxis()->SetTitle("beta");
       betaVsVz.at(c)->Draw("");
       betaVsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       betaVsVzCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsVz.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       betaVsDistCan.at(c)->cd();
       betaVsDist.at(c)->SetTitle("");
       betaVsDist.at(c)->GetXaxis()->SetTitle("distance from IP");
       betaVsDist.at(c)->GetYaxis()->SetTitle("free inverse beta");
       betaVsDist.at(c)->Draw("");
       betaVsDistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsDist.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       betaVsDistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsDist.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       betaVsTimeCan.at(c)->cd();
       betaVsTime.at(c)->SetTitle("");
       betaVsTime.at(c)->GetXaxis()->SetTitle("time");
       betaVsTime.at(c)->GetYaxis()->SetTitle("free inverse beta");
       betaVsTime.at(c)->Draw("");
       betaVsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       betaVsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ betaVsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
*/

       for(uint32_t j=0; j<120; j++)
       {
          //cout << "j" << j << endl;
          //cout << "hist address " << narrowTrackSharing1DataEvolution.at(c).at(j) << endl;
          int ne=  narrowTrackSharing1DataEvolution.at(c).at(j)->GetEntries();
          if( ne> 80)
          {
              //cout << " j " << j << "canvas address " << narrowTrackSharing1DataEvolutionCan.at(c).at(j) << endl;
              //narrowTrackSharing1DataEvolutionCan.at(c).at(j)->cd();

		  gmaxbin = narrowTrackSharing1DataEvolution.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolution.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolution.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolution.at(c).at(j)->GetBinCenter(gmaxbin2);
		  
		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 = gmax2+0.15  ;
              TCanvas* canTest = new TCanvas("ct", "ct");
              canTest->cd();
              cout << "fitting " << endl;
              TF1* ffiteta  =new TF1("feta","gaus", lowr1, highr1); //different range for different geometries
              narrowTrackSharing1DataEvolution.at(c).at(j)->Fit(ffiteta, "RL");
              double fitMeanEta = ffiteta->GetParameter(1);
              double fitMeanEtaErr = ffiteta->GetParError(1);
              cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
              if(j>0) 
              {
                  cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
                  etaOneaAsTime.at(c)->SetBinContent(j, fitMeanEta );
                  //cout << "etapmone " << " bin  " << j-2 << " position  " << etaOneaAsTime.at(c)->GetBinLowEdge(j+1) 
                  etaOneaAsTime.at(c)->SetBinError(j, fitMeanEtaErr );
              }
              canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) + ".eps").c_str());
              canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) + ".root").c_str());
           }
       }

       etaOneaAsTimeCan.at(c)->cd();
       etaOneaAsTime.at(c)->SetTitle("");
       etaOneaAsTime.at(c)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       etaOneaAsTime.at(c)->GetXaxis()->SetRangeUser(-15,5);
       etaOneaAsTime.at(c)->GetYaxis()->SetTitle("#eta_{#pm 1}");
       etaOneaAsTime.at(c)->Draw("");
       text.Draw("same");
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       for(uint32_t j=0; j<120; j++)
       {
          //cout << "j" << j << endl;
          //cout << "hist address " << narrowTrackSharing2DataEvolution.at(c).at(j) << endl;
          int ne=  narrowTrackSharing2DataEvolution.at(c).at(j)->GetEntries();
          if( ne> 80)
          {
              //cout << " j " << j << "canvas address " << narrowTrackSharing2DataEvolutionCan.at(c).at(j) << endl;
              //narrowTrackSharing2DataEvolutionCan.at(c).at(j)->cd();
		  gmaxbin = narrowTrackSharing1DataEvolution.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolution.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolution.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolution.at(c).at(j)->GetBinCenter(gmaxbin2);
		  
		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 = gmax2+0.15  ;
              TF1* ffiteta  =new TF1("feta","gaus", lowr2, highr2); //different range for different geometries
              narrowTrackSharing2DataEvolution.at(c).at(j)->Fit(ffiteta, "RL");
              double fitMeanEta = ffiteta->GetParameter(1);
              double fitMeanEtaErr = ffiteta->GetParError(1);
              if(j>0) 
              {
                  cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTime.at(c)->GetBinLowEdge(j)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
                  etaTwoAsTime.at(c)->SetBinContent(j, fitMeanEta );
                  etaTwoAsTime.at(c)->SetBinError(j, fitMeanEtaErr );
              }
           }
       }

       etaTwoAsTimeCan.at(c)->cd();
       etaTwoAsTime.at(c)->SetTitle("");
       etaTwoAsTime.at(c)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       etaTwoAsTime.at(c)->GetYaxis()->SetTitle("#eta_{#pm 2}");
       etaTwoAsTime.at(c)->GetXaxis()->SetRangeUser(-15,5);
       etaTwoAsTime.at(c)->Draw("");
       text.Draw("same");
       etaTwoAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaTwoAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


   double eta1ValP;
   double eta1ErrValP;
   double eta2ValP;
   double eta2ErrValP;

   double eta0ValP ;
   double eta0ErrValP;


   for(uint32_t y=0; y<etaOneaAsTime.at(c)->GetNbinsX(); y++) //TODO
   {
           if( etaOneaAsTime.at(c)->GetNbinsX() != etaTwoAsTime.at(c)->GetNbinsX())
           {
               cout << "not same size plots" << endl;
               continue;
           }
	   eta1ValP = eta1( etaOneaAsTime.at(c)->GetBinContent(y+1) , etaTwoAsTime.at(c)->GetBinContent(y+1) );
	   eta1ErrValP = eta1Err(etaOneaAsTime.at(c)->GetBinContent(y+1), etaOneaAsTime.at(c)->GetBinError(y+1), etaTwoAsTime.at(c)->GetBinContent(y+1), etaTwoAsTime.at(c)->GetBinError(y+1) );
	   eta2ValP = eta2( etaOneaAsTime.at(c)->GetBinContent(y+1) , etaTwoAsTime.at(c)->GetBinContent(y+1)  );
	   eta2ErrValP = eta2Err( etaOneaAsTime.at(c)->GetBinContent(y+1), etaOneaAsTime.at(c)->GetBinError(y+1), etaTwoAsTime.at(c)->GetBinContent(y+1), etaTwoAsTime.at(c)->GetBinError(y+1) );

	   eta0ValP = eta0( etaOneaAsTime.at(c)->GetBinContent(y+1) , etaTwoAsTime.at(c)->GetBinContent(y+1) );
	   eta0ErrValP = eta0Err(etaOneaAsTime.at(c)->GetBinError(y+1) , etaTwoAsTime.at(c)->GetBinError(y+1) );

           xtZero.at(c)->SetBinContent(y+1, 1-(2*eta1ValP)-(2*eta2ValP));
           xtZero.at(c)->SetBinError(y+1, eta0ErrValP);
           xtOne.at(c)->SetBinContent(y+1, eta1ValP);
           xtOne.at(c)->SetBinError(y+1, eta1ErrValP);
           xtTwo.at(c)->SetBinContent(y+1, eta2ValP);
           xtTwo.at(c)->SetBinError(y+1, eta2ErrValP);
           cout << "xtalk plots "  << (string)part+(string)muTrack << " bin " << y+1 << "x0 " << eta0ValP << " x1 " << eta1ValP <<" x2 " << eta2ValP << " sum " <<  eta0ValP+2*eta1ValP+ 2*eta2ValP << endl;

   }
       xtZeroCan.at(c)->cd();
       xtZero.at(c)->SetTitle("");
       xtZero.at(c)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       xtZero.at(c)->GetYaxis()->SetTitle("x_0");
       xtZero.at(c)->GetXaxis()->SetRangeUser(-15,10);
       xtZero.at(c)->Draw("");
       xtZeroCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ xtZero.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       xtZeroCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ xtZero.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       xtOneCan.at(c)->cd();
       xtOne.at(c)->SetTitle("");
       xtOne.at(c)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       xtOne.at(c)->GetYaxis()->SetTitle("x_1");
       xtOne.at(c)->GetXaxis()->SetRangeUser(-15,10);
       xtOne.at(c)->Draw("");
       xtOneCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ xtOne.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       xtOneCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ xtOne.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       xtTwoCan.at(c)->cd();
       xtTwo.at(c)->SetTitle("");
       xtTwo.at(c)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       xtTwo.at(c)->GetYaxis()->SetTitle("x_1");
       xtTwo.at(c)->GetXaxis()->SetRangeUser(-15,10);
       xtTwo.at(c)->Draw("");
       xtTwoCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ xtTwo.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       xtTwoCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ xtTwo.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

       for(uint32_t j=0; j<200; j++)
       {
          //cout << "j" << j << endl;
          //cout << "hist address " << narrowTrackSharing1DataEvolutionDist.at(c).at(j) << endl;
          int ne=  narrowTrackSharing1DataEvolutionDist.at(c).at(j)->GetEntries();
          if( ne> 80)
          {
              //cout << " j " << j << "canvas address " << narrowTrackSharing1DataEvolutionDistCan.at(c).at(j) << endl;
              //narrowTrackSharing1DataEvolutionDistCan.at(c).at(j)->cd();
              //TCanvas* canTest = new TCanvas("ct", "ct");
              //canTest->cd();
              cout << "fitting " << endl;
		  gmaxbin = narrowTrackSharing1DataEvolutionDist.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolutionDist.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolutionDist.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolutionDist.at(c).at(j)->GetBinCenter(gmaxbin2);
		  
		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 = gmax2+0.15  ;
              TF1* ffiteta  =new TF1("feta","gaus",lowr1, highr1); //different range for different geometries
              narrowTrackSharing1DataEvolutionDist.at(c).at(j)->Fit(ffiteta, "RL");
              double fitMeanEta = ffiteta->GetParameter(1);
              double fitMeanEtaErr = ffiteta->GetParError(1);
              cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsDist.at(c)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl; 
              if(j-3>0)
              {
              etaOneaAsDist.at(c)->SetBinContent(j-3, fitMeanEta );
              etaOneaAsDist.at(c)->SetBinError(j-3, fitMeanEtaErr );
              }
              //canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsDist.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsDist.at(c)->GetBinLowEdge(j+1)) + ".eps").c_str());
              //canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsDist.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsDist.at(c)->GetBinLowEdge(j+1)) + ".root").c_str());
           }
       }

       etaOneaAsDistCan.at(c)->cd();
       etaOneaAsDist.at(c)->SetTitle("");
       etaOneaAsDist.at(c)->GetXaxis()->SetTitle("distance to the IP [cm]");
       etaOneaAsDist.at(c)->GetYaxis()->SetTitle("#eta #pm 1");
       //etaOneaAsDist.at(c)->Rebin(2);
       etaOneaAsDist.at(c)->GetXaxis()->SetRangeUser(0,90);
       etaOneaAsDist.at(c)->SetMaximum(0.2);
       etaOneaAsDist.at(c)->SetMinimum(0.1);
       etaOneaAsDist.at(c)->Draw("");
       etaOneaAsDistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsDist.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsDistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsDist.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


       for(uint32_t j=0; j<200; j++)
       {
          //cout << "j" << j << endl;
          //cout << "hist address " << narrowTrackSharing2DataEvolutionDist.at(c).at(j) << endl;
          int ne=  narrowTrackSharing2DataEvolutionDist.at(c).at(j)->GetEntries();
          if( ne> 80)
          {
              //cout << " j " << j << "canvas address " << narrowTrackSharing2DataEvolutionDistCan.at(c).at(j) << endl;
              //narrowTrackSharing2DataEvolutionDistCan.at(c).at(j)->cd();
              //TCanvas* canTest = new TCanvas("ct", "ct");
              //canTest->cd();Dist
		  gmaxbin = narrowTrackSharing1DataEvolutionDist.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolutionDist.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolutionDist.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolutionDist.at(c).at(j)->GetBinCenter(gmaxbin2);
		  
		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 = gmax2+0.15  ;
              cout << "fitting " << endl;
              TF1* ffiteta  =new TF1("feta","gaus",lowr2, highr2 ); //different range for different geometries
              narrowTrackSharing2DataEvolutionDist.at(c).at(j)->Fit(ffiteta, "RL");
              double fitMeanEta = ffiteta->GetParameter(1);
              double fitMeanEtaErr = ffiteta->GetParError(1);
              cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsDist.at(c)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl; 
              if(j-3>0)
              {
              etaTwoAsDist.at(c)->SetBinContent(j-3, fitMeanEta );
              etaTwoAsDist.at(c)->SetBinError(j-3, fitMeanEtaErr );
              }
              //canTest->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsDist.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaTwoAsDist.at(c)->GetBinLowEdge(j+1)) + ".eps").c_str());
              //canTest->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsDist.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaTwoAsDist.at(c)->GetBinLowEdge(j+1)) + ".root").c_str());
           }
       }

       etaTwoAsDistCan.at(c)->cd();
       etaTwoAsDist.at(c)->SetTitle("");
       etaTwoAsDist.at(c)->GetXaxis()->SetTitle("distance to the IP [cm]");
       etaTwoAsDist.at(c)->GetYaxis()->SetTitle("#eta #pm 2");
       //etaTwoAsDist.at(c)->Rebin(2);
       etaTwoAsDist.at(c)->GetXaxis()->SetRangeUser(0,90);
       etaTwoAsDist.at(c)->SetMaximum(0.08);
       etaTwoAsDist.at(c)->SetMinimum(0.02);
       etaTwoAsDist.at(c)->Draw("");
       etaTwoAsDistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsDist.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaTwoAsDistCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsDist.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


/*           TF1 *fb = new TF1("fb","TMath::Landau(x,[0],[1],0)",0,1000);
           fb->SetParameters(130,21);
	   chargeVsLE.at(c)->FitSlicesY(fb);
	   chargeVsLE_1.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsLE.at(c)->GetName()+(string)part+(string)muTrack+ "_0").c_str());
	   chargeVsLE_2.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsLE.at(c)->GetName()+(string)part+(string)muTrack+ "_1").c_str());
	   //chargeVsLE_3.at(c) =  (TH1D*)gDirectory->Get( ((string)chargeVsLE.at(c)->GetName()+(string)part+(string)muTrack+ "_2").c_str());
*/

       etaOneaAsTimeLayerCan.at(c)->cd();
       TLegend leg2a(0.58,0.20,0.93,0.40);
       for(uint32_t j=0; j<120; j++)
       {
	  int ne=  narrowTrackSharing1DataEvolutionL1.at(c).at(j)->GetEntries();
	  if( ne> 80)
	  {
		  gmaxbin = narrowTrackSharing1DataEvolutionL1.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolutionL1.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolutionL1.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolutionL1.at(c).at(j)->GetBinCenter(gmaxbin2);

		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 = gmax2+0.15  ;
	      cout << "fitting " << endl;
	      TF1* ffiteta  =new TF1("feta","gaus", lowr1, highr1); //different range for different geometries
	      narrowTrackSharing1DataEvolutionL1.at(c).at(j)->Fit(ffiteta, "RL");
	      double fitMeanEta = ffiteta->GetParameter(1);
	      double fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeLayer.at(c).at(0)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeLayer.at(c).at(0)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeLayer.at(c).at(0)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing1DataEvolutionL2.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeLayer.at(c).at(1)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeLayer.at(c).at(1)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeLayer.at(c).at(1)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing1DataEvolutionL3.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeLayer.at(c).at(2)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeLayer.at(c).at(2)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeLayer.at(c).at(2)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing1DataEvolutionL4.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeLayer.at(c).at(3)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeLayer.at(c).at(3)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeLayer.at(c).at(3)->SetBinError(j-1, fitMeanEtaErr );
	      }
	   }
       }

       etaOneaAsTimeLayer.at(c).at(0)->SetTitle("");
       etaOneaAsTimeLayer.at(c).at(0)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       etaOneaAsTimeLayer.at(c).at(0)->GetXaxis()->SetRangeUser(-15,5);
       etaOneaAsTimeLayer.at(c).at(0)->GetYaxis()->SetTitle("#eta_{#pm 1}");
       etaOneaAsTimeLayer.at(c).at(0)->SetLineColor(hcolors.at(1));
       etaOneaAsTimeLayer.at(c).at(1)->SetLineColor(hcolors.at(2));
       etaOneaAsTimeLayer.at(c).at(2)->SetLineColor(hcolors.at(3));
       etaOneaAsTimeLayer.at(c).at(3)->SetLineColor(hcolors.at(4));
       etaOneaAsTimeLayer.at(c).at(0)->SetMarkerColor(hcolors.at(1));
       etaOneaAsTimeLayer.at(c).at(1)->SetMarkerColor(hcolors.at(2));
       etaOneaAsTimeLayer.at(c).at(2)->SetMarkerColor(hcolors.at(3));
       etaOneaAsTimeLayer.at(c).at(3)->SetMarkerColor(hcolors.at(4));
       etaOneaAsTimeLayer.at(c).at(0)->Draw("e");
       etaOneaAsTimeLayer.at(c).at(1)->Draw("same e");
       etaOneaAsTimeLayer.at(c).at(2)->Draw("same e");
       etaOneaAsTimeLayer.at(c).at(3)->Draw("same e");
       text.Draw("same");
       leg2a.AddEntry( etaOneaAsTimeLayer.at(c).at(0)  , "TOB L1"  , "p");
       leg2a.AddEntry( etaOneaAsTimeLayer.at(c).at(1)  , "TOB L2"  , "p");
       leg2a.AddEntry( etaOneaAsTimeLayer.at(c).at(2)  , "TOB L3"  , "p");
       leg2a.AddEntry( etaOneaAsTimeLayer.at(c).at(3)  , "TOB L4"  , "p");
       leg2a.Draw();
       etaOneaAsTimeLayerCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeLayer.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsTimeLayerCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeLayer.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".root").c_str());



       etaTwoAsTimeLayerCan.at(c)->cd();
       TLegend leg2b(0.58,0.20,0.93,0.40);
       for(uint32_t j=0; j<120; j++)
       {
	  int ne=  narrowTrackSharing2DataEvolutionL1.at(c).at(j)->GetEntries();
	  if( ne> 80)
	  {
		  gmaxbin = narrowTrackSharing1DataEvolutionL1.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolutionL1.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolutionL1.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolutionL1.at(c).at(j)->GetBinCenter(gmaxbin2);
		  
		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 = gmax2+0.15  ;
	      cout << "fitting " << endl;
	      TF1* ffiteta  =new TF1("feta","gaus", lowr2, highr2); //different range for different geometries
	      narrowTrackSharing2DataEvolutionL1.at(c).at(j)->Fit(ffiteta, "RL");
	      double fitMeanEta = ffiteta->GetParameter(1);
	      double fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeLayer.at(c).at(0)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeLayer.at(c).at(0)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeLayer.at(c).at(0)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing2DataEvolutionL2.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeLayer.at(c).at(1)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeLayer.at(c).at(1)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeLayer.at(c).at(1)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing2DataEvolutionL3.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeLayer.at(c).at(2)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeLayer.at(c).at(2)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeLayer.at(c).at(2)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing2DataEvolutionL4.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeLayer.at(c).at(3)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeLayer.at(c).at(3)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeLayer.at(c).at(3)->SetBinError(j-1, fitMeanEtaErr );
	      }
	   }
       }

       etaTwoAsTimeLayer.at(c).at(0)->SetTitle("");
       etaTwoAsTimeLayer.at(c).at(0)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       etaTwoAsTimeLayer.at(c).at(0)->GetXaxis()->SetRangeUser(-15,5);
       etaTwoAsTimeLayer.at(c).at(0)->GetYaxis()->SetTitle("#eta_{#pm 2}");
       etaTwoAsTimeLayer.at(c).at(0)->SetLineColor(hcolors.at(1));
       etaTwoAsTimeLayer.at(c).at(1)->SetLineColor(hcolors.at(2));
       etaTwoAsTimeLayer.at(c).at(2)->SetLineColor(hcolors.at(3));
       etaTwoAsTimeLayer.at(c).at(3)->SetLineColor(hcolors.at(4));
       etaTwoAsTimeLayer.at(c).at(0)->SetMarkerColor(hcolors.at(1));
       etaTwoAsTimeLayer.at(c).at(1)->SetMarkerColor(hcolors.at(2));
       etaTwoAsTimeLayer.at(c).at(2)->SetMarkerColor(hcolors.at(3));
       etaTwoAsTimeLayer.at(c).at(3)->SetMarkerColor(hcolors.at(4));
       etaTwoAsTimeLayer.at(c).at(0)->Draw("e");
       etaTwoAsTimeLayer.at(c).at(1)->Draw("same e");
       etaTwoAsTimeLayer.at(c).at(2)->Draw("same e");
       etaTwoAsTimeLayer.at(c).at(3)->Draw("same e");
       text.Draw("same");
       leg2b.AddEntry( etaTwoAsTimeLayer.at(c).at(0)  , "TOB L1"  , "p");
       leg2b.AddEntry( etaTwoAsTimeLayer.at(c).at(1)  , "TOB L2"  , "p");
       leg2b.AddEntry( etaTwoAsTimeLayer.at(c).at(2)  , "TOB L3"  , "p");
       leg2b.AddEntry( etaTwoAsTimeLayer.at(c).at(3)  , "TOB L4"  , "p");
       leg2b.Draw();
       etaTwoAsTimeLayerCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsTimeLayer.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaTwoAsTimeLayerCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsTimeLayer.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".root").c_str());



       etaOneaAsTimeMonoStereoCan.at(c)->cd();
       TLegend leg3a(0.58,0.20,0.93,0.40);
       for(uint32_t j=0; j<120; j++)
       {
	  int ne=  narrowTrackSharing1DataEvolutionL1m.at(c).at(j)->GetEntries();
	  if( ne> 80)
	  {
		  gmaxbin = narrowTrackSharing1DataEvolutionL1m.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolutionL1m.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolutionL1m.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolutionL1m.at(c).at(j)->GetBinCenter(gmaxbin2);
		  
		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 =gmax2+0.15  ;
	      cout << "fitting " << endl;
	      TF1* ffiteta  =new TF1("feta","gaus", lowr1, highr1); //different range for different geometries
	      narrowTrackSharing1DataEvolutionL1m.at(c).at(j)->Fit(ffiteta, "RL");
	      double fitMeanEta = ffiteta->GetParameter(1);
	      double fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeMonoStereo.at(c).at(0)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeMonoStereo.at(c).at(0)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeMonoStereo.at(c).at(0)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing1DataEvolutionL1s.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeMonoStereo.at(c).at(1)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeMonoStereo.at(c).at(1)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeMonoStereo.at(c).at(1)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing1DataEvolutionL2m.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeMonoStereo.at(c).at(2)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeMonoStereo.at(c).at(2)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeMonoStereo.at(c).at(2)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing1DataEvolutionL2s.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTimeMonoStereo.at(c).at(3)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaOneaAsTimeMonoStereo.at(c).at(3)->SetBinContent(j-1, fitMeanEta );
		  etaOneaAsTimeMonoStereo.at(c).at(3)->SetBinError(j-1, fitMeanEtaErr );
	      }
	   }
       }

       etaOneaAsTimeMonoStereo.at(c).at(0)->SetTitle("");
       etaOneaAsTimeMonoStereo.at(c).at(0)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       etaOneaAsTimeMonoStereo.at(c).at(0)->GetXaxis()->SetRangeUser(-15,5);
       //etaOneaAsTimeMonoStereo.at(c).at(0)->GetYaxis()->SetRangeUser(-0.08,0.22);
       //etaOneaAsTimeMonoStereo.at(c).at(1)->GetYaxis()->SetRangeUser(-0.08,0.22);
       //etaOneaAsTimeMonoStereo.at(c).at(2)->GetYaxis()->SetRangeUser(-0.08,0.22);
       //etaOneaAsTimeMonoStereo.at(c).at(3)->GetYaxis()->SetRangeUser(-0.08,0.22);
       etaOneaAsTimeMonoStereo.at(c).at(0)->GetYaxis()->SetTitle("#eta_{#pm 1}");
       etaOneaAsTimeMonoStereo.at(c).at(0)->SetLineColor(hcolors.at(1));
       etaOneaAsTimeMonoStereo.at(c).at(1)->SetLineColor(hcolors.at(2));
       etaOneaAsTimeMonoStereo.at(c).at(2)->SetLineColor(hcolors.at(3));
       etaOneaAsTimeMonoStereo.at(c).at(3)->SetLineColor(hcolors.at(4));
       etaOneaAsTimeMonoStereo.at(c).at(0)->SetMarkerColor(hcolors.at(1));
       etaOneaAsTimeMonoStereo.at(c).at(1)->SetMarkerColor(hcolors.at(2));
       etaOneaAsTimeMonoStereo.at(c).at(2)->SetMarkerColor(hcolors.at(3));
       etaOneaAsTimeMonoStereo.at(c).at(3)->SetMarkerColor(hcolors.at(4));
       etaOneaAsTimeMonoStereo.at(c).at(0)->Draw("e");
       etaOneaAsTimeMonoStereo.at(c).at(1)->Draw("same e");
       etaOneaAsTimeMonoStereo.at(c).at(2)->Draw("same e");
       etaOneaAsTimeMonoStereo.at(c).at(3)->Draw("same e");
       text.Draw("same");
       leg3a.AddEntry( etaOneaAsTimeMonoStereo.at(c).at(0)  , "TOB L1 mono"  , "p");
       leg3a.AddEntry( etaOneaAsTimeMonoStereo.at(c).at(1)  , "TOB L1 stereo"  , "p");
       leg3a.AddEntry( etaOneaAsTimeMonoStereo.at(c).at(2)  , "TOB L2 mono"  , "p");
       leg3a.AddEntry( etaOneaAsTimeMonoStereo.at(c).at(3)  , "TOB L2 stereo"  , "p");
       leg3a.Draw();
       etaOneaAsTimeMonoStereoCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeMonoStereo.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsTimeMonoStereoCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTimeMonoStereo.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".root").c_str());



       etaTwoAsTimeMonoStereoCan.at(c)->cd();
       TLegend leg3b(0.58,0.20,0.93,0.40);
       for(uint32_t j=0; j<120; j++)
       {
	  int ne=  narrowTrackSharing2DataEvolutionL1m.at(c).at(j)->GetEntries();
	  if( ne> 80)
	  {
		  gmaxbin = narrowTrackSharing1DataEvolutionL1m.at(c).at(j)->GetMaximumBin();
		  gmax = narrowTrackSharing1DataEvolutionL1m.at(c).at(j)->GetBinCenter(gmaxbin);
		  gmaxbin2 = narrowTrackSharing2DataEvolutionL1m.at(c).at(j)->GetMaximumBin();
		  gmax2 = narrowTrackSharing2DataEvolutionL1m.at(c).at(j)->GetBinCenter(gmaxbin2);
		  
		  lowr1 = gmax-0.1 ;
		  highr1 = gmax+0.1 ;
		  lowr2 = gmax2-0.15 ;
		  highr2 = gmax2+0.15  ;
	      cout << "fitting " << endl;
	      TF1* ffiteta  =new TF1("feta","gaus", lowr2, highr2); //different range for different geometries
	      narrowTrackSharing2DataEvolutionL1m.at(c).at(j)->Fit(ffiteta, "RL");
	      double fitMeanEta = ffiteta->GetParameter(1);
	      double fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeMonoStereo.at(c).at(0)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeMonoStereo.at(c).at(0)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeMonoStereo.at(c).at(0)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing2DataEvolutionL1s.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeMonoStereo.at(c).at(1)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeMonoStereo.at(c).at(1)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeMonoStereo.at(c).at(1)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing2DataEvolutionL2m.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeMonoStereo.at(c).at(2)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeMonoStereo.at(c).at(2)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeMonoStereo.at(c).at(2)->SetBinError(j-1, fitMeanEtaErr );
	      }
	      narrowTrackSharing2DataEvolutionL2s.at(c).at(j)->Fit(ffiteta, "RL");
	      fitMeanEta = ffiteta->GetParameter(1);
	      fitMeanEtaErr = ffiteta->GetParError(1);
	      cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaTwoAsTimeMonoStereo.at(c).at(3)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
	      if(j>4) 
	      {
		  etaTwoAsTimeMonoStereo.at(c).at(3)->SetBinContent(j-1, fitMeanEta );
		  etaTwoAsTimeMonoStereo.at(c).at(3)->SetBinError(j-1, fitMeanEtaErr );
	      }
	   }
       }

       etaTwoAsTimeMonoStereo.at(c).at(0)->SetTitle("");
       etaTwoAsTimeMonoStereo.at(c).at(0)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       etaTwoAsTimeMonoStereo.at(c).at(0)->GetXaxis()->SetRangeUser(-15,5);
       etaTwoAsTimeMonoStereo.at(c).at(0)->GetYaxis()->SetTitle("#eta_{#pm 2}");
       etaTwoAsTimeMonoStereo.at(c).at(0)->SetLineColor(hcolors.at(1));
       etaTwoAsTimeMonoStereo.at(c).at(1)->SetLineColor(hcolors.at(2));
       etaTwoAsTimeMonoStereo.at(c).at(2)->SetLineColor(hcolors.at(3));
       etaTwoAsTimeMonoStereo.at(c).at(3)->SetLineColor(hcolors.at(4));
       etaTwoAsTimeMonoStereo.at(c).at(0)->SetMarkerColor(hcolors.at(1));
       etaTwoAsTimeMonoStereo.at(c).at(1)->SetMarkerColor(hcolors.at(2));
       etaTwoAsTimeMonoStereo.at(c).at(2)->SetMarkerColor(hcolors.at(3));
       etaTwoAsTimeMonoStereo.at(c).at(3)->SetMarkerColor(hcolors.at(4));
       etaTwoAsTimeMonoStereo.at(c).at(0)->Draw("e");
       etaTwoAsTimeMonoStereo.at(c).at(1)->Draw("same e");
       etaTwoAsTimeMonoStereo.at(c).at(2)->Draw("same e");
       etaTwoAsTimeMonoStereo.at(c).at(3)->Draw("same e");
       text.Draw("same");
       leg3b.AddEntry( etaTwoAsTimeMonoStereo.at(c).at(0)  , "TOB L1 mono"  , "p");
       leg3b.AddEntry( etaTwoAsTimeMonoStereo.at(c).at(1)  , "TOB L1 stereo"  , "p");
       leg3b.AddEntry( etaTwoAsTimeMonoStereo.at(c).at(2)  , "TOB L2 mono"  , "p");
       leg3b.AddEntry( etaTwoAsTimeMonoStereo.at(c).at(3)  , "TOB L2 stereo"  , "p");
       leg3b.Draw();
       etaTwoAsTimeMonoStereoCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsTimeMonoStereo.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaTwoAsTimeMonoStereoCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaTwoAsTimeMonoStereo.at(c).at(0)->GetName()+(string)part+(string)muTrack+ ".root").c_str());


/////////////////
/*       for(uint32_t j=0; j<120; j++)
       {
          //cout << "j" << j << endl;
          //cout << "hist address " << narrowTrackSharing1DataEvolution.at(c).at(j) << endl;
          int ne=  narrowTrackSharing1DataEvolution.at(c).at(j)->GetEntries();
          if( ne> 50)
          {
              //cout << " j " << j << "canvas address " << narrowTrackSharing1DataEvolutionCan.at(c).at(j) << endl;
              //narrowTrackSharing1DataEvolutionCan.at(c).at(j)->cd();
              TCanvas* canTest = new TCanvas("ct", "ct");
              canTest->cd();
              cout << "fitting " << endl;
              TF1* ffiteta  =new TF1("feta","gaus", lowr1, highr1); //different range for different geometries
              narrowTrackSharing1DataEvolution.at(c).at(j)->Fit(ffiteta, "RL");
              double fitMeanEta = ffiteta->GetParameter(1);
              double fitMeanEtaErr = ffiteta->GetParError(1);
              cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
              if(j>2) 
              {
                  etaOneaAsTime.at(c)->SetBinContent(j-2, fitMeanEta );
                  etaOneaAsTime.at(c)->SetBinError(j-2, fitMeanEtaErr );
              }
              canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) + ".eps").c_str());
              canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) + ".root").c_str());
           }
       }

       etaOneaAsTimeCan.at(c)->cd();
       etaOneaAsTime.at(c)->SetTitle("");
       etaOneaAsTime.at(c)->GetXaxis()->SetTitle("time");
       etaOneaAsTime.at(c)->GetYaxis()->SetTitle("#eta #pm 1");
       etaOneaAsTime.at(c)->Draw("");
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       for(uint32_t j=0; j<120; j++)
       {
          //cout << "j" << j << endl;
          //cout << "hist address " << narrowTrackSharing1DataEvolution.at(c).at(j) << endl;
          int ne=  narrowTrackSharing1DataEvolution.at(c).at(j)->GetEntries();
          if( ne> 50)
          {
              //cout << " j " << j << "canvas address " << narrowTrackSharing1DataEvolutionCan.at(c).at(j) << endl;
              //narrowTrackSharing1DataEvolutionCan.at(c).at(j)->cd();
              TCanvas* canTest = new TCanvas("ct", "ct");
              canTest->cd();
              cout << "fitting " << endl;
              TF1* ffiteta  =new TF1("feta","gaus", lowr1, highr1); //different range for different geometries
              narrowTrackSharing1DataEvolution.at(c).at(j)->Fit(ffiteta, "RL");
              double fitMeanEta = ffiteta->GetParameter(1);
              double fitMeanEtaErr = ffiteta->GetParError(1);
              cout << "binned fit bin " << (string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) << "mean " << fitMeanEta << "+-" << fitMeanEtaErr << endl;
              if(j>2) 
              {
                  etaOneaAsTime.at(c)->SetBinContent(j-2, fitMeanEta );
                  etaOneaAsTime.at(c)->SetBinError(j-2, fitMeanEtaErr );
              }
              canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) + ".eps").c_str());
              canTest->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ "bin" +to_string( etaOneaAsTime.at(c)->GetBinLowEdge(j+1)) + ".root").c_str());
           }
       }

       etaOneaAsTimeCan.at(c)->cd();
       etaOneaAsTime.at(c)->SetTitle("");
       etaOneaAsTime.at(c)->GetXaxis()->SetTitle("time");
       etaOneaAsTime.at(c)->GetYaxis()->SetTitle("#eta #pm 1");
       etaOneaAsTime.at(c)->Draw("");
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
       etaOneaAsTimeCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ etaOneaAsTime.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());

*/



             

  /*     innerZCan.at(c)->cd();
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

       innerVYCan.at(c)->cd();
       innerVY.at(c)->GetXaxis()->SetTitle("vy");
       innerVY.at(c)->SetTitle("");
       innerVY.at(c)->Draw("hist"); 
       innerVYCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVY.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       innerVYCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVY.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       innerVXCan.at(c)->cd();
       innerVX.at(c)->GetXaxis()->SetTitle("vx");
       innerVX.at(c)->SetTitle("");
       innerVX.at(c)->Draw("hist"); 
       innerVXCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVX.at(c)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       innerVXCan.at(c)->SaveAs(("output/"+(string)dir+"/"+ innerVX.at(c)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());
  */
       //sort(timeMedian.at(c).begin(), timeMedian.at(c).end() );
       //uint32_t vecSize =timeMedian.at(c).size();
       //float median = -100 ;
       //if(vecSize != 0)
       //    median = timeMedian.at(c).at( (int)ceil(vecSize/2) );

       //cout << " time median for " << narrowTrackSharing1Data.at(c)->GetName()+(string)part+(string)muTrack << " " << median << endl;

       }


      /////////////////////////////////////////////////////


       TCanvas c35("dummyCTplot","dummyCTplot");
       dummyCTplot->Draw("hist"); 
       c35.SaveAs(("output/"+(string)dir+"/"+  "dummyCTplot.root").c_str());
       c35.SaveAs(("output/"+(string)dir+"/"+  "dummyCTplot.eps").c_str());

       timeVsVzLayersCan->cd();
       timeVsVzLayersNotZCorr->GetXaxis()->SetTitle("vz");
       timeVsVzLayersNotZCorr->GetYaxis()->SetTitle("time");
       timeVsVzLayersNotZCorr->SetTitle("");
       timeVsVzLayersNotZCorr->SetLineColor(kRed); 
       timeVsVzLayersNotZCorr->Draw(""); 
       timeVsVzLayers->Draw(" same"); 
       timeVsVzLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVzLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timeVsVzLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVzLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       timeVsVxLayersCan->cd();
       timeVsVxLayers->GetXaxis()->SetTitle("vx");
       timeVsVxLayers->GetYaxis()->SetTitle("time");
       timeVsVxLayers->SetTitle("");
       timeVsVxLayers->Draw(""); 
       timeVsVxLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVxLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timeVsVxLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVxLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());


       timeVsVyLayersCan->cd();
       timeVsVyLayers->GetXaxis()->SetTitle("vy");
       timeVsVyLayers->GetYaxis()->SetTitle("time");
       timeVsVyLayers->SetTitle("");
       timeVsVyLayers->Draw(""); 
       timeVsVyLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVyLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timeVsVyLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsVyLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       timeVsDistLayersCan->cd();
       timeVsDistLayersNotDistCorr->GetXaxis()->SetTitle("distance from IP");
       timeVsDistLayersNotDistCorr->GetYaxis()->SetTitle("time");
       timeVsDistLayersNotDistCorr->SetTitle("");
       timeVsDistLayersNotDistCorr->SetLineColor(kRed); 
       timeVsDistLayersNotDistCorr->Draw(""); 
       timeVsDistLayers->Draw("same"); 
       timeVsDistLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsDistLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timeVsDistLayersCan->SaveAs(("output/"+(string)dir+"/"+ timeVsDistLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       timeVsDistLayers2DCan->cd();
       timeVsDistLayers2D->GetXaxis()->SetTitle("distance from IP");
       timeVsDistLayers2D->GetYaxis()->SetTitle("time");
       timeVsDistLayers2D->SetTitle("");
       timeVsDistLayers2D->Draw("colz"); 
       timeVsDistLayers2DCan->SaveAs(("output/"+(string)dir+"/"+ timeVsDistLayers2D->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       timeVsDistLayers2DCan->SaveAs(("output/"+(string)dir+"/"+ timeVsDistLayers2D->GetName()+(string)part+(string)muTrack+ ".eps").c_str());



       chargePerUnitLayersCan->cd();
       chargePerUnitLayers->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
       chargePerUnitLayers->GetYaxis()->SetTitle("cluster charge over path [ADC/cm]");
       chargePerUnitLayers->SetTitle("");
       chargePerUnitLayers->SetLineColor(kBlack);
       chargePerUnitLayers->Draw("");
       chargePerUnitLayersGlobal->SetLineColor(kGreen);
       chargePerUnitLayersGlobal->Draw("same");
       chargePerUnitLayersTracker->SetLineColor(kRed);
       chargePerUnitLayersTracker->Draw("same");
       chargePerUnitLayersBeta->SetLineColor(kBlue);
       chargePerUnitLayersBeta->Draw("same");
       chargePerUnitLayersCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       chargePerUnitLayersCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       chargePerUnitHistLayersCan->cd();
       chargePerUnitHistLayers->GetXaxis()->SetTitle(" rescaled cluster charge");
       chargePerUnitHistLayers->SetTitle("");
       chargePerUnitHistLayers->Draw(""); 
       chargePerUnitHistLayersCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitHistLayers->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       chargePerUnitHistLayersCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitHistLayers->GetName()+(string)part+(string)muTrack+ ".eps").c_str());


       chargePerUnitLayersBinsCan->cd();
       TLegend leg1(0.6,0.7,0.9,0.9);
       for(uint32_t u=0; u<4; u++)
       {
           chargePerUnitLayersBins.at(u)->GetXaxis()->SetTitle("time_{IP}^{InOut} [ns]");
           chargePerUnitLayersBins.at(u)->GetYaxis()->SetTitle("cluster seed charge over path [ADC/cm]");
           chargePerUnitLayersBins.at(u)->SetTitle("");
           chargePerUnitLayersBins.at(u)->SetLineColor(hcolors.at(u+1));
           chargePerUnitLayersBins.at(u)->SetMarkerColor(hcolors.at(u+1));
           chargePerUnitLayersBins.at(u)->SetStats(kFALSE);
           if(u==0)
               chargePerUnitLayersBins.at(u)->SetMaximum(1.2*(chargePerUnitLayersBins.at(u)->GetMaximum()));
           if(u==0)
               chargePerUnitLayersBins.at(u)->Draw("e");
           else
               chargePerUnitLayersBins.at(u)->Draw("same e");
       }
       TF1* fb  =new TF1("feta","gaus", -16, 4); //different range for different geometries
       for(uint32_t u=0; u< 4; u++)
       {
           sort(timeMedianLayers.at(u).begin(), timeMedianLayers.at(u).end() );
           uint32_t half = floor(timeMedianLayers.at(u).size()/2) ;
           cout << " size " << timeMedianLayers.at(u).size() <<  " half  " << half << endl;
           float medL = 0;
           if(half>0)
                medL = timeMedianLayers.at(u).at(half);
           cout << "end time emdian " << endl;
           fb->SetLineColor(hcolors.at(u+1));
           chargePerUnitLayersBins.at(u)->Fit(fb, "RL");
           chargePerUnitLayersBins.at(u)->SetStats(kFALSE);
	   cout << "fit bin " << u << " mean " <<  fb->GetParameter(1) << " error  " << fb->GetParError(1) << endl;
           double ft = fb->GetParameter(1);
           double ftE = fb->GetParError(1);
           float whichb = chargePerUnitLayersBinsFit->FindBin(medL);
           chargePerUnitLayersBinsFit->SetBinContent(whichb ,ft);
           cout << " median " <<  medL <<  " point " << whichb << " fit "<< ft << endl;
           chargePerUnitLayersBinsFit->SetBinError(whichb ,ftE);
       }
       //TLegend leg1(0.6,0.7,0.9,0.9);
       leg1.AddEntry( chargePerUnitLayersBins.at(0)  , "dist<20cm"  , "p");
       leg1.AddEntry( chargePerUnitLayersBins.at(1)  , "20cm<dist<40cm"  , "p");
       leg1.AddEntry( chargePerUnitLayersBins.at(2)  , "40cm<dist<60cm"  , "p");
       leg1.AddEntry( chargePerUnitLayersBins.at(3)  , "60cm<dist<80cm"  , "p");
       leg1.Draw();
       chargePerUnitLayersBinsCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayersBins.at(0)->GetName()+(string)part+(string)muTrack+ ".root").c_str());
       chargePerUnitLayersBinsCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayersBins.at(0)->GetName()+(string)part+(string)muTrack+ ".eps").c_str());

       TF1* linTimeL  =new TF1("fl1L","pol1", 0, 100); //different range for different geometries

       TFitResultPtr fitresL = chargePerUnitLayersBinsFit->Fit( linTimeL , "RS"); 
       chargePerUnitLayersBinsFit->GetYaxis()->SetTitle("time_{IP}^{InOut} [cm]");
       chargePerUnitLayersBinsFit->GetXaxis()->SetTitle("track distance to the IP [cm]");
       //cout << chargePerUnitlayersBins.at(0)->GetName() << "fit" << part << muTrack << endl;
       TMatrixDSym cov = fitresL->GetCovarianceMatrix();
       double fitp1 = linTimeL->GetParameter(0);
       double fitp1Err = linTimeL->GetParError(0);
       double fitp2 = linTimeL->GetParameter(1);
       double fitp2Err = linTimeL->GetParError(1);
       //double totalErr = TMath::Sqrt( (fitp1Err*fitp1Err)+(fitp2Err*fitp2Err)+ cov(0,1)  ); 
       double totalErr = fitp1Err; 
       cout << "time correction par1 " << fitp1 << " par1 err  " << fitp1Err << " par2  " << fitp2 << " par2 err " << fitp2Err << " total err " << totalErr << endl;
       cout << "covariance element " << cov(0,1) << endl;
       fitresL->PrintCovMatrix(cout);
       chargePerUnitLayersBinsFitCan->cd();
       chargePerUnitLayersBinsFit->Draw("e");
       chargePerUnitLayersBinsFitCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayersBins.at(0)->GetName()+"fit"+(string)part+(string)muTrack+ ".root").c_str());
       chargePerUnitLayersBinsFitCan->SaveAs(("output/"+(string)dir+"/"+ chargePerUnitLayersBins.at(0)->GetName()+"fit"+(string)part+(string)muTrack+ ".eps").c_str());

    //cout << "in here 7"  << endl;

   return 0;
}

double eta0Err( double seta1, double seta2 )
{
    return TMath::Sqrt( 4*TMath::Power(seta1 ,2 ) + 4*TMath::Power( seta2,2 )  );
}

double eta1Err( double mean1, double smean1, double mean2, double smean2 )
{
    double term1 = (2*mean2 + 1)/TMath::Power(2*mean1 + 2*mean2 +1, 2);
    double term2 = (2*mean1)/TMath::Power(2*mean1 + 2*mean2 +1, 2);
    return TMath::Sqrt( (TMath::Power( term1  ,2 )*TMath::Power(smean1 ,2 )) + (TMath::Power( term2,2 )*TMath::Power( smean2,2 ))  );
}


double eta2Err( double mean1, double smean1, double mean2, double smean2 )
{
    double term1 = (2*mean2)/TMath::Power(2*mean1 + 2*mean2 +1,2);
    double term2 = (2*mean1 +1)/TMath::Power(2*mean1 + 2*mean2 +1,2);
    return TMath::Sqrt( (TMath::Power( term1  ,2 )*TMath::Power(smean1 ,2 )) + (TMath::Power( term2,2 )*TMath::Power( smean2,2 ))  );
}



double eta0( double eta1, double eta2 )
{
    return 1-(2*eta1)-(2*eta2);
}

double eta1( double mean1, double mean2 )
{
    return mean1/ (1+2*mean1+2*mean2);
}


double eta2( double mean1,  double mean2 )
{
    return mean2/ (1+2*mean1+2*mean2);
}

