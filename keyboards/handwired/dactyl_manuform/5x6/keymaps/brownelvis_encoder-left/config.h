/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once


#define USE_SERIAL

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS
// Rows are doubled-up

// wiring of the encoder (left side)
#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTION 4

// wiring of the encoder (right side)
//#define ENCODERS_PAD_A { D1 } // dummy encoder to passs error. there is no left encoder.
//#define ENCODERS_PAD_B { D0 } // dummy encoder to passs error. there is no left encoder.
//#define ENCODERS_PAD_A_RIGHT { F4 }
//#define ENCODERS_PAD_B_RIGHT { F5 }
//#define ENCODER_RESOLUTION 4

