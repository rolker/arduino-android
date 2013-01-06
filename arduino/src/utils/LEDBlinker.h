/*
 * LEDBlinker.h
 *
 *  Created on: Jan 5, 2013
 *      Author: roland
 */

#ifndef LEDBLINKER_H_
#define LEDBLINKER_H_

#include <Arduino.h>

class LEDBlinker
{
	int _ledPin;
	unsigned long _timeLengths[2];

	bool _active;
	bool _state;
	unsigned long _lastStateChange;

public:
	struct TimeLengths{
		unsigned int _on;
		unsigned int _off;
		TimeLengths(unsigned int on, unsigned int off):_on(on),_off(off){}
	};

	LEDBlinker(int ledPin=13):_ledPin(ledPin),_timeLengths{500,500},_active(false),_state(LOW),_lastStateChange(0){

	}

	~LEDBlinker(){
		digitalWrite(_ledPin, LOW);
	}

	bool setup(){
		pinMode(_ledPin, OUTPUT);
		return true;
	}

	void loop(unsigned long timestamp){
		if(_active){
			unsigned long elapsed;

			// detect clock overflow
			if(timestamp < _lastStateChange){
				elapsed = 0xffffffffUL - _lastStateChange + timestamp;
			}
			else {
				elapsed = timestamp - _lastStateChange;
			}

			if(elapsed < _timeLengths[_state])
				return;

			_state = !_state;
			if (_timeLengths[_state]==0)
				_state = !_state;
			digitalWrite(_ledPin, _state);
			_lastStateChange = timestamp;
		}
	}

	void setTimes(unsigned int onTime, unsigned int offTime)
	{
		_timeLengths[HIGH] = onTime;
		_timeLengths[LOW] = offTime;
	}

	void setTimes(const TimeLengths &tl){
		setTimes(tl._on,tl._off);
	}

	void setActive(bool active=true)
	{
		_active = active;
		_state = active;
		digitalWrite(_ledPin, _state);
		_lastStateChange = millis();
	}
};



#endif /* LEDBLINKER_H_ */
