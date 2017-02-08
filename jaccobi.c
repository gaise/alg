#include <stdio.h>
#include <stdlib.h>

#define N 2
#define ITER 20

double *mvmul(double a[N][N], double x[N], double *b)
{
  int i, j;

  for (i = 0; i < N; i++) {
    b[i] = 0.0;
    for (j = 0; j < N; j++) {
      b[i] += a[i][j] * x[j];
    }
  }

  return b;
}

double *mvadd(double a[N], double b[N], double *c)
{
  int i;

  for (i = 0; i < N; i++) {
    c[i] = a[i] + b[i];
  }

  return c;
}

double *mvsub(double a[N], double b[N], double *c)
{
  int i;

  for (i = 0; i < N; i++) {
    c[i] = a[i] - b[i];
  }

  return c;
}

double norm(double a[N])
{
  int i;
  double x = 0;

  for (i = 0; i < N; i++) {
    x += a[i] * a[i];
  }

  return x;
}
	
int main(void)
{
  double a[N][N] = {{5,3},{2,4}};
    /* {{9,3,2,5,6},{1,7,2,2,4},{5,2,8,3,5},{1,2,1,5,3},{2,8,7,9,10}}; */
  double a_t[N][N];
  double d[N][N];
  double buf;
  double x0[N], x1[N], x2[N];
  double b[N] = {39,-4};

  double r[ITER+1];

  int i, j, k;

  FILE *gp;

  for (i = 0; i < N; i++) {
    x0[i] = 0.0;
    for (j = 0; j < N; j++) {
      a_t[i][j] = (i==j)?a[i][j]:0.0;
      d[i][j] = (i==j)?1.0:0.0;
    }
  }

  for (i = 0; i < N; i++) {
    buf = 1 / a_t[i][i];
    for (j = 0; j < N; j++) {
      a_t[i][j] *= buf;
      d[i][j] *= buf;
    }
    for (j = 0; j < N; j++) {
      if (i != j) {
	buf = a_t[j][i];
	for (k = 0; k < N; k++) {
	  a_t[j][k] -= a_t[i][k] * buf;
	  d[j][k] -= d[i][k] * buf;
	}
      }
    }
  }

  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      printf("%f ", d[i][j]);
    }
    printf("\n");
  }

  mvmul(a,x0,x2);
  mvsub(b,x2,x1);
  r[0] = norm(x1);

  for (i = 0; i < ITER; i++) {
    if ((i%2) == 0) {
      mvmul(a,x0,x2);
      mvsub(b,x2,x1);
      mvmul(d,x1,x2);
      mvadd(x0,x2,x1);
      mvmul(a,x1,x2);
      mvsub(b,x2,x0);
      r[i+1] = norm(x0);
      for (j = 0; j < N; j++) {
	printf("%f ", x1[j]);
      }
      printf("\n");
    }
    else {
      mvmul(a,x1,x2);
      mvsub(b,x2,x0);
      mvmul(d,x0,x2);
      mvadd(x1,x2,x0);
      mvmul(a,x0,x2);
      mvsub(b,x2,x1);
      r[i+1] = norm(x1);
      for (j = 0; j < N; j++) {
	printf("%f ", x0[j]);
      }
      printf("\n");
    }
  }
  
  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set logscale y\n");
  fprintf(gp, "plot '-' with lines title 'zansa'\n");
  for (i = 0; i < ITER+1; i++) fprintf(gp, "%f %f\n", (float)i, r[i]);
  fprintf(gp, "e\n");
  fprintf(gp, "quit\n");

  pclose(gp);

  return 0;
}
  

  

  
  
