#ifndef IMAGE_HANDLER_H
#define IMAGE_HANDLER_H
/**
developers:
    Rodrigo Caetano de Oliveira Rocha

PUC Minas - Pontifícia Universidade Católica de Minas Gerais
Ciência da Computação
*/

/*
    Funções de manipulação de imagens.
*/

#include <cmath>
#include <cstring>

#include "Image.h"
#include "Kernel.h"

namespace imageOperator
{
/*
    Função que converte uma imagem colorida (RGB) para a escala de cinza.

Parâmetros:
    image - referência para a imagem colorida a ser convertida para escala de cinza.

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
    Função que reduz uma imagem (RGB ou GreyScale) por um dado fator.

Parâmetros:
    image - referência para a imagem colorida a ser reduzida.
    factor - fator, inteiro positivo, de redução

Retorno:
     nova imagem reduzida pelo fator.
*/
Image *reduce(const Image *image, unsigned int factor);

/*
    Função que faz a quantização de cores de uma dada imagem (RGB ou GreyScale).

Parâmetros:
    image - referência para a imagem a ser quantizada.
    factor - fator, inteiro positivo, de quantização.

Retorno:
     nova imagem quantizada.
*/
Image *quantisation(const Image *image, unsigned int factor);

Image *convolution(const Image *image, const Kernel *kernel);

Image *histogramEqualization(const Image *image);

}

#endif

