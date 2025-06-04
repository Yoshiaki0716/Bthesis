#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
 
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
 
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/TMVARegGui.h"

void ML() {

    TMVA::Tools::Instance();//初期化？

    TString outfileName( "TMVAReg.root" );
    TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

    TMVA::Factory *factory = new TMVA::Factory( "TMVARegression", outputFile,"!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression" );
 
    TMVA::DataLoader *dataloader=new TMVA::DataLoader("datasetreg");

    dataloader->AddVariable( "Ch2", "Ch2", "", 'F' );
    dataloader->AddVariable( "Ch3", "Ch3", "", 'F' );
    dataloader->AddVariable( "Ch4", "Ch4", "", 'F' );
    //dataloader->AddVariable( "Ch5", "Ch5", "", 'F' );
    dataloader->AddVariable( "Ch6", "Ch6", "", 'F' );
    dataloader->AddVariable( "Ch7", "Ch7", "", 'F' );
    dataloader->AddVariable( "Ch8", "Ch8", "", 'F' );
    dataloader->AddVariable( "Ch9", "Ch9", "", 'F' );
    //dataloader->AddVariable( "Ch10", "Ch10", "", 'F' );
    dataloader->AddVariable( "Ch11", "Ch11", "", 'F' );
    dataloader->AddVariable( "Ch12", "Ch12", "", 'F' );
    dataloader->AddVariable( "Ch13", "Ch13", "", 'F' );
    //dataloader->AddVariable( "AsyLR", "AsyLR", "", 'F' );
//良くわからん
    dataloader->AddSpectator( "spec1:=Ch2*2", "Spectator 1", "", 'F' );
    dataloader->AddSpectator( "spec2:=Ch3*2", "Spectator 2", "", 'F' );
    dataloader->AddSpectator( "spec3:=Ch7*2", "Spectator 3", "", 'F' );
    //dataloader->AddSpectator( "spec4:=AsyLR*2", "Spectator 4", "", 'F' );

    //dataloader->AddTarget("theta");
    dataloader->AddTarget("r");
    //TFile *inputFile = TFile::Open("AllMLAsytree.root");
    //TTree *regTree = (TTree*)inputFile->Get("tree");//tree複数もいける？
    TFile *inputFile1 = TFile::Open("All15tree.root");
    TTree *regTree1 = (TTree*)inputFile1->Get("tree");
    TFile *inputFile2 = TFile::Open("All20tree.root");
    TTree *regTree2 = (TTree*)inputFile2->Get("tree");
    TFile *inputFile3 = TFile::Open("All23tree.root");
    TTree *regTree3 = (TTree*)inputFile3->Get("tree");
    /*TFile *inputFile4 = TFile::Open("150test8tree.root");
    TTree *regTree4 = (TTree*)inputFile4->Get("tree");
    TFile *inputFile5 = TFile::Open("15-10test8tree.root");
    TTree *regTree5 = (TTree*)inputFile5->Get("tree");
    TFile *inputFile6 = TFile::Open("15-20test8tree.root");
    TTree *regTree6 = (TTree*)inputFile6->Get("tree");
    TFile *inputFile7 = TFile::Open("15-30test8tree.root");
    TTree *regTree7 = (TTree*)inputFile7->Get("tree");*/

    Double_t regWeight  = 1.0;//重み？

    //dataloader->AddRegressionTree( regTree, regWeight );//tree
    dataloader->AddRegressionTree( regTree1, regWeight );
    dataloader->AddRegressionTree( regTree2, regWeight );
    dataloader->AddRegressionTree( regTree3, regWeight );
    /*dataloader->AddRegressionTree( regTree4, regWeight );
    dataloader->AddRegressionTree( regTree5, regWeight );
    dataloader->AddRegressionTree( regTree6, regWeight );
    dataloader->AddRegressionTree( regTree7, regWeight );*/

    //各データの重み？ 30度の重み減らしたいかも treeの重みにするとか？
    //dataloader->SetWeightExpression( "var1", "Regression" );

    //データの分割
    TCut mycut = "";
    //TCut mycut = "Ch2>900 && Ch2<1100 && Ch3>830 && Ch3<900 && Ch7>850 && Ch7<950";
    //dataloader->PrepareTrainingAndTestTree( mycut,"nTrain_Regression=37383:nTest_Regression=9346:SplitMode=Random:NormMode=NumEvents:!V" );
    dataloader->PrepareTrainingAndTestTree( mycut,"nTrain_Regression=80000:nTest_Regression=20000:SplitMode=Random:NormMode=NumEvents:!V" );
   
   // If no numbers of events are given, half of the events in the tree are used
   // for training, and the other half for testing:
   // なんもなしだと半々になるらしい
   // dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );

   //機械学習の手法を選択
   factory->BookMethod( dataloader,  TMVA::Types::kBDT, "BDT","!H:!V:NTrees=100:MinNodeSize=1.0%:BoostType=AdaBoostR2:SeparationType=RegressionVariance:nCuts=20:PruneMethod=CostComplexity:PruneStrength=30" );
   //factory->BookMethod( dataloader,  TMVA::Types::kMLP, "MLP", "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=20000:HiddenLayers=N+20:TestRate=6:TrainingMethod=BFGS:Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:ConvergenceTests=15:!UseRegulator" );
 

   factory->TrainAllMethods();

   factory->TestAllMethods();

   factory->EvaluateAllMethods();

   outputFile->Close();

   delete factory;
   delete dataloader;

   if (!gROOT->IsBatch()) TMVA::TMVARegGui( outfileName );
}

//複数の手法をやった時に確かめるやつ？
/*
int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   TMVARegression(methodList);
   return 0;
}*/

