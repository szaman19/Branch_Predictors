#include "OneBitBimodal.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;
unsigned long OneBitBimodal(vector<string> traces,int size){
  vector<bool> table (size,true);
  bool result;
  unsigned long correct = 0;
  unsigned long address;
  int index;
  string line;

  for(int i = 0; i < traces.size(); i++){
    line = traces[i];
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
  return correct;
  // trace_file.open(argv[1]);
	// if(trace_file.is_open()){
	// 	while(getline(trace_file,line)){
	// 		address = stoul(line.substr(0,10),nullptr, 16);
  //     index = address % size;
  //     result = (line[11] == 'T');
  //     if(table[index] == result){
  //       correct ++;
  //     }else{
  //       if(table[index]){
  //         table[index] = false;
  //       }else{
  //         table [index] = true;
  //       }
  //     }
	// 	}
  //   trace_file.close();
	// }
  // return correct;
}
