#define ML_cxx
#include "ML.h"
#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMVA/Factory.h>
#include <TMVA/DataLoader.h>
#include <TMVA/Tools.h>
#include <TFile.h>
#include <TTree.h>
#include <map>
#include <vector>
#include <cmath>
#include <algorithm>

// Clip the value to within mean ± threshold * stddev
double clip(double value, double mean, double stddev, double threshold = 3.0) {
    double lower = mean - threshold * stddev;
    double upper = mean + threshold * stddev;
    return std::max(lower, std::min(value, upper));
}

void ML::Loop()
{
    if (fChain == 0) return;

    // Output tree and new variables
    Float_t theta_noisy, theta_sin, theta_cos;
    Float_t ratio1, ratio2, ratio3;
    TTree *tree_with_noise = fChain->CloneTree(0);
    tree_with_noise->Branch("theta_noisy", &theta_noisy, "theta_noisy/F");
    tree_with_noise->Branch("theta_sin", &theta_sin, "theta_sin/F");
    tree_with_noise->Branch("theta_cos", &theta_cos, "theta_cos/F");
    tree_with_noise->Branch("ratio1", &ratio1);
    tree_with_noise->Branch("ratio2", &ratio2);
    tree_with_noise->Branch("ratio3", &ratio3);

    // Statistics containers
    double ch_sum[7] = {0}, ch_sq_sum[7] = {0};
    double ratio_sum[3] = {0}, ratio_sq_sum[3] = {0};
    double theta_sum[2] = {0}, theta_sq_sum[2] = {0};

    Long64_t nEntries = fChain->GetEntries();

    // First pass: compute mean and stddev for raw channel values
    for (Long64_t i = 0; i < nEntries; ++i) {
        fChain->GetEntry(i);
        int ch[7] = {Ch1, Ch2, Ch3, Ch4, Ch5, Ch6, Ch7};
        for (int j = 0; j < 7; ++j) {
            ch_sum[j] += ch[j];
            ch_sq_sum[j] += ch[j] * ch[j];
        }
    }

    double ch_mean[7], ch_stddev[7];
    for (int i = 0; i < 7; ++i) {
        ch_mean[i] = ch_sum[i] / nEntries;
        ch_stddev[i] = std::sqrt(ch_sq_sum[i] / nEntries - ch_mean[i] * ch_mean[i]);
        ch_sum[i] = 0;
        ch_sq_sum[i] = 0;
    }

    // Second pass: noise injection, feature calculation, clipping, and filling
    for (Long64_t i = 0; i < nEntries; ++i) {
        fChain->GetEntry(i);

        // Inject Gaussian noise to theta and compute sine/cosine targets
        theta_noisy = this->theta + 0.01f * gRandom->Gaus();
        theta_sin = std::sin(theta_noisy * TMath::DegToRad());
        theta_cos = std::cos(theta_noisy * TMath::DegToRad());

        theta_sum[0] += theta_sin;
        theta_sum[1] += theta_cos;
        theta_sq_sum[0] += theta_sin * theta_sin;
        theta_sq_sum[1] += theta_cos * theta_cos;

        // Compute channel ratios
        float sum67 = std::max(1e-6f, static_cast<float>(Ch6 + Ch7));
        float sum56 = std::max(1e-6f, static_cast<float>(Ch5 + Ch6));
        float sum27 = std::max(1e-6f, static_cast<float>(Ch2 + Ch7));
        ratio1 = (Ch3 + Ch4) / sum67;
        ratio2 = (Ch2 + Ch3) / sum56;
        ratio3 = (Ch4 + Ch5) / sum27;

        ratio_sum[0] += ratio1;
        ratio_sum[1] += ratio2;
        ratio_sum[2] += ratio3;
        ratio_sq_sum[0] += ratio1 * ratio1;
        ratio_sq_sum[1] += ratio2 * ratio2;
        ratio_sq_sum[2] += ratio3 * ratio3;

        // Clip channels
        int ch[7] = {Ch1, Ch2, Ch3, Ch4, Ch5, Ch6, Ch7};
        for (int j = 0; j < 7; ++j) {
            ch[j] = clip(ch[j], ch_mean[j], ch_stddev[j]);
            ch_sum[j] += ch[j];
            ch_sq_sum[j] += ch[j] * ch[j];
        }

        Ch1 = ch[0]; Ch2 = ch[1]; Ch3 = ch[2]; Ch4 = ch[3];
        Ch5 = ch[4]; Ch6 = ch[5]; Ch7 = ch[6];

        tree_with_noise->Fill();
    }

    // Final recalculation of clipped mean/stddev
    for (int i = 0; i < 7; ++i) {
        ch_mean[i] = ch_sum[i] / nEntries;
        ch_stddev[i] = std::sqrt(ch_sq_sum[i] / nEntries - ch_mean[i] * ch_mean[i]);
    }

    double ratio_mean[3], ratio_stddev[3];
    for (int i = 0; i < 3; ++i) {
        ratio_mean[i] = ratio_sum[i] / nEntries;
        ratio_stddev[i] = std::sqrt(ratio_sq_sum[i] / nEntries - ratio_mean[i] * ratio_mean[i]);
    }

    double theta_mean[2], theta_stddev[2];
    for (int i = 0; i < 2; ++i) {
        theta_mean[i] = theta_sum[i] / nEntries;
        theta_stddev[i] = std::sqrt(theta_sq_sum[i] / nEntries - theta_mean[i] * theta_mean[i]);
    }

    // Create output file
    const char* output_file_name = "TMVAOutput.root";
    TFile *outputFile = TFile::Open(output_file_name, "RECREATE");

    TMVA::Tools::Instance();
    TMVA::Factory factory("TMVARegression_theta", outputFile,
        "!V:!Silent:Color:DrawProgressBar:AnalysisType=Regression");
    TMVA::DataLoader dataloader("dataset_theta");

    // Add normalized channel input variables
    dataloader.AddVariable(Form("(Ch2 - %.5f)/%.5f", ch_mean[1], ch_stddev[1]), "Ch2_norm", "", 'F');
    dataloader.AddVariable(Form("(Ch3 - %.5f)/%.5f", ch_mean[2], ch_stddev[2]), "Ch3_norm", "", 'F');
    dataloader.AddVariable(Form("(Ch4 - %.5f)/%.5f", ch_mean[3], ch_stddev[3]), "Ch4_norm", "", 'F');
    dataloader.AddVariable(Form("(Ch5 - %.5f)/%.5f", ch_mean[4], ch_stddev[4]), "Ch5_norm", "", 'F');
    dataloader.AddVariable(Form("(Ch6 - %.5f)/%.5f", ch_mean[5], ch_stddev[5]), "Ch6_norm", "", 'F');
    dataloader.AddVariable(Form("(Ch7 - %.5f)/%.5f", ch_mean[6], ch_stddev[6]), "Ch7_norm", "", 'F');

    // Add normalized ratio variables// not huge effect so removed atm 
    //dataloader.AddVariable(Form("(ratio1 - %.5f)/%.5f", ratio_mean[0], ratio_stddev[0]), "ratio1", "", 'F');
    //dataloader.AddVariable(Form("(ratio2 - %.5f)/%.5f", ratio_mean[1], ratio_stddev[1]), "ratio2", "", 'F');
    //dataloader.AddVariable(Form("(ratio3 - %.5f)/%.5f", ratio_mean[2], ratio_stddev[2]), "ratio3", "", 'F');

    // Add normalized targets 
    dataloader.AddTarget(Form("(theta_sin - %.5f)/%.5f", theta_mean[0], theta_stddev[0]));
    //dataloader.AddTarget(Form("(theta_cos - %.5f)/%.5f", theta_mean[1], theta_stddev[1]));

    // Register training data
    dataloader.AddRegressionTree(tree_with_noise, 1.0);
    dataloader.PrepareTrainingAndTestTree("", "SplitMode=Random:NormMode=NumEvents:!V");

    // Book MLP method for regression
    factory.BookMethod(&dataloader, TMVA::Types::kMLP, "MLP_theta",
        "!H:!V:VarTransform=Norm:NeuronType=tanh:NCycles=20000:"
        "HiddenLayers=N+20,N+5,N:TestRate=6:TrainingMethod=BFGS:"
        "Sampling=0.3:SamplingEpoch=0.8:ConvergenceImprove=1e-6:"
        "ConvergenceTests=15:!UseRegulator");

    factory.TrainAllMethods();
    factory.TestAllMethods();
    factory.EvaluateAllMethods();

    outputFile->Close();
}

