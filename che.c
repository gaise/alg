#include <stdio.h>
#include <stdlib.h>

#define N 1000

int main(void)
{
  double p1[N+1], p2[N+1], p3[N+1], p4[N+1], p5[N+1];
  double x[N+1];

  int i;

  FILE *gp;

  for (i = 0; i < N+1; i++) {
    x[i] = -1.0 + i * (2.0 / N);
    p1[i] = x[i];
    p2[i] = 2.0 * x[i] * p1[i] - 1.0;
    p3[i] = 2.0 * x[i] * p2[i] - p1[i];
    p4[i] = 2.0 * x[i] * p3[i] - p2[i];
    p5[i] = 2.0 * x[i] * p4[i] - p3[i];
  }

  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "set xrange [-1.0:1.0]\n");
  fprintf(gp, "set yrange [-1.0:1.0]\n");
  fprintf(gp, "plot '-' with lines title 'p1', '-' with lines title 'p2', '-' with lines title 'p3', '-' with lines title 'p4', '-' with lines title 'p5'\n");
  for (i = 0; i < N+1; i++) fprintf(gp, "%f %f\n", x[i], p1[i]);
  fprintf(gp, "e\n");
  for (i = 0; i < N; i++) fprintf(gp, "%f %f\n", x[i], p2[i]);
  fprintf(gp, "e\n");
  for (i = 0; i < N; i++) fprintf(gp, "%f %f\n", x[i], p3[i]);
  fprintf(gp, "e\n");
  for (i = 0; i < N; i++) fprintf(gp, "%f %f\n", x[i], p4[i]);
  fprintf(gp, "e\n");
  for (i = 0; i < N; i++) fprintf(gp, "%f %f\n", x[i], p5[i]);
  fprintf(gp, "e\n");
  fprintf(gp, "quit\n");
  pclose(gp);
  
  return 0;

}
