//./overlayDisr etaOneaAsTimeCanTOB2 4 output/combinatonOfHitsOneRun/etaOneaAsTimeTOB2topmuTop.root output/combinatonOfHitsOneRun/etaOneaAsTimeTOB2bottommuTop.root output/combinatonOfHitsOneRun/etaOneaAsTimeTOB2topmuBottom.root output/combinatonOfHitsOneRun/etaOneaAsTimeTOB2bottommuBottom.root  

//./overlayDisr xtZeroCanTOB2 3 output/newdatamorestatsSEED/xtZeroTOB2bottommuBottom.root output/newdatamorestatsSEEDtracker/xtZeroTOB2bottommuBottom.root  output/newdatamorestatsSEEDnottracker/xtZeroTOB2bottommuBottom.root
//
//./overlayDisr xtOneCanTOB2 3 output/newdatamorestatsSEED/xtOneTOB2bottommuBottom.root output/newdatamorestatsSEEDtracker/xtOneTOB2bottommuBottom.root  output/newdatamorestatsSEEDnottracker/xtOneTOB2bottommuBottom.root

//./overlayDisr xtTwoCanTOB2 3 output/newdatamorestatsSEED/xtTwoTOB2bottommuBottom.root output/newdatamorestatsSEEDtracker/xtTwoTOB2bottommuBottom.root  output/newdatamorestatsSEEDnottracker/xtTwoTOB2bottommuBottom.root
#include <fstream>
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

#include "tdrstyle.C"

int main(int argc, char *argv[]){

Modified_tdr_style();

 gStyle->SetOptStat(0);
 gROOT->ForceStyle();
 
 TString hname = argv[1];
 TString nfiless = argv[2];
 int nfiles = nfiless.Atoi();

 TH1::SetDefaultSumw2();
    if(argc != nfiles+3)
        throw std::runtime_error("Bad number of arguments!");
    

    vector<TString> files;
    for(uint32_t a=0; a<nfiles; a++)
    {
        files.push_back(argv[a+3]);
    }


    vector<TFile*> f1;
    f1.resize(nfiles, NULL);
    vector<TCanvas*> c1;
    c1.resize(nfiles, NULL);
    vector<TH1*> h1;
    h1.resize(nfiles, NULL);

    for(uint32_t b=0; b<f1.size(); b++)
    {
        f1.at(b) = TFile::Open(files.at(b)); 
        if(f1.at(b)==NULL)
            throw std::runtime_error("File" + to_string(b+1) + " address not set");
        c1.at(b) = dynamic_cast<TCanvas*>(f1.at(b)->Get(hname));
        if(c1.at(b)==NULL)
	    throw std::runtime_error("canvas " +  to_string(b+1)+" address not set");
        TObject *obj; 
        TIter next(c1.at(b)->GetListOfPrimitives());
        while ((obj=next())) 
        {
            cout << "Reading: " << obj->GetName() << endl;
            if (obj->InheritsFrom("TH1")) 
            {
	        cout << "histo: " << obj->GetName() << endl;
		h1.at(b) = dynamic_cast<TH1F*>(obj);
		if(h1.at(b)==NULL)
		     h1.at(b) = dynamic_cast<TProfile*>(obj);
		if(h1.at(b)==NULL)
		    throw std::runtime_error("histo " +  to_string(b+1)+" address not set");
            }
        }
        cout << "h address " << h1.at(b) << " hist " <<  hname << endl;

       
    }


       TCanvas c(hname+"merged",hname+"merged");
       for(uint32_t d=0; d<h1.size(); d++)
       {
           h1.at(d)->SetLineColor(d+1);
           if( d == 0 )
               h1.at(d)->Draw("hist e");
           else
               h1.at(d)->Draw("hist same e");
       }
       c.SaveAs(((string)hname+  "merged.root").c_str());
       c.SaveAs(((string)hname+  "merged.eps").c_str());


    //cout << "in here 7"  << endl;

   return 0;
}
