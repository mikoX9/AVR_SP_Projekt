

#	CC=xyz	->definiowanie zmiennej
#	$(CC)	->uzywanie zmiennej

MCU = atmega328p
MCU_ = m328p
F_CPU = 8000000

FILE1 		= lcd44780
LOCATION1 	= src

FILE2 		= klawiatura
LOCATION2 	= src

FILE3 		= menu
LOCATION3 	= src

FILE4 		= mfrc522
LOCATION4 	= src

FILE5 		= rs232
LOCATION5 	= src

FILE6 		= spi
LOCATION6 	= src


all:	main.hex
	rm -f main.o
	rm -f main.elf
	rm -f $(FILE1).o
	rm -f $(FILE2).o
	rm -f $(FILE3).o
	rm -f $(FILE4).o
	rm -f $(FILE5).o
	rm -f $(FILE6).o
	avrdude -p $(MCU_) -c usbasp -e -U flash:w:main.hex

.c.o:
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -c -mmcu=$(MCU) $(LOCATION6)/$(FILE6).c -o $(FILE6).o
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -c -mmcu=$(MCU) $(LOCATION5)/$(FILE5).c -o $(FILE5).o
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -c -mmcu=$(MCU) $(LOCATION4)/$(FILE4).c -o $(FILE4).o
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -c -mmcu=$(MCU) $(LOCATION3)/$(FILE3).c -o $(FILE3).o
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -c -mmcu=$(MCU) $(LOCATION2)/$(FILE2).c -o $(FILE2).o
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -c -mmcu=$(MCU) $(LOCATION1)/$(FILE1).c -o $(FILE1).o
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -c -mmcu=$(MCU) main.c -o main.o

main.elf: main.o $(FILE1).o $(FILE2).o $(FILE3).o $(FILE4).o $(FILE5).o $(FILE6).o
	avr-gcc -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) main.o $(FILE2).o $(FILE1).o $(FILE3).o $(FILE4).o $(FILE5).o $(FILE6).o -o main.elf

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

clean:
	rm -f main.hex
	rm -f main.o
	rm -f main.elf
	rm -f $(FILE1).o
	rm -f $(FILE2).o
	rm -f $(FILE3).o
	rm -f $(FILE4).o
	rm -f $(FILE5).o
	rm -f $(FILE6).o
