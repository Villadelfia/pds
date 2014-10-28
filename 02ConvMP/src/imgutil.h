#include <string>

#ifndef IMGUTIL_H_
#define IMGUTIL_H_

typedef std::tuple<float*,int,int> imgdata;
namespace imgutil {
    imgdata getImageData(const std::string& fileName);
    void saveImageData(const float* pValues, int w, int h, const std::string& fileName);
    void kernelNorm(float* kernel, int w, int h, float scale, float offset);
}

#endif /* IMGUTIL_H_ */

