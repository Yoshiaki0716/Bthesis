#include<iostream>
//TMVAReg内のTestTreeの中身からプロットや平均二乗誤差の計算を行う

void get_rmse(float targettheta){
//GetEntry for rmse thetaごとに分けたい

TFile*inputfile=TFile::Open("TMVAOutput.root");

TDirectoryFile* dir = (TDirectoryFile*)inputfile->Get("dataset_theta");

TTree* tree = (TTree*)dir->Get("TestTree");

float BDT;
float MLP;
float MLP_theta;
float theta;
float S = 0;
int n = 0;

//asin(MLP_theta[0]*0.324126380+0.01894146825)
/*
//tree->SetBranchAddress("BDT", &BDT);
//tree->SetBranchAddress("MLP", &MLP);
tree->SetBranchAddress("MLP_theta", &MLP_theta);
//tree->SetBranchAddress("theta", &theta);
tree->SetBranchAddress("_theta_sin_M_0.01894__D_0.32413", &theta_sin);
    int Entries = tree->GetEntries();  
    for (int i = 0; i < Entries; ++i) {
        tree->GetEntry(i);
        if (theta_sin < -1.55){

        }

        if (theta == targettheta){
        //S += pow((BDT - targettheta), 2);
        //S += pow((MLP - targettheta), 2);
        S += pow((MLP_theta - targettheta), 2);
        n += 1;
        }
    }
    float rmse = sqrt(S/n);

std::cout << "rmse_" << targettheta << "=" << rmse << std::endl;
std::cout << S << "," << n << std::endl;
*/
}


