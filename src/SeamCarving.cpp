#include "SeamCarving.h"

//#include "hr_time.h"//DEBUG

#include <math.h>
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;

Kernel *energyKernel(const Image *image, const Kernel *kernelA, const Kernel *kernelB) {
	double operationA, operationB;
	Kernel *ker = 0;

	int temp;

	if(image && kernelA && kernelB) {
		//cout << "Data ok" << endl;
		ker = new Kernel(image->getWidth(), image->getHeight());

		if(kernelA->getHeight()==kernelB->getHeight() && kernelA->getWidth()==kernelB->getWidth()){
			for (unsigned int i=0; i<image->getHeight(); i++ ) {
				for (unsigned int j=0; j<image->getWidth(); j++ ) {
					operationA = operationB = 0.0;
					for (unsigned int ki=0; ki<kernelA->getHeight(); ki++ ) {
						for (unsigned int kj=0; kj<kernelA->getWidth(); kj++ ) {
							int pi = i-int(kernelA->getHeight()/2)+ki;
							int pj = j-int(kernelA->getWidth()/2)+kj;
							if(pi>=0 && pi<image->getHeight() && pj>=0 && pj<image->getWidth()){
								RGB rgbPx( image->getPixel(pi,pj) );
								operationA += rgbPx.intensity()*kernelA->get(ki, kj);
								operationB += rgbPx.intensity()*kernelB->get(ki, kj);
							}
						}
					}
					ker->set(i, j, (double)sqrt(double(operationA*operationA+operationB*operationB)));
				}
			}
		}else{
			for (unsigned int i=0; i<image->getHeight(); i++ ) {
				for (unsigned int j=0; j<image->getWidth(); j++ ) {
					operationA = operationB = 0.0;
					for (unsigned int ki=0; ki<kernelA->getHeight(); ki++ ) {
						for (unsigned int kj=0; kj<kernelA->getWidth(); kj++ ) {
							int pi = i-int(kernelA->getHeight()/2)+ki;
							int pj = j-int(kernelA->getWidth()/2)+kj;
							if(pi>=0 && pi<image->getHeight() && pj>=0 && pj<image->getWidth()){
								RGB rgbPx( image->getPixel(pi,pj) );
								operationA += rgbPx.intensity()*kernelA->get(ki, kj);
							}
						}
					}
					for (unsigned int ki=0; ki<kernelB->getHeight(); ki++ ) {
						for (unsigned int kj=0; kj<kernelB->getWidth(); kj++ ) {
							int pi = i-int(kernelB->getHeight()/2)+ki;
							int pj = j-int(kernelB->getWidth()/2)+kj;
							if(pi>=0 && pi<image->getHeight() && pj>=0 && pj<image->getWidth()){
								RGB rgbPx( image->getPixel(pi,pj) );
								operationB += rgbPx.intensity()*kernelB->get(ki, kj);
							}
						}
					}
					ker->set(i, j, (double)sqrt(double(operationA*operationA+operationB*operationB)));
				}
			}
		}
		//cout << "done ok" << endl;
	}
	return ker;
}

Kernel *sobelEnergyKernel(const Image *image)
{
	Kernel kA(3, 3);
	kA.set(0,0,-1.0); kA.set(0,1,-2.0); kA.set(0,1,-1.0);
	kA.set(1,0,0.0); kA.set(1,1,0.0); kA.set(1,1,0.0);
	kA.set(2,0,1.0); kA.set(2,1,2.0); kA.set(2,1,1.0);

	Kernel kB(3, 3);
	kB.set(0,0,-1.0); kB.set(0,1,0.0); kB.set(0,1,1.0);
	kB.set(1,0,-2.0); kB.set(1,1,0.0); kB.set(1,1,2.0);
	kB.set(2,0,-1.0); kB.set(2,1,0.0); kB.set(2,1,1.0);

	return energyKernel(image, &kA, &kB);
}

