/***********************************************
*
*       file edge.c
*
*       Functions: This file contains
*          quick_edge, fix_edges
*
*       Purpose:
*          These functions implement several
*          types of basic edge detection.
*
*************************************************/

#include "cips.h"
#include "stdio.h"
#include <omp.h>

int fix_edges();

short quick_mask[3][3] =  {
       {-1,  0, -1},
       { 0,  4,  0},
       {-1,  0, -1} };


/***************************
*
*   Directions for the masks
*  3 2 1
*  4 x 0
*  5 6 7
*
****************************/


/*******************************************
*
*   quick_edge(...
*
*   This function finds edges by using
*   a single 3x3 mask.
*
*******************************************/


int quick_edge(the_image, out_image, threshold, high, rows, cols, bits_per_pixel)
	int    high, threshold;
	long   rows, cols, bits_per_pixel;
	short  **the_image, **out_image;

{
	short  a, b, i, j, k, length, max, new_hi, new_low, sum, width;
	//double start_time, end_time;

	new_hi  = 250;
	new_low = 16;
	max = 255;
   
	if(bits_per_pixel == 4){
		new_hi  = 10;
		new_low = 3;
		max = 16;
	}
	
	/* Do convolution over image array */
	//start_time = omp_get_wtime();
	
	for(i=1; i<rows-1; i++){
		for(j=1; j<cols-1; j++){
			sum = 0;
			for(a=-1; a<2; a++){
				for(b=-1; b<2; b++){
					sum = sum + the_image[i+a][j+b] * quick_mask[a+1][b+1];
				}
			}
			if(sum < 0)   sum = 0;
			if(sum > max) sum = max;
			out_image[i][j]   = sum;
		}  /* ends loop over j */
	}  /* ends loop over i */

	/* if desired, threshold the output image */
	if(threshold == 1){
		for(i=0; i<rows; i++){
			for(j=0; j<cols; j++){
				if(out_image[i][j] > high){
					out_image[i][j] = new_hi;
				}
				else{
					out_image[i][j] = new_low;
				}
			}
		}
	}  /* ends if threshold == 1 */
	
	//end_time = omp_get_wtime();
	
	//printf("Serial execution time: %f miliseconds\n", (end_time - start_time) * 1000);

	fix_edges(out_image, 1, rows-1, cols-1);
	
	
	return 0;
}  /* ends quick_edge */

/***********************************************
*
*    fix_edges(...
*
*    This function fixes the edges of an image
*    array after convolution was performed.
*    It copies the points near the edge of the
*    array out to the edge of the array.
*
***********************************************/

int fix_edges(im, w, rows, cols)
	int   w;
	short **im;
	long  rows, cols;
{
	int i, j;

        // Top-left corner
	for (i = w; i > 0; i--) {
            im[i - 1][i - 1] = im[i][i];
        }

        // Top-right corner
        for (i = w; i > 0; i--) {
            im[i - 1][cols - (i - 1)] = im[i][cols - 1 - (i - 1)];
        }

        // Bottom-left corner
        for (i = w; i > 0; i--) {
            im[rows - (i - 1)][i - 1] = im[rows - 1 - (i - 1)][i];
        }

        // Bottom-right corner
        for (i = w; i > 0; i--) {
            im[rows - (i - 1)][cols - (i - 1)] = im[rows - 1 - (i - 1)][cols - 1 - (i - 1)];
        }

	for (i = 0; i < rows; i++) {
		for (j = w; j > 0; j--) {
			im[i][j - 1] = im[i][j];
		}
	}

	for (j = 0; j < cols; j++) {
		for (i = w; i > 0; i--) {
			im[i - 1][j] = im[i][j];
		}
	}

	return 0;
}

