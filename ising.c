#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>


#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
  float *params = malloc(2*sizeof(float));

  *params = 0;
  *(params+1) = 0;

  FILE *output = fopen("output.txt", "w");
  if (output == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }

  int n = 32;
  int *lattice = malloc(n * n * sizeof(int));

   float prob = 0.5; //Probabilidad inicial de llenado de la red. Está elegida de forma tal que los spines arranquen
   //con la condición inicial de forma mas aleatoria posible, asi tarda menos en termalizar.

   int nter =20000; //es la cantidad de pasos para el sistema termalice.
   //int corr = 2000;
   srand(time(NULL));
   float B = 0.0;
   for (int l=0;l<6;l++){
     float J=0.1+l*(0.1);
     float J2=0;
     int jmax= 2000;
     int hmax= 2*(n*n);

     params = fill_lattice(lattice, n, prob, params);
   //print_lattice(lattice, n, *params, *(params+1));
    for (int k=0;k<600;k++) {
     float T=6-k*(0.01); //No poner T=0
     //float T=4;
     for (int i = 0; i < nter; i++) {
       params = metropolis(lattice, n, T, params, B, J);
     } //for para termalizar. Una vez que el sistema queda termalizado, hago metrópolis para guardar los datos.
     float mag=0; //Armo la variable magnetizacion donde se va a ir acumulando la mag para cada T.
     float energia=0;

     for (int j =0; j <jmax; j++) {
       for (int h= 0; h<hmax; h++){
         params = metropolis (lattice, n, T, params, B, J);
         }
       mag += *(params+1);
       energia += *(params);
       //mag = *(params+1);
       //energia= *(params);
       //printf("%f %f %f %f %f %f\n", energia,mag,m,e,energia2,mag2 );
    //   print_lattice(lattice,n,energia,mag);
     }

     mag=mag/(jmax);
      energia=energia/(jmax); //Jmax cantidad de muestras
      //float cv=0;
      //mag2=mag2-(mag*mag)/T;
      //  cv = energia2-(energia*energia)/(T*T);
      //printf("%f\n", (T*T) );
      //printf("%f %f %f %f\n",mag,mag/(n*n), energia2,energia2/(n*n) );
     //hmax tamaño del paso de correlacion.
    fprintf(output, "%f %f %f %f\n",J, T, mag/(n*n), energia); //escribe: mag ener
   }
  }

  free(lattice);
  return 0;
}
