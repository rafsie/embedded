#include <stdio.h>
#include <stdlib.h>
#include "AT91SAM9263.h"
#include "AT91SAM9263-EK.h"
#define LED1 (1<<8)

int start();
int stop();
int delay();
int blink();

void dbgu_print_ascii(const char* string){
}

int main()
{
	*AT91C_PIOB_PER=1<<8;
	*AT91C_PIOB_OER=1<<8;
	*AT91C_PIOC_PER=AT91C_PIO_PC5;
	*AT91C_PIOC_ODR=AT91C_PIO_PC5;
	*AT91C_PIOC_PPUER=AT91C_PIO_PC5;

	int counter = 0;
	int led_status = 0;

	while(1)
	{
		volatile int x;
		x = *AT91C_PIOC_PDSR;
		x = AT91C_PIO_PC5;
		x = *AT91C_PIOC_PDSR & AT91C_PIO_PC5;

		if ((counter % 1000000) == 0)
		{
			if (led_status == 0)
			{
				start();
				led_status = 1;
			}

			else
			{
				stop();
				led_status = 0;
			}
		}

		if( (*AT91C_PIOC_PDSR & AT91C_PIO_PC5) == 0) //switch BP1
		{
			start();
		}

		counter++;
	}

	return 0;
}

int start(){
	*AT91C_PIOB_CODR = 1<<8;
	return 0;
	}

int stop(){
	*AT91C_PIOB_SODR = 1<<8;
	return 0;
	}

int delay(){
	volatile int i;
	for(i=0; i<1000000; i++){
	}
	return 0;
	}

int blink(){
	start();
	delay();
	stop();
	delay();
	return 0;
}
