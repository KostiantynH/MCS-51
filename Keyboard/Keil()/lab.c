#include <AT89C51RB2.h>
#include <intrins.h>

#define P_OUT	P1
#define STB_MAX	4
unsigned char idata STB_cout;
void init_UART(void);
void init_T0(void);
/*---------------------------------*/
void main(void)
{
init_T0();
init_UART();
EA=1;
P_OUT=0;
STB_cout=0;

while(1);
}
/*---------------------------------*/
void init_T0(void)
{
ET0=1;
TMOD &= 0XF0;                    /* clear Timer 0   */
TMOD |= 0X2;

TH0=0;
TR0=1;
}
/*---------------------------------*/
void int_T0(void) interrupt 1
{
unsigned int i;//delay
unsigned char t=255;	
TR0=0;
	P3_4=0x1;
	P3_5=0x1;
	P3_6=0x1;
	P3_7=0x1;

STB_cout++;
if(STB_cout==STB_MAX)STB_cout=0;
	
	if(STB_cout==0)P3_4=0x0;
	if(STB_cout==1)P3_5=0x0;
	if(STB_cout==2)P3_6=0x0;
	if(STB_cout==3)P3_7=0x0;

_nop_();_nop_();_nop_();_nop_();

if((P0_0==0x0)&&(P3_4==0x0))t=0x0;
if((P0_0==0x0)&&(P3_5==0x0))t=0x1;
if((P0_0==0x0)&&(P3_6==0x0))t=0x2;
if((P0_0==0x0)&&(P3_7==0x0))t=0x3;

if((P0_1==0x0)&&(P3_4==0x0))t=0x4;
if((P0_1==0x0)&&(P3_5==0x0))t=0x5;
if((P0_1==0x0)&&(P3_6==0x0))t=0x6;
if((P0_1==0x0)&&(P3_7==0x0))t=0x7;

if((P0_2==0x0)&&(P3_4==0x0))t=0x8;
if((P0_2==0x0)&&(P3_5==0x0))t=0x9;
if((P0_2==0x0)&&(P3_6==0x0))t=0xA;
if((P0_2==0x0)&&(P3_7==0x0))t=0xB;

if((P0_3==0x0)&&(P3_4==0x0))t=0xC;
if((P0_3==0x0)&&(P3_5==0x0))t=0xD;
if((P0_3==0x0)&&(P3_6==0x0))t=0xE;
if((P0_3==0x0)&&(P3_7==0x0))t=0xF;

if((P0_4==0x0)&&(P3_4==0x0))t=0x10;
if((P0_4==0x0)&&(P3_5==0x0))t=0x11;
if((P0_4==0x0)&&(P3_6==0x0))t=0x12;
if((P0_4==0x0)&&(P3_7==0x0))t=0x13;



if(t<255)
{
P_OUT=t^0xFF;
if(t<10){SBUF=t+0x30;}else{SBUF=t+0x37;}
for(i=0;i<0xffff;i++);
}
TR0=1;
}

void init_UART(void)
{
//SCON=0x50; ///*register of special functions (Control of serial interface mode used)*/
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
if(RI)RI=0;
if(TI)TI=0;
}
