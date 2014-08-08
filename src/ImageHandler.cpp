/**
developers:
    Rodrigo Caetano de Oliveira Rochas

PUC Minas - Pontifícia Universidade Católica de Minas Gerais
Ciência da Computação
*/


#include "ImageHandler.h"

namespace imageOperator
{

/*
   Converte uma imagem em escala de cinza.

Parâmetros:
   image - referência para a imagem que será convertida em uma outra imagem em escala de cinza.

Retorno:
     referência da nova imagem, em escala de cinza.
*/
Image *convertToGreyScale(const Image *image) {
    Image *greyImage = 0;

    if (image) {

        // Aloca imagem resultante.
        greyImage = new Image(image->getWidth(), image->getHeight(), Image::GREY_SCALE_IMAGE);

        int pixel, greyPixel;

        // Para cada pixel da imagem original, calcula-se o pixel correspondente na imagem em escala de cinza
        // somando-se as respectivas componentes (canais) do pixel original e obtendo-se a média aritimética entre
        // essas componentes.
        for (unsigned int i = 0; i<image->getHeight(); i++) {
            for (unsigned int j = 0; j<image->getWidth(); j++) {
                pixel = image->getPixel(i,j);
                greyPixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++)
                    greyPixel += (pixel>>(8*(image->getChannel()-k)))&0xFF;
                greyPixel = greyPixel/image->getChannel();

                // Uma vez calculado o pixel correspondente para a imagem em escala de cinza, o mesmo é inserido
                // na imagem resultante.
                greyImage->setPixel(i,j,greyPixel);
            }
        }
    }

    return greyImage;
}

Image *kernelToGreyScale(const Kernel *ker)
{
    if(!ker) return NULL;

    Image *kerImg = new Image(ker->getWidth(), ker->getHeight(), Image::GREY_SCALE_IMAGE);
    double maxVal = 0;
    for(int i = 0; i<ker->getHeight(); i++)
        for(int j = 0; j<ker->getWidth(); j++)
            if(ker->get(i, j)>maxVal)
                maxVal = ker->get(i, j);

    for(int i = 0; i<ker->getHeight(); i++)
        for(int j = 0; j<ker->getWidth(); j++)
            kerImg->setPixel(i, j, int((ker->get(i, j)/maxVal)*0xFF) );

    return kerImg;
}

Image *invertColour(const Image *image) {
    Image *nImage = 0;

    if (image) {

        // Aloca imagem resultante.
        nImage = new Image(image->getWidth(), image->getHeight(), image->getChannel());

        int pixel, nPixel;

        // Para cada pixel da imagem original, calcula-se o pixel correspondente na imagem em escala de cinza
        // somando-se as respectivas componentes (canais) do pixel original e obtendo-se a média aritimética entre
        // essas componentes.
        for (unsigned int i = 0; i<image->getHeight(); i++) {
            for (unsigned int j = 0; j<image->getWidth(); j++) {
                pixel = image->getPixel(i,j);
                nPixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++) {
                    nPixel = nPixel | ( 0xFF- ( (pixel>>(8*(image->getChannel()-k)))&0xFF ) );
                    if (k<image->getChannel()) nPixel = nPixel << 8;
                }

                // Uma vez calculado o pixel correspondente para a imagem em escala de cinza, o mesmo é inserido
                // na imagem resultante.
                nImage->setPixel(i,j,nPixel);
            }
        }
    }

    return nImage;
}

Image *transpose(const Image *image)
{
    if(!image) return NULL;

    Image *img = new Image(image->getHeight(), image->getWidth(), image->getChannel());
    for (unsigned int i = 0; i<image->getHeight(); i++) {
        for (unsigned int j = 0; j<image->getWidth(); j++) {
            img->setPixel(j,i, image->getPixel(i,j));
        }
    }
    return img;
}

