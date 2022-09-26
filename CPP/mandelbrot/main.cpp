#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#include <stdio.h>
#include <windows.h>
#include <SDL.h>
#include <complex>

#include <omp.h>

SDL_Surface *surface;
SDL_Event *evt;

	
void putPixel(int X, int Y, int color) {
	// zeichnen
	unsigned char *scr = (unsigned char *)(surface->pixels);
	scr += Y * surface->pitch + X * 4;
	*((unsigned int *)scr) = color;
}


int mandelbrot(double real, double imag) {
	int limit = 256;
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
			putPixel(i, j, palette[iters]);
		}
	}
	return GetTickCount() - ticks;	
}


int mandelbrot_multi(int height, int width, double x_start, double y_fin, double dx, double dy, unsigned int palette[])
{	
	int ticks = GetTickCount();
	
	double x, y;
	int iters, i, j;
		for (i = 0; i < width; i++) {
			#pragma omp parallel for private(x, y, iters, j) shared (i, width, height) schedule (dynamic, 10)
			for (j = 0; j < height; j++) {
				x = x_start + j*dx; // current real value
				y = y_fin - i*dy; // current imaginary value
				iters = mandelbrot(x,y);
				putPixel(i, j, palette[iters]);
					
			}
		}	
	return GetTickCount() - ticks;
}


int main(int argc, char** argv) {
	freopen( "CON", "wt", stdout );
	freopen( "CON", "wt", stderr );
	
	unsigned int palette[256] = {
	0x00200000,0x00240000,0x00280000,0x002C0000,0x00300000,0x00340000,0x00380000,0x003C0000,
	0x00400000,0x00440000,0x00480000,0x004C0000,0x00500000,0x00540000,0x00580000,0x005C0000,
	0x00600000,0x00640000,0x00680000,0x006C0000,0x00700000,0x00740000,0x00780000,0x007C0000,
	0x00800000,0x00840000,0x00880000,0x008C0000,0x00900000,0x00940000,0x00980000,0x009C0000,
	0x00A00000,0x00A40000,0x00A80000,0x00AC0000,0x00B00000,0x00B40000,0x00B80000,0x00BC0000,
	0x00C00000,0x00C40000,0x00C80000,0x00CC0000,0x00D00000,0x00D40000,0x00D80000,0x00DC0000,
	0x00E00000,0x00E40000,0x00E80000,0x00EC0000,0x00F00000,0x00F40000,0x00F80000,0x00FC0000,
	0x00FF0000,0x00FF0400,0x00FF0800,0x00FF0C00,0x00FF1000,0x00FF1400,0x00FF1800,0x00FF1C00,
	0x00FF2000,0x00FF2400,0x00FF2800,0x00FF2C00,0x00FF3000,0x00FF3400,0x00FF3800,0x00FF3C00,
	0x00FF4000,0x00FF4400,0x00FF4800,0x00FF4C00,0x00FF5000,0x00FF5400,0x00FF5800,0x00FF5C00,
	0x00FF6000,0x00FF6400,0x00FF6800,0x00FF6C00,0x00FF7000,0x00FF7400,0x00FF7800,0x00FF7C00,
	0x00FF8000,0x00FF8400,0x00FF8800,0x00FF8C00,0x00FF9000,0x00FF9400,0x00FF9800,0x00FF9C00,
	0x00FFA000,0x00FFA400,0x00FFA800,0x00FFAC00,0x00FFB000,0x00FFB400,0x00FFB800,0x00FFBC00,
	0x00FFC000,0x00FFC400,0x00FFC800,0x00FFCC00,0x00FFD000,0x00FFD400,0x00FFD800,0x00FFDC00,
	0x00FFE000,0x00FFE400,0x00FFE800,0x00FFEC00,0x00FFF000,0x00FFF400,0x00FFF800,0x00FFFC00,
	0x00FFFF00,0x00FFFF02,0x00FFFF04,0x00FFFF06,0x00FFFF08,0x00FFFF0A,0x00FFFF0C,0x00FFFF0E,
	0x00FFFF10,0x00FFFF12,0x00FFFF14,0x00FFFF16,0x00FFFF18,0x00FFFF1A,0x00FFFF1C,0x00FFFF1E,
	0x00FFFF20,0x00FFFF22,0x00FFFF24,0x00FFFF26,0x00FFFF28,0x00FFFF2A,0x00FFFF2C,0x00FFFF2E,
	0x00FFFF30,0x00FFFF32,0x00FFFF34,0x00FFFF36,0x00FFFF38,0x00FFFF3A,0x00FFFF3C,0x00FFFF3E,
	0x00FFFF40,0x00FFFF42,0x00FFFF44,0x00FFFF46,0x00FFFF48,0x00FFFF4A,0x00FFFF4C,0x00FFFF4E,
	0x00FFFF50,0x00FFFF52,0x00FFFF54,0x00FFFF56,0x00FFFF58,0x00FFFF5A,0x00FFFF5C,0x00FFFF5E,
	0x00FFFF60,0x00FFFF62,0x00FFFF64,0x00FFFF66,0x00FFFF68,0x00FFFF6A,0x00FFFF6C,0x00FFFF6E,
	0x00FFFF70,0x00FFFF72,0x00FFFF74,0x00FFFF76,0x00FFFF78,0x00FFFF7A,0x00FFFF7C,0x00FFFF7E,
	0x00FFFF80,0x00FFFF82,0x00FFFF84,0x00FFFF86,0x00FFFF88,0x00FFFF8A,0x00FFFF8C,0x00FFFF8E,
	0x00FFFF90,0x00FFFF92,0x00FFFF94,0x00FFFF96,0x00FFFF98,0x00FFFF9A,0x00FFFF9C,0x00FFFF9E,
	0x00FFFFA0,0x00FFFFA2,0x00FFFFA4,0x00FFFFA6,0x00FFFFA8,0x00FFFFAA,0x00FFFFAC,0x00FFFFAE,
	0x00FFFFB0,0x00FFFFB2,0x00FFFFB4,0x00FFFFB6,0x00FFFFB8,0x00FFFFBA,0x00FFFFBC,0x00FFFFBE,
	0x00FFFFC0,0x00FFFFC2,0x00FFFFC4,0x00FFFFC6,0x00FFFFC8,0x00FFFFCA,0x00FFFFCC,0x00FFFFCE,
	0x00FFFFD0,0x00FFFFD2,0x00FFFFD4,0x00FFFFD6,0x00FFFFD8,0x00FFFFDA,0x00FFFFDC,0x00FFFFDE,
	0x00FFFFE0,0x00FFFFE2,0x00FFFFE4,0x00FFFFE6,0x00FFFFE8,0x00FFFFEA,0x00FFFFEC,0x00FFFFEE,
	0x00FFFFF0,0x00FFFFF2,0x00FFFFF4,0x00FFFFF6,0x00FFFFF8,0x00FFFFFA,0x00FFFFFC,0x00FFFFFE,
	0x00000000};
	
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
	
	
	omp_set_num_threads(4);
	
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
