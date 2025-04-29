Note: use the following commands to compile this program for the ATMEGA328P on the Arduino Uno.
avr-gcc -Wall -Os -DF_CPU=16000000 -mmcu=atmega328p -o main.elf main.c
avr-objcopy -j .text -j .data -O ihex main.elf main.hex
avrdude -c Arduino -b 115200 -P COMx -p atmega328p -U flash:w:main.hex:i

Note: in the final command, you must change COMx to the proper COM port shown in device manager.
