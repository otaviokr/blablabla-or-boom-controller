/********************************************
 * This is the controller of the briefbomb
 * It needs to be activated at the start of the game
 * and the value defined by the switches determine
 * how the game is played (variables, sequence etc.)
 *
 * The timer starts right after the START button is pressed.
 * Once the timer is up, the piezo will sound and all functions
 * in the briefbomb will be disable. To reactivate, press the
 * START button again (you may change the slides before,
 * if you want).
 *****************************************************/

#include <Arduino.h>
#include "pins.h"
#include "7seg/startup.h"
#include "SevSeg.h"
#include "Tone32.h"

SevSeg sevseg;

int currentTime = 0;
int selectedGame = 0;

const int SEVEN_SEG_OFF[7] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
const int SEVEN_SEG_ZERO[7] = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH};
const int SEVEN_SEG_ONE[7] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH};
const int SEVEN_SEG_TWO[7] = {LOW, LOW, HIGH, LOW, LOW, HIGH, LOW};
const int SEVEN_SEG_THREE[7] = {LOW, LOW, LOW, LOW, HIGH, HIGH, LOW};
const int SEVEN_SEG_FOUR[7] = {HIGH, LOW, LOW, HIGH, HIGH, LOW, LOW};
const int SEVEN_SEG_FIVE[7] = {LOW, HIGH, LOW, LOW, HIGH, LOW, LOW};
const int SEVEN_SEG_SIX[7] = {LOW, HIGH, LOW, LOW, LOW, LOW, LOW};
const int SEVEN_SEG_SEVEN[7] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, HIGH};
const int SEVEN_SEG_EIGHT[7] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW};
const int SEVEN_SEG_NINE[7] = {LOW, LOW, LOW, LOW, HIGH, LOW, LOW};

// int segments[7] = {
// 	SEV_SEG_11,SEV_SEG_7,SEV_SEG_4,SEV_SEG_2,SEV_SEG_1,SEV_SEG_10,SEV_SEG_5
int segments[7] = {
	3, 5, 27, 25, 33, 21, 14
};

void lightChar(int value, int segments[]) {
    int listChars[11][7] = {
        {SEVEN_SEG_OFF[0],SEVEN_SEG_OFF[1],SEVEN_SEG_OFF[2],SEVEN_SEG_OFF[3],SEVEN_SEG_OFF[4],SEVEN_SEG_OFF[5],SEVEN_SEG_OFF[6]},
        {SEVEN_SEG_ZERO[0],SEVEN_SEG_ZERO[1],SEVEN_SEG_ZERO[2],SEVEN_SEG_ZERO[3],SEVEN_SEG_ZERO[4],SEVEN_SEG_ZERO[5],SEVEN_SEG_ZERO[6]},
        {SEVEN_SEG_ONE[0],SEVEN_SEG_ONE[1],SEVEN_SEG_ONE[2],SEVEN_SEG_ONE[3],SEVEN_SEG_ONE[4],SEVEN_SEG_ONE[5],SEVEN_SEG_ONE[6]},
        {SEVEN_SEG_TWO[0],SEVEN_SEG_TWO[1],SEVEN_SEG_TWO[2],SEVEN_SEG_TWO[3],SEVEN_SEG_TWO[4],SEVEN_SEG_TWO[5],SEVEN_SEG_TWO[6]},
        {SEVEN_SEG_THREE[0],SEVEN_SEG_THREE[1],SEVEN_SEG_THREE[2],SEVEN_SEG_THREE[3],SEVEN_SEG_THREE[4],SEVEN_SEG_THREE[5],SEVEN_SEG_THREE[6]},
        {SEVEN_SEG_FOUR[0],SEVEN_SEG_FOUR[1],SEVEN_SEG_FOUR[2],SEVEN_SEG_FOUR[3],SEVEN_SEG_FOUR[4],SEVEN_SEG_FOUR[5],SEVEN_SEG_FOUR[6]},
        {SEVEN_SEG_FIVE[0],SEVEN_SEG_FIVE[1],SEVEN_SEG_FIVE[2],SEVEN_SEG_FIVE[3],SEVEN_SEG_FIVE[4],SEVEN_SEG_FIVE[5],SEVEN_SEG_FIVE[6]},
        {SEVEN_SEG_SIX[0],SEVEN_SEG_SIX[1],SEVEN_SEG_SIX[2],SEVEN_SEG_SIX[3],SEVEN_SEG_SIX[4],SEVEN_SEG_SIX[5],SEVEN_SEG_SIX[6]},
        {SEVEN_SEG_SEVEN[0],SEVEN_SEG_SEVEN[1],SEVEN_SEG_SEVEN[2],SEVEN_SEG_SEVEN[3],SEVEN_SEG_SEVEN[4],SEVEN_SEG_SEVEN[5],SEVEN_SEG_SEVEN[6]},
        {SEVEN_SEG_EIGHT[0],SEVEN_SEG_EIGHT[1],SEVEN_SEG_EIGHT[2],SEVEN_SEG_EIGHT[3],SEVEN_SEG_EIGHT[4],SEVEN_SEG_EIGHT[5],SEVEN_SEG_EIGHT[6]},
        {SEVEN_SEG_NINE[0],SEVEN_SEG_NINE[1],SEVEN_SEG_NINE[2],SEVEN_SEG_NINE[3],SEVEN_SEG_NINE[4],SEVEN_SEG_NINE[5],SEVEN_SEG_NINE[6]}
    };

    for(int i = 0; i < 7; i++) {
        digitalWrite(segments[i], listChars[value+1][i]);
    }
}

