#include <avr/io.h>
#include <stdlib.h>
#include "../inc/lcd44780.h"

char uzytkownik[5][10] = {
  {"Mikolaj"},
  {"Krzysztof"},
  {"Wojciech"},
  };

void pokaz_menu_1(int nr)
{
  lcd_cls();
  lcd_locate(0, 0);
  lcd_str("Wybierz login:");
  lcd_locate(1, 0);
  lcd_str(uzytkownik[nr]);
}

void pokaz_menu_2(int nr)
{
  lcd_cls();
  lcd_locate(0, 0);
  lcd_str("Podaj haslo:");
  lcd_locate(1, 0);
  for(int i=0;i<nr;i++)
    lcd_str("*");
}
