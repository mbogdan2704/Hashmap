#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "t1.h"
/*
Functia face copierea unui hashmap intr-un alt hashmap, folosita pentru resize
*/
int copyy (node **address, table *newhashmap, int size) 
{

	int i;
	int hashCode;
	node *current = (*address);
	node *list;
	if(current == NULL)
		return 0;

	for(i = 0; ; i++) 
	{
	
		hashCode = hash(current -> val, size);
		

		list = newhashmap -> hash[hashCode];
		if(list == NULL) 
		{ 
			if( insertNodeEmptyList(newhashmap->hash + hashCode, current -> val) == -1)
				fprintf(stderr, "eroare la inserare");
		}
		else 
		{
			if( insertNodeNotEmpty(newhashmap->hash + hashCode, current -> val) == -1)
				fprintf(stderr, "eroare la inserare");
		}
		if(current -> next == NULL)
			break;
		current = current -> next;
	}
	return 0;

}
/*
Functia care dubleaza numarul de elemente dintr-un hashmap
*/
int resizeDouble(table *hashmap, table *newhashmap, int size) 
{
	int el;
	for(el = 0; el < size; el++) 
	{
		copyy(hashmap->hash + el, newhashmap, size * 2);
	}

	return 0;
}
int resizeHalf(table *hashmap, table *newhashmap, int size)
{

	int el;
	for(el = 0 ; el < size; el++) 
	
		copyy(hashmap->hash + el, newhashmap, size / 2);
	
	return 0;
}

