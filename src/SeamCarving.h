#ifndef __SEAM_CARVING
#define __SEAM_CARVING

#include "RGB.h"
#include "Image.h"
#include "Kernel.h"

Kernel *energyKernel(const Image *image, const Kernel *kernelA, const Kernel *kernelB);
Kernel *sobelEnergyKernel(const Image *img);

Image  *seamCarvingColumn (const Image *image, const Kernel *energy);
Image  *seamCarvingRemoveColumn(const Image *image, int nCol, const Kernel *kerGx=0, const Kernel *kerGy=0);

#endif
