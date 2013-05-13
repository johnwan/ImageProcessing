#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void otsu(int m,int n,int cols,int rows,float *edge_mag)
{
  // Histogram
  int max=0;
  int i,j,c,r;
  float drows = (float)rows/n;
  float dcols = (float)cols/m;
  unsigned int k;
  float *vb;  
  float *edge_mag_histo;  
  unsigned int *histo;
  histo = (unsigned int*)malloc(sizeof(unsigned int)*256); 
  vb = (float*)malloc(sizeof(float)*256);
   //initial histo array
   for (i=0; i<256;i++)
   {
    histo[i]=0;
    //printf("%d\n",histo[i]);    
    
   }
   
   // devide the image to m*n

for (r=0; r < n; r++)
 {
 for (c=0; c< m; c++)
  { 
   //initial array
   for (i=0;i<256;i++)
          histo[i]=0;
       
   // caculate histo array
   for (j=r*drows; j<(r+1)*drows; j++)
   {
     for (i=c*dcols; i<(c+1)*dcols; i++)
     {  
        
        histo[(int)edge_mag[j*cols+i]]++;
        if (histo[(int)edge_mag[j*cols+i]]>max)
         max = histo[(int)edge_mag[j*cols+i]];
         
        //printf("%f\t%d\n",edge_mag[j*cols+i],histo[(int)edge_mag[j*cols+i]]);
     }
   }

// Ostu Process
  // T = k
  
  
  float vbmax=0;
  int kmax=0;
  float p1;
  float mean;
  float mg;
  
  for (k=0;k<256;k++)
  {
  // caculate p1
  p1=0;
   for (i=0; i<256; i++)
   {
       if (i<=k)
         p1 = p1 + histo[i];
   }
   p1=p1/(dcols*drows);
   //Compute the accumulative means
  mean=0;
  mg=0;
   for (i=0; i<256; i++)
    { 
     mg = mg + i*histo[i];
       if (i<=k)
         mean = mean + i*histo[i];
   
    }
   mg = mg/(dcols*drows);
   mean = mean/(dcols*drows);
   
   //printf("%f\t%f\t%f\n",p1,mean,mg);
   //Compute the global intensity variance
   

   
   //Compute the between-class variance
   vb[k] = sqrt(pow(mg*p1-mean,2)/(p1*(1-p1)));
   if (vb[k]>=vbmax)
      {
      
        kmax=k;
        vbmax = vb[k];
      }
   //printf("%f\t%d\n",vb[k],k);
   }// end of k loop
   //system("pause");   
   printf("%d\n",kmax);
   
   // rescale the image;
   for (j=r*drows; j<(r+1)*drows; j++)
   {
     for (i=c*dcols; i<(c+1)*dcols; i++)
     {  
        if (edge_mag[j*cols+i] >= kmax)
           {
           edge_mag[j*cols+i] = 255;
           //system("pause");
           }
          else 
           edge_mag[j*cols+i] = 0;
        /*
        if (edge_mag[j*cols+i] < 0 || edge_mag[j*cols+i] > 255)   
        {
         printf("%d\n",edge_mag[j*cols+i]);
         system("pause");
         }
         */
     }
     
  }
  
  //system("pause");  
 }//end of c loop
 }//end of r loop
}
