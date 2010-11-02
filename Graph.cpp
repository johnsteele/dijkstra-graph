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

#include "Graph.h"


//========================Default-Constructor=========================
// Creates a Graph object with default values. 
// 
// Preconditions: None.
//		
// Postconditions: this Graph object is instantiated with 
//    		   default values. 
//====================================================================
Graph::Graph ()
{	
	// Initialie the table. 
	init_table (); 
	// Start with zero vertices in the graph.
	my_size = 0;	
}


//========================Copy-Constructor============================
// Creates a Graph object with the specified values set to the values
// of the given Graph object.
// 
// Preconditions: the_other Graph object is not null, and has all 
//		  correct invariance of a Graph object.
//		
// Postconditions: this Graph object is instantiated with its data
//		   members set to the_other's. 
//====================================================================
Graph::Graph (const Graph &the_other)
{
	
}


//========================Destructor==================================
// Deallocates all resources obtained by this graph.
// 
// Preconditions: None.
//		
// Postconditions: All resources have been released. 
//====================================================================
Graph::~Graph ()
{
	
}


//========================init_table==================================
// Initializes the table of shortes paths.
// 	1.) Sets visited to false.
//	2.) Sets the initial distance to -1.
//	3.) Sets previous vertex to zero.
// 
// Preconditions: None.
//		
// Postconditions: The table has been initialized.
//====================================================================
void Graph::init_table ()
{
	int row, col;
	for (row = 1; row <= MAX_VERTICES; row++) {
		for (col = 0; col < MAX_VERTICES; col++) {
			my_table [row][col].isVisited   = false;
			my_table [row][col].distance    = -1;
			my_table [row][col].prev_vertex = 0;
		}
	}
}


//========================buildGraph==================================
// Builds this graph using the provided file ifstream. 
//
// The format of the stream should be as follows: 
//	- The first line is the number of vertices.  
//	- Flollowing is a text description for each vertex.  
//	  (One description per line, and 50 chars max length)
//	- After that, each line has 3 ints representing an edge.
//	  (first int is from, second int is to, third int is weight) 
//	- A zero for the first int of the three signals end of data. 
// 
// Preconditions: The input file stream should be open. It should be
//		  properly formatted, and be organize as described 
//		  above. 
//		
// Postconditions: The graph is built using the data from the provided
//		   stream.
//====================================================================
void Graph::buildGraph (ifstream &infile)
{
	int cur, src, dest, cost;	
	Object     *vertex_data;

	// GET SIZE 
	infile >> my_size;	

	if (infile.eof()) return;
	infile.ignore(); // Throw away '\n'.			

	// GET VERTEX DESCRIPTION
	for (cur = 1; cur <= my_size; cur++) { 
		vertex_data = new Object ();
		vertex_data->setData (infile);

		// SET VERTEX DATA.  
		my_vertices [cur].data = vertex_data;
		my_vertices [cur].edgeHead = NULL; 
		my_size++;			
	}	

	// FILL COST EDGE ARRAY	
	src = dest = cost = 1;
	for (;;) {
		infile >> src >> dest >> cost;
		if (src == 0 || infile.eof()) break;
		insertEdge (src, dest, cost);	
	}	
}


//========================insertEdge==================================
// Inserts an edge into this graph. Inserting this edge must not
// exceed the max of 100 edges. The first int is the from vertex, the
// second is the to vertex, and the third int is the weight of the 
// edge. 
// 
// Preconditions: The vertices must exist in the graph. Adding the
//		  edge must not exceed the max edges of	100. 
//		
// Postconditions: Returns true if the edge was inserted into the
//		   graph, false otherwise.
//==================================================================== 
bool Graph::insertEdge (int the_from_v, int the_to_v, int the_weight)
{
	EdgeNode *edge_node, *cur;

	// Ensure vertices are within range, and non negative weight.
	if (the_from_v < 1 || the_from_v > my_size || 
		the_to_v < 1 || the_to_v > my_size || 
			the_weight < 0) return false;		

	// Setup the new edge.
	edge_node            = new EdgeNode;
	edge_node->weight    = the_weight;
	edge_node->adjVertex = the_to_v;

	// Is it the first edge being added.
	if (my_vertices [the_from_v].edgeHead == NULL) { 
		// Link it in as our head.
		edge_node->nextEdge = NULL;
		my_vertices [the_from_v].edgeHead = edge_node;
	}
	
	else {
		// First check for a duplicate.
		cur = my_vertices [the_from_v].edgeHead;
		while (cur != NULL) {
		 	if (cur->adjVertex == the_to_v) {
				// We have a duplicate, update weight. 
				cur->weight = the_weight;	
				delete edge_node;
				return true;		
			} 	
			cur = cur->nextEdge;	
		}
	
		// Not a duplicate, so link it in as our new head.
		edge_node->nextEdge = my_vertices [the_from_v].edgeHead;
		my_vertices [the_from_v].edgeHead = edge_node;
	} 
	return true;
}


