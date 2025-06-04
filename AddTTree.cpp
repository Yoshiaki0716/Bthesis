#include<iostream>

void AddTTree(){
TFile *outputFile = new TFile("All23tree.root", "RECREATE");
TChain*chain = new TChain("tree","MLdata");
/*
TTree *tree1 = (TTree*)TFile::Open("MLr15theta0tree.root")->Get("tree");
TTree *tree2 = (TTree*)TFile::Open("MLr15theta10tree.root")->Get("tree");
TTree *tree3 = (TTree*)TFile::Open("MLr15theta20tree.root")->Get("tree");
TTree *tree4 = (TTree*)TFile::Open("MLr15theta30tree.root")->Get("tree");
TTree *tree5 = (TTree*)TFile::Open("MLr15theta-10tree.root")->Get("tree");
TTree *tree6 = (TTree*)TFile::Open("MLr15theta-20tree.root")->Get("tree");
TTree *tree7 = (TTree*)TFile::Open("MLr15theta-30tree.root")->Get("tree");
*/
chain->Add("230test7MLtree.root");
chain->Add("2310test7MLtree.root");
chain->Add("23-10test7MLtree.root");
/*chain->Add("2030test7MLtree.root");
chain->Add("20-10test7MLtree.root");
chain->Add("20-20test7MLtree.root");
chain->Add("20-30test7MLtree.root");*/

chain->Write(); 
outputFile->Close();

}
