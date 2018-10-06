#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
	char * val;
	struct node * next;
} node;

typedef struct table {
	node** hash;
	int size;
} table;

table* initTable(int size);
int insert(table* hashmap, char *string,unsigned int hashCode);
void afisHash(table *hashmap);
int removee(table *hashmap, char *string,unsigned int hashCode);
int clearr(table *hashmap);
int elibHash(table *hashmap, int size);
int insertNodeEmptyList(node **address, char *string);
int insertNodeNotEmpty(node **address, char *string);
int cauta(table *hashmap, char *cuvant, int hashCode);
