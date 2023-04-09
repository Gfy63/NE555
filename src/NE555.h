/***********************************
 * @file NE555.h
 * @author Gfy63 (mrgoofy@gmx.net)
 * @brief Simulate the NE555 timer chip. The state change every elapse interval time.
 *          This can be use for the blink function, without stopping the program on Delay().
 * @version 0.9.0
 * @date 2023-04-09
 * 
 * GPLv2 Licence https://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
 * 
 * @copyright 2023
 **********************************/

#ifndef NE555_h
#define NE555_h

#include <Arduino.h>

class NE555
{
    protected:
        typedef void( *CallbackFunction)(boolean state);

    public:
        /**
         * @brief   Constructors.
         * @param   highTimer   Interval time for HIGH state in millis.
         * @param   lowTimer    Interval time for LOW state in millis. (optional)
         * @param   cb          Callback function for state change. Format: void cb( boolean state ); (optional)
         */
        NE555( unsigned long highTimer );
        NE555( unsigned long highTimer, CallbackFunction cb );
        NE555( unsigned long highTimer, unsigned long lowTimer );
        NE555( unsigned long highTimer, unsigned long lowTimer, CallbackFunction cb );

        /**
         * @brief   Inspect if the NE555 time is expiered.
         * @return  True if the state has changed.
         */
        bool inspect( void );

        /**
         * @brief   Restart the timer. First inspect() will fire the callback function with state is true.
         * @param   highTimer   Interval time for HIGH state in millis. (optional)
         * @param   lowTimer    Interval time for LOW state in millis. (optional)
         */
        void restart( void );
        void restart( unsigned long highTimer );
        void restart( unsigned long highTimer, unsigned long lowTimer );


        /**
         * @brief   Delay mode. Run only one time.
         * @param   lowTimer     Delay in millis.
         */
        void delay( unsigned long lowTimer );
       
        /**
         * @brief   Get OR set the enable.
         * @param   enable  Set the enable.
         *  OR
         * @return  Get the enable.
         */
        void enable( boolean enable );
        boolean enable( void );
        
        /**
         * @brief   Set OR get the state.
         * @param   state   Set the state.
         *  OR
         * @return  Get the state. (true/false)
         */
        void state( boolean state );
        bool state( void );

    private:
        CallbackFunction _stateChange_cb = NULL;
        boolean _enable = false;        // If true, NE555 is running.
        boolean _state = false;         // State.
        unsigned long _intervalH;       // Interval time for hight state.
        unsigned long _intervalL;       // Interval time for low state.

        // --- Intern only ---
        unsigned long _current;         // Current time.
        unsigned long _previouse;       // Previouse time.
        unsigned long _expiered=0;      // Expiered time.

        enum { MODE_PULSE=0, MODE_DELAY };
        int _mode = MODE_PULSE;         // Mode.

        /***
         * @brief   Set all parameter for restart.
        */
        void SetupRestart( void );
};

#endif

// End of 'NE555.h'