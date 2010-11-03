//====================================================================
// Graph.h 
//  
// This class represents a Graph that is implemented using an 
// adjacency list. A graph can not have more than 100 edges. 
// The entire graph can be displayed or a specific path can be 
// displayed. 
// 
// Author: John Steele <steelejr@u.washington.edu> 
// Date  : 2010/11/02
// Class : CSS 343 - Lab 3
//====================================================================
// Graph class: 
//   Includes following features:
// 	- allows building a graph. 
//	- allows inserting an edge into the graph.
//	- allows removing  an edge from the graph.
//	- allows finding the shortest (lowest cost) path. 
//	- allows displaying the graph.
//	- allows dislplaying the graph from one vertex to another. 
// Assumptions:
// 	- input is properly formatted. 
//	- description of each vertex is no longer than 50 characters.
//	- each line following the description contains three ints
//	  representing an edge. 
//	- a zero for the first integer signals the end of the data. 
//==================================================================== 

#ifndef _GRAPH_H
#define _GRAPH_H
#include "Object.h" // Vertex data.
#include <iostream>  
#include <iomanip>
#include <fstream>
#include <queue>
#include <limits.h>
using namespace std;

class Graph {   
                         
public:

	//========================Default-Constructor=================
	// Creates a Graph object with default values. 
	// 
	// Preconditions: None.
	//		
	// Postconditions: this Graph object is instantiated with 
	//    		   default values. 
	//============================================================ 
	Graph ();


	//========================Copy-Constructor====================
	// Creates a Graph object with the specified values set to 	
	// the values of the given Graph object.
	// 
	// Preconditions: the_other Graph object is not null, and has
	// 		  all correct invariance of a Graph object.
	//		
	// Postconditions: this Graph object is instantiated with
	// 		   its data members set to the_other's. 
	//============================================================ 
	Graph (const Graph &);


	//========================Destructor==========================
	// Deallocates all resources obtained by this graph.
	// 
	// Preconditions: None.
	//		
	// Postconditions: All resources have been released. 
	//============================================================ 
	~Graph ();


	//========================buildGraph==========================
	// Builds this graph using the provided ifstream. 
	//
	// The format of the stream should be as follows: 
	//	- The first line is the number of vertices.  
	//	- Flollowing is a text description of each vertex.  
	//	  (One description per line, and 50 chars max lenght)
	//	- After that, each line has 3 ints rep. an edge. 
	//	- A zero for the first int signals end of data. 
	// 
	// Preconditions: The input must be properly formatted, and 
	// 		  be organize as described above. 
	//		
	// Postconditions: The graph is built using the data from 
	//		   the provided stream.
	//============================================================ 
	void buildGraph (ifstream &);


	//========================insertEdge==========================
	// Inserts an edge into this graph. Inserting this edge must 
	// not exceed the max of 100 edges. The first int is the from
	// vertex, the second is the to vertex, and the third int is
	// the weight of the edge. 
	//
	// If an edge is inserted, the findShortestPath method is ran
	// to prevent a display of data that is not up to date.
	// 
	// Preconditions: The vertices must exist in the graph. Adding
	//		  the edge must not exceed the max edges of 	
	//		  100. 
	//		
	// Postconditions: Returns true if the edge was inserted into
	//	 	   the graph, false otherwise.
	//============================================================ 
	bool insertEdge (int, int, int);


	//========================removeEdge==========================
	// Removes an edge from the graph. The first provided int is
	// the from vertex, and the second int is the to vertex.  
	//		
	// If an edge is removed, the findShortestPath method is ran
	// to prevent a display of data that is not up to date.
	// 
	// Preconditions: The edge must exist. The from vertex and to
	// 		  vertex must exist.
	//		
	// Postconditions: Returns true if the edge was removed, 	
	//		   false otherwise.
	//============================================================ 
	bool removeEdge (int, int);


	//========================findShortestPath====================
	// Finds the shortest path between all vertices in the graph.  
	// 
	// Preconditions: The graph is built.
	//		
	// Postconditions: The shortest paths between all the vertices
	//		   have been found. 
	//============================================================ 
	void findShortestPath ();


	//========================displayAll==========================
	// Displays the entire graph. Prints out the vertices
	// description, the edges associated with the vertices, and
	// the edge weights. 
	// 
	// Preconditions: The graph must have already built. 
	//		
	// Postconditions: A detailed graph is desplayed showing all
	//		   the vertices, the edges, and weights. 
	//============================================================ 
	void displayAll ();


