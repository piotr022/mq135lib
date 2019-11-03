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

#include "mq135.h"

Mq135::Mq135(int pin, int ave, byte adcBits, float voltage)
:_pin(pin),_ave(ave),_adcBits(adcBits),_voltage(voltage),
_cPPM(0),_RL(1)  {}

void Mq135::setRL(float RL)
{
  _RL = RL;
}

void Mq135::setR0(float R0)
{
  _R0 = R0;
}


float Mq135::adcAverage()
{
  float a=0;
  for(int i=0;i<_ave;i++)
  {
    a += analogRead(_pin);
  //  delay(2);
  }
  return a/_ave;
}

float Mq135::getResistance()  //voltage divider pattern
{
  return ((5.0/((adcAverage()/((pow(2,_adcBits)-1)))*_voltage)-1.0)*_RL);
}

float Mq135::calibrate(int cPPM)
                    //this is not required if gas concentration = 0ppm on program startup

{                   //calibration with real gas concentration in the air
  _cPPM = cPPM;     //to check real concentration use other calibrated sensor
  _R0 = getResistance()*pow((_cPPM/aBezneze),(1.0/-bBenzene));
  return _R0;
}

double Mq135::getPPM()
{
  return aBezneze * pow((getResistance()/_R0), bBenzene);
}


float Mq135::getCorrection(float t, float h)
{
  return aCor * t * t - bCor * t + cCor - (h-33.)*dCor;
}

double Mq135::getCorrectedPPM(float t, float h)
{
  return aBezneze * pow(((getResistance()/getCorrection(t,h))/_R0), bBenzene);
}
