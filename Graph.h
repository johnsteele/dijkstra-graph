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

	// Use 101 as maximum, if you don't use vertex 0
	static const int MAX_VERTICES = 100;

	struct EdgeNode {			// can change to a class, if desired
		int adjVertex;			// subscript of the adjacent vertex 
		int weight;			// weight of edge
		EdgeNode *nextEdge;
	};

	struct VertexNode {
		EdgeNode *edgeHead;		// head of the list of edges
		Object *data;			// store vertex data here
	};

	// array of VertexNodes
	VertexNode vertices[MAX_VERTICES];

	// table of information for Dijkstra's algorithm
	struct Table {
		bool visited;			// whether vertex has been visited
		int dist;			// shortest known distance from source
		int path;			// previous vertex in path of min dist
	};
		
	int size;				// number of vertices in the graph
    	Table T[MAX_VERTICES][MAX_VERTICES];	// stores visited, distance, path -
						// two dimensional in order to solve
						// for all sources
};
#endif /* _GRAPH_H */