int exista(table *hashmap, char *token, int hashcode) 
{
	node *current = hashmap -> hash[hashcode];
	int j;
	if(current != NULL) 
	{
		for(j = 0 ; ; j ++) 
		{
			if(strcmp(current -> val, token) == 0)
				return 1;
			if(current -> next == NULL)
				break;
			else
				current = current -> next;
		}
	}
	return 0;
}
void readfromFile(table *hashmap, FILE *f) 
{

	int i;
	int len = 20000;
	char *line = malloc(50000* sizeof(char));
	char *token;
	int hashcode;
	int ok = 0;
	FILE *outputFile;
	table *newhashmap;
	int number;
	int j;
	node **address;
	node *current;
	while(fgets(line, len, f)) 
	{
		
		ok = 0;
		token =  strtok(line, " ");
		if(strcmp(token, "\n") == 0)
			continue;
		if((strcmp(token, "add") == 0
		   ||strncmp(token, "add", strlen(token) -1) == 0) &&
		   	strcmp(token, "\n") != 0) 
		{ //Operatia de add
		
			token = strtok(NULL, " ");
			
			if(token != NULL) 
			{
				if(token[strlen(token)-1] == '\n')
					token[strlen(token)-1] = '\0';
		
				hashcode = hash(token, hashmap->size);
				if(exista(hashmap, token, hashcode) == 1)
					continue;
				insert(hashmap, token, hashcode);
			
			}
			else 
			{
				fprintf(stderr, "add nu are parametru");
				return;
			}
		}
		else if((strcmp(token, "remove") == 0
		   ||strncmp(token, "remove", strlen(token) -1) == 0) &&
		   	strcmp(token, "\n") != 0) 
		{ 

			token = strtok(NULL, " ");
			if(token != NULL) 
			{
				if(token[strlen(token)-1] == '\n')
					token[strlen(token)-1] = '\0';
				hashcode = hash(token, hashmap->size); 
				removee(hashmap, token, hashcode);
			}
			else 
			{
				fprintf(stderr, "remove nu are parametru");
				return ;
			}
		}
		else if((strcmp(token, "find") == 0
		   ||strncmp(token, "find", strlen(token) -1) == 0) &&
		   	strcmp(token, "\n") != 0) 
		{ 
			token = strtok(NULL, " ");
			if(token == NULL)
			{
				fprintf(stderr, "find nu are parametru");
				return ;
			}
			if(token[strlen(token)-1] == '\n') 
			{
				token[strlen(token) -1] = '\0';
			}
	
			hashcode = hash(token, hashmap->size);
			
			ok = cauta(hashmap, token, hashcode);
			
			token = strtok(NULL, " ");
			if(token != NULL) 
			{
				if(token[strlen(token)-1] == '\n') 
					token[strlen(token) -1] = '\0';
				outputFile = fopen(token, "a+");
			
				
				if(ok == 1)
					fprintf(outputFile, "True\n" );
				else
					fprintf(outputFile, "False\n" );
				fclose(outputFile);
			}
			else 
			{
				if(ok == 1)
					fprintf(stdout, "True\n");
				else
					fprintf(stdout, "False\n");
			}
		}
		else if((strcmp(token, "clear") == 0 || 
				strncmp(token, "clear", strlen(token)-1) == 0) &&
				strcmp(token,"\n") != 0) 
		{
			
			clearr(hashmap);
		
		}
		else if(strcmp(token, "print_bucket") == 0) 
		{
			token = strtok(NULL, " ");
		
			if(token[strlen(token)-1] == '\n') 
			{
				token[strlen(token) -1] = '\0';
			}
		
			for(i = 0 ; i <= strlen(token) -1 ; i++) 
			{
				if(token[i] < '0' || token[i] > '9') 
				{
					fprintf(stderr, "Eroare parametru prin_bucket");
					return ;
				}
			}
			number = atoi(token);
			token = strtok(NULL, " ");
			if(token != NULL) 
			{
				if(token[strlen(token)-1] == '\n')
					token[strlen(token) -1] = '\0';
				outputFile = fopen(token, "a+");
				address = hashmap->hash + number;
				current = (*address);
				if(current == NULL)
					continue;
				else 
				{
					for(j = 0 ; ; j++) 
					{
						fprintf(outputFile, "%s", current -> val);
						fprintf(outputFile, " ");
						if(current -> next == NULL)
							break;
						current = current -> next;
					}

				}	
				fprintf(outputFile, "\n")	;		
				fclose(outputFile);
			}
			else 
			{
				address = hashmap->hash + number;
				current = (*address);
				if(current == NULL)
					continue;
				else 
				{
					for(j = 0 ; ; j++) 
					{
						fprintf(stdout, "%s", current -> val);
						fprintf(stdout, " ");
						if(current -> next == NULL)
							break;
						current = current -> next;
					}
				
				}				
				fprintf(stdout, "\n");			

			}

		}
		else if((strcmp(token, "print") == 0 || 
				strncmp(token, "print", strlen(token)-1) == 0) &&
				strcmp(token,"\n") != 0) 
		{
			
		
			token = strtok(NULL, " ");
			if(token != NULL) {
				if(token[strlen(token)-1] == '\n') 
				{
					token[strlen(token) -1] = '\0';
				}
				outputFile = fopen(token, "w+");


			
				for(i = 0; i < hashmap -> size; i++) 
				{
					address = hashmap->hash + i;
					current = (*address);
					if(current == NULL)
						continue;
					else 
					{
						for(j = 0 ; ; j++) 
						{
							fprintf(outputFile, "%s",  current -> val);
							fprintf(outputFile, " ");
							if(current -> next == NULL)
								break;
							current = current -> next;
						}
				
					}			
				fprintf(outputFile, "\n");
				}
			fclose(outputFile);
			}
			else {
			for(i = 0; i < hashmap -> size; i++) 
			{
					address = hashmap->hash + i;
					current = (*address);
					if(current == NULL)
						continue;
					else 
					{
						for(j = 0 ; ; j++) 
						{
							fprintf(stdout, "%s",  current -> val);
							fprintf(stdout, " ");
							if(current -> next == NULL)
								break;
							current = current -> next;
						}
				
					}			
				fprintf(stdout, "\n");
				}
			}
		}
		else if(strcmp(token, "resize")== 0) 
		{
			token = strtok(NULL, " ");

			if(token[strlen(token)-1] == '\n') 
			{
					token[strlen(token) -1] = '\0';
			}
			if((strcmp(token, "double") == 0 ||
				strncmp(token, "double", strlen(token)-1) == 0) 
				&& strcmp(token,"\n") != 0) 
			{
				
				newhashmap = (table *) initTable(hashmap -> size * 2);
				resizeDouble(hashmap, newhashmap, hashmap->size);
				hashmap = newhashmap;
			}
			else if((strcmp(token, "halve") == 0 ||
					strncmp(token, "halve", strlen(token)-1) == 0) 
					&& strcmp(token,"\n") != 0) 
			{

				newhashmap = (table *) initTable(hashmap -> size / 2);
				resizeHalf(hashmap, newhashmap, hashmap->size);
				hashmap = newhashmap;


			}
		}
		else 
		{
			fprintf(stderr, "nici o comanda valida");
			return ;
		}
		
	}
	free(line);

}
int main(int argc, char **argv) 
{

	int i;
	int hashSize = 0;
	table *hashmap;
	FILE *f;
	if(argv[1] == NULL) 
	{
		
		fprintf(stderr, "Lipsa primul parametru");
		return 0;
	}
	else 
	{
		for(i = 0 ; i < strlen(argv[1]) ; i++)
			if(argv[1][i] < '0' || argv[1][i] >'9') 
			{
				fprintf(stderr, "eroare parametru 1");
				return 0;
			}
		hashSize = atoi(argv[1]);
		

	}
	hashmap = (table *) initTable(hashSize);

	if(argv[2] == NULL) 
	{
	
		f = stdin;
		readfromFile(hashmap,f);
	
	}
	else {

		for (i = 2; i <= argc - 1; i++ ) 
		{
			
			f = fopen(argv[i], "r");
			if(f == NULL) 
			{
				printf("ERROR");
			}
			else {
			
				readfromFile(hashmap, f);
				fclose(f);
			}
		}
	}
	elibHash(hashmap, hashmap->size);
	return 0;
	

}
