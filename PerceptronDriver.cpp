#include "Perceptron.h"

#include <string>
#include <iostream>
#include <fstream>

#include <cmath>
#include <vector>
#include <cassert>
#include <stdlib.h>
using namespace std;
 int main(int argc, char *argv[]) {
   if(argc >1){
     string line;
     ifstream trace_file;
     trace_file.open(argv[1]);
     unsigned long total = 0;
     if(trace_file.is_open()){
       while ( getline (trace_file,line) )
       {
         total++;
       }
       trace_file.close();
     }
     ofstream output_file;
     output_file.open(argv[2], ios::trunc);

     output_file<<Perceptron(argv)<<","<<total<<";\n";
     output_file<<PerceptronWithAgree(argv)<<","<<total<<";\n";
     output_file.close();
   }

   return 0;
 }
