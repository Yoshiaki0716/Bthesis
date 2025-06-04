#include <iostream>
const int nbin=100;
unsigned int getBigEndian32(const char *b){
    return ((b[0] << 24) & 0xff000000) |
           ((b[1] << 16) & 0x00ff0000) |
           ((b[2] << 8) & 0x0000ff00) |
           ((b[3] << 0) & 0x000000ff);
	}
TH1D* testhist(TString filename="2Channeltest.dat", int targetChannel=33, TString targetType="AdcLg"){
  TH1D* h=new TH1D(Form("h_%s",filename.Data()),";channel;#events",nbin,850,3500);
  std::ifstream datFile(filename.Data(), std::ios::in | std::ios::binary);
  char bin[4];
  unsigned int header;
  unsigned int data;
  int size;
  TString type;
  int value, channel; 
  while (datFile){
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
	if(channel==targetChannel){
	  printf("%5d",size);
	  h->Fill(value);
	}
      }
    }
  }
  return h;
}
