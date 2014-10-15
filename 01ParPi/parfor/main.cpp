#include <vector>
#include <iostream>
#include <limits>
#include <iomanip>
#include <omp.h>

int main() {
    long numSteps = 100000000;
    double x;
    double step = 1.0 / (double) numSteps;
    int i;
    double sum = 0, localSum;

    #pragma omp parallel private(localSum, x)
    {
        localSum = 0;

        #pragma omp for
        for(i = 0; i < numSteps; i++) {
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
