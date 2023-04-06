#include <Arduino.h>
#include "NE555.h"

#define pinDelay	13
#define pinEnable   8

void DelayCB( boolean state );

NE555 delay2( 1000, DelayCB );

int enable=true;		// PULLUP

void setup() {
	// put your setup code here, to run once:
	pinMode( pinDelay, OUTPUT );
	pinMode( pinEnable, INPUT_PULLUP );

	delay(3000);
}

void loop() {
	// put your main code here, to run repeatedly:

	if( digitalRead( pinEnable ) != enable )
	{
		enable = !enable;
		delay( 50 );    // Debounce

		if( !enable )
		{
			digitalWrite( pinDelay, LOW );
			delay2.delay( 3000 );
		}
	}

	delay2.inspect();
}

void DelayCB( boolean state )
{
	Serial.println( "Delay" );
	digitalWrite( pinDelay, state );
}