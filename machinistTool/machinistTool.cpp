#include "machinistTool.h"
#include "TwistedDrillCalculator.h"
#include "MillCalculator.h"
#include "TurnCalculator.h"

//some switches and leds are connected to pins for vcc
uint8_t pinsToSetHigh[] = {
    A14 };

//the pin used to keep the power on
#define POWERPIN A2

#define BLINK_LED_ON_TIME 500
#define BLINK_LED_OFF_TIME 1000

VoltMeter batteryMeter(A1, BATTERY_MULTIPLYER);
//for turning the workpiece(inner or outer diameter)  otherwise the tool diameter
MedianAnalog diameterMeter(A15);

DebounceButton WorkPieceButtons[numberOfWorkPieceMaterials] = {
    DebounceButton(15),
    DebounceButton(17),
    DebounceButton(18),
    DebounceButton(19),
    DebounceButton(21),
    DebounceButton(33),
    DebounceButton(43) };

BlinkLed WorkPieceLeds[numberOfWorkPieceMaterials] = {
    BlinkLed(32, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(36, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(8, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(38, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(14, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(20, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(46, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME) };

DebounceButton cutterButtons[NumberOfCutterMaterials] = {
    DebounceButton(A7),
    DebounceButton(A6) };

BlinkLed cutterLeds[NumberOfCutterMaterials] = {
    BlinkLed(A5, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(A4, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME) };

DebounceButton operationButtons[numberOfOperations] = {
    DebounceButton(23),
    DebounceButton(35),
    DebounceButton(50) };

BlinkLed operationLeds[numberOfOperations] = {
    BlinkLed(49, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(41, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME),
    BlinkLed(53, BLINK_LED_ON_TIME, BLINK_LED_OFF_TIME) };

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
//the millis at the time of entering the loop
#ifndef LOOPMILLIS
#error this sketch assumes it is compiled with -DLOOPMILLIS=loopmillis
#endif
uint32_t LOOPMILLIS;

WorkPieceMaterials selectedWorkpieceMaterial = defaultWorkpieceMaterial;
cutterMaterials selectedCutterMaterial = defaultCutterMaterial;
operations SelectedOperation = defaultOperation;
int selectedDia = -1;
WorkPieceMaterials previouselectedWorkpieceMaterial = numberOfWorkPieceMaterials;
cutterMaterials previousSelectedCutterMaterial = NumberOfCutterMaterials;
operations previousSelectedOperation = numberOfOperations;
int prefSelectedDiameter = -1;
const char diameterChar = 'D';
const char operationChar = 2;
const char cuttingMaterialChar = 3;
const char RPMChar = 4;
const char feedChar = 5;
const char perMinChar = 6;
const char perRoundChar = 7;

// Creat a set of new characters
byte perMinCharPixels[8] = {
    0b00100,
    0b01000,
    0b10000,
    0b10101,
    0b11101,
    0b10101,
    0b00000,
    0b00000 };
byte feedCharPixels[8] = {
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b10101,
    0b01110,
    0b00100 };
byte RPMCharPixels[8] = {
    0b01110,
    0b10001,
    0b10001,
    0b00101,
    0b01101,
    0b11111,
    0b01100,
    0b00100 };
byte diameterCharPixels[8] = {
    0b00000,
    0b01110,
    0b01010,
    0b10001,
    0b10001,
    0b01010,
    0b01110,
    0b00000 };
byte millCharPixels[8] = {
    0b10111,
    0b01110,
    0b11101,
    0b11011,
    0b10111,
    0b01111,
    0b11011,
    0b10001 };
byte drillCharPixels[8] = {

    0b11011,
    0b10111,
    0b01110,
    0b11101,
    0b11011,
    0b10111,
    0b01110,
    0b00100 };
byte turnCharPixels[8] = {
    0b00100,
    0b01110,
    0b11011,
    0b01110,
    0b10101,
    0b11011,
    0b11111,
    0b11111 };
byte hssCharPixels[8] = {
    0b10100,
    0b11100,
    0b10100,
    0b00000,
    0b01001,
    0b10010,
    0b01001,
    0b10010 };
byte carbideCharPixels[8] = {
    0b00000,
    0b00100,
    0b01110,
    0b11011,
    0b01110,
    0b00100,
    0b00000,
    0b00000 };

byte unknownCharPixels[8] = {
    0b00000,
    0b01100,
    0b10010,
    0b00100,
    0b01000,
    0b01000,
    0b00000,
    0b01000 };
/*
 * Has the user changed any of the settings since last time we looked
 */
boolean thingsChanged() {
    return !(previouselectedWorkpieceMaterial == selectedWorkpieceMaterial && previousSelectedCutterMaterial == selectedCutterMaterial
                    && previousSelectedOperation == SelectedOperation && selectedDia == prefSelectedDiameter);

}
/*
 * shuts down the module
 */
void shutDown() {
    Serial.println("Shutting down");
    digitalWrite(POWERPIN, LOW);
    delay(10000);
}
/* the arduino powered by a USB?
 *
 */
boolean poweredByUSB() {
    int batteryCentivolt = batteryMeter.getCentiVoltage();
    return batteryCentivolt < 30;
}
TwistedDrillCalculator drillCalculator;
MillCalculator millCalculator;
TurnCalculator turnCalculator;
void checkBattery() {
    if (poweredByUSB()) {
        return;
    }
    int batteryCentivolt = batteryMeter.getCentiVoltage();
    //If the  battery voltage is really low we are probably on USB power
    if ((batteryCentivolt < BATTERY_TO_LOW_CENTI_VOLTAGE)) {
        lcd.clear();
        lcd.println("Battery Low");
        lcd.print("!!Recharge Battery!!");
        Serial.println("Battery Low");
        Serial.println(batteryMeter.getCentiVoltage());
        delay(5000);
        shutDown();
    }
}
boolean isDataEntryIncomplete() {
    return (selectedWorkpieceMaterial == numberOfWorkPieceMaterials || selectedCutterMaterial == NumberOfCutterMaterials
                    || SelectedOperation == numberOfOperations);
}
void updateDisplay() {
    if (loopMillis < 5000) {
        //make sure there is a difference when this is skipped
        selectedDia--;
        return;
    }
    if (!thingsChanged()) {
        return;
    }
    lcd.clear();
    char diabuffer[17];
    if (isDataEntryIncomplete()) {
        snprintf(diabuffer, sizeof(diabuffer), "Press leds..%c%d ", diameterChar, selectedDia);
        lcd.print(diabuffer);
        lcd.setCursor(0, 1);
        if (selectedWorkpieceMaterial == numberOfWorkPieceMaterials) {
            lcd.print("Workpiece Mat?  ");
        } else if (selectedCutterMaterial == NumberOfCutterMaterials) {
            lcd.print("Cutter Mat?     ");
        } else if (SelectedOperation == numberOfOperations) {
            lcd.print("Operation?      ");
        }
        return;
    }

    snprintf(diabuffer, sizeof(diabuffer), "%s%c%c%c%d ", workPieceMaterialNames[selectedWorkpieceMaterial], operationChar, cuttingMaterialChar, diameterChar,
                    selectedDia);
    lcd.print(diabuffer);
    lcd.setCursor(0, 1);
    ICalculator *calc;
    switch (SelectedOperation) {
        case drilling: {
            calc=&drillCalculator;
            break;
        }
        case turning: {
            calc=&turnCalculator;
            break;
        }
        case milling: {
            calc=&millCalculator;
            break;
        }
        default: {
            lcd.print("Unknown operatio");
            Serial.println("Unknown operation");
            return;
        }

    }
    int RPM = calc->calculateRPM(selectedCutterMaterial, selectedWorkpieceMaterial, selectedDia);
    int feed = calc->calculatellFeedPer100Revolutions(selectedCutterMaterial, selectedWorkpieceMaterial, selectedDia);
    char line[16];
    sprintf(line, "%c:%i %c:.%i", RPMChar, RPM, feedChar, feed);
    lcd.print(line);
}

void updateLeds() {

    if (selectedWorkpieceMaterial != previouselectedWorkpieceMaterial) {
        Serial.println("WorkPiece Selected");
        for (int curWorkPieceMaterial = 0; curWorkPieceMaterial < numberOfWorkPieceMaterials; curWorkPieceMaterial++) {
            WorkPieceLeds[curWorkPieceMaterial].setLedState(BlinkLed::off);
        }
        WorkPieceLeds[selectedWorkpieceMaterial].setLedState(BlinkLed::on);
    }

    if (selectedCutterMaterial != previousSelectedCutterMaterial) {
        Serial.println("Cutter material selected");
        for (int curCutterMaterial = 0; curCutterMaterial < NumberOfCutterMaterials; curCutterMaterial++) {
            cutterLeds[curCutterMaterial].setLedState(BlinkLed::off);
        }
        cutterLeds[selectedCutterMaterial].setLedState(BlinkLed::on);
    }

    if (SelectedOperation != previousSelectedOperation) {
        Serial.println("Operation Selected");
        for (int curOperation = 0; curOperation < numberOfOperations; curOperation++) {
            operationLeds[curOperation].setLedState(BlinkLed::off);
        }
        operationLeds[SelectedOperation].setLedState(BlinkLed::on);

    }
}
void loadOperationImage() {
    switch (SelectedOperation) {

        case milling:
            lcd.createChar(operationChar, millCharPixels);
            break;
        case drilling:
            lcd.createChar(operationChar, drillCharPixels);
            break;
        case turning:
            lcd.createChar(operationChar, turnCharPixels);
            break;
        default:
            lcd.createChar(operationChar, unknownCharPixels);
    }
}
void loadCutterMaterialImage() {
    switch (selectedCutterMaterial) {
        case hss:
            lcd.createChar(cuttingMaterialChar, hssCharPixels);
            break;
        case carbide:
            lcd.createChar(cuttingMaterialChar, carbideCharPixels);
            break;
        default:
            lcd.createChar(cuttingMaterialChar, unknownCharPixels);
    }
}
void setup() {
#ifdef SOFTPWM
    SoftPWMBegin();
    for (int curWorkPieceMaterial = 0; curWorkPieceMaterial < numberOfWorkPieceMaterials; curWorkPieceMaterial++) {
        WorkPieceLeds[curWorkPieceMaterial].setPwmValue(PWMVALUE);
    }
    for (int curCutterMaterial = 0; curCutterMaterial < NumberOfCutterMaterials; curCutterMaterial++) {
        cutterLeds[curCutterMaterial].setPwmValue(PWMVALUE);
    }
    for (int curOperation = 0; curOperation < numberOfOperations; curOperation++) {
        operationLeds[curOperation].setPwmValue(PWMVALUE);
    }

#endif
    lcd.begin(16, 2);
    lcd.createChar(diameterChar, diameterCharPixels);
    lcd.createChar(RPMChar, RPMCharPixels);
    lcd.createChar(feedChar, feedCharPixels);
    loadOperationImage();
    loadCutterMaterialImage();

    lcd.clear();
    lcd.home();
    lcd.print("Jantje Machinist");
    delay(1000); //let the serial monitor some time to connect
    Serial.begin(115200);
    Serial.println("MachinistTool");
    pinMode(POWERPIN, OUTPUT);
    digitalWrite(POWERPIN, HIGH);
    for (int curWorkPieceMaterial = 0; curWorkPieceMaterial < numberOfWorkPieceMaterials; curWorkPieceMaterial++) {
        WorkPieceButtons[curWorkPieceMaterial].setup();
        WorkPieceLeds[curWorkPieceMaterial].setup();
    }
    for (int curCutterMaterial = 0; curCutterMaterial < NumberOfCutterMaterials; curCutterMaterial++) {
        cutterButtons[curCutterMaterial].setup();
        cutterLeds[curCutterMaterial].setup();
    }
    for (int curOperation = 0; curOperation < numberOfOperations; curOperation++) {
        operationButtons[curOperation].setup();
        operationLeds[curOperation].setup();
    }

    for (unsigned int curSetHighPin = 0; curSetHighPin < sizeof(pinsToSetHigh); ++curSetHighPin) {
        pinMode(pinsToSetHigh[curSetHighPin], OUTPUT);
        digitalWrite(pinsToSetHigh[curSetHighPin], HIGH);
    }
    batteryMeter.setup();
    diameterMeter.setup();
    loadOperationImage();
    Serial.println("initialisation done");

}
//there is no off-buton so shut down when nothing changes
void timeToShutDown() {
    if (poweredByUSB()) {
        return;
    }
    static int32_t lastChange = millis();
    if (thingsChanged()) {
        lastChange = loopMillis;
    } else {
        if ((loopMillis - lastChange) > 600000) {
            Serial.println("Shutting down as nothing ever happens");
            shutDown();
        }
    }
}

//UI stuff and so on that is not so time critical
// runs only every n millis
void businessLoop() {
    for (int curWorkPieceMaterial = 0; curWorkPieceMaterial < numberOfWorkPieceMaterials; curWorkPieceMaterial++) {
        if (WorkPieceButtons[curWorkPieceMaterial].isPushed()) {
            selectedWorkpieceMaterial = (WorkPieceMaterials) curWorkPieceMaterial;
//                Serial.print("Workpiece button ");
//                Serial.print(curWorkPieceMaterial);
//                Serial.println(" pushed");
        }
    }
    for (int curCutterMaterial = 0; curCutterMaterial < NumberOfCutterMaterials; curCutterMaterial++) {
        if (cutterButtons[curCutterMaterial].isPushed()) {
            selectedCutterMaterial = (cutterMaterials) curCutterMaterial;
            loadCutterMaterialImage();
        }
    }
    for (int curOperation = 0; curOperation < numberOfOperations; curOperation++) {
        if (operationButtons[curOperation].isPushed()) {
            SelectedOperation = (operations) curOperation;
            loadOperationImage();
        }
    }
    batteryMeter.loop();
    diameterMeter.loop();

    int pinValue = 1010 - diameterMeter.getValue();
    selectedDia = map(constrain(pinValue, 10, 1010), 0, 1000, MINIMUM_DIAMETER_IN_MM, MAXIMUM_DIAMETER_IN_MM);

    timeToShutDown();
    checkBattery();
    updateDisplay();
    updateLeds();
//do some change logging for debugging
    if (thingsChanged()) {
        Serial.print("things changed from: ");
        Serial.print(previouselectedWorkpieceMaterial);
        Serial.print(", ");
        Serial.print(previousSelectedCutterMaterial);
        Serial.print(", ");
        Serial.print(previousSelectedOperation);
        Serial.print(", ");
        Serial.print(prefSelectedDiameter);
        Serial.println();

        Serial.print("things changed to: ");
        Serial.print(selectedWorkpieceMaterial);
        Serial.print(", ");
        Serial.print(selectedCutterMaterial);
        Serial.print(", ");
        Serial.print(SelectedOperation);
        Serial.print(", ");
        Serial.print(selectedDia);
        Serial.println();

        previouselectedWorkpieceMaterial = selectedWorkpieceMaterial;
        previousSelectedCutterMaterial = selectedCutterMaterial;
        previousSelectedOperation = SelectedOperation;
        prefSelectedDiameter = selectedDia;
    }
}
void loop() {
    static uint32_t prefAction = 0;
    LOOPMILLIS = millis();
    for (int curWorkPieceMaterial = 0; curWorkPieceMaterial < numberOfWorkPieceMaterials; curWorkPieceMaterial++) {
        WorkPieceButtons[curWorkPieceMaterial].loop();
        WorkPieceLeds[curWorkPieceMaterial].loop();
    }
    for (int curCutterMaterial = 0; curCutterMaterial < NumberOfCutterMaterials; curCutterMaterial++) {
        cutterButtons[curCutterMaterial].loop();
        cutterLeds[curCutterMaterial].loop();
    }
    for (int curOperation = 0; curOperation < numberOfOperations; curOperation++) {
        operationButtons[curOperation].loop();
        operationLeds[curOperation].loop();
    }
    if (LOOPMILLIS - prefAction > 100) {
        prefAction = LOOPMILLIS;
        businessLoop();

    }
//debug info
    static uint32_t lastLogged;
    static uint32_t numloops;
    numloops++;
    if (LOOPMILLIS - lastLogged > 1000) {
        lastLogged = LOOPMILLIS;
        Serial.print("Lils ");
        Serial.print(numloops);
        Serial.println();
        numloops = 0;
    }

}
