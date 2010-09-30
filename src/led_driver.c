#include "LPC13xx.h"

extern void wait_ms(int ms);

void led_init( void ){
	// Set Port 2 bits 4,5,6,7 and Port 3 bits 0,1,2,3 to outputs (That is where the 8 leds are)
	LPC_GPIO2->DIR = 0xF0;
	LPC_GPIO3->DIR = 0x0F;

		LPC_GPIO3->DATA = 0x0F;
		LPC_GPIO2->DATA = 0xF0;

#ifdef DBG_TOY
		// For Debugging Purposes
		// Blink One Set, then the other .... 2 Times ~400ms
		int i;
		for( i = 0; i < 2; i++ ){
			LPC_GPIO3->DATA = 0x00;
			wait_ms( 100 );
			LPC_GPIO3->DATA = 0x0F;
			wait_ms( 100 );
			LPC_GPIO2->DATA = 0x00;
			wait_ms( 100 );
			LPC_GPIO2->DATA = 0xF0;
			wait_ms( 100 );
		}
#endif
}

void led_on( int led ){
	if( led < 8 && led > 3 ) 	LPC_GPIO2->DATA &= ~( ( 1 << led ) ) & 0xF0;  /* Turn On  LED */
	if( led < 4 && led > -1 ) 	LPC_GPIO3->DATA &=  ~( 1 << led );  /* Turn On  LED */
}

void led_off( int led ){
	if( led < 8 && led > 3 ) 	LPC_GPIO2->DATA |=  ( ( 1 << led ) ) & 0xF0;  /* Turn On  LED */
	if( led < 4 && led > -1 ) 	LPC_GPIO3->DATA |=  ( 1 << led );  /* Turn On  LED */
}

/*
 * 	Purpose: Twiddle LED On/Off For the Olimex LPC1343 Board
 *
 *	Input: LED #, Millisecond Wait Time
 *	Output: nothing
 *
 */
void led_blip( int led, int ms ){
	led_on( led );
	wait_ms( ms );
	led_off( led );
}
