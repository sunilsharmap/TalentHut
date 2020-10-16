/*
 * esp_32_bt_car.ino
 *
 * Description: BT Car - ESP32
 *
 *  Created on: 13-Oct-2020
 *      Author: Sunil Sharma P <sunilsharma.pv@gmail.com>
 *
 *     Version: 1.0v
 */

#include "BluetoothSerial.h"
#include "analogWrite.h"

#define ENA   16          /* Enable/speed motors Right        GPIO14(D5) */
#define ENB   17          /* Enable/speed motors Left         GPIO12(D6) */
#define IN_1  18          /* L298N in1 motors Right           GPIO15(D8) */
#define IN_2  19          /* L298N in2 motors Right           GPIO13(D7) */
#define IN_3  22          /* L298N in3 motors Left            GPIO2(D4)  */
#define IN_4  23          /* L298N in4 motors Left            GPIO0(D3)  */

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; /* Bluetooth serial instance */
String command;           /* String to store app command state */
int speed_Coeff = 50;

/* Setting PWM properties */
const int freq = 30000;
const int pwmChannelA = 0;
const int pwmChannelB = 1;
const int resolution = 8;
int dutyCycle = 200;

void setup()
{
	pinMode(ENA, OUTPUT);
	pinMode(ENB, OUTPUT);
	pinMode(IN_1, OUTPUT);
	pinMode(IN_2, OUTPUT);
	pinMode(IN_3, OUTPUT);
	pinMode(IN_4, OUTPUT);

	/* configure LED PWM functionalitites */
	ledcSetup(pwmChannelA, freq, resolution);
	ledcSetup(pwmChannelB, freq, resolution);

	/* attach the channel to the GPIO to be controlled */
	ledcAttachPin(ENA, pwmChannelA);
	ledcAttachPin(ENB, pwmChannelB);

	Serial.begin(115200);
	SerialBT.begin("Sharma_Car_BT"); /* Bluetooth device name */
	Serial.println("The Car started, now you can pair it with bluetooth!");
}

void goAhead()
{
	digitalWrite(IN_1, LOW);
	digitalWrite(IN_2, HIGH);
	ledcWrite(pwmChannelA, dutyCycle);

	digitalWrite(IN_3, LOW);
	digitalWrite(IN_4, HIGH);
 	ledcWrite(pwmChannelB, dutyCycle);
}

void goBack()
{
	digitalWrite(IN_1, HIGH);
	digitalWrite(IN_2, LOW);
	ledcWrite(pwmChannelA, dutyCycle);

	digitalWrite(IN_3, HIGH);
	digitalWrite(IN_4, LOW);
	ledcWrite(pwmChannelB, dutyCycle);
}

void goRight()
{
	digitalWrite(IN_1, HIGH);
	digitalWrite(IN_2, LOW);
	ledcWrite(pwmChannelA, dutyCycle);

	digitalWrite(IN_3, LOW);
	digitalWrite(IN_4, HIGH);
	ledcWrite(pwmChannelB, dutyCycle);
}

void goLeft()
{
	digitalWrite(IN_1, LOW);
	digitalWrite(IN_2, HIGH);
	ledcWrite(pwmChannelA, dutyCycle);

	digitalWrite(IN_3, HIGH);
	digitalWrite(IN_4, LOW);
	ledcWrite(pwmChannelB, dutyCycle);
}

void goAheadRight()
{
	digitalWrite(IN_1, LOW);
	digitalWrite(IN_2, HIGH);
	ledcWrite(pwmChannelA, dutyCycle - speed_Coeff);

	digitalWrite(IN_3, LOW);
	digitalWrite(IN_4, HIGH);
	ledcWrite(pwmChannelB, dutyCycle);
}

void goAheadLeft()
{
	digitalWrite(IN_1, LOW);
	digitalWrite(IN_2, HIGH);
	ledcWrite(pwmChannelA, dutyCycle);

	digitalWrite(IN_3, LOW);
	digitalWrite(IN_4, HIGH);
	ledcWrite(pwmChannelB, dutyCycle - speed_Coeff);
}

void goBackRight()
{
	digitalWrite(IN_1, HIGH);
	digitalWrite(IN_2, LOW);
	ledcWrite(pwmChannelA, dutyCycle - speed_Coeff);

	digitalWrite(IN_3, HIGH);
	digitalWrite(IN_4, LOW);
	ledcWrite(pwmChannelB, dutyCycle);
}

void goBackLeft()
{
	digitalWrite(IN_1, HIGH);
	digitalWrite(IN_2, LOW);
	ledcWrite(pwmChannelA, dutyCycle);

	digitalWrite(IN_3, HIGH);
	digitalWrite(IN_4, LOW);
	ledcWrite(pwmChannelB, dutyCycle - speed_Coeff);
}

void stopRobot()
{
	digitalWrite(IN_1, LOW);
	digitalWrite(IN_2, LOW);
	ledcWrite(pwmChannelA, dutyCycle);

	digitalWrite(IN_3, LOW);
	digitalWrite(IN_4, LOW);
	ledcWrite(pwmChannelB, dutyCycle);
}

void loop()
{
	/* Read received messages */
	if (SerialBT.available()){
		char incomingChar = SerialBT.read();
		if (incomingChar != '\n'){
			command += String(incomingChar);
		}
		else{
			command = "";
		}
	}

	/* Perform the operation depending on the command */
	if(command == "F")
		goAhead();
	else if(command == "B")
		goBack();
	else if(command == "L")
		goLeft();
	else if(command == "R")
		goRight();
	else if(command == "I")
		goAheadRight();
	else if(command == "G")
		goAheadLeft();
	else if(command == "J")
		goBackRight();
	else if(command == "H")
		goBackLeft();
	else if(command == "0")
		dutyCycle = 165;
	else if(command == "1")
		dutyCycle = 175;
	else if(command == "2")
		dutyCycle = 185;
	else if(command == "3")
		dutyCycle = 195;
	else if(command == "4")
		dutyCycle = 205;
	else if(command == "5")
		dutyCycle = 215;
	else if(command == "6")
		dutyCycle = 225;
	else if(command == "7")
		dutyCycle = 235;
	else if(command == "8")
		dutyCycle = 245;
	else if(command == "9")
		dutyCycle = 255;
	else if(command == "S")
		stopRobot();
  command = "";
}
