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
