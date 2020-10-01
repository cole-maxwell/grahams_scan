#ifndef HW5_H
#define HW5_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <getopt.h>
#ifndef TEST_FILE
#define TEST_FILE(f,s,s1) 	\
		if (NULL==f){		\
			fprintf(stderr, "%s: can't open %s\n", s,s1);\
			exit(1);}
#endif

typedef struct 
{
	double x,y;
} Point;


typedef struct 
{
	int i;
	double ang;
} PAngle;


Point *createData(int seed,int n);
int* sorting_angle(Point *data, int n);
void convex(Point* data,int *index,int n);

#endif