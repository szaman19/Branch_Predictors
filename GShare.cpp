#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "GShare.h"

using namespace std;

unsigned long GShare(vector<string> trace, int size){
  vector<short> gTable (2048,3);
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  string line;
  unsigned int gcounter = 0;
  for(int i = 0; i < trace.size(); i++){
      line = trace[i];
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
      gcounter = gcounter <<1;
      int mod = pow(2,size);
      gcounter = gcounter % mod;
      if(result){
        gcounter++;
      }
  }
  return correct;
}
