#include <string>
#include <iostream>
#include <fstream>

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
  }

  return 0;
}
