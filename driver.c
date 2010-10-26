//---------------------------------------------------------------------------
// HW3.CPP
// Driver code for testing the Graph class.
// Authors:  Clark Olson and Carol Zander
//---------------------------------------------------------------------------
// This code tests the basic functionality of the class to
// perform Dijkstra's algorithm for CSS 343 HW 3.
// It is not meant to exhaustively test the class.
//
// Assumptions:
//   -- a text file named "HW3.txt" exists in the same directory
//      as the code and is formatted as described in the specifications
//---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include "Graph.h"
using namespace std;

//-------------------------- main -------------------------------------------
// Tests the Graph class by reading data from "HW3.txt" 
// Preconditions:   If HW3.txt file exists, it must be formatted
//                  as described in the specifications.
// Postconditions:  The basic functionalities of the Graph class 
//                  are used.  Should compile, run to completion, and output  
//                  correct answers if the classes are implemented correctly.
int main() {
   ifstream infile1("HW3.txt");
   if (!infile1) {
      cerr << "File could not be opened." << endl;
      return 1;
   }

   //for each graph, find the shortest path from every vertex to all other vertices
   for(;;){
      Graph G;
      G.buildGraph(infile1);
      if (infile1.eof()) 
         break;
      G.findShortestPath();        
      G.displayAll();              // display shortest distance, path to cout
      G.display(3,2);              // display path from vertex 3 to 2 to cout
   }

   return 0;
}


