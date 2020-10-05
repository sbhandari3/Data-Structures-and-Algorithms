/*********************************************************************************
* Suneet Bhandari, sugbhand
* 2020 Spring CSE101 PA7
* Shuffle.c
* Client for List
*********************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include"List.h"
using namespace std;

#define MAX_LEN 300

void shuffle(List& D){
	List one;
	List two;
	List three;
	int t;
	int split = D.size()/2;
	int i = 0;
	int j = 0;
	if(D.size()%2 == 1){
		t = 1;
	}
	else{
		t = 0;
	}
	D.moveFront();
	while(i < split){
		one.insertBefore(D.peekNext());
		D.moveNext();
		i++;
	}
	while(D.position() != D.size()){
		two.insertBefore(D.peekNext());
		D.moveNext();
	}
	one.moveFront();
	two.moveFront();
	
	D.clear();
	
	while(j < split){
		D.insertBefore(two.peekNext());
		D.insertBefore(one.peekNext());
		one.moveNext();
		two.moveNext();	
		j++;
	}
	if(t == 1){
		D.insertBefore(two.peekNext());
	}
	one.clear();
	two.clear();
}

int main(int argc, char * argv[]){

   // check command line for correct number of arguments
   if( argc != 2 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   }
/*
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
   line_count = 0;
   while( getline(in, line) )  {
      line_count++;
      line_length = line.length();
      
      // get tokens in this line
      token_count = 0;
      tokenBuffer = "";

      // get first token
      begin = min(line.find_first_not_of(" ", 0), line_length);
      end = min(line.find_first_of(" ", begin), line_length);
      token = line.substr(begin, end-begin);
      
      while( token!="" ){  // we have a token
         // update token buffer
         tokenBuffer += "   "+token+"\n";
         token_count++;

         // get next token
         begin = min(line.find_first_not_of(" ", end+1), line_length);
         end = min(line.find_first_of(" ", begin), line_length);
         token = line.substr(begin, end-begin);
      }

      // print tokens in this line
      out << "line " << line_count << " contains " << token_count;
      out << " token" << (token_count==1?"":"s") << endl;
      out << tokenBuffer << endl;
   }

   // close files 
   in.close();
   out.close();
*/
   int one;
   List D;
   List E;
   int a;
   int count;
   int check;

   one = atoi(argv[1]);
  
   cout << "deck size       shuffle count" << endl;
   cout << "------------------------------" << endl;
 
   a = 1;
   while(a < one){
	count = 0;
	D.clear();
	E.clear();
	int b = 0;
	while(b < a){
		D.insertBefore(b);
		E.insertBefore(b);
		b++;
	}
	check = 1;
	
	while(!D.equals(E) || check == 1){
		check = 0;
		count++;
		shuffle(D);
	}
	cout << " " << a << "\t\t " << count << endl;
   }
   return(0);
}
