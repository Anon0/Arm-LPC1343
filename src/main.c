//
// Test program for the Olimex LPC_P1343 board.
//
// There are 8 LEDs on this board and this program will simply count up in binary on them with
// a half second delay between each count.
//
// The program is slightly more complex because 4 of the LEDs are on port 2 and 4 on port 3.
// See the schematic http://olimex.com/dev/pdf/ARM/LPC/LPC-P1343-schematic.pdf
//
// To get the program onto the board, set the jumper on the board and reboot. It should then appear as
// a mass storage drive on a PC, (Assume drive E: for this)
//
// After compiling to olddemo.afx you need to run the following commands assuming the PATH is set up
//
// arm-none-eabi-objcopy.exe -O binary olidemo.axf firmware.bin
// checksum.exe firmware.bin
//
// Then simply delete the existing firmware.bin from the drive and copy firmware.bin to it and reset the board
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LPC13xx.h"

extern void led_init( void );
extern void led_on( int led );
extern void led_blip( int led, int ms );
//
// Number of millisecond timer ticks so far
//
volatile int msTicks = 0;

//
// Interrupt handler for 1ms system timer
//
void SysTick_Handler()
{
	msTicks++;
}

//
// Simple function to wait 'X' millseconds before it returns
//
void wait_ms(int ms)
{
	int target = msTicks + ms;
	while(msTicks < target); /* Busy wait for time to reach desired time */
}

uint8_t getBtn1State()
{
  // Read the current state of all pins in GPIO block 0
  int pinBlockState = LPC_GPIO2->DATA;

  // Read the value of 'pinNumber'
  int pinState = (pinBlockState & (1 << 9)) ? 1 : 0;

  // Return the value of pinState
  return pinState;
}

uint8_t getBtn2State()
{
  // Read the current state of all pins in GPIO block 0
  int pinBlockState = LPC_GPIO2->DATA;

  // Read the value of 'pinNumber'
  int pinState = (pinBlockState & (1 << 10)) ? 1 : 0;

  // Return the value of pinState
  return pinState;
}

int main()
{
	SystemInit();

	// Set the system timer to 1ms counts
	SysTick_Config(SystemCoreClock / 1000);

	led_init();

	while(1)
	{
		int i;
		for( i = 0; i < 4; i++){
			led_on( i );
			led_on( (7-i) );
			wait_ms( 150 );
			led_off( i );
			led_off( (7-i) );
		}
		for( i = 2; i > 0; i--){
			led_on( i );
			led_on( (7-i) );
			wait_ms( 150 );
			led_off( i );
			led_off( (7-i) );
		}
	}
}
