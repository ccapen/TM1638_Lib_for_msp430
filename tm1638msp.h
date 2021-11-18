/*
 * tm1638msp.h
 *
 *  Created on: 2021Äê5ÔÂ28ÈÕ
 *      Author: Administrator
 */

#ifndef TM1638MSP_H_
#define TM1638MSP_H_

#include <msp430f5529.h>
#define u8 unsigned char

#define Tpwclk 0.4/////all in "micro second"
#define Tpwstb 1
#define Tsetup 0.1
#define Thold 0.1
#define Tclkstb 1
#define Twait 1
#define Tplz 0.3
#define Tpzl 0.1

#define STBup P6OUT|=BIT0
#define STBdw P6OUT&=~BIT0
#define CLKup P6OUT|=BIT1
#define CLKdw P6OUT&=~BIT1
#define DIOup P6OUT|=BIT2
#define DIOdw P6OUT&=~BIT2
#define rdDIO P6IN&BIT2
#define STBinit {P6DIR|=BIT0;STBup;}
#define CLKinit {P6DIR|=BIT1;CLKup;}
#define DIOinit {P6DIR|=BIT2;DIOup;}
#define DIOsetrd {P6DIR&=~BIT2;DIOup;}


void tm_init(void);
void tm_clear(void);
void setNum(u8 order,u8 num);//num==16 >> clear
void setNumdot(u8 order,u8 num);//same as setNum(), expect dot
void setLed(u8 order,u8 on);
u8 readKey(void);           //return the order of key
u8 readKeylist(u8 *keylist);//return number of keys

#endif /* TM1638MSP_H_ */
