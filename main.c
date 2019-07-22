#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "inc/lcd44780.h"
#include "inc/klawiatura.h"
#include "inc/menu.h"
#include "inc/mfrc522_cmd.h"
#include "inc/mfrc522_reg.h"
#include "inc/mfrc522.h"
#include "inc/rs232.h"
#include "inc/spi.h"
#include "inc/spi_config.h"

void cyfry(void);
uint8_t haslo[4];
uint8_t cyfra_haslo;


int main(void)
{

  sei();

  USART_Init( __UBRR );
  lcd_init();
  klawiatura_init();

  spi_init();
  _delay_ms(1000);
  //LCDClear();
  mfrc522_reset();
  //init reader
  mfrc522_init();


	uint8_t byte;
  uint8_t str[10];
  //check version of the reader
  byte = mfrc522_read(VersionReg);
  if(byte == 0x92)
  {
  //  uart_puts_Trans("MIFARE RC522v2"); USART_Transmit( '\n' ); USART_Transmit( '\r' );
  //  uart_puts_Trans("Detected"); USART_Transmit( '\n' ); USART_Transmit( '\r' );

  }else if(byte == 0x91 || byte==0x90)
  {
  //  uart_puts_Trans("MIFARE RC522v1"); USART_Transmit( '\n' ); USART_Transmit( '\r' );
  //  uart_puts_Trans("Detected"); USART_Transmit( '\n' ); USART_Transmit( '\r' );
  }else
  {
  //  uart_puts_Trans("No reader found"); USART_Transmit( '\n' ); USART_Transmit( '\r' );
  }

  byte = mfrc522_read(ComIEnReg);
  mfrc522_write(ComIEnReg,byte|0x20);
  byte = mfrc522_read(DivIEnReg);
  mfrc522_write(DivIEnReg,byte|0x80);

  DDRC |=(1<<PC5);
  PORTC &=~(1<<PC5);

  uint8_t poz_uzytkownik=0;
  pokaz_menu_1(poz_uzytkownik);

  enum menu{LOG, PAS};
  uint8_t menu_state=LOG;

  uint8_t dane;
  //uart_puts_Trans("Przed while\n\r");

  while (1) {

    obsluga_przyciskow();

    if(flaga_menu==1)
    {

      switch (menu_state) {
        case LOG:
          if(p_A==1)
          {
            poz_uzytkownik++;
            pokaz_menu_1(poz_uzytkownik);
          }
          if(p_B==1)
          {
            poz_uzytkownik--;
            pokaz_menu_1(poz_uzytkownik);
          }
          if(p_C==1)
          {
            pokaz_menu_2(0);
            menu_state = PAS;
            pokaz_menu_2(0);
            cyfra_haslo=0;
          }
          break;

        case PAS:
          if(p_C)
          {
            menu_state = LOG;
            pokaz_menu_1(poz_uzytkownik);
          }
          cyfry();
          cyfra_haslo++;
          pokaz_menu_2(cyfra_haslo);

          if(cyfra_haslo == 4)  //wyslij haslo i login
          {
            USART_Transmit( 1 );    //wysylanie start
            USART_Transmit( poz_uzytkownik );    //id usera
            for(int i=0; i<cyfra_haslo;i++)
            {
              lcd_int(haslo[i]);
              USART_Transmit( haslo[i] );
              //uart_puts_Trans("cos\n\r");
            }

      			while( ! (dane = uart_getc()) );	//czekaj dopoki nie bedzie danych
            if( dane == 1)
            {
              lcd_cls();
              lcd_locate(0, 0);
              lcd_str("Wchodzisz!");
              PORTC |=(1<<PC5);
              _delay_ms(2000);
              PORTC &=~(1<<PC5);

            }
            else
            {
              lcd_cls();
              lcd_locate(0, 0);
              lcd_str("Brak dostepu!");
              _delay_ms(2000);
            }
            pokaz_menu_1(poz_uzytkownik);
            cyfra_haslo=0;
            menu_state = LOG;
          }
          break;
      }
      flaga_menu = 0;
    }

    byte = mfrc522_request(PICC_REQALL,str);

    if(byte == CARD_FOUND)
    {
      *str = "";
      byte = mfrc522_get_card_serial(str);			//tablica str zawiera bajty z karty
      if(byte == CARD _FOUND)
      {

        USART_Transmit( 2 );        //wejscie za pomoca karty
        for(byte=0; byte< 5; byte++)
        {
          USART_Transmit( str[byte] );
        }

        while( ! (dane = uart_getc()) );
        if( dane == 1 )
        {
          lcd_cls();
          lcd_locate(0, 0);
          lcd_str("Wchodzisz!");
          PORTC |=(1<<PC5);
          _delay_ms(2000);
          PORTC &=~(1<<PC5);
        }
        else
        {
          lcd_cls();
          lcd_locate(0, 0);
          lcd_str("Brak dostepu!");
          _delay_ms(2000);
        }
        pokaz_menu_1(poz_uzytkownik);
        cyfra_haslo=0;
        menu_state = LOG;
      }
      else
      {
        for(byte=0; byte< 5; byte++)
          USART_Transmit( 0 );
      }
    }
  }
}


/////////////////////////////////////////////////////////////////









void cyfry(void)
{
  if(p_1==1)
  {
    haslo[cyfra_haslo]=1;
  }
  if(p_2==1)
  {
    haslo[cyfra_haslo]=2;
  }
  if(p_3==1)
  {
    haslo[cyfra_haslo]=3;
  }
  if(p_4==1)
  {
    haslo[cyfra_haslo]=4;
  }
  if(p_5==1)
  {
    haslo[cyfra_haslo]=5;
  }
  if(p_6==1)
  {
    haslo[cyfra_haslo]=6;
  }
  if(p_7==1)
  {
    haslo[cyfra_haslo]=7;
  }
  if(p_8==1)
  {
    haslo[cyfra_haslo]=8;
  }
  if(p_9==1)
  {
    haslo[cyfra_haslo]=9;
  }
  if(p_0==1)
  {
    haslo[cyfra_haslo]=0;
  }
}
