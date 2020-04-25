#ifndef MAGICCHESS_DRIVER_MAIN_H
#define MAGICCHESS_DRIVER_MAIN_H

// Libraries
#include <Arduino.h>
#include <Wire.h>
#include <Stepper.h>

#include "config.h"

// Functions
void goToTile(int x, int y, int field);
void getStep();
void I2C_send();
void goHome();
void makeStep();
void makeStep(int xFrom, int yFrom, int xTo, int yTo);

//  Steppers
Stepper sX(SPR_X, S_X1, S_X2, S_X3, S_X4);
Stepper sY(SPR_Y, S_Y1, S_Y2, S_Y3, S_Y4);

#endif //MAGICCHESS_DRIVER_MAIN_H
