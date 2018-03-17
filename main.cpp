#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "perceptron.h"
using namespace std;

unsigned long OneBitBimodal(char *argv[],int size){
  vector<bool> table (size,true);
  ifstream trace_file;
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  string line;
  trace_file.open(argv[1]);
	if(trace_file.is_open()){
		while(getline(trace_file,line)){
			address = stoul(line.substr(0,10),nullptr, 16);
      index = address % size;
      result = (line[11] == 'T');
      if(table[index] == result){
        correct ++;
      }else{
        if(table[index]){
          table[index] = false;
        }else{
          table [index] = true;
        }
      }
		}
    trace_file.close();
	}
  return correct;
}

unsigned long TwoBitBimodal(char *argv[],int size){
  vector<short> twoBitTable (size,3);
  ifstream trace_file;
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  string line;
  trace_file.open(argv[1]);
  if(trace_file.is_open()){

    while(getline(trace_file,line)){
      address = stoul(line.substr(0,10),nullptr, 16);
      index = address % size;
      result = (line[11] == 'T');

      if(twoBitTable[index] > 1 && result){
        correct ++;
        if(twoBitTable[index] == 2){
          twoBitTable[index]++;
        }
      }
      else if(twoBitTable[index]> 1 && !result){
        twoBitTable[index]--;
      }
      else if(twoBitTable[index] < 2 && !result){
        correct++;
        if(twoBitTable[index] == 1){
          twoBitTable[index] --;
        }
      }else{
        twoBitTable[index]++;
      }

    }
  trace_file.close();
  }
  return correct;
}

unsigned long GShare(char *argv[],int size){
  vector<short> gTable (2048,3);
  ifstream trace_file;
  trace_file.open(argv[1]);
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  string line;
  unsigned int gcounter = 0;
  if(trace_file.is_open()){

    while(getline(trace_file,line)){
      address = stoul(line.substr(0,10),nullptr, 16);
      index = (address % 2048) ^ gcounter;
      result = (line[11] == 'T');

      if(gTable[index] >1 && result){
        correct++;
        if(gTable[index] == 2){
            gTable[index]++;
        }
      }
      else if(gTable[index] > 1 && !result){
        gTable[index]--;
      }
      else if(gTable[index] < 2 && !result){
        correct++;
        if(gTable[index] == 1){
            gTable[index]--;
        }
      }
      else{
        gTable[index]++;
      }
      gcounter = gcounter * 2;
      int mod = pow(2,size);
      gcounter = gcounter % mod;
      if(result){
        gcounter++;
      }
    }
    trace_file.close();
  }
  return correct;
}

