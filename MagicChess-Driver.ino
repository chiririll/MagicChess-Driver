#include "main.h"

// Current position
short nowPos[2];
short freeStor[3] = {0, 0, 0};


void I2C_ready() {
    Wire.beginTransmission(0);
    Wire.write('1');
    Wire.endTransmission();
}

// Getting step from ESP
void getCmd(int count) {
    String cmd = "";
    for (int i = 0; i < count; i++) {
        cmd += Wire.read();
    }
    
    if (cmd[0] == 'M')
        makeStep((int)cmd[1], (int)cmd[2], (int)cmd[3], (int)cmd[4]);
    else if (cmd[0] == 'R')
        removeFigure((int)cmd[1], (int)cmd[2]);
    else {
        // TODO: add freq to array
    }
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

    I2C_ready();
    debug("Done!");
}

void goToTile(int x, int y, int field) {
    int target[2] = {CELL_W * x + X_HOME[field], CELL_W * y + Y_HOME[field] };
    
    if (target[0] > nowPos[0])
        sX.step((target[0] - nowPos[0]) / X_LEN * SPR_X);
    else
        sX.step((nowPos[0] - target[0]) / X_LEN * SPR_X);

    nowPos[0] = target[0];

    if (target[1] > nowPos[1])
        sX.step((target[1] - nowPos[1]) / Y_LEN * SPR_Y);
    else
        sX.step((nowPos[1] - target[1]) / Y_LEN * SPR_Y);

    nowPos[1] = target[1];
}

void makeStep(int xFrom, int yFrom, int xTo, int yTo) {
    debug("Moving from (" + String(xFrom) + "; " + String(yFrom) + ") to (" + String(xTo) + "; " + String(yTo) + ")");

    // Disabling magnet
    digitalWrite(MAGNET, LOW);
    // Go to start point
    goToTile(xFrom, yFrom, 1);
    // Enabling Magnet
    digitalWrite(MAGNET, HIGH);
    // Go to target point
    goToTile(xTo, yTo, 1);
    // Disabling magnet
    digitalWrite(MAGNET, LOW);
    // Saying ready
    I2C_ready();
    debug("Done!");
}

void removeFigure(int x, int y) {
    digitalWrite(MAGNET, LOW);
    goToTile(x, y, 1);

    digitalWrite(MAGNET, HIGH);
    goToTile(freeStor[0], freeStor[1], freeStor[2]);
    digitalWrite(MAGNET, LOW);

    if (freeStor[0] >= 1) {
        if (freeStor[1] >= 7) {
            freeStor[1] = 0;
            freeStor[2] = 1;
        } else
            freeStor[1]++;
        freeStor[0] = 0;
    }
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
    Wire.onReceive(getCmd);

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
    I2C_ready();
    debug("Ready!");
}

void loop() {

}
