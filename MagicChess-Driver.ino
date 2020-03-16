#include "main.h"

// Step vars
short getPos = 0; // reading position
short from[3], to[3]; // 0 - x, 1 - y, 2 - field

// Current position
short nowPos[2];

void I2C_send() {
    Wire.beginTransmission(0);
    Wire.write('1');
    Wire.endTransmission();
}

// Getting step from ESP
void getStep() {
    if (getPos < 3)
        from[getPos] = short(Wire.read());
    else
        to[getPos - 3] = short(Wire.read());
    getPos++;
}

// Return electromagnet to start position
void goHome() {
    debug("Returning home...");
    digitalWrite(MAGNET, LOW);
    bool atHomeX = false;
    bool atHomeY = false;
    while (!atHomeX || !atHomeY) {
        if (digitalRead(trX) == HIGH)
            sX.step(1);
        else
            atHomeX = true;

        if (digitalRead(trY) == HIGH)
            sY.step(1);
        else
            atHomeY = true;
    }
    nowPos[0] = 0;
    nowPos[1] = 0;

    I2C_send();
    debug("Done!");
}

void makeStep() {
    debug("Moving from (" + String(from[0]) + "; " + String(from[1]) + ") to (" + String(to[0]) + "; " + String(to[1]) + ")");
    // Cleaning counter
    getPos = 0;
    // Disabling magnet
    digitalWrite(MAGNET, LOW);
    // Go to start point
    sX.step((from[0] - nowPos[0]) * SPR_X / (3.1416 * 2 * X_RAD));
    sY.step((from[1] - nowPos[1]) * SPR_Y / (3.1416 * 2 * Y_RAD));
    // Changing now position var
    nowPos[0] = from[0];
    nowPos[1] = from[1];
    // Enabling Magnet
    digitalWrite(MAGNET, HIGH);
    // Go to target point
    sX.step((to[0] - nowPos[0]) * SPR_X / (3.1416 * 2 * X_RAD));
    sY.step((to[1] - nowPos[1]) * SPR_Y / (3.1416 * 2 * Y_RAD));
    // Changing now position var
    nowPos[0] = to[0];
    nowPos[1] = to[1];
    // Disabling magnet
    digitalWrite(MAGNET, LOW);
    // Saying ready
    I2C_send();
    debug("Done!");
}

void debug(String str) {
#ifdef DEBUG_MODE
    Serial.println(str);
#endif
}

void setup() {
    // Serial
    Serial.begin(9600);

    // I2C
    Wire.begin(I2C_ADR);
    Wire.onReceive(getStep);

    // Steppers
    sX.setSpeed(SPEED_X);
    sY.setSpeed(SPEED_Y);

    // Trailers
    pinMode(trX, INPUT_PULLUP);
    pinMode(trY, INPUT_PULLUP);

    // Electromagnet
    pinMode(MAGNET, OUTPUT);
    digitalWrite(MAGNET, LOW);

    goHome();

    // Ready to receive commands
    I2C_send();
    debug("Ready!");
}

void loop() {
    if (getPos >= 6)
        makeStep();

    #ifdef DEBUG_MODE
    else {
        if (Serial.available() > 0) {
            if (getPos < 3)
                from[getPos] = short(Serial.read());
            else
                to[getPos - 3] = short(Serial.read());
            getPos++;
        }
    }
    #endif
}
