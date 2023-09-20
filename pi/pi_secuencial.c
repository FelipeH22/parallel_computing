#include <stdio.h>
#include <math.h>

int main()
{
    int i,n;
    double sum=.0;
    double pi, term;
    int iterations = 1e08;
    for (i=0; i<iterations; i++)
    {
        term = pow(-1, i) / (2*i+1);
        sum+=term;
    }
    pi = 4*sum;
    printf("Pi: %f", pi);
    return 0;
}