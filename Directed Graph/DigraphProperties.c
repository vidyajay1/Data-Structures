// Vidya Jayaraman
// vijayara
// PA2
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 1000
#include "Digraph.h"

void PrintDigraph(FILE *out, Digraph G){
	printDigraph(out, G);
}
int GetOrder(Digraph G){
	return getOrder(G);
}
int GetSize(Digraph G){
	return getSize(G);

}
int GetOutDegree(Digraph G, int u){
	return getOutDegree(G, u);
}
int AddEdge(Digraph G, int u, int v){
	return addEdge(G, u, v);
}
int DeleteEdge(Digraph G, int u, int v){
	return deleteEdge(G, u, v);
}

void InSameSCC(FILE* out, Digraph G,  int u, int v){
	int value = inSameSCC( G, u, v);
	//fprintf(out, "%d",  value);
	if(value == 1){
		fprintf(out, "YES");
	}
	if(value == 0){
		fprintf(out, "NO");
	}
	if(value == -1){
		fprintf(out, "ERROR");
	}
	//      fprintf(out, "%d", value);

}
void GetCountSCC(FILE* out, Digraph G){     
	int value = getCountSCC( G);
	fprintf(out,"%d", value);
}
void GetNumSCCVertices(FILE* out, Digraph G, int u){
	int value =  getNumSCCVertices(G, u);
	//        fprintf(out, "%d", value);
	if(value == -1){
		fprintf(out, "ERROR");

	}
	else{
		fprintf(out,"%d", value);
	}
	//	fprintf(out, "%d", value);

}

