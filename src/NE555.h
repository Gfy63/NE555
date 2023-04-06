/***********************************
 * @file NE555.h
 * @author Gfy63 (mrgoofy@gmx.net)
 * @brief Simulate the NE555 timer chip. The state change every elapse interval time.
 *          This can be use for the blink function, without stopping the program on Delay().
 * @version 0.0.1
 * @date 2023-03-30
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
         * 
         * @param   interval    Interval time in millis.
         * @param   cb          State change callback function. (optional)
         *                      Format: void cb( boolean state );
         */
        NE555( unsigned long interval );
        NE555( unsigned long interval, CallbackFunction cb );

        NE555( unsigned long intervalHight, unsigned long intervalLow );
        NE555( unsigned long intervalHight, unsigned long intervalLow, CallbackFunction cb );

        /**
         * @brief   Inspect if the NE555 time is expiered.
         * 
         * @return  True if the state has changed.
         */
        bool inspect( void );

        /**
         * @brief   Restart the timer. First inspect() will fire the callback function with state is true.
         */
        void restart( void );

        /**
         * @brief   Delay mode. Run only one time.
         * 
         * @param   t    Delay in millis.
         */
        void delay( unsigned long t );

        /**
         * @brief   Set the interval time for hight and low state.
         * 
         * @param   invl    Time in millis.
         */
        void interval( unsigned long invl );

        /**
         * @brief   Set the interval time for hight state.
         * 
         * @param   invl    Time in millis.
         * 
         * @return  Time in millis.
         */
        void intervalH( unsigned long invl );
        unsigned long intervalH( void );

        /**
         * @brief   Set the interval time for low state.
         * 
         * @param   invl    Time in millis.
         * 
         * @return  Time in millis.
         */
        void intervalL( unsigned long invl );
        unsigned long intervalL( void );
       
        /**
         * @brief   Get OR set enable.
         * 
         * @param   enb     Set the enable. True will also do a restart().
         * @return  Get the enable.
         */
        void enable( boolean enb );
        boolean enable( void );
        
        /**
         * @brief   Set OR get the state.
         * 
         * @param   st      New state.
         * 
         * @return  true / false
         */
        void state( boolean st );
        bool state( void );

      
    private:

        CallbackFunction _stateChange_cb = NULL;
        boolean _enable = false;        // If true, NE555 is running.
        boolean _state = false;         // State.
        unsigned long _intervalH;       // Interval time for hight state.
        unsigned long _intervalL;       // Interval time for low state.

        // --- Intern only.
        unsigned long _current;         // Current time.
        unsigned long _previouse;       // Previouse time.
        unsigned long _expiered=0;      // Expiered time.

        enum { MODE_PULSE=0, MODE_DELAY };
        int _mode = MODE_PULSE;
};

#endif
