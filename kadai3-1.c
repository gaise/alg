#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define GAN 2
#define BETA 0.5

double f(double x)
{
  return (exp(pow(x,4)) - M_PI);
}

double g(double x)
{
  return (4*pow(x,3)*exp(pow(x,4)));
}
  
int main(int argc, char *argv[])
{
  int n, i, j;
  double x[10000];
  double y[10000];
  FILE *gp;
  
  n = 0;

  scanf("%lf", &x[0]);
  y[0] = exp(pow(x[0],4)) - M_PI;

  for (i = 0; i < 10000; i++) {
    j = 1;
    printf("%d\n", i);
    while(1) {
      double l, r;
      l = fabs(f(x[i] - pow(GAN, -j) * f(x[i]) / g(x[i])));
      r = (1 - BETA*pow(GAN, -j) * fabs(f(x[i])));
      if (l <= r) break;
      j++;
    }
    
    x[i+1] = x[i] + pow(GAN,-j)*y[i] / g(x[i]);
    y[i+1] = f(x[i+1]);
    n++;
    if (x[i] == x[i+1]) break;
  }

  printf("%d\n", n);
  printf("%lf\n", exp(0) - M_PI);

  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set xrange [-1:5]\n");
  fprintf(gp, "set yrange [-100:100]\n");
  fprintf(gp, "plot '-' with lines linetype 1 title \"newton\"\n");

  for (i = 0; i <= n; i++) {
    fprintf(gp, "%lf\t%lf\n", x[i], y[i]);
  }

  fprintf(gp, "e\n");

  pclose(gp);

  return 0;
}
