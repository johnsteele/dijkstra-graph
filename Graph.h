class Graph {                            
public:
 
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
		
    int size;					// number of vertices in the graph
    Table T[MAX_VERTICES][MAX_VERTICES];	// stores visited, distance, path -
						// two dimensional in order to solve
						// for all sources
};

