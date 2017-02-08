#include <stdio.h>

int main()
{
  float matrix1[6][6];
  float matrix2[6][6];
  float matrix3[6][6];

  int i, j, k;

  printf("input matrix1\n");

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      scanf("%f", &matrix1[i][j]);
    }
  }

  printf("input matrix2\n");

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      scanf("%f", &matrix2[i][j]);
    }
  }

  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      matrix3[i][j] = 0.0;
      for (k = 0; k < 6; k++) {
	matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
      }
    }
  }

  printf("\n");
  for (i = 0; i < 6; i++) {
    for (j = 0; j < 6; j++) {
      printf("%f ", matrix3[i][j]);
    }
    printf("\n");
  }

  return 0;
}
