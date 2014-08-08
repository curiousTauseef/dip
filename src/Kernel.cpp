#include "Kernel.h"

Kernel::Kernel(const unsigned int width, const unsigned int height)
    : data_(0)
{
    create(width, height);
}

Kernel::Kernel(const Kernel &kernel)
    : data_(0)
{
    create(kernel.getWidth(), kernel.getHeight());

    for(unsigned int i = 0; i<kernel.getWidth(); i++)
        for(unsigned int j = 0; j<kernel.getHeight(); j++)
            set(i,j, kernel.get(i,j));
}

Kernel::~Kernel()
{
    kill();
}

void Kernel::createKernel(const unsigned int width, const unsigned int height)
{
    kill(); // Desaloca área de imagem alocada previamente, se necessário.
    create(width, height);
}

void Kernel::destroyKernel()
{
    kill();
}

void Kernel::set(const unsigned int row, const unsigned int column, const double value)
{
    *(data_+row*width_+column) = value;
}

double Kernel::get(const unsigned int row, const unsigned int column) const
{
    return *(data_+row*width_+column);
}

double *Kernel::at(const unsigned int row, const unsigned int column)
{
    return (data_+row*width_+column);
}

void Kernel::setWidth(const unsigned int width)
{
    this->width_ = width;
}

unsigned int Kernel::getWidth() const
{
    return this->width_;
}

void Kernel::setHeight(const unsigned int height)
{
    this->height_ = height;
}

unsigned int Kernel::getHeight() const
{
    return this->height_;
}

Kernel &Kernel::operator=(const Kernel &kernel)
{
    if( getWidth()!=kernel.getWidth() || getHeight()!=kernel.getHeight() )
        createKernel( kernel.getWidth(), kernel.getHeight() );

    for(unsigned int i = 0; i<kernel.getWidth(); i++)
        for(unsigned int j = 0; j<kernel.getHeight(); j++)
            set(i,j, kernel.get(i,j));

    return (*this);
}

void Kernel::kill()
{
    if(data_) delete data_, data_ = 0, width_ = height_ = 0;
}

void Kernel::create(const unsigned int width, const unsigned int height)
{
    // Caso este objeto de imagem não tenha sido utilizado para alocar os dados de uma imagem previamente,
    // aloca-se uma região em memória para armazenar estes dados, bem como atualizam-se os atributos da imagem.
    if(!data_ && width && height) data_ = new double[width*height], width_ = width, height_ = height;
}
