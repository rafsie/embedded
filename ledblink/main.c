#include <stdio.h>
#include <stdlib.h>
#include "AT91SAM9263.h"
#include "AT91SAM9263-EK.h"
#define LED1 (1<<8)

void dbgu_print_ascii(const char* string){
}

void del();

*(PIOB_PDR) = 0xFFFFFFFF;

int main(){
	*AT91C_PIOB_PER = 1<<8;
	*AT91C_PIOB_OER = 1<<8;
	unsigned count=0;	

	while(1){
		if(count % 1111 == 0)
		{
			*AT91C_PIOB_SODR = LED1;
			del();
		}
		if(count % 2313 == 0)
		{
			*AT91C_PIOB_CODR = LED1;
			del();
		}
	++count;
	}

	return 0;
}

void del(){
volatile int i;
	for(i=0;i<1000000;i++);
}
