#include <Arduino.h>
#include <NE555.h>

#define pinFlash	13

void FlashCB( boolean state );

NE555 flash( 100, 900, FlashCB );

void setup() {
	// put your setup code here, to run once:

	pinMode( pinFlash, OUTPUT );

	delay(3000);

	flash.restart();		// Start flash.
}

void loop() {
	// put your main code here, to run repeatedly:

	flash.inspect();
}

void BlinkCB( boolean state )
{
	digitalWrite( pinFlash, state );
}