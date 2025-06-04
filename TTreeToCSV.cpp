#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>

void TTreeToCSV() {
    // ROOTファイルを開く
    TFile *file = TFile::Open("AllMLAsytree.root");  // 変換元のROOTファイル名
    
    // TTreeを取得
    TTree *tree = (TTree*)file->Get("tree");  // "tree"というTTreeを取得

    // ブランチを取得
    int Ch1;
    int Ch2;
    int Ch3;
    int Ch4;
    int Ch5;
    int Ch6;
    int Ch7;
    int r;
    int theta;
    int sum;
    float Asy;

    tree->SetBranchAddress("Ch1",&Ch1);
    tree->SetBranchAddress("Ch2",&Ch2);
    tree->SetBranchAddress("Ch3",&Ch3);
    tree->SetBranchAddress("Ch4",&Ch4);
    tree->SetBranchAddress("Ch5",&Ch5);
    tree->SetBranchAddress("Ch6",&Ch6);
    tree->SetBranchAddress("Ch7",&Ch7);
    tree->SetBranchAddress("r",&r);  
    tree->SetBranchAddress("theta",&theta);  
    tree->SetBranchAddress("sum",&sum);
    tree->SetBranchAddress("Asy",&Asy); 
    
       // 出力CSVファイルを開く(あらかじめ作っとく)
    std::ofstream outFile("AllMLAsy.csv");
    if (!outFile.is_open()) {
        std::cerr << "Could not open CSV file!" << std::endl;
        file->Close();
        return;
    }

    // CSVファイルのヘッダーを書き込む
    outFile << "Ch1,Ch2,Ch3,Ch4,Ch5,Ch6,Ch7,r,theta,sum,Asy" << std::endl;  // ここでCSVのヘッダーを書き込む

    // TTreeの全エントリをループ
    int nEntries = tree->GetEntries();
    for (int i = 0; i < nEntries; i++) {
        tree->GetEntry(i);  // i番目のエントリを取得

        // CSVファイルにデータを書き込む
        outFile << Ch1 << "," << Ch2 << "," << Ch3 << "," << Ch4 << "," << Ch5 << "," << Ch6 << "," << Ch7 << "," << r << "," << theta << "," << sum << "," << Asy << std::endl;
    }

    // ファイルを閉じる
    outFile.close();
    file->Close();

    std::cout << "CSV file has been written!" << std::endl;
}

