/*
Author: Himol Shah
Description: Zoom an image
*/

//	Header Files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

//	Main Function
void main()
{
	//	Declaration of variables
	int pix, npix, scan, nscan, npix_out, nscan_out, *fp1, *fp2, cnt, temp, x, y, a, b, i, x0, y0, xx, yy;
	char input_file[100],output_file[100];
	float zoom;
	double rads;

	//	Accepting size and names of input and output files
	printf("Enter npix nscan of the image: \n");
	scanf("%d %d",&npix,&nscan);

	printf("Enter name of the input file: \n");
	scanf("%s", input_file);
	printf("Enter name of the output file: \n");
	scanf("%s",output_file);

	//	accepting the zooming factor
	printf("Enter the zooming factor:\n");
	scanf("%f", &zoom);

	//	computing new dimesions of the image
	npix_out = zoom*npix;
	nscan_out = zoom*nscan;


	//	declaring and allocating memory for entire image
	unsigned char **image = (unsigned char **)malloc(nscan * sizeof(unsigned char *));
    	for (scan=0; scan<nscan; scan++)
        	image[scan] = (unsigned char *)malloc(npix * sizeof(unsigned char));

	unsigned char **image_out = (unsigned char **)malloc(nscan_out * sizeof(unsigned char *));
    	for (scan=0; scan<nscan_out; scan++)
        	image_out[scan] = (unsigned char *)malloc(npix_out * sizeof(unsigned char));

	//	initializing image_out for output image
	for(scan = 0; scan < nscan_out; scan++)
	{
		for(pix = 0; pix < npix_out; pix++)
		{
			image_out[scan][pix] = 255;
		}
	}

	
	fp1 = open(input_file,O_RDONLY);	//	opening the input file
	if(fp1<0)	//	checking for errors while opening the file
	{
		printf("Error in opening the input file. \n");
		exit(1);
	}

	for(scan=0;scan<nscan;scan++)
	{
		read(fp1,&image[scan][0],npix*sizeof(unsigned char));	//	reading the input image
	}

	close(fp1);	//	closing the input image


	fp2 = creat(output_file,0666);	//	creating new file

	if(fp2 < 0)	//	checking for errors while creating the new file
	{
		printf("Error in creating the output file. \n");
		exit(1);
	}

	for(scan = 0; scan < nscan_out; scan++)
	{
		for(pix = 0; pix < npix_out; pix++)
		{
			//	performing change of coordinates operation
			x = (int)scan/zoom;
			y = (int)pix/zoom;

			image_out[scan][pix] = image[x][y];	//	mapping the exact coordinates of input image to the output image
		}
	}

	for(scan = 0; scan < nscan_out; scan++)
	{
		write(fp2, &image_out[scan][0], npix_out*sizeof(unsigned char));	//	writing into the file
	}

	close(fp2);	//	closing the file

}
