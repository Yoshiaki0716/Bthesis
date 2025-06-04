#include<iostream>
//Nothing->Onetree.root ManyTape->011703tree.root

void multiplot(TString filename1="1530test3caltree.root",TString filename2="1520test3caltree.root",TString filename3="1510test3caltree.root",
               TString filename4="150test3caltree.root",TString filename5="15-10test3caltree.root",TString filename6="15-20test3caltree.root",
               TString filename7="15-30test3caltree.root",TString filename8="011507tree.root",TString filename9="012302tree.root",
               TString filename10="012301tree.root",TString filename11="012303tree.root",TString filename12="012206tree.root",
               TString filename13="012405tree.root"){
  
    TCanvas*canvas = new TCanvas("canvas", "compare",800,600);
    gStyle->SetOptStat(0); 
    //canvas->SetBorderMode(0);
    
    TFile* file1 = TFile::Open(filename1);
    TTree* tree1 = (TTree*)file1->Get("tree");
    TH1F *hist1 = new TH1F("hist1", "Data Histogram1", 100, -100, 100);
    hist1->SetLineColor(kBlack);
    tree1->Draw("cal>>hist1","","same,HIST");//1個目からsame使えたから関数みたいにして良さそう
    //file1->Close();
    
    TFile* file2 = TFile::Open(filename2);
    TTree* tree2 = (TTree*)file2->Get("tree");
    TH1F *hist2 = new TH1F("hist2", "Data Histogram2", 100, -100, 100);
    hist2->SetLineColor(kRed);
    tree2->Draw("cal>>hist2","","same,HIST");
    //file2->Close();

    TFile* file3 = TFile::Open(filename3);
    TTree* tree3 = (TTree*)file3->Get("tree");
    TH1F *hist3 = new TH1F("hist3", "Data Histogram3", 100, -100, 100);
    //hist3->SetLineColor(kMagenta);
    hist3->SetLineColor(kBlue);
    tree3->Draw("cal>>hist3","","same,HIST");
    //file3->Close();

    TFile* file4 = TFile::Open(filename4);
    TTree* tree4 = (TTree*)file4->Get("tree");
    TH1F *hist4 = new TH1F("hist4", "Data Histogram4", 100, -100, 100);
    hist4->SetLineColor(kGreen);
    tree4->Draw("cal>>hist4","","same,HIST");

    TFile* file5 = TFile::Open(filename5);
    TTree* tree5 = (TTree*)file5->Get("tree");
    TH1F *hist5 = new TH1F("hist5", "Data Histogram5", 100, -100, 100);
    hist5->SetLineColor(kOrange);
    tree5->Draw("cal>>hist5","","same,HIST");
    
    TFile* file6 = TFile::Open(filename6);
    TTree* tree6 = (TTree*)file6->Get("tree");
    TH1F *hist6 = new TH1F("hist6", "Data Histogram6", 100, -100, 100);
    //hist6->SetLineColor(kBlue);
    hist6->SetLineColor(kMagenta);
    //hist6->SetLineStyle(2);
    tree6->Draw("cal>>hist6","","same,HIST");
    
    TFile* file7 = TFile::Open(filename7);
    TTree* tree7 = (TTree*)file7->Get("tree");
    TH1F *hist7 = new TH1F("hist7", "Data Histogram7", 100, -100, 100);
    hist7->SetLineColor(kCyan);
    tree7->Draw("cal>>hist7","","same,HIST");    
 /* 
    TFile* file8 = TFile::Open(filename8);
    TTree* tree8 = (TTree*)file8->Get("tree");
    TH1F *hist8 = new TH1F("hist8", "Data Histogram8", 350, 0, 3500);
    hist8->SetLineColor(26);
    tree8->Draw("Ch1>>hist8","","same,HIST");

    TFile* file9 = TFile::Open(filename9);
    TTree* tree9 = (TTree*)file9->Get("tree");
    TH1F *hist9 = new TH1F("hist9", "Data Histogram9", 350, 0, 3500);
    hist9->SetLineColor(8);
    tree9->Draw("Ch1>>hist9","","same,HIST");
    
    TFile* file10 = TFile::Open(filename10);
    TTree* tree10 = (TTree*)file10->Get("tree");
    TH1F *hist10 = new TH1F("hist10", "Data Histogram10", 350, 0, 3500);
    hist10->SetLineColor(kCyan);
    tree10->Draw("Ch1>>hist10","","same,HIST");

    TFile* file11 = TFile::Open(filename11);
    TTree* tree11 = (TTree*)file11->Get("tree");
    TH1F *hist11 = new TH1F("hist11", "Data Histogram11", 350, 0, 3500);
    hist11->SetLineColor(kCyan);
    hist11->SetLineStyle(2);
    tree11->Draw("Ch1>>hist11","","same,HIST");   

    TFile* file12 = TFile::Open(filename12);
    TTree* tree12 = (TTree*)file12->Get("tree");
    TH1F *hist12 = new TH1F("hist12", "Data Histogram12", 350, 0, 3500);
    hist12->SetLineColor(kMagenta);
    tree12->Draw("Ch1>>hist12","","same,HIST");

    TFile* file13 = TFile::Open(filename13);
    TTree* tree13 = (TTree*)file13->Get("tree");
    TH1F *hist13 = new TH1F("hist13", "Data Histogram13", 350, 0, 3500);
    hist13->SetLineColor(kBlue);
    tree13->Draw("Ch1>>hist13","","same,HIST");
 */   
/*
    hist1->Scale(1/hist1->Integral());
    hist2->Scale(1/hist2->Integral());
    hist3->Scale(1/hist3->Integral());
    hist4->Scale(1/hist4->Integral());
    hist5->Scale(1/hist5->Integral());
    hist6->Scale(1/hist6->Integral());
    hist7->Scale(1/hist7->Integral());
    hist8->Scale(1/hist8->Integral());
    hist9->Scale(1/hist9->Integral());
    hist10->Scale(1/hist10->Integral());
    hist11->Scale(1/hist11->Integral());
    hist12->Scale(1/hist12->Integral());
    hist13->Scale(1/hist13->Integral());*/

    hist1->SetTitle("Asy");
    hist1->GetXaxis()->SetTitle("Asy");//単位
    hist1->GetYaxis()->SetTitle("counts");
    hist1->GetYaxis()->SetTitleOffset(1.5);

    //TLegend *legend = new TLegend(0.5, 0.5, 0.95, 0.95);
    TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9);
    /*legend->AddEntry(hist1, "Ch2", "l");  
    legend->AddEntry(hist2, "Ch3", "l");  
    legend->AddEntry(hist3, "Ch4", "l");
    legend->AddEntry(hist4, "Ch5", "l");
    legend->AddEntry(hist5, "Ch6", "l"); 
    legend->AddEntry(hist6, "Ch7", "l"); */
    
    legend->AddEntry(hist1, "30#circ", "l");  
    legend->AddEntry(hist2, "20#circ", "l");  
    legend->AddEntry(hist3, "10#circ", "l");
    legend->AddEntry(hist4, "0#circ", "l");
    legend->AddEntry(hist5, "-10#circ", "l"); 
    legend->AddEntry(hist6, "-20#circ", "l");  
    legend->AddEntry(hist7, "-30#circ", "l");  
    /*legend->AddEntry(hist8, "WTape", "l");
    legend->AddEntry(hist9, "Al", "l");
    legend->AddEntry(hist10, "FewTape+Al(out)", "l");
    legend->AddEntry(hist11, "FewTape+Al(in)", "l");
    legend->AddEntry(hist12, "FewTape+Spray", "l");
    legend->AddEntry(hist13, "Tape*10", "l");*/
    legend->Draw();

    canvas->Update();
    canvas->SaveAs("2Chasycompare.pdf");

}
