#include <iostream>

double Ch1;
double Ch2;
double Ch3;
double Ch4;
double Ch5;
double Ch6;
double Ch7;
double Ch8;
double Ch9;
double Ch10;
double Ch11;
double Ch12;
double Ch13;

//Chの対応チェック


unsigned int getBigEndian32(const char *b){
    return ((b[0] << 24) & 0xff000000) |
           ((b[1] << 16) & 0x00ff0000) |
           ((b[2] << 8) & 0x0000ff00) |
           ((b[3] << 0) & 0x000000ff);
}
void maketree(TString filename="test0530.dat", int targetChannel1=32, int targetChannel2=33, int targetChannel3=34, int targetChannel4=36, int targetChannel5=38, int targetChannel6=40, int targetChannel7=43,
              int targetChannel8=37, int targetChannel9=41, int targetChannel10=44, int targetChannel11=45, int targetChannel12=46, int targetChannel13=48,TString targetType="AdcLg"){
  TFile* file = new TFile("test0530tree.root","RECREATE");//出力されるTTreeの入ったROOTファイル
  TTree* tree = new TTree("tree","DATA");

  tree->Branch("Ch1",&Ch1);
  tree->Branch("Ch2",&Ch2);
  tree->Branch("Ch3",&Ch3);
  tree->Branch("Ch4",&Ch4);
  tree->Branch("Ch5",&Ch5);
  tree->Branch("Ch6",&Ch6);
  tree->Branch("Ch7",&Ch7);
  tree->Branch("Ch8",&Ch8);
  tree->Branch("Ch9",&Ch9);
  tree->Branch("Ch10",&Ch10);
  tree->Branch("Ch11",&Ch11);
  tree->Branch("Ch12",&Ch12);
  tree->Branch("Ch13",&Ch13);
  //tree->Branch("sum",&sum);/**/
//TTreeのブランチを変更

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
	          else if(channel==targetChannel4){
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
            else if(channel==targetChannel8){
              Ch8 = value;
            }
	          else if(channel==targetChannel9){
		          Ch9 = value;
            }
	          else if(channel==targetChannel10){
		          Ch10 = value;
            }            
	          else if(channel==targetChannel11){
		          Ch11 = value;
            }            
	          else if(channel==targetChannel12){
		          Ch12 = value;
            }            
	          else if(channel==targetChannel13){
		          Ch13 = value;
            }
             
      } 
    }
/*
    if(Ch2>Ch1 && Ch2>Ch3 && Ch2>Ch4 && Ch2>Ch5 && Ch2>Ch6 && Ch2>Ch7){
      sum = (Ch2+Ch3+Ch4+Ch5+Ch6+Ch7-b)/a;
        
        tree->Fill();
    }
*/
  //treeに書き込む際の条件などを指定
    tree->Fill();
     
  }
  tree->Draw("Ch1");
  tree->Write();
  file->Close();
}













































































































































































































































