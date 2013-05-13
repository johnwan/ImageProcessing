#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float getmg(int m,int n,int cols,int rows,float *edge_mag)
{
  // Histogram
  int i,j;
  unsigned int k;
  unsigned int *histo;
  histo = (unsigned int*)malloc(sizeof(unsigned int)*256); 
   //initial histo array
   for (i=0; i<256;i++)
   {
    histo[i]=0;
    //printf("%d\n",histo[i]);    
    
   }
   
   // devide the image to m*n


   //initial array
   for (i=0;i<256;i++)
          histo[i]=0;
   // caculate histo array
   for (j=0; j<rows; j++)
   {
     for (i=0; i<cols; i++)
     {  
        
        histo[(int)edge_mag[j*cols+i]]++;
         
        //printf("%f\t%d\n",edge_mag[j*cols+i],histo[(int)edge_mag[j*cols+i]]);
     }     
   }

// Ostu Process
  // T = k
  
  float mg;
  

   
   //Compute the accumulative means
  mg=0;
   for (i=0; i<256; i++)
    { 
     mg = mg + i*histo[i];
   
    }
   mg = mg/(cols*rows);
   
   
  
  return mg;
}
