# NE555

Simulation of the function from a NE555 timer chip. ;)

* State change with defined interval time, without stopping the ```loop()``` like ```Delay()```.
* State changes calls a defined callback function it used.
* Enable allow to freeze and resume the timer.
* High and low state timing are independent.

## MODE
### PULSE
Mode pulse can also by flash.

<img src="https://github.com/Gfy63/NE555/blob/main/images/Pulse.png" height="120">

### DELAY
Delay fires the callback function only ones.

<img src="https://github.com/Gfy63/NE555/blob/main/images/Delay.png" height="120">

## INSTALLATION & DOWNLOAD
Install via the Arduino Library Manager, the PlatformIO Library Manager or download from [github](https://github.com/Gfy63/NE555.git)

## BASIC USAGE

### INSTANTIATE

```cpp
#include <NE555.h>

#define pinBlink 	13

void BlinkCB( boolean state );

NE555 blink( <highTimer>, <lowTimer>, <Callback> );

// Create callback function
void BlinkCB( boolean state )
{
    digitalWrite( pinBlink, state );
}
```

### SETUP

```cpp
blink.restart();            // Restart & enable timer.
```

### LOOP

```cpp
blink.inspect();
```
Inspect the delayed time and change state if expired and call the callback function if used.

The first call of ```inspect()``` fires always the callback function with state by high.

## Constructors
For Pulse (blink and flash) or Delay the constructor are the same.

Construct a blink function. (No callback function used)
```cpp
NE555 blink( 1000 );
```
Construct a flash function. (No callback function used) 
```cpp
NE555 blink( 100, 900 );
```
Construct a blink function with callback function.
```cpp
NE555 blink( 1000, BlinkCB );
```
Construct a flash function with callback function.
```cpp
NE555 blink( 100, 900, BlinkCB );
```

## Setup method
Normally called from within ```setup()``` but can be updated at runtime.

```void enable( boolean enable )``` False freeze the timer and resume with true.

```boolean enable()``` Get the enable.

```void restart()``` Restart the timer. State and enable are set to true and on the next ```inspect()``` the callback function is called. (Timer are unchanged)

```void restart( unsigned long highTimer )``` Restart and change the pulse time. (High and low timer are the same and changed)

```void restart( unsigned long highTimer, unsigned long lowTimer )``` Restart and change the pulse time. (High & low timer are changed)

```void delay( unsigned long lowTimer )``` Start delay. State is false, enable set to true. After the delay time the callback function is call one time.

## Loop method
This is the only method to be call from the loop.
```void inspect()``` check the timer, and if it is expired, the callback function is fired.

## Callback function
After the interval time is elapsed, the callback function is called.

Format: ```void cb( boolean state )```
