#include "Morphology.h"

#include <vector>
#include <algorithm>
using std::vector;

namespace imageOperator
{

Image *median(const Image *image, const unsigned int factor)
{
    Image *img = 0;

    int pixel;
    if (image && factor>0) {
        img = new Image(image->getWidth(), image->getHeight(), image->getChannel() );
        for (unsigned int i=0; i<(image->getHeight()-factor); i++ ) {
            for (unsigned int j=0; j<(image->getWidth()-factor); j++ ) {
                pixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++) {
                    vector<int> pixels;
                    for (unsigned int ki=0; ki<factor; ki++ ) {
                        for (unsigned int kj=0; kj<factor; kj++ ) {
                            pixels.push_back( (image->getPixel(i+ki,j+kj)>>(8*(image->getChannel()-k)))&0xFF );
                        }
                    }
                    sort( pixels.begin(), pixels.end() );//sorts the vector to get the median
                    pixel = pixel | pixels.at( (int)(pixels.size()/2) ) ; //gets the median value
                    if (k<image->getChannel()) pixel = pixel << 8;
                }

                img->setPixel(i+( (int)(factor/2) ), j+( (int)(factor/2) ), pixel);

            }
        }
    }

    return img;
}

Image *dilation(const Image *image, const unsigned int factor)
{
    Image *img = 0;

    int pixel, maxPixel, tempPixel;
    if (image && factor>0) {
        img = new Image(image->getWidth(), image->getHeight(), image->getChannel() );
        for (unsigned int i=0; i<(image->getHeight()-factor); i++ ) {
            for (unsigned int j=0; j<(image->getWidth()-factor); j++ ) {
                pixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++) {
                    maxPixel = 0;
                    for (unsigned int ki=0; ki<factor; ki++ ) {
                        for (unsigned int kj=0; kj<factor; kj++ ) {
                            tempPixel = ( (image->getPixel(i+ki,j+kj)>>(8*(image->getChannel()-k)))&0xFF );
                            if( tempPixel>maxPixel ) maxPixel = tempPixel;
                        }
                    }
                    pixel = pixel | maxPixel;
                    if (k<image->getChannel()) pixel = pixel << 8;
                }

                img->setPixel(i+( (int)(factor/2) ), j+( (int)(factor/2) ), pixel);

            }
        }
    }

    return img;
}


Image *erosion(const Image *image, const unsigned int factor)
{
    Image *img = 0;

    int pixel, minPixel, tempPixel;
    if (image && factor>0) {
        img = new Image(image->getWidth(), image->getHeight(), image->getChannel() );
        for (unsigned int i=0; i<(image->getHeight()-factor); i++ ) {
            for (unsigned int j=0; j<(image->getWidth()-factor); j++ ) {
                pixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++) {
                    minPixel = 0xFF;
                    for (unsigned int ki=0; ki<factor; ki++ ) {
                        for (unsigned int kj=0; kj<factor; kj++ ) {
                            tempPixel = ( (image->getPixel(i+ki,j+kj)>>(8*(image->getChannel()-k)))&0xFF );
                            if( tempPixel<minPixel ) minPixel = tempPixel;
                        }
                    }
                    pixel = pixel | minPixel;
                    if (k<image->getChannel()) pixel = pixel << 8;
                }

                img->setPixel(i+( (int)(factor/2) ), j+( (int)(factor/2) ), pixel);

            }
        }
    }

    return img;
}

Image *opening(const Image *image, const unsigned int factor) //erosion->dilation
{
    Image *erosionImg = erosion(image, factor);
    Image *openingImg = dilation(erosionImg, factor);
    delete erosionImg;
    return openingImg;
}

Image *closing(const Image *image, const unsigned int factor) //dilation->erosion
{
    Image *dilationImg = dilation(image, factor);
    Image *closingImg = erosion(dilationImg, factor);
    delete dilationImg;
    return closingImg;
}

}//end namespace imageOperator
