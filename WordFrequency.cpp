//-----------------------------------------------------------------------------
// jovigil
// joey vigil
// pa8
// WordFrequency.cpp
// RBT Dictionary client program
//
//-----------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cctype>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){

   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";

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

   // read each line of input file, then count and print tokens 
   Dictionary D;
   while( getline(in, line) )  {

      len = line.length();
      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);

      while( token!="" ){  // we have a token
         // make lower case
         int strLen = token.length(), i;
         for ( i=0; i<strLen; i++ ){
            token[i] = tolower(token[i]);
         }
         // update dictionary with token
         if ( D.contains(token) ){
            //cout << "does this ever happen" << endl;
            valType val = D.getValue(token);
            // valType val0 = val;
            // val += 1;
            // assert( D.getValue(token) == (val0 + 1) );
            D.setValue(token, (val + 1));
         }
         else {
            //cout << "how bout this" << endl;
            D.setValue(token, 1);
         }

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }
   // print resulting dictionary to out
   out << D << endl;

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}

