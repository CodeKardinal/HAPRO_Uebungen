#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <stdint.h>
#include <inttypes.h>
#include <time.h>       /* time */

uint64_t fib(uint64_t i){
    if (i<3){
        return 1;
    }
    else{
		return fib(i - 1) + fib(i - 2);
    }
}

int main(){
    uint64_t f;
    uintmax_t erg;
    
	erg = 2880067194370816120; //Fib(90)
	printf(" Ergebnis theoretisch: %ju \n", erg);
	printf(" Ergebnis gerechnet:   ");
    
	f = fib(90);
    //f= 1000000000000000;
    
	printf("   %llu \n", f);
	
}
