//Vidya Jayaraman 
//vijayara
//12B
//February 27, 2018
//Dictionary.c implements ADT operations by using hash tables and hash function computes the index h(k) where a given pair(k,v) will be stored. 

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Dictionary.h"

//define TABLESIZE 101
const int tableSize = 101;

//private types
//StackObj
typedef struct StackObj{
char* key;
char* value;
}StackObj;


//Stack
typedef StackObj* Stack;

//NodeObj
typedef struct NodeObj{
Stack stack;
struct NodeObj* next;
}NodeObj;


//Node
typedef NodeObj* Node;

//constructor for the pair type
Stack newStack(char* k, char *v){
//allocate memory
Stack S = malloc(sizeof(StackObj));
assert( S!= NULL );
S->key = calloc(strlen(k)+1, sizeof(char));
S->value = calloc(strlen(v)+1, sizeof(char));
//initialize k and v 
strcpy(S->key, k);
strcpy(S->value, v);
return (S);
}


//constructor for the Node type
Node newNode(char* k, char* v){
//allocate memory 
Node N = malloc(sizeof(NodeObj));
Stack S = newStack(k, v);
assert( N != NULL && S != NULL);
//initialize node fields
N->stack = S;
N->next = NULL;
return (N);
}


//destructor for the pair type
void freeStack(Stack* pS){
if( pS != NULL && *pS != NULL){
//free memory allocated
free((*pS)->key);
free((*pS)->value);
free(*pS);
*pS=NULL;
}
}


//destructor for the Node type
void freeNode(Node* pN){
//free memory
freeStack(&(*pN)->stack);
if( pN != NULL && *pN != NULL){
free(*pN);
*pN=NULL;
}
}


//rotate_left()
//rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
int sizeInBits = 8*sizeof(unsigned int);
shift = shift & (sizeInBits - 1);
if ( shift == 0 )
   return value;
return (value << shift) | (value >> (sizeInBits - shift));
}

//pre_hash()
//turn a string into an unsigned int
unsigned int pre_hash(char* input) { 
unsigned int result = 0xBAE86554;
while (*input) { 
   result ^= *input++;
   result = rotate_left(result, 5);
}
return result;
}

//hash()
//turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
return pre_hash(key)%tableSize;
}

//showBits()
//print out the bits in an unsigned int
void showBits(unsigned int x) {
int i;
int sizeInBits = 8*sizeof(unsigned int);
char symbol[2] = {'0','1'};
char* binary = malloc(sizeInBits + 1);

memset(binary, 0, sizeInBits + 1);

for (i=0; i<sizeInBits; i++) {
    binary[sizeInBits-i-1] = symbol[(x>>i) & 0x01];
}

printf("%s\n", binary);
free(binary);
}

//public types 

//ListObj
typedef struct ListObj{
Node head;
Node tail;
int numItems;
}ListObj;

typedef ListObj* List;

//constructor for the List type
List newList(void){
//allocate memory
List L = malloc(sizeof(ListObj));
assert( L != NULL );
//initialize list fields
L->head = NULL;
L->tail = NULL;
L->numItems = 0;
return (L);
}
//destructor for the List type
void freeList(List* pL){
	if(pL!= NULL && *pL !=NULL) {
	//free memory
	free(*pL);
	*pL = NULL;
	}
  }

//returns true if L  is empty
int ListIsEmpty(List L){
//error if L is NULL
if ( L == NULL ){
fprintf(stderr, 
	    "List Error: Calling isEmpty() on NULL List reference\n");
exit(EXIT_FAILURE);
}

//if empty, return true
return (L->numItems==0);
}


//returns the size of the list 
int ListSize(List L){
//error if L is NULL
if( L == NULL){
fprintf(stderr, 
	    "List Error: Calling size() on NULL List reference\n");
exit(EXIT_FAILURE);
}

//return numItems
return (L->numItems);
}


//returns value v if it exists 
char* ListLookup(List L, char* k){

//if L is NULL, then there is an error
if ( L == NULL ){
fprintf(stderr,
	    "List Error: calling lookup() on NULL List reference\n");
exit(EXIT_FAILURE);
}


//set N to point to beginning 
Node N = L->head;
//set T to the front of the list too
Node T = N;
//initialize the integer that finds the value
int f = 0;  

//search matching key and value
while( N != NULL && !f ){

//when key is found
if( !strcmp(N->stack->key, k) ){
T = N;
f = 1;
}
//otherwise go to the next node
N = N->next;
} 

//return value, when found 
if (f){
return(T->stack->value); 
}
else{
return NULL;
}

}

//inserts the key and value into L
void ListInsert(List L, char* k, char* v){

//check if key already exists
if( ListLookup(L, k) != NULL ){
fprintf(stderr, 
	    "List Error: calling insert() when there’s a duplicate key: %s\n", k);
}
else{                                               
Node K = newNode(k, v);

//if list is empty                                                                         
if(ListIsEmpty(L)){
L->head = K;
L->tail = K;
}
else{                                                           
K->next = L->head;
L->head = K;
}

//increment number of items                                                              
L->numItems++;
}
}


