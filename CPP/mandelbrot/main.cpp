#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include <stdio.h>
#include <windows.h>
#include <SDL.h>
#include <complex>

#include <omp.h>
#include <math.h>
#include <inttypes.h>

SDL_Surface *surface;
SDL_Event *evt;

int limit = 2016;

	
void putPixel(int X, int Y, int color) {
	// zeichnen
	unsigned char *scr = (unsigned char *)(surface->pixels);
	scr += Y * surface->pitch + X * 4;
	*((unsigned int *)scr) = color;
}


int mandelbrot(double real, double imag) {
	double zReal = real;
	double zImag = imag;

	for (int i = 0; i < limit; ++i) {
		double r2 = zReal * zReal;
		double i2 = zImag * zImag;
		
		if (r2 + i2 > 4.0) return i;

		zImag = 2.0 * zReal * zImag + imag;
		zReal = r2 - i2 + real;
	}
	return limit;
}


int mandelbrot_single(int heigth, int width, double x_start, double y_fin, double dx, double dy, unsigned int palette[])
{
	int ticks = GetTickCount();
	
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < heigth; j++) {
			double x = x_start + j*dx; // current real value
			double y = y_fin - i*dy; // current imaginary value
			
			int iters = mandelbrot(x,y);
			double t=sqrt(iters)*limit/13;
			putPixel(i, j, palette[(int) t]);
		}
	}
	return GetTickCount() - ticks;	
}


int mandelbrot_multi(int height, int width, double x_start, double y_fin, double dx, double dy, unsigned int palette[])
{	
	int ticks = GetTickCount();
	
	double x, y;
	int iters, i, j;
	#pragma omp parallel for collapse(2) private(x, y, iters, j) shared (i, width, height) schedule (dynamic, 10)
	for (i = 0; i < width; i++) {
		for (j = 0; j < height; j++) {
			x = x_start + j*dx; // current real value
			y = y_fin - i*dy; // current imaginary value
			iters = mandelbrot(x,y);
			double t=sqrt(iters)*limit/13;
			putPixel(i, j, palette[(int) t]);
				
		}
	}	
	return GetTickCount() - ticks;
}


int main(int argc, char** argv) {
	freopen( "CON", "wt", stdout );
	freopen( "CON", "wt", stderr );
	
	unsigned int palette[limit] ;
	unsigned int m = 0, n = 0;
	
	unsigned int step = 255*255*255 / limit;
	unsigned long color;
	
	int red, green, blue;
	
	for (red = 32; red <=255; red ++){
		color = ((0 & 0xff) << 24) + ((red & 0xff) << 16) + ((0 & 0xff) << 8) + (0 & 0xff);
		palette[n] = color;
		n++;
	}
	for (green = 0; green <=255; green++){
		color = ((0 & 0xff) << 24) + ((255 & 0xff) << 16) + ((green & 0xff) << 8) + (0 & 0xff);
		palette[n] = color;
		n++;
	}
	for (red = 255; red >=0; red--){
		color = ((0 & 0xff) << 24) + ((red & 0xff) << 16) + ((255 & 0xff) << 8) + (0 & 0xff);
		palette[n] = color;
		n++;
	}
	for (blue = 0; blue <=255; blue++){
		color = ((0 & 0xff) << 24) + ((0 & 0xff) << 16) + ((255 & 0xff) << 8) + (blue & 0xff);
		palette[n] = color;
		n++;
	}
	for (green = 255; green >=0; green--){
		color = ((0 & 0xff) << 24) + ((0 & 0xff) << 16) + ((green & 0xff) << 8) + (255 & 0xff);
		palette[n] = color;
		n++;
	}
	for (red = 0; red <=255; red++){
		color = ((0 & 0xff) << 24) + ((red & 0xff) << 16) + ((0 & 0xff) << 8) + (255 & 0xff);
		palette[n] = color;
		n++;
	}
	for (blue = 255; blue >=0; blue--){
		color = ((0 & 0xff) << 24) + ((255 & 0xff) << 16) + ((0 & 0xff) << 8) + (blue & 0xff);
		palette[n] = color;
		n++;
	}
	for (red = 255; red >=0; red--){
		color = ((0 & 0xff) << 24) + ((red & 0xff) << 16) + ((0 & 0xff) << 8) + (255 & 0xff);
		palette[n] = color;
		n++;
	}

	
	color = ((0 & 0xff) << 24) + ((0 & 0xff) << 16) + ((0 & 0xff) << 8) + (0 & 0xff);
	palette[n] = color;	
	
	int width = 1080, height = 1080, ticks;
	
	double x_start = -2.0;
	double x_fin = 1.0;
	double y_start = -1.0;
	double y_fin = 1.0;
	
	double dx = (x_fin - x_start)/(width - 1);
	double dy = (y_fin - y_start)/(height - 1);
	
	SDL_Init(SDL_INIT_VIDEO);
	surface = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
		
	evt = new SDL_Event;	
	do {
		ticks = mandelbrot_single(height, width, x_start, y_fin, dx, dy, palette);
		printf("Ticks Single: %i\n", ticks);
		
		SDL_UnlockSurface(surface);
		SDL_Flip(surface);
		SDL_PollEvent(evt);
	} while (evt->type != SDL_KEYDOWN);
	
	
	evt = new SDL_Event;
	do {
		SDL_LockSurface(surface);
	
		ticks = mandelbrot_multi(width, height, x_start, y_fin, dx, dy, palette);
		printf("Ticks Multi:  %i\n", ticks);

		SDL_UnlockSurface(surface);
		SDL_Flip(surface);
		SDL_PollEvent(evt);
	} while (evt->type != SDL_KEYDOWN);
	
	
	return 0;
}
