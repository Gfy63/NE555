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

NE555::NE555( unsigned long interval )
{
    _intervalH = interval;
    _intervalL = interval;
}

NE555::NE555( unsigned long intervalHight, unsigned long intervalLow )
{
    _intervalH = intervalHight;
    _intervalL = intervalLow;
}

NE555::NE555( unsigned long interval, CallbackFunction cb )
{
    _intervalH = interval;
    _intervalL = interval;
    _stateChange_cb = cb;
}

NE555::NE555( unsigned long intervalHight, unsigned long intervalLow, CallbackFunction cb )
{
    _intervalH = intervalHight;
    _intervalL = intervalLow;
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
    _state = false;
    _enable = true;
    _previouse = millis() - _intervalL;      // Provoke a Callback fire next inspect().
    _expiered = 0;

} // restart()

void NE555::delay( unsigned long t )
{
    _intervalL = t;     // Start with low!

    _mode = MODE_DELAY;
    _state = false;
    _enable = true;
    _previouse = millis();
    _expiered = 0;

} // delay()

void NE555::interval( unsigned long invl )
{ 
    _intervalH = invl;
    _intervalL = invl;
} // interval()

void NE555::intervalH( unsigned long invl ) { _intervalH = invl; }
unsigned long NE555::intervalH( void ) { return _intervalH; }

void NE555::intervalL( unsigned long invl ) { _intervalL = invl; }
unsigned long NE555::intervalL( void ) { return _intervalL; }

void NE555::enable( boolean enb ) 
{
    _enable = enb;

    if( _enable )
    {
        // Start timer.
        _previouse = millis();
    }
    else
    {
        _expiered = millis() - _previouse;
    }
} // enable()

bool NE555::enable( void ){ return _enable; }

void NE555::state( boolean st ) { _state = st; }
bool NE555::state( void ) { return _state; }