Image *addImages(const Image *imageA, const Image *imageB) {
    Image *nImage = 0;

    if (imageA && imageB && imageA->getChannel()==imageB->getChannel()) {
        unsigned int width = imageA->getWidth()<imageB->getWidth()?imageA->getWidth():imageB->getWidth();
        unsigned int height = imageA->getHeight()<imageB->getHeight()?imageA->getHeight():imageB->getHeight();
        nImage = new Image(width, height, imageA->getChannel());

        int pixelA, pixelB, nPixel;
        int temp;
        for (unsigned int i = 0; i<height; i++) {
            for (unsigned int j = 0; j<width; j++) {
                pixelA = imageA->getPixel(i,j);
                pixelB = imageB->getPixel(i,j);
                nPixel = 0;

                for (unsigned int k = 1; k<=imageA->getChannel(); k++) {
                    temp = ( ( (pixelA>>(8*(imageA->getChannel()-k)))&0xFF )+( (pixelB>>(8*(imageB->getChannel()-k)))&0xFF ) );
                    if (temp>0xFF) temp = 0xFF;
                    nPixel = nPixel | temp;
                    if (k<imageA->getChannel()) nPixel = nPixel << 8;
                }

                // Uma vez calculado o pixel correspondente para a imagem em escala de cinza, o mesmo é inserido
                // na imagem resultante.
                nImage->setPixel(i,j,nPixel);
            }
        }

    }

    return nImage;
}

/*
   Reduz a amostragem de uma imagem.

Parâmetros:
   image - referência para a imagem que será terá a amostragem reduzida.
   factor - valor inteiro, positivo, que indica fator de redução de amostragem.

Retorno:
     referência da nova imagem, reduzida.
*/
Image *reduce(const Image *image, unsigned int factor) {
    Image *nImage = 0;

    if (image) {

        // Aloca imagem resultante.
        nImage = new Image(image->getWidth()/factor, image->getHeight()/factor, image->getChannel());

        int pixel, nPixel;

        // Para cada bloco da imagem original contendo até (factor * factor) pixels:
        for (unsigned int i = 0; i<image->getHeight(); i+=factor) {
            for (unsigned int j = 0; j<image->getWidth(); j+=factor) {
                nPixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++) {
                    pixel = 0;

                    // São percorridos todos os pixels no bloco corrente, manipulando-se a k-ésima componente
                    // desses pixels.
                    for (unsigned int fi = 0; fi<factor; fi++) {
                        for (unsigned int fj = 0; fj<factor; fj++) {

                            // Caso o pixel corrente do bloco esteja dentro das dimensões da imagem original,
                            // soma-se o valor de sua k-ésima componente à soma acumulativa da k-ésima componente dos pixels
                            // já processados no mesmo bloco.
                            if ((i+fi)<image->getHeight() && (j+fj)<image->getWidth()) {
                                pixel += (image->getPixel(i+fi,j+fj)>>(8*(image->getChannel()-k)))&0xFF;
                            }
                        }
                    }

                    // Uma vez somada a k-ésima componente de cada pixel válido no bloco corrente,
                    // obtém-se a média aritimética que irá representar a k-ésima componente do pixel correspondente
                    // na imagem resultante.
                    pixel = pixel/(factor*factor);
                    nPixel = nPixel | pixel;
                    if (k<image->getChannel())
                        nPixel = nPixel<<8;
                }

                // Uma vez calculadas e posicionadas todas as componentes (canais) do pixel correspondente, o mesmo
                // é atribuído na imagem resultante.
                nImage->setPixel(i/factor,j/factor,nPixel);
            }
        }
    }

    return nImage;
}

/*
   Procedimento responsável por fazer a quantização de uma imagem.

Parâmetros:
   image - referência para a imagem que será feita a quantização.
   factor - valor inteiro, positivo, que indica fator de quantização de cores da imagem.

Retorno:
     referência da nova imagem, com a quantização das cores.
*/
Image *quantisation(const Image *image, unsigned int factor) {
    Image *nImage = 0;
    if (image) {
        nImage = new Image(image->getWidth(), image->getHeight(), image->getChannel());

        int pixel, nPixel;

        //Para cada pixel da imagem:
        for (unsigned int i = 0; i<image->getHeight(); i++) {
            for (unsigned int j = 0; j<image->getWidth(); j++) {
                pixel = 0;
                nPixel = 0;

                //São percorridas todas as componentes (channels) do pixel
                for (unsigned int k = 1; k<=image->getChannel(); k++) {

                    //obtém a componente do pixel
                    pixel = (image->getPixel(i,j)>>(8*(image->getChannel()-k)))&0xFF;

                    //faz a quantização da componente do pixel
                    nPixel = nPixel | (pixel-pixel%factor); //valor inferior do intervalo
                    //nPixel = nPixel | (pixel+(factor-pixel%factor)); //valor superior do intervalo
                    //nPixel = nPixel | ( (pixel-pixel%factor)+(pixel+(factor-pixel%factor)) )/2; //valor médio do intervalo

                    //desloca a componente (channel) do pixel
                    if (k<image->getChannel())
                        nPixel = nPixel<<8;
                }

                //preenche a imagem quantizada.
                nImage->setPixel(i,j,nPixel);
            }
        }
    }

    return nImage;
}

