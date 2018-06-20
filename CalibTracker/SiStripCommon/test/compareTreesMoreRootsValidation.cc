//e to ADC tuned OLD
//./compareTreesMoreRootsValidation 6 test_shallowTrackAndCluster_CollDataValidation.root test_shallowTrackAndCluster_CollMCValidation.rootColl2017ePerADCdefstep3.root test_shallowTrackAndCluster_CollMCValidation.rootColl2017ePerADCmin20step3.root test_shallowTrackAndCluster_CollMCValidation.rootColl2017ePerADCmin10step3.root test_shallowTrackAndCluster_CollMCValidation.rootColl2017ePerADCpl10step3.root test_shallowTrackAndCluster_CollMCValidation.rootColl2017ePerADCpl20step3.root  TOB 1 4 yes ColltunedXTALKValidation
//
//data/MC default
//./compareTreesMoreRootsValidation 2 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root TOB 1 4 yes tuningDef simulation

//data/MC template
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/ TOB 1 4 yes tuning

//data/MC AV
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_240step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_270step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_330step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_360step3.rootanalyzer2.root TOB 1 4 yes tuningAV AV 300-default 240 270 330 360
//
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_240step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_270step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_330step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_AV_360step3.rootanalyzer2.root TOB 1 4 yes tuningAV AV 300 -20% -10% +10% +20%

//data/MC DV
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DV_136step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DV_153step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DV_187step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DV_204step3.rootanalyzer2.root TOB 1 4 yes tuningDV DV 170 -20% -10% +10% +20%
//
//
//data/MC gevPerElectron
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_GevPerElectron_2.888e-09step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_GevPerElectron_3.249e-09step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_GevPerElectron_3.971e-09step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_GevPerElectron_4.332e-09step3.rootanalyzer2.root TOB 1 4 yes tuningGevPerElectron Ee 3.61e-09  -20% -10% +10% +20%

//data/MC temperature
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Temperature_219step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Temperature_246step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Temperature_300step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Temperature_327step3.rootanalyzer2.root TOB 1 4 yes tuningTemperature T 273  -20% -10% +10% +20%
//
////data/MC chargeDistrRMS
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_ChargeDistributionRMS_5.2e-10step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_ChargeDistributionRMS_5.85e-10step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_ChargeDistributionRMS_7.15e-10step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_ChargeDistributionRMS_7.8e-10step3.rootanalyzer2.root TOB 1 4 yes tuningChargeDistributionRMS ChargeDistrRMS 6.5e-10-default 5.2e-10 5.85e-10 7.15e-10 7.8e-10
//
//data/MC DeltaProductionCut
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.09634step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.1083825step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.1324675step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.14451step3.rootanalyzer2.root TOB 1 4 yes tuningDeltaProductionCut #delta 0.120425 0.09634 0.1083825 0.1324675 0.14451
//
//
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.09634step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.1083825step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.1324675step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.14451step3.rootanalyzer2.root TOB 1 4 yes tuningDeltaProductionCut delta 0.120425 0.120425-20% 0.120425-10% 0.120425+10% 0.120425+20%
//
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.09634step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.1083825step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.1324675step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_DeltaProductionCut_0.14451step3.rootanalyzer2.root TOB 1 4 yes tuningDeltaProductionCut delta 0.120425 -20% -10% +10% +20%
//
//
//data/MC ChatgeMobility 
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Mobility_248step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Mobility_279step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Mobility_341step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_Mobility_372step3.rootanalyzer2.root TOB 1 4 yes tuningChargeMobility mu 310 -20% -10% +10% +20%
//
//data/MC ePerADC
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_electronPerAdc_197step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_electronPerAdc_222step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_electronPerAdc_272step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_electronPerAdc_297step3.rootanalyzer2.root TOB 1 4 yes tuningElectronPerAdc eADC 247 -20% -10% +10% +20%

//data/MC coupling
//./compareTreesMoreRootsValidation 7 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_247_0.12_0.029000000000000001step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_247_0.12_0.023step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_247_0.10000000000000001_0.029000000000000001step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_247_0.10000000000000001_0.023step3.rootanalyzer2.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_247_0.070000000000000007_0.023step3.rootanalyzer2.root TOB 1 4 yes tuningXtalk XT 0.725,0.110,0.027 =0.702,0.120,0.029 =0.714,0.120,0.023  =0.742,0.100,0.029 =0.754,0.100,0.023 =0.814,0.070,0.023

//data/MC LA
//./compareTreesMoreRootsValidation 6 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_LA_0.01444step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_LA_0.01889step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_LA_0.02777step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_LA_0.03222step3.rootanalyzer2.root TOB 1 4 yes tuningLA LA 0.023+-0.004 -2 -1 +1 +2


