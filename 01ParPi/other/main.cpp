#include <vector>
#include <omp.h>

int main() {
    long numSteps = 100000000;
    double x;
    double step = 1.0 / (double) numSteps;
    int i, begin, end, chunksize;
    double sum[40];
    for(i = 0; i < 40; ++i)
        sum[i] = 0;

    #pragma omp parallel private(begin, end, chunksize, i)
    {
        chunksize = numSteps / omp_get_num_threads();
        begin = omp_get_thread_num() * chunksize;
        end = begin + chunksize;
        for(i = begin; i < end; i++) {
            x = (i - 0.5) * step;
            sum[omp_get_thread_num()] += 4.0 / (1.0 + x * x);
        }
    }

    for(i = 1; i < 40; ++i) {
        sum[0] += sum[i];
    }
    double pi = step * sum[0];
}
