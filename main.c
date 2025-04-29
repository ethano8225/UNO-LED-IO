/* Author: Ethan O'Connor
 * Date: 2025-04-12
 * ECE 231 Lab 8.1 
 * 
 * This program is for the atmega328p on the Arduino uno, it blinks a red
 * LED at 5Hz when BTN_RED is pressed, blinks a green LED at 5Hz when 
 * BTN_GREEN is pressed, and blinks both LEDs if BTN_RG is pressed. 
 * When more than one or no buttons are pressed, both LEDs are off
 */
 #include <avr/io.h>
 #include <util/delay.h>
 
 // CPU frequency for delay function if its not defined
 #ifndef F_CPU
 #define F_CPU 16000000UL
 #endif
 
 // bit positions for buttons / leds (for cleaner code/to change pins)
 #define BTN_RED    PD2     // button 1 (for red LED)
 #define BTN_GREEN  PD3     // button 2 (for green LED)
 #define BTN_RG   PD4       // button 3 (for both LEDs)
 #define LED_RED    PB0     // red LED output
 #define LED_GREEN  PB1     // green LED output
 
 int main(void) {
     // Config LED pins as pinout & config button pins as input, enable pull-up resistors 
     DDRB |= (1 << LED_RED) | (1 << LED_GREEN);
     DDRD &= ~((1 << BTN_RED) | (1 << BTN_GREEN) | (1 << BTN_RG));
     PORTD |= (1 << BTN_RED) | (1 << BTN_GREEN) | (1 << BTN_RG);
     
     // infinite loop
     while (1) {
         // Read button states, buttons are active when low due to pull-ups
         uint8_t btn_red_state   = !(PIND & (1 << BTN_RED));
         uint8_t btn_green_state = !(PIND & (1 << BTN_GREEN));
         uint8_t btn_rg_state  = !(PIND & (1 << BTN_RG));
         
         // Count how many buttons are pressed
         uint8_t pressedCount = btn_red_state + btn_green_state + btn_rg_state;
         
         // check pressedcount to determine LED behavior
         if (pressedCount == 1) {         // Only if 1 is pressed
             if (btn_red_state) {           // If red button is pressed,...
                 PORTB |= (1 << LED_RED);     // Make LED_RED//PB0 high, LED ON
                 _delay_ms(100);              // wait for 100 ms
                 PORTB &= ~(1 << LED_RED);    // Make LED_RED low, LED OFF
                 _delay_ms(100);              // wait 100 ms
             }
             else if (btn_green_state) {    // If green button is pressed,...
                 PORTB |= (1 << LED_GREEN);   // Make LED_GREEN//PB1 high, LED ON
                 _delay_ms(100);
                 PORTB &= ~(1 << LED_GREEN);  // Make LED_GREEN low, LED OFF
                 _delay_ms(100);
             }
             else if (btn_rg_state) {  // If 2-color button is pressed, blink both LEDs
                 PORTB |= (1 << LED_RED) | (1 << LED_GREEN);  // Make LED_RED&GREEN high, LEDs ON
                 _delay_ms(100);
                 PORTB &= ~((1 << LED_RED) | (1 << LED_GREEN)); // Make PB0//PB1 low, LEDs OFF
                 _delay_ms(100);
             }
         }
         else {                     // no buttons or more than one button pressed:
             PORTB &= ~((1 << LED_RED) | (1 << LED_GREEN)); // make sure both LEDs are off
         }
     }
     return 0; // this return statement should never be reached
 }
 