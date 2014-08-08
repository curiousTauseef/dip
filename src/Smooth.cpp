#include "Smooth.h"

#include <cmath>
#include <iostream>
using namespace std;

namespace imageOperator {

Kernel *getGaussianKernel(GaussianKernelType kernelType)
{
    Kernel *gK = 0;
    switch(kernelType){
        case GAUSSIAN_KERNEL_TYPE_3X3:
            /*
            gK = new Kernel(3,3);
            gK->set(0,0,1.0/16.0);gK->set(0,1,2.0/16.0);gK->set(0,2,1.0/16.0);
            gK->set(1,0,2.0/16.0);gK->set(1,1,4.0/16.0);gK->set(1,2,2.0/16.0);
            gK->set(2,0,1.0/16.0);gK->set(2,1,2.0/16.0);gK->set(2,2,1.0/16.0);
            */
            gK = getGaussianKernel(3, 1.0);
            break;
        case GAUSSIAN_KERNEL_TYPE_5X5:
            /*
            gK = new Kernel(5,5);
            gK->set(0,0,1.0/256.0);gK->set(0,1,4.0/256.0);gK->set(0,2,6.0/256.0);gK->set(0,3,4.0/256.0);gK->set(0,4,1.0/256.0);
            gK->set(1,0,4.0/256.0);gK->set(1,1,16.0/256.0);gK->set(1,2,24.0/256.0);gK->set(1,3,16.0/256.0);gK->set(1,4,4.0/256.0);
            gK->set(2,0,6.0/256.0);gK->set(2,1,24.0/256.0);gK->set(2,2,36.0/256.0);gK->set(2,3,24.0/256.0);gK->set(2,4,6.0/256.0);
            gK->set(3,0,4.0/256.0);gK->set(3,1,16.0/256.0);gK->set(3,2,24.0/256.0);gK->set(3,3,16.0/256.0);gK->set(3,4,4.0/256.0);
            gK->set(4,0,1.0/256.0);gK->set(4,1,4.0/256.0);gK->set(4,2,6.0/256.0);gK->set(4,3,4.0/256.0);gK->set(4,4,1.0/256.0);
            */
            gK = getGaussianKernel(5, 1.0);
            break;
    };
    return gK;
}

Image *gaussian(Image *image, GaussianKernelType kernelType)
{
    Kernel *gK = getGaussianKernel(kernelType);
    Image *gaussianImage = convolution(image, gK);
    delete gK;
    return gaussianImage;
}

Kernel *getGaussianKernel(unsigned int size, double scale)
{
    Kernel *k = new Kernel(size, size);
    for(unsigned int i = 0; i<size; i++)
        for(unsigned int j = 0; j<size; j++){
            double x = -((int)size/2)+(int)i;
            double y = -((int)size/2)+(int)j;
            k->set(i,j, exp( (-(x*x + y*y))/(2*scale*scale) )/(2*3.1415926*scale*scale) );
        }
    return k;
}

Image *lowPassOperator(Image *image, unsigned int factor)
{
    Image *blurImage = 0;

    Kernel k(factor, factor);
    for(unsigned int i = 0; i<factor; i++)
        for(unsigned int j = 0; j<factor; j++)
            k.set(i,j, 1.0/(factor*factor));

    blurImage = convolution(image, &k);

    return blurImage;
}

}//end namespace imageOperator
