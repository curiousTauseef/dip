/**
@authors:
	ROCHA, Rodrigo C. O.

UFMG - Universidade Federal de Minas Gerais
PUC Minas - Pontificia Universidade Catolica de Minas Gerais
Computer Science
*/
#include "Image.h"

/*
  Construtor - cria uma nova imagem com dimensões e número de canais especificados.

Parameters:
   width - The width of the image being created.
   height - The height of the image being created.
   channel - The number of channels of the image. A coloured image with RGB pixel has 3 channels. A grey scale image has just 1 channel.
*/
Image::Image(const unsigned int width, const unsigned int height, const unsigned int channel)
    : data_(0)
{
    create(width, height);
    setChannel(channel);
}

/*
  Construtor - cria uma cópia de uma imagem.

Parameters:
   img - referência para  a imagem a ser copiada.
*/
Image::Image(const Image &img)
    : data_(0)
{
    create(img.getWidth(), img.getHeight());
    setChannel(img.getChannel());

    for(unsigned int i = 0; i<img.getWidth(); i++)
        for(unsigned int j = 0; j<img.getHeight(); j++)
            setPixel(i,j, img.getPixel(i,j));
}
/*
  Destructor - desaloca área alocada para a imagem.
*/
Image::~Image()
{
    kill();
}

/*
  Sobrecarga do operator de atribuição.
  Copia os atributos e dados de uma determinada imagem e os associa a este objeto.

 Parameters:
    img - referência para a imagem cujos atributos e dados serão copiados.
*/
Image &Image::operator=(const Image &img)
{
    if( getWidth()!=img.getWidth() || getHeight()!=img.getHeight() )
        createImage( img.getWidth(), img.getHeight() );
    setChannel(img.getChannel());
    for(unsigned int i = 0; i<img.getWidth(); i++)
        for(unsigned int j = 0; j<img.getHeight(); j++)
            setPixel(i,j, img.getPixel(i,j));

    return (*this);
}

/*
  Cria uma nova imagem com dimensões e número de canais especificados.

Parameters:
   width - largura da imagem a ser criada.
   height - altura da imagem a ser criada.
   channel - número de canais da imagem a ser criada.
*/
void Image::createImage(const unsigned int width, const unsigned int height, const unsigned int channel)
{
    kill(); // Desaloca área de imagem alocada previamente, se necessário.

    create(width, height);
    setChannel(channel);
}

void Image::destroyImage()
{
    kill();
}

/*
  Atribui um valor para um determinado pixel da imagem.

Parameters:
   row - linha em que o pixel se encontra na imagem.
   col - coluna em que o pixel se encontra na imagem.
*/
void Image::setPixel(const unsigned int row, const int unsigned column, const int pixel)
{
    *(data_+row*width_+column) = pixel;
}

/*
  Retorna o valor de um determinado pixel da imagem.

Parameters:
   row - linha em que o pixel se encontra na imagem.
   col - coluna em que o pixel se encontra na imagem.

Return:
   valor do pixel situação na posição (row, col) da imagem.
*/
int Image::getPixel(const unsigned int row, const int unsigned column) const
{
    return *(data_+row*width_+column);
}

/*
  Atribui a quantidade de canais da imagem.

Parameters:
   channel - inteiro que indica quantidade de canais da imagem.
*/
void Image::setChannel(const unsigned int channel)
{
    this->channel_ = channel;
}

/*
  Retorna a quantidade de canais da imagem.

Return:
   inteiro que indica a quantidade de canais da imagem.
*/
unsigned int Image::getChannel() const
{
    return this->channel_;
}

/*
  Atribui a largura da imagem.

Parameters:
   width - inteiro que indica largura da imagem.
*/
void Image::setWidth(const unsigned int width)
{
    this->width_ = width;
}

/*
  Retorna a largura da imagem.

Return:
   inteiro que indica largura da imagem.
*/
unsigned int Image::getWidth() const
{
    return this->width_;
}

/*
  Atribui a altura da imagem.

Parameters:
   height - inteiro que indica altura da imagem.
*/
void Image::setHeight(const unsigned int height)
{
    this->height_ = height;
}

/*
  Retorna a altura da imagem.

 Return:
   inteiro que indica altura da imagem.
*/
unsigned int Image::getHeight() const
{
    return this->height_;
}

/*
  Desaloca a área de dados reservada para representar uma imagem, caso a mesma tenha sido alocada.
*/
void Image::kill()
{
    if(data_) delete data_, data_ = 0, width_ = height_ = 0;
}

/*
  Cria uma nova imagem com dimensões específicas.
  O número de canais da imagem permanece inalterado.

Parameters:
   width - largura da imagem a ser criada.
   height - altura da imagem a ser criada.
*/
void Image::create(const unsigned int width, const unsigned int height)
{
    // Caso este objeto de imagem não tenha sido utilizado para alocar os dados de uma imagem previamente,
    // aloca-se uma região em memória para armazenar estes dados, bem como atualizam-se os atributos da imagem.
    if(!data_ && width && height) data_ = new int[width*height], width_ = width, height_ = height;
}

