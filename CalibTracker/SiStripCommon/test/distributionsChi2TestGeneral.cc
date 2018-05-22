//./distributionsChi2TestGeneral test_shallowTrackAndClusterSeedInfoNoPU2016_dataTest.root test_shallowTrackAndClusterSeedInfo.rootgainOption3ePerADC252Tuned0.805step3.root 252 TOB 1 4 yes CTtuning 

//./distributionsChi2TestGeneral /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_230_0.044999999999999998_0.001step3.rootanalyzer.root /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017Update_230_0.044999999999999998_0.001step3.rootanalyzer.root 230 0.045 0.001 TOB 1 4 yes CTparameters 


//./distributionsChi2TestGeneral /opt/sbg/data/data6/cms/mjansova/CMSSW_10_0_2/src/CalibTracker/SiStripCommon/test/test_shallowTrackAndCluster_ZBData.root  /opt/sbg/scratch1/cms/mjansova/store/tmp/MCtuning/Coll2017_230_0.044999999999999998_0.001step3.rootanalyzer.root  230 0.045 0.001 TOB 1 4 mono CTparameters 

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
#include "TH3F.h"
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


   std::multimap<float,string> fillMap( string fname );
   void writeMap(string fname, std::multimap<float,string> chimap);

int main(int argc, char *argv[]){

 //gStyle->SetOptStat(0);
 //gROOT->ForceStyle();
 TH1::SetDefaultSumw2();
    if(argc != 11)
    {
        cout << "argc " << argc<< endl;
        for(uint32_t a= 0; a<argc; a++)
        {
            cout << a << " argument value " << argv[a] << endl;
        }
        throw std::runtime_error("Bad number of arguments!");
    }
    
    TString file1 = argv[1];
    TString file2 = argv[2];
    TString sePerADC = argv[3];
    TString sx2 = argv[4];
    TString sx3 = argv[5];
    TString subDet = argv[6];
    TString slayerCutDown = argv[7];
    TString slayerCutUp = argv[8];
    string norm = argv[9];
    TString dir = argv[10];

    float ePerADC = sePerADC.Atof();
    float x2 = sx2.Atof();
    float x3 = sx3.Atof();
    float x1 = 1-(2*x2)- (2*x3);
    string sx1= to_string(x1);

    int layerCutDown = slayerCutDown.Atoi();
    int layerCutUp = slayerCutUp.Atoi();

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
       vector<float>* clusterchargeRescaled = 0;
       vector<float>* clusterchargeRescaled2 =0;
       vector<float>* clusterwidth = 0;
       vector<float>* clusterwidth2 = 0;
       vector<float>* clusterlayerwheel = 0;
       vector<float>* clusterlayerwheel2 = 0;
       vector<float>* clusterstereo = 0;
       vector<float>* clusterupper = 0;
       vector<float>* clusterstereo2 = 0;
       vector<float>* clusterside = 0;
       vector<float>* clusterside2 = 0;
       vector<float>* clusterlocalMomZ = 0;
       vector<float>* clusterlocalMomZ2 = 0;
       vector<float>* tsosglobalphi = 0;
       vector<float>* tsosglobalphi2 = 0;
       vector<float>* tsosBdotZ = 0;
       vector<float>* tsosBdotZ2 = 0;
       vector<float>* tsosBdotY = 0;
       vector<float>* tsosBdotY2 = 0;
       vector<float>* tsoslocalpitch = 0;
       vector<float>* tsoslocalpitch2 = 0;

       vector<float>* tsoslocalx = 0;
       vector<float>* tsoslocaly = 0;
       vector<float>* tsosglobalz = 0;
       vector<unsigned int>* clusterdetid = 0;

       vector<float> subpartition;
       vector<float> subpartition2;
       vector<float> subclustercharge;
       vector<float> subclustercharge2;
       vector<float> subclusterchargeRescaled;
       vector<float> subclusterchargeRescaled2;
       vector<float> subclusterwidth;
       vector<float> subclusterwidth2;
       vector<float> subclusterlayerwheel;
       vector<float> subclusterlayerwheel2;
       vector<float> subclusterstereo;
       vector<float> subclusterupper;
       vector<float> subclusterstereo2;
       vector<float> subclusterside;
       vector<float> subclusterside2;
       vector<float> subclusterlocalMomZ;
       vector<float> subclusterlocalMomZ2;
       vector<float> subtsosglobalphi;
       vector<float> subtsosglobalphi2;
       vector<float> subtsosBdotZ;
       vector<float> subtsosBdotZ2;
       vector<float> subtsosBdotY;
       vector<float> subtsosBdotY2;
       vector<float> subtsoslocalpitch;
       vector<float> subtsoslocalpitch2;

       vector<float> subtsoslocalx;
       vector<float> subtsoslocaly;
       vector<float> subtsosglobalz;
       vector<unsigned int> subclusterdetid;

       t1->SetBranchAddress("clustersubdetid",  &partition );
       t1->SetBranchAddress("clustercharge",  &clustercharge );
       t1->SetBranchAddress("clusterchargeRescaled",  &clusterchargeRescaled );
       t1->SetBranchAddress("clusterwidth",  &clusterwidth );
       t1->SetBranchAddress("clusterlayerwheel",  &clusterlayerwheel );
       t1->SetBranchAddress("clusterstereo",  &clusterstereo );
       t1->SetBranchAddress("clusterupper",  &clusterupper );
       t1->SetBranchAddress("clusterside",  &clusterside );
       t1->SetBranchAddress("clusterlocalMomZ",  &clusterlocalMomZ );
       t1->SetBranchAddress("tsosglobalphi",  &tsosglobalphi );
       t1->SetBranchAddress("tsosBdotZ",  &tsosBdotZ );
       t1->SetBranchAddress("tsosBdotY",  &tsosBdotY );
       t1->SetBranchAddress("tsoslocalpitch",  &tsoslocalpitch );


       t1->SetBranchAddress("tsoslocalx",  &tsoslocalx );
       t1->SetBranchAddress("tsoslocaly",  &tsoslocaly );
       t1->SetBranchAddress("tsosglobalz",  &tsosglobalz );
       t1->SetBranchAddress("clusterdetid",  &clusterdetid );


       t2->SetBranchAddress("clustersubdetid",  &partition2 );
       t2->SetBranchAddress("clustercharge",  &clustercharge2 );
       t2->SetBranchAddress("clusterchargeRescaled",  &clusterchargeRescaled2 );
       t2->SetBranchAddress("clusterwidth",  &clusterwidth2 );
       t2->SetBranchAddress("clusterlayerwheel",  &clusterlayerwheel2 );
       t2->SetBranchAddress("clusterstereo",  &clusterstereo2 );
       t2->SetBranchAddress("clusterside",  &clusterside2 );
       t2->SetBranchAddress("clusterlocalMomZ",  &clusterlocalMomZ2 );
       t2->SetBranchAddress("tsosglobalphi",  &tsosglobalphi2 );
       t2->SetBranchAddress("tsosBdotZ",  &tsosBdotZ2 );
       t2->SetBranchAddress("tsosBdotY",  &tsosBdotY2 );
       t2->SetBranchAddress("tsoslocalpitch",  &tsoslocalpitch2 );

   //data always first
    

   uint32_t evCount=0;
   
   cout << "in here a" << endl;
   Int_t nentries = (Int_t)t1->GetEntries();
   Int_t nentriesT2 = (Int_t)t2->GetEntries();
   cout << "entries " << nentries << "enstries 2" << nentriesT2 << endl;

   cout << "in here b" << endl;
   unsigned int selMod = 0;
   uint32_t fillNr = 0;
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
                   subpartition.push_back(partition->at(k));
                   subclustercharge.push_back(clustercharge->at(k));
                   subclusterchargeRescaled.push_back(clusterchargeRescaled->at(k));
                   subclusterwidth.push_back(clusterwidth->at(k));
                   subclusterlayerwheel.push_back(clusterlayerwheel->at(k));
                   subclusterstereo.push_back(clusterstereo->at(k));
                   subclusterupper.push_back(clusterupper->at(k));
                   subclusterside.push_back(clusterside->at(k));
                   subclusterlocalMomZ.push_back(clusterlocalMomZ->at(k));
                   subtsosglobalphi.push_back(tsosglobalphi->at(k));
                   subtsosBdotZ.push_back(tsosBdotZ->at(k));
                   subtsosBdotY.push_back(tsosBdotY->at(k));
                   subtsoslocalpitch.push_back(tsoslocalpitch->at(k));

                   subtsoslocalx.push_back(tsoslocalx->at(k));
                   subtsoslocaly.push_back(tsoslocaly->at(k));
                   subtsosglobalz.push_back(tsosglobalz->at(k));
                   subclusterdetid.push_back(clusterdetid->at(k));

               }
           }

   }

   cout << "selected module " << selMod << endl;

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
                   subpartition2.push_back(partition2->at(k));
                   subclustercharge2.push_back(clustercharge2->at(k));
                   subclusterchargeRescaled2.push_back(clusterchargeRescaled2->at(k));
                   subclusterwidth2.push_back(clusterwidth2->at(k));
                   subclusterlayerwheel2.push_back(clusterlayerwheel2->at(k));
                   subclusterstereo2.push_back(clusterstereo2->at(k));
                   subclusterside2.push_back(clusterside2->at(k));
                   subclusterlocalMomZ2.push_back(clusterlocalMomZ2->at(k));
                   subtsosglobalphi2.push_back(tsosglobalphi2->at(k));
                   subtsosBdotZ2.push_back(tsosBdotZ2->at(k));
                   subtsosBdotY2.push_back(tsosBdotY2->at(k));
                   subtsoslocalpitch2.push_back(tsoslocalpitch2->at(k));
               }
           }
   }



       TH1F* chargeData = new TH1F("chargeForAllWidths", "chargeForAllWidths" , 30, 100, 500 );
       TH1F* chargeMC = new TH1F("chargeForAllWidthsMC", "chargeForAllWidthsMC" , 30, 100, 500 );
       TH1F* widthData = new TH1F("widthAllTo10Data", "widthAllTo10Data" , 6, 1, 7  );
       TH1F* widthMC = new TH1F("widthAllTo10MC", "widthAllTo10MC" ,6, 1, 7 );
       TH1F* chargeRescaledData = new TH1F("chargeForAllWidthsRescaled", "chargeForAllWidthsRescaled" , 30, 2000, 6000 );
       TH1F* chargeRescaledMC = new TH1F("chargeForAllWidthsRescaledMC", "chargeForAllWidthsRescaledMC" , 30, 2000, 6000 );
       TH1F* clusterlocalMomZData = new TH1F("clusterlocalMomZ", "clusterlocalMomZ" , 60, -30, 30 );
       TH1F* clusterlocalMomZMC = new TH1F("clusterlocalMomZMC", "clusterlocalMomZMC" , 60, -30, 30 );
       TH1F* clusterstereoData = new TH1F("clusterstereo", "clusterstereo" , 2, 0, 2 );
       TH1F* clusterstereoMC = new TH1F("clusterstereoMC", "clusterstereoMC" , 2, 0, 2 );
       TH1F* clustersideData = new TH1F("clusterside", "clusterside" , 4, -2, 2 );
       TH1F* clustersideMC = new TH1F("clustersideMC", "clustersideMC" , 4, -2, 2 );
       TH1F* tsosglobalphiData = new TH1F("tsosglobalphi", "tsosglobalphi" , 100, -3.5, 3.5 );
       TH1F* tsosglobalphiMC = new TH1F("tsosglobalphiMC", "tsosglobalphiMC" , 100, -3.5, 3.5 );
       TH1F* tsosBdotZData = new TH1F("tsosBdtoZ", "tsosBdtoZ" , 100, -5, 5 );
       TH1F* tsosBdotZMC = new TH1F("tsosBdtoZMC", "tsosBdtoZMC" , 100, -5, 5 );
       TH1F* tsosBdotYData = new TH1F("tsosBdtoY", "tsosBdtoY" , 100, -5, 5 );
       TH1F* tsosBdotYMC = new TH1F("tsosBdtoYMC", "tsosBdtoYMC" , 100, -5, 5 );
       TH1F* tsoslocalpitchData = new TH1F("tsoslocalpitch", "tsoslocalpitch" , 1000, 0.006, 0.03 );
       TH1F* tsoslocalpitchMC = new TH1F("tsoslocalpitchMC", "tsoslocalpitchMC" , 1000, 0.006, 0.03 );
  

       TH2F* localxAsGlobalzData = new TH2F("localxAsGlobalzData", "localxAsGlobalzData" , 6000, -300, 300, 1200, -6,6 );
       TProfile* globalzAsLocalXData = new TProfile("globalzAsLocalXData", "globalzAsLocalXData" , 20, -6,6 );
       TH1F*  globZData = new TH1F("globZData", "globZData" , 1200, -6,6 );
       TH1F* clusterupperData = new TH1F("clusterupper", "clusterupper" , 4, -2, 2 );

 
       cout << "in here 2"  << endl;
       for(uint32_t m = 0; m<subclusterwidth.size(); m++)
       {
           if(subclusterlayerwheel.at(m) >= layerCutDown && subclusterlayerwheel.at(m) <= layerCutUp)
           {

               if(norm.find("mono")!=std::string::npos && subclusterstereo.at(m) ==  1)
                   continue;
               if(norm.find("stereo")!=std::string::npos && subclusterstereo.at(m) ==  0)
                   continue;
               /*if(subtsosglobalphi.at(m)<0)
                   continue;
               if(subclusterside.at(m)<0)
                   continue;
               //if(subclusterstereo.at(m) ==  1)
               //    continue;*/
               chargeData->Fill(subclustercharge.at(m));
               chargeRescaledData->Fill(subclusterchargeRescaled.at(m));
               widthData->Fill(subclusterwidth.at(m));
               clusterlocalMomZData->Fill(subclusterlocalMomZ.at(m));
               clustersideData->Fill(subclusterside.at(m));
               clusterstereoData->Fill(subclusterstereo.at(m));
               clusterupperData->Fill(subclusterupper.at(m));
               tsosglobalphiData->Fill(subtsosglobalphi.at(m));
               tsosBdotZData->Fill(subtsosBdotZ.at(m));
               tsosBdotYData->Fill(subtsosBdotY.at(m));
               tsoslocalpitchData->Fill(subtsoslocalpitch.at(m));
               if(fillNr == 0)
                    selMod = subclusterdetid.at(m);  
                   

               //if(selMod == subclusterdetid.at(m))
               //{
                    if( subtsoslocaly.at(m) > 3.0 && subtsoslocaly.at(m) < 3.1)
                    {
                       if( subtsosglobalz.at(m) > 80.0 && subtsosglobalz.at(m) < 90.0)
                       {
                       localxAsGlobalzData->Fill( subtsosglobalz.at(m), subtsoslocalx.at(m) );
                       globalzAsLocalXData ->Fill( subtsoslocalx.at(m), subtsosglobalz.at(m) );
                       uint32_t lx = globZData->FindBin(subtsoslocalx.at(m) );
                       globZData->SetBinContent( lx, subtsosglobalz.at(m) );
                       }
                       //cout << "bin " << lx << " content " << subtsosglobalz.at(m) << endl;
                    }
               //}
               fillNr++;
           }
         
       }
   
    cout << "in here 3"  << endl;
       for(uint32_t m = 0; m<subclusterwidth2.size(); m++)
       {
           if(subclusterlayerwheel2.at(m) >=layerCutDown &&  subclusterlayerwheel2.at(m)<= layerCutUp )
           {
               if(norm.find("mono")!=std::string::npos && subclusterstereo2.at(m) ==  1)
                   continue;
               if(norm.find("stereo")!=std::string::npos && subclusterstereo2.at(m) ==  0)
                   continue;
               //if(subclusterstereo2.at(m) ==  0)
               //    continue;
        /*       if(subtsosglobalphi2.at(m)<0)
                      continue;
               if(subclusterside2.at(m)<0)
                   continue;*/
               chargeMC->Fill(subclustercharge2.at(m));
               chargeRescaledMC->Fill(subclusterchargeRescaled2.at(m));
               widthMC->Fill(subclusterwidth2.at(m));
               clusterlocalMomZMC->Fill(subclusterlocalMomZ2.at(m));
               clustersideMC->Fill(subclusterside2.at(m));
               clusterstereoMC->Fill(subclusterstereo2.at(m));
               tsosglobalphiMC->Fill(subtsosglobalphi2.at(m));
               tsosBdotZMC->Fill(subtsosBdotZ2.at(m));
               tsosBdotYMC->Fill(subtsosBdotY2.at(m));
               tsoslocalpitchMC->Fill(subtsoslocalpitch2.at(m));
           }
       }


    cout << "in here 4"  << endl;
       
       float Ndata=  chargeData->Integral();
       float NMC=  chargeMC->Integral();
       float scale = Ndata/NMC;
       chargeMC->Scale(scale);

       float NdataR=  chargeRescaledData->Integral();
       float NMCR=  chargeRescaledMC->Integral();
       float scaleR =  NdataR/NMCR;
       chargeRescaledMC->Scale(scaleR);

       float NdataW=  widthData->Integral();
       float NMCW=  widthMC->Integral();
       float scaleW = NdataW/NMCW;
       widthMC->Scale(scaleW);

       
    //TString subDet = argv[6];
    //TString slayerCutDown = argv[7];
    //TString slayerCutUp = argv[8];

