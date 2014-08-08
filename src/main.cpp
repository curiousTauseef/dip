
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <fstream>
using namespace std;

//#include "hr_time.h"
#include "arg.h"

#include "SeamCarving.h"
#include "Kernel.h"
#include "Image.h"
#include "ImageIO.h"
#include "ImageHandler.h"
#include "EdgeDetection.h"
#include "Morphology.h" //Mathematical Morphology
#include "Smooth.h"
#include "Sharpen.h"

using namespace imageOperator;

void seamColumnReduction(const char *fileName, const char *output, int cols, Kernel *kerA, Kernel *kerB, bool dijkstra);
void seamRowReduction(const char *fileName, const char *output, int rows, Kernel *kerA, Kernel *kerB, bool dijkstra);
void seamReduction(const char *fileName, const char *output, int rows, int cols, Kernel *kerA, Kernel *kerB, bool dijkstra);

void paint(const char *fileName, const char *paint, const char *sketch, int factor, int threshold);

Kernel *loadKernel(ifstream &in);

Image *sketch(Image *img, unsigned int threshold);

int main(int argc, char **argv)
{
	//paint("input/test.ppm","painting.ppm","output/sketch.pgm", 30, 15);
	//paint("herp.ppm","painting.ppm","sketch.pgm", 30, 6);
	//paint("Dijkstra.ppm","painting.ppm","sketch.pgm", 30, 10);
	//paint("anders.ppm","painting.ppm","sketch.pgm", 30, 4);
	//paint("beachwalk.ppm","painting.ppm","sketch.pgm", 30, 10);
	//paint("reach1.ppm","painting.ppm","sketch.pgm", 30, 5);
	paint("bedroom.ppm","output.ppm","bedroom.pgm", 30, 3);
	return 0;

	char *arg;
	int h = 0, w = 0;
	char *matrixFile = 0;
	char *fileName = 0;
	char *outFileName = 0;

	Kernel *kerA = 0;
	Kernel *kerB = 0;

	if(argc>1)
		fileName = argv[1];
	else return 0;

	if( (arg=ArgGetValue(argc, argv, "-o")) ){
		outFileName = arg;
	}

	if( (arg=ArgGetValue(argc, argv, "-h")) ){
		h = atoi(arg);
	}

	if( (arg=ArgGetValue(argc, argv, "-w")) ){
		w = atoi(arg);
	}

	if( (arg=ArgGetValue(argc, argv, "-m")) ){
		matrixFile = arg;
		ifstream in(matrixFile);
		kerA = loadKernel(in);
		kerB = loadKernel(in);
	}

	bool dijkstra = false;
	if(ArgExists(argc, argv, "-g"))
		dijkstra = true;

   if(w==0 && h!=0){
		seamRowReduction(fileName, outFileName, h, kerA, kerB, dijkstra);
   }else if(w!=0 && h==0){
		seamColumnReduction(fileName, outFileName, w, kerA, kerB, dijkstra);
   }else if(w!=0 && h!=0){
		seamReduction(fileName, outFileName, h, w, kerA, kerB, dijkstra);
	}
	return 0;
}

void seamColumnReduction(const char *fileName, const char *output, int cols, Kernel *kerA, Kernel *kerB, bool dijkstra)
{
	Image *img;
	Image *rImg;
	//hr_timer_t timer; //DEBUG

	img = loadPNMImage(fileName);
    if(cols<0){
        cols = (img->getWidth()/2);
    }

	//hrt_start(&timer); //DEBUG
	if(dijkstra){
		rImg = seamCarvingRemoveColumnDijkstra(img, cols, kerA, kerB);
	}else {
		rImg = seamCarvingRemoveColumn(img, cols, kerA, kerB);
	}
	//hrt_stop(&timer); //DEBUG

	if (rImg) {

		if(output){
			storePNMImage(rImg, output);
		}else{
			filePNMPrint(stdout, rImg);
		}
		delete rImg;
	}

	//cout  << "reduzido: " << cols << " -- " << hrt_elapsed_time(&timer) << "s" << endl; //DEBUG
	delete img;
}

