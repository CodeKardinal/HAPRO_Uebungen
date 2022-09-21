#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdint.h>
#include <inttypes.h>

double pi (uintmax_t num_iter){
	const double delta_x = 1.0 / num_iter;
	double sum = 0.0;
	double x, f_x;
	uintmax_t i;
	double zwsum = 0;
	
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


int main (int argc, char* argv []) {
	int nthreads, tid;
	double erg;
	omp_set_num_threads(6);
	
	int ticks = GetTickCount();
	
	uintmax_t iterations = 100000000000;
	erg = pi(iterations);
	
	ticks = GetTickCount() - ticks;
	printf("Summe: %.20f, Ticks: %d\n", erg, ticks);
}


