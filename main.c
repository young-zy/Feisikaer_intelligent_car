#include<reg52.h>
#define u16 unsigned int 

int runPwm(u16 arg);
void delay(u16 i);
int get_status();

sbit Linput = P2^0;
sbit Rinput = P2^1;
sbit Loutput = P1^0;
sbit Routput = P3^3;
u16 Lduty_ratio=0;    //Left duty ratio
u16 Rduty_ratio=0;		//Right duty ratio
u16 cycle_limit=100;	//Pwm cycle limit
u16 cycle=0;					//Pwm cycle value
u16 flag=0;						//status flag || 0 for none || 1 for Left input || 2 for right input || 3 for both
u16 Ojudge=0;
sbit LL=P3^4;
sbit LR=P3^5;
sbit RL=P3^6;
sbit RR=P3^7;



void main(){
	TMOD=0x01;
	TH0=(65536-700)/256;
	TL0=(65536-700)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1){
		flag=get_status();;
//		if(Ojudge==3){break;}
		if(flag==0){
			Lduty_ratio = 35;
			Rduty_ratio = 35;
			LL=0;
			LR=1;
			RL=0;
			RR=1;
		}else if(flag==1){
			RL=0;
			RR=1;
			LL=1;
			LR=0;
			Lduty_ratio = 50;  //turn left
			Rduty_ratio = 50;
		}else if(flag==2){
			LL=0;
			LR=1;
			RL=1;
			RR=0;
			Lduty_ratio = 50;  //turn right
			Rduty_ratio = 50;
//		}else if(flag==3){
//			Lduty_ratio = 40;  //turn left rapidly
//			Rduty_ratio = 70;
//		}else if(flag==4){
//			Lduty_ratio = 70;  //turn right rapidly
//			Rduty_ratio = 40;
		}
	}
}



void T0_interrupt() interrupt 1{
	TH0=(65536-700)/256;
	TL0=(65536-700)%256;
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

int get_status(){
	if(Linput==1){
//		if(Rinput==1){
//			Ojudge++;
//			return 3; 
//		}else{
			return 1;
//		}
	}else if(Rinput==1){
		return 2;
	}else{  
		return 0;
	}
}

void delay(u16 i){
	while(i--);
}
