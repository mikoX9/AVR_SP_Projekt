#ifndef KLAWIATURA_H_
#define KLAWIATURA_H_

#define COLUMN_PORT   PORTB
#define COLUMN_PIN    PINB
#define COLUMN_DDR    DDRB
#define COLUMN_1_PIN  PB7
#define COLUMN_2_PIN  PB6
#define COLUMN_3_PIN  PB1
#define COLUMN_4_PIN  PB0
#define COLUMN_MASK   ( (1<<COLUMN_1_PIN) | (1<<COLUMN_2_PIN) | (1<<COLUMN_3_PIN) | (1<<COLUMN_4_PIN) )

#define ROW_PORT      PORTC
#define ROW_PIN       PINC
#define ROW_DDR       DDRC
#define ROW_1_PIN     PC3
#define ROW_2_PIN     PC2
#define ROW_3_PIN     PC1
#define ROW_4_PIN     PC0
#define ROW_MASK      ( (1<<ROW_1_PIN) | (1<<ROW_2_PIN) | (1<<ROW_3_PIN)  | (1<<ROW_4_PIN) )

void klawiatura_init(void);

//flagi prrzyciskow

volatile uint8_t p_1;
volatile uint8_t p_2;
volatile uint8_t p_3;
volatile uint8_t p_4;
volatile uint8_t p_5;
volatile uint8_t p_6;
volatile uint8_t p_7;
volatile uint8_t p_8;
volatile uint8_t p_9;
volatile uint8_t p_0;

volatile uint8_t p_star;
volatile uint8_t p_hash;
volatile uint8_t p_A;
volatile uint8_t p_B;
volatile uint8_t p_C;
volatile uint8_t p_D;


uint8_t *przycisk;
void obsluga_przyciskow();


#endif