bool dpRemoveColumn(const Image *image, const Kernel *energy, Kernel *dist, Image *prevcol, Image *nimg, double &minDist)
{
	for(unsigned int i=0; i<image->getHeight(); i++){
		for(unsigned int j=0; j<image->getWidth(); j++){
			dist->set(i, j, numeric_limits<double>::max());
			prevcol->setPixel(i, j, -1);
		}
	}

	for(unsigned int j=0; j<image->getWidth(); j++){
		//dist->set(0, j, energy->get(0, j));
		dist->set(0, j, 0);
	}

	for(unsigned int i=0; i<image->getHeight(); i++){
		for(unsigned int j=0; j<image->getWidth(); j++){
			int nrow = i+1;
			int ncol = j-1;
			if(nrow<image->getHeight() && (ncol>=0 && ncol<image->getWidth())){
				double alt = dist->get(i, j) + energy->get(nrow, ncol);
				//if(dist->get(nrow, ncol)<0 || alt<dist->get(nrow, ncol)){
				if(alt<dist->get(nrow, ncol)){
					dist->set(nrow, ncol, alt);
					prevcol->setPixel(nrow, ncol, j);
				}
			}

			nrow = i+1;
			ncol = j;
			if(nrow<image->getHeight() && (ncol>=0 && ncol<image->getWidth())){
				double alt = dist->get(i, j) + energy->get(nrow, ncol);
				if(alt<dist->get(nrow, ncol)){
					dist->set(nrow, ncol, alt);
					prevcol->setPixel(nrow, ncol, j);
				}
			}

			nrow = i+1;
			ncol = j+1;
			if(nrow<image->getHeight() && (ncol>=0 && ncol<image->getWidth())){
				double alt = dist->get(i, j) + energy->get(nrow, ncol);
				if(alt<dist->get(nrow, ncol)){
					dist->set(nrow, ncol, alt);
					prevcol->setPixel(nrow, ncol, j);
				}
			}
		}
	}

	int col = -1;
	double min = numeric_limits<double>::max();
	for(int j = 0; j<dist->getWidth(); j++){
		double d = dist->get(image->getHeight()-1, j);
		if(d>=0 && d<min){
			col = j;
			min = d;
		}
	}


	if(col>=0){
		//if(minDist<0 || min<minDist){
			int nj;

			minDist = min;

			for(int i = image->getHeight()-1; i>=0; i--){
				nj = 0;
				for(int j = 0; j<image->getWidth(); j++){
					if(j!=col){
						nimg->setPixel(i, nj, image->getPixel(i, j));
						nj++;
					}
				}
				col = prevcol->getPixel(i, col);
			}
		//}
	}else {
		//cout << "min: " << min << " col: " << col << endl;
		return false;
	}

	return true;
}
/*
bool dpRemoveColumn(const Image *image, const Kernel *energy, Kernel *dist, Image *prevcol, Image *nimg, double &minDist)
{
	for(unsigned int i=0; i<image->getHeight(); i++){
		for(unsigned int j=0; j<image->getWidth(); j++){
			dist->set(i, j, -1);
			prevcol->setPixel(i, j, -1);
		}
	}

	for(unsigned int j=0; j<image->getWidth(); j++){
		//dist->set(0, j, energy->get(0, j));
		dist->set(0, j, 0);
	}

	for(unsigned int i=0; i<image->getHeight(); i++){
		for(unsigned int j=0; j<image->getWidth(); j++){
			int nrow = i+1;
			int ncol = j-1;
			if(nrow<image->getHeight() && (ncol>=0 && ncol<image->getWidth())){
				double alt = dist->get(i, j) + energy->get(nrow, ncol);
				if(dist->get(nrow, ncol)<0 || alt<dist->get(nrow, ncol)){
				//if(alt<dist->get(nrow, ncol)){
					dist->set(nrow, ncol, alt);
					prevcol->setPixel(nrow, ncol, j);
				}
			}

			nrow = i+1;
			ncol = j;
			if(nrow<image->getHeight() && (ncol>=0 && ncol<image->getWidth())){
				double alt = dist->get(i, j) + energy->get(nrow, ncol);
				if(dist->get(nrow, ncol)<0 || alt<dist->get(nrow, ncol)){
				//if(alt<dist->get(nrow, ncol)){
					dist->set(nrow, ncol, alt);
					prevcol->setPixel(nrow, ncol, j);
				}
			}

			nrow = i+1;
			ncol = j+1;
			if(nrow<image->getHeight() && (ncol>=0 && ncol<image->getWidth())){
				double alt = dist->get(i, j) + energy->get(nrow, ncol);
				if(dist->get(nrow, ncol)<0 || alt<dist->get(nrow, ncol)){
				//if(alt<dist->get(nrow, ncol)){
					dist->set(nrow, ncol, alt);
					prevcol->setPixel(nrow, ncol, j);
				}
			}
		}
	}

	int col = -1;
	double min = -1;
	for(int j = 0; j<dist->getWidth(); j++){
		double d = dist->get(image->getHeight()-1, j);
		if(d>=0){
			if(col==-1){
				col = j;
				min = d;
			}else if(d<min){
				col = j;
				min = d;
			}
		}
	}

	if(col>=0){
		//if(minDist<0 || min<minDist){
			int nj = 0;

			minDist = min;
	
			for(int i = image->getHeight()-1; i>=0; i--){
				for(int j = 0; j<image->getWidth(); j++){
					if(j!=col){
						nimg->setPixel(i, nj, image->getPixel(i, j));
						nj++;
					}
				}
				nj = 0;
				col = prevcol->getPixel(i, col);
			}
		//}
	}else {
		return false;
	}

	return true;
}
*/
Image *seamCarvingColumn(const Image *image, const Kernel *energy)
{
	//cout << "seam carving" << endl;
	//double mdist;
	double min;

	//for reasons of bad_malloc, we need to keep a working malloc for the many calls of dijkstraColumn
	Kernel *dist = new Kernel(image->getWidth(), image->getHeight());
	Image *prevcol = new Image(image->getWidth(), image->getHeight(), Image::GREY_SCALE_IMAGE);
	//Image *vset = new Image(image->getWidth(), image->getHeight(), Image::GREY_SCALE_IMAGE);
	//Image *img = new Image(image->getWidth()-1, image->getHeight(), image->getChannel());
	Image *minImg = new Image(image->getWidth()-1, image->getHeight(), image->getChannel());

	//Image *swapImg;

	//hr_timer_t timer; //DEBUG
	min = -1.0;
	//cout << "Dijkstra: "; //DEBUG
	//hrt_start(&timer); //DEBUG
	//for(int j = 0; j<image->getWidth(); j++){
	dpRemoveColumn(image, energy, dist, prevcol, minImg, min);
	//}
	//hrt_stop(&timer); //DEBUG
	//cout << " min: " << min; //DEBUG
	//cout  << " -- " << hrt_elapsed_time(&timer) << "s" << endl; //DEBUG

	delete dist;
	delete prevcol;
	//delete vset;
	//delete img;

	return minImg;
}

