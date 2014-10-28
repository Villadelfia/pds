#include "imgutil.h"
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <QImage>
#include <string>
#include <iostream>
#include <tuple>


imgdata imgutil::getImageData(const std::string& fileName) {
    QImage img;

    if(!img.load(fileName.c_str()))
        return std::make_tuple(nullptr, 0, 0);

    int w = img.width();
    int h = img.height();
    float* pValues = new float[w * h];

    #pragma omp parallel for
    for(int y = 0 ; y < h ; y++) {
        for(int x = 0 ; x < w ; x++) {
            QRgb pixel = img.pixel(x, y);

            pValues[x + y * w] = (float)qGray(pixel);
        }
    }

    return std::make_tuple(pValues, w, h);
}

void imgutil::saveImageData(const float* pValues, int w, int h,
                            const std::string& fileName) {
    QImage img(w, h, QImage::Format_RGB32);

    #pragma omp parallel for
    for(int y = 0 ; y < h ; y++) {
        for(int x = 0 ; x < w ; x++) {
            int value = (int)pValues[x + y * w];

            if(value < 0)
                value = 0;
            else if(value > 255)
                value = 255;

            img.setPixel(x, y, qRgb(value, value, value));
        }
    }

    img.save(fileName.c_str());
}

void imgutil::kernelNorm(float* kernel, int w, int h, float scale,
                         float offset) {
    if(scale == 0) {
        for(int y = 0 ; y < h ; y++) {
            for(int x = 0 ; x < w ; x++)
                scale += kernel[x + y * w];
        }
    }

    for(int y = 0 ; y < h ; y++) {
        for(int x = 0 ; x < w ; x++) {
            kernel[x + y * w] -= offset;
            kernel[x + y * w] /= scale;
        }
    }
}

