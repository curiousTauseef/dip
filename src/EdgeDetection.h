#ifndef EDGE_DETECTION_H
#define EDGE_DETECTION_H

#include "ImageHandler.h"

namespace imageOperator
{
    Image *robertsOperator(const Image *image);
    Image *sobelOperator(const Image *image);
    Image *prewittOperator(const Image *image);
}

#endif
