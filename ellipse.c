/*
Author: Himol Shah
Description: Fill in a ellipse
*/

//	Header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

//	Void Function
void main()
{
	//	Declaration of variables
    	int pix, npix, scan, nscan, *fp1,*fp2, x_centre, y_centre;
	unsigned char *image;
	char output_file[100], input_file[100];
	float x,y,a,b;

	//	Accepting size and names of input and output files
	printf("Enter npix nscan of the image: \n");
	scanf("%d %d",&npix,&nscan);

	image = (unsigned char *)calloc(npix,sizeof(unsigned char));	//	assigning memory to the array

	//	Accepting names of input and output files
	printf("Enter name of the input file: \n");
	scanf("%s", input_file);
	printf("Enter name of the output file: \n");
	scanf("%s",output_file);

	//	accepting constants of ellipse
	printf("Enter a: \n");
	scanf("%f", &a);
	printf("Enter b: \n");
	scanf("%f", &b);

	//	computing centre coordinates
	x_centre = (npix+1)/2;
	y_centre = (nscan+1)/2;

	fp1 = open(input_file,O_RDONLY);	//	opening the input file

	if(fp1 < 0)	//	checking for errors while opening the file
	{
		printf("Error in opening the input file\n");
		exit(1);
	}

	fp2 = creat(output_file,0666);	//	creating output file

	if(fp2 < 0)	//	checking for errors while creating the file
	{
		printf("Error in creating the output file\n");
		exit(1);
	}

	for(scan = 0; scan < nscan; scan++)
	{
		read(fp1, &image[0], npix*sizeof(unsigned char));	//	 reading a pixel row from the image

		for(pix=0; pix < npix; pix++)
		{
			//	computing distance form centre coordinates
			x = pix - x_centre;
			y = y_centre - scan;

			if(((x*x/(a*a) + y*y/(b*b)) -1<=(float)(1)))    //If the point lies inside the ellipse, assign black color to it
			{
				image[pix] = 0;
			}
		}

		write(fp2,&image[0],npix*sizeof(unsigned char));	//	writing into the output file
	}

    	free(image);	//	freeing memory
	close(fp1);	//	closing file
	close(fp2);
}
