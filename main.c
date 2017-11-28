#include<reg52.h>
#define u16 unsigned int 
#define v0 50 //0
#define v1 40 //L R
#define v2 60 //LL RR
#define D 100 //delay
#define v3 70 //
int runPwm(u16 arg);
void delay(u16 i);
int get_status();

sbit Linput = P2^0;
sbit Rinput = P2^1;
sbit LLinput = P2^2;
sbit RRinput = P2^3;
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
	TH0=(65536-20)/256;
	TL0=(65536-20)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1){
		flag=get_status();
		if(flag==0){
			LL=0;
			LR=1;
			RL=0;
			RR=1;
			Lduty_ratio = v0;
			Rduty_ratio = v0;
		}else if(flag==1){
			RL=0;
			RR=1;
			LL=1;
			LR=0;
			Lduty_ratio = v1;  //turn left
			Rduty_ratio = v2;
		}else if(flag==2){
			LL=0;
			LR=1;
			RL=1;
			RR=0;
			Lduty_ratio = v2;  //turn right
			Rduty_ratio = v1;
 	 	}else if(flag==3){
			RL=0;
			RR=1;
			LL=1;
			LR=0;
  		Lduty_ratio = v3;  //turn left rapidly
			Rduty_ratio = v3;
//			delay(D);
		}else if(flag==4){
			LL=0;
			LR=1;
			RL=1;
			RR=0;
			Lduty_ratio = v3;  //turn right rapidly
			Rduty_ratio = v3;
//			delay(D);
		}
	}
}



void T0_interrupt() interrupt 1{
	TH0=(65536-20)/256;
	TL0=(65536-20)%256;
	Loutput = runPwm(Lduty_ratio);
	Routput = runPwm(Rduty_ratio);
	flag=get_status();
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
//	if(Linput==1){
//			return 1;
//	}else if(Rinput==1){
//		return 2;
//	}else{  
//		return 0;
//	}
	if(Linput==1){
			return 1;
	}
	if(Rinput==1){
			return 2;
	}
	if(LLinput==1){
			return 3;
	}	
	if(RRinput==1){
			return 4;
	}
	return 0;
}

void delay(u16 i){
	while(i--);
}
