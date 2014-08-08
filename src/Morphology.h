#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "Image.h"

namespace imageOperator
{
    Image *median(const Image *image, const unsigned int factor);

    Image *dilation(const Image *image, const unsigned int factor);
    Image *erosion(const Image *image, const unsigned int factor);
    Image *opening(const Image *image, const unsigned int factor); //erosion->dilation
    Image *closing(const Image *image, const unsigned int factor); //dilation->erosion
}

#endif
