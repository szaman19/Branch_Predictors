#include <string>
#include <iostream>
#include <vector>
#include "TwoBitBimodal.h"
using namespace std;

unsigned long TwoBitBimodal(vector<string> trace, int size){
  vector<short> twoBitTable (size,3);
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  string line;
  for(int i= 0; i < trace.size(); i++){
      line = trace[i];
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
  return correct;
}
