/**
developers:
    Rodrigo Caetano de Oliveira Rocha

PUC Minas - Pontifícia Universidade Católica de Minas Gerais
Ciência da Computação
*/
#include "ImageIO.h"
#include "ImageHandler.h"

#include <cstdlib>

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;

namespace imageOperator
{
/*
    Função que lê o próximo caractere (char) do arquivo de entrada,
    ignorando espaço em branco e comentários de uma linha, #.

Parâmetros:
    in - arquivo de entrada, instância da classe ifstream.

Retorno:
     caractere alfanumérico lido do arquivo de entrada.
*/
char nextChar(ifstream &in)
{
    char ch;
    if(in){
        ch = in.get();

        do {
            //white space
            //ignora espaço em branco
            while( in && (ch==' ' || ch=='\n' || ch=='\t')  ) { ch = in.get(); }

            //comment
            //ignora comentários de uma linha, #
            if(ch=='#'){
                while(in && in.get()!='\n'){}
                ch = in.get();
            }//end if

        } while(in && !isalnum(ch));
    }
    return ch;
}

/*
    Função que lê o próximo inteiro(int) do arquivo ascii de entrada,
    ignorando espaço em branco e comentários de uma linha, #.

Parâmetros:
    in - arquivo de entrada no formato ascii, instância da classe ifstream.

Retorno:
     inteiro lido do arquivo ascii de entrada.
*/
int nextInt(ifstream &in)
{
    int val = 0;

    if(in){
        char temp[32];
        int i = 0;
        char ch;

        //ignora o caractere lido enquanto não for um digito
        while( in && !isdigit(ch=nextChar(in)) ){}

        //enquanto o caractere lido for um digito,
        //concatena-o ao buffer de caracteres
        while(in && isdigit(ch)){
            temp[i++] = ch;
            ch = in.get();
        }
        temp[i] = 0;

        //converte os caracteres de digitos lidos para um inteiro
        val = atoi(temp);
    }//end if

    //retorna o inteiro lido
    return val;
}


/*
    Formatos PPM, PGM.
    P2, P3
*/
Image *loadPNMImage(const char *fileName)
{
    Image *image = 0;

    ifstream inFile(fileName);
    unsigned int width, height;
    unsigned int max_value;
    unsigned int channel;
    char ch;

    if(inFile){

        //lê o cabeçalho do arquivo
        ch=nextChar(inFile);
        if(ch=='P'){
            ch=nextChar(inFile);
            if( ch=='3') {
                channel = Image::RGB_IMAGE;
            }else if( ch=='2') {
                channel = Image::GREY_SCALE_IMAGE;
            }

            width = nextInt(inFile);
            height = nextInt(inFile);
            max_value = nextInt(inFile);
            if(!inFile) return 0;

            /*
             após ler o cabeçalho do arquivo,
             cria-se uma imagem equivalente 'a
             imagem descrita pelo arquivo de entrada.
            */
            image = new Image(width, height, channel);

            int pixel;
            unsigned int i;
            unsigned int j;

            //lê os pixels da imagem
            for(i = 0; i<height && inFile; i++){
                for(j = 0; j<width && inFile; j++){
                    pixel = 0;
                    for(unsigned int k = 1; k<=channel && inFile; k++){
                        pixel = pixel | nextInt(inFile);
                        if( k<channel ) pixel = pixel<<8;
                    }
                    image->setPixel(i,j,pixel);
                }
            }

            //confere a validade do arquivo de entrada
            if(i<height || j<width){
                delete image, image = 0;
            }

        }
    }


    //retorna a imagem lida
    //nulo se arquivo invalido
    return image;
}

/*
    Formatos PPM, PGM.
    P2, P3
*/
void storePNMImage(Image *image, const char *fileName)
{
    ofstream outFile(fileName);

    if(outFile){

        char temp[25];
        char channelCode;
        int pixel;
        if(image->getChannel()==Image::RGB_IMAGE) channelCode = '3';
        else if(image->getChannel()==Image::GREY_SCALE_IMAGE) channelCode = '2';

        //escreve o cabeçalho do arquivo
        outFile << 'P' << channelCode << endl;
        outFile << image->getWidth() << ' ' << image->getHeight() << endl;
        outFile << "255" << endl;

        //grava os pixels da imagem no arquivo de saída.
        for(unsigned int i = 0; i<image->getHeight(); i++){
            for(unsigned int j = 0; j<image->getWidth(); j++){
                pixel = image->getPixel(i,j);
                for(unsigned int k = 1; k<=image->getChannel(); k++){

                    unsigned char ch = (pixel>>(8*(image->getChannel()-k)))&0xFF;

                    //itoa((int)ch, temp, 10);
                    sprintf(temp, "%d", int(ch));
                    outFile << temp << endl;
                }
            }
        }
        outFile.close();
    }
}

void filePNMPrint(FILE *out, Image *image)
{
	if(out && image){
		char temp[25];
		char channelCode;
		int pixel;
		if(image->getChannel()==Image::RGB_IMAGE) channelCode = '3';
		else if(image->getChannel()==Image::GREY_SCALE_IMAGE) channelCode = '2';

		//escreve o cabeçalho do arquivo
		fprintf(out, "P%d\n", channelCode);
		fprintf(out, "%d %d\n", image->getWidth(), image->getHeight());
		fprintf(out, "255\n");

		//grava os pixels da imagem no arquivo de saída.
		for(unsigned int i = 0; i<image->getHeight(); i++){
			for(unsigned int j = 0; j<image->getWidth(); j++){
				pixel = image->getPixel(i,j);
				for(unsigned int k = 1; k<=image->getChannel(); k++){
					unsigned char ch = (pixel>>(8*(image->getChannel()-k)))&0xFF;
						//itoa((int)ch, temp, 10);
						//sprintf(temp, "%d", int(ch));
						//outFile << temp << endl;
						fprintf(out, "%d\n", int(ch));
				}
			}
		}
	}
}

void storeKernel(Kernel *ker, const char *fileName)
{
    Image *kerImg = kernelToGreyScale(ker);
    if(kerImg) storePNMImage(kerImg, fileName);
    delete kerImg;
}

}//end namespace imageOperator
