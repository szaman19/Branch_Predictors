#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include "Tournament.h"

unsigned long Tournament(vector<string> trace){
  string line;
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

  for(int i =0; i < trace.size(); i ++){
    line = trace[i];

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
return correct;
}