if(norm == "mono" || norm == "stereo" || norm == "all")
{

       std::multimap<float,string> returnedMap = fillMap((string)subDet+"l"+(string)slayerCutDown+"to"+(string)slayerCutUp+ norm+"Width.txt" );
       returnedMap.insert ( std::pair<float,string>( widthData->Chi2Test(widthMC, "UW CHI2/NDF P") , "eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 ) );
       writeMap((string)subDet+"l"+(string)slayerCutDown+"to"+(string)slayerCutUp+norm+"Width.txt",returnedMap  );

       std::multimap<float,string> returnedMap2 = fillMap((string)subDet+"l"+(string)slayerCutDown+"to"+(string)slayerCutUp+norm+"Charge.txt" );
       returnedMap2.insert ( std::pair<float,string>( chargeData->Chi2Test(chargeMC, "UW CHI2/NDF P") , "eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 ) );
       writeMap((string)subDet+"l"+(string)slayerCutDown+"to"+(string)slayerCutUp+norm+"Charge.txt",returnedMap2  );
       
       std::multimap<float,string> returnedMap3 = fillMap((string)subDet+"l"+(string)slayerCutDown+"to"+(string)slayerCutUp+norm+"ChargeRescaled.txt" );
       returnedMap3.insert ( std::pair<float,string>( chargeRescaledData->Chi2Test(chargeRescaledMC, "UW CHI2/NDF P") , "eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 ) );
       writeMap((string)subDet+"l"+(string)slayerCutDown+"to"+(string)slayerCutUp+norm+"ChargeRescaled.txt",returnedMap3  );
   
     cout << "finished " << endl;    
     returnedMap.clear();
     returnedMap2.clear();
     returnedMap3.clear();
       //fill the map
}

/*       TFile *f_chi2ch = new TFile (((string)dir+"chi2charge.root").c_str(), "UPDATE");
       TH3F* chi23Dch = NULL;
       chi23Dch = dynamic_cast<TH3F*>(f_chi2ch->Get("chi23Dch"));
       if(chi23Dch == NULL)
       {
           cout << "new chi2 histogram created " << endl;
           chi23Dch = new TH1F("chi23Dch", "chi23Dch", 1000, 190, 300);
       }


       
       TAxis* xaxis = chi21D->GetXaxis();
       int binx = xaxis->FindBin(ePerADC);

       chi21D->SetBinContent(binx, chargeData->Chi2Test(chargeMC, "UW CHI2/NDF P"));
       chi21D->Write(chi21D->GetName(),TObject::kOverwrite);
       f_chi2->Close();

       TFile *f_Kolmogorov = new TFile (("output/"+(string)dir+"/"+(string)dir+"Kolmogorov.root").c_str(), "UPDATE");
       TH1F* kol1D = NULL;
       kol1D = dynamic_cast<TH1F*>(f_Kolmogorov->Get("kol1D"));
       if(kol1D == NULL)
       {
           cout << "new kol histogram created " << endl;
           kol1D = new TH1F("kol1D", "kol1D", 1000,190,300 );
       }
       kol1D->SetBinContent(binx, chargeData->KolmogorovTest(chargeMC));
       kol1D->Write(kol1D->GetName(),TObject::kOverwrite);
       f_Kolmogorov->Close();

*/
    cout << "in here 5"  << endl;
if(norm == "monop" || norm == "stereop" || norm == "allp")
{
//////////////////////filling
       chargeData->SetMarkerStyle(kFullCircle);
       chargeMC->SetMarkerColor(kBlack);
       chargeRescaledData->SetMarkerStyle(kFullCircle);
       chargeRescaledMC->SetMarkerColor(kBlack);
       widthData->SetMarkerStyle(kFullCircle);
       widthData->SetMarkerColor(kBlack);


       chargeMC->SetTitle("");
       chargeData->SetTitle("");
       chargeRescaledMC->SetTitle("");
       chargeRescaledData->SetTitle("");
       widthData->SetTitle("");


       chargeData->GetXaxis()->SetTitle("cluster charge");
       chargeRescaledData->GetXaxis()->SetTitle("cluster charge rescaled");
       widthData->GetXaxis()->SetTitle("cluster width");

       chargeData->SetMaximum(1.5*  (chargeData->GetMaximum()));
       chargeRescaledData->SetMaximum(1.5*  (chargeRescaledData->GetMaximum()));
       widthData->SetMaximum(1.5*  (widthData->GetMaximum()));

       chargeMC->SetLineColor(kRed);
       chargeRescaledMC->SetLineColor(kRed);
       widthMC->SetLineColor(kRed);



       clusterlocalMomZData->SetMarkerStyle(kFullCircle);
       clusterlocalMomZData->GetXaxis()->SetTitle("local pz");
       clustersideData->SetMarkerStyle(kFullCircle);
       clustersideData->GetXaxis()->SetTitle("module side");
       clusterstereoData->SetMarkerStyle(kFullCircle);
       clusterstereoData->GetXaxis()->SetTitle("module stereo");
       clusterupperData->SetMarkerStyle(kFullCircle);
       clusterupperData->GetXaxis()->SetTitle("upper module");
       clusterlocalMomZMC->SetLineColor(kRed);
       clustersideMC->SetLineColor(kRed);
       clusterstereoMC->SetLineColor(kRed);
       tsosglobalphiData->SetMarkerStyle(kFullCircle);
       tsosglobalphiData->GetXaxis()->SetTitle("global phi");
       tsosglobalphiMC->SetLineColor(kRed);
       tsosBdotZData->SetMarkerStyle(kFullCircle);
       tsosBdotZData->GetXaxis()->SetTitle("B(z)");
       tsosBdotZMC->SetLineColor(kRed);
       tsosBdotYData->SetMarkerStyle(kFullCircle);
       tsosBdotYData->GetXaxis()->SetTitle("B(y)");
       tsosBdotYMC->SetLineColor(kRed);
       tsoslocalpitchData->SetMarkerStyle(kFullCircle);
       tsoslocalpitchData->GetXaxis()->SetTitle("pitch");
       tsoslocalpitchMC->SetLineColor(kRed);


    cout << "in here 6"  << endl;

       TCanvas c1("chargeForAllWidths","chargeForAllWidths");
       TPad pad1("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad2("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad1.Draw();
       pad2.Draw();
       
       pad1.cd();
       chargeData->Draw("P");
       chargeMC->Draw("same"); 
       pad2.cd();
       TH1F* chargeDataClone = (TH1F*) chargeData->Clone();
       chargeDataClone->Divide(chargeMC);
       chargeDataClone->SetMaximum(2);
       chargeDataClone->SetMinimum(0);
       chargeDataClone->Draw("e");

       TCanvas c2("widthForAllWidths","widthForAllWidths");
       TPad pad3("pad3", "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad4("pad4", "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad3.Draw();
       pad4.Draw();
       
       pad3.cd();
       widthData->Draw("P");
       widthMC->Draw("same"); 
       pad4.cd();
       TH1F* widthDataClone = (TH1F*) widthData->Clone();
       widthDataClone->Divide(widthMC);
       widthDataClone->SetMaximum(2);
       widthDataClone->SetMinimum(0);
       widthDataClone->Draw("e");


       TCanvas c3("chargeRescaledForAllWidths","chargeRescaledForAllWidths");
       TPad pad5("pad1", "The pad 80% of the height",0.0,0.2,1.0,1.0);
       TPad pad6("pad2", "The pad 20% of the height",0.0,0.0,1.0,0.2);
       pad5.Draw();
       pad6.Draw();
       
       pad5.cd();
       chargeRescaledData->Draw("P");
       chargeRescaledMC->Draw("same"); 
       pad6.cd();
       TH1F* chargeRescaledDataClone = (TH1F*) chargeRescaledData->Clone();
       chargeRescaledDataClone->Divide(chargeRescaledMC);
       chargeRescaledDataClone->SetMaximum(2);
       chargeRescaledDataClone->SetMinimum(0);
       chargeRescaledDataClone->Draw("e");


       TCanvas d("pz", "pz");
       clusterlocalMomZData->DrawNormalized("");
       clusterlocalMomZMC->DrawNormalized("same");

       TCanvas e("side", "side");
       clustersideData->DrawNormalized("");
       clustersideMC->DrawNormalized("same");

       TCanvas f("stereo", "stereo");
       clusterstereoData->DrawNormalized("");
       clusterstereoMC->DrawNormalized("same");

       TCanvas g("phi", "phi");
       tsosglobalphiData->DrawNormalized("");
       tsosglobalphiMC->DrawNormalized("same");

       TCanvas h("bDotZ", "BdotZ");
       tsosBdotZData->DrawNormalized("");
       tsosBdotZMC->DrawNormalized("same");

       TCanvas i("bDotY", "BdotY");
       tsosBdotYData->DrawNormalized("");
       tsosBdotYMC->DrawNormalized("same");

       TCanvas j("localPitch", "localPitch");
       tsoslocalpitchData->DrawNormalized("");
       tsoslocalpitchMC->DrawNormalized("same");

       TCanvas k("zx", "zx");
       localxAsGlobalzData->Draw("box" );
      
       TCanvas l("xz", "xz");
       globalzAsLocalXData ->Draw(  );

       TCanvas m("upper", "upper");
       clusterupperData->DrawNormalized("");

       TCanvas n("globZ", "globZ");
       globZData->Draw("");

       cout << "correlation factor of local x vs global z" << localxAsGlobalzData->GetCorrelationFactor() << endl ;
       cout << "covariance factor of local x vs global z" << localxAsGlobalzData->GetCovariance() << endl ;

       c1.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 + norm+  "charge.root").c_str());
       c1.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"charge.eps").c_str());

       c2.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 + norm+ "width.root").c_str());
       c2.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 + norm+ "width.eps").c_str());

       c3.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 + norm+ "chargeRescaled.root").c_str());
       c3.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 + norm+ "chargeRescaled.eps").c_str());
       

       d.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"localPz.root").c_str());
       d.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 + norm+ "localPz.eps").c_str());
       e.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"side.root").c_str());
       e.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"side.eps").c_str());
       f.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"stereo.root").c_str());
       f.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"stereo.eps").c_str());
       g.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"tsosglobalphi.root").c_str());
       g.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"tsosglobalphi.eps").c_str());
       h.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"bdotZ.root").c_str());
       h.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"bdotZ.eps").c_str());
       i.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"bdotY.root").c_str());
       i.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"bdotY.eps").c_str());
       j.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"localPitch.root").c_str());
       j.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"localPitch.eps").c_str());
       k.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"localXGlobalZ.root").c_str());
       k.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"localXGlobalZ.eps").c_str());
       l.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"profGlobalZLocx.root").c_str());
       l.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"progGlobalZlocx.eps").c_str());
       m.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"upper.root").c_str());
       m.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"upper.eps").c_str());
       n.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"globZ.root").c_str());
       n.SaveAs(("output/"+(string)dir+"/"+ (string)slayerCutDown+ "lt" +(string)subDet +"mt"+(string)slayerCutUp +"_eToADC_"+ (string)sePerADC  + "_xtalk_"+ (string)sx1 + "_"+ (string)sx2+ "_"+ (string)sx3 +  norm+"globZ.eps").c_str());
      /////////////////////////////////////////////////////

}
     
       delete chargeData; 
       delete chargeMC; 
       delete widthData;
       delete widthMC; 
       delete chargeRescaledData; 
       delete chargeRescaledMC; 

       delete clusterlocalMomZMC;
       delete clustersideMC;
       delete clusterstereoMC;
       delete clusterlocalMomZData;
       delete clustersideData;
       delete clusterstereoData;

       delete tsosglobalphiData;
       delete tsosglobalphiMC;
       delete tsosBdotZData;
       delete tsosBdotZMC;
       delete tsosBdotYData;
       delete tsosBdotYMC;
       delete tsoslocalpitchData;
       delete tsoslocalpitchMC;
       delete localxAsGlobalzData;
       delete globalzAsLocalXData; 
       delete  globZData;
       delete clusterupperData;

return 0;


    cout << "in here 7"  << endl;

}

   std::multimap<float,string> fillMap( string fname )
   {
       std::multimap<float,string> chimap;
       std::ifstream in;
       in.open ( fname);
       if(in.is_open())
       {
           //fill the map
           std::string   myline;
           while(std::getline(in, myline))
           {
               std::vector<string>   mylineData;
               std::stringstream  mylineStream(myline);
               string myvalue;
               while(mylineStream >> myvalue)
               {
                   mylineData.push_back(myvalue);
               }
               if(mylineData.size() == 2)
               {
                  chimap.insert( std::pair<float, string>(stof(mylineData.at(0)), mylineData.at(1)));
               }
            }

           in.close();
       }
       return chimap;
  }

   void writeMap(string fname, std::multimap<float,string> chimap)
   {
       std::ofstream out;
       out.open ( fname , std::ofstream::out | std::ofstream::trunc);
       if(out.is_open())
       {
           //write the map
           for (std::multimap<float,string>::iterator it = chimap.begin(); it!=chimap.end(); ++it)
           {
               out << (*it).first << " " << (*it).second << endl;
           }
           out.close();
       }
       
   }