void lightDisplay(int value, int segments[]) {
		// Just clear the display.
	if (value < 0) {
		clearDisplay();
		return;
	}

	// Ignore any number higher than 9999 because it won fit in the display.
	if (value > 9999) {
		value = 9999;
	}

	int thousands = (value / 1000);
	digitalWrite(SEV_SEG_12, HIGH);
	lightChar(thousands, segments);
	delay(20);

	int hundreds = (value - thousands / 100);
	digitalWrite(SEV_SEG_12, LOW);
	digitalWrite(SEV_SEG_9, HIGH);
	lightChar(thousands, segments);
	delay(20);

	int tens = (value - (thousands + hundreds) / 10);
	digitalWrite(SEV_SEG_12, LOW);
	digitalWrite(SEV_SEG_9, LOW);
	digitalWrite(SEV_SEG_8, HIGH);
	lightChar(tens, segments);
	delay(20);

	int units = value % 10;
	digitalWrite(SEV_SEG_12, LOW);
	digitalWrite(SEV_SEG_9, LOW);
	digitalWrite(SEV_SEG_8, LOW);
	digitalWrite(SEV_SEG_6, HIGH);
	lightChar(units, segments);
}

void setup() {
	byte numDigits = 4;
	byte digitPins[] = {SEV_SEG_12, SEV_SEG_9, SEV_SEG_8, SEV_SEG_6};
	byte segmentPins[] = {SEV_SEG_11, SEV_SEG_7, SEV_SEG_4, SEV_SEG_2,
			SEV_SEG_1, SEV_SEG_10, SEV_SEG_5, SEV_SEG_3};
	byte hardwareConfig = COMMON_ANODE;
	bool resistorsOnSegments = false;
	bool updateWithDelays = false;
	bool leadingZeros = true;
	bool disableDecPoint = true;

	sevseg.begin( hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
			updateWithDelays, leadingZeros, disableDecPoint);


	// // Serial.begin(9600);

	// // The  selector and the game select
	// //pinMode(SELECTOR, INPUT);
	// //pinMode(GAME_SELECT, OUTPUT);

	// // The 7-seg display
	// pinMode(SEV_SEG_1, OUTPUT);
	// pinMode(SEV_SEG_2, OUTPUT);
	// pinMode(SEV_SEG_3, OUTPUT);
	// pinMode(SEV_SEG_4, OUTPUT);
	// pinMode(SEV_SEG_5, OUTPUT);
	// pinMode(SEV_SEG_6, OUTPUT);
	// pinMode(SEV_SEG_7, OUTPUT);
	// pinMode(SEV_SEG_8, OUTPUT);
	// pinMode(SEV_SEG_9, OUTPUT);
	// pinMode(SEV_SEG_10, OUTPUT);
	// pinMode(SEV_SEG_11, OUTPUT);
	// pinMode(SEV_SEG_12, OUTPUT);

	// clearDisplay();

	// // The START button
	// pinMode(START_BTN, INPUT);

	// The Go LED
	pinMode(GO_LED, OUTPUT);
	digitalWrite(GO_LED, LOW);

	// PIEZO
	pinMode(PIEZO, OUTPUT);
	digitalWrite(PIEZO, LOW);

	// // Start sequence 7segments.
	// startSevenSegs();
}

void blinkDotStart() {
	clearDisplay();
	digitalWrite(SEV_SEG_12, HIGH);
	digitalWrite(SEV_SEG_9, HIGH);
	digitalWrite(SEV_SEG_8, HIGH);
	digitalWrite(SEV_SEG_6, HIGH);
	for(int i = 0; i < 3; i++) {
		digitalWrite(SEV_SEG_3, LOW);
		delay(200);
		digitalWrite(SEV_SEG_3, HIGH);
		delay(200);
	}
}

int begin() {
	// int selectedGame = analogRead(SELECTOR);
	// int mapped = map(selectedGame, 0, 1023, 0, 255);
	// analogWrite(GAME_SELECT, mapped);
	// Serial.println(mapped);
	// blinkDotStart();
	int currentTime = 25;

	digitalWrite(GO_LED, HIGH);

	// lightChar(-1, segments);
	return currentTime;
}

void loop() {
	sevseg.blank();
	// START_BTN is pressed - set config and timer.
	int btn = digitalRead(START_BTN);
	if (btn == HIGH) {
		currentTime = begin();
	}

	// Serial.println(currentTime);
	// If time is running, refresh it.
	if (currentTime > -1) {
		// lightDisplay(-1, segments);
		// sevseg.blank();
		// delay(200);
		// lightDisplay(currentTime--, segments);
		for(int i = 0; i < 200000; i++) {
			sevseg.setNumber(currentTime, 0);
			sevseg.refreshDisplay();
		}
		for(int i = 0; i < 50000; i++) {
			sevseg.blank();
			sevseg.refreshDisplay();
		}
		currentTime--;
		// delay(800);

	// If time is up.
	} else if(currentTime == -1) {
		digitalWrite(GO_LED, LOW);
		tone(PIEZO, NOTE_A, 3000, 0);
		// notone(PIEZO);
		currentTime = -2;
	}
}
