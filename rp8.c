#include <stdio.h>
#include <stdlib.h>

int main()
{
  int n, m, l;
  int i, j, k;

  printf("input matrix size\n");
  printf("n :\n");

  scanf("%d", &n);

  printf("m :\n");

  scanf("%d", &m);

  printf("l :\n");

  scanf("%d", &l);

  float **matrix1;
  matrix1 = malloc(sizeof(float *) * n);
  for (i = 0; i < n; i++) {
    matrix1[i] = malloc(sizeof(float) * m);
  }

  float **matrix2;
  matrix2 = malloc(sizeof(float *) * m);
  for (i = 0; i < m; i++) {
    matrix2[i] = malloc(sizeof(float) * l);
  }

  float **matrix3;
  matrix3 = malloc(sizeof(float *) * n);
  for (i = 0; i < n; i++) {
    matrix3[i] = malloc(sizeof(float) * l);
  }

  printf("input matrix1\n");

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      scanf("%f", &matrix1[i][j]);
    }
  }

  printf("input matrix2\n");

  for (i = 0; i < m; i++) {
    for (j = 0; j < l; j++) {
      scanf("%f", &matrix2[i][j]);
    }
  }
  
  for (i = 0; i < n; i++) {
    for (j = 0; j < l; j++) {
      matrix3[i][j] = 0;
      for (k = 0; k < m; k++) {
	matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }

  for (i = 0; i < n; i++) {
    for (j = 0; j < l; j++) {
      printf("%f ", matrix3[i][j]);
    }
    printf("\n");
  }

  return 0;

}
