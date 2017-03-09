#include "Arduino.h"
#include "SPI.h"
#include "MS5803_14.h"
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"

//Please set it to 1, if factory reset is desired during startup otherwise set it to 0
#define FACTORYRESET_ENABLE 1
#define VBATPIN A9

Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

//Pressure Sensor initialization
MS_5803 sensor = MS_5803(512);

const int ledPin = 13;  // led pin

//Message handling related variables 
String messageBuffer = "";
bool recordMessage = false;

void setup() {
	Serial.begin(115200);

	while (!Serial) { // Wait for USB Serial
	}
	delay(1000);

	Serial.println(F("\nBleSensorRemote - START\n"));

  if (sensor.initializeMS_5803(false)) {
    Serial.println(F("Pressure sensor: OK\n"));
  }
  else {
    Serial.println(F("Pressure sensor: FAILED\n"));
  } 

	/* Initialise the module */
	Serial.print(F("BLE - Initializing the Bluefruit LE module: "));

	if (!ble.begin(VERBOSE_MODE)) {
		Serial.println(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
	}
	Serial.println(F("OK!"));

	if (FACTORYRESET_ENABLE) {
		/* Perform a factory reset to make sure everything is in a known state */
		Serial.println(F("BLE - Performing a factory reset: "));
		if (!ble.factoryReset()) {
			Serial.println(F("Couldn't do factory reset"));
		} else {
			Serial.println(F("OK!"));
		}
	}

	ble.echo(false);
	ble.info();
  
  Serial.println(F("Setting device name to 'BleSensor': "));
  if (! ble.sendCommandCheckOK(F("AT+GAPDEVNAME=BleSensor")) ) {
    Serial.println(F("Could not set device name?"));
  }
 
	ble.verbose(false);

	/* Wait for connection - Adafruit Bluefruit LE app has to be used to establish an UART connection. */
	while (!ble.isConnected()) {
		delay(500);
	}

  // Set module to DATA mode
  Serial.println(F("Switching to DATA mode!"));
  ble.setMode(BLUEFRUIT_MODE_DATA);
 
  Serial.println(F("\nREADY!\n"));
}

void loop() {
	//Read messages from the standard Serial interface
	if (Serial.available() > 0) {
		readMessageFromSerial(Serial.read());
	}

	//Read messages from the BLE interface
	while (ble.available()) {
		readMessageFromSerial((char) ble.read());
	}
}

void readMessageFromSerial(char data) {
	if (data == '@') {
		messageBuffer = "";
		recordMessage = true;
		digitalWrite(ledPin, HIGH); //Turn the LED on
	} else if (data == '#') {  
		handleMessage(messageBuffer);
		recordMessage = false;
		digitalWrite(ledPin, LOW); //Turn the LED off
	} else {
		if (recordMessage) {
			messageBuffer += data;
		}
	}
}

void handleMessage(String message) {
	Serial.println(message);
	Serial.flush();

	String responseMessage = "";
	if (message.startsWith(F("TEMP:")) || message.startsWith(F("temp"))) {
    sensor.readSensor();
    responseMessage += sensor.temperature();
	} else if (message.startsWith(F("PRES")) || message.startsWith(F("pres"))) {
		sensor.readSensor();
    responseMessage += sensor.pressure();
	} else if (message.startsWith(F("BAT")) || message.startsWith(F("bat"))) {
    float measuredvbat = analogRead(VBATPIN);
    measuredvbat *= 2;    // we divided by 2, so multiply back
    measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
    measuredvbat /= 1024; // convert to voltage
    responseMessage += measuredvbat;
	}
  
  Serial.println(responseMessage);
  Serial.flush();
  ble.print(responseMessage);
  ble.flush();
}

