#include <iostream>

int main() {
    long numSteps = 100000000;
    double x, sum = 0;
    double step = 1.0 / (double) numSteps;
    int i;

    #pragma omp parallel for private(i) reduction(+:sum)
    for(i = 0; i < numSteps; i++) {
        x = (i - 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    double pi = step * sum;
}
