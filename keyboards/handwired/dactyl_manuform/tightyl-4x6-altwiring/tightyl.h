#pragma once

#include "dactyl_manuform.h"
#include "quantum.h"

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

#define LAYOUT(\
    L00, L01, L02, L03, L04, L05,                    R00, R01, R02, R03, R04, R05, \
    L10, L11, L12, L13, L14, L15,                    R10, R11, R12, R13, R14, R15, \
    L20, L21, L22, L23, L24, L25,                    R20, R21, R22, R23, R24, R25, \
         L32, L33, L31, L34, L35,                    R30, R31, R34, R32, R33       \
    ) \
    { \
        { L00,   L01,   L02, L03, L04, L05 }, \
        { L10,   L11,   L12, L13, L14, L15 }, \
        { L20,   L21,   L22, L23, L24, L25 }, \
        { KC_NO, L31,   L32, L33, L34, L35 }, \
\
        { R00, R01, R02, R03, R04,   R05    }, \
        { R10, R11, R12, R13, R14,   R15    }, \
        { R20, R21, R22, R23, R24,   R25    }, \
        { R30, R31, R32, R33, R34,   KC_NO  } \
\
   }