int main(int argc, char * argv[]){

	FILE *in, *out;
	char line[MAX_LEN];
	//   Graph tokenGraph = newGraph;
	char* token;

	// check command line for correct number of arguments
	if( argc != 3 ){
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open files for reading and writing
	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");
	if( in==NULL ){
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}
	if( out==NULL ){
		printf("Unable to open file %s for writing\n", argv[2]);
		exit(1);
	}


	fgets(line, MAX_LEN, in);
	const char needle[] = ",";
	const char space[] = "";
	char *ret;
	ret = strstr(line, space);
	int x = strtol(line, &ret, 10);
	int n = 0;
	int m = 0;
	Digraph graph = newDigraph(x);
	//addEdge(graph, n, m);
	while( ret !=NULL){
		sscanf(ret, ", %d %d",&n, &m );
		addEdge(graph, n, m);
		ret = strstr(ret+1, needle);

	}

	while(fgets(line, MAX_LEN, in) != NULL) {
		token = strtok(line, ", ");
		//test = strtok(line, ", ");

		if ((strcmp(token, "GetOrder\n")!=0) && (strcmp(token, "PrintDigraph\n")!= 0) && (strcmp(token, "GetSize\n")!= 0) && (strcmp(token, "GetOutDegree")!= 0) && (strcmp(token, "AddEdge")!= 0) && (strcmp(token, "DeleteEdge")!= 0) && (strcmp(token, "GetCountSCC\n")!=0) && (strcmp(token, "GetNumSCCVertices")!=0) && (strcmp(token, "InSameSCC")!=0)){
			//      fprintf(out, "\n");
			fprintf(out, "%s", token);
			//fprintf(out, "%s", "\n");
			fprintf(out, "ERROR");
			fprintf(out, "\n");            
		}

		else if(strcmp(token,"\n") == 0) {
			//fprintf(out, "\n");
			fprintf(out, "ERROR");
			// printf("ERROR");
			fprintf(out, "\n");
		}


		else if(strcmp(token, "PrintDigraph\n")== 0){
			fprintf(out, "%s", token);
			PrintDigraph(out, graph);
			fprintf(out, "\n");
		}

		else if(strcmp(token,"GetOrder\n") ==0){
			fprintf(out, "%s", token);
			int j = GetOrder(graph);
			//fprintf(out, "%d", j);
			fprintf(out, "%d", j);
			fprintf(out, "\n");		
		}


		else if(strcmp(token, "GetSize\n") == 0){
			//	fprintf(out, "\n");
			fprintf(out, "%s", token);
			int s = GetSize(graph);
			fprintf(out,"%d",s);
			fprintf(out, "\n");
		}



		else if(strcmp(token, "GetOutDegree") == 0){
			//	fprintf(out, "\n");
			fprintf(out,"%s", token);
			token  = strtok(NULL, "\n");

			if(token != NULL) {
				fprintf(out, "%s"," ");
				fprintf(out, "%s", token);
				fprintf(out, "\n");
				int x = atoi(token);  
				int tester = GetOutDegree(graph, x);
				if(tester == -1){
					fprintf(out, "ERROR");
				}
				else{
					fprintf(out,"%d", tester);
				}
			}
			else{
				fprintf(out, "\n");
				fprintf(out, "ERROR");
			}
			fprintf(out, "\n");		
		}



		else if(strcmp(token, "InSameSCC") == 0){
			//	fprintf(out, "\n");
			fprintf(out, "%s", token);
			char* new = 0;
			token = strtok(NULL, " ");
			new = token;
			new = strtok(NULL, "\n\r");
			if(token != NULL && new != NULL) {
				fprintf(out, "%s", " ");
				fprintf(out, "%s", token);
				fprintf(out, "%s", " ");
				fprintf(out, "%s", new);
				fprintf(out, "%s",  "\n");
				int x = atoi(token);
				int y = atoi(new);
				InSameSCC(out,  graph, x, y);
			}

			if(new == NULL) {
				fprintf(out, " ");
				fprintf(out, "%s", token);
				fprintf(out, "\n");
				fprintf(out, "%s", " ERROR");
			}
			if(token == NULL){
				fprintf(out, "\n");
				fprintf(out, "%s", " ERROR");


			}

			fprintf(out, "\n");

		}

		else if(strcmp(token, "GetCountSCC\n")== 0){
			//	fprintf(out, "\n");
			fprintf(out, "%s", token);
			GetCountSCC(out, graph);
			fprintf(out, "\n");
		}
		else if(strcmp(token, "GetNumSCCVertices") == 0){
			//	fprintf(out, "\n");
			fprintf(out,"%s", token);
			token = strtok(NULL, "\n");
			if(token != NULL) {
				fprintf(out, "%s"," ");
				fprintf(out, "%s", token);
				fprintf(out, "\n");
				int x = atoi(token);
				GetNumSCCVertices(out, graph, x);
			}
			else{
				fprintf(out, "\n");
				fprintf(out, "ERROR");
			}
			fprintf(out, "\n");		
		}



		else if(strcmp(token, "DeleteEdge") == 0){
			//     fprintf(out, "\n");
			fprintf(out, "%s", token);
			char* new = 0;    
			token = strtok(NULL, " ");
			new = token;
			new = strtok(NULL, " ");
			if(token != NULL && new != NULL) {
				fprintf(out, "%s", " ");
				fprintf(out, "%s", token);
				fprintf(out, "%s", " ");
				fprintf(out, "%s", new);
				int x = atoi(token);
				int y = atoi(new);
				int add = DeleteEdge( graph, x, y);
				if(add == -1){
					fprintf(out, "ERROR");
				}
				else{
					fprintf(out,"%d", add);
				}
			}
			if(new == NULL) { 
				fprintf(out, " ");
				fprintf(out, "%s", token);
				fprintf(out, "\n");
				fprintf(out, "%s", " ERROR");  
			}
			if(token == NULL){
				fprintf(out, "\n");
				fprintf(out, "%s", " ERROR");


			}

			fprintf(out, "\n");   
		}




		else if(strcmp(token, "AddEdge") == 0){
			// fprintf(out, "\n");
			fprintf(out, "%s", token);
			char* new = 0;
			token = strtok(NULL, " ");
			new = token;
			new = strtok(NULL, "\n\r");
			if(token != NULL && new != NULL) {
				fprintf(out, "%s", " ");
				fprintf(out, "%s", token);
				fprintf(out, "%s", " ");        
				fprintf(out, "%s", new); 
				fprintf(out, "%s",  "\n");
				int x = atoi(token);
				int y = atoi(new);
				int add = AddEdge( graph, x, y);
				if(add == -1){
					fprintf(out, "ERROR");
				}
				else{
					fprintf(out,"%d", add);
				}
			}
			if(new == NULL) {
				fprintf(out, " ");
				fprintf(out, "%s", token);
				fprintf(out, "\n");
				fprintf(out, "%s", " ERROR");
			}
			if(token == NULL){
				fprintf(out, "\n");
				fprintf(out, "%s", " ERROR");


			}
			fprintf(out, "\n");

		}
	}
	freeDigraph(&graph);    

	//         close files
	fclose(in);
	fclose(out);

	return(0);
}
