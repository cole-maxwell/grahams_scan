/*
 * driver for Graham's scan
 *
 * project: hw5
 * name: 
 * user??
 * date: 
 * file: driver.c
 */


#include "hw5.h"



int main(int argc, char* argv[])
{
  
    int n, seed, c;

	/* command line options
	 * ./drive -n nValue -s seedValue
	 */
	
	while ((c = getopt(argc, argv, "n:s:")) != -1) {
		switch (c) {
		case 'n': sscanf(optarg, "%u", &n); break;
		case 's': sscanf(optarg, "%d", &seed); break;
		default: break;
		}
	}
	printf("Seed: %d		Points Number: %d\n", seed,n);


    Point *data = createData(seed,n);

	int *index = sorting_angle(data, n);
    convex(data,index,n);
    free(index);
	free(data);
	return 0;
}
