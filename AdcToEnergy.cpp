#include <iostream>
//ADC値のピークとぺデスタルから
//errorつけると近似がうまくできないpython?プロットするだけになるかも
void AdcToEnergy(double peak1 = 10195.9, double peak2 = 11393.1, double meanError1 = 56.1635, double meanError2 = 83.4331, double pedestal = 9410){
    double x[3] = {0, 511.0, 1275.0};
    double y[3] = {pedestal, peak1, peak2};
    double ex[3] = {0.0, 0.0, 0.0};
    double eyy[3] = {0.0, meanError1, meanError2};
    double ey[3] ={0.0, 1.68, 7.50};

    double xx[6];
    double yy[6];
    for (int i=0; i<3; i++){
      yy[i] = y[i]+eyy[i];
      yy[5-i] = y[i]-eyy[i];
      xx[i] = x[i];
      xx[5-i] =x[i];
    }


    TCanvas*c1 = new TCanvas("c1", "Energy:ADC",800,600);
//TGraphErrors
    //TGraph * graph = new TGraphErrors (3,x,y,ex,ey);
    //TGraph * graph2 = new TGraphErrors (6,xx,yy);
    TGraph * graph = new TGraphErrors (3,y,x,ey,ex);
    TGraph * graph2 = new TGraphErrors (6,yy,xx);
    //TGraph *graph = new TGraph (3,x,y);
    graph->Draw("AP");

    //TF1 *Fit3 = new TF1("Fit3", "pol1", 0.0, 1275.0);
    TF1 *Fit3 = new TF1("Fit3", "pol1", 9400, 12000);
    //TF1 *Fit3 = new TF1("Fit3", "[0]*x + [1]", 0, 1275);
    Fit3->SetParameters((peak2-pedestal)/1275.0, 0);
    //Fit3->SetParameters(1.41,783);

    //graph->SetMarkerStyle(21);
    //graph->SetMarkerColor(kBlack);

    graph->SetMarkerStyle(21);
    graph->SetMarkerColor(kRed);
    graph2->SetFillColorAlpha(kGreen,0.30);
    
    graph2->Draw("SAME F");
    graph->Draw("SAME P");


    graph->Fit("Fit3","RW");
    //graph->Fit("pol1");
    Fit3->Draw("same");

    graph->SetTitle("Energy:ADC");
    //graph->SetTitle("ADC:Energy");
    //graph->GetXaxis()->SetTitle("Energy (keV)");//単位
    //graph->GetYaxis()->SetTitle("ADC_Value");
    graph->GetYaxis()->SetTitle("Energy (keV)");//単位
    graph->GetXaxis()->SetTitle("ADC_Value");
    //graph->GetXaxis()->SetLimits(0, 7250);
    //graph->GetXaxis()->SetRangeUser(0, 7250);
    graph->GetYaxis()->SetTitleOffset(1.5);
    c1->Update();

    TLegend *legend = new TLegend(0.15, 0.85, 0.25, 0.8);
    legend->AddEntry(graph2, ":1#sigma", "f"); 
    legend->Draw();

    double a = Fit3->GetParameter(1);
    double Error1 = Fit3->GetParError(1);
    double b = Fit3->GetParameter(0);
    double Error2 = Fit3->GetParError(0);

    std::cout << "a:" << a << "+-" << Error1 << std::endl;
    std::cout << "b:" << b << "+-" << Error2 << std::endl;
    std::cout << "R_E:" << 235*a*meanError1/511 <<std::endl;

}
/*
    //エネルギーのtree作っちゃう+=3sigmaのデータはmaketreeMLで
    double Ch1;
    double Ch2;
    double Ch3;
    double Ch4;
    double Ch5;
    double Ch6;
    double Ch7;/


unsigned int getBigEndian32(const char *b){
    return ((b[0] << 24) & 0xff000000) |
           ((b[1] << 16) & 0x00ff0000) |
           ((b[2] << 8) & 0x0000ff00) |
           ((b[3] << 0) & 0x000000ff);
}
void maketree(TString filename="OutGAGG4.dat", int targetChannel1=32, int targetChannel2=33, int targetChannel3=34, int targetChannel4=36, int targetChannel5=38, int targetChannel6=40, int targetChannel7=43, TString targetType="AdcLg"){
  TFile* file = new TFile("OutGAGG4Etree.root","RECREATE");
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
              Ch1 = value;
              //Ch1 = (value-b)/a;//aとbかける
            }
            else if(channel==targetChannel2){
              Ch2 = value;
              //Ch2 = (value-b)/a;
            }
	      else if(channel==targetChannel3){
		      Ch3 = value;
              //Ch3 = (value-b)/a;
            }
	      else if(channel==targetChannel4){
		      Ch4 = value;
              //Ch4 = (value-b)/a;
            }            
	      else if(channel==targetChannel5){
		      Ch5 = value;
              //Ch5 = (value-b)/a;
            }            
	       else if(channel==targetChannel6){
		      Ch6 = value;
              //Ch6 = (value-b)/a;
            }            
	      else if(channel==targetChannel7){
		      Ch7 = value;
              //Ch7 = (value-b)/a;
            }
             
      } 
    }
    if (Ch2>Ch1 && Ch2>Ch3 && Ch2>Ch4 && Ch2>Ch5 && Ch2>Ch6 && Ch2>Ch7 && Ch2+Ch3+Ch4+Ch5+Ch6+Ch7>4800){
        Ch1 = (Ch1-b)/a;
        Ch2 = (Ch2-b)/a;
        Ch3 = (Ch3-b)/a;
        Ch4 = (Ch4-b)/a;
        Ch5 = (Ch5-b)/a;
        Ch6 = (Ch6-b)/a;
        Ch7 = (Ch7-b)/a;
        
        tree->Fill();
    }
    //tree->Fill();
     
  }
  tree->Write();
  file->Close();
}*/



    