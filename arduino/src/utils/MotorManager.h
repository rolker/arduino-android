/*
 * MotorManager.h
 *
 *  Created on: Jan 5, 2013
 *      Author: roland
 */

#ifndef MOTORMANAGER_H_
#define MOTORMANAGER_H_

#include <Arduino.h>
#include <MotorShield.h>


class MotorManager{
	MS_DCMotor _motor;
	uint8_t _speed;
	uint8_t _current_speed;

	// helper function to print the motor's states in human-readable strings.
	String decodeState(unsigned char state) {
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

public:
	MotorManager(uint8_t motor):_motor(motor),_speed(0),_current_speed(0){

	}

	String getStatusString() {
	    String result = "";
	    result += _speed;
	    result += " ";
	    result += decodeState(_motor.getState());
	    result += " ";
	    result += decodeState(_motor.getDirection());
	    result += " ";
	    char temp[10];
	    dtostrf(_motor.getCurrentAmps(),2,3,temp);
	    result += temp;
	    result += "A ";
	    dtostrf(_motor.getCurrentVoltage(),2,3,temp);
	    result += temp;
	    result += "V";

	    return result;
	}

	void setSpeed(uint8_t speed){
		_motor.setSpeed(speed);
		_speed = speed;
	}

	void setReverse(bool r = true){
		if(r)
			_motor.run(BACKWARD);
		else
			_motor.run(FORWARD);
		_current_speed = 0;
	}

	void setBrake(bool b = true){
		if(b)
			_motor.run(BRAKE);
		else
			_motor.run(RELEASE);
		_current_speed = 0;
	}

	void loop(unsigned long timestamp){
		if(_current_speed != _speed){
			if(_current_speed > _speed)
				_current_speed = _speed;
			else
				++_current_speed;
			//_motor.setSpeed(_current_speed);
			//Serial.println(_current_speed);
		}
	}

};

class MotorPair{
	MotorManager _a;
	MotorManager _b;

public:
	MotorPair():_a(MOTOR_A),_b(MOTOR_B){

	}

	String getStatusString() {
	    String result = "a:";
	    result += _a.getStatusString();
	    result += "\tb:";
	    result += _b.getStatusString();
	    return result;
	}

	void setSpeeds(uint8_t sa, uint8_t sb){
		_a.setSpeed(sa);
		_b.setSpeed(sb);
	}

	void setReverses(bool ra, bool rb){
		_a.setReverse(ra);
		_b.setReverse(rb);
	}

	void setBrakes(bool ba, bool bb){
		_a.setBrake(ba);
		_b.setBrake(bb);
	}

	void loop(unsigned long timestamp){
		_a.loop(timestamp);
		_b.loop(timestamp);
	}

};

#endif /* MOTORMANAGER_H_ */

