
//*********************************************************************//
//                                                                     //
//    Script to check the Left HRS timing for S0 and S2                //
//                                                                     //
//                                                                     //
//    Author Tong Su ---------Aug 2017                                 //
//                                                                     //
//                                                                     //
//                                                                     //
//*********************************************************************//





#include "TTree.h"
#include "TROOT.h"
#include "TStyle.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "TH1.h"
#include "TChain.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TSystem.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TH2.h"
#include "TLine.h"
#include "TEllipse.h"
#include "TCut.h"
#include "TProfile.h"

void Check_L_Time()

{
    gROOT->SetStyle("Plain");
    gStyle->SetPaperSize(TStyle::kUSLetter);
    gStyle->SetPaperSize(18,22);
    gStyle->SetOptFit(1111);
    gStyle->SetPalette(1);
    gStyle->SetNdivisions(505);
    
    gStyle->SetCanvasColor(10);
    gStyle->SetPadTopMargin(.05);
    gStyle->SetPadLeftMargin(.15);
    gStyle->SetPadRightMargin(.1);
    gStyle->SetPadBottomMargin(.15);
    gStyle->SetTitleYOffset(1.3);
    gStyle->SetLabelFont(42,"X");
    gStyle->SetLabelFont(42,"Y");
    
    gStyle->SetLineStyleString(1,"[]");
    gStyle->SetLineStyleString(2,"[30 10]");
    gStyle->SetLineStyleString(3,"[4 8]");
    gStyle->SetLineStyleString(4,"[15 12 4 12]");
    gStyle->SetLineStyleString(5,"[15 15]");
    gStyle->SetLineStyleString(6,"[15 12 4 12 4 12]");
    gStyle->SetLabelSize(0.045,"X");
    gStyle->SetLabelSize(0.045,"Y");
    gStyle->SetNdivisions(505,"Y");
    gStyle->SetOptDate(0);
    gStyle->SetDateY(.98);
    gStyle->SetStripDecimals(kFALSE);
    gStyle->SetOptTitle(0);
    gStyle->SetTitleFont();
    gStyle->SetTitleFontSize(20);
    gStyle->SetOptStat(0);

    
    TChain * t = new TChain("T");
    Int_t run_no;
    cout<<"please enter a run rumber:"<<endl;
    cin>>run_no;
    t->Add(Form("/chafs1/work1/tritium/Rootfiles/tritium_%d*.root",run_no));
    
     TH2F *S2_Pad =new TH2F("S2_Pad","S2_Pad",16,-0.5,15.5,400,-2,2);
     S2_Pad->GetYaxis()->SetTitle("x_s2[m]");
     S2_Pad->GetXaxis()->SetTitle("Pad No");
     S2_Pad->GetYaxis()->CenterTitle();
     S2_Pad->GetXaxis()->CenterTitle();
    
    
    TH2F *S0_Pad =new TH2F("S0_Pad","S0_trx VS S2_Pad ",16,-0.5,15.5,400,-2,2);
    S0_Pad->GetYaxis()->SetTitle("x_s0[m]");
    S0_Pad->GetXaxis()->SetTitle("Pad No for S2");
    S0_Pad->GetYaxis()->CenterTitle();
    S0_Pad->GetXaxis()->CenterTitle();
    
    
     TH2F *S2_rt_Time[16];
     TH2F *S2_lt_Time[16];
     TH2F *S0_rt_Time[16];
     TH2F *S0_lt_Time[16];
     TH2F *S0_coinc_Time[16];
     TH2F *S2_coinc_Time[16];
     TH2F *S0_Time_Diff[16];
     TH2F *S0_RT_CHECK[16];
     TH2F *S2_RT_CHECK[16];
    
    
    
     for(Int_t i=0;i<16;i++)
        
     {S2_rt_Time[i]=new TH2F(Form("S2_rt_Time[%d]",i),Form("S2_rt VS S2_try for paddle %d",i+1),200,-1,1,200,1650,1850);
      S2_rt_Time[i]->GetXaxis()->SetTitle("y_s2[m]");
      S2_rt_Time[i]->GetYaxis()->SetTitle(Form("S2_rt TDC for paddle %d",i+1));
      S2_rt_Time[i]->GetXaxis()->CenterTitle();
      S2_rt_Time[i]->GetYaxis()->CenterTitle();
         
      S2_lt_Time[i]=new TH2F(Form("S2_lt_Time[%d]",i),Form("S2_lt VS S2_try for paddle %d",i+1),200,-1,1,200,1700,1900);
      S2_lt_Time[i]->GetXaxis()->SetTitle("y_s2[m]");
      S2_lt_Time[i]->GetYaxis()->SetTitle(Form("S2_lt TDC for paddle %d",i+1));
      S2_lt_Time[i]->GetXaxis()->CenterTitle();
      S2_lt_Time[i]->GetYaxis()->CenterTitle();
         
      S0_rt_Time[i]=new TH2F(Form("S0_rt_Time[%d]",i),Form("S0_rt VS S0_trx for paddle %d",i+1),200,-1,1,400,1400,1800);
      S0_rt_Time[i]->GetXaxis()->SetTitle("x_s0[m]");
      S0_rt_Time[i]->GetYaxis()->SetTitle(Form("S0_rt TDC for paddle %d",i+1));
      S0_rt_Time[i]->GetXaxis()->CenterTitle();
      S0_rt_Time[i]->GetYaxis()->CenterTitle();
         
      S0_lt_Time[i]=new TH2F(Form("S0_lt_Time[%d]",i),Form("S0_lt VS S0_trx for paddle %d",i+1),200,-1,1,200,1600,1800);
      S0_lt_Time[i]->GetXaxis()->SetTitle("x_s0[m]");
      S0_lt_Time[i]->GetYaxis()->SetTitle(Form("S0_lt TDC for paddle %d",i+1));
      S0_lt_Time[i]->GetXaxis()->CenterTitle();
      S0_lt_Time[i]->GetYaxis()->CenterTitle();
         
      S2_coinc_Time[i]=new TH2F(Form("S2_coinc_Time[%d]",i),Form("S2_coinc VS S2_try for paddle %d",i+1),200,-1,1,200,1600,1800);
      S2_coinc_Time[i]->GetXaxis()->SetTitle("y_s2[m]");
      S2_coinc_Time[i]->GetYaxis()->SetTitle(Form("S2_coinc TDC for paddle %d",i+1));
      S2_coinc_Time[i]->GetXaxis()->CenterTitle();
      S2_coinc_Time[i]->GetYaxis()->CenterTitle();
        
      S0_coinc_Time[i]=new TH2F(Form("S0_coinc_Time[%d]",i),Form("S0_coinc VS S0_trx for paddle %d",i+1),200,-1,1,200,1500,1700);
      S0_coinc_Time[i]->GetXaxis()->SetTitle("x_s0[m]");
      S0_coinc_Time[i]->GetYaxis()->SetTitle(Form("S0_coinc TDC for paddle %d",i+1));
      S0_coinc_Time[i]->GetXaxis()->CenterTitle();
      S0_coinc_Time[i]->GetYaxis()->CenterTitle();
     
         
      S0_Time_Diff[i]=new TH2F(Form("S0_Time_Diff[%d]",i),Form("S0_Diff VS S0_trx for paddle %d",i+1),200,-1,1,500,-250,250);
      S0_Time_Diff[i]->GetXaxis()->SetTitle("x_s0[m]");
      S0_Time_Diff[i]->GetYaxis()->SetTitle(Form("S0_Diff TDC for paddle %d",i+1));
      S0_Time_Diff[i]->GetXaxis()->CenterTitle();
      S0_Time_Diff[i]->GetYaxis()->CenterTitle();
         
     
     }
    
    
    //Define Variables
    Double_t L_tr_n,L_cer_asum_c,L_ps_e,L_sh_e;
    Double_t L_tr_p[100],L_s2_try[100];
    Double_t L_s2_lt[16],L_s2_rt[16];
    Double_t L_s2_nthit;
    Double_t L_s2_t_pads[16];
    Double_t evtypebits;
    Double_t L_s0_trpath[100],L_s2_trpath[100];
    Double_t L_s0_lt[10],L_s0_rt[10];
    Double_t L_s0_nthit;
    Double_t L_s0_trx[100],L_s0_try[100];
    Double_t L_s0_ladc;
    Double_t L_s0_radc;
    Double_t L_tr_beta[100];
    Double_t L_s2_trx[100];
    Double_t s0_coinc_time;
    Double_t s2_coinc_time;
    
    
    
    
    //Define Branch Status/Addresses
    
    
    
    t->SetBranchStatus("*",0);
    t->SetBranchStatus("L.tr.n",1);
    t->SetBranchStatus("L.tr.p",1);
    t->SetBranchStatus("L.cer.asum_c",1);
    t->SetBranchStatus("L.prl1.e",1);
    t->SetBranchStatus("L.prl2.e",1);
    t->SetBranchStatus("L.s2.lt",1);
    t->SetBranchStatus("L.s2.rt",1);
    t->SetBranchStatus("L.s2.try",1);
    t->SetBranchStatus("L.s2.nthit",1);
    t->SetBranchStatus("L.s2.t_pads",1);
    t->SetBranchStatus("L.s0.trpath",1);
    t->SetBranchStatus("L.s2.trpath",1);
    t->SetBranchStatus("L.s0.lt",1);
    t->SetBranchStatus("L.s0.rt",1);
    t->SetBranchStatus("L.s0.nthit",1);
    t->SetBranchStatus("L.s0.la_p",1);
    t->SetBranchStatus("L.s0.ra_p",1);
    t->SetBranchStatus("DL.evtypebits",1);
    t->SetBranchStatus("L.s2.trx",1);
    t->SetBranchStatus("L.tr.beta",1);
    t->SetBranchStatus("L.s0.trx",1);
    t->SetBranchStatus("L.s0.try",1);
    t->SetBranchStatus("L.s0.trx",1);
    t->SetBranchStatus("DL.tS0coinc",1);
    t->SetBranchStatus("DL.tS2coinc",1);
    t->SetBranchStatus("DL.l_raw_T13",1);
    
    
    t->SetBranchAddress("L.tr.n",&L_tr_n);
    t->SetBranchAddress("L.tr.p",L_tr_p);
    t->SetBranchAddress("L.cer.asum_c",&L_cer_asum_c);
    t->SetBranchAddress("L.prl1.e",&L_ps_e);
    t->SetBranchAddress("L.prl2.e",&L_sh_e);
    t->SetBranchAddress("L.s2.lt",L_s2_lt);
    t->SetBranchAddress("L.s2.rt",L_s2_rt);
    t->SetBranchAddress("L.s2.try",L_s2_try);
    t->SetBranchAddress("L.s2.nthit",&L_s2_nthit);
    t->SetBranchAddress("L.s2.t_pads",L_s2_t_pads);
    t->SetBranchAddress("L.s0.trpath",L_s0_trpath);
    t->SetBranchAddress("L.s2.trpath",L_s2_trpath);
    t->SetBranchAddress("L.s0.lt",L_s0_lt);
    t->SetBranchAddress("L.s0.rt",L_s0_rt);
    t->SetBranchAddress("L.s0.trx",L_s0_trx);
    t->SetBranchAddress("L.s0.try",L_s0_try);
    t->SetBranchAddress("L.s0.nthit",&L_s0_nthit);
    t->SetBranchAddress("DL.evtypebits",&evtypebits);
    t->SetBranchAddress("L.s0.la_p",&L_s0_ladc);
    t->SetBranchAddress("L.s0.ra_p",&L_s0_radc);
    t->SetBranchAddress("L.s2.trx",L_s2_trx);
    t->SetBranchAddress("L.tr.beta",L_tr_beta);
    t->SetBranchAddress("DL.tS0coinc",&s0_coinc_time);
    t->SetBranchAddress("DL.tS2coinc",&s2_coinc_time);
    t->SetBranchAddress("DL.l_raw_T13",&s2_coinc_time);
    
    Int_t nentries = t->GetEntries();
    cout<<"Total Number of Events = "<<nentries<<endl;
    //Loop over events
    
    for(Int_t i=0;i<nentries;i++){
        
    //******************print how many events processed for every 100000 events*********//
    if(i%100000==0) cout << " events processed = " << i << endl;
    //**********************************************************************************//
        
    t->GetEntry(i);
    for(Int_t j=0;j<16;j++){
        if(L_tr_n==1&&L_s0_nthit==1&&(int)evtypebits==2&&L_s2_t_pads[0]==j)
            
        {
           
           
            
           S2_Pad->Fill(L_s2_t_pads[0],L_s2_trx[0]);
           S0_Pad->Fill(L_s2_t_pads[0],L_s0_trx[0]);
            S2_lt_Time[j]->Fill(L_s2_try[0],L_s2_lt[j]);
           S2_rt_Time[j]->Fill(L_s2_try[0],L_s2_rt[j]);
           S0_lt_Time[j]->Fill(L_s0_trx[0],L_s0_lt[0]);
           S0_rt_Time[j]->Fill(L_s0_trx[0],L_s0_rt[0]);
           S2_coinc_Time[j]->Fill(L_s2_try[0],s2_coinc_time);
           S0_coinc_Time[j]->Fill(L_s0_trx[0],s0_coinc_time);
           S0_Time_Diff[j]->Fill(L_s0_trx[0],L_s0_lt[0]-L_s0_rt[0]);
           
        
        }
    }
    
}
    TString name1=Form("check_L_time_%d.pdf",run_no);
    
    TString name2=name1+Form("[");
    TString name3=name1+Form("]");
    
    TCanvas *c1[16];
    TCanvas *c2[16];
    TCanvas *c3[16];
    TCanvas *c4[16];
    TCanvas *c5[16];
    TCanvas *c6[16];
    TCanvas *c7[17];
    TCanvas *c8[17];
    TCanvas *c9[17];
    
    TCanvas *cc=new TCanvas("cc","cc",1200,1200);
    
    cc->cd();
    S2_Pad->Draw("COLZ");
    cc->SaveAs(name2);
    cc->SaveAs(name1);

    
    for(Int_t index=0;index<16;index++)
    
    { c1[index]=new TCanvas(Form("c1[%d]",index),Form("c1[%d]",index),1200,1200);
      c2[index]=new TCanvas(Form("c2[%d]",index),Form("c2[%d]",index),1200,1200);
      c3[index]=new TCanvas(Form("c3[%d]",index),Form("c3[%d]",index),1200,1200);
      c4[index]=new TCanvas(Form("c4[%d]",index),Form("c4[%d]",index),1200,1200);
      c5[index]=new TCanvas(Form("c5[%d]",index),Form("c5[%d]",index),1200,1200);
      c6[index]=new TCanvas(Form("c6[%d]",index),Form("c6[%d]",index),1200,1200);
      c7[index]=new TCanvas(Form("c7[%d]",index),Form("c7[%d]",index),1200,1200);
      
        
        
        c1[index]->cd();
        S2_lt_Time[index]->Draw("COLZ");
        c2[index]->cd();
        S2_rt_Time[index]->Draw("COLZ");
        c3[index]->cd();
        S0_lt_Time[index]->Draw("COLZ");
        c4[index]->cd();
        S0_rt_Time[index]->Draw("COLZ");
        c5[index]->cd();
        S2_coinc_Time[index]->Draw("COLZ");
        c6[index]->cd();
        S0_coinc_Time[index]->Draw("COLZ");
   
        c7[index]->cd();
        S0_Time_Diff[index]->Draw("COLZ");
        
        c1[index]->SaveAs(name1);
        c2[index]->SaveAs(name1);
        c3[index]->SaveAs(name1);
        c4[index]->SaveAs(name1);
        c5[index]->SaveAs(name1);
        c6[index]->SaveAs(name1);
        c7[index]->SaveAs(name1);
       
    }
    
    
    
    
    
    TCanvas *cc2=new TCanvas("cc2","cc2",1200,1200);
    
    cc2->cd();
    S0_Pad->Draw("COLZ");
    cc2->SaveAs(name1);
    cc2->SaveAs(name3);
        
    
   // for(Int_t index2=0;index2<16;index2++)
        
    //{cout<< "for paddle "<<index2+1<<": speed of light of s0="<<c_speed[index2]<<"; "<<endl; }
    
    
    

}
