#include<stdio.h>
#include<stdlib.h>
#include "Digraph.h"

int main(int argc, char* argv[]){

	Digraph A = newDigraph(5);
//List s = newList();
addEdge(A, 2, 1);
addEdge(A, 1, 3);
addEdge(A, 3, 2);
addEdge(A, 1, 4);
addEdge(A, 4, 5);




//	addEdge(A, 1, 3);
//	addEdge(A, 2, 4);
//addEdge(A, 3, 1);
//		addEdge(A, 3, 2);
//	addEdge(A, 4, 1);
//	addEdge(A, 1, 2);
//	addEdge(A, 0, 5);
//	deleteEdge(A, 3, 2);
/*List temp = A->adjacency[2];
Node front = getFront(temp);
for(int i = 0; i < length(temp); i++) {
    printf("%d", getValue(front));
    front = getNextNode(front);
}
*/
	unvisitAll(A);
	printf("mark1 = %d\n", getMark(A, 1));
	printf("mark2 = %d\n", getMark(A, 2));
	printf("mark3 = %d\n", getMark(A, 3));
	printf("mark4 = %d\n", getMark(A, 4));

	setMark(A, 1, ALLDONE);
	printf("mark1 = %d\n", getMark(A, 1));
	setMark(A, 2, INPROGRESS);
	printf("mark2 = %d\n", getMark(A, 2));

	List ListTest = getNeighbors(A, 3);
	printList(stdout, ListTest);printf("\n");
	int IntTest = getOutDegree(A, 2);
	printf("Neighbor Count: %d\n", IntTest);

	int GraphSize = getSize(A);
	printf("Graph Size: %d\n", GraphSize);

	int GraphOrder = getOrder(A);
	printf("Graph Order: %d\n", GraphOrder);
	
	unvisitAll(A);
	//int distance = distance(A, 4, 3);
	//printf("Distance: %d\n", distance(A, 4, 3));
//int DFS = DFS(A, s);
//printf("DFS: %d", DFS);
//printf("DFS");
//DFS(A);
//printf("transpose \n");
// transpose(A);
//printf("\n");


int getCount = getCountSCC(A);
printf("# of SCCs: %d\n", getCount);
/*int getNum = getNumSCCVertices(A, u);
printf("# of vertices in SCC: %d\n", getNum);
int sameSCC = inSameSCC(A, u, v);
printf("Same SCC: %d\n", sameSCC); 
*/
printDigraph(stdout, A);printf("\n");
//	freeDigraph(&A);
}

