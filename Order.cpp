//-----------------------------------------------------------------------------
// Order.cpp
// joey vigil
// jovigil
// pa7
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char* argv[]){

   int line_count;
   ifstream in;
   ofstream out;
   string line;

   // check command line for correct number of arguments
   if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }

   // open files for reading and writing 
   in.open(argv[1]);
   if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

   out.open(argv[2]);
   if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   }
 
   line_count = 0;
   Dictionary D;
   while( getline(in, line) )  { // read in all lines and store in dict
      line_count++;              // as "line":line_count
      D.setValue(line, line_count);
   }
   out << D << endl; // print in order walk to output file
   out << D.pre_string() << endl;   // print pre order walk to output file
   
   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

