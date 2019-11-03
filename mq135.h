/*
mq135lib, library to read ppm values of Benzene concentration from analog MQ-135 gas sensor

Copyright (C) 2019  Piotr Lewandowski < plewandowski012@gmail.com >

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#include "Arduino.h"

const float aBezneze = 23.4461175;
const float bBenzene = -3.98724605;
const float aCor = 0.00035;
const float bCor = 0.02718;
const float cCor = 1.39538;
const float dCor = 0.0018;

class Mq135{
private:
	int _pin, _ave;
	byte _adcBits;
	float _R0, _R, _voltage, _RL;
	unsigned int _cPPM;

  float adcAverage();
	float getResistance();
	float getCorrection(float, float);
public:
	//for arduino uno/nano ADC is 10bit with 5v reference (default)
	//for bluepill on stm32 ADC is 12 bit with 3.3v reference (can be set in constructor)
	//defaults are loaded for arduino
	Mq135(int,int=30,byte=10,float=5.0);
	void setRL(float);
	void setR0(float);
	float calibrate(int);
  double getPPM();
	double getCorrectedPPM(float,float);


};
