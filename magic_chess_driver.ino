#include "main.h"

// Step vars
short getPos = 0; // reading position
short cFrom[2], cTo[2]; // cell from and to
short fFrom, fTo; // field from and to

void I2C_send() {
    Wire.beginTransmission(0);
    Wire.write('1');
    Wire.endTransmission();
}

// Getting step from ESP
void getStep() {
    switch (getPos) {
        case 0:
            cFrom[0] = short(Wire.read());
            break;
        case 1:
            cFrom[1] = short(Wire.read());
            break;
        case 2:
            fFrom = short(Wire.read());
            break;
        case 3:
            cTo[0] = short(Wire.read());
            break;
        case 4:
            cTo[1] = short(Wire.read());
            break;
        case 5:
            fTo = short(Wire.read());
            break;
    }
    getPos++;
}

// Return electromagnet to start position
void goHome() {
    bool atHomeX = false;
    bool atHomeY = false;
    while (!atHomeX || !atHomeY) {
        if (digitalRead(trX) == HIGH)
            sX.step(xSteps);
        else
            atHomeX = true;

        if (digitalRead(trY) == HIGH)
            sY.step(ySteps);
        else
            atHomeY = true;
    }
}

void makeStep() {
    // TODO: make function
}

void setup() {
    // Serial
    Serial.begin(9600);

    // I2C
    Wire.begin(I2C_ADR);
    Wire.onReceive(getStep());

    // Steppers
    sX.setSpeed(SPEED_X);
    sY.setSpeed(SPEED_Y);

    // Trailers
    pinMode(trX, INPUT_PULLUP);
    pinMode(trY, INPUT_PULLUP);

    goHome();

    // Ready to receive commands
    I2C_send();
}

void loop() {
    if (getPos >= 6)
        makeStep();
}

