/*
Author: Himol Shah
Description: Mosiac two images
*/

//  Header files
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<fcntl.h>

//  Void Function
void main()
{
//  Declaration of variables
unsigned char *l1, *arrpix, *arrscan;
int scan, npix1, nscan1, npix2, nscan2, npixmax, *fp1, *fp2, *fp3, *fp4;
char var[100];
// merging pixwise
l1 = (unsigned char *)calloc(npix,sizeof(unsigned char));   //  allocating memory to the array

//  accepting size and name of the first input file
printf("Enter pix and scan of first file: ");
scanf("%d %d", &npix1,&nscan1);

printf("Name the first file: ");
scanf("%s", var);

fp1 = open(var, O_RDONLY);  //  opening first input file

if(fp1 < 0) //  checking for errors while opening the first file
{
	printf("Error in opening input file");
	exit(1);
}

//  accepting size and name of the first input file
printf("Enter pix and scan of second file: ");
scanf("%d %d", &npix2,&nscan2);

printf("Name the second file: ");
scanf("%s", var);

fp2 = open(var, O_RDONLY);  //  opening first input file

if(fp2 < 0) //  checking for errors while opening the first file
{
	printf("Error in opening input file");
	exit(1);
}

//  printing out name of the output file for pixwise mearging
printf("Name the output file(merging pixwise): ");
scanf("%s", var);

fp3 = creat(var, 0666); //  creating output file

if(fp3 < 0) //  checking for errors while creating output file
{
	printf("Error in opening output file");
	exit(1);
}

//  writing into output files simaltaneously for both images
for(scan = 0 ; scan < nscan ; scan++)
{
	read(fp1, &l1[0], npix*sizeof(unsigned char));  //  reading from first image
	write(fp4, &l1[0], npix*sizeof(unsigned char)); //  writing into output file
    read(fp2, &l1[0], npix*sizeof(unsigned char));  //  reading from second image
	write(fp4, &l1[0], npix*sizeof(unsigned char)); //  writing into output file
}

free(l1);   //  freeing memory
//  closing files
close(fp1);
close(fp2);
close(fp3);

// merging scanwise
printf("Name the first file: ");
scanf("%s", var);

fp1 = open(var, O_RDONLY);

if(fp1 < 0)
{
	printf("Error in opening input file");
	exit(1);
}


printf("Name the second file: ");
scanf("%s", var);

fp2 = open(var, O_RDONLY);

if(fp2 < 0)
{
	printf("Error in opening input file");
	exit(1);
}

printf("Name the output file(merging scanwise): ");
scanf("%s", var);

fp4 = creat(var, 0666);

if(fp4 < 0)
{
	printf("Error in opening output file");
	exit(1);
}

l1 = (unsigned char *)calloc(npix,sizeof(unsigned char));   //  allocating memory to the image array

//  writing into output files sequentially for both images
for(scan = 0 ; scan < nscan ; scan++)
{
	read(fp1, &l1[0], npix*sizeof(unsigned char));  //  reading from first image
	write(fp4, &l1[0], npix*sizeof(unsigned char)); //  writing into output file
}
for(scan = 0 ; scan < nscan ; scan++)
{
	read(fp2, &l1[0], npix*sizeof(unsigned char));  //  reading from second image
	write(fp4, &l1[0], npix*sizeof(unsigned char)); //  writing into output file
}

free(l1);   //  freeing memory
//  closing files
close(fp1);
close(fp2);
close(fp3);
close(fp4);

}