//data/MC xtalk measurement
//./compareTreesMoreRootsValidation 3 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_XTmNZstep3.rootanalyzer2.root TOB 1 4 yes tuningMeasured XTm default updated

//./compareTreesMoreRootsValidation 3 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_XTmdiststep3.rootanalyzer2.root TOB 1 4 yes tuningMeasured XT default updated

//./compareTreesMoreRootsValidation 3 /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_test.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_default_1step3.rootanalyzer2.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_XTmdiststep3.rootanalyzer2.root TID 1 1 yes tuningMeasured XT default updated

//Coll2017_XTmdiststep3.rootanalyzer2.root

//TODO rest
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream> 
#include <cmath>
#include <exception>
#include <ctime>

#include "TNtuple.h"
#include "TROOT.h"
#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
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
#include "TLatex.h"

using namespace std;

#include "tdrstyle.C"

int main(int argc, char *argv[]){

Modified_tdr_style();

//    gStyle->SetOptStat(0);
//gROOT->ForceStyle();

    //if(argc != 7)
    //    throw std::runtime_error("Bad number of arguments!");
    
    TString nfiles = argv[1];
    uint32_t nfile = nfiles.Atoi();
    TString file1 = argv[2];

    vector<TString> fileSim;
    for(uint32_t t = 0; t< nfile-1; t++)
    {
        fileSim.push_back(argv[t+3]);
    }
    TString subDet = argv[nfile+2];
    TString slayerD = argv[nfile+3];
    TString slayerU = argv[nfile+4];
    TString norm = argv[nfile+5];
    TString dir = argv[nfile+6];
    TString qt = argv[nfile+7];

    int layerD = slayerD.Atoi();      
    int layerU = slayerU.Atoi();      

    vector<TString> LE;
    for(uint32_t t = 0; t< nfile-1; t++)
    {
        LE.push_back(argv[t+8+nfile]);
    }


    uint16_t sdId = 0;

    if(subDet == "TIB")
        sdId = 3;
    else if(subDet == "TID")
        sdId = 4;
    else if(subDet == "TOB")
        sdId = 5;
    else if(subDet == "TEC")
        sdId = 6;
    else if(subDet == "all")
        sdId = 0;
    else
        throw std::runtime_error("Wrong partition entered");

    string label = "";
    if(sdId==3 && layerD==1)
        label = "IB1";
    if(sdId==3 && layerD==3)
        label = "IB2";
    if(sdId==5 && layerD==1)
        label = "OB2";
    if(sdId==5 && layerD==5)
        label = "OB1";

    TFile* f1 = NULL;
    TTree* t1 = NULL;
    f1 = TFile::Open(file1); 

    vector<TFile*> f2;
    vector<TTree*> t2;
    for(uint32_t t =0; t<fileSim.size(); t++)
    {
        TFile* fle = NULL;
        fle =  TFile::Open(fileSim.at(t));
        f2.push_back(fle);
    }
 
    if(f1==NULL)
        throw std::runtime_error("File 1 address not set");
    t1 = dynamic_cast<TTree*>(f1->Get("testTree/tree"));
    if(t1==NULL)
        throw std::runtime_error("Tree 1 address not set");

    for(uint32_t t =0; t<f2.size(); t++)
    {
       if(f2.at(t)==NULL)
           throw std::runtime_error("File 2 address not set t=" +t );
       TTree * tre =NULL;
       tre  = dynamic_cast<TTree*>(f2.at(t)->Get("testTree/tree"));
       if(tre==NULL)
       {
           TString  message = TString("Tree 2 address not set file ") + to_string(t)+ "  " + fileSim.at(t);
           throw std::runtime_error(message);
       }
       t2.push_back(tre);

    }

    TObjArray *branchList = t1->GetListOfBranches();
    TObjArray *branchListT2 = t2.at(0)->GetListOfBranches();

    if( branchList->GetEntries() != branchListT2->GetEntries() ) //@MJ@ TODO could be more sophiticated, liek comparing elements
        throw std::runtime_error("Trees have different content");

    vector<string> observables;
    for(int i = 0; i < branchList->GetEntries(); ++i) 
    { 
       if((string) branchList->At(i)->GetName() == "nrofevents")
          continue;
       if((string) branchList->At(i)->GetName() == "nroftracks")
          continue;

       observables.push_back(branchList->At(i)->GetName());
            //cout << branchList->At(i)->GetName() << endl; 
    }

    for(uint32_t b=0; b<observables.size(); b++)
    for(std::vector<string>::iterator it = observables.begin() ; it != observables.end(); ++it)
    {
       cout << "observables to be read: " << *it << endl;
       if(*it == "nrofevents" || *it == "nroftracks")
           observables.erase(it);
    }

   if(observables.size() == 0)
       throw std::runtime_error("The vector of observables not filled");

 
   vector< vector<float>* > var;
   vector< vector< vector<float>* > > varT2;
   vector< vector<float> > varTot;
   vector< vector< vector<float> > > varTotT2;
   var.resize(observables.size());
   varTot.resize(observables.size());
   
   varT2.resize(t2.size());
   varTotT2.resize(t2.size());

   uint32_t posSdId = 0;
   uint32_t posSdIdLayer = 0;
   uint32_t puId = 0;


   for(uint32_t v=0;v<var.size();v++)
   {
       if(observables.at(v) == "clustersubdetid")
           posSdId = v; 
       if(observables.at(v) == "clusterlayerwheel")
           posSdIdLayer = v; 
       if(observables.at(v) == "clusterstringringrod" && (  subDet == "TEC" || subDet == "TID") )
       {
           cout << "getting ring now " << endl;
           posSdIdLayer = v; 
       }
       if(observables.at(v) == "PU")
          puId = v; 
       t1->SetBranchAddress(observables.at(v).c_str(), & (var.at(v)) );
       for(uint32_t t=0;t<t2.size();t++)
       {
           varT2.at(t). resize(observables.size());
           varTotT2.at(t).resize(observables.size());
       
           t2.at(t)->SetBranchAddress(observables.at(v).c_str(), & (varT2.at(t).at(v)) );
       }
   }
   cout << "data hist size " << var.size() << " mc hist size " << varT2.at(0).size() << endl;
   //data always first
    

   uint32_t evCount=0;
   
   //cout << "in here a" << endl;
   Int_t nentries = (Int_t)t1->GetEntries();
   vector<Int_t> nentriesT2;
   for(uint32_t tr=0; tr<t2.size(); tr++)
   {
    nentriesT2.push_back( (Int_t)t2.at(tr)->GetEntries() );
   }
   ///fill variables from tree 1
   for (Int_t e=0; e<nentries; e++) 
   {
       t1->GetEntry(e);

      // float PU = var.at(puId).at(0);
       //if(PU>=5)
         //  continue;

       evCount++;

   //cout << "in here b" << endl;
       for(uint32_t j=0; j<var.size();j++)
       {
           //cout << "variable " << j << " address " << & (var.at(j)) << " size " << var.at(j)->size() << endl; 
          
           uint32_t up = var.at(posSdId)->size() < var.at(j)->size() ? var.at(posSdId)->size() :var.at(j)->size();
           for(uint32_t k=0; k<up;k++)
           {
               if(observables.at(j) == "clusternumber")
                   varTot.at(j).push_back(var.at(j)->at(k));

               if(var.at(posSdId)->at(k) == sdId || sdId==0 )
               {
                   if( (var.at(posSdIdLayer)->at(k)>=layerD && var.at(posSdIdLayer)->at(k)<=layerU) || (layerD==0 && layerU==0)) //@MJ@ TODO temporaray solution!!!!
                   {
       //                cout << "layer "
                       varTot.at(j).push_back(var.at(j)->at(k));
                   }
               }
   //cout << "in here d" << endl;
           }
       }

   }

   //fill variables from tree 2
   for(uint32_t t=0;t<t2.size();t++)
   {
       for (Int_t e=0; e<nentriesT2.at(t); e++) 
       {
	       t2.at(t)->GetEntry(e);

	       for(uint32_t j=0; j<varT2.at(t).size();j++)
	       {
	   //cout << "in here e" << endl;
		   
		   uint32_t up = varT2.at(t).at(posSdId)->size() < varT2.at(t).at(j)->size() ? varT2.at(t).at(posSdId)->size() :varT2.at(t).at(j)->size();
		   for(uint32_t k=0; k<up;k++)
		   {
		       if(observables.at(j) == "clusternumber")
			   varTotT2.at(t).at(j).push_back(varT2.at(t).at(j)->at(k));

		       if(varT2.at(t).at(posSdId)->at(k) == sdId || sdId==0 )
		       {
                           if( (varT2.at(t).at(posSdIdLayer)->at(k)>=layerD && varT2.at(t).at(posSdIdLayer)->at(k)<=layerU) || (layerD==0 && layerU==0) ) //@MJ@ TODO temporaray solution!!!!
			       varTotT2.at(t).at(j).push_back(varT2.at(t).at(j)->at(k));
		       }
	   //cout << "in here f" << endl;
		   }
	       }

        }

   }

   cout << "in here g" << endl;
   vector<TH1F*> hists;
   vector< vector<TH1F*> > histsT2;
   //cout << "in here h" << endl;
   hists.resize(varTot.size());
   histsT2.resize(t2.size());
   vector<int> hcolors = {632, 602, 618, 922, 434,  824, 634, 419, 594, 892  };
   //if(hists.size() != histsT2.at(0).size())
   //    throw std::runtime_error("The histogras do not have same size, something went terribly wrong!");

   for(uint32_t h=0; h<varTot.size(); h++) //@MJ@ TODO in case of empty vector do something!!!
   {
       cout << "in here back" << endl;
       if(varTot.at(h).size()==0) //@MJ@ TODO do it better
       {
           cout << "continuing 1 " << endl;
           continue;
       }
       if(varTotT2.at(0).at(h).size()==0) //@MJ@ TODO do it better
       {
           cout << "continuing 2 " << endl;
           continue;
       }

       sort(varTot.at(h).begin(), varTot.at(h).end());
       for(uint32_t t=0;t<t2.size();t++)
       {
           sort(varTotT2.at(t).at(h).begin(), varTotT2.at(t).at(h).end());
       }

    //cout << "in here 1"  << endl;
       float start = varTot.at(h).at(0) < varTotT2.at(0).at(h).at(0) ? varTot.at(h).at(0) : varTotT2.at(0).at(h).at(0);
    //cout << "in here 1.1"  << endl;
       float size1 = varTot.at(h).size() -1;
    //cout << "in here 1.2"  << endl;
       float size2 = varTotT2.at(0).at(h).size() -1;
    //cout << "in here 1.3"  << endl;
       float end = varTot.at(h).at(size1) > varTotT2.at(0).at(h).at(size2) ? varTot.at(h).at(size1) : varTotT2.at(0).at(h).at(size2);
    //cout << "in here 1.4"  << endl;
    //
       TLegend *leg;
       if(nfile< 4)
       {
           leg = new TLegend(0.6,0.7, 0.90 , 0.90);
       }
       else
       {
           if(qt=="XT" || qt=="LA")
                leg = new TLegend(0.55,0.68, 1 , 0.93);
           else
                leg = new TLegend(0.6,0.68, 0.95 , 0.93);
           leg->SetBorderSize(0);
           leg->SetFillStyle(0);
           leg->SetTextFont(42);
       }
       float nbins=200;
       string histname = observables.at(h);
       if(observables.at(h) == "clusterchargeRescaled")
       {
           nbins = 30;
           start = 1000;
           end = 8000;
           histname = "cluster charge over path [ADC/cm]";
       }
       if(observables.at(h) == "clusterwidth")
       {
           nbins = 7;
           //nbins = 6;
           start = 1;
           end = 8;
           //end = 7;
           histname = "cluster width [strip]";
       }
       if(observables.at(h) == "clusterseedchargeRescaled")
       {
           nbins = 30;
           start = 500;
           end = 6000;
           histname = "cluster seed charge over path [ADC/cm]";
       }
       if(observables.at(h) == "clusterseednoise")
       {
           nbins = 20;
           start = 5;
           end = 8;
           histname = "cluster seed noise [ADC]";
       }
 
       hists.at(h) = new TH1F(observables.at(h).c_str(), observables.at(h).c_str(), nbins, start, end );
       //hists.at(h) = new TH1F(observables.at(h).c_str(), observables.at(h).c_str(), 100, start, 15 );
       //hists.at(h) = new TH1F(observables.at(h).c_str(), observables.at(h).c_str(), 10, 0, 10 );
    //cout << "in here 1.5"  << endl;
       
       for(uint32_t t=0;t<t2.size();t++)
       {
           histsT2.at(t).resize(varTotT2.at(t).size());
           histsT2.at(t).at(h) = new TH1F((observables.at(h)+"T2").c_str(), (observables.at(h)+"T2").c_str(), nbins, start, end );
           //histsT2.at(t).at(h) = new TH1F((observables.at(h)+"T2").c_str(), (observables.at(h)+"T2").c_str(), 100, start, 15 );
           //histsT2.at(t).at(h) = new TH1F((observables.at(h)+"T2").c_str(), (observables.at(h)+"T2").c_str(), 10, 0, 10 );
       }

    cout << "in here 2"  << endl;
       for(uint32_t m = 0; m<varTot.at(h).size(); m++)
       {
           hists.at(h)->Fill(varTot.at(h).at(m));
       }
    cout << "in here 3"  << endl;
       for(uint32_t t=0;t<t2.size();t++)
       {
           for(uint32_t m = 0; m<varTotT2.at(t).at(h).size(); m++)
           {
               histsT2.at(t).at(h)->Fill(varTotT2.at(t).at(h).at(m));
           }
       }
    cout << "in here 4"  << endl;
       TCanvas c(observables.at(h).c_str(),observables.at(h).c_str());
       TPad pad1(("pad1"+observables.at(h)).c_str(), "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad2(("pad2"+observables.at(h)).c_str(), "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad1.Draw();
       pad2.Draw();

       pad1.cd();
 
    //cout << "in here 5"  << endl;

       //hists.at(h)->SetLineColor(kBlack);
       hists.at(h)->SetMarkerStyle(kFullCircle);
       hists.at(h)->SetMarkerColor(kBlack);
       if(nfile>3 && qt!="XT" && qt!="Ee"  && qt!="eADC")
       {
           hists.at(h)->SetMarkerColor(kWhite);
           hists.at(h)->SetMarkerStyle(1);
       }
       hists.at(h)->GetXaxis()->SetTitle(histname.c_str());
       hists.at(h)->GetYaxis()->SetTitle("#clusters");
       //hists.at(h)->GetYaxis()->SetTitle("a.u.");
       float maxm = hists.at(h)->GetMaximum();
       hists.at(h)->SetMaximum(1.5*maxm);
       if(observables.at(h) == "clusterseedchargeRescaled" && ( qt== "eADC" || qt=="Ee") )
           hists.at(h)->SetMaximum(1.7*maxm);
       hists.at(h)->SetTitle("");
       if(nfile<4 || qt=="XT" || qt=="Ee"|| qt=="eADC")
           leg->AddEntry(hists.at(h), "data", "p");
       hists.at(h)->Draw("P");
       TLatex text(0.2,0.85, label.c_str());  
       //TLatex text(0.2,0.2, "test");  
       text.SetNDC(kTRUE);
       //hists.at(h)->Draw("*H");
       text.Draw("same");
       //hists.at(h)->DrawNormalized("P");

       double n = hists.at(h)->Integral();
       //cout << "norm 1 " << hists.at(h)->GetNormFactor() << " netries " << n << end;
       //double n = 80654/5948;
       double nMC = 0;
       uint32_t o=0; 
       for(uint32_t t=0;t<t2.size();t++)
       {
           //histsT2.at(t).at(h)->SetLineColor(2+(2*t));
           //if(2+(t)+o == 5 || 2+(t)+o == 7 || 2+(t)+o == 10  )
           //    o++;
           histsT2.at(t).at(h)->SetLineColor(hcolors.at(t));
           histsT2.at(t).at(h)->SetMarkerStyle(1);
           cout << "hist nr " << t << " color " << hcolors.at(t) << endl;
           TString qt2= qt;
           if(t==0)
              qt2+= " default =";
           if(qt=="delta" || qt=="mu")
               leg->AddEntry(histsT2.at(t).at(h),"#"+qt2+LE.at(t), "l");
           else if(qt=="XT" && nfile<4)
               leg->AddEntry(histsT2.at(t).at(h),qt+" "+LE.at(t), "l");
           else if(qt=="LA" && t>0)
               leg->AddEntry(histsT2.at(t).at(h), qt2+LE.at(t)+"#sigma", "l");
           else
           leg->AddEntry(histsT2.at(t).at(h), qt2+LE.at(t), "l");
           //leg.AddEntry(histsT2.at(t).at(h), "simulation", "l");
       /*    if(norm == "yes" && t==0)
           {
               histsT2.at(t).at(h)->DrawNormalized("hist e", n);
           }*/
           nMC=histsT2.at(t).at(h)->Integral();
           cout << "data norm " << n << "mc norm " << nMC << endl;
           if(norm == "yes")
           {
              //histsT2.at(t).at(h)->DrawNormalized("same hist e");
               histsT2.at(t).at(h)->Scale(n/nMC);
               histsT2.at(t).at(h)->Draw("same hist e");
           }
           else
               histsT2.at(t).at(h)->Draw("same hist e");
  
           leg->Draw();
           cout << "hist " << observables.at(h) << " mean 1 " << hists.at(h)->GetMean() << "  mean2 " <<  histsT2.at(t).at(h)->GetMean()<< " mean 1 err " << hists.at(h)->GetMeanError() << "  mean2 err " <<  histsT2.at(t).at(h)->GetMeanError() << endl;
 
       }
   //cout << "in here 6"  << endl;
       pad2.cd();
       vector<TH1F*> histD;
       histD.resize(t2.size());
       vector<double> n2;
       n2.resize(t2.size());
       //uint32_t o2=20;
       for(uint32_t t=0;t<t2.size();t++)
       {
           if(nfile>3 && qt!="XT" && qt!="Ee"&& qt!="eADC")
               histD.at(t)  = (TH1F*) histsT2.at(0).at(h)->Clone() ; //@MJ@ TODO for all root files
           else
               histD.at(t)  = (TH1F*) hists.at(h)->Clone() ; //@MJ@ TODO for all root files
           //n2.at(t) = histsT2.at(t).at(h)->Integral();
           //histsT2.at(t).at(h)->Scale(n/n2.at(t));
           histD.at(t)->Divide(histsT2.at(t).at(h));
           histD.at(t)->GetXaxis()->SetTitle("");
           histD.at(t)->GetYaxis()->SetTitle("");
           histD.at(t)->GetYaxis()->SetLabelSize(0.12);
           histD.at(t)->GetYaxis()->SetNdivisions(505);
           histD.at(t)->GetXaxis()->SetLabelSize(0);
           //histD.at(t)->SetLineColor(2+(2*t));
           //if(2+(t)+o2 == 5 || 2+(t)+o2 == 7 || 2+(t)+o2 == 10  )
           //    o2++;
           histD.at(t)->SetLineColor(hcolors.at(t));
           histD.at(t)->SetMaximum(2);
           histD.at(t)->SetMinimum(0);
           histD.at(t)->SetTitle("");
           histD.at(t)->SetMarkerStyle(1);
           histD.at(t)->ResetAttMarker();
           if(t==0)
               histD.at(t)->Draw("hist e");
           else
               histD.at(t)->Draw("same hist e");
       }
       cout << "hist " << h << " drawn" << endl; 

       c.Update();

       string specialC = "";
       if(dir == "tuningMeasured")
           specialC ="m";
       c.SaveAs(("output/"+(string)dir+"/"+observables.at(h) + (string)subDet + "l" + (string)slayerD+"to" +(string)slayerU+(string)qt+specialC+".root").c_str());
       c.SaveAs(("output/"+(string)dir+"/"+observables.at(h) + (string)subDet +"l" + (string)slayerD+"to" +(string)slayerU+(string)qt+specialC+ ".eps").c_str());
       //delete histD; //do i need that actually?!
   }

   float const decoValues[651] = 
                           { 0.00924234, 0.00994226, 0.0106394, 0.0115231, 0.0127115
                           , 0.0138952, 0.015074, 0.0162481, 0.0174175, 0.0185821
                           , 0.019742, 0.0208972, 0.0220476, 0.0231934, 0.0243346
                           , 0.0254711, 0.0266029, 0.0281052, 0.0298238, 0.0315354
                           , 0.03324, 0.0349377, 0.0366285, 0.0383124, 0.0399894
                           , 0.0416596, 0.0433229, 0.0449794, 0.0466291, 0.0482721
                           , 0.0499082, 0.0515377, 0.0531605, 0.0552102, 0.0574934
                           , 0.0597673, 0.0620319, 0.0642872, 0.0665332, 0.06877
                           , 0.0709976, 0.073216, 0.0754253, 0.0776255, 0.0798165
                           , 0.0819985, 0.0841715, 0.0863354, 0.0884904, 0.0906364
                           , 0.0927736, 0.0956311, 0.0984767, 0.101311, 0.104133
                           , 0.106943, 0.109742, 0.11253, 0.115305, 0.118069
                           , 0.120822, 0.123563, 0.126293, 0.129011, 0.131718
                           , 0.134414, 0.137098, 0.139771, 0.142433, 0.145342
                           , 0.148737, 0.152118, 0.155485, 0.158838, 0.162177
                           , 0.165501, 0.168812, 0.172109, 0.175392, 0.178662
                           , 0.181917, 0.185159, 0.188387, 0.191602, 0.194802
                           , 0.19799, 0.201164, 0.204324, 0.207728, 0.211617
                           , 0.215489, 0.219346, 0.223186, 0.22701, 0.230818
                           , 0.234609, 0.238385, 0.242145, 0.245888, 0.249616
                           , 0.253328, 0.257024, 0.260704, 0.264368, 0.268017
                           , 0.27165, 0.275268, 0.279366, 0.28368, 0.287975
                           , 0.292252, 0.296511, 0.300752, 0.304974, 0.309179
                           , 0.313365, 0.317534, 0.321685, 0.325817, 0.329932
                           , 0.33403, 0.338109, 0.342171, 0.346215, 0.350268
                           , 0.354953, 0.359618, 0.364262, 0.368887, 0.373492
                           , 0.378077, 0.382642, 0.387187, 0.391712, 0.396218
                           , 0.400705, 0.405172, 0.409619, 0.414047, 0.418456
                           , 0.422877, 0.427844, 0.43279, 0.437715, 0.442618
                           , 0.4475, 0.45236, 0.4572, 0.462018, 0.466815
                           , 0.471591, 0.476346, 0.48108, 0.485794, 0.490636
                           , 0.495805, 0.500951, 0.506075, 0.511177, 0.516256
                           , 0.521313, 0.526347, 0.53136, 0.53635, 0.541318
                           , 0.546369, 0.551673, 0.556954, 0.562211, 0.567445
                           , 0.572655, 0.577843, 0.583008, 0.588245, 0.593612
                           , 0.598955, 0.604274, 0.60957, 0.61494, 0.620297
                           , 0.62563, 0.630939, 0.636225, 0.641487, 0.646725
                           , 0.65194, 0.657131, 0.662299, 0.667444, 0.672566
                           , 0.677664, 0.682739, 0.687792, 0.692821, 0.697828
                           , 0.702812, 0.707773, 0.712711, 0.717627, 0.722521
                           , 0.727392, 0.732241, 0.737067, 0.741871, 0.746653
                           , 0.751413, 0.756151, 0.760867, 0.765562, 0.770234
                           , 0.774885, 0.779514, 0.784121, 0.788707, 0.793272
                           , 0.797815, 0.802336, 0.806837, 0.811316, 0.815774
                           , 0.820212, 0.824628, 0.829023, 0.833397, 0.837751
                           , 0.842084, 0.846396, 0.850687, 0.854958, 0.859209
                           , 0.863336, 0.867415, 0.871474, 0.875513, 0.879443
                           , 0.883142, 0.886823, 0.890485, 0.894129, 0.897755
                           , 0.901363, 0.904953, 0.908339, 0.911433, 0.914511
                           , 0.917573, 0.920619, 0.923649, 0.926664, 0.929663
                           , 0.932646, 0.935613, 0.938565, 0.941271, 0.943589
                           , 0.945894, 0.948186, 0.950465, 0.952732, 0.954985
                           , 0.957225, 0.959453, 0.961668, 0.963871, 0.96606
                           , 0.968237, 0.970402, 0.972099, 0.973515, 0.974922
                           , 0.97632, 0.977708, 0.979087, 0.980456, 0.981816
                           , 0.983167, 0.984508, 0.98584, 0.987163, 0.988476
                           , 0.98978, 0.991075, 0.992361, 0.993112, 0.993562
                           , 0.994007, 0.994446, 0.994879, 0.995307, 0.995729
                           , 0.996145, 0.996555, 0.99696, 0.99736, 0.997754
                           , 0.998142, 0.998524, 0.998902, 0.999273, 0.99964
                           , 1, 0.99947, 0.998939, 0.998406, 0.997871
                           , 0.997334, 0.996796, 0.996255, 0.995713, 0.995169
                           , 0.994623, 0.994076, 0.993526, 0.992975, 0.992422
                           , 0.991867, 0.991311, 0.990753, 0.990193, 0.989317
                           , 0.987837, 0.986359, 0.984883, 0.983409, 0.981937
                           , 0.980467, 0.978999, 0.977533, 0.976069, 0.974606
                           , 0.973146, 0.971688, 0.970231, 0.968777, 0.967324
                           , 0.965874, 0.964425, 0.962978, 0.961222, 0.958862
                           , 0.956508, 0.95416, 0.951817, 0.94948, 0.947149
                           , 0.944822, 0.942502, 0.940187, 0.937877, 0.935573
                           , 0.933274, 0.930981, 0.928693, 0.926411, 0.924134
                           , 0.921863, 0.919597, 0.916734, 0.913596, 0.910467
                           , 0.907348, 0.904237, 0.901134, 0.898041, 0.894956
                           , 0.89188, 0.888813, 0.885754, 0.882705, 0.879663
                           , 0.876631, 0.873607, 0.870591, 0.867585, 0.864555
                           , 0.860745, 0.856948, 0.853162, 0.849388, 0.845626
                           , 0.841876, 0.838137, 0.834409, 0.830693, 0.826989
                           , 0.823296, 0.819615, 0.815945, 0.812286, 0.808639
                           , 0.804965, 0.800616, 0.796281, 0.79196, 0.787653
                           , 0.78336, 0.779081, 0.774817, 0.770566, 0.766329
                           , 0.762106, 0.757897, 0.753701, 0.749519, 0.74517
                           , 0.740412, 0.735671, 0.730946, 0.726236, 0.721543
                           , 0.716865, 0.712203, 0.707557, 0.702927, 0.698312
                           , 0.693585, 0.688541, 0.683514, 0.678505, 0.673513
                           , 0.668538, 0.663581, 0.65864, 0.653601, 0.648394
                           , 0.643205, 0.638034, 0.632881, 0.627627, 0.622379
                           , 0.61715, 0.611939, 0.606746, 0.601572, 0.596415
                           , 0.591277, 0.586158, 0.581056, 0.575972, 0.570907
                           , 0.565859, 0.560829, 0.555817, 0.550823, 0.545846
                           , 0.540887, 0.535946, 0.531023, 0.526117, 0.521228
                           , 0.516357, 0.511503, 0.506667, 0.501848, 0.497046
                           , 0.492261, 0.487494, 0.482743, 0.47801, 0.473293
                           , 0.468594, 0.463911, 0.459245, 0.454596, 0.449964
                           , 0.445349, 0.44075, 0.436168, 0.431602, 0.427053
                           , 0.42252, 0.418003, 0.413503, 0.40902, 0.404552
                           , 0.400101, 0.395666, 0.391247, 0.386844, 0.382457
                           , 0.378118, 0.373803, 0.369503, 0.36522, 0.360979
                           , 0.356818, 0.352672, 0.348541, 0.344425, 0.340325
                           , 0.336239, 0.332169, 0.328169, 0.324268, 0.320381
                           , 0.316508, 0.31265, 0.308806, 0.304975, 0.301159
                           , 0.297357, 0.293569, 0.289795, 0.286104, 0.282541
                           , 0.27899, 0.275453, 0.271928, 0.268417, 0.264919
                           , 0.261433, 0.25796, 0.2545, 0.251053, 0.247619
                           , 0.244197, 0.240789, 0.237531, 0.234366, 0.231214
                           , 0.228072, 0.224943, 0.221825, 0.218719, 0.215624
                           , 0.212541, 0.209469, 0.206409, 0.20336, 0.200322
                           , 0.197296, 0.194281, 0.191278, 0.188445, 0.185712
                           , 0.182988, 0.180275, 0.177572, 0.174879, 0.172197
                           , 0.169524, 0.166861, 0.164208, 0.161565, 0.158932
                           , 0.156309, 0.153696, 0.151092, 0.148499, 0.145915
                           , 0.143341, 0.141045, 0.138757, 0.136478, 0.134208
                           , 0.131946, 0.129693, 0.127448, 0.125211, 0.122983
                           , 0.120764, 0.118552, 0.116349, 0.114155, 0.111969
                           , 0.109791, 0.107621, 0.105459, 0.103306, 0.101256
                           , 0.0993974, 0.0975454, 0.0957005, 0.0938625, 0.0920315
                           , 0.0902075, 0.0883903, 0.0865801, 0.0847768, 0.0829803
                           , 0.0811906, 0.0794078, 0.0776318, 0.0758625, 0.0741
                           , 0.0723443, 0.0705953, 0.0688529, 0.067212, 0.0657611
                           , 0.0643156, 0.0628756, 0.0614412, 0.0600122, 0.0585887
                           , 0.0571706, 0.055758, 0.0543508, 0.052949, 0.0515525
                           , 0.0501615, 0.0487758, 0.0473954, 0.0460204, 0.0446506
                           , 0.0432862, 0.041927, 0.0407559, 0.0396748, 0.0385978
                           , 0.037525, 0.0364564, 0.0353918, 0.0343314, 0.033275
                           , 0.0322228, 0.0311746, 0.0301305, 0.0290904, 0.0280544
                           , 0.0270223, 0.0259943, 0.0249703, 0.0239503, 0.0229442
                           , 0.0221806, 0.02142, 0.0206624, 0.0199077, 0.0191559
                           , 0.0184071, 0.0176611, 0.0169181, 0.016178, 0.0154408
                           , 0.0147064, 0.0139749, 0.0132463, 0.0125206, 0.0117976
                           , 0.0110893, 0.0105918, 0.0100963, 0.00960269, 0.00911102
                           , 0.00862127, 0.00813344, 0.00764753, 0.00716353, 0.00668143
                           , 0.00620122 };

    TH1F* deco = new TH1F("deco", "deco", 651, -30, 35.1 );
    for(uint32_t d=0; d<651; d++)
    {
        deco->SetBinContent(d+1, decoValues[d]);
    }

    TCanvas ca("dec", "dec");
    ca.cd();
    deco->GetXaxis()->SetTitle("TOF of reference - TOF of particle [ns]");
    deco->GetYaxis()->SetTitle("fraction of collected charge");
    deco->Draw("HC");
    ca.SaveAs(("output/"+(string)dir+"/decoShape.eps").c_str());
    ca.SaveAs(("output/"+(string)dir+"/decoShape.root").c_str());
    //cout << "in here 7"  << endl;

   return 0;
}
