#include <AT89C51RB2.h>
#include <intrins.h>//for taste - show getInfo from Terminal
#define Fclk	11059000
#define P_OUT	P1_6
#define P_OUTT	P0//for taste - show getInfo from Terminal

unsigned char freq=1;
unsigned int Time_nul;
unsigned int Time_one;

void init_UART(void);
void init_T0(void);
void comp_THTL(unsigned char f);
/*---------------------------------*/
void main(void)
{
init_UART();
init_T0();
EA=1;
while(1);
}
/*---------------------------------*/
void init_UART(void)
{
SM0=0;//SCON.7//Біти вибору режиму роботи
SM1=1;//SCON.6//Біти вибору режиму роботи
SM2=0;//SCON.5//Біт блокування прийому повідомлень з нульовим програмованим 9-тим бітом (діє тільки для режимів 2 та 3)
REN=1;//SCON.4//Дозвіл роботи приймача 
TB8=0;//SCON.3//9-тий біт даних, який передається в режимах 2 та 3
RB8=0;//SCON.2//9-тий прийнятий бід в режимах 2 та 3
TI=0;//SCON.1//Запит на переривання передавача. Встановлюється апаратно після завершення передачі байту. Повинен скидатися програмно в функції обробки переривання.
RI=0;//SCON.0//Запит на переривання приймача. Встановлюється апаратно після завершення прийому байту. Повинен скидатися програмно в функції обробки переривання.
RCAP2L=0xB7;
RCAP2H=0xFF;
T2CON=0x34;
RI=0;
ES=1;
}
/*---------------------------------*/
void int_UART(void) interrupt 4
{
	unsigned char k;
	if(RI)
		{
			RI=0;
			k=SBUF;			
			if(k>='0' && k<='9' )
				{
				freq=k-'0';
				P_OUTT=freq^0xff;//for taste - show getInfo from Terminal
				comp_THTL(freq);
				P2=0;//for taste - show getInfo from Terminalm 2
				}  
		}

	if(TI)TI=0;
}
/*---------------------------------*/
void init_T0(void)
{
unsigned int k;

ET0=1;
TMOD &= 0XF0;                    /* clear Timer 0   */
TMOD |= 0X1;
comp_THTL(freq);

P_OUT=0;
k=Time_nul;
TL0=k;
k=(k&0xFF00);
k>>=8;
TH0=k;
TR0=1;
}
/*---------------------------------*/
void int_T0(void) interrupt 1
{
unsigned int k;
TR0=0;
if(P_OUT)
  {
  P_OUT=0;
  k=Time_nul;
  }
  else 
    {
	P_OUT=1;
	k=Time_one;
	}
TL0=k;
k=(k&0xFF00);
k>>=8;
TH0=k;
TR0=1;
}
/*---------------------------------*/
void comp_THTL(unsigned char f)
{
float Period,Timer_tic;
Period=1/(f*1e3);
Timer_tic=Period*Fclk/12-0x3C;			//0x3C***
Time_one=0xFFFF-Timer_tic/3;				//signal 1/3: _ _-_ _-
Time_nul=0xFFFF-Timer_tic*2/3;
}
/*---------------------------------*/
