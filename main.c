#include <msp430f5529.h>
#include "tm1638msp.h"

/*
 * main.c
 */
//=====================Demo=================//
int main(void) {
    u8 key[8],t,num;
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	tm_init();
	while(1){
	    num=readKeylist(key);
	    for(t=0;t<num;++t){
	        setNum(t+1,key[t]);
	    }
	    for(;t<8;++t){
	        setNumdot(t+1,16);
	    }
	    t=readKey();
	    setLed(t,1);
	    __delay_cycles(5000);
	    setLed(t,0);
	}
	return 0;
}
