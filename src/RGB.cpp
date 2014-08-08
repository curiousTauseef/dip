/**
developers:
    Rodrigo Caetano de Oliveira Rocha

PUC Minas - Pontifícia Universidade Católica de Minas Gerais
Ciência da Computação
*/

#include "RGB.h"

/*
  Construtor - cria um pixel RGB, a partir de um valor inteiro do pixel.

Parâmetros:
   rgb_value - inteiro que representa o valor do pixel em RGB.
*/
RGB::RGB(const int rgb_value)
{
    setRGB(rgb_value);
}

/*
  Construtor - cria um pixel RGB, a partir dos valores RGB.

Parâmetros:
   red - caractere(byte) que indica o valor vermelho.
   green - caractere(byte) que indica o valor verde.
   blue - caractere(byte) que indica o valor azul.
*/
RGB::RGB(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

/*
  Construtor - cria uma cópia do pixel RGB.

Parâmetros:
   rgb - referência para o RGB a ser copiado.
*/
RGB::RGB(const RGB &rgb)
{
    copy(rgb);
}

/*
  Atribui o valor do RGB.

Parâmetros:
   rgb_value - inteiro que representa o valor do pixel em RGB.
*/
void RGB::setRGB(const int rgb_value)
{
    setRed( (rgb_value>>16)&0xFF );
    setGreen( (rgb_value>>8)&0xFF );
    setBlue( (rgb_value)&0xFF );
}

/*
  Atribui o valor do RGB.

Parâmetros:
   red - caractere(byte) que indica o valor vermelho.
   green - caractere(byte) que indica o valor verde.
   blue - caractere(byte) que indica o valor azul.
*/
void RGB::setRGB(const unsigned char red, const unsigned char green, const unsigned char blue)
{
    setRed(red);
    setGreen(green);
    setBlue(blue);
}

/*
  Retorna o pixel em RGB.

Retorno:
   inteiro que representa o valor pixel em RGB.
*/
int RGB::getRGB() const
{
    return ( this->red_<<16 | this->green_<<8 | this->blue_ );
}

/*
  Atribui o valor vermelho do RGB.

Parâmetros:
   red - caractere(byte) que indica o valor vermelho.
*/
void RGB::setRed(const unsigned char red)
{
    this->red_ = red;
}

/*
  Retorna o valor vermelho do RGB.

Retorno:
   caractere(byte) que indica o valor vermelho.
*/
unsigned char RGB::getRed() const
{
    return this->red_;
}

/*
  Atribui o valor verde do RGB.

Parâmetros:
   green - caractere(byte) que indica o valor verde.
*/
void RGB::setGreen(const unsigned char green)
{
    this->green_ = green;
}

/*
  Retorna o valor verde do RGB.

Retorno:
   caractere(byte) que indica o valor verde.
*/
unsigned char RGB::getGreen() const
{
    return this->green_;
}

/*
  Atribui o valor azul do RGB.

Parâmetros:
   blue - caractere(byte) que indica o valor azul.
*/
void RGB::setBlue(const unsigned char blue)
{
    this->blue_ = blue;
}

/*
  Retorna o valor azul do RGB.

Retorno:
   caractere(byte) que indica o valor azul.
*/
unsigned char RGB::getBlue() const
{
    return this->blue_;
}


double RGB::intensity()
{
	return(0.30*double(this->red_)+0.59*double(this->green_)+0.11*double(this->blue_));
}

void RGB::copy(const RGB &rgb)
{
    setRed(rgb.getRed());
    setGreen(rgb.getGreen());
    setBlue(rgb.getBlue());
}



RGB &RGB::operator=(const RGB &rgb)
{
    copy(rgb);
    return (*this);
}

ostream &operator<<(ostream &out, const RGB &rgb)
{
    out << '(' << (int)rgb.red_ << ", " << (int)rgb.green_ << ", " << (int)rgb.blue_ << ')';
    return out;
}

