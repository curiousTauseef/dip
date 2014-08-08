#ifndef IMAGE_HANDLER_H
#define IMAGE_HANDLER_H
/**
developers:
    Rodrigo Caetano de Oliveira Rocha

PUC Minas - Pontif�cia Universidade Cat�lica de Minas Gerais
Ci�ncia da Computa��o
*/

/*
    Fun��es de manipula��o de imagens.
*/

#include <cmath>
#include <cstring>

#include "Image.h"
#include "Kernel.h"

namespace imageOperator
{
/*
    Fun��o que converte uma imagem colorida (RGB) para a escala de cinza.

Par�metros:
    image - refer�ncia para a imagem colorida a ser convertida para escala de cinza.

Retorno:
     nova imagem em escala de cinza, gerada a partir da imagem colorida.
*/
Image *convertToGreyScale(const Image *image);

Image *kernelToGreyScale(const Kernel *ker);

Image *invertColour(const Image *image);
Image *transpose(const Image *image);

Image *addImages(const Image *imageA, const Image *imageB);

//scale(resize an image)
//scale for reducing an image is called downsampling.
/*
    Fun��o que reduz uma imagem (RGB ou GreyScale) por um dado fator.

Par�metros:
    image - refer�ncia para a imagem colorida a ser reduzida.
    factor - fator, inteiro positivo, de redu��o

Retorno:
     nova imagem reduzida pelo fator.
*/
Image *reduce(const Image *image, unsigned int factor);

/*
    Fun��o que faz a quantiza��o de cores de uma dada imagem (RGB ou GreyScale).

Par�metros:
    image - refer�ncia para a imagem a ser quantizada.
    factor - fator, inteiro positivo, de quantiza��o.

Retorno:
     nova imagem quantizada.
*/
Image *quantisation(const Image *image, unsigned int factor);

Image *convolution(const Image *image, const Kernel *kernel);

Image *histogramEqualization(const Image *image);

}

#endif

