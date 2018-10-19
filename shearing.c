/*
Author: Himol Shah
Description: Shearing an image
Details: Please link the mathematical library while compilation
use: "gcc shearing.c -lm"
*/

//	Header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <fcntl.h>

//	Main Function
void main()
{

	//	Declaration of variables
	unsigned char *image,*image_out;
	int pix, npix, scan, nscan, *fp1, *fp2, nscan_out, npix_out, cnt = 0;
    	char output_file[100],input_file[100];
	float radians,theta;

	//	accepting size of input image
	printf("Enter npix nscan of the image: \n");
	scanf("%d %d",&npix,&nscan);

	image = (unsigned char *)calloc(npix,sizeof(unsigned char));	// allocating memory to the image array

	//	Accepting names of input and output files
	printf("Enter name of the input file: \n");
	scanf("%s", input_file);
	printf("Enter name of the output file: \n");
	scanf("%s",output_file);

	//	accepting shear angle
	printf("Give Shear angle: \n");
	scanf("%f",&theta);

	//	computing radians
	radians = (theta)*22/(7*180);

	//	computing new dimensions of the image
	npix_out = npix + nscan*tan(fabs(radians));
	nscan_out = nscan;


	image_out = (unsigned char *)calloc(npix_out,sizeof(unsigned char));	//	allocating memory to the output image array

	fp1 = open(input_file,O_RDONLY);	//	opening the input file

	if(fp1 < 0)	//	checking for errors while opening the input file
	{
		printf("Error in opening the input file. \n");
		exit(1);
	}

	fp2 = creat(output_file,0666);	//	creating the output file

	if(fp2 < 0)	//	checking for errorrs while creating the output file
	{
		printf("Error in creating the output file. \n");
		exit(1);
	}

	if(theta >= (float)0)	//	checking for a special case
	{
		for(scan = nscan_out; scan > 0; scan--)
		{
			read(fp1, &image[0], npix*sizeof(unsigned char));	//	reading a pixel row from input image

			for(pix = scan*tan(radians) ; pix < npix_out; pix++)
			{
				if((pix - scan*tan(radians)) >= 0 && (pix - scan*tan(radians)) < npix)
					image_out[pix] = image[(int)(pix - scan*tan(radians))];	//	mapping the exact coordinates of input image to the output image

				else
					image_out[pix] = 0;	//	assigning black to unwanted part of the image

			}

			write(fp2, &image_out[0], npix_out*sizeof(unsigned char));	//	writing into the output file
		}
	}

	else
	{
		for(scan = nscan_out - 1; scan >= 0; scan--)
		{
			read(fp1, &image[0], npix*sizeof(unsigned char));	//	reading a pixel row from input image
			cnt = npix -1;	//	setting count

			for(pix = npix_out - (pix-scan*tan(radians)) ; pix > 0; pix--)
			{
				if(cnt >= 0)
					image_out[pix] = image[cnt];	//	mapping the exact coordinates of input image to the output image	

				else
					image_out[pix] = 0;	//	assigning black to unwanted part of the image


				cnt--;	//	decrementing cpunt

			}
			write(fp2, &image_out[0], npix_out*sizeof(unsigned char));	//	writing into the output file
		}
	}

    	free(image);	//	freeing memory
	free(image_out);//	freeing memory
	close(fp1);	//	closing file
	close(fp2);	//	closing file
}