unsigned long Tournament(char  *argv[]){
  string line;
  ifstream trace_file;
  trace_file.open(argv[1]);
  vector<short> twoBitTable (2048,3);
  vector<short> GShare(2048,3);
  unsigned long correct = 0;
  unsigned long address;
  unsigned int gcounter = 0;
  int gindex;
  int bindex;
  bool result;
  bool BiModalPrediction = false;
  bool GSharePrediction = false;
  vector <short> selector (2048,0);


  if(trace_file.is_open()){

    while(getline(trace_file,line)){
      address = stoul(line.substr(0,10),nullptr, 16);

      gindex = (address % 2048) ^ gcounter;
      bindex = (address % 2048);

      result = (line[11] == 'T');



    BiModalPrediction = false;
    GSharePrediction = false;
      /*GShare */
      if(GShare[gindex] >1 && result){
        // correct++;
        GSharePrediction = true;
        if(GShare[gindex] == 2){
            GShare[gindex]++;
        }
      }
      else if(GShare[gindex] > 1 && !result){
        GShare[gindex]--;
      }
      else if(GShare[gindex] < 2 && !result){
        //correct++;
        GSharePrediction = true;
        if(GShare[gindex] == 1){
            GShare[gindex]--;
        }
      }
      else{
        GShare[gindex]++;
      }

      gcounter = gcounter * 2;
      int mod = pow(2,11);
      gcounter = gcounter % mod;

      if(result){
        gcounter++;
      }

      /*BiModal */

      if(twoBitTable[bindex] > 1 && result){
        // correct ++;
        BiModalPrediction = true;
        if(twoBitTable[bindex] == 2){
          twoBitTable[bindex]++;
        }
      }
      else if(twoBitTable[bindex]> 1 && !result){
        twoBitTable[bindex]--;
      }
      else if(twoBitTable[bindex] < 2 && !result){
        // correct++;
        BiModalPrediction = true;
        if(twoBitTable[bindex] == 1){
          twoBitTable[bindex] --;
        }
      }else{
        twoBitTable[bindex]++;
      }


      /*Tournament */


      /*
      * Strong GShare = 0
      * Weak GShare = 1
      * Weak Selector = 2
      * Strong Selector = 3
      */

      /*
      * GShare Prediction = 2 -> T
      * GShare Prediction = 3 -> T
      * GShare Prediction = 1 -> N
      * GShare Prediction = 0 -> N
      */

      /*
      * BiModal Prediction = 3 -> T
      * BiModal Prediction = 2 -> T
      * BiModal Prediction = 1 -> N
      * BiModal Prediction = 0 -> N
      */
/* Ok from segfaults */

      if(GSharePrediction && BiModalPrediction){
        correct++;
      }else if (!GSharePrediction && BiModalPrediction){
        if(selector[bindex] < 2){
          selector[bindex]++;
        }else{
          correct++;
          if(selector[bindex] != 3){
            selector[bindex]++;
          }
        }
      }
      else if(GSharePrediction && !BiModalPrediction){
        if(selector[bindex] < 2){
          correct++;
          if(selector[bindex]!=0){
            selector[bindex]--;
          }
        }else{
          selector[bindex]--;
        }
      }
    }
    trace_file.close();
  }
  return correct;
}


int main(int argc, char *argv[]) {
  /* code */
  cout << "Number of arguments "<< argc << '\n';



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

  output_file <<
   OneBitBimodal(argv,16) << "," << notTaken + taken <<"; "<<
   OneBitBimodal(argv,32) << "," << notTaken + taken <<"; "<<
   OneBitBimodal(argv,128) << "," << notTaken + taken <<"; "<<
   OneBitBimodal(argv,256) << "," << notTaken + taken <<"; "<<
   OneBitBimodal(argv,512) << "," << notTaken + taken <<"; "<<
   OneBitBimodal(argv,1024) << "," << notTaken + taken <<"; "<<
   OneBitBimodal(argv,2048) << "," << notTaken + taken <<";"<<'\n';
   output_file <<
    TwoBitBimodal(argv,16) << "," << notTaken + taken <<"; "<<
    TwoBitBimodal(argv,32) << "," << notTaken + taken <<"; "<<
    TwoBitBimodal(argv,128) << "," << notTaken + taken <<"; "<<
    TwoBitBimodal(argv,256) << "," << notTaken + taken <<"; "<<
    TwoBitBimodal(argv,512) << "," << notTaken + taken <<"; "<<
    TwoBitBimodal(argv,1024) << "," << notTaken + taken <<"; "<<
    TwoBitBimodal(argv,2048) << "," << notTaken + taken <<";"<<'\n';
    output_file <<
     GShare(argv,3) << "," << notTaken + taken <<"; "<<
     GShare(argv,4) << "," << notTaken + taken <<"; "<<
     GShare(argv,5) << "," << notTaken + taken <<"; "<<
     GShare(argv,6) << "," << notTaken + taken <<"; "<<
     GShare(argv,7) << "," << notTaken + taken <<"; "<<
     GShare(argv,8) << "," << notTaken + taken <<"; "<<
     GShare(argv,9) << "," << notTaken + taken <<"; "<<
     GShare(argv,10) << "," << notTaken + taken <<"; "<<
     GShare(argv,11) << "," << notTaken + taken <<";"<<'\n';

  output_file << Tournament(argv)<<"," << notTaken + taken <<";"<<'\n';
  output_file.close();
  }
  return 0;
}
