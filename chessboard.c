/*
Author: Himol Shah
Description: Create a chess board image
*/

//	Header Files
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<fcntl.h>

//	Main Function
void main()
{

	//	Declaration of variables
	int i, unit, size, c, *fp;
	unsigned char *white, *black;
	char output_file[100];

	//	initiating a do...while loop
	do
	{
	printf("Enter appropriate size of chessboard: \n");	//	accepting the desired size of a chess board
	scanf("%d", &i);
		
	size = i;
	
	}while(i%8 != 0 && i > 0);	//	checking condition for appropriate size, i.e. is it in the multiples of 8 or not

	unit = i/8;	//	defining one unit
	
	black = (unsigned char *)calloc(unit,sizeof(unsigned char));	//	allocating memory for a black unit 	
	white = (unsigned char *)calloc(unit,sizeof(unsigned char));	//	allocating memory for a white unit	

	for(i = 0 ; i < unit ; i++)
	{
		white[i] = 255;	//	assigning pixel values
		black[i] = 0;	//	assigning pixel values
	}
	
	//	accepting desired name of output file
	printf("Name the output file: ");
	scanf("%s", output_file);

	//	creating the output file
	fp = creat(output_file, 0666);
	if(fp < 0)	//	checking for error while creating the output file
	{
		printf("Error in opening output file");
		exit(1);
	}
	
	
	for(i = 0, c = 0; i < size*size - 2*unit ; i = i + 2*unit)
	{
		if(c == 16*unit)	//	checking for change in pattern
			c = 0;
		if(c < 8*unit)	//	writing white and black blocks alternatively for 1 unit of scan into the file
		{
			write(fp, &white[0], unit*sizeof(unsigned char));	
			write(fp, &black[0], unit*sizeof(unsigned char));
			c = c + 2;
		}	
		else if(c >= 8*unit && c < 16*unit)	//	writing white and black blocks alternatively for 1 unit of scan into the file
		{
			write(fp, &black[0], unit*sizeof(unsigned char));	
			write(fp, &white[0], unit*sizeof(unsigned char));
			c = c + 2;
		}	
	}
	
	free(white);	//	freeing memory
	free(black);	//	freeing memory
	close(fp);	//	closing file

}
