#include <AT89C51RB2.h>
//#include <REGX51.H>
#include <intrins.h>

/*---------------------------------*/
#define P_DAT	P0
#define P_STB	P1
unsigned char idata position;
unsigned char idata print_line[5];//кількість розрядів індикатора
/*---------------------------------*/
#define segA	0x80
#define segB	0x04
#define segC	0x08
#define segD	0x10
#define segE	0x20
#define segF	0x40
#define segG	0x02
#define segH	0x01

#define Digit0	segA|segB|segC|segD|segE|segF
#define Digit1	segB|segC
#define Digit2	segA|segB|segD|segE|segG
#define Digit3	segA|segB|segC|segD|segG
#define Digit4	segB|segC|segF|segG
#define Digit5	segA|segC|segD|segF|segG
#define Digit6	segA|segC|segD|segE|segF|segG
#define Digit7	segA|segB|segC
#define Digit8	segA|segB|segC|segD|segE|segF|segG
#define Digit9	segA|segB|segC|segD|segF|segG

unsigned char code segm7[]={Digit0,Digit1,Digit2,Digit3,Digit4,Digit5,Digit6,Digit7,Digit8,Digit9};
/*---------------------------------*/
void init_UART(void);
void init_T0(void);
void delay(unsigned int n);
/*---------------------------------*/
void main(void)
{
init_UART();
init_T0();
print_line[0]=0;
print_line[1]=1;
print_line[2]=2;
print_line[3]=3;
print_line[4]=4;
EA=1;
while(1)
  {
  delay(200);
  }
}
/*---------------------------------*/
void delay(unsigned int n)
{
unsigned int i,j;
for(j=0;j<n;j++)
	for(i=0;i<0x200;i++);
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
  k=SBUF-'0';
  if(k>9)k=9;
  RI=0;
  print_line[0]=print_line[1];
  print_line[1]=print_line[2];
  print_line[2]=print_line[3];
	print_line[3]=print_line[4];
  print_line[4]=k;
  }
if(TI)TI=0;
}
/*---------------------------------*/
void init_T0(void)
{
TMOD=TMOD&0xF0;
TMOD=TMOD|0x01;
TH0=0x00;
ET0=1;
TR0=1;
}
/*---------------------------------*/
void int_T0(void) interrupt 1
{
TH0=0xFC;
TL0=0;
P_STB=0;
P_DAT=segm7[print_line[position]]^0xFF;
P_STB=(1<<position);
position++;
if(position==5)position=0;
}
/*---------------------------------*/
