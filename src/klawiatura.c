#include <avr/io.h>
#include <avr/interrupt.h>
#include "../inc/klawiatura.h"
#include "../inc/menu.h"


void klawiatura_init(void)
{

  COLUMN_DDR |= COLUMN_MASK;
  COLUMN_PORT &=~ COLUMN_MASK;

  ROW_DDR    &=~ ROW_MASK;
  ROW_PORT   |= ROW_MASK;


	TCCR0A |=(1<<WGM01);	//tryb ctc
	TCCR0B |= (1<<CS00) | (1<<CS02);	//preskaler 1024
	OCR0A = 38;		//dodatkowy podzia� przez 38
  TIMSK0 |=(1<<OCIE0A);
  //TIMSK0 |= (1<<OCIE0A);	//zezwolenie na przerwania od porownania z rejestrem OCR0A

}


void obsluga_przyciskow(){
  if(p_1==1)
  {
    while(p_1);
    p_1=1;
    flaga_menu=1;
  }
  if(p_2==1)
  {
    while(p_2);
    p_2=1;
    flaga_menu=1;
  }
  if(p_3==1)
  {
    while(p_3);
    p_3=1;
    flaga_menu=1;
  }
  if(p_4==1)
  {
    while(p_4);
    p_4=1;
    flaga_menu=1;
  }
  if(p_5==1)
  {
    while(p_5);
    p_5=1;
    flaga_menu=1;
  }
  if(p_6==1)
  {
    while(p_6);
    p_6=1;
    flaga_menu=1;
  }
  if(p_7==1)
  {
    while(p_7);
    p_7=1;
    flaga_menu=1;
  }
  if(p_8==1)
  {
    while(p_8);
    p_8=1;
    flaga_menu=1;
  }
  if(p_9==1)
  {
    while(p_9);
    p_9=1;
    flaga_menu=1;
  }
  if(p_0==1)
  {
    while(p_0);
    p_0=1;
    flaga_menu=1;
  }
  if(p_A==1)
  {
    while(p_A);
    p_A=1;
    flaga_menu=1;
  }
  if(p_B==1)
  {
    while(p_B);
    p_B=1;
    flaga_menu=1;
  }
  if(p_C==1)
  {
    while(p_C);
    p_C=1;
    flaga_menu=1;
  }
  if(p_D==1)
  {
    while(p_D);
    p_D=1;
    flaga_menu=1;
  }
  if(p_star==1)
  {
    while(p_star);
    p_star=1;
    flaga_menu=1;
  }
  if(p_hash==1)
  {
    while(p_hash);
    p_hash=1;
    flaga_menu=1;
  }
}


ISR(TIMER0_COMPA_vect)
{



    COLUMN_PORT = ((COLUMN_PORT & ~COLUMN_MASK) | (COLUMN_MASK & ~(1<<COLUMN_1_PIN)));
    if( !(ROW_PIN & (1<<ROW_1_PIN)) ) p_star=1;
    else p_star=0;
    if( !(ROW_PIN & (1<<ROW_2_PIN)) ) p_2=1;
    else p_2=0;
    if( !(ROW_PIN & (1<<ROW_3_PIN)) ) p_3=1;
    else p_3=0;
    if( !(ROW_PIN & (1<<ROW_4_PIN)) ) p_A=1;
    else p_A=0;

    COLUMN_PORT = ((COLUMN_PORT & ~COLUMN_MASK) | (COLUMN_MASK & ~(1<<COLUMN_2_PIN)));
    if( !(ROW_PIN & (1<<ROW_1_PIN)) ) p_1=1;
    else p_1=0;
    if( !(ROW_PIN & (1<<ROW_2_PIN)) ) p_5=1;
    else p_5=0;
    if( !(ROW_PIN & (1<<ROW_3_PIN)) ) p_6=1;
    else p_6=0;
    if( !(ROW_PIN & (1<<ROW_4_PIN)) ) p_B=1;
    else p_B=0;

    COLUMN_PORT = ((COLUMN_PORT & ~COLUMN_MASK) | (COLUMN_MASK & ~(1<<COLUMN_3_PIN)));
    if( !(ROW_PIN & (1<<ROW_1_PIN)) ) p_4=1;
    else p_4=0;
    if( !(ROW_PIN & (1<<ROW_2_PIN)) ) p_8=1;
    else p_8=0;
    if( !(ROW_PIN & (1<<ROW_3_PIN)) ) p_9=1;
    else p_9=0;
    if( !(ROW_PIN & (1<<ROW_4_PIN)) ) p_C=1;
    else p_C=0;

    COLUMN_PORT = ((COLUMN_PORT & ~COLUMN_MASK) | (COLUMN_MASK & ~(1<<COLUMN_4_PIN) ));
    if( !(ROW_PIN & (1<<ROW_1_PIN)) ) p_7=1;
    else p_7=0;
    if( !(ROW_PIN & (1<<ROW_2_PIN)) ) p_0=1;
    else p_0=0;
    if( !(ROW_PIN & (1<<ROW_3_PIN)) ) p_hash=1;
    else p_hash=0;
    if( !(ROW_PIN & (1<<ROW_4_PIN)) ) p_D=1;
    else p_D=0;

}
