/***********************************
 * @file NE555.cpp
 * @author Gfy63 (mrgoofy@gmx.net)
 * 
 * GPLv2 Licence https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
 * 
 * @copyright 2023
 **********************************/

#include "NE555.h"

/**
 * --- PUBLIC FUNCTIONS ---
*/

NE555::NE555( unsigned long highTimer )
{
    _intervalH = _intervalL = highTimer;
}

NE555::NE555( unsigned long highTimer, unsigned long lowTimer )
{
    _intervalH = highTimer;
    _intervalL = lowTimer;
}

NE555::NE555( unsigned long highTimer, CallbackFunction cb )
{
    _intervalH = _intervalL = highTimer;
    _stateChange_cb = cb;
}

NE555::NE555( unsigned long highTimer, unsigned long lowTimer, CallbackFunction cb )
{
    _intervalH = highTimer;
    _intervalL = lowTimer;
    _stateChange_cb = cb;
}

bool NE555::inspect( void )
{
    boolean ret = false;
    unsigned long invl = (_state) ? _intervalH : _intervalL;

    if( !_enable ) return ret;

    _current = millis();

	if( _current - _previouse >= invl - _expiered )
	{
        // Time elapse.
		_previouse = _current;
        _expiered = 0;
        _state = !_state;

        if( _stateChange_cb != NULL ) _stateChange_cb( _state );

        ret = true;

        if( _mode == MODE_DELAY ) _enable = false;       // One shot.
	}
    
    return ret;

} // inspect()

void NE555::restart( void )
{
    _mode = MODE_PULSE;

    SetupRestart();

} // restart()

void NE555::restart( unsigned long highTimer )
{
    _intervalH = _intervalL = highTimer;

    _mode = MODE_PULSE;

    SetupRestart();

} // restart()

void NE555::restart( unsigned long highTimer, unsigned long lowTimer )
{
    _intervalH = highTimer;
    _intervalL = lowTimer;

    _mode = MODE_PULSE;

    SetupRestart();

} // restart()

void NE555::delay( unsigned long lowTimer )
{
    _intervalL = lowTimer;     // Start with low!

    _mode = MODE_DELAY;

    SetupRestart();

} // delay()

void NE555::enable( boolean enable ) 
{
    _enable = enable;

    if( _enable )
    {
        // True. Timer start.
        _previouse = millis();      // Set start time.
    }
    else
    {
        // False. Timer freeze.
        _expiered = millis() - _previouse;      // Save elapsed time.
    }
    
} // enable()

bool NE555::enable( void ) { return _enable; }

void NE555::state( boolean state ) { _state = state; }
bool NE555::state( void ) { return _state; }

/**
 * --- PRIVATE FUNCTIONS ---
*/
void NE555::SetupRestart( void )
{
    _state = false;
    _enable = true;
    _previouse = millis();
    if( _mode == MODE_PULSE ) _previouse -= _intervalL;      // Provoke a callback fire next inspect().

    _expiered = 0;

} // SetupRestart()

// End of 'NE555.cpp'