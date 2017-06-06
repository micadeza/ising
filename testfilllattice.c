#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../src/lattice.h"

int main () {

int n=32;
int *lattice = (int *)malloc(n*n*sizeof(int));
float *params = malloc(2*sizeof(float));
int kmax=10000;
float ener = *params;
float mag = *(params+1);
srand(time(NULL));
FILE *output3 = fopen("t.txt", "w");
if (output3 == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}
for (int i=0;i<11;i++){
  float prob=0+i*(0.1);
  *params = 0;
  *(params+1) = 0;
  float mup=0;
  float mdown=0;
  for (int k=0;k<kmax;k++){
    params=fill_lattice(lattice,n,prob,params);
    mup = mup + ((*(params+1))+(n*n))/2; // m me guarda la cantidad de spines up
    mdown = mdown + ((n*n)-(*(params+1)))/2;
    print_lattice(lattice,n,ener,mag);
  }
    mup=mup/(n*n);
    mdown=mdown/(n*n);
    printf("%f %f \n", mup, mdown);
    printf("%f %f \n", mup/kmax, mdown/kmax);
  fprintf(output3,"%f %f %f \n" , prob, mup/kmax, mdown/kmax);

}
fclose(output3);
return 0;


}
