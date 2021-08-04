/*SERIAL4_PROTOCOL = 9;		//Rangefinder
SERIAL4_BAUD = 115;			//Serial 4 Baud Rate 115200
RNGFND1_TYPE = 20;			//Rangefinder is Rangefinder
RNGFND1_MIN_CM = 10;		//Rangefinder minimum distance 10 [cm]
RNGFND1_MAX_CM = 300;		//Rangefinder maximum distance 300 [cm]
RNGFND1_GNDCLEAR = 10;		//Distance from the range finder to the ground [cm]
*/


#include <stdint.h>
#include "pru_ctrl.h"

volatile register uint32_t __R30;
volatile register uint32_t __R31;

// Trigger pin
#define TRIGGER 1<<14

// Echo pin
#define ECHO 1<<14

#define TICKS_PER_US 200
#define TICKS_PER_MS (1000 * TICKS_PER_US)

#define TICKS_PER_CM 11600

#define COUNTER_MIN_DISTANCE (2 * TICKS_PER_CM)
#define COUNTER_MAX_DISTANCE (400 * TICKS_PER_CM)

enum RangeFinder_Status {
        RangeFinder_NotConnected = 0,
        RangeFinder_NoData,
        RangeFinder_OutOfRangeLow,
        RangeFinder_OutOfRangeHigh,
        RangeFinder_Good
};

struct range {
    uint32_t distance;
    uint32_t status;
};

#pragma LOCATION(ranger, 0x0)
volatile struct range ranger;

main() {
    // Init data
    ranger.distance = 0;
    ranger.status = RangeFinder_NoData;

    // Reset trigger
    __R30 &= ~(TRIGGER);

    // Wait 100ms
    __delay_cycles(250 * TICKS_PER_MS);

    // Disable counter
    PRU0_CTRL.CONTROL_bit.CTR_EN = 0;

    // Clear counter
    PRU0_CTRL.CYCLE_bit.CYCLECOUNT = 0xFFFFFFFF;

    while(1) {
        // Enable trigger
        __R30 |= TRIGGER;

        // Wait 15us
        __delay_cycles(3000);

        // Reset trigger
        __R30 &= ~(TRIGGER);

        // Wait for echo
        while((__R31 & ECHO) == 0) {
            if(PRU0_CTRL.CYCLE_bit.CYCLECOUNT > (600 * TICKS_PER_CM)) {
                ranger.status = RangeFinder_NoData;
            }
        }

        // Start counter
        PRU0_CTRL.CONTROL_bit.CTR_EN = 1;

        // Count echo length
        while(__R31 & ECHO) {
            ;
        }

        // Stop counter
        PRU0_CTRL.CONTROL_bit.CTR_EN = 0;

        // Check status
        if(PRU0_CTRL.CYCLE_bit.CYCLECOUNT < COUNTER_MIN_DISTANCE) {
            ranger.distance = 0;

            // Set status out of range low
            ranger.status = RangeFinder_OutOfRangeLow;
        }
        else if(PRU0_CTRL.CYCLE_bit.CYCLECOUNT > COUNTER_MAX_DISTANCE) {
            ranger.distance = 0;

            // Set stauts
            ranger.status = RangeFinder_OutOfRangeHigh;
        }
        else {
            // Calculate distance in cm
            ranger.distance = PRU0_CTRL.CYCLE_bit.CYCLECOUNT / TICKS_PER_CM;

            //  Set status out of range high
            ranger.status = RangeFinder_Good;
        }

        // Clear counter
        PRU0_CTRL.CYCLE_bit.CYCLECOUNT = 0xFFFFFFFF;

        // Wait 20ms
        __delay_cycles(20 * TICKS_PER_MS);
    }
}