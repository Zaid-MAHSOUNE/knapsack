#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <math.h>
#include <errno.h>
#include <time.h>
#include <assert.h>




typedef struct dataSet 
{
	//Attributes of the instance
	//Nombre d'objets
	int n;
	//Capacite b
	int b;
	//Tableau d'entiers de taille n contenant la valeur de chacun des objets
	int*c;
	//Tableau d'entiers de taille n contenant le poids de chacun des objets
	int*a;


} dataSet;

typedef struct  Item
{
    int index;     // Index of the item
    float ratio;   // Value-to-weight ratio
} Item;

int read_TP1_instance(FILE*fin,dataSet* dsptr);
int KP_greedy(dataSet* dsptr);
int KP_LP(dataSet* dsptr);
void generate_csv(int n, int b);
int compareItems(const void *a, const void *b);


