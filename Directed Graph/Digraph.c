// Vidya Jayaraman
// vijayara
// PA4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Digraph.h"



struct DigraphObj {
	List *adjacency; //array of List: contains neighbors for a particular vertex
	//(depending on the jth element
	int numVertices; //number of vertices in Graph
	int numEdges; //number of edges in graph (size of graph)
	int *marks; //UNVISITED, INPROGRESS, ALLDONE
	//  List *n;
	int* parent;  //keeps track of the parent vertex during DFS
	int* distance; //keeps track of the distance between two vertices
	int time;      //keeps track of the times of each of the vertices
	List finish;   //keeps track of the finish time of each of the vertices
	List* num;     //keeps track of which vertex is in which SCC


}

DigraphObj;


// Returns a Graph that points to a newly created GraphObj representing a graph which has
// n vertices and no edges.


Digraph newDigraph(int numVertices){
	Digraph graph = malloc(sizeof(struct DigraphObj));
	//const size_t size = sizeof(struct GraphObj);
	//Digraph graph = (struct DigraphObj*) malloc(size);
	graph->marks = calloc( (numVertices +1), sizeof(int));
	graph->adjacency = calloc((numVertices + 1), sizeof(List));
	//graph->n = malloc((numVertices + 1), sizeof(List)));
	graph->parent = calloc((numVertices + 1), sizeof(List));
	graph->distance = calloc((numVertices + 1), sizeof(List));
	//graph->finish = malloc(sizeof(List)*(numVertices+1));	
	graph->num = calloc((numVertices + 1), sizeof(List));
	//G->time = 0;

	//  graph->adjacency = calloc(n+1, sizeof(List));
	//graph->marks = calloc(n+1, sizeof(int));
	graph->numVertices = numVertices;
	graph->numEdges = 0;
	graph->finish = newList();
	graph->time = 0;
	int j = 0;
	for(j = 0; j<(numVertices+1); j++) {
		graph->adjacency[j] = newList();
		graph->marks[j] = UNVISITED; //2 for unvisited
		// graph->n[j] = newList();
		graph->parent[j] = NIL;
		graph->distance[j] = INF;
		//  graph->time[j] = 0; 
		graph->num[j] = newList();

	}


	return graph;
}



// Frees all dynamic memory associated with its Graph* argument, and sets
// *pG to NULL.


void freeDigraph(Digraph *pG) {
	Digraph graph = *pG;

	//if(pG != NULL && *pG != NULL){
		int j = 0;

		//printf("Hi");
		for(j = 0; j< getOrder(graph)+ 1; j++){
			// printf("%d\n", length(graph->adjacency[j]));
			//   free(graph->adjacency[j]);
                        freeList(&(*pG)->num[j]);
			freeList(&(*pG)->adjacency[j]);
			// free((graph)->adjacency[j]);
			// free(&(graph)->marks[j]);
		}
		//                free(graph->num) = NULL;
		//    free(graph->new);
		free(graph->parent);
		free(graph->distance);
		//freeList(*graph->finish);		
		//        free(graph->adjacency);
		free(graph->marks);
		free(graph->adjacency);
		free(graph->num);
		free(graph->finish);
	        //free(graph->time);
	 	//graph->adjacency = NULL;
		//graph->num = NULL;
		//graph->marks = NULL;
		free(*pG);
		*pG = NULL;
		//pG = NULL;

	//}
}

