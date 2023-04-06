#include <Arduino.h>
#include <NE555.h>

#define pinBlink	13
#define pinEnable   8

void BlinkCB( boolean state );

NE555 blink( 1000, BlinkCB );

int enable=1;		// PULLUP

void setup() {
	// put your setup code here, to run once:

	pinMode( pinBlink, OUTPUT );

	pinMode( pinEnable, INPUT_PULLUP );

	delay(3000);

	blink.restart();		// Start blinking.
}

void loop() {
	// put your main code here, to run repeatedly:

	if( digitalRead( pinEnable ) != enable )
	{
		enable = !enable;
		blink.enable( enable );
	
		delay( 50 );    // Debounce
	}

	blink.inspect();
}

void BlinkCB( boolean state )
{
	digitalWrite( pinBlink, state );
}