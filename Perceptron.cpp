#include "Perceptron.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include <stdlib.h>

#define PERCEPTRON_COUNT 52
#define G_HISTORY_LENGTH 10
#define THRESHHOLD 33
#define BIAS 100

using namespace std;
unsigned long Perceptron(char *argv[]){
  ifstream trace_file;
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  string line;
  trace_file.open(argv[1]);
  //EFFECTIVE G HISTORY LENGTH IS G_HISTORY_LENGTH - 1;
  vector<bool>g_history(G_HISTORY_LENGTH,true);
  //Initalize Matrix as 0;
  int matrix[PERCEPTRON_COUNT][G_HISTORY_LENGTH] = {{0}};
  for(int i = 0; i < PERCEPTRON_COUNT; i++){
    //Insert bias value
    matrix[i][0] = BIAS;
  }
 long y_out = 0;
  bool prediction = true;
  if(trace_file.is_open()){


    while (getline(trace_file,line)) {
      /* code */
      address = stoul(line.substr(0,10),nullptr,16);
      index = address % PERCEPTRON_COUNT;
      result = (line[11] == 'T');
      y_out = 0;
      // Compute dot product of perceptron weights and g history
      for(int p = 0; p < G_HISTORY_LENGTH; p++){
        y_out += matrix[index][p] * ((2*g_history[p])-1);
      }

      // If positive then predict taken, if negative predict not taken
      if(y_out > 0){
        prediction = true;
      }else{
        prediction = false;
      }
      //Prediction matches result, increment counter
      if(prediction == result){
        correct++;
      }
      /*
       TRAINING PHASE
      */
      //If prediction is incorrect or result is less than threshhold
      if(prediction != result || abs(y_out) < THRESHHOLD){
        matrix[index][0] += ((2 * (int)result)-1); //Bias update
        for (int l = 1; l < G_HISTORY_LENGTH; l++){
          //Update weights
          matrix[index][l] = matrix[index][l]+((2*(g_history[l] == result))-1);
        }
      }
      //update global history
      //First bit is always 1. So start from second element on vector.
      for(int g = 1; g < G_HISTORY_LENGTH - 1; g++){
        g_history[g] = g_history[g+1];
      }
      g_history[G_HISTORY_LENGTH - 1] = result;

    }
  }
  return correct;
}

unsigned long PerceptronWithAgree(char *argv[]){
  ifstream trace_file;
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  unsigned int gcounter = 0;
  int gindex;
  int bindex;
  vector<short> GShare(2048,3);
  vector <short> selector (2048,0);
  bool GSharePrediction = false;
  string line;
  trace_file.open(argv[1]);
  //EFFECTIVE G HISTORY LENGTH IS G_HISTORY_LENGTH - 1;
  vector<bool>g_history(G_HISTORY_LENGTH,true);
  //Initalize Matrix as 0;
  int matrix[PERCEPTRON_COUNT][G_HISTORY_LENGTH] = {{0}};
  for(int i = 0; i < PERCEPTRON_COUNT; i++){
    //Insert bias value
    matrix[i][0] = BIAS;
  }
  long y_out = 0;
  bool prediction = true;
  bool PerceptronPrediction = true;
  if(trace_file.is_open()){


    while (getline(trace_file,line)) {
      /* code */
      address = stoul(line.substr(0,10),nullptr,16);
      index = address % PERCEPTRON_COUNT;
      gindex = (address % 2048) ^ gcounter;
      bindex = (address % 2048);
      result = (line[11] == 'T');
      y_out = 0;
      // Compute dot product of perceptron weights and g history
      for(int p = 0; p < G_HISTORY_LENGTH; p++){
        y_out += matrix[index][p] * ((2*g_history[p])-1);
      }

      // If positive then predict taken, if negative predict not taken
      if(y_out > 0){
        prediction = true;
      }else{
        prediction = false;
      }
      //Prediction matches result, increment counter
      if(prediction == result){
        PerceptronPrediction = true;
      }
      /*
       TRAINING PHASE
      */
      //If prediction is incorrect or result is less than threshhold
      if(prediction != result || abs(y_out) < THRESHHOLD){
        matrix[index][0] += ((2 * (int)result)-1); //Bias update
        for (int l = 1; l < G_HISTORY_LENGTH; l++){
          //Update weights
          matrix[index][l] = matrix[index][l]+((2*(g_history[l] == result))-1);
        }
      }
      //update global history
      //First bit is always 1. So start from second element on vector.
      for(int g = 1; g < G_HISTORY_LENGTH - 1; g++){
        g_history[g] = g_history[g+1];
      }
      g_history[G_HISTORY_LENGTH - 1] = result;

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
        int mod = pow(2,G_HISTORY_LENGTH-1);
        gcounter = gcounter % mod;

        if(result){
          gcounter++;
        }

        if(GSharePrediction && PerceptronPrediction){
          correct++;
        }else if (!GSharePrediction && PerceptronPrediction){
          if(selector[bindex] < 2){
            selector[bindex]++;
          }else{
            correct++;
            if(selector[bindex] != 3){
              selector[bindex]++;
            }
          }
        }
        else if(GSharePrediction && !PerceptronPrediction){
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
  }
  return correct;
}
