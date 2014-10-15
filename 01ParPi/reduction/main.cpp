#include <iostream>
#include <iomanip>
#include <limits>

int main() {
    long numSteps = 100000000;
    double x, sum = 0;
    double step = 1.0 / (double) numSteps;
    int i;

    #pragma omp parallel for private(x) reduction(+:sum)
    for(i = 0; i < numSteps; i++) {
        x = (i - 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = step * sum;
    std::cout << std::setprecision(std::numeric_limits<double>::digits10) <<
        pi << std::endl;
}
