// Buzzer as output on pin PB0;
// LDR as external interrupt on pin PB1
// Button as input_pullup on pin PB2;

#include <avr/interrupt.h>
#include <avr/sleep.h>

#define PRR _SFR_IO8(0x25) // Equivalent to 'power_all_disable();' on attiny85
#define PRADC 0
#define PRTIM0 1
#define BODCR _SFR_IO8(0x30) // Closing the BOD CONTROL Register
#define BPDSE 0
#define BPDS 1

bool B; // Stores button status

ISR(PCINT0_vect){ // Interrupt handling
  PORTB |= (1 << PB0); // Buzzing, PB0 = 1
  while(B){ // Until button is pressed
    B = PINB & 0b00000100; // Implements digitalRead(2) with port manipulation
  }
  B = 1; // Button was pressed
  PORTB &= ~(1 << PB0); // Stop buzzing, PB0 = 0
}

void setup () {
  cli(); // Disable interrupts for setup
  PCMSK |= (1 << PCINT1); // Enable Pin PB1 Change Interrupts
  GIMSK |= (1 << PCIE); // Use PB0 as interrupt pin
  ADCSRA &= ~_BV(ADEN); // ADC off for lower power consumption
  ACSR |= _BV(ACD);         // Disable analog comparator
  DIDR0 |= (1<< AIN1D)|(1 << AIN0D);// Disable analog input buffers
  DDRB = 0b00000001; // The following two lines set PB0 as OUTPUT and PBB2 as INPUT_PULLUP
  PORTB = 0b00000100;
  B = 1;
  sei(); // Enable interrupts
}

void loop() {
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_cpu();
}