void seamRowReduction(const char *fileName, const char *output, int rows, Kernel *kerA, Kernel *kerB, bool dijkstra)
{
    Image *img;
	Image *rImg;
	//hr_timer_t timer; //DEBUG

	img = loadPNMImage(fileName);

    if(rows<0){
        rows = (img->getHeight()/2);
    }

	Image *tImg = transpose(img);
	//hrt_start(&timer); //DEBUG
	//rImg = seamCarvingRemoveColumn(tImg, rows, kerA, kerB);
	if(dijkstra){
		rImg = seamCarvingRemoveColumnDijkstra(tImg, rows, kerA, kerB);
	}else {
		rImg = seamCarvingRemoveColumn(tImg, rows, kerA, kerB);
	}
	//hrt_stop(&timer); //DEBUG
	delete tImg;
	tImg = transpose(rImg);
	delete rImg;
	rImg = tImg;

	if (rImg) {

		//cout << "gravando imagem seam carving..." << endl;
		if(output){
			storePNMImage(rImg, output);
		}else{
			filePNMPrint(stdout, rImg);
		}
		delete rImg;
	}

	//cout  << "reduzido: " << rows << " -- " << hrt_elapsed_time(&timer) << "s" << endl; //DEBUG

	delete img;
}

void seamReduction(const char *fileName, const char *output, int rows, int cols, Kernel *kerA, Kernel *kerB, bool dijkstra)
{
   Image *img;
	Image *rImg;
	//hr_timer_t timer; //DEBUG

	img = loadPNMImage(fileName);

	if(cols<0){
		cols = (img->getWidth()/2);
	}

	if(rows<0){
		rows = (img->getHeight()/2);
	}

	//hrt_start(&timer); //DEBUG
	//rImg = seamCarvingRemoveColumn(img, (img->getWidth()/2), kerA, kerB);
	if(dijkstra){
		rImg = seamCarvingRemoveColumnDijkstra(img, cols, kerA, kerB);
	}else {
		rImg = seamCarvingRemoveColumn(img, cols, kerA, kerB);
	}
	//hrt_stop(&timer); //DEBUG

	Image *tImg = transpose(rImg);
	delete rImg;
	//hrt_start(&timer); //DEBUG
	//rImg = seamCarvingRemoveColumn(tImg, (tImg->getWidth()/2), kerA, kerB);
	if(dijkstra){
		rImg = seamCarvingRemoveColumnDijkstra(tImg, rows, kerA, kerB);
	}else {
		rImg = seamCarvingRemoveColumn(tImg, rows, kerA, kerB);
	}
	//hrt_stop(&timer); //DEBUG
    delete tImg;
    tImg = transpose(rImg);
    delete rImg;
    rImg = tImg;

	if (rImg) {

		//cout << "gravando imagem seam carving..." << endl;
		if(output){
			storePNMImage(rImg, output);
		}else{
			filePNMPrint(stdout, rImg);
		}
		delete rImg;
	}

	//cout  << "reduzido: " << cols << ", " << rows << " -- " << hrt_elapsed_time(&timer) << "s" << endl; //DEBUG
	delete img;
}

Kernel *loadKernel(ifstream &in)
{
    int width, height;
    double val;
    in >> width;
    in >> height;
    cout << width << ", " << height << endl;

    Kernel *ker = new Kernel(width, height);
    for(int i = 0; i<height; i++){
        for(int j = 0; j<width; j++){
            in >> val;
            ker->set(i, j, val);
            cout << val << " ";
        }
        cout << endl;
    }

    return ker;
}

void paint(const char *fileName, const char *paint, const char *sketchFile, int factor, int threshold)
{
	Image *img = loadPNMImage(fileName);
	Image *kImg = sketch(img, threshold);
	storePNMImage(kImg, sketchFile);
	delete kImg;
}

