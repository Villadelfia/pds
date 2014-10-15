#include <vector>
#include <omp.h>

int main() {
    long numSteps = 100000000;
    double x;
    double step = 1.0 / (double) numSteps;
    int i;
    double sum[40];
    for(i = 0; i < 40; ++i)
        sum[i] = 0;

    #pragma omp parallel for
    for(i = 0; i < numSteps; i++) {
        x = (i - 0.5) * step;
        sum[omp_get_thread_num()] += 4.0 / (1.0 + x * x);
    }

    for(i = 1; i < 40; ++i) {
        sum[0] += sum[i];
    }
    double pi = step * sum[0];
}
