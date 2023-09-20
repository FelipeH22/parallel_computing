#include "omp.h"
#include "stdio.h"

static long num_steps = 1e10;
#define PAD 8
double step;
#define THREADS 6


void main ()
{
    double start;
    double end;
    int i, nthreads;
    double pi, sum[THREADS][PAD];
    step = 1.0/(double) num_steps;
    omp_set_num_threads(THREADS);
    start = omp_get_wtime();
    #pragma omp parallel
    {
        int i, id,nthrds;
        double x;
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();
        if (id == 0) nthreads = nthrds;
        for (i=id, sum[id][0]=0.0 ;i< num_steps; i=i+nthrds) {
            x = (i+0.5)*step;
            sum[id][0] += 4.0/(1.0+x*x);
        }
    }
    for(i=0, pi=0.0;i<nthreads;i++)pi += sum[i][0] * step;
    end = omp_get_wtime();
    printf("Time: %f seconds\n", end - start);

}