/*
 * driver for Graham's scan
 *
 * project: hw5
 * name: 
 * user??
 * date: 
 * file: hw5.c
 */


#include "hw5.h"



Point *createData(int seed,int n){

    FILE *f = fopen("points.csv", "w");
	TEST_FILE(f,"createData","points.csv");
	srand48(seed); /* seeding the pseudorandom number generator */
	Point *data = malloc(sizeof(Point) * n);
	for (int i = 0; i < n; i++) {
		data[i].x = drand48();data[i].y = drand48();
		fprintf(f, "%f,%f\n",data[i].x,data[i].y);
	}

	fclose(f);
	return data;
}

// Here we don't consider three points are colinear thus no need to check equal
int com(const void *s1, const void *s2){
	return  ((PAngle*) s1)->ang > ((PAngle*) s2)->ang;
}


// Here I calculate out all the polar angle of points to A, make it a member in a new structure and then sort them
// Some students make the A a global variable and sorting the points themselves, is also a good idea.
int * sorting_angle(Point *data, int n){
	//imy is the index of max y
	int imy = 0, *index;
	index = malloc(sizeof(int)*n);
	for (int i=1;i<n;i++)
		if (data[i].y > data[imy].y) 
			imy = i;
	printf("The point with max y is: (%g,%g)\n",data[imy].x, data[imy].y);

	PAngle *pas = malloc(sizeof(PAngle)*n);
	double xx,yy;
	// Here I am useing cosine
	for (int i=0;i<n;i++){
		if (i!=imy){
		 	pas[i].i=i;
		 	xx = data[i].x - data[imy].x;
		 	yy = data[i].y - data[imy].y;
			pas[i].ang = xx / sqrt(xx*xx + yy*yy);
		}else{
			//  The point A itself is set to -1.0
			pas[i].i = i;
			pas[i].ang = -1.0;
		}
	}

    FILE *f = fopen("sortedPoints.csv", "w");
	TEST_FILE(f,"sorting_angle","sortedPoints.csv");
	qsort(pas,n,sizeof(PAngle),com);
	for (int i=0;i<n;i++){
		index[i] = pas[i].i;
		fprintf(f, "%f,%f\n",data[index[i]].x,data[index[i]].y);
		printf("%d\t%g\n",pas[i].i,pas[i].ang);
	}
	fclose(f);

	return index;
}



//
void convex(Point* data,int *index,int n){
	int stack[n], top=2; double flag;
	Point *a,*b,*c;
	memcpy(stack,index,3*sizeof(int));

	int i =3;
	while (i<n+1){		
		a = &data[stack[top-1]];
		b = &data[stack[top]];
		c = &data[index[i % n]];
		flag = (b->x-a->x)*(c->y-a->y)
			  -(c->x-a->x)*(b->y-a->y);
		if (flag >= 0.0) 
			stack[++top] = index[i++ % n]; 
		else top--;
	}

    FILE *f = fopen("pointsCon.csv", "w");
	TEST_FILE(f,"convex","pointsCon.csv");
	printf("There are %d points in the stack\n", top);
	for (int i=0;i < top;i++){
		fprintf(f, "%f,%f\n",data[stack[i]].x,data[stack[i]].y);
		printf("%f6\t%g\n",data[stack[i]].x,data[stack[i]].y);
	}
	fclose(f);
}


