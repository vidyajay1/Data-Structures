Vidya Jayaraman
vijayara
PA3
CS101

Makefile
List.c
List.h
Digraph.c
Digraph.h
DigraphProperties.c
Makefile
README

For the getCountSCC function, I performed DFS on Digraph G and computed the finishing times 
for each of the vertices in sorted order from least to greatest. Then I transposed the graph 
by reversing the edges in Digraph G and creating a new Digraph T. I performed DFS on Digraph 
T iterated through each of the vertices in order of the greatest finish time. I kept track of 
each of the SCCs by incrementing the counter variable and returning the value from this counter 
variable. 

For getNumSCCVertices function, I used the same DFS and transpose functions as the getCountSCC 
function. But whe it performed DFS on the transposed graph, I didn't just increment the counter 
variable to get the number of SCCs, but I also created a list of array that kept track of which vertices 
were in each SCC by appending these vertices to the list at the end of the DFS. I then iterated through
this list of arrays and compared each value to the integer u that was passed into the Digraph. If this value was 
the same, then I would return the length of this list that contained all the vertices in the SCC that u
was also in. Otherwise, I would return -1, since u was not in any of the SCCs. 

For inSameSCC, I used the same DFS, tranpose and second DFS functions as getNumSCCVertices. But I also had 
to check for v when I iterated through the list of arrays that contained each of the SCCs. So, I had a counter
variable that checked to see if v was also in the same list as u. If u was in the list, then count would increment by 
1. If v was in the list, then count would increment by 1. If count was 2, then u and v were in the same list and I would
return 1. Otherwise, I would return 0. 

Each of these functions take time O(n+m) because DFS takes O(n+m), iterating through each of the numVertices to get the 
transpose takes O(m), and doing DFS again takes O(n+m). The extra methods of iterating through the list still takes O(n),
since it also just iterates through all the vertices. By simplifying these runtimes, it just gives O(n+m), since the constants
do not matter. 

Since I am calling the functions unnecessarily (such as when the directed graph does not change), this makes the 
algorithm inefficient. 
