/**************************************
 * Zeyun Yu (yuz@uwm.edu)             *
 * Department of Computer Science     *
 * University of Wisconsin-Milwaukee  *
 **************************************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void ReadPGM(FILE* , unsigned char** , int* , int* );
void WritePGM(int, int, unsigned char *, unsigned char *, FILE*);
void EdgeMag(int, int, unsigned char *, float *);
void otsu(int x,int y,int cols,int rows,int *edge_mag);

main(int argc, char *argv[])
{
  int rows, cols;
  unsigned char *image;
  unsigned char *output;
  float *edge_mag;
  FILE * fp;
  int i,j;
  

  if (argc != 3){
    printf("Usage: Test <input_filename> <output_filename> \n");
    printf("       <input_filename>:   PGM file \n");
    printf("       <output_filename>:  PGM file \n");
    printf("       <output2_filename>: PGM file \n");
    exit(0);              
  }

  
  printf("Reading PGM.... \n");
  if ((fp=fopen(argv[1], "rb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  ReadPGM(fp,&image,&rows,&cols);
  

  /* you may replace your own applications here */
  
  edge_mag = (float*)malloc(sizeof(float)*rows*cols);
  
  /*
  printf("begin calculting edge_magnitude.... \n");
  EdgeMag(rows, cols, image, edge_mag);
  */
  // copy the data
  
  for (j=0; j<rows; j++)
   {
     for (i=0; i<cols; i++)
     { 
          edge_mag[j*cols+i] = image[j*cols+i];
     }
   }
  
  
    otsu(2,2,cols,rows,edge_mag);  
  
  /* end of your application */
  
  
  
  output = (unsigned char*)malloc(sizeof(unsigned char)*cols*rows);

  for (j=0; j<rows; j++)   
    for (i=0; i<cols; i++)
      output[j*cols+i] = (unsigned char)edge_mag[j*cols+i];
 
  
  if ((fp=fopen(argv[2], "wb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  printf("Writing PGM....\n");
  WritePGM(rows, cols, image, output, fp);
  
  /*
  
  output2 = (unsigned char*)malloc(sizeof(unsigned char)*256*256);
  for (j=0; j<256; j++)   
    for (i=0; i<256; i++)
      output2[j*255+i] = (unsigned char)edge_mag_histo[j*255+i];
  
  if ((fp=fopen(argv[3], "wb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  
  printf("Writing PGM....\n");
  
  WritePGM(rows, cols, image, output2, fp);
  */
}

