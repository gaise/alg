#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
  int n, i;
  double x[10000];
  double y[10000];
  FILE *gp;
  
  n = 0;

  scanf("%lf", &x[0]);
  y[0] = exp(pow(x[0],4)) - M_PI;

  for (i = 0; i < 10000; i++) {
    x[i+1] = x[i] + y[i] / (4*pow(x[i],3)*exp(pow(x[i],4)));
    y[i+1] = exp(pow(x[i+1],4)) - M_PI;
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