//deletes the value 
void ListDelete(List L, char* k){

//if there is no key, then there is an error
if( ListLookup(L, k) == NULL ) {
fprintf(stderr,
	    "List Error: calling delete() when there is no key: %s\n", k);
}
else{
Node cur  = L->head;
Node prev = L->head;
int f     = 0;

//with only one node 
if( L->numItems == 1 ){
freeNode(&L->head);
L->head = NULL;
L->tail = NULL;
}
else{
//while loop 
while( !f ){

// when key is found
if( !strcmp(cur->stack->key, k) ){
	// set found to true
	f = 1;
	
	// if key is at the beginning 
	if( cur == L->head ){
	  L->head = L->head->next;
	  cur->next = NULL;
	  freeNode(&cur);
	}
	// if key is at the end of the list
	else if( cur == L->tail){
	  L->tail = prev;
	  prev->next = NULL;
	  freeNode(&cur);
	}
	// if key is in the middle 
	else{
	  prev->next = cur->next;
	  cur->next = NULL;
	  freeNode(&cur);
	}
}
// if key still needs to be found 
else{
	//if it’s at the beginning of the list
	if( cur == L->head){
	  cur = cur->next;
	}
	else{
	  cur = cur->next;
	  prev= prev->next;
	}
}
}
}
//numItems decrements node is deleted 
L->numItems--;
}
}


//makes L an  empty state.
void ListMakeEmpty(List L){

//if L is NULL, then there is an error
if( L == NULL ){
printf(stderr, "List Error: calling makeEmpty() on NULL List reference\n");
exit(EXIT_FAILURE);
}

Node currently = L->head;
Node remove  = L->head;

while( currently != NULL ){
currently = currently->next;
//remove node
freeNode(&remove);
remove = currently;
}
//initialize 
L->head     = NULL;
L->tail     = NULL;
L->numItems = 0;

}
//print out the list, if it is not NULL
void ListPrint(FILE* out, Node N){
	while(N!= NULL) {
		fprintf(out,"%s %s\n", N->stack->key, N->stack->value);
		N = N->next;
	}
}
//free ListArray 
void freeListArray(List** pL){
 
 if( pL != NULL && *pL != NULL ){
     //free the memory
     free(*pL);
     *pL = NULL;
 }
}
//define DictionaryObj
typedef struct DictionaryObj{
 int items;
 List* L;
}DictionaryObj;

typedef DictionaryObj* Dictionary;
//constructor for the Dictionary type
Dictionary newDictionary(void)
{
 Dictionary D = malloc(sizeof(DictionaryObj));
 assert(D!=NULL);
 D->L = calloc(tableSize, sizeof(List*));
 for(int i=0;i<tableSize;i++)
 {
     D->L[i]=newList();
 }
 D->items=0;
 return D;
}

//return true if empty, false otherwise 
int isEmpty(Dictionary D) {
if ( D == NULL ){
fprintf(stderr, 
	    "Dictionary Error: Calling isEmpty() on NULL Dictionary reference\n");
          exit(EXIT_FAILURE);
}
    if(D->items==0)
	return 1; 
     else
	return 0;
 
}
//returns the size of the list
int size(Dictionary D) {
if( D == NULL){
fprintf(stderr, 
	    "Dictionary Error: Calling size() on NULL Dictionary reference\n");
exit(EXIT_FAILURE);
}
   return D->items;
}
//returns the value for D or return NULL if value does not exist, using a hash table
char* lookup(Dictionary D, char* k) {


 int hashTable=hash(k);
 return(ListLookup(D->L[hashTable], k));
}
//inserts a new key & value into D, using a hash table 
void insert(Dictionary D, char* k, char* v)
{
 if(lookup(D, k)!=NULL)
 {
     printf("Error: insert() called on an already existing key \n");
     exit(EXIT_FAILURE);
 }
 int hashTable=hash(k);
 ListInsert(D->L[hashTable], k, v);
 D->items++;
}
//deletes a key & value, using a hash table
void delete(Dictionary D, char* k)
{
 if(lookup(D, k)==NULL)
 {
     printf("Error: delete() called on a nonexistent key \n");
     exit(EXIT_FAILURE);
 }
 int hashTable=hash(k);
 ListDelete(D->L[hashTable], k);
 D->items--;
}
//makes chain empty
void makeEmpty(Dictionary D)
{
 if(D==NULL)
 {
     fprintf(stderr, "Dictionary Error: makeEmpty() called on an already empty list \n");
     exit(EXIT_FAILURE);
 }
 //iterates through table and makes chain empty
 for(int i=0;i<tableSize;i++)
 {
     ListMakeEmpty(D->L[i]);
 }
 //size of list is now 0
 D->items=0;
}
//prints out the Dictionary list, if it is not NULL
void printDictionary(FILE* out, Dictionary D)
{
 if(D==NULL)
 {
     printf("Error: printDictionary() called on an empty dictionary");
     exit(EXIT_FAILURE);
 }
 for(int i=0; i<tableSize;i++)
 {
     if(D->L[i]->head!=NULL)
	ListPrint(out, D->L[i]->head);
 }

}
//frees the Dictionary and is the destructor for the Dictionary type
void freeDictionary(Dictionary *pD){
	makeEmpty(*pD);
     if( pD != NULL && *pD !=NULL){
	for(int i=0;i<tableSize; i++){
		freeList(&((*pD)->L[i]));
        }
     //frees array of pointers to list
    freeListArray(&((*pD)->L));
    free(*pD);
    *pD = NULL;
    }
}
