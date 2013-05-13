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
  unsigned int x1,x2,y1,y2;
  float t1,t2;
  unsigned char *image;
  unsigned char *output;
  float *edge_mag;
  FILE * fp;
  int i,j,x,y;
  float a,b,c,d;
  

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
  

  edge_mag = (float*)malloc(sizeof(float)*(rows*3+1)*(cols*3+2));
  /*
  printf("begin calculting edge_magnitude.... \n");
  EdgeMag(rows, cols, image, edge_mag);
  */
   for (j=0; j<rows*3; j++)
    for (i=0; i<cols*3; i++)
    { if ((i % 3 == 0)&&(j % 3 == 0))  
         {
          edge_mag[j*cols*3+i]  = image[j/3*cols+i/3];    
          }
    }
    
   
/*
   for (i=0; i<rows*3+1; i++)
     for (j=0; j<2; j++)
     {          
       edge_mag[i*(cols*3+2)+cols*3+j]  = edge_mag[i*(cols*3+2)+(cols*3-3+j)];  
     }
   for (i=0; i<cols*3+1; i++)
     {
       edge_mag[rows*3*(cols*3+2)+i]  = edge_mag[(rows*3-3)*(cols*3+2)+i];   
     }
  */ 
    
  // I am tring to solve it by Bilinear interpolation.
  
  
  for (j=0; j<rows*3; j++)
    for (i=0; i<cols*3; i++)
    { 
        if ((i % 3 == 0)&&(j % 3 == 0))  
        {
        i=i;
        }
        else if ((cols*3-i<4)||(rows*3-j<4))
             edge_mag[j*cols*3+i]  = image[j/3*cols+i/3];   
        else
          
        
            {
            x1=(i/3)*3;
            x2=x1+3;
            y1=(j/3)*3;
            y2=y1+3;
            a = ((float)j-(float)y1)/3;
            b = ((float)y2-(float)j)/3;
            c = ((float)i-(float)x1)/3;
            d = ((float)x2-(float)i)/3;
            t1=a*edge_mag[y1*cols*3+x1]+b*edge_mag[y2*cols*3+x1];
            t2=a*edge_mag[y2*cols*3+x1]+b*edge_mag[y2*cols*3+x2];
            //printf("%d\t%d\t%d\t%d\t%lf\t%lf\n" ,x1,x2,y1,y2,t1,t2);
            //system("pause");  
            edge_mag[j*cols*3+i]=c*t2+d*t1;
            //printf("%d\t%lf\t%lf\t%lf\n",i,c,d,c*t2+d*t1);
            //system("pause");  
               
            
              
            }
        
       /* 
      {
        for (y=0; y<3; y++)
         for (x=0; x<3; x++)
         {
            x1=x/3*3;
            x2=x1+3;
            y1=y-(y%3);
            y2=x/3*3;
            t1=(y-y1)/3*edge_mag[(j+y1)*cols*3+i+x1]+(y2-y)/3*edge_mag[(j+y1)*cols*3+i+x2];
            t2=(y-y1)/3*edge_mag[(j+y2)*cols*3+i+x1]+(y2-y)/3*edge_mag[(j+y2)*cols*3+i+x2];         
            printf("%d\t%d\t%d\t%d\t%d\t%d\t",x1,x2,y1,y2,t1,t2);
            system("pause");  
          edge_mag[(j+y)*cols*3+i+x]=(i-x1)/3*(unsigned char)t2+(x2-i)/3*(unsigned char)t1;
         }
      }
      
      */
    }
  
   
  /* end of your application */


  output = (unsigned char*)malloc(sizeof(unsigned char)*(rows*3)*(cols*3));
  for (j=0; j<rows*3; j++)   
    for (i=0; i<cols*3; i++)
      output[j*cols*3+i] = (unsigned char)edge_mag[j*cols*3+i];

  if ((fp=fopen(argv[2], "wb"))==NULL){
    printf("reading error...\n");
    exit(0); 
  }
  printf("Writing PGM....\n");
  WritePGM(rows*3, cols*3, image, output, fp);
  
}

