#ifndef KERNEL_H
#define KERNEL_H

class Kernel {

public:
    Kernel(const unsigned int width=0, const unsigned int height=0);
    Kernel(const Kernel &kernel);
    ~Kernel();

    void createKernel(const unsigned int width, const unsigned int height);
    void destroyKernel();

    void set(const unsigned int row, const unsigned int column, const double value);
    double get(const unsigned int row, const unsigned int column) const;

	 double *at(const unsigned int row, const unsigned int column);

    void setWidth(const unsigned int width);
    unsigned int getWidth() const;

    void setHeight(const unsigned int height);
    unsigned int getHeight() const;

    Kernel &operator=(const Kernel &kernel);

private:

    void kill();
    void create(const unsigned int width, const unsigned int height);

    double *data_;
    unsigned int width_;
    unsigned int height_;
};

#endif
