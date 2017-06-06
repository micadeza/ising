#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../src/metropolis.h"

int main() {
  int i, j, niter, n;

  n = 10;
  int *lattice = (int *)malloc(n*n*sizeof(int));
  for (j=0;j<n*n;j++) *(lattice + j) = 1;
  niter = 1000000;
  srand(time(NULL));

  FILE *output = fopen("histogram.txt", "w");
  if (output == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }

  for(i=0;i<niter;i++) {
    fprintf(output, "%d\n", pick_site(lattice, n)); //datos para histograma
  }

  fclose(output);
  return 0;
}