Image *convolution(const Image *image, const Kernel *kernel) {
    double operation;
    Image *img = 0;

    int pixel;
    if (image && kernel) {
        img = new Image(image->getWidth(), image->getHeight(), image->getChannel() );
        for (unsigned int i=0; i<(image->getHeight()-kernel->getHeight()); i++ ) {
            for (unsigned int j=0; j<(image->getWidth()-kernel->getWidth()); j++ ) {
                pixel = 0;
                for (unsigned int k = 1; k<=image->getChannel(); k++) {
                    operation = 0.0;
                    for (unsigned int ki=0; ki<kernel->getHeight(); ki++ ) {
                        for (unsigned int kj=0; kj<kernel->getWidth(); kj++ ) {
                            operation += ( (image->getPixel(i+ki,j+kj)>>(8*(image->getChannel()-k)))&0xFF )*kernel->get(ki, kj);
                        }
                    }
                    if(operation>255.0) operation = 255.0;
                    else if(operation<0.0) operation = 0.0;

                    pixel = pixel | ( ((int)floor(operation))&0xFF );
                    if (k<image->getChannel()) pixel = pixel << 8;
                }

                img->setPixel(i+(int)(kernel->getHeight()/2), j+(int)(kernel->getWidth()/2), pixel);

            }
        }
    }

    return img;
}



Image *histogramEqualization(const Image *image) {

    Image * img = 0;
    unsigned int ** histogram;
    double ** normalizedHistogramSum;
    unsigned int totalPixels;

    if (image) {

        img = new Image(image->getWidth(), image->getHeight(), image->getChannel());
        totalPixels = image->getWidth() * image->getHeight();

        histogram = new unsigned int*[image->getChannel()];
        normalizedHistogramSum = new double*[image->getChannel()];

        for (unsigned int h = 0; h < image->getChannel(); h++) {
            histogram[h] = new unsigned int[256];
            normalizedHistogramSum[h] = new double[256];

            memset(histogram[h], 0x0, 256);
        }

        for (unsigned int i = 0; i < image->getHeight(); i++) {
            for (unsigned int j = 0; j < image->getWidth(); j++) {

                unsigned int pixel = image->getPixel(i, j);

                for (unsigned int k = 1; k <= image->getChannel(); k++) {
                    unsigned int channel = ( (pixel >> (8 * (image->getChannel() - k) ) ) & 0xFF );
                    histogram[k-1][channel]++;
                }
            }
        }

        for (unsigned int k = 0; k < image->getChannel(); k++) {
            normalizedHistogramSum[k][0] = (double)histogram[k][0] / (double)totalPixels;
        }

        for (unsigned int k = 0; k < image->getChannel(); k++) {
            for (unsigned int c = 1; c < 256; c++) {
                normalizedHistogramSum[k][c] = normalizedHistogramSum[k][c-1] +  (double)histogram[k][c] / (double)totalPixels;
            }
        }


        for (unsigned int i = 0; i < image->getHeight(); i++) {
            for (unsigned int j = 0; j < image->getWidth(); j++) {

                unsigned int originalPixel = image->getPixel(i, j);
                unsigned int newPixel = 0;

                for (unsigned int k = 1; k <= image->getChannel(); k++) {

                    unsigned int originalChannel = ( (originalPixel >> (8 * (image->getChannel() - k) ) ) & 0xFF );
                    unsigned int newChannel = (int)(round(normalizedHistogramSum[k-1][originalChannel] * 255.0));

                    newPixel = newPixel | (newChannel << (8 * (image->getChannel() - k) ) );
                }

                img->setPixel(i, j, newPixel);
            }
        }

        for (unsigned int h = 0; h < image->getChannel(); h++) {
            delete [] histogram[h];
            delete [] normalizedHistogramSum[h];
        }


        delete histogram;
        delete normalizedHistogramSum;
    }

    return img;
}

}//end namespace imageOperator
