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
int  DFT(int ,int ,int, float *,float *);


main(int argc, char *argv[])
{
  int rows, cols;
  unsigned char *image;
  unsigned char *output;
  float *edge_mag,*edge_mag_real,*edge_mag_image;
  FILE * fp;
  int i,j;
  float d0,fmax,fmin;
  

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
   
    //edge_mag  = (float*)malloc(sizeof(float)*(2*rows-1)*(2*cols-1));
    edge_mag_real  = (float*)malloc(sizeof(float)*(2*rows-1)*(2*cols-1));
    edge_mag_image = (float*)malloc(sizeof(float)*(2*rows-1)*(2*cols-1));
  /*
  printf("begin calculting edge_magnitude.... \n");
  EdgeMag(rows, cols, image, edge_mag);
  */
  


  // Enlarge the image with zero-pad
  for (j=0; j<rows; j++)
    for (i=0; i<cols; i++)
    { 
          edge_mag_real[j*(2*cols-1)+i]  = image[j*cols+i];   

    }

 
    // Motiply (-1)^(x+y)
  for (j=0; j<(2*rows-1); j++)
    for (i=0; i<(2*cols-1); i++)
    { 
          

          edge_mag_real[j*(2*cols-1)+i]  =  edge_mag_real[j*(2*cols-1)+i]*(pow(-1,i+j));
          edge_mag_image[j*(2*cols-1)+i]  = 0;    
    }
    

  //DFT part
  float *p;
  p = &edge_mag_real[0];
  float *q ;
  q = &edge_mag_image[0];
  

  DFT(-1,(2*cols-1),(2*rows-1),p,q);

 
  //motiple H(u,v)
  d0 = 320;
  for (j=0; j<(2*rows-1); j++)
    for (i=0; i<(2*cols-1); i++)
    { 
          if ( sqrt(pow(i-cols,2)+pow(j-rows,2)) > d0 )
             {
                 
                 edge_mag_real[j*(2*cols-1)+i] = 0;                          
                                           
             } 
    }
  
  //IDFT
  
  p = &edge_mag_real[0];
  q = &edge_mag_image[0];
  DFT(1,(2*cols-1),(2*rows-1),p,q);
  
  
   // recover original image by multiple (-1)^(x+y)


    
  for (j=0; j<(2*rows-1); j++)
    for (i=0; i<(2*cols-1); i++)
    { 
        edge_mag_real[j*(2*cols-1)+i]  =  edge_mag_real[j*(2*cols-1)+i]*(pow(-1,i+j));
    }
  
     // re-scale
  fmin=255;
  fmax=0;
  for (j=0; j<(2*rows-1); j++)
    for (i=0; i<(2*cols-1); i++)
    { 
          if (edge_mag_real[j*(2*cols-1)+i]>fmax) 
            fmax =  edge_mag_real[j*(2*cols-1)+i];
          if (edge_mag_real[j*(2*cols-1)+i]<fmin) 
            fmin =  edge_mag_real[j*(2*cols-1)+i];    
    } 
    printf("fmax=%f\tfmin=%f\n",fmax,fmin);
    system("pause");
  for (j=0; j<(2*rows-1); j++)
    for (i=0; i<(2*cols-1); i++)
    { 
        edge_mag_real[j*(2*cols-1)+i] = 255*(edge_mag_real[j*(2*cols-1)+i]-fmin)/(fmax-fmin);
    }

  
  /* end of your application */

  // new rows and cols, remember change it back
  //rows = rows*2-1;
  //cols = cols*2-1;
  
  //remember change it back
  
  output = (unsigned char*)malloc(sizeof(unsigned char)*rows*cols);
  for (j=0; j<rows; j++)   
    for (i=0; i<cols; i++)
      // only changing out of the sample-code
      output[j*cols+i] = (unsigned char)edge_mag_real[j*(2*cols-1)+i];
      //output[j*cols+i] = (unsigned char)edge_mag_real[j*cols+i];
  if ((fp=fopen(argv[2], "wb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  printf("Writing PGM....\n");
  WritePGM(rows, cols, image, output, fp);
  
}

