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
  unsigned char *output2;
  int *histo;
  float *edge_mag_histo;
  float *edge_mag;
  FILE * fp;
  int i,j;
  

  if (argc != 4){
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
  rows = 256;
  cols = 256;  
  edge_mag = (float*)malloc(sizeof(float)*rows*cols);
  /*
  printf("begin calculting edge_magnitude.... \n");
  EdgeMag(rows, cols, image, edge_mag);
  */
  int d0,a,b;
  int noise=0;
  srand((int)time(NULL));
  // uniform noise;
  a=30;
  b=60;
  // end of uniform noise;
  // impulse noise
  float pa = 0.1;
  float pb = 0.1;
  
  d0 = 50;
  for (j=0; j<rows; j++)
  {
    for (i=0; i<cols; i++)
    {     
          
          //noise=rand()%(b-a)+a; //uniform
          
          //impulse
          float random;
          random = (float)rand()/RAND_MAX;;
          if (random > 1 - pa)
              noise = a;
            else if(random < pb)
               noise = b;
               else noise = 0;
          
          if ( sqrt(pow(i-cols/2,2)+pow(j-rows/2,2)) < d0 )
             {
                edge_mag[j*cols+i] = 100+noise;
                // replase the image with the noise
                /*                                    
                if(noise == 0)
                 edge_mag[j*cols+i] = 100;
                  else
                    edge_mag[j*cols+i] = noise;  
                   */                        
                                           
             } 
             else 
             {
                    edge_mag[j*cols+i] = 0+noise;   
             }
    }
  }
    
  // Histogram
  int max=0;
  histo = (int*)malloc(sizeof(int)*rows*cols);
  edge_mag_histo = (float*)malloc(sizeof(float)*rows*cols);
   //initial histo array
   for (i=0; i<256;i++)
   {
    histo[i]=0;
    //printf("%d\n",histo[i]);    
    
   }
   // caculate histo array
   for (j=0; j<rows; j++)
   {
     for (i=0; i<cols; i++)
     {  
        histo[(int)edge_mag[j*cols+i]]++;
        if (histo[(int)edge_mag[j*cols+i]]>max)
         max = histo[(int)edge_mag[j*cols+i]];
         
        //printf("%d\n",histo[(int)edge_mag[j*cols+i]]);
     }
   }
   printf("%d\n",max);
   // compress the Histogram to 256*256
    for (i=0; i<256;i++)
   {
    histo[i]=255*(float)histo[i]/max;
    //histo[i]=sqrt(histo[i]);
    //printf("%d\n",histo[i]);
   }
   system("pause");
   // change histo array to histogram
     for(i=0; i<256; i++)
     { 
              
       for (j=0; j<histo[i]; j++)
        {  
           edge_mag_histo[(rows-j)*cols+i] = 255;
        }
        
     }
    
  /* end of your application */
  
  
  output = (unsigned char*)malloc(sizeof(unsigned char)*rows*cols);
  for (j=0; j<rows; j++)   
    for (i=0; i<cols; i++)
      output[j*cols+i] = (unsigned char)edge_mag[j*cols+i];
      
  output2 = (unsigned char*)malloc(sizeof(unsigned char)*rows*cols);
  for (j=0; j<rows; j++)   
    for (i=0; i<cols; i++)
      output2[j*cols+i] = (unsigned char)edge_mag_histo[j*cols+i];

  if ((fp=fopen(argv[2], "wb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  printf("Writing PGM....\n");
  WritePGM(rows, cols, image, output, fp);
  
  if ((fp=fopen(argv[3], "wb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  
  printf("Writing PGM....\n");
  
  WritePGM(rows, cols, image, output2, fp);
  
}

