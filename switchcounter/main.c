#include <stdio.h>
#include <stdlib.h>
#include "AT91SAM9263.h"
#include "AT91SAM9263-EK.h"
#define PB(x) (1<<(x))

void start()
{
    volatile int i;
    for(i=20; i<=31; i++) {
        AT91C_BASE_PIOB -> PIO_MDDR = PB(i);
        AT91C_BASE_PIOB -> PIO_PER = PB(i);
        AT91C_BASE_PIOB -> PIO_OER = PB(i);
    }
    AT91C_BASE_PIOB -> PIO_CODR = PB(29);
    *AT91C_PIOC_PER=AT91C_PIO_PC5;
}

void start_right()
{
    AT91C_BASE_PIOB -> PIO_SODR = PB(28);
    AT91C_BASE_PIOB -> PIO_CODR = PB(30);
}

void start_left()
{
    AT91C_BASE_PIOB -> PIO_CODR = PB(28);
    AT91C_BASE_PIOB -> PIO_SODR = PB(30);
}

int on(char letter)
{
    if(letter == 'A') {
        AT91C_BASE_PIOB -> PIO_SODR = PB(25);
    } else if(letter == 'B') {
        AT91C_BASE_PIOB -> PIO_SODR = PB(24);
    } else if(letter == 'C') {
        AT91C_BASE_PIOB -> PIO_SODR = PB(22);
    } else if(letter == 'D') {
        AT91C_BASE_PIOB -> PIO_SODR = PB(21);
    } else if(letter == 'E') {
        AT91C_BASE_PIOB -> PIO_SODR = PB(20);
    } else if(letter == 'F') {
        AT91C_BASE_PIOB -> PIO_SODR = PB(27);
    } else if(letter == 'G') {
        AT91C_BASE_PIOB -> PIO_SODR = PB(26);
    }
    return 0;
}

int off(char letter)
{
    if(letter == 'A') {
        AT91C_BASE_PIOB -> PIO_CODR = PB(25);
    } else if(letter == 'B') {
        AT91C_BASE_PIOB -> PIO_CODR = PB(24);
    } else if(letter == 'C') {
        AT91C_BASE_PIOB -> PIO_CODR = PB(22);
    } else if(letter == 'D') {
        AT91C_BASE_PIOB -> PIO_CODR = PB(21);
    } else if(letter == 'E') {
        AT91C_BASE_PIOB -> PIO_CODR = PB(20);
    } else if(letter == 'F') {
        AT91C_BASE_PIOB -> PIO_CODR = PB(27);
    } else if(letter == 'G') {
        AT91C_BASE_PIOB -> PIO_CODR = PB(26);
    }
    return 0;
}

int delay()
{
    volatile int i;
    for(i=0; i<100; i++) {};
    return 0;
}

int play_number(int n, int play)
{
    if(n==0) {
        if(play==1) {
            on('A');
            on('B');
            on('C');
            on('D');
            on('E');
            on('F');
        } else {
            off('A');
            off('B');
            off('C');
            off('D');
            off('E');
            off('F');
        }
    } else if(n==1) {
        if(play==1) {
            on('B');
            on('C');
        } else {
            off('B');
            off('C');
        }
    } else if(n==2) {
        if(play==1) {
            on('A');
            on('B');
            on('D');
            on('E');
            on('G');
        } else {
            off('A');
            off('B');
            off('D');
            off('E');
            off('G');
        }
    } else if(n==3) {
        if(play==1) {
            on('A');
            on('B');
            on('C');
            on('D');
            on('G');
        } else {
            off('A');
            off('B');
            off('C');
            off('D');
            off('G');
        }
    } else if(n==4) {
        if(play==1) {
            on('B');
            on('C');
            on('F');
            on('G');
        } else {
            off('B');
            off('C');
            off('F');
            off('G');
        }
    } else if(n==5) {
        if(play==1) {
            on('A');
            on('C');
            on('D');
            on('F');
            on('G');
        } else {
            off('A');
            off('C');
            off('D');
            off('F');
            off('G');
        }
    } else if(n==6) {
        if(play==1) {
            on('A');
            on('C');
            on('D');
            on('E');
            on('F');
            on('G');
        } else {
            off('A');
            off('C');
            off('D');
            off('E');
            off('F');
            off('G');
        }
    } else if(n==7) {
        if(play==1) {
            on('A');
            on('B');
            on('C');
        } else {
            off('A');
            off('B');
            off('C');
        }
    } else if(n==8) {
        if(play==1) {
            on('A');
            on('B');
            on('C');
            on('D');
            on('E');
            on('F');
            on('G');
        } else {
            off('A');
            off('B');
            off('C');
            off('D');
            off('E');
            off('F');
            off('G');
        }
    } else if(n==9) {
        if(play==1) {
            on('A');
            on('B');
            on('C');
            on('D');
            on('F');
            on('G');
        } else {
            off('A');
            off('B');
            off('C');
            off('D');
            off('F');
            off('G');
        }
    }
    return 0;
}

void dbgu_print_ascii(const char* string)
{
}

int main()
{
    start();
    start_right();
    play_number(8,0);
    start_left();
    play_number(8,0);

    volatile int j, k;
    j = 0;
    k = 0;

    //left
    while(1) {
        //right
        while(1) {
            volatile int out = 0;

            volatile int slow;
            for(slow=0; slow<2000; slow++) {
                start_right();
                play_number(j,1);
                delay();
                play_number(j,0);

                start_left();
                play_number(k,1);
                delay();
                play_number(k,0);
            }

            if( (*AT91C_PIOC_PDSR & AT91C_PIO_PC5) == 0) {
                if(j==0) {
                    j=9;
                    out=1;
                } else {
                    j--;
                }
            } else {
                if(j==9) {
                    j=0;
                    out=1;
                } else {
                    j++;
                }
            }

            if(out == 1) {
                break;
            }
        }

        if( (*AT91C_PIOC_PDSR & AT91C_PIO_PC5) == 0) {
            if(k==0) {
                k=9;
            } else {
                k--;
            }
        } else {
            if(k==9) {
                k=0;
            } else {
                k++;
            }
        }
    }
    return 0;
}
