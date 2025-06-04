#include<iostream>

void savehist(){
TFile* file = TFile::Open("OutGAGG4tree.root");
TTree *tree = (TTree*)file->Get("tree");
TH1F*hist = new TH1F("hist","22Na_ADCspectrum",500,4500,6000); 
//TH2F*hist = new TH2F("hist","title",500,800,2500,1000,4500,6000);
//("name","title","bin","min","max")
//hist->GetXaxis()->SetTitle("Energy");
//hist->GetXaxis()->SetTitle("ADC_1");
hist->GetXaxis()->SetTitle("ADC_others");
hist->GetYaxis()->SetTitle("counts");//ADC_others
hist->GetYaxis()->SetTitleOffset(1.5);
hist->SetTitle("ADC_others");


gStyle->SetOptStat(0); 

gStyle->SetCanvasBorderSize(0);

//hist->SetLineColor(kBlue);

//TLegend *legend = new TLegend( 0.8, 0.68, 0.99, 0.78) ; //（）の中は位置の指定（左下の x , y 、右上の x , y ）
//legend->AddEntry( h0, "histogram 0" , "l") ; // AddEntry( pointer , "interpretation" , "option" )
//legend->AddEntry( h1, "histogram 1" , "l") ; // option は　"f"=box, "l"="L"=line, "p"=marker
TCanvas*c1 = new TCanvas("c1", "22Na_Energyspectrum",800,600);
tree->Draw("Ch2+Ch3+Ch4+Ch5+Ch6+Ch7>>hist","Ch1>Ch2&&Ch1>Ch3&&Ch1>Ch4&&Ch1>Ch5&&Ch1>Ch6&&Ch1>Ch7&&Ch2+Ch3+Ch4+Ch5+Ch6+Ch7>4800","colz");//("value","jouken","option")
c1->SaveAs("012701E.png");
}