	//========================display=============================
	// Displays the path from the first int to the second int. 
	// The ints represents vertices in the graph, so they must 
	// exist. Prins out the vertices description, the edges 
	// associated with the vertices, and the edge weights. 
	// 
	// Preconditions: The provided vertices must exist.
	//		
	// Postconditions: A detailed graph is displayed showing all
	//		   the vertices, their description, the edges, 
	//	       	   and weights. 
	//============================================================ 
	void display (int, int);


private:

	// Maximum number of vertices allowed in a graph. 
	static const int MAX_VERTICES = 101; // Not using index 0.


	// A struct to represent an edge in the graph.
	struct EdgeNode {		
		// The subscript of the adjacent vertex. 
		int adjVertex;     	
		// The weight of the edge. 
		int weight;      
		// A link to the next edge.
  		EdgeNode *nextEdge;
	};


	// A struct to represent a vertex in the graph. 
	struct VertexNode {
		// The head of the list of edges.
		EdgeNode *edgeHead;		
		// The vertex data.
		Object *data;			
	};


	// The array of VertexNodes in this graph.
	VertexNode my_vertices [MAX_VERTICES];

	// The number of vertices in this graph.
	int my_size;				


	// A table to store information for Dijkstra's algorithm
	struct Table {
		// A flag to mark if the  vertex has been visited.
		bool isVisited;	
		// The shortest known distance from source vertex.
		int distance;
		// The previous vertex in optimal path from source.
		int prev_vertex;
	};

	// The table that stores: visited, distance, and path. 
	// It's two dimensional in order to solve shortest path 	
	// for all vertices in the graph.
    	Table my_table [MAX_VERTICES][MAX_VERTICES];	


	//========================init_table==========================
	// Initializes the table of shortes paths.
	// 	1.) Sets visited to false.
	//	2.) Sets the initial distance to -1.
	//	3.) Sets previous vertex to zero.
	// 
	// Preconditions: None.
	//		
	// Postconditions: The table has been initialized.
	//============================================================ 
	void init_table ();


	//========================run_dijkstra========================
	// Finds the shortest path for each of the vertices in the 
	// graph to all the other vertices.
	// 
	// Preconditions: The graph is built and init_table is needed
	//		  to initialize the table.
	// 		  		
	// Postconditions: The shortest paths for each of the vertices
	//		   in the graph have been found.
	//============================================================ 
	void run_dijkstra (int);


	//========================find_and_vist_minimum===============
	// Finds and returns the vertex with the minimum distance from
	// the vertices that have not yet been visited within my_table
	//
	// It then marks the returned vertex as being visisted.
	//
	// Preconditions:  my_table needs to have all vertices that 
	//		   have not been visisted set to false. 	
	// 		   The distance of each vertex in my_table 
	//		   need to be set to -1 if a distance has 
	//		   not yet been assigned.
	//		    	  		  		
	// Postconditions: Returns the vertex with the shortest
	//		   distance from the vertex that has not yet
	//		   been visited.
	//============================================================ 
	int find_and_visit_minimum (int);


	//========================display_helper======================
	// A recursive helper method for displaying shortest paths.
	// 
	// Preconditions:  my_table is up to date. Otherwise the 
	//		   path might not print correctly. 
	// 		  		
	// Postconditions: The shortest path from the_source to 
	//		   the_last has been printed to the output
	//		   stream. 
	//============================================================ 
	void display_helper (int, int, int);

	//========================delete_vertices=====================
	// A helper method for the deconstructor. It deletes all 
	// dynamic memory within my_vertices.  
	// 
	// Preconditions: my_size is set to the number of vertices
	//		  in the graph.
	//		  		  		
	// Postconditions: All dynamic memory has been deleted from 	
	//		   my_vertices.
	//============================================================ 
	void delete_vertices (); 
	
	//========================print_vertices======================
	// A helper method for displaying the descriptions of	
	// vertices.
	// 
	// Preconditions: my_table is up to data.
	//		  		  		
	// Postconditions: The descriptions are printed to output.
	//============================================================ 
	void print_vertices (int, int, int); 
};
#endif /* _GRAPH_H */

