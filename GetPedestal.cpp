#include<iostream>
//ぺデスタルを各チャンネルごとに出す
//各チャンネルをヒストグラムにプロット
//ヒストグラムの780前後をガウシアンで近似
//平均を誤差付きで出す
//canvasに書く？

void GetPedestal(TString filename="pedestal13tree.root"){
    TFile* file = TFile::Open(filename);
    TTree* tree = (TTree*)file->Get("tree");

    TH1F *hist1 = new TH1F("hist1", "Data Histogram", 30, 770, 800);
    TH1F *hist2 = new TH1F("hist2", "Data Histogram", 30, 770, 800);
    TH1F *hist3 = new TH1F("hist3", "Data Histogram", 30, 770, 800);
    TH1F *hist4 = new TH1F("hist4", "Data Histogram", 30, 770, 800);
    TH1F *hist5 = new TH1F("hist5", "Data Histogram", 30, 770, 800);
    TH1F *hist6 = new TH1F("hist6", "Data Histogram", 30, 770, 800);
    TH1F *hist7 = new TH1F("hist7", "Data Histogram", 30, 770, 800);
    TH1F *hist8 = new TH1F("hist8", "Data Histogram", 30, 770, 800);
    TH1F *hist9 = new TH1F("hist9", "Data Histogram", 30, 770, 800);
    TH1F *hist10 = new TH1F("hist10", "Data Histogram", 30, 770, 800);
    TH1F *hist11 = new TH1F("hist11", "Data Histogram", 30, 770, 800);
    TH1F *hist12 = new TH1F("hist12", "Data Histogram", 30, 770, 800);
    TH1F *hist13 = new TH1F("hist13", "Data Histogram", 30, 770, 800);

    //plot用
    
    TCanvas*canvas = new TCanvas("canvas", "pedstal",800,600);
    gStyle->SetOptStat(0);
    

    tree->Draw("Ch1>>hist1");
    tree->Draw("Ch2>>hist2");
    tree->Draw("Ch3>>hist3");
    tree->Draw("Ch4>>hist4");
    tree->Draw("Ch5>>hist5");
    tree->Draw("Ch6>>hist6");
    tree->Draw("Ch7>>hist7");
    tree->Draw("Ch8>>hist8");
    tree->Draw("Ch9>>hist9");
    tree->Draw("Ch10>>hist10");
    tree->Draw("Ch11>>hist11");
    tree->Draw("Ch12>>hist12");
    tree->Draw("Ch13>>hist13");
    
    TF1 * Fit1 = new TF1("Fit1","gaus",770,800);
    TF1 * Fit2 = new TF1("Fit2","gaus",770,800);
    TF1 * Fit3 = new TF1("Fit3","gaus",770,800);
    TF1 * Fit4 = new TF1("Fit4","gaus",770,800);
    TF1 * Fit5 = new TF1("Fit5","gaus",770,800);
    TF1 * Fit6 = new TF1("Fit6","gaus",770,800);
    TF1 * Fit7 = new TF1("Fit7","gaus",770,800);
    TF1 * Fit8 = new TF1("Fit8","gaus",770,800);
    TF1 * Fit9 = new TF1("Fit9","gaus",770,800);
    TF1 * Fit10 = new TF1("Fit10","gaus",770,800);
    TF1 * Fit11 = new TF1("Fit11","gaus",770,800);
    TF1 * Fit12 = new TF1("Fit12","gaus",770,800);
    TF1 * Fit13 = new TF1("Fit13","gaus",770,800);

    hist1->Fit("Fit1","R");
    hist2->Fit("Fit2","R");
    hist3->Fit("Fit3","R");
    hist4->Fit("Fit4","R");
    hist5->Fit("Fit5","R");
    hist6->Fit("Fit6","R");
    hist7->Fit("Fit7","R");
    hist8->Fit("Fit8","R");
    hist9->Fit("Fit9","R");
    hist10->Fit("Fit10","R");
    hist11->Fit("Fit11","R");
    hist12->Fit("Fit12","R");
    hist13->Fit("Fit13","R");
   
    
    hist13->SetTitle("pedestal");
    hist13->GetXaxis()->SetTitle("ADC_Value");//単位
    hist13->GetYaxis()->SetTitle("counts");
    hist13->GetYaxis()->SetTitleOffset(1.5);

    canvas->Update();
    
    //Fit1->Draw("same");


    double peak1 = Fit1->GetParameter(1);
    double peak2 = Fit2->GetParameter(1);
    double peak3 = Fit3->GetParameter(1);
    double peak4 = Fit4->GetParameter(1);
    double peak5 = Fit5->GetParameter(1);
    double peak6 = Fit6->GetParameter(1);
    double peak7 = Fit7->GetParameter(1);
    double peak8 = Fit8->GetParameter(1);
    double peak9 = Fit9->GetParameter(1);
    double peak10 = Fit10->GetParameter(1);
    double peak11 = Fit11->GetParameter(1);
    double peak12 = Fit12->GetParameter(1);
    double peak13 = Fit13->GetParameter(1);

    double meanError1 = Fit1->GetParError(1);
    double meanError2 = Fit2->GetParError(1);
    double meanError3 = Fit3->GetParError(1);
    double meanError4 = Fit4->GetParError(1);
    double meanError5 = Fit5->GetParError(1);
    double meanError6 = Fit6->GetParError(1);
    double meanError7 = Fit7->GetParError(1);
    double meanError8 = Fit8->GetParError(1);
    double meanError9 = Fit9->GetParError(1);
    double meanError10 = Fit10->GetParError(1);
    double meanError11 = Fit11->GetParError(1);
    double meanError12 = Fit12->GetParError(1);
    double meanError13 = Fit13->GetParError(1);
   

    std::cout << "Pedestal1:" << peak1 << "+-" << meanError1 << std::endl;
    std::cout << "Pedestal2:" << peak2 << "+-" << meanError2 << std::endl;
    std::cout << "Pedestal3:" << peak3 << "+-" << meanError3 << std::endl;
    std::cout << "Pedestal4:" << peak4 << "+-" << meanError4 << std::endl;
    std::cout << "Pedestal5:" << peak5 << "+-" << meanError5 << std::endl;
    std::cout << "Pedestal6:" << peak6 << "+-" << meanError6 << std::endl;
    std::cout << "Pedestal7:" << peak7 << "+-" << meanError7 << std::endl;
    std::cout << "Pedestal8:" << peak8 << "+-" << meanError8 << std::endl;
    std::cout << "Pedestal9:" << peak9 << "+-" << meanError9 << std::endl;
    std::cout << "Pedestal10:" << peak10 << "+-" << meanError10 << std::endl;
    std::cout << "Pedestal11:" << peak11 << "+-" << meanError11 << std::endl;
    std::cout << "Pedestal12:" << peak12 << "+-" << meanError12 << std::endl;
    std::cout << "Pedestal13:" << peak13 << "+-" << meanError13 << std::endl;
}
