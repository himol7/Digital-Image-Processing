/*
Author: Himol Shah
Description: Fill in a circle with the image
Details: Please link the mathematical library while compilation
use: "gcc circle.c -lm"
*/

//	Header files
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

//	Main Function
void main()
{
	//	Declaration of variables
	int pix, npix, scan, nscan, *fp1,*fp2, x_centre, y_centre;
	unsigned char *image;
	char output_file[100], input_file[100];
    	float x, y, radi;

	//	accepting the dimensions of input image
	printf("Enter npix nscan of the image: \n");
	scanf("%d %d",&npix,&nscan);

	image = (unsigned char *)calloc(npix,sizeof(unsigned char));	//	allocating memory to the image array

	//	Accepting names of input and output files
	printf("Enter name of the input file: \n");
	scanf("%s", input_file);
	printf("Enter name of the output file: \n");
	scanf("%s",output_file);

	//	accepting radius of the circle
	printf("Enter the radius of the circle: \n");
	scanf("%f", &radi);

	//	computing centre coordinates
	x_centre = (npix+1)/2;
	y_centre = (nscan+1)/2;

	fp1 = open(input_file,O_RDONLY);	//	opening the input file


	if(fp1<0)	//	checking for errors while opening the file
	{
		printf("Error in opening the input file. \n");
		exit(1);
	}

	fp2 = creat(output_file, 0666);	//	creating output file

	if(fp2<0)	//	checking for errors while creating the file
	{
		printf("Error in creating the output file. \n");
		exit(1);
	}

	for(scan = 0; scan < nscan; scan++)
	{
		read(fp1, &image[0], npix*sizeof(unsigned char));

		for(pix = 0; pix < npix; pix++)
		{
			x = x_centre - pix;
			y = y_centre - scan;

			if(abs(sqrt((x*x + y*y))- radi) <= (float)(0.1))    //drawing boundaries of the circle
			{
				image[pix] = 0;	//	assigning black color to the boundaries
			}
		}

		write(fp2, &image[0], npix*sizeof(unsigned char));	//	write into the output file
	}

    	free(image);	//	freeing memory
	close(fp1);	//	closing file
	close(fp2);	//	closing file
}
