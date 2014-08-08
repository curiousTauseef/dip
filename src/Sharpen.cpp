#include "Sharpen.h"

#include <cmath>

namespace imageOperator {

Kernel *getLaplacianKernel(LaplacianKernelType kernelType)
{
    Kernel *k = new Kernel(3,3);
    switch(kernelType){
        case LAPLACIAN_KERNEL_TYPE_DEFAULT:
            k->set(0,0,0.0);k->set(0,1,1.0);k->set(0,2,0.0);
            k->set(1,0,1.0);k->set(1,1,-4.0);k->set(1,2,1.0);
            k->set(2,0,0.0);k->set(2,1,1.0);k->set(2,2,0.0);
            break;
        case LAPLACIAN_KERNEL_TYPE_SHARPER:
            k->set(0,0,1.0);k->set(0,1,1.0);k->set(0,2,1.0);
            k->set(1,0,1.0);k->set(1,1,-8.0);k->set(1,2,1.0);
            k->set(2,0,1.0);k->set(2,1,1.0);k->set(2,2,1.0);
            break;
    };
    return k;
}

Image *laplacian(Image *image, LaplacianKernelType kernelType)
{
    Kernel *k = getLaplacianKernel(kernelType);
    Image *laplacianImage = convolution(image, k);
    delete k;
    return laplacianImage;
}

Image *highPassOperator(Image *image, unsigned int factor)
{
    Kernel k(factor, factor);
    for(unsigned int i = 0; i<factor; i++)
        for(unsigned int j = 0; j<factor; j++)
            k.set(i,j, -1.0/(factor*factor));
    k.set( ceil( ((double)factor)/2.0 ), ceil( ((double)factor)/2.0 ), ((factor*factor)-1.0)/(factor*factor) );
    return convolution(image, &k);
}

}//end namespace imageOperator

