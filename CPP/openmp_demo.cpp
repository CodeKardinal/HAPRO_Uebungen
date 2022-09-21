#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main (int argc, char argv []) {
	int nthreads, tid;
	omp_set_num_threads(6);
	
	#pragma omp parallel private( nthreads , tid)
	{ /* Fork */
		tid = omp_get_thread_num();
		printf("Hello World from thread = %d\n", tid);
		if (tid == 0) {
			nthreads = omp_get_num_threads();
			printf("Hi, i am the master thread\n");
			printf("Number of threads = %d\n", nthreads);
		}
	} /* Join */
	
	int ticks = GetTickCount();
	
	// Gauﬂ
	int gesamtsumme;
	int zwischensumme;
	int i;
	gesamtsumme = 0;
	
	#pragma omp parallel private(i, zwischensumme) shared(gesamtsumme)
	{
		zwischensumme = 0;
		#pragma omp for
		for (i = 1; i <= 100000000; i++) {
			zwischensumme = zwischensumme + i;
		}
		#pragma omp critical
		{
			gesamtsumme = gesamtsumme + zwischensumme;
		}
	}
	ticks = GetTickCount() - ticks;
	printf("Summe: %d, Ticks: %d\n", gesamtsumme, ticks);
}