Image *seamCarvingRemoveColumn(const Image *image, int nCol, const Kernel *kerGx, const Kernel *kerGy)
{
	if(nCol>0){
		//cout << "removing column: " << 1 << " of " << nCol << endl; //DEBUG
		Kernel *energy = 0;
        //cout << "HERE 1" << endl;
		if(kerGx==0 || kerGy==0){
            energy = sobelEnergyKernel(image);
        }else{
            energy = energyKernel(image, kerGx, kerGy);
            //cout << "dif. energy" << endl;
        }
        //cout << "HERE 2" << endl;
        if(!energy) return 0;

		Image *img = seamCarvingColumn(image, energy);
		delete energy;
		for(int i = 1; i<nCol; i++){
			//cout << "removing column: " << (i+1) << " of " << nCol << endl; //DEBUG
			//cout << "Sobel Energizing" << endl; //DEBUG
			//energy = sobelEnergyKernel(img); //DEBUG
            if(kerGx==0 || kerGy==0){
                energy = sobelEnergyKernel(img);
            }else{
                energy = energyKernel(img, kerGx, kerGy);
            }
			//cout << "calling Seam Carving" << endl; //DEBUG
			Image *temp = seamCarvingColumn(img, energy);
			delete img;
			img = temp;
			delete energy;
		}
		return img;
	}else return 0;
}

