/********************************************************************************* 
* Ryan Miller, rnmiller 
* 2023 Winter CSE101 PA8 
* WordFrequency.c
* WordFrequency program that counts occurrences of words
* Usage: Order <input file> <output file>
*********************************************************************************/ 
#include "Dictionary.h"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
   Dictionary D = Dictionary();
   size_t begin, end, len;
   ifstream in;
   ofstream out;
   string line;
   string tokenBuffer;
   string token;
   string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$^&*()-_=+0123456789%";

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
   while( getline(in, line) )  {
      len = line.length();
      
      // get tokens in this line
      tokenBuffer = "";

      // get first token
      begin = min(line.find_first_not_of(delim, 0), len);
      end   = min(line.find_first_of(delim, begin), len);
      token = line.substr(begin, end-begin);

      while( token!="" ){  // we have a token

         string tokenLower(token);
         transform(tokenLower.begin(), tokenLower.end(), tokenLower.begin(),
                        [](unsigned char c){ return tolower(c); });
         
         if (D.contains(tokenLower)) {
            D.setValue(tokenLower, D.getValue(tokenLower) + 1);
         }
         else {
            D.setValue(tokenLower, 1);
         }
         // update token buffer
         tokenBuffer += "   "+token+"\n";

         // get next token
         begin = min(line.find_first_not_of(delim, end+1), len);
         end   = min(line.find_first_of(delim, begin), len);
         token = line.substr(begin, end-begin);
      }
   }

   out << D.to_string();

   // close files 
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}