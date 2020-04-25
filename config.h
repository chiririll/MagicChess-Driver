#ifndef MAGICCHESS_DRIVER_CONFIG_H
#define MAGICCHESS_DRIVER_CONFIG_H

#define DEBUG_MODE

/* Steppers */
// Pins X
#define S_X1 8
#define S_X2 9
#define S_X3 10
#define S_X4 11
// Pins Y
#define S_Y1 4
#define S_Y2 5
#define S_Y3 6
#define S_Y4 7
// Steps per revolution
#define SPR_X 48
#define SPR_Y 48
// Speed
#define SPEED_X 60
#define SPEED_Y 60
// Radius (in mm)
#define X_LEN 28.2743	// Diameter = 9
#define Y_LEN 47.1239	// Diameter = 15
/* ----- */

/* Trailers */
#define trX 13
#define trY 2
/* ----- */

/* Sound */
#define SOUND 3		// Sound pin
#define S_DELAY 100 // Delay between tones (in ms)
/* ----- */

// I2C Address
#define I2C_ADR 2

// Electromagnet pin
#define MAGNET 12

/* Chessboard settings (in mm) */
// Fields {0, 1, 2}
const int X_HOME[3] = {22, 74, 246};
const int Y_HOME[3] = {22, 22, 22};

// Cell width
#define CELL_W 20
/* ----- */

#endif //MAGICCHESS_DRIVER_CONFIG_H
