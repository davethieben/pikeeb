#include <wiringPi.h>
#include "PiLights.h"

void PiLights::Enable(unsigned short bcmPinNumber)
{
    pinMode(bcmPinNumber, OUTPUT);
    digitalWrite(bcmPinNumber, HIGH);
}

void PiLights::Disable(unsigned short bcmPinNumber)
{
    pinMode(bcmPinNumber, OUTPUT);
    digitalWrite(bcmPinNumber, LOW);
}
