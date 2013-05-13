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


main(int argc, char *argv[])
{
  int rows, cols;
  unsigned char *image;
  unsigned char *output;
  float *edge_mag;
  FILE * fp;
  int i,j,x,y;
  float sum;
  

  if (argc != 3){
    printf("Usage: Test <input_filename> <output_filename> \n");
    printf("       <input_filename>:   PGM file \n");
    printf("       <output_filename>:  PGM file \n");
    exit(0);              
  }


  printf("Reading PGM.... \n");
  if ((fp=fopen(argv[1], "rb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  ReadPGM(fp,&image,&rows,&cols);
   

  /* you may replace your own applications here */
  //rows = rows - (rows % 3);
  rows = rows/3;
  int cols_original=cols;
  cols/=3;
  //cols = cols/3;
  
  edge_mag = (float*)malloc(sizeof(float)*rows*cols);
  /*
  printf("begin calculting edge_magnitude.... \n");
  EdgeMag(rows, cols, image, edge_mag);
  */
 
  for (j=0; j<rows; j++)
    for (i=0; i<cols; i++)
    {  
        //down down.pgm downresult.pgm
      //printf("%d\t%d\t%d\t%d",j,i,j*cols+i,(j*3+1)*754+(i*3+1));  
      //system("pause");  
      //edge_mag[j*cols+i]=image[(j*3+1)*cols_original+(i*3+1)];
        
      
        for (y=0; y<3; y++)
         for (x=0; x<3; x++)         
          sum = sum+image[(j*3+y)*cols_original+(i*3+x)]; 
        
        
      
       sum = sum/9;        
       edge_mag[j*cols+i]  = sum;
       //printf("%d\n",sum);
       sum=0;
           
       
    }
   printf("%d\n",rows);
  /* end of your application */


  output = (unsigned char*)malloc(sizeof(unsigned char)*rows*cols);
  for (j=0; j<rows; j++)   
    for (i=0; i<cols; i++)
      output[j*cols+i] = (unsigned char)edge_mag[j*cols+i];

  if ((fp=fopen(argv[2], "wb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  printf("Writing PGM....\n");
  WritePGM(rows, cols, image, output, fp);
  
}