// Returns the order of G, the number of vertices in G.
int getOrder(Digraph G){
	if(G == NULL){
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	return G->numVertices;
}

int getSize(Digraph G){
	// Returns the size of G, the number of edges in G.
	if(G == NULL){
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	return G->numEdges;
}
int getOutDegree(Digraph G, int u){
	// Returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such
	// that (u, v) is an edge in G. Returns -1 if v is not a legal vertex.
	if(u < 1 || u > G-> numVertices ){
		return -1;
	}
	else{
		return length(G->adjacency[u]);

	}
}

List getNeighbors(Digraph G, int u){
	// Returns a list that has all the vertices that are neighbors of u. There is no input operation
	// that corresponds to getNeighbors.
	if(u < 1 || u > G->numVertices) {
		printf("Graph Error; calling getNeighbors() on NULL Graph reference\n");
	}
	return (G->adjacency[u]);
}

//sorts the edges before adding them to the graph
void Sort(Digraph G, List L, int v){
	if(length(L)== 0){
		append(L, v);
		G->numEdges++;

	}
	Node front = getFront(L);
	while(front != NULL){ 
		int temp = getValue(front);
		if(temp == v){
			return;
		}
		if (temp > v) {
			insertBefore(L, front, v);
			G->numEdges++; 
			return;
		}
		front = getNextNode(front);
	}
	append(L, v);
	G->numEdges++;
	return;
}  

int addEdge(Digraph G, int u, int v){
	// Adds v to the adjacency list of u, if that edge doesn’t already exist.
	// If the edge does already exist, does nothing. Used when edges are entered or added.
	// Returns 0 if (u, v) is a legal edge, and the edge didn’t already exist.
	// Returns 1 if (u, v) is a legal edge and the edge did already exist.
	// Returns -1 if (u, v) is not a legal edge.


	if(G == NULL) {
		printf("Graph error: calling addEdge() on NULL Graph reference\n");
		exit(1);
	}
	if(u <= 0 ||  u >G-> numVertices){
		return -1;
	}
	if(v <= 0 || v >G-> numVertices){
		return -1;
	}
	else{
		List temp = G->adjacency[u];
		Node front = getFront(temp);
		for(int j = 0; j < length(temp); j++) {
			if(getValue(front) == v){

				return 1;
			}

			front = getNextNode(front);
		}
		List L = G->adjacency[u];
		Sort(G, L, v);
		//	append(G->adjacency[u], v);
		//	G->numEdges++;

		return 0;


	}
}

int deleteEdge(Digraph G, int u, int v) {
	// Deletes v from the adjacency list of u, if that edge exists.
	// If the edge doesn’t exist, does nothing. Used when edges are deleted.
	// Returns 0 if (u, v) is a legal edge, and the edge did already exist.
	// Returns 1 if (u, v) is a legal edge and the edge didn’t already exist.
	// Returns -1 if (u, v) is not a legal edge.

	if(G == NULL) {
		printf("Graph error: calling addEdge() on NULL Graph reference\n");
		exit(1);
	}

	if(u <= 0 ||  u >G-> numVertices){
		return -1;
	}
	if(v <= 0 || v >G-> numVertices){
		return -1;
	}
	else{
		List adj = G->adjacency[u];
		Node front = getFront(adj);
		for(int j = 0; j < length(adj); j++) {
			if(getValue(front) == v){
				deleteNode(G->adjacency[u], front);
				// deleteNode(G->adjacency[v], u);
				G->numEdges--;
				return 0;

			}
			front = getNextNode(front);
		}
		return 1;

	}
}


void unvisitAll(Digraph G){
//unvisits all the vertices
	if(G == NULL ){
		printf("Graph error: calling unvisitAll() on NULL Graph reference/n");
		exit(1);
	}
	for(int j = 0; j< (G->numVertices); j++){
			G->marks[j] = UNVISITED;
		}
	

}

// Marks all vertices of the graph as UNVISITED.
int getMark(Digraph G, int u) {
	return (G->marks[u]);
}

// Returns the mark for vertex u, which will be UNVISITED, INPROGRESS or ALLDONE.
void setMark(Digraph G, int u, int theMark) {
	// Sets the mark for vertex u to be theMark.
	// theMark must be UNVISITED, INPROGRESS or ALLDONE
	G->marks[u] = theMark;
}

void printDigraph(FILE* out, Digraph G) {
	// Outputs the digraph G in the same format as an input line, including the number of vertices
	// and the edges. The edges should be in sorted order, as described above.
	if(G == NULL){
		printf("Graph Error: calling printGraph() on NULL Graph reference\n");
		exit(1);
	}
	int k = 0;
	int j = 0;
	fprintf(out,"%d", G->numVertices);
	for( j = 0; j<= G-> numVertices; j++){
		List temp = G->adjacency[j];
		Node curr = getFront(temp);
		/*
		   if(temp == 0 || temp == NULL){
		   break;
		   }
		 */
		for( k = 0; k< (length(temp)); k++) {
			fprintf(out, ", ");
			fprintf(out, "%d", j);
			fprintf(out," %d", getValue(curr));
			curr = getNextNode(curr);
		}
	}
}
Digraph transpose( Digraph G){
	//reverses all the edges in the Digraph G

	if(G== NULL){
		fprintf(stdout, "Invalid: cannot call transpose");
		exit(1);
	}
	Digraph T = newDigraph(G->numVertices);
	int i = 0;
	int u = 0;
	for( i = 1; i<= G->numVertices; i++){
		List adj = G->adjacency[i];
		Node node = getFront(adj);	
		while(node != NULL){
			u = getValue(node);
			addEdge(T, u,  i);		
			node = getNextNode(node);
		}
	}
	return T;
}

//perform DFS a second time to keep count of all the SCCs
void Visited(Digraph G, int u) {
	//        G->time++;
	G->distance[u] = G->time;
	G->marks[u] = INPROGRESS;
	int v = 0;

	List adj = G->adjacency[u];
	Node front = getFront(adj);
	//v = getValue(front);
	for(int i = 0; i<length(adj); i++){
		v = getValue(front);
		/* if(G->marks[v] == INPROGRESS){
		   count++;
		   }
		 */
		if(G->marks[v] == UNVISITED){
			G->parent[v] = u;
			Visit(G, v);
		}
		front = getNextNode(front);

	}
	G->marks[u] = ALLDONE;

}

int DFSagain(Digraph T, Digraph G){
	//DFS to get append each vertex to the appropriate SCC
	for(int i = 1; i<T->numVertices; i++){
		T->marks[i] = UNVISITED;
		T->parent[i] = NIL;
	}
	int count = 0;   
	List finished = G->finish;
	Node front_fin = getFront(finished);
	int v = 0;
	for(int i = 0; i<length(finished); i++){
		v = getValue(front_fin);          
		if(T->marks[v] == UNVISITED){
			Visited( T, v);
			count++;
		}
		front_fin = getNextNode(front_fin);
	}
	return count;
}
//DFS calls this to keep track of all the finish times
void Visit(Digraph G, int u) {
	G->time++;
	G->distance[u] = G->time;
	G->marks[u] = INPROGRESS;
	int v = 0;
	List adj = G->adjacency[u];
	Node front = getFront(adj);
	//v = getValue(front);
	for(int i = 0; i<length(adj); i++){
		v = getValue(front);
		/* if(G->marks[v] == INPROGRESS){
		   count++;
		   }
		 */
		if(G->marks[v] == UNVISITED){
			G->parent[v] = u;
			Visit(G, v);
		}
		front = getNextNode(front);

	}
	G->marks[u] = ALLDONE;
	prepend(G->finish, u);	  
	//printList(stdout, G->finish);	

}

//perform DFS to keep track of all the finish times
void DFS(Digraph G){
	//DFS to get finish times for each vertex
	for(int i = 1; i<G->numVertices; i++){
		// G->marks[i] = UNVISITED;
		G->marks[i] = UNVISITED;   
		G->parent[i] = NIL;
	}
	for(int i = 1; i<G->numVertices; i++){     
		if(G->marks[i] == UNVISITED){
			Visit(G, i);
		}
	}
}
// Returns the number of Strongly Connected Components in G. 
int getCountSCC(Digraph G){
	DFS( G);
	Digraph T = transpose(G);
	int count = DFSagain(T, G);
	return count;

}
//this will keep track of which SCC each vertex is in 
void VisitU(Digraph G, int u, int count) {
	G->marks[u] = INPROGRESS;
	int v = 0;

	List adj = G->adjacency[u];
	Node front = getFront(adj);
	for(int i = 0; i<length(adj); i++){
		v = getValue(front);

		//if(G->marks[v] == INPROGRESS){
		//           count++;
		//   }

		if(G->marks[v] == UNVISITED){
			G->parent[v] = u;

			VisitU(G, v, count);
		}
		front = getNextNode(front);

	}
	G->marks[u] = ALLDONE;
	// count++;
	append(G->num[count], u); 


}
//perform DFS to iterate through all the vertices to know which ones belong 
//in which SCC
int DFSNum(Digraph T, Digraph G, int u ){
	for(int i = 1; i<T->numVertices; i++){
		T->marks[i] = UNVISITED;
		T->parent[i] = NIL;
	}
	int count = 0;
	//int num;
	List finished = G->finish;
	Node front_fin = getFront(finished);
	int v = 0;
	for(int i = 0; i<length(finished); i++){
		v= getValue(front_fin);
		if(T->marks[v] == UNVISITED){
			VisitU( T, v, count);
			count++;
		}
		front_fin = getNextNode(front_fin);
	}
	//printf("%d", count);
	return count;
}

// Returns the number of vertices (including u) that are in the same Strongly Connected Component
// as u in G.. Returns -1 if u is not a legal vertex. 
int getNumSCCVertices(Digraph G, int u){
	DFS(G);
	Digraph T = transpose(G);
	int count = DFSNum(T, G, u);
	int i = 0;
	int j = 0;
//	List temp = T->num[i];
//	Node front = getFront(temp);
//	front = getFront(temp);

	//int size = sizeof(G->num)/sizeof(G->num[j]);

	for(i = 0; i<count; i++) {
		Node n = getFront(T->num[i]);
		for(j = 0; j<length(T->num[i]); j++){
			int v =  getValue(n);
			n = getNextNode(n);         
			if(v == u){
				return length(T->num[i]);
			}



		}
	}
	return -1;
}

// Returns 1 if u and v are in the same Strongly Connected Component of G, and returns 0 if u and v
// are not in the same Strongly Connected Component of the current digraph.
// A vertex is always in the same Strongly Connected Component as itself.
// Returns -1 if u or v is not a legal vertex.
int inSameSCC(Digraph G, int u, int v){
	DFS(G);
	Digraph T = transpose(G);
	int count = DFSNum(T, G, u);
	int i = 0;
	int j = 0;
	//int check = 0;
	for(i = 0; i<count; i++) {

		Node n = getFront(T->num[i]);
		// while(n != NULL)
		int check = 0;
		for(j = 0; j<length(T->num[i]); j++){
			int y =  getValue(n);   
			// n = getNextNode(n);
			if(v == y){
				check++;
			}
			if(u == y){
				check++;
			}
			if(check == 2){

				return 1;
			}
			n = getNextNode(n);
		}
	}
	return 0;
}
