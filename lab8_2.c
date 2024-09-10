#include "my_adc_lib.h"
#include "my_uart_lib.h"
#include "i2c.h"
#include "SSD1306.h"
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#define BUFFER_SIZE 6
#define TOO_HOT 80

int main(void)
{
    DDRD = 1<<DDD6;// Output
    PORTD = 1<<PORTD3; // Input
    unsigned int digValue;
    double analogVal, celsius, fahr;
    OLED_Init(); 
    adc_init();
    char buffer1[BUFFER_SIZE];
    
  while (1)
  {
    //ADC conversion to celsius and fahrenheit
    digValue = get_adc();
    analogVal = digValue * V_REF / 1023;
    celsius = ((analogVal -0.75)* 100.0) + 25.0;
    fahr = celsius * 9.0/5.0 + 32.0;
    if (fahr > TOO_HOT){ // Turns LED on if temperature exceeds TOO_HOT value
        PORTD |= (1<<PORTD6);
    } else {
        PORTD &= ~(1<<PORTD6);
    }
    if ((PIND & (1<<PIND3)) == 0){ // Changes screen to display in C if button is pressed
        dtostrf(celsius, 5, 1, buffer1);
        strncat(buffer1, "C", 2);
    } else { // Displays temperature in F if no button is pressed
        dtostrf(fahr, 5, 1, buffer1);
        strncat(buffer1, "F", 2);
    }
    // Sends string to terminal
    send_string(buffer1);
    uart_send(13);
    uart_send(10);

    // Displays string on OLED display
    OLED_GoToLine(4);
    OLED_DisplayString(buffer1);
    _delay_ms(100);
    
  }
}