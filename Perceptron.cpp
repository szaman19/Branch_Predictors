#include "perceptron.h"

#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cassert>
#include <stdlib.h>

#define PERCEPTRON_COUNT 101
#define G_HISTORY_LENGTH 15
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


      // for (int i = 0; i < G_HISTORY_LENGTH; i++) {
      //   cout << g_history[i] << " " ;
      // }cout<< "\n";
    }



  }
  return correct;
}
