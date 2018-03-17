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
unsigned long AlwaysTaken(vector<string> trace){
  string line;
  unsigned long correct = 0;
  for(int i =0; i < trace.size(); i++){
    if(line[11] == 'T'){
      correct++;
    }
  }
  return correct;
}
unsigned long AlwaysNotTaken(vector <string> trace){
  string line;
  unsigned long correct = 0;
  for(int i =0; i < trace.size(); i++){
    if(line[11] != 'T'){
      correct++;
    }
  }
  return correct;
}
int main(int argc, char *argv[]) {
  /* code */
  vector<string> trace;

  if(argc >1){
    string line;
    ifstream trace_file;
    trace_file.open(argv[1]);
    unsigned long taken = 0;
    unsigned long notTaken = 0;
    if (trace_file.is_open())
    {
      while ( getline (trace_file,line) )
      {
        trace.push_back(line);
      }
      trace_file.close();
    }

    taken = AlwaysTaken(trace);
    notTaken = AlwaysNotTaken(trace);
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
  output_file << Tournament(trace)<<"," << notTaken + taken <<";"<<'\n';
  output_file.close();
  }
  return 0;
}
