#include<reg52.h>
#define u16 unsigned int 

int runPwm(u16 arg);
void delay(u16 i);

sbit Linput = P2^0;
sbit Rinput = P2^1;
sbit Loutput = P3^0;
sbit Routput = P3^1;
u16 Lduty_ratio=0;    //Left duty ratio
u16 Rduty_ratio=0;		//Right duty ratio
u16 cycle_limit=100;	//Pwm cycle limit
u16 cycle=0;					//Pwm cycle value





void main(){
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1){
		
	}
}



void T0_interrupt() interrupt 1{
	Loutput = runPwm(Lduty_ratio);
	Routput = runPwm(Rduty_ratio);
	cycle++;
	if(cycle==100){
		cycle=0;
	}
}

int runPwm(u16 arg){
	if(cycle<arg){
		return 1;
	}else{
		return 0;
	}
}

void delay(u16 i){
	while(i--);
}
