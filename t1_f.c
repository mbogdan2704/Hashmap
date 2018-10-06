#include "t1.h"
/*
Initializeaza un hashmap
*/
table* initTable(int size) {

	table* tb = (table*) calloc(1, sizeof(table));
	if(!tb) {

		fprintf(stderr, "Avem eroare la alocare table");
		return NULL;
	
	}
	tb->size = size;
	tb->hash = (node **) calloc(size, sizeof(node*));
	if(!tb->hash) {
		fprintf(stderr, "eroare la alocare vector de noduri");
		free(tb);
		return NULL;
	}

	return tb;
}
/*
Insereaza intr-o lista goala
*/
int insertNodeEmptyList(node **address, char *string)
{

	node *aux = (node *) malloc(sizeof(node));
	if(!aux) {
		return -1;
	}

	aux -> val = malloc(sizeof(string));
	if(!aux->val)
		return -1;
	aux -> val = strdup(string);
	aux -> next = NULL;
	(*address) = aux;
	return 1;

}
/*
Insereaza intr-o lista care nu e goala
*/
int insertNodeNotEmpty(node **address, char *string)
{
		

	
	int j;
	node *aux = (node *) malloc(sizeof(node));
	node *current;
	if(!aux) {
		return -1;
	}

	aux -> val = malloc(sizeof(string));
	if(!aux->val)
		return -1;
	aux -> val = strdup(string);
	current = (*address);
	for(j = 0; ; j++) {

		if(current -> next == NULL)
			break;
		current = current -> next;
	
	}
	current -> next = aux;
	aux -> next = NULL;
	return 1;

}
/*
Sterge un string
*/
void removeString(node **address, char *string) {

	int j;
	node *current = (*address);
	node *previous = NULL;
	int ok = 0;
	for(j = 0; ; j++) {

		if(strcmp((current->val), string) == 0) {
			ok = 1;
			break;
		}
		if(current -> next == NULL)
			break;
		previous = current;
		current = current -> next;
	
	}
	if(ok == 1) {
	
		if(previous == NULL && current -> next == NULL) { //Stergem singurul element din lista 
			free(current -> val);
			free(current);
			(*address) = NULL;

		}
		else if(previous == NULL) { //Stergem primul element din lista
			
			if(current -> next != NULL)
				(*address) = current -> next;
			else
				(*address) = NULL;	
			free(current -> val);
			free(current);	
		}
		else {
			
			previous -> next = current -> next;
			free(current -> val);
			free(current);
		}
	
	
	}


}
/*
Afiseaza un hashmap
*/
void afisHash(table *hashmap)
{
	int i;
	int j; 
	node *current;
	for(i = 0; i< hashmap->size; i++) {

		if(hashmap ->hash[i] == NULL)
			continue;

		current = hashmap -> hash[i];
		printf("Bucketul%d ", i);
		for(j = 0; ; j++) {
			printf("%s ", current->val);
			if(current -> next == NULL)
				break;
			current = current -> next;
		
		}
			printf("\n");
		
		
	}
}
/*
Insereaza intr-un hashmap
*/
int insert(table *hashmap, char *string, unsigned int hashCode)
{

	node* list = hashmap -> hash[hashCode];
	if(list == NULL) { //Daca nu exista niciun element in lista
		if( insertNodeEmptyList(hashmap->hash + hashCode, string) == -1)
			fprintf(stderr, "eroare la inserare");
	}
	else {
		if( insertNodeNotEmpty(hashmap->hash + hashCode, string) == -1)
			fprintf(stderr, "eroare la inserare");
	}
	return 0;
	

}

/*
Sterge dintr-un hashmap
*/
int removee(table *hashmap, char *string, unsigned int hashCode) {

	node *list = hashmap -> hash[hashCode];
	if(list == NULL) {
		return 0;
	}
	else {
		removeString(hashmap->hash + hashCode, string);
	}
	return 0;
}
/*
Elibereaza un hashmap
*/
int elib(node **address) {
	node *current = (*address);
	int j;	
	node *aux;
	int ok = 1;
	if(current == NULL)
		return 0;
	else
		for(j = 0;;j++) {
			
			aux = current;
			if(current -> next == NULL)
				ok = 0;
			else
				current = current -> next;
			free(aux -> val);
			free(aux);
			if(ok == 0)
				break;

		}
	*address = NULL;
	return 0;
}

int clearr(table *hashmap) {
	
	int size = hashmap -> size;
	int el = 0;
	for(el = 0; el < size; el++)
		elib(hashmap -> hash + el);

	return 0;

}
/*
Elibereaza un hashmap
*/
int elibHash(table *hashmap, int size) {

	int el;
	for(el = 0; el < size; el++) {
		elib(hashmap -> hash + el);
		free(hashmap->hash[el]);
	}
	free(hashmap->hash);
	free(hashmap);
	return 0;
}
/*
Cauta intr-un hashmap
*/
int cauta(table *hashmap, char *cuvant, int hashCode) {
	node **address = hashmap->hash + hashCode;
	node *current = (*address);
	int j;
	if(current == NULL)
		return 0;
	else {
		for(j = 0 ; ; j++) {
			if(strcmp(cuvant, current-> val) == 0)
				return 1;
			if(current -> next == NULL)
				break;
			current = current -> next;
		}
	}
	return 0;
}


