#ifndef SMOOTH_H
#define SMOOTH_H

#include "Kernel.h"
#include "Image.h"
#include "ImageHandler.h"

namespace imageOperator {

enum GaussianKernelType {
    GAUSSIAN_KERNEL_TYPE_3X3,
    GAUSSIAN_KERNEL_TYPE_5X5
};

Kernel *getGaussianKernel(GaussianKernelType kernelType=GAUSSIAN_KERNEL_TYPE_3X3);
Kernel *getGaussianKernel(unsigned int size, double scale);

Image *gaussian(Image *image, GaussianKernelType kernelType=GAUSSIAN_KERNEL_TYPE_3X3);

Image *lowPassOperator(Image *image, unsigned int factor = 3);

}//end namespace imageOperator

#endif
