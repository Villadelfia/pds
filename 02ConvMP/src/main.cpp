#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <QImage>
#include <vector>
#include <string>
#include <iostream>


float* getImageData(const std::string& fileName, int* w, int* h); // you MUST delete[] this memory when no longer needed.
void saveImageData(const float* pValues, int w, int h, const std::string& fileName);
void normImageData(float* pValues, int w, int h);

int main(int argc, char** argv) {
    (void) argc;
    (void) argv;
    // TODO!

    return 0;
}

//
// Implementation of utility functions
//

float* getImageData(const std::string& fileName, int* imgWidth, int* imgHeight) {
    QImage img;

    if(!img.load(fileName.c_str()))
        return 0;

    int w = img.width();
    int h = img.height();
    float* pValues = new float[w * h];

    for(int y = 0 ; y < h ; y++) {
        for(int x = 0 ; x < w ; x++) {
            QRgb pixel = img.pixel(x, y);

            pValues[x + y * w] = (float)qGray(pixel);
        }
    }

    *imgWidth = w;
    *imgHeight = h;

    return pValues;
}

void saveImageData(const float* pValues, int w, int h, const std::string& fileName) {
    QImage img(w, h, QImage::Format_RGB32);

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

    if(img.save(fileName.c_str()))
        std::cerr << "Saved " << img.width() << "x" << img.height() << " pixels to '" << fileName << "'" << std::endl;
    else
        std::cerr << "Unable to save pixels to " << fileName << std::endl;
}

void normImageData(float* pValues, int w, int h) {
    float sum = 0;

    for(int y = 0 ; y < h ; y++)
        for(int x = 0 ; x < w ; x++)
            sum += pValues[x + y * w];

    for(int y = 0 ; y < h ; y++)
        for(int x = 0 ; x < w ; x++)
            pValues[x + y * w] /= sum;
}

