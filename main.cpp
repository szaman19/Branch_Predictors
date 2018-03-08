#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

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

    ofstream output_file;
    output_file.open("output.txt", ios::trunc);
    output_file <<"Input file name: "<< argv[1] << '\n';
    output_file <<taken << "," << notTaken + taken <<";"<<'\n';
    output_file << notTaken << "," << notTaken + taken <<";" << '\n';
    output_file.close();

    /*
    One-bit bimodal test with table size 16
    */


	unsigned long address;
  int index;
  vector<bool> table (32,true);
  bool result;
  int correct = 0;


  trace_file.open(argv[1]);
	if(trace_file.is_open()){
		while(getline(trace_file,line)){
			address = stoul(line.substr(0,10),nullptr, 16);
      index = address % 32;
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
  output_file.open("OneBitBimodal.txt", ios::trunc);
  output_file <<"Input file name: "<< argv[1] << '\n';
  output_file <<correct << "," << notTaken + taken <<";"<<'\n';
  output_file.close();

  /*
  2 bit BiModal
  */
  correct = 0;
  vector<int> twoBitTable (2048,3);
  trace_file.open(argv[1]);
  if(trace_file.is_open()){

    while(getline(trace_file,line)){
      address = stoul(line.substr(0,10),nullptr, 16);
      index = address % 2048;
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

  output_file.open("TwoBitBimodal.txt", ios::trunc);
  output_file <<"Input file name: "<< argv[1] << '\n';
  output_file <<correct << "," << notTaken + taken <<";"<<'\n';
  output_file.close();
  cout << correct << '\n';
  /*
  G share
  */
  }
  return 0;
}
