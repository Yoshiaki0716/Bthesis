#include<iostream>

int Ch1;
int Ch2;
int Ch3;
int Ch4;
int Ch5;
int Ch6;
int Ch7;
//求めたやつ
double a = 1.293;
int b = 779;

unsigned int getBigEndian32(const char *b){
    return ((b[0] << 24) & 0xff000000) |
           ((b[1] << 16) & 0x00ff0000) |
           ((b[2] << 8) & 0x0000ff00) |
           ((b[3] << 0) & 0x000000ff);
}
void EnergyPlot(TString filename="012802.dat", int targetChannel1=43, int targetChannel2=33, int targetChannel3=34, int targetChannel4=38, int targetChannel5=40, int targetChannel6=41, int targetChannel7=43, TString targetType="AdcLg"){
  TFile* file = new TFile("012802Etree.root","RECREATE");
  TTree* tree = new TTree("tree","DATA");

  tree->Branch("Ch1",&Ch1);
  tree->Branch("Ch2",&Ch2);
  tree->Branch("Ch3",&Ch3);
  tree->Branch("Ch4",&Ch4);
  tree->Branch("Ch5",&Ch5);
  tree->Branch("Ch6",&Ch6);
  tree->Branch("Ch7",&Ch7);

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
              Ch1 = (value-b)/a;
            }
        else if(channel==targetChannel2){
              Ch2 = (value-b)/a;
            }
	    else if(channel==targetChannel3){
		      Ch3 = (value-b)/a;
            }
	    else if(channel==targetChannel4){
		      Ch4 = (value-b)/a;
            }            
	    else if(channel==targetChannel5){
		      Ch5 = (value-b)/a;
            }            
	    else if(channel==targetChannel6){
		      Ch6 = (value-b)/a;
            }            
	    else if(channel==targetChannel7){
		      Ch7 = (value-b)/a;
          }
                       
      } 
    }
    tree->Fill();
  }
  tree->Write();
  file->Close();
}