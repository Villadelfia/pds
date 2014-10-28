#include <iostream>
#include <cstdio>
#include <tuple>
#include <algorithm>
#include <string>
#include "imgutil.h"

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
    float offset = std::atof(argv[3]);
    float scale = std::atof(argv[4]);
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
    int padw = kernelw / 2;
    int padh = kernelh / 2;
    size_t size = (inputw + (2 * padw)) * (inputh + (2 * padh));
    float* paddedinput = new float[size];
    std::fill_n(paddedinput, size, 0);

    #pragma omp parallel for
    for(int i = 0; i < inputh; ++i) {
        int paddedoffset = (padh + i) * (inputw + 2 * padw) + padw;
        std::copy_n(input + (i * inputw), inputw, paddedinput + (paddedoffset));
    }

    delete[] input;

    //**************************************************************************
    // Convolve.
    float* output = new float[inputw * inputh];
    int outputw = inputw + (2 * padw);

    #pragma omp parallel for schedule(runtime)
    for(int x = 0; x < inputw; ++x) {
        for(int y = 0; y < inputh; ++y) {
            float result = 0;
            for(int i = 0; i < kernelw; ++i) {
                for(int j = 0; j < kernelh; ++j) {
                    result +=
                        kernel[i + j * kernelw] *
                        paddedinput[(i + x) + (j + y) * outputw];
                }
            }
            output[y * inputw + x] = result;
        }
    }

    //**************************************************************************
    // Write output.
    imgutil::saveImageData(output, inputw, inputh, outputFile);
    delete[] kernel;
    delete[] output;
    delete[] paddedinput;
}