//========================removeEdge==================================
// Removes an edge from the graph. The first provided int is the from
// vertex, and the second int is the to vertex. 
// 
// Preconditions: The edge must exist. The from vertex and to vertex
//		  must exist.
//		
// Postconditions: Returns true if the edge was removed, returns false
//		   otherwise.
//==================================================================== 
bool Graph::removeEdge (int the_from_v, int the_to_v) 
{
	EdgeNode *cur, *prev;

	// Ensure vertices are within range.
	if (the_from_v < 1 || the_from_v > my_size || 
		the_to_v < 1 || the_to_v > my_size) return false;		

	cur = prev = my_vertices [the_from_v].edgeHead; 	
	
	if (cur != NULL) {
		if (cur->adjVertex == the_to_v) {
			// We found the edge, link prev to next.
			prev->nextEdge = cur->nextEdge;	
			delete cur;	
			cur->nextEdge = NULL;
			return true;			
		}	
		prev = cur;
		cur  = cur->nextEdge;	
	} 
	return false;
}


//========================findShortestPath============================
// Finds the shortest path between all vertices in the graph.  
// 
// Preconditions: The graph is built.
//		
// Postconditions: The shortest paths between all the vertices have
//		   been found. 
//==================================================================== 
void Graph::findShortestPath ()
{
	run_dijkstra (1);
}


//========================run_dijkstra================================
// Finds the shortest path for each of the vertices in the graph to
// all the other vertices.
// 
// Preconditions: The graph is built and init_table is needed
//		  to initialize the table
// 		  		
// Postconditions: The shortest paths for each of the vertices
//		   in the graph have been found.
//==================================================================== 
void Graph::run_dijkstra (int the_source) 
{
	// Used for traversing vertex edges.
	EdgeNode *edge;

	// The current vertex, current distance, and edge weight .
	int vertex, distance, weight; 
	int count;
	count = my_size;
 
	// A queue for 
	queue<int> Q;

	// Initialize the table.
	init_table();

	// Distance from source to source is zero.
	my_table [the_source][the_source].distance    = 0;
	my_table [the_source][the_source].prev_vertex = the_source; 


	while (count > 0) {
		// Get the vertex associated with the shortest distance. 	
		vertex = find_and_visit_minimum (the_source);
		if (vertex == -1) break;		

		// Get the first edge of the vertex.
		edge = my_vertices[vertex].edgeHead;	

		while (edge) {	
			
			// If the shortest path to the adjacent vertex hasn't been found. 	
			if (!my_table[the_source][edge->adjVertex].isVisited) {

				// Get the weight of the edge. 	
				weight = edge->weight;
	
				// If this is the fist time adding a distance to this vertex.	
				if (my_table[the_source][edge->adjVertex].distance == -1) {
					my_table[the_source][edge->adjVertex].distance = 
						weight + my_table[the_source][vertex].distance;
						// It's shortest path has been updated.
						my_table[the_source][edge->adjVertex].prev_vertex = vertex;
						// Add it to the queue.
						//Q.push (my_table[the_source][edge->adjVertex].distance);
				}
				
				else { // Otherwise, get the distance and compare it to its' current.
					distance = weight + my_table[the_source][vertex].distance;
					// If the new distance is shorter than the current, update it.	
					if (distance < my_table[the_source][edge->adjVertex].distance) {
						my_table[the_source][edge->adjVertex].distance = distance;
						// It's shortest path has been updated.
						my_table[the_source][edge->adjVertex].prev_vertex = vertex;
					}
					// It should already be on the queue.
				} 
			} 
			// Now move to the next edge. 
			edge = edge->nextEdge;
		} // end while(edge) 
		count--;
	} // end while (count > 0)	
}


//========================find_and_vist_minimum=======================
// Finds and returns the vertex with the minimum distance from the 
// vertices that have not yet been visited within my_table
//
// It then marks the returned vertex as being visisted.
//
// Preconditions:  my_table needs to have all vertices that have not
//		   been visisted set to false. The distance of each 
//		   vertex in my_table need to be set to -1 if a
//		   distance has not yet been assigned. the_source
//		   needs to be a valid index of my_table.
//		    	  		  		
// Postconditions: Returns the vertex with the shortest distance 
//		   from the vertex that has not yet been visited.
//==================================================================== 
int Graph::find_and_visit_minimum (int the_source)
{
	int i;
	int distance;
	int vertex;
	vertex   = 0;
	distance = INT_MAX;

	for (i = 1; i <= my_size; i++) {
		// If it's not visited, and has a distance already 
		// assigned, and its distance is shorter than 
		// the current distance we have stored.
		if (!my_table[the_source][i].isVisited && 
		    my_table[the_source][i].distance != -1 &&
		    my_table[the_source][i].distance < distance) {
			distance = my_table[the_source][i].distance;
			vertex = i;
		}
	}

	if (vertex == 0) {
		return -1;
	}  else  {
		my_table[the_source][vertex].isVisited = true; 
		return vertex; 
	}
}


//========================displayAll==================================
// Displays the entire graph. Prints out the vertices description, the
// edges associated with the vertices, and the edge weights. 
// 
// Preconditions: The graph must have already built. 
//		
// Postconditions: A detailed graph is desplayed showing all the 
//		   vertices, the edges, and weights. 
//==================================================================== 
void Graph::displayAll ()
{
	
}


//========================display=====================================
// Displays the path from the first int to the second int. The ints
// represents vertices in the graph, so they must exist. Prins out the
// vertices description, the edges associated with the vertices, and
// the edge weights. 
// 
// Preconditions: The provided vertices must exist.
//		
// Postconditions: A detailed graph is displayed showing all the 
//		   vertices, their description, edges, and weights. 
//==================================================================== 
void Graph::display(int the_start_v, int the_finish_v)
{

} 

