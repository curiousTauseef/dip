#ifndef IMAGE_H
#define IMAGE_H
/**
@authors:
	ROCHA, Rodrigo C. O.

UFMG - Universidade Federal de Minas Gerais
PUC Minas - Pontificia Universidade Catolica de Minas Gerais
Computer Science
*/

/*
    Classe que implementa uma imagem.
    Trata imagens como uma matriz de inteiros representando os pixels, onde considera-se
        que cada byte do pixel e' o valor de um canal (channel).
    Imagens RGB's são representadas por imagens com o channel RGB_IMAGE = 3.
    Imagens em escala de cinza são representadas por imagens com o channel GREY_SCALE_IMAGE = 1.

 */
class Image {
public:
    static const int unsigned GREY_SCALE_IMAGE = 1;
    static const int unsigned RGB_IMAGE = 3;

    Image(const unsigned int width=0, const unsigned int height=0, const unsigned int channel=GREY_SCALE_IMAGE);
    Image(const Image &img);
    ~Image();

    void createImage(const unsigned int width, const unsigned int height, const unsigned int channel=GREY_SCALE_IMAGE);
    void destroyImage();

    void setPixel(const unsigned int row, const int unsigned column, const int pixel);
    int getPixel(const unsigned int row, const int unsigned column) const;

    void setChannel(const unsigned int channel);
    unsigned int getChannel() const;

    void setWidth(const unsigned int width);
    unsigned int getWidth() const;

    void setHeight(const unsigned int height);
    unsigned int getHeight() const;

    Image &operator=(const Image &img);

private:

    void kill();
    void create(const unsigned int width, const unsigned int height);

    int *data_;
    unsigned int channel_;
    unsigned int width_;
    unsigned int height_;
};

#endif