Image *sketch(Image *img, unsigned int threshold)
{
    Image *nImg;
    Image *pntImg;// = lowPassOperator(img);//20
    Image *paintImg;// = quantisation(pntImg, factor);//20
    //delete pntImg;
    Image *kImg;
    Kernel *k;

    Image *grey = convertToGreyScale(img);

    //pntImg = lowPassOperator(grey);
    pntImg = gaussian(grey, GAUSSIAN_KERNEL_TYPE_5X5);
    delete grey;

    storePNMImage(pntImg, "img1.pgm");

    nImg = laplacian(pntImg, LAPLACIAN_KERNEL_TYPE_SHARPER);
    storePNMImage(nImg, "img2.pgm");
    delete pntImg;
    pntImg = nImg;
    nImg = 0;

    //nImg = lowPassOperator(pntImg);
    nImg = gaussian(pntImg, GAUSSIAN_KERNEL_TYPE_5X5);
    storePNMImage(nImg, "img3.pgm");
    delete pntImg;
    pntImg = nImg;
    nImg = 0;
    /*
    k = sobelEnergyKernel(pntImg);
    kImg = kernelToGreyScale(k);
    delete k;
    //delete pntImg;
    storePNMImage(kImg, "energy.pgm");

    //pntImg = lowPassOperator(paintImg);
    //delete paintImg;

    nImg = gaussian(kImg);
    delete kImg;
    kImg = nImg;
    */
    kImg = pntImg;
    /*
    nImg = new Image(kImg->getWidth(), kImg->getHeight(), Image::GREY_SCALE_IMAGE);
    for(int i = 0; i<kImg->getHeight(); i++){
        for(int j = 0; j<kImg->getWidth(); j++){
            //if(kImg->getPixel(i,j)){//20
                int pixel = 0;
                int n = 0;
                for(int ki = i-1; ki<=(i+1); ki++){
                    for(int kj = j-1; kj<=(j+1); kj++){
                        if(ki>=0 && ki<kImg->getHeight() && kj>=0 && kj<kImg->getWidth()){
                            pixel += kImg->getPixel(ki,kj);
                            n++;
                        }
                    }
                }
                nImg ->setPixel(i,j, int(pixel/n));
            //}
        }
    }
    delete kImg;
    kImg = nImg;
    */
    //nImg = lowPassOperator(kImg);
    //delete kImg;
    //kImg = nImg;

    //delete pntImg;
    //pntImg = paintImg;

    //storePNMImage(pntImg, "quantization.ppm");
    storePNMImage(kImg, "edges.pgm");

    //nImg = highPassOperator(kImg);
    //delete kImg;
    //kImg = nImg;
    //storePNMImage(kImg, "edges2.pgm");

    //k = sobelEnergyKernel(kImg);
    //delete kImg;
    //kImg = kernelToGreyScale(k);

    //storePNMImage(kImg, "energy2.pgm");

    for(int i = 0; i<kImg->getHeight(); i++){
        for(int j = 0; j<kImg->getWidth(); j++){
            int px = kImg->getPixel(i,j);
            if(px>threshold){//20
                kImg->setPixel(i,j,0);
                //pntImg->setPixel(i,j,0);
            }else {
                kImg->setPixel(i,j,0xFF);
            }
        }
    }
    /*
    nImg = new Image(kImg->getWidth(), kImg->getHeight(), Image::GREY_SCALE_IMAGE);
    for(int i = 0; i<kImg->getHeight(); i++){
        for(int j = 0; j<kImg->getWidth(); j++){
            nImg ->setPixel(i,j, 0xFF);
            if(kImg->getPixel(i,j)==0){//20
                int pixel = 0;
                int n = 0;
                for(int ki = i-1; ki<=(i+1); ki++){
                    for(int kj = j-1; kj<=(j+1); kj++){
                        if(ki>=0 && ki<kImg->getHeight() && kj>=0 && kj<kImg->getWidth()){
                            pixel += kImg->getPixel(ki,kj);
                            n++;
                        }
                    }
                }
                nImg ->setPixel(i,j, int(pixel/n));
            }
        }
    }
    delete kImg;
    kImg = nImg;
    nImg = 0;

    for(int i = 0; i<pntImg->getHeight(); i++){
        for(int j = 0; j<pntImg->getWidth(); j++){
            int px = kImg->getPixel(i,j);
            if(px<(200)){//20
                pntImg->setPixel(i,j,0);
                kImg->setPixel(i,j,0);
            }else {
                kImg->setPixel(i,j,0xFF);
            }
        }
    }
    */
    //storePNMImage(pntImg, paint);

    //delete pntImg;
    //delete kImg;
	//delete img;
	return kImg;
}

