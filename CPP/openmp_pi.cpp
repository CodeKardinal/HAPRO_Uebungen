#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

double pi (uintmax_t num_iter){
	const double delta_x = 1.0 / num_iter;
	double sum = 0.0;
	double x, f_x;
	uintmax_t i;
	double zwsum = 0.0;
	
	#pragma omp parallel private(x, f_x, zwsum) shared(sum)
	{
		zwsum = 0;
		#pragma omp for
		for (i = 1; i <= num_iter; i++) 
		{
			x = delta_x * (i-0.5);
			f_x = 4.0 / (1.0 + x*x);
			zwsum += f_x;

		}

		#pragma omp critical
		{
			sum += zwsum;
		}
	}

		return delta_x * sum;
}


uintmax_t fak(uintmax_t f){
	if (f <= 0){
		return (1);
	}
	return (fak(f - 1) * f);
}


double pi_imp (uintmax_t num_iter){
	double sum = 0.0;
	uintmax_t i, fak1, fak2;
	double zwsum = 0.0;

	#pragma omp parallel private(zwsum) shared(sum)
	{
		zwsum = 0;
		#pragma omp for
		for (i = 0; i <= num_iter; i++) 
		{
			if(i>0)
			{
				for(uintmax_t n = 1; n <= 4*i; i++)
				{
				fak1 *= n;
				}
				for(uintmax_t n = 1; n <= i; i++)
				{
				fak2 *= n;
				}
				
			}
			else
			{
				fak1 = 1;
				fak2 = 1;
			}
				
				
			//zwsum += (fak(4*i) * (1103 + (26390 * i))) / (pow(fak(i), 4) * pow(396, 4*i));
			zwsum += (fak1 * (1103 + (26390 * i))) / (pow(fak2, 4) * pow(396, 4*i));
		}

		#pragma omp critical
		{
			sum += zwsum;
		}
	}

		sum = (sqrt(8)/9801) * sum;
		return 1 / sum;
}


int main (int argc, char* argv []) {
	int nthreads, tid;
	double erg;
	omp_set_num_threads(12);
	uintmax_t iterations = 10000000000;
	printf("Musterloesung:      3.14159265358979323846264338327950288419716939937510\n");
	
	int ticks = GetTickCount();
	//erg = pi(iterations);
	erg = pi(1000000000);
	ticks = GetTickCount() - ticks;
	printf("Ergebnis Integral:  %.50f, Ticks: %d\n", erg, ticks);
	
	ticks = GetTickCount();
	//erg = pi_imp(iterations);
	erg = pi_imp(12);
	ticks = GetTickCount() - ticks;
	printf("Ergebnis Ramanujan: %.50f, Ticks: %d\n", erg, ticks);
	
	
	return 0;
}


