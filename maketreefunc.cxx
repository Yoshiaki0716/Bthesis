#include<iostream>

int Ch1;
int Ch2;
int Ch3;
int radius;
int theta;
float A;

TTree* tree = new TTree("tree","DATA");
    tree->Branch("Ch1",&Ch1);
    tree->Branch("Ch2",&Ch2);
    tree->Branch("Ch3",&Ch3);
    tree->Branch("radius",&radius);
    tree->Branch("theta",&theta);
    tree->Branch("Asy",&A);

unsigned int getBigEndian32(const char *b){
    return ((b[0] << 24) & 0xff000000) |
           ((b[1] << 16) & 0x00ff0000) |
           ((b[2] << 8) & 0x0000ff00) |
           ((b[3] << 0) & 0x000000ff);
}
//Ch3とCh7
float asymmetry(int Ch2,
                int Ch3,
                TString pfilename){

    int p2;
    int p3;

    TFile* pfile = TFile::Open(pfilename);
    TTree *Ptree = (TTree*)pfile->Get("Ptree");

    Ptree->SetBranchAddress("Pedestal2",&p2);
    Ptree->SetBranchAddress("Pedestal3",&p3);
    Ptree->GetEntry(0);

    pfile->Close();

    float Asy = ((float)(Ch2-p2-Ch3+p3))/((float)(Ch2-p2+Ch3-p3));
    return Asy;
}

void convert(TString filename,
             int targetChannel1, 
             int targetChannel2,
             int targetChannel3,
             int targetRadius,
             int targetTheta,
             TString targetType){

  std::ifstream datFile(filename.Data(), std::ios::in | std::ios::binary); 
  char bin[4];
  unsigned int header;
  unsigned int data;
  int size;
  TString type;
  int value, channel;while (datFile){
    datFile.read(bin,4);
    header=getBigEndian32(bin);
    size=header&0x0fff;
    
    for (int i = 0; i < size; i++){
      datFile.read(bin,4);
      data=getBigEndian32(bin);
      type="None";
      if((data & 0x00680000) == 0x00000000){
	type="AdcHg";
      }else if ((data & 0x00680000) == 0x00080000){
	type="AdcLg";
      }else if((data & 0x00601000) == 0x00201000){
	type="TdcLeading";
      }else if((data & 0x00601000) == 0x00200000){
	type="TdcTrailing";
      }else if((data & 0x00600000) == 0x00400000){
	type="Scaler";
      }
      value=data&0x0fff;
      channel=(data >> 13) & 0x3f;
      if(type==targetType){
            if(channel==targetChannel1){
                Ch1 = value;
            }
            else if(channel==targetChannel2){
                Ch2 = value;
            }
	        else if(channel==targetChannel3){
		        Ch3 = value;
            }
      } 
    }
    radius = targetRadius;
    theta = targetTheta;
    A = asymmetry(Ch2,Ch3,"pedestaltree.root");
    if(Ch1>Ch2 && Ch1>Ch3){
        tree->Fill();
        }
  }
}

void maketreefunc(){
    
    convert("testR15theta30.dat", 32, 33, 34, 15, 30, "AdcLg");
    convert("testR15theta20.dat", 32, 33, 34, 15, 20, "AdcLg");
    convert("testR15theta10.dat", 32, 33, 34, 15, 10, "AdcLg");
    convert("testR15theta0.dat", 32, 33, 34, 15, 0, "AdcLg");
    convert("testR15theta-10.dat", 32, 33, 34, 15, -10, "AdcLg");
    convert("testR15theta-20.dat", 32, 33, 34, 15, -20, "AdcLg");
    convert("testR15theta-30.dat", 32, 33, 34, 15, -30, "AdcLg");
    TFile* file = new TFile("testR15tree.root","RECREATE");
    tree->Write();
    file->Close(); 
}

