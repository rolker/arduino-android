#include <Arduino.h>
#include <MotorShield.h>

#include <Max3421e.h>
#include <Usb.h>
#include <AndroidAccessory.h>

extern HardwareSerial Serial;

MS_DCMotor motorA(MOTOR_A);
MS_DCMotor motorB(MOTOR_B);

// helper function to print the motor's states in human-readable strings.
String decodeState(int state) {
    String result = "";
    switch (state) {
        case FORWARD:
            result = "Forward";
            break;
        case BACKWARD:
            result = "Backward";
            break;
        case BRAKE:
            result = "Brake";
            break;
        case RELEASE:
            result = "Release";
            break;
    }
    return result;
}

void PrintMotorState(MS_DCMotor &m, char m_code)
{
	  Serial.print(m_code);
	  Serial.print(" ");
	  Serial.print(decodeState(m.getState()));
	  Serial.print(" ");
	  Serial.print(decodeState(m.getDirection()));
	  Serial.print(" ");
	  Serial.print(m.getCurrentAmps());
	  Serial.print("A ");
	  Serial.print(m.getCurrentVoltage());
	  Serial.println("V");
}

AndroidAccessory acc("Roland Arsenault",
		     "Robot",
		     "Homebuilt robot",
		     "1.0",
		     "https://github.com/rolker/arduino-android",
		     "001");

void setup() {
  Serial.begin(115200);
  Serial.println("setup");

  // engage the motor's brake 
//  motorA.run(BRAKE);
//  motorA.setSpeed(100);
//  motorB.run(BRAKE);
//  motorB.setSpeed(100);

  PrintMotorState(motorA,'A');
  PrintMotorState(motorB,'B');

  acc.powerOn();

  Serial.println("setup done");
}

void loop() {
  Serial.println("loop");
  //PrintMotorState(motorA,'A');
  //PrintMotorState(motorB,'B');

  if (acc.isConnected()) {
	  byte msg[3];
	  int len = acc.read(msg, sizeof(msg), 1);
	  if(len > 0)
	  {
		  Serial.println(len);
	  }
  }
  delay(10);
  // switch directions and engage the brake

}

