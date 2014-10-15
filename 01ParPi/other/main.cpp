#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>
#include <omp.h>

int main() {
    long numSteps = 100000000;
    double x;
    double step = 1.0 / (double) numSteps;
    int i, begin, end, chunksize;
    double sum = 0, localSum;

    #pragma omp parallel private(begin, end, chunksize, i, localSum, x)
    {
        chunksize = numSteps / omp_get_num_threads();
        begin = omp_get_thread_num() * chunksize;
        end = begin + chunksize;
        localSum = 0;

        for(i = begin; i < end; i++) {
            x = (i - 0.5) * step;
            localSum += 4.0 / (1.0 + x * x);
        }

        #pragma omp critical
        sum += localSum;
    }


    double pi = step * sum;
    std::cout << std::setprecision(std::numeric_limits<double>::digits10) <<
        pi << std::endl;
}
