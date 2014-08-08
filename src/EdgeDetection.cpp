#include "EdgeDetection.h"

namespace imageOperator
{

Image *edgeDetection(const Image *image, const Kernel *kernelA, const Kernel *kernelB) {
    double operationA, operationB;
    Image *img = 0;

    int pixel, temp;

    if (image && kernelA && kernelB && kernelA->getHeight()==kernelB->getHeight() && kernelA->getWidth()==kernelB->getWidth()) {
        img = new Image(image->getWidth(), image->getHeight(), image->getChannel() );
        for (unsigned int i=0; i<(image->getHeight()-kernelA->getHeight()); i++ ) {
            for (unsigned int j=0; j<(image->getWidth()-kernelA->getWidth()); j++ ) {
                pixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++) {
                    operationA = operationB = 0.0;
                    for (unsigned int ki=0; ki<kernelA->getHeight(); ki++ ) {
                        for (unsigned int kj=0; kj<kernelA->getWidth(); kj++ ) {
                            operationA += ( (image->getPixel(i+ki,j+kj)>>(8*(image->getChannel()-k)))&0xFF )*kernelA->get(ki, kj);
                            operationB += ( (image->getPixel(i+ki,j+kj)>>(8*(image->getChannel()-k)))&0xFF )*kernelB->get(ki, kj);
                        }
                    }
                    temp = ( ((int)floor(operationA))&0xFF ) + ( ((int)floor(operationB))&0xFF );
                    if (temp>0xFF) temp = 0xFF;
                    pixel = pixel | temp;
                    if (k<image->getChannel()) pixel = pixel << 8;
                }

                //img->setPixel(i+(int)(kernelA->getHeight()/2), j+(int)(kernelA->getWidth()/2), 0xFF - pixel); //inverte cor
                img->setPixel(i+(int)(kernelA->getHeight()/2), j+(int)(kernelA->getWidth()/2), pixel);
            }
        }
    }

    return img;
}

Image *robertsOperator(const Image *image)
{
    Kernel kA(2, 2);
    kA.set(0,0,1.0); kA.set(0,1,0.0);
    kA.set(1,0,0.0); kA.set(1,1,-4.0);

    Kernel kB(2, 2);
    kB.set(0,0,0.0); kB.set(0,1,1.0);
    kB.set(1,0,-1.0); kB.set(1,1,0.0);

    return edgeDetection(image, &kA, &kB);
}

Image *sobelOperator(const Image *image)
{
    Kernel kA(3, 3);
    kA.set(0,0,-1.0); kA.set(0,1,-2.0); kA.set(0,1,-1.0);
    kA.set(1,0,0.0); kA.set(1,1,0.0); kA.set(1,1,0.0);
    kA.set(2,0,1.0); kA.set(2,1,2.0); kA.set(2,1,1.0);

    Kernel kB(3, 3);
    kB.set(0,0,-1.0); kB.set(0,1,0.0); kB.set(0,1,1.0);
    kB.set(1,0,-2.0); kB.set(1,1,0.0); kB.set(1,1,2.0);
    kB.set(2,0,-1.0); kB.set(2,1,0.0); kB.set(2,1,1.0);

    return edgeDetection(image, &kA, &kB);
}

Image *prewittOperator(const Image *image)
{
    Kernel kA(3, 3);
    kA.set(0,0,-1.0); kA.set(0,1,-1.0); kA.set(0,1,-1.0);
    kA.set(1,0,0.0); kA.set(1,1,0.0); kA.set(1,1,0.0);
    kA.set(2,0,1.0); kA.set(2,1,1.0); kA.set(2,1,1.0);

    Kernel kB(3, 3);
    kB.set(0,0,-1.0); kB.set(0,1,0.0); kB.set(0,1,1.0);
    kB.set(1,0,-1.0); kB.set(1,1,0.0); kB.set(1,1,1.0);
    kB.set(2,0,-1.0); kB.set(2,1,0.0); kB.set(2,1,1.0);

    return edgeDetection(image, &kA, &kB);
}

}//end namespace imageOperator
