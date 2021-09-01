/*
 * SparkDisplayControl.h
 *
 *  Created on: 23.08.2021
 *      Author: stangreg
 */

#ifndef SPARKDISPLAYCONTROL_H_
#define SPARKDISPLAYCONTROL_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306

#include "SparkDataControl.h"

// OLED Screen config
#define SCREEN_WIDTH 128 // Display width
#define SCREEN_HEIGHT 64 // Display height
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define DISPLAY_MIN_X_FACTOR -12 // for text size 2, scales linearly with text size

// Splash logo measurements
#define imageWidth 128
#define imageHeight 47

class SparkDataControl;

class SparkDisplayControl {
public:
	SparkDisplayControl();
	SparkDisplayControl(SparkDataControl* dc);
	virtual ~SparkDisplayControl();
	void init(int mode);
	void update();
	// Can only be used in Server mode as in Client mode display is controlled by active preset
	void showMessage(std::string* msg, int numLines, int size, int x = 0, int y = 0);


private:
	static Adafruit_SSD1306 display;
	SparkDataControl* spark_dc;
	int activeBank = 1;
	int pendingBank = 1;
	const preset* activePreset;
	const preset* pendingPreset;
	const preset* presetFromApp;
	int presetEditMode;
	int buttonMode = 1;
	int activePresetNum = 1;
	int selectedPresetNum = 1;
	int opMode = 1;
	bool isConnected = false;

	std::string primaryLineText;
	const preset* primaryLinePreset;
	std::string secondaryLineText;
	const preset* secondaryLinePreset;

	unsigned long previousMillis = 0;
	int showMessageInterval = 2000;
	bool showMsgFlag = false;

	//DISPLAY variables x1 for the first line, x2 for the second line
	int display_x1 = 0;
	int display_minX1 = DISPLAY_MIN_X_FACTOR * 10;
	int display_scroll_num1 = -1; // scroll speed, make more negative to speed up the scroll

	int display_x2 = 0;
	int display_minX2 = DISPLAY_MIN_X_FACTOR * 10;
	int display_scroll_num2 = -1; // scroll speed, make more negative to speed up the scroll

	SparkDataControl* dataControl() {return spark_dc;}
	void showInitialMessage();
	void showConnection();
	void showBankAndPresetNum();
	void showPresetName();
	void showFX_SecondaryName();
	void updateTextPositions();

	// 'Sparky_Logo', 128x47px
	const unsigned char epd_bitmap_Sparky_Logo [768] PROGMEM = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xfe, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xfd, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xf3, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xcf, 0xef, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xef, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xf8, 0xef, 0x1f, 0xe7, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0x78, 0xff, 0xff, 0xf1, 0xec, 0x7f, 0xe7, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0x1f, 0xff, 0xb7, 0xc0, 0xfb, 0xe7, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xb7, 0xce, 0x13, 0xa7, 0x81, 0xfb, 0xe7, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xfe, 0xff, 0xb7, 0xee, 0x63, 0xcf, 0xe5, 0xfb, 0xe7, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xf1, 0xff, 0x73, 0xcc, 0xe7, 0xcf, 0xe4, 0xfb, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xc7, 0xfe, 0xf3, 0xcd, 0xc3, 0xef, 0xe6, 0x7b, 0xcf, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0x9f, 0xfd, 0xf3, 0x1d, 0x93, 0xef, 0xe7, 0x3d, 0x8f, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0x3f, 0xfb, 0xf0, 0x7c, 0x3b, 0xef, 0xe7, 0x8c, 0x2f, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0x7f, 0xe7, 0xf3, 0xff, 0xfb, 0xef, 0xe7, 0xe3, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfe, 0x7f, 0xcf, 0xf3, 0xff, 0xfd, 0xff, 0xef, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfe, 0x7f, 0x0f, 0xfb, 0xff, 0xff, 0xff, 0xef, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfe, 0xfc, 0x1f, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x3f, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfe, 0xf0, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc7, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xfe, 0x41, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0x07, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x6f, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xef, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xcf, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xf7, 0xcf, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x0f, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};

	// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 768)
	const int epd_bitmap_allArray_LEN = 1;
	const unsigned char* epd_bitmap_allArray[1] = {
		epd_bitmap_Sparky_Logo
	};

};

#endif /* SPARKDISPLAYCONTROL_H_ */
