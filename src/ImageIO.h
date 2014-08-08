#ifndef IMAGE_IO_H
#define IMAGE_IO_H
/**
developers:
    Rodrigo Caetano de Oliveira Rocha

PUC Minas - Pontif�cia Universidade Cat�lica de Minas Gerais
Ci�ncia da Computa��o
*/
/*
    Fun��es de I/O de imagens.
*/

#include <stdio.h>

#include "Image.h"
#include "Kernel.h"


namespace imageOperator
{
/*
    Fun��o respons�vel por ler uma imagem de um arquivo do formato PNM(Portable Any-Map,
    como PPM, PGM).
    Formatos P2 e P3.

Par�metros:
    fileName - arquivo PNM de entrada da imagem,
        tanto arquivos PPM (RGB Images) quanto PGM (Grey Scale Images)

Retorno:
     Inst�ncia da classe Image com a imagem lida do arquivo de entrada.
     Nulo se arquivo inv�lido.
*/
Image *loadPNMImage(const char *fileName);

/*
    Procedimento respons�vel por gravar uma imagem em um arquivo do formato PNM(Portable Any-Map,
    como PPM, PGM).
    Formatos P2 e P3.

Par�metros:
    image - inst�ncia da classe image. imagem a ser armazenada em um arquivo PNM.
    fileName - arquivo PNM de sa�da da imagem,
        tanto arquivos PPM (RGB Images) quanto PGM (Grey Scale Images)

Retorno:
     ---
*/
void storePNMImage(Image *image, const char *fileName);
void filePNMPrint(FILE *out, Image *image);
void storeKernel(Kernel *ker, const char *fileName);
}
#endif
