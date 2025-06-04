#include <iostream>

int Ch1;
int Ch2;
int Ch3;
int Ch4;
int Ch5;
int Ch6;
int Ch7;
int Ch8;
int Ch9;
int Ch10;
int Ch11;
int Ch12;
int Ch13;/**/
//int r;
//int theta;
int sum;
//仮に
double Asy37;
double Asy46;
double Asy28;
double AsyLR;
double Asyout;
double Asyin;
int mean = 10078;
int sigma = 88;
int minimum = mean-(3*sigma);
int maximum = mean+(3*sigma);
double a = 0.64254;
double b = -6044.03;
double a_Err = 5.3003;
double b_Err = 0.757361;
double cal;
double calErr;


//Chの対応チェック



unsigned int getBigEndian32(const char *b){
    return ((b[0] << 24) & 0xff000000) |
           ((b[1] << 16) & 0x00ff0000) |
           ((b[2] << 8) & 0x0000ff00) |
           ((b[3] << 0) & 0x000000ff);
}
void maketreeML(TString filename="OutGAGG6.dat", int targetChannel1=48, int targetChannel2=40, int targetChannel3=41,
               int targetChannel4=44, int targetChannel5=43, int targetChannel6=45, int targetChannel7=46,
               int targetChannel8=32, int targetChannel9=38, int targetChannel10=37, int targetChannel11=36,
               int targetChannel12=33, int targetChannel13=34,int r = 15, int theta = 30, TString targetType="AdcLg"){

  TFile* file = new TFile("OutGAGG6Etree.root","RECREATE");
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
  tree->Branch("r",&r);
  tree->Branch("theta",&theta);
  tree->Branch("sum",&sum);
  tree->Branch("Asy37",&Asy37);
  tree->Branch("Asy46",&Asy46);
  tree->Branch("Asy28",&Asy28);
  tree->Branch("Asyout",&Asyout);
  tree->Branch("Asyin",&Asyin);
  tree->Branch("AsyLR",&AsyLR);
  tree->Branch("cal",&cal);
  tree->Branch("calErr",&calErr);
  /**/


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
              Ch1 = value;//ぺデスタル引く?
            
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
            }/**/
             
      } 
      
    }
    sum = Ch2+Ch3+Ch4+Ch5+Ch6+Ch7+Ch8+Ch9+Ch10+Ch11+Ch12+Ch13;
    Asy37 = (double)(Ch3-784.0-Ch7+787.0)/(Ch3-784.0+Ch7-787.0);
    Asy46 = (double)(Ch4-786.0-Ch6+784.0)/(Ch4-786.0+Ch6-784.0);
    Asy28 = (double)(Ch2-790.0-Ch8+779.0)/(Ch2-790.0+Ch8-779.0);
    //AsyLR = (double)(Ch1-783.0-Ch2+785.0)/(Ch1-783.0+Ch2-785.0); 
    Asyout = (double)(Ch3-784.0+Ch4-786.0-Ch7+787.0-Ch6+784.0)/(Ch3-784.0+Ch4-786.0+Ch7-787.0+Ch6-784.0);
    Asyin = (double)(Ch9-784.0+Ch10-784.0-Ch13+783.0-Ch12+782.0)/(Ch9-784.0+Ch10-784.0+Ch13-783.0+Ch12-782.0);
    AsyLR = (double)(Ch3-784.0+Ch4-786.0+Ch9-784.0+Ch10-784.0-Ch7+787.0-Ch6+784.0-Ch13+783.0-Ch12+782.0)/(Ch3-784.0+Ch4-786.0+Ch9-784.0+Ch10-784.0+Ch7-787.0+Ch6-784.0+Ch13-783.0+Ch12-782.0);
    cal = AsyLR * a + b;
    calErr = sqrt(pow(a_Err*AsyLR,2)+pow(b_Err,2));
    //tree->Fill();
    

    //Ch2に対する制限とかつけたい900~1100 Ch3:830~900 Ch7:
    /*if (Ch2>Ch3 && Ch2>Ch7 && Ch2>Ch4 && Ch2>Ch6 && Ch2>Ch5 && Ch8>Ch9 && Ch8>Ch13 && Ch8>Ch10 && Ch8>Ch12 && Ch8>Ch11 && sum < maximum && sum > minimum){
        tree->Fill();
    }*/
    
    //tree->Fill();
    if (Ch1>Ch2 && Ch1>Ch3 && Ch1>Ch4 && Ch1>Ch5 && Ch1>Ch6 && Ch1>Ch7 && Ch1>Ch8 && Ch1>Ch9 && Ch1>Ch10 && Ch1>Ch11 && Ch1>Ch12 && Ch1>Ch13 && sum>9600 ){
        tree->Fill();
    }
   /*
    if (Ch2>Ch1 & Ch2>Ch3 & Ch2>Ch4 & Ch2>Ch5 & Ch2>Ch6 &Ch2>Ch7){
        if (Ch3>Ch4 & Ch7>Ch6 & Ch4>Ch5 & Ch6>Ch5){
            tree->Fill();
        }
    }
    else if(Ch3>Ch1 & Ch3>Ch2 & Ch3>Ch4 & Ch3>Ch5 & Ch3>Ch6 &Ch3>Ch7){
        if (Ch4>Ch5 & Ch2>Ch7 & Ch5>Ch6 & Ch7>Ch6){
            tree->Fill();
        }
    }
    else if(Ch4>Ch1 & Ch4>Ch2& Ch4>Ch3 & Ch4>Ch5 & Ch4>Ch6 &Ch4>Ch7){
        if (Ch5>Ch6 & Ch3>Ch2 & Ch6>Ch7 & Ch2>Ch7){
            tree->Fill();
        }
    }
    else if(Ch5>Ch1 & Ch5>Ch2 & Ch5>Ch3 & Ch5>Ch4 & Ch5>Ch6 &Ch5>Ch7){
        if (Ch6>Ch7 & Ch4>Ch3 & Ch7>Ch2 & Ch3>Ch2){
            tree->Fill();
        }
    }
    else if(Ch6>Ch1 & Ch6>Ch2 & Ch6>Ch3 & Ch6>Ch4 & Ch6>Ch5 & Ch6>Ch7){
        if (Ch7>Ch2 & Ch5>Ch4 & Ch2>Ch3 & Ch4>Ch3){
            tree->Fill();
        }
    }
    else if(Ch7>Ch1 & Ch7>Ch2 & Ch7>Ch3 & Ch7>Ch4 & Ch7>Ch5 &Ch7>Ch6){
        if (Ch2>Ch3& Ch6>Ch5 & Ch3>Ch4 & Ch5>Ch4){
            tree->Fill();
        }
    }*/
  }
  tree->Draw("Ch1+sum");
  tree->Write();
  file->Close();
}