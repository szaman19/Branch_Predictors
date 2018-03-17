#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "OneBitBimodal.h"
#include "TwoBitBimodal.h"
#include "GShare.h"
#include "Tournament.h"
using namespace std;

int main(int argc, char *argv[]) {
  /* code */
  vector<string> trace;

  if(argc >1){
    string line;
    ifstream trace_file;
    trace_file.open(argv[1]);
    int taken = 0;
    int notTaken = 0;
    if (trace_file.is_open())
    {
      while ( getline (trace_file,line) )
      {
        trace.push_back(line);
        if(line[11] == 'T'){
          taken++;
        }else{
          notTaken++;
        }
      }
      trace_file.close();
    }
    // unsigned int num = Perceptron(argv);
    // double Misprediction =  (double)((taken + notTaken) - num)/ (double)(taken + notTaken) * 100;
    // cout <<num  << ',' << taken+notTaken<<";"<< '\n';
    // cout << "Misprediction Rate: "<< Misprediction<< "\% \n";
    ofstream output_file;
    output_file.open(argv[2], ios::trunc);
    output_file <<taken << "," << notTaken + taken <<";"<<'\n';
    output_file << notTaken << "," << notTaken + taken <<";" << '\n';

  //OneBitBimodal
  for(int i = 16; i < 2049; i*=2){
    if(i == 64) continue;
    output_file <<OneBitBimodal(trace,i)<<"," << notTaken + taken <<"; ";
  }
  output_file <<"\n";

  //TwoBitBimodal
  for(int i = 16; i < 2049; i*=2){
    if(i == 64) continue;
    output_file <<TwoBitBimodal(trace,i)<<"," << notTaken + taken <<"; ";
  }
  output_file <<"\n";
  //GShare
  for(int i = 3; i < 12; i++){
    output_file <<GShare(trace,i) << "," << notTaken + taken <<"; ";
  }
  output_file <<"\n";

  // output_file <<
  //  OneBitBimodal(argv,16) << "," << notTaken + taken <<"; "<<
  //  OneBitBimodal(argv,32) << "," << notTaken + taken <<"; "<<
  //  OneBitBimodal(argv,128) << "," << notTaken + taken <<"; "<<
  //  OneBitBimodal(argv,256) << "," << notTaken + taken <<"; "<<
  //  OneBitBimodal(argv,512) << "," << notTaken + taken <<"; "<<
  //  OneBitBimodal(argv,1024) << "," << notTaken + taken <<"; "<<
  //  OneBitBimodal(argv,2048) << "," << notTaken + taken <<";"<<'\n';
   // output_file <<
   //  TwoBitBimodal(argv,16) << "," << notTaken + taken <<"; "<<
   //  TwoBitBimodal(argv,32) << "," << notTaken + taken <<"; "<<
   //  TwoBitBimodal(argv,128) << "," << notTaken + taken <<"; "<<
   //  TwoBitBimodal(argv,256) << "," << notTaken + taken <<"; "<<
   //  TwoBitBimodal(argv,512) << "," << notTaken + taken <<"; "<<
   //  TwoBitBimodal(argv,1024) << "," << notTaken + taken <<"; "<<
   //  TwoBitBimodal(argv,2048) << "," << notTaken + taken <<";"<<'\n';
    // output_file <<
    //  GShare(argv,3) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,4) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,5) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,6) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,7) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,8) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,9) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,10) << "," << notTaken + taken <<"; "<<
    //  GShare(argv,11) << "," << notTaken + taken <<";"<<'\n';

  output_file << Tournament(trace)<<"," << notTaken + taken <<";"<<'\n';
  output_file.close();
  }
  return 0;
}
