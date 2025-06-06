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
 
 
using namespace TMVA;
 
void TMVARegression( TString myMethodList = "" )
{
   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc
 
   // methods to be processed can be given as an argument; use format:
   //
   //     mylinux~> root -l TMVARegression.C\‍(\"myMethod1,myMethod2,myMethod3\"\‍)
   //
 
   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();
 
 
 
   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   //
   // Boosted Decision Trees
   Use["BDT"]             = 0;
   // ---------------------------------------------------------------
 
   std::cout << std::endl;
   std::cout << "==> Start TMVARegression" << std::endl;
 
   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
 
      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i].Data());
 
         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }
 
   // --------------------------------------------------------------------------------------------------
 
   // Here the preparation phase begins
 
   // Create a new root output file
   TString outfileName( "TMVAReg.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
 
   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory will
   // then run the performance analysis for you.
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   TMVA::Factory *factory = new TMVA::Factory( "TMVARegression", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression" );
 
 
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("datasetreg");
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //     (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //     (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";
 
   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
   dataloader->AddVariable( "var1", "Variable 1", "units", 'F' );
   dataloader->AddVariable( "var2", "Variable 2", "units", 'F' );
 
   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables
   dataloader->AddSpectator( "spec1:=var1*2",  "Spectator 1", "units", 'F' );
   dataloader->AddSpectator( "spec2:=var1*3",  "Spectator 2", "units", 'F' );
 
   // Add the variable carrying the regression target
   dataloader->AddTarget( "fvalue" );
 
   // It is also possible to declare additional targets for multi-dimensional regression, ie:
   //     factory->AddTarget( "fvalue2" );
   // BUT: this is currently ONLY implemented for MLP
 
   // Read training and test data (see TMVAClassification for reading ASCII files)
   // load the signal and background event samples from ROOT trees
   TFile *input(nullptr);
   TString fname =  gROOT->GetTutorialDir() + "/machine_learning/data/tmva_reg_example.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVARegression           : Using input file: " << input->GetName() << std::endl;
 
   // Register the regression tree
 
   TTree *regTree = (TTree*)input->Get("TreeR");
 
   // global event weights per tree (see below for setting event-wise weights)
   Double_t regWeight  = 1.0;
 
   // You can add an arbitrary number of regression trees
   dataloader->AddRegressionTree( regTree, regWeight );
 
   // This would set individual event weights (the variables defined in the
   // expression need to exist in the original TTree)
   dataloader->SetWeightExpression( "var1", "Regression" );
 
   // Apply additional cuts on the signal and background samples (can be different)
   TCut mycut = ""; // for example: TCut mycut = "abs(var1)<0.5 && abs(var2-0.5)<1";
 
   // tell the DataLoader to use all remaining events in the trees after training for testing:
   dataloader->PrepareTrainingAndTestTree( mycut,
                                         "nTrain_Regression=1000:nTest_Regression=0:SplitMode=Random:NormMode=NumEvents:!V" );
   //
   //     dataloader->PrepareTrainingAndTestTree( mycut,
   //            "nTrain_Regression=0:nTest_Regression=0:SplitMode=Random:NormMode=NumEvents:!V" );
 
   // If no numbers of events are given, half of the events in the tree are used
   // for training, and the other half for testing:
   //
   //     dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
 
   // Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/old_site/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable
 
   // PDE - RS method
   
   // Boosted Decision Trees
   if (Use["BDT"])
     factory->BookMethod( dataloader,  TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=100:MinNodeSize=1.0%:BoostType=AdaBoostR2:SeparationType=RegressionVariance:nCuts=20:PruneMethod=CostComplexity:PruneStrength=30" );
 
   // Now you can tell the factory to train, test, and evaluate the MVAs
 
   // Train MVAs using the set of training events
   factory->TrainAllMethods();
 
   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();
 
   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();
 
   // --------------------------------------------------------------
 
   // Save the output
   outputFile->Close();
 
   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVARegression is done!" << std::endl;
 
   delete factory;
   delete dataloader;
 
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVARegGui( outfileName );
}
 
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
}