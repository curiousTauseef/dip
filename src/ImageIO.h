#ifndef IMAGE_IO_H
#define IMAGE_IO_H
/**
developers:
    Rodrigo Caetano de Oliveira Rocha

PUC Minas - Pontifícia Universidade Católica de Minas Gerais
Ciência da Computação
*/
/*
    Funções de I/O de imagens.
*/

#include <stdio.h>

#include "Image.h"
#include "Kernel.h"


namespace imageOperator
{
/*
    Função responsável por ler uma imagem de um arquivo do formato PNM(Portable Any-Map,
    como PPM, PGM).
    Formatos P2 e P3.

Parâmetros:
    fileName - arquivo PNM de entrada da imagem,
        tanto arquivos PPM (RGB Images) quanto PGM (Grey Scale Images)

Retorno:
     Instância da classe Image com a imagem lida do arquivo de entrada.
     Nulo se arquivo inválido.
*/
Image *loadPNMImage(const char *fileName);

/*
    Procedimento responsável por gravar uma imagem em um arquivo do formato PNM(Portable Any-Map,
    como PPM, PGM).
    Formatos P2 e P3.

Parâmetros:
    image - instância da classe image. imagem a ser armazenada em um arquivo PNM.
    fileName - arquivo PNM de saída da imagem,
        tanto arquivos PPM (RGB Images) quanto PGM (Grey Scale Images)

Retorno:
     ---
*/
void storePNMImage(Image *image, const char *fileName);
void filePNMPrint(FILE *out, Image *image);
void storeKernel(Kernel *ker, const char *fileName);
}
#endif
