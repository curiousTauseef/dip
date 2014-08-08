#ifndef RGB_H
#define RGB_H
/**
developers:
    Rodrigo Caetano de Oliveira Rocha

PUC Minas - Pontifícia Universidade Católica de Minas Gerais
Ciência da Computação
*/


#include <iostream>
using std::ostream;

/*
    Classe que implementa um pixel em RGB (Red, Green e Blue).
 */
class RGB {
public:
    RGB(const int rgb_value);
    RGB(const unsigned char red=0, const unsigned char green=0, const unsigned char blue=0);
    RGB(const RGB &rgb);

    void setRGB(const int rgb_value);
    void setRGB(const unsigned char red, const unsigned char green, const unsigned char blue);
    int getRGB() const;

    void setRed(const unsigned char red);
    unsigned char getRed() const;

    void setGreen(const unsigned char green);
    unsigned char getGreen() const;

    void setBlue(const unsigned char blue);
    unsigned char getBlue() const;

    double intensity();

    void copy(const RGB &rgb);


    RGB &operator=(const RGB &rgb);
    friend ostream &operator<<(ostream &out, const RGB &rgb);
private:
    unsigned char red_;
    unsigned char green_;
    unsigned char blue_;
};

#endif
