#include<iostream>

int Ch1;
int Ch2;
int Ch3;
int Ch4;
int Ch5;
int Ch6;
int Ch7;


TTree* tree = new TTree("tree","DATA");
    tree->Branch("Ch1",&Ch1);
    tree->Branch("Ch2",&Ch2);
    tree->Branch("Ch3",&Ch3);
    tree->Branch("Ch4",&Ch4);
    tree->Branch("Ch5",&Ch5);
    tree->Branch("Ch6",&Ch6);
    tree->Branch("Ch7",&Ch7);

unsigned int getBigEndian32(const char *b){
    return ((b[0] << 24) & 0xff000000) |
           ((b[1] << 16) & 0x00ff0000) |
           ((b[2] << 8) & 0x0000ff00) |
           ((b[3] << 0) & 0x000000ff);
}

void convert(TString filename,
               int targetChannel1, 
               int targetChannel2,
               int targetChannel3,
               int targetChannel4, 
               int targetChannel5,
               int targetChannel6,
               int targetChannel7, 
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
            if(channel==targetChannel4){
                Ch4 = value;
            }
            else if(channel==targetChannel5){
                Ch5 = value;
            }
	        else if(channel==targetChannel6){
		    Ch6 = value;
            }
              else if(channel==targetChannel7){
		    Ch7 = value;
            }
      } 
    }
    tree->Fill();
  }
}

void GetPedestal(){
//int->float meanを出すときに誤差もつける？
      int mean1;
      int mean2;
      int mean3;
      int mean4;
      int mean5;
      int mean6;
      int mean7;

      TTree* Ptree = new TTree("Ptree","DATA");
      Ptree->Branch("Pedestal1",&mean1);
      Ptree->Branch("Pedestal2",&mean2);
      Ptree->Branch("Pedestal3",&mean3);
      Ptree->Branch("Pedestal4",&mean4);
      Ptree->Branch("Pedestal5",&mean5);
      Ptree->Branch("Pedestal6",&mean6);
      Ptree->Branch("Pedestal7",&mean7);

     convert("pedestal11.dat", 32, 33, 34, 38, 40, 41, 43,"AdcLg"); 

      TH1F* hist1 = new TH1F("hist1","hist1",1000,0,1000);
      TH1F* hist2 = new TH1F("hist2","hist1",1000,0,1000);
      TH1F* hist3 = new TH1F("hist3","hist1",1000,0,1000);
      TH1F* hist4 = new TH1F("hist4","hist4",1000,0,1000);
      TH1F* hist5 = new TH1F("hist5","hist5",1000,0,1000);
      TH1F* hist6 = new TH1F("hist6","hist6",1000,0,1000);
      TH1F* hist7 = new TH1F("hist7","hist7",1000,0,1000);

      
      tree->Draw("Ch1>>hist1");
      tree->Draw("Ch2>>hist2"); 
      tree->Draw("Ch3>>hist3");
      tree->Draw("Ch4>>hist4");
      tree->Draw("Ch5>>hist5"); 
      tree->Draw("Ch6>>hist6");
      tree->Draw("Ch7>>hist7");

      
      mean1 = hist1->GetMean();
      mean2 = hist2->GetMean(); 
      mean3 = hist3->GetMean();
      mean4 = hist4->GetMean();
      mean5 = hist5->GetMean(); 
      mean6 = hist6->GetMean();
      mean7 = hist7->GetMean();

      Ptree->Fill();
      TFile* file = new TFile("pedestaltree.root","RECREATE");
      Ptree->Write();
      file->Close();
}