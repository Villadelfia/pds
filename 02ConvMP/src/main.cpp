#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>
#include <string>
#include "imgutil.h"

inline float convolve(float* input, int inputw, int pad, float* kernel,
                      int kernelw, int x, int y) {
    x += pad;
    y += pad;
    inputw += 2 * pad;
    float result = 0;

    for(int i = x - pad; i <= x + pad; ++i) {
        for(int j = y - pad; j <= y + pad; ++j) {
            result +=
                kernel[(i - x + pad) + ((j - y + pad) * kernelw)] *
                input[i + j * inputw];
        }
    }

    return result;
}

int main(int argc, char** argv) {
    //**************************************************************************
    // Argument parsing.
    if(argc < 6) {
        std::cerr << "Usage: " << argv[0] << " input_file kernel_file offset "
                  << "scale output_file" << std::endl;
        return -1;
    }

    std::string inputFile = argv[1];
    std::string kernelFile = argv[2];
    double offset = std::atof(argv[3]);
    double scale = std::atof(argv[4]);
    std::string outputFile = argv[5];

    std::cout << "Convolving " << inputFile << " with kernel " << kernelFile <<
              " (offset: " << offset << ", scale: " << scale << ")" <<
              std::endl;

    //**************************************************************************
    // Get input.
    float* input, *kernel;
    int inputw, inputh, kernelw, kernelh;
    std::tie(input, inputw, inputh) = imgutil::getImageData(inputFile);
    std::tie(kernel, kernelw, kernelh) = imgutil::getImageData(kernelFile);
    imgutil::kernelNorm(kernel, kernelw, kernelh, scale, offset);


    //**************************************************************************
    // Pad.
    int padamt = kernelw / 2;
    size_t size = (inputw + (2 * padamt)) * (inputh + (2 * padamt));
    float* paddedinput = new float[size];
    std::fill_n(paddedinput, size, 0);

    #pragma omp parallel for
    for(int i = 0; i < inputh; ++i) {
        int paddedoffset = (padamt + i) * (inputw + 2 * padamt) + padamt;
        std::copy_n(input + (i * inputw), inputw, paddedinput + (paddedoffset));
    }

    delete[] input;

    //**************************************************************************
    // Convolve.
    float* output = new float[inputw * inputh];

    #pragma omp parallel for schedule(runtime)
    for(int x = 0; x < inputw; ++x) {
        for(int y = 0; y < inputh; ++y) {
            output[y * inputw + x] = convolve(paddedinput, inputw, padamt,
                                              kernel, kernelw, x, y);
        }
    }

    //**************************************************************************
    // Write output.
    imgutil::saveImageData(output, inputw, inputh, outputFile);
    delete[] kernel;
    delete[] output;
    delete[] paddedinput;
}

