#ifndef SHARPEN_H
#define SHARPEN_H

#include "Kernel.h"
#include "Image.h"
#include "ImageHandler.h"

namespace imageOperator {

enum LaplacianKernelType {
    LAPLACIAN_KERNEL_TYPE_DEFAULT,
    LAPLACIAN_KERNEL_TYPE_SHARPER
};

Kernel *getLaplacianKernel(LaplacianKernelType kernelType=LAPLACIAN_KERNEL_TYPE_DEFAULT);

Image *laplacian(Image *image, LaplacianKernelType kernelType=LAPLACIAN_KERNEL_TYPE_DEFAULT);

Image *highPassOperator(Image *image, unsigned int factor = 3);

}//end namespace imageOperator

#endif
