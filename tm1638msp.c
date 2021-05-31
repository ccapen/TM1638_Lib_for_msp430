/*
 * tm1638.c
 *
 *  Created on: 2021Äê5ÔÂ28ÈÕ
 *      Author: Administrator
 */
#include "tm1638msp.h"
void delay_us(u8 i){
	while(--i);
    return;
}
void sendbyte(u8 i){
	u8 t;
	STBdw;
	for(t=8;t;--t){
		CLKdw;
		if(i&1) DIOup;
		else DIOdw;
		i>>=1;
		delay_us(1);
		CLKup;
		delay_us(1);
	}
	STBup;
	delay_us(1);
	return;
}
u8 receivebyte(void){
	u8 t,i=0;
	STBdw;
	for(t=8;t;--t){
		CLKdw;
		delay_us(1);
		i<<=1;
		if(rdDIO) i++;
		CLKup;
		delay_us(1);
	}
	STBup;
	delay_us(1);
	return i;
}
void sendbytewstb(u8 i){
	u8 t;
	for(t=8;t;--t){
		CLKdw;
		if(i&1) DIOup;
		else DIOdw;
		i>>=1;
		delay_us(1);
		CLKup;
		delay_us(1);
	}
	return;
}
u8 receivebytewstb(void){
	u8 t,i=0;
	DIOsetrd;
	for(t=8;t;--t){
		CLKdw;
		delay_us(1);
		i<<=1;
		if(rdDIO) i++;
		CLKup;
		delay_us(1);
	}
	DIOinit;
	return i;
}
void sendbytesinc(u8 address,u8 num,const u8 *data){
	u8 t;
	sendbyte(0x40);
	STBdw;
	delay_us(1);
	sendbytewstb(0xc0|address);
	for(t=num;t;--t){
		sendbytewstb(*data);
		data++;
	}
	STBup;
	delay_us(1);
    return;
}
void sendbytesfixed(u8 address,u8 data){
	sendbyte(0x44);
	STBdw;
	delay_us(1);
	sendbytewstb(0xc0|address);
	sendbytewstb(data);
	STBup;
	delay_us(1);
	return;
}
void receivebytes(u8 *data){
    u8 t;
    STBdw;
    delay_us(1);
    sendbytewstb(0x42);
    delay_us(2);
    for(t=4;t;--t){
        *data=receivebytewstb();
        data++;
    }
    STBup;
    delay_us(1);
    return;
}
/*bit0~7:a~g,'.'*/
const u8 dig[17]={0x3f,0x6,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0};
const u8 cleardata[16]={0};
void tm_init(void){
    STBinit;
    CLKinit;
    DIOinit;
	sendbytesinc(0,16,cleardata);
	sendbyte(0x88);
    return;
}
void tm_clear(void){
    sendbytesinc(0,16,cleardata);
    return;
}
void setNum(u8 order,u8 num){
    if(order>8||!order||num>0x10) return;
    sendbytesfixed((order-1)<<1,dig[num]);
}
void setNumdot(u8 order,u8 num){
    if(order>8||!order||num>0x10) return;
    sendbytesfixed((order-1)<<1,dig[num]|0x80);
}
void setLed(u8 order,u8 on){
    if(order>8||!order) return;
    if(on) on=1;
    sendbytesfixed(((order-1)<<1)+1,on);
}
u8 keydata[4];
u8 readKey(void){
    u8 t;
    receivebytes(keydata);
    for(t=0;t<4;++t)
        if(keydata[t]&0x80) return t+1;
    for(t=0;t<4;++t)
        if(keydata[t]&8) return t+5;
    return 0;
}
u8 readKeylist(u8 *keylist){
    u8 t,num=0;
    receivebytes(keydata);
    for(t=0;t<4;++t)
        if(keydata[t]&0x80){
            *keylist=t+1;
            keylist++;
            num++;
        }
    for(t=0;t<4;++t)
        if(keydata[t]&8){
            *keylist=t+5;
            keylist++;
            num++;
        }
    return num;
}
