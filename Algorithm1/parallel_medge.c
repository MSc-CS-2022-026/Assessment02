   /***********************************************
   *
   *   file medge.c
   *
   *   Functions: This file contains
   *      main
   *
   *   Purpose:
   *      This file contains the main calling
   *      routine that performs edge
   *      detection.
   *
   *   External Calls:
   *      imageio.c - create_image_file
   *                  read_image_array
   *                  write_image_array
   *                  get_image_size
   *                  allocate_image_array
   *                  free_image_array
   *      edge.c -
   *          quick_edge
   *
   *************************************************/



#include "cips.h"
#include "stdio.h"
#include "omp.h"

int does_not_exist();
int create_image_file();
int get_image_size();
int read_image_array();
int free_image_array();
int write_image_array();
int get_bitsperpixel();
int show_edge_usage();
int quick_edge();

int main(argc, argv)
   int argc;
   char *argv[];
{
	char  image_name[MAX_NAME_LENGTH];
	char  image_name2[MAX_NAME_LENGTH];
	char  response[MAX_NAME_LENGTH];
	int   i, j;
	int   high, size, threshold, type;
	long  bits_per_pixel, height, width;
	short **the_image, **out_image;
	struct   tiff_header_struct image_header;


      /******************************************
      *
      *   Ensure the command line is correct.
      *
      ******************************************/

	if(argc < 4   || argc > 7){
		show_edge_usage();
		exit(0);
	}

	strcpy(image_name,  argv[2]);
	strcpy(image_name2, argv[3]);

	if(does_not_exist(image_name)){
		printf("\nERROR input file %s does not exist", image_name);
		exit(0);
	}

	create_image_file(image_name, image_name2);
	get_image_size(image_name, &height, &width);
	get_bitsperpixel(image_name, &bits_per_pixel);
	the_image = allocate_image_array(height, width);
	out_image = allocate_image_array(height, width);
	read_image_array(image_name, the_image);
   
	if(argv[1][0] == 'q' || argv[1][0] == 'Q'){
		threshold = atoi(argv[4]);
		high = atoi(argv[5]);
      	
		double tstart, tcalc, tstop;
	
		tstart = omp_get_wtime();
      	
		quick_edge(the_image, out_image, threshold, high, height, width, bits_per_pixel);
      	
		tstop  = omp_get_wtime();

		tcalc = tstop - tstart;
      	
		printf("Time taken to execute in mili seconds: %f\n", tcalc*1000);
      	
	}  /* ends if q */

	write_image_array(image_name2, out_image);
	free_image_array(the_image, height);
	free_image_array(out_image, height);

}  /* ends main */


int show_edge_usage()
{

	printf("\nusage of medge""\n  Quick edge detector""\n medge Q in-file out-file threshold (1/0) high""\n");
	return 0;

}  /* ends show_edge_usage */
