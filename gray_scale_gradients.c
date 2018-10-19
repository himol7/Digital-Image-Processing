/*
Author: Himol Shah
Description: Create gradient of gray scale intensities
*/

//	Header Files
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<fcntl.h>

//	Main Function
void main()
{

	//	declaration of variables	
	int nscan, unit, npix, pix, scan, fp, i;
	unsigned char *pat;
	char output_file[100];
	
	//	accepting desires size and name of the image
	printf("Enter the size of image: \n");
	scanf("%d", &nscan);
	
	printf("Enter name of the output file: ");
	scanf("%s", output_file);	

	//	creating a new file
	fp = creat(output_file, 0666);
	if(fp < 0)	//	checking for errors while creating the file
	{
		printf("Error in opening output file");
		exit(1);
	}	
		
	npix = nscan;	//	creating a square sized image

	if(nscan < 255)	// checking a special case
		unit = 1;
	else	
		unit = nscan/256;	//	defining a unit as one unit of pixel rows will have same intensity
	
	pat = (unsigned char *)calloc(npix, sizeof(unsigned char));	//	assigning memory to the array used for writing in the file 
	
	for(scan = 0 ; scan < nscan ; scan++)
	{
		i = 0;

		for(pix = 0; pix < npix ; pix++)
			pat[pix] = scan;	//	assigning pixel values as current scan

		while(i < unit)	//	iterating till 1 unit
		{
			write(fp, &pat[0], npix*sizeof(unsigned char));	//	writing into the file
			i = i + 1;
		}
	}

	free(pat);	//	freeing memory
	close(fp);	//	closing file

}
