/*
Program: Histogram Equalization
Author:	 Himol Shah
Roll No: 201501098
*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

//  Void Function
void main()
{
    //  Declaration of variables
	unsigned char *image;
	int *image_out;
	char output_file[100], input_file[100];
	int pix, npix, scan, nscan, *fp1, npix_out, nscan_out;
	float x,y,r;
	int i,j;

	FILE *fp2;  //  creating a file

    //  accepting size of input files
	printf("Enter npix nscan of the image: \n");
	scanf("%d %d",&npix, &nscan);

	image = (unsigned char *)calloc(npix,sizeof(unsigned char));    //  allocating memory to the image array

    //  accepting names of input and output files
	printf("Enter name of the input file: \n");
	scanf("%s", input_file);
	printf("Enter name of the output file: \n");
	scanf("%s",output_file);

    //  setting dimensions
	npix_out = npix;
	nscan_out = nscan;

	image_out = (int *)calloc(256,sizeof(int)); //  allocating memory to output image array

	memset(image_out,0,256*sizeof(int));    //  setting 0

	fp1 = open(input_file,O_RDONLY);    //  opening input image

	if(fp1<0)   //  checking for errors while opening the file
	{
		printf("Error in opening the input file. \n");
		exit(1);
	}

	fp2 = fopen(output_file,"w");   //  creating an output file with writing permissions

	if(fp2 < 0) //  checking for errors while creating the output file
	{
		printf("Error in creating the output file. \n");
		exit(1);
	}

	for(scan = 0; scan < nscan; scan++)
	{
		read(fp1, &image[0], npix*sizeof(unsigned char));   //  reading from input file

		for(pix = 0; pix < npix; pix++)
		{
			image_out[(int)image[pix]]++;   //  incrementing frequency
		}

	}

	for(scan = 0; scan < 256; scan++)
	{
		fprintf(fp2,"%d %d\n",scan,image_out[scan]);    //  printing frequencies with their respective intensities in output file
	}

    	free(image);    //  freeing memory
	close(fp1); //  closing file
	close(fp2); //  closing file

	int hmax = -1 , hmin = 257;
	
	for(i = 0; i < 256 ; i++)
	{
		if(image_out[i] > hmax)
			hmax = image_out[i];
		if(image_out[i] < hmin)
			hmin = image_out[i];
	}
	 
	float prt[256];
	int pixels = npix_out*nscan_out;
	for(i = 0 ; i < 256 ; i++)
		prt[i] = image_out[i]/pixels;
	 
	 
   // Cumulative Distribution Function
	float cdfmax = -1, cdfmin = 257;
	float cdf[256];
	cdf[0] = prt[0];
	for(i = 1 ; i < 256 ; i++)
	{
		cdf[i] = prt[i] + cdf[i-1];
		if(cdf[i] > cdfmax)
			cdfmax = cdf[i];
		if(cdf[i] < cdfmin)
			cdfmin = cdf[i];
	}
	 
	 
	// Final Image
	for (i = 0 ; i < npix_out ; i++)
	{
	    for(j = 0 ; j < nscan_out ; j++)
	    {
	    	image_out[i][j] = (unsigned char)(((cdf[image_in[i][j]] - cdfmin)/(pixels - cdfmin))*255);
	    }
	}

}

