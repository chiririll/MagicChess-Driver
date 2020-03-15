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
#define X_RAD 10
#define Y_RAD 15
/* ----- */

/* Trailers */
#define trX 2
#define trY 3
/* ----- */

// I2C Address
#define I2C_ADR 2

// Electromagnet pin
#define MAGNET 12

/* Chessboard settings (in mm) */
// Field 0 (left storage)
#define X_HOME 243
#define Y_HOME 24
// Field 1 (chessboard)
#define X_HOME 73
#define Y_HOME 24
// Field 2 (right storage)
#define X_HOME 22
#define Y_HOME 24
// Cell width
#define CELL_W 20
/* ----- */

#endif //MAGICCHESS_DRIVER_CONFIG_H
