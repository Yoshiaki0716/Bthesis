#include<iostream>
#include<cmath>

//ADC値、エネルギー、非対称度、角度をプロットしつつ、のピークの中心と分散を求める

void GetPeak(TString filename = "OutGAGG6tree.root"){
TFile* file = TFile::Open(filename);
    TTree* tree = (TTree*)file->Get("tree");
    double r = 23;
    double theta_in = 10;
    double cal;
    double S = 0;
/*
    tree->SetBranchAddress("cal", &cal);
    int nEntries = tree->GetEntries();  
    for (int i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        S += pow((cal-theta_in),2);
    }

    double dtheta = sqrt(S/nEntries);
*/


    double a = 527.173;
    double b = 71.6203;
    double a_Err = 139.773;
    double b_Err = 19.5293;
    double AsyLR = -0.119;
    double Asigma = 0.075;
   


    //plot用
    
    TCanvas*canvas = new TCanvas("canvas", "spectrum",800,600);//変える必要あるかも
    gStyle->SetOptStat(0);
    

    //TH1F *hist = new TH1F("hist", "Data Histogram", 300, 700, 3500);
    TH1F *hist = new TH1F("hist", "Data Histogram", 300, 9500, 12000);
    //TH1F *hist = new TH1F("hist", "Data Histogram", 400, 0, 2000); 
    //TH1F *hist = new TH1F("hist", "Data Histogram", 100, -100, 100);
    //TH1F *hist = new TH1F("hist", "Data Histogram", 100, -0.4, 0.2);
    //TH1F *hist = new TH1F("hist", "Data Histogram", 100, -0.8, 0.2);
    //TH1F *hist = new TH1F("hist", "Data Histogram", 100, -0.4, 0.4);
    //TH1F *Ehist = new TH1F("Ehist", "Data Histogram", 100, -100, 100);

    //tree->Draw("sum>>hist");
    tree->Draw("sum+Ch1>>hist");
    //tree->Draw("(Ch1+Ch2+Ch3+Ch4+Ch5+Ch6+Ch7-b)/a>>hist","Ch1>Ch2&&Ch1>Ch3&&Ch1>Ch4&&Ch1>Ch5&&Ch1>Ch6&&Ch1>Ch7&&Ch2+Ch3+Ch4+Ch5+Ch6+Ch7>4800");
    //tree->Draw("(Ch2+Ch3+Ch4+Ch5+Ch6+Ch7-b)/a")//これでうまく計算できてるか不安->AdcToEnergyとかでtreeも作る
    //tree->Draw("cal>>hist");
    //tree->Draw("Asyout>>hist");
    //tree->Draw("cal>>hist");

    
    TF1 * Fit1 = new TF1("Fit1","gaus",10810,11050);
    TF1 * Fit2 = new TF1("Fit2","gaus",11300,11500);
    //TF1 * Fit1 = new TF1("Fit1","gaus",-100,100);
    //TF1 * Fit1 = new TF1("Fit1","gaus",450,560);//511近傍
    //TF1 * Fit1 = new TF1("Fit1","gaus",-0.4,0.2);//0.00幾つとか
    //TF1 * Fit1 = new TF1("Fit1","gaus",-0.8,0.2);
    //TF1 * Fit1 = new TF1("Fit1","gaus",-0.2,0.2);

    hist->Fit("Fit1","R");
    hist->Fit("Fit2","R");

    Fit1->Draw("same");
    Fit2->Draw("same");

    
    //hist->SetTitle("22Na ADC_spectrum ");
    //hist->SetTitle("22Na Energy_spectrum ");
    //hist->SetTitle("22Na Energy_spectrum r15 theta0");
    //hist->SetTitle("AsyLR"); 
    hist->SetTitle("theta_cal");
    //hist->GetXaxis()->SetTitle("ADC_Value");//単位
    //hist->GetXaxis()->SetTitle("Energy (keV)");//単位
    //hist->GetXaxis()->SetTitle("AsyLR");
    hist->GetXaxis()->SetTitle("theta_cal(#circ)");//単位3:7じゃない
    hist->GetYaxis()->SetTitle("counts");
    hist->GetYaxis()->SetTitleOffset(1.5);

    canvas->Update();
    

    double peak1 = Fit1->GetParameter(1);
    double sigma1 = Fit1->GetParameter(2);
   //double peak2 = Fit2->GetParameter(1);

    double meanError1 = Fit1->GetParError(1);
    //double meanError2 = Fit2->GetParError(1);
    double sigmaError1 = Fit1->GetParError(2);//エラーを取得
    //double meanError1 = sqrt(pow(a_Err*AsyLR,2)+pow(b_Err,2)) 
    //double sigmaError1 = Asigma * a_Err;

    //double R_E = 2.35*sigma1/peak1;
    //double R_EErr = 2.35*sqrt(pow((sigmaError1/peak1),2)+pow((sigma1*meanError1/pow(peak1,2)),2));

    std::cout << "PEAK1:" << peak1 << "+-" << meanError1 << std::endl;
    std::cout << "SIGMA1:" << sigma1 << "+-" << sigmaError1 << std::endl;
    //std::cout << "PEAK2:" << peak2 << "+-" << meanError2 << std::endl;

    //std::cout << "R:" << R_E << "+-" << R_EErr << std::endl;
   //角度分解能に関する計算
    
/*
    double Delta_theta = peak1-theta_in;
    double Err_theta = sigmaError1+0.6;
    //double Err_theta = sqrt(pow(a_Err*AsyLR,2)+pow(b_Err,2))+0.6
    double sigma_in = (asin(0.932/r))*180.0/M_PI;
    double sigma_Err = 180.0*0.021/(M_PI*sqrt(pow(r,2)-pow(0.932,2)));
    double R = sqrt(pow(sigma1,2)-pow(sigma_in,2));
    double R_Err = sqrt((pow(sigma1,2)*pow(sigmaError1,2))/(pow(sigma1,2)-pow(sigma_in,2))+(pow(sigma_in,2)*pow(sigma_Err,2))/(pow(sigma1,2)-pow(sigma_Err,2)));


    std::cout << "Delta_theta:" << Delta_theta << "+-" << Err_theta << std::endl;
    //std::cout << "Delta_theta':" << dtheta << "+-" << S << std::endl;
    //std::cout << "SIGMA_in:" << sigma_in << "+-" << sigma_Err << std::endl;
    std::cout << "R:" << R << "+-" << R_Err << std::endl;
*/
}