void MLAnalysis(){

TCanvas*canvas = new TCanvas("canvas", "compare",800,600);
gStyle->SetOptStat(0); 

TFile*inputfile=TFile::Open("TMVAOutput.root");

TDirectoryFile* dir = (TDirectoryFile*)inputfile->Get("dataset_theta");

TTree* tree = (TTree*)dir->Get("TestTree");

TH1F *hist1 = new TH1F("hist1", "Data Histogram1", 100, -40, 40);
hist1->SetLineColor(kBlack);
//tree->Draw("MLP>>hist1","theta ==30","same,HIST");
//tree->Draw("BDT>>hist1","theta ==30","same,HIST");
tree->Draw("asin(MLP_theta[0]*0.324126380+0.01894146825)* 180.0 / TMath::Pi()>>hist1","_theta_sin_M_0.01894__D_0.32413>1.4","same,HIST");

TH1F *hist2 = new TH1F("hist2", "Data Histogram2", 100, -40, 40);
hist2->SetLineColor(kRed);
//tree->Draw("MLP>>hist2","theta ==20","same,HIST");
//tree->Draw("BDT>>hist2","theta ==20","same,HIST");
tree->Draw("asin(MLP_theta[0]*0.324126380+0.01894146825)* 180.0 / TMath::Pi()>>hist2","_theta_sin_M_0.01894__D_0.32413<1.1 && _theta_sin_M_0.01894__D_0.32413>0.9","same,HIST");

TH1F *hist3 = new TH1F("hist3", "Data Histogram3", 100, -40, 40);
hist3->SetLineColor(kBlue);
//tree->Draw("MLP>>hist3","theta ==10","same,HIST");
//tree->Draw("BDT>>hist3","theta ==10","same,HIST");
tree->Draw("asin(MLP_theta[0]*0.324126380+0.01894146825)* 180.0 / TMath::Pi()>>hist3","_theta_sin_M_0.01894__D_0.32413>0.4 && _theta_sin_M_0.01894__D_0.32413<0.6","same,HIST");

TH1F *hist4 = new TH1F("hist4", "Data Histogram4", 100, -40, 40);
hist4->SetLineColor(kGreen);
//tree->Draw("MLP>>hist4","theta ==0","same,HIST");
//tree->Draw("BDT>>hist4","theta ==0","same,HIST");
tree->Draw("asin(MLP_theta[0]*0.324126380+0.01894146825)* 180.0 / TMath::Pi()>>hist4","_theta_sin_M_0.01894__D_0.32413>-0.1 && _theta_sin_M_0.01894__D_0.32413<0.0","same,HIST");

TH1F *hist5 = new TH1F("hist5", "Data Histogram5", 100, -40, 40);
hist5->SetLineColor(kOrange);
//tree->Draw("MLP>>hist5","theta ==-10","same,HIST");
//tree->Draw("BDT>>hist5","theta ==-10","same,HIST");
tree->Draw("asin(MLP_theta[0]*0.324126380+0.01894146825)* 180.0 / TMath::Pi()>>hist5","_theta_sin_M_0.01894__D_0.32413>-0.7 && _theta_sin_M_0.01894__D_0.32413<-0.5","same,HIST");

TH1F *hist6 = new TH1F("hist6", "Data Histogram6", 100, -40, 40);
hist6->SetLineColor(kMagenta);
//tree->Draw("MLP>>hist6","theta ==-20","same,HIST");
//tree->Draw("BDT>>hist6","theta ==-20","same,HIST");
tree->Draw("asin(MLP_theta[0]*0.324126380+0.01894146825)* 180.0 / TMath::Pi()>>hist6","_theta_sin_M_0.01894__D_0.32413>-1.2 && _theta_sin_M_0.01894__D_0.32413<-1.0","same,HIST");

TH1F *hist7 = new TH1F("hist7", "Data Histogram7", 100, -40, 40);
hist7->SetLineColor(kCyan);
//tree->Draw("MLP>>hist7","theta ==-30","same,HIST");
//tree->Draw("BDT>>hist7","theta ==-30","same,HIST");
tree->Draw("asin(MLP_theta[0]*0.324126380+0.01894146825)* 180.0 / TMath::Pi()>>hist7","_theta_sin_M_0.01894__D_0.32413<-1.5","same,HIST");

/*
TH1F *hist1 = new TH1F("hist1", "Data Histogram1", 100, 13, 25);
hist1->SetLineColor(kBlack);
//tree->Draw("MLP>>hist1","r ==15","same,HIST");
tree->Draw("BDT>>hist1","r ==15","same,HIST");

TH1F *hist2 = new TH1F("hist2", "Data Histogram2", 100, 13, 25);
hist2->SetLineColor(kRed);
//tree->Draw("MLP>>hist2","r ==20","same,HIST");
tree->Draw("BDT>>hist2","r ==20","same,HIST");

TH1F *hist3 = new TH1F("hist3", "Data Histogram3", 100, 13, 25);
hist3->SetLineColor(kBlue);
//tree->Draw("MLP>>hist3","r ==23","same,HIST");
tree->Draw("BDT>>hist3","r ==23","same,HIST");
*/

hist1->SetTitle("Predicted Theta");
hist1->GetXaxis()->SetTitle("Predicted Theta");//単位
hist1->GetYaxis()->SetTitle("counts");
hist1->GetYaxis()->SetTitleOffset(1.5);

TLegend *legend = new TLegend(0.1, 0.7, 0.3, 0.9);
legend->AddEntry(hist1, "30#circ", "l");  
legend->AddEntry(hist2, "20#circ", "l");  
legend->AddEntry(hist3, "10#circ", "l");
legend->AddEntry(hist4, "0#circ", "l");
legend->AddEntry(hist5, "-10#circ", "l"); 
legend->AddEntry(hist6, "-20#circ", "l"); 
legend->AddEntry(hist7, "-30#circ", "l");
/*
legend->AddEntry(hist1, "r=15mm", "l");  
legend->AddEntry(hist2, "r=20mm", "l");  
legend->AddEntry(hist3, "r=23mm", "l");
*/
legend->Draw();
/*
get_rmse(30.0);
get_rmse(20.0);
get_rmse(10.0);
get_rmse(0.0);
get_rmse(-10.0);
get_rmse(-20.0);
get_rmse(-30.0);
*/
}

