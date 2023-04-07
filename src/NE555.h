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
         * @param   highTimer   Interval time for HIGH state in millis.
         * @param   lowTimer    Interval time for LOW state in millis. (optional: Use 'invlHigh' if not used)
         * @param   cb          Callback function for state change. Format: void cb( boolean state ); (optional)
         *                      
         */
        NE555( unsigned long highTimer );
        NE555( unsigned long highTimer, CallbackFunction cb );

        NE555( unsigned long highTimer, unsigned long lowTimer );
        NE555( unsigned long highTimer, unsigned long lowTimer, CallbackFunction cb );

        /**
         * @brief   Inspect if the NE555 time is expiered.
         * 
         * @return  True if the state has changed.
         */
        bool inspect( void );

        /**
         * @brief   Restart the timer. First inspect() will fire the callback function with state is true.
         * 
         * @param   highTimer    Interval time for HIGH state in millis. (optional: Use old value)
         * @param   lowTimer    Interval time for LOW state in millis. (optional: Use 'invlHigh' if not used)
         */
        void restart( void );
        void restart( unsigned long highTimer );
        void restart( unsigned long highTimer, unsigned long lowTimer );

        /**
         * @brief   Delay mode. Run only one time.
         * 
         * @param   lowTimer     Delay in millis.
         */
        void delay( unsigned long lowTimer );

        // /**
        //  * @brief   Set the interval time for hight and low state.
        //  * 
        //  * @param   invl    Time in millis.
        //  */
        // void interval( unsigned long invl );

        // /**
        //  * @brief   Set the interval time for hight state.
        //  * 
        //  * @param   invl    Time in millis.
        //  * 
        //  * @return  Time in millis.
        //  */
        // void intervalH( unsigned long invl );
        // unsigned long intervalH( void );

        // /**
        //  * @brief   Set the interval time for low state.
        //  * 
        //  * @param   invl    Time in millis.
        //  * 
        //  * @return  Time in millis.
        //  */
        // void intervalL( unsigned long invl );
        // unsigned long intervalL( void );
       
        /**
         * @brief   Get OR set the enable.
         * 
         * @param   enable  Set the enable.
         * @return  Get the enable.
         */
        void enable( boolean enable );
        boolean enable( void );
        
        /**
         * @brief   Set OR get the state.
         * 
         * @param   state   Set the state.
         * 
         * @return  Get the state. (true/false)
         */
        void state( boolean state );
        bool state( void );

      
    private:
        void SetupRestart( void );

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
