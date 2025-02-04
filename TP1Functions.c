#include "TP1Functions.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include<stdio.h>

int read_TP1_instance(FILE*fin,dataSet* dsptr)
{
	int rval = 0;

	//capacite b
	int b;
	//Nombre d'objets
	int n;
	rval = fscanf(fin,"%d,%d\n",&n,&b);
	dsptr->b = b;
	dsptr->n = n;
	dsptr->c = (int*)malloc(sizeof(int)*n);
	dsptr->a = (int*)malloc(sizeof(int)*n);


	int i;
	for( i = 0 ; i < n ; i++)
		rval = fscanf(fin,"%d,%d\n",&(dsptr->c[i]),&(dsptr->a[i]));

	fprintf(stderr,"\nInstance file read, we have capacity %d and there is %d items of values/weights:\n",
			b,n);
	for( i = 0 ; i < n ; i++)
		fprintf(stderr,"%d,%d\n",dsptr->c[i],dsptr->a[i]);
	fprintf(stderr,"\n");


	return rval;
}

void generate_csv(int n, int b) {
	const char *filename = "instance1.csv";
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    fprintf(file, "%d,%d\n", n, b);

    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        int c = rand() % 100 + 1; // Random value between 1 and 100
        int a = rand() % 100 + 1; // Random weight between 1 and 100
        fprintf(file, "%d,%d\n", c, a);
    }

    fclose(file);
    printf("CSV file '%s' generated successfully.\n", filename);
}

int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemA->ratio < itemB->ratio) return 1;
    if (itemA->ratio > itemB->ratio) return -1;
    return 0;
}

int KP_greedy(dataSet* dsptr)
{
    int n = dsptr->n;
    int b = dsptr->b;
    int *c = dsptr->c;
    int *a = dsptr->a;

    // Initialize the solution vector x, set to all 0s (nothing taken initially)
    int *x = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        x[i] = 0;
    }

    // Create an array of items with their index and value-to-weight ratio
    Item *items = (Item *)malloc(n * sizeof(Item));
    for (int i = 0; i < n; i++) {
        items[i].index = i;
        items[i].ratio = (float)c[i] / a[i];
    }

    // Sort the items based on the value-to-weight ratio in descending order
    qsort(items, n, sizeof(Item), compareItems);

    // Process each item in sorted order
    for (int j = 0; j < n; j++) {
        int idx = items[j].index;  // Get the original index of the item

        // If there is no remaining capacity, stop
        if (b == 0) {
            break;
        }

        // If the remaining capacity is greater than or equal to the weight of the item
        if (b >= a[idx]) {
            // Take the whole item
            x[idx] = 1;
            b -= a[idx];  // Reduce the remaining capacity
        }
    }

    // Print the solution (optional, for debugging or visualization)
    for (int i = 0; i < n; i++) {
        printf("Item %d: %d\n", i + 1, x[i]);
    }

    // Clean up memory
    free(x);
    free(items);

    return 0;
}


int KP_LP(dataSet* dsptr)
{
	int n = dsptr->n;
    int b = dsptr->b;
    int *c = dsptr->c;
    int *a = dsptr->a;
    float *x = (float *)malloc(n * sizeof(float));  // Solution vector
    Item *items = (Item *)malloc(n * sizeof(Item)); // Array of items with value-to-weight ratio

    // Initialization
    for (int i = 0; i < n; i++) {
        x[i] = 0;
    }

    //Create items array with value-to-weight ratio
    for (int i = 0; i < n; i++) {
        items[i].index = i;
        items[i].ratio = (float)c[i] / a[i];
    }

    //Sort items by value-to-weight ratio
    qsort(items, n, sizeof(Item), compareItems);

    //Fill the knapsack
    for (int i = 0; i < n; i++) {
        int idx = items[i].index;  // Get the original index of the item
        if (b == 0) {
            break;  // If no remaining capacity, exit
        }

        // Take as much of item i as possible (fractional knapsack)
        if (a[idx] <= b) {
            // Take the whole item
            x[idx] = 1;
            b -= a[idx];
        } else {
            // Take fraction of item
            x[idx] = (float)b / a[idx];
            b = 0;  // Knapsack is full
        }
    }

    // Return the result: (you can also print the solution if needed)
    for (int i = 0; i < n; i++) {
        printf("Item %d: %.2f\n", i+1, x[i]);
    }

    // Clean up memory
    free(x);
    free(items);

    return 0;
}

typedef void (*KPFunction)(dataSet* data);

void complexity_test(int n, int b, KPFunction kpAlgorithm)
{
    clock_t start, end;
    double cpu_time_used;
	dataSet data;

    generate_csv(n,b); 
    FILE* fin = fopen("instance1.csv","r");
	read_TP1_instance(fin,&data);
	fclose(fin);
    start = clock();
    kpAlgorithm(&data);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
}