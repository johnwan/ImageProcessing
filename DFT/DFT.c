#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int DFT(int dir,int m,int n,float *x1,float *y1)
{
    long i,j,k;
    double arg;
    double cosarg,sinarg;
    double *x2=NULL,*y2=NULL,
           *x3=NULL,*y3=NULL;

    x2 = malloc(m*n*sizeof(double));
    y2 = malloc(m*n*sizeof(double));
    x3 = malloc(m*n*sizeof(double));
    y3 = malloc(m*n*sizeof(double));
    
    //printf("m=%d\tn=%d\n",m,n);
    /*
    if (x2 == NULL || y2 == NULL)
    return(0);
    */
/*
for (int y = 0; y < N; y++) {
for (int u = 0; u < M; u++) {
Preal[M*y+u] = 0;
Pimg[M*y+u] = 0;
for (int x = 0; x < M; x++) {
Preal[M*y+u] += f[M*y + x] * cos((2 * PI * u * x) / M);
Pimg[M*y+u] += -f[M*y + x] * sin((2 * PI * u * x) / M);
}
}
}

for (int x = 0; x < M; y++) {
for (int v = 0; v < N; u++) {
Preal[M*v+x] = 0;
Pimg[M*v+x] = 0;
for (int y = 0; y < M; x++) {
Preal[M*v+x] += f[M*y + x] * cos((2 * PI * u * x) / M);
Pimg[M*v+x] += -f[M*y + x] * sin((2 * PI * u * x) / M);
}
}
}
*/



    // DFT of the P = 2*rows-1
    for (i=0;i<n;i++) {
     for (j=0;j<m;j++)
     {
        x2[m*i+j] = 0;
        y2[m*i+j] = 0;
        
        for (k=0;k<m;k++) 
        {    
            //printf("m*i+j=%d\tm*i+k=%d\n",m*i+j,m*i+k);
            arg = - dir * 2.0 * 3.141592654 * (double)j / (double)m;
            cosarg = cos(k * arg);
            sinarg = sin(k * arg);
            x2[m*i+j] += (x1[m*i+k] * cosarg);
            y2[m*i+j] += (-x1[m*i+k] * sinarg);
            //x2[m*i+j] += (x1[m*i+k] * cosarg - y1[m*i+k] * sinarg);
          //  y2[m*i+j] += (x1[m*i+k] * sinarg + y1[m*i+k] * cosarg);
        }
     }
    }
    
    
    // DFT of the Q = 2*cols-1
    for (i=0;i<n;i++)  {
      for (j=0;j<m;j++)
     {  
        
        for (k=0;k<n;k++) 
        {    
            arg = - dir * 2.0 * 3.141592654 * (double)i / (double)n;
            cosarg = cos(k * arg);
            sinarg = sin(k * arg);
            x3[m*i+j] += (x2[m*k+j] * cosarg);
            y3[m*i+j] += (-x2[m*k+j] * sinarg);
            //x3[m*i+j] += (x2[m*k+j] * cosarg - y2[m*k+j] * sinarg);
            //y3[m*i+j] += (x2[m*k+j] * sinarg + y2[m*k+j] * cosarg);
            
        }
     }
    }    
    
    
    /* Copy the data back based on DFT or IDFT */
    if (dir == 1) 
    {   printf("IDFT");
        for (i=0;i<n;i++) {
         for (j=0;j<m;j++)         
        {   
            x1[m*i+j] = x3[m*i+j] / ((float)m * (float)n);
            y1[m*i+j] = y3[m*i+j] / ((float)m * (float)n);
        }
        } 
    } 
    else 
    {   printf("DFT");
        for (i=0;i<n;i++) {
         for (j=0;j<m;j++)
         
        {   
            x1[m*i+j] = x3[m*i+j];
            y1[m*i+j] = y3[m*i+j];
        }
        } 
    }

    free(x2);
    free(y2);
    free(x3);
    free(y3);
    return(1);
    
}
