#include <ctype.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "TP1Functions.h"


int main(int argc, char **argv)
{
	int rval =0;	
	//File instance name
	//-F option
        char instance_file[1024];
        snprintf(       instance_file,
                        1024,
                        "%s",
                        "instance1.csv");

	char c;
        while ((c=getopt (argc, argv,"F:h")) != EOF)
	{
		switch(c)
		{
                        case 'F':
				snprintf(       instance_file,
						1024,
						"%s",
						optarg);
				break;

			case 'h':
				fprintf(stderr,"Usage: ./TP1 [options]\nOptions:\n\n");
				fprintf(stderr,"******** INSTANCE DATA ********\n");
				fprintf(stderr,"\t-F Instance file name to load............................(default %s).\n",instance_file);
				break;
			default:
				exit(0);
		}
	}

	// dataSet data;

	// //Open the instance file
	// FILE* fin = fopen(instance_file,"r");
	// read_TP1_instance(fin,&data);
	// fclose(fin);

	// //execute your solution methods on the instance you just read
	// printf("Solution LP Greedy:\n");
	// KP_greedy(&data);
	// printf("Solution LP with relaxation:\n");
	// KP_LP(&data);

	// KP_Greedy Complexity
	// N fixed
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	// B fixed
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	complexity_test(10, 10, KP_greedy);
	// KP_Linear Complexity
	// N fixed
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);
	// B fixed
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);
	complexity_test(10, 10, KP_LP);




	return rval;
}

