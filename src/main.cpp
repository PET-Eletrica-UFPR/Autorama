#include <Arduino.h>
#include "LiquidCrystal.h"

// D0 - RX
// D1 - TX
// D3 - PWM
// D5 - PWM
// D6 - PWM
// D7 - PWM
// D10 - PWM
// D11 - PWM

float combustivel1;
float combustivel2;
int count_lap1;
int count_lap2;

int velocidade(float, int, bool);

float gas_level(int, float);

void print();

void setup()
{
  // put your setup code here, to run once:
  pinMode(2, INPUT);     // Pedal 1
  pinMode(4, INPUT);     // Pedal 2
  pinMode(A0, INPUT);    // Controle de velocidade 1
  pinMode(A1, OUTPUT);   // Controle de velocidade 2
  pinMode(3, OUTPUT);    // Seta velocidade 1
  pinMode(5, OUTPUT);    // Seta velocidade 2
  combustivel1 = 100.00; // Nivel de combustivel 1
  combustivel2 = 100.00; // Nivel de combustivel 2
  count_lap1 = 0;        // contador de voltas 1
  count_lap2 = 0;        // contador de voltas 2
}

void loop()
{
  // put your main code here, to run repeatedly:
  int divisor1 = analogRead(A0);
  int divisor2 = analogRead(A1);

  bool pedal1 = digitalRead(2);
  bool pedal2 = digitalRead(4);

  int spd1 = velocidade(combustivel1, divisor1, pedal1);
  int spd2 = velocidade(combustivel2, divisor2, pedal2);

  combustivel1 = gas_level(spd1, combustivel1);
  combustivel2 = gas_level(spd2, combustivel2);

  analogWrite(3, spd1);
  analogWrite(5, spd2);

  
}
int velocidade(float gas, int divisor, bool pedal)
{
  int PWM;
  if (pedal)
  {
    if (gas > 0)
    {
      PWM = map(divisor, 0, 1023, 0, 255);
    }
    else
    {
      PWM = 0;
      delay(5000);
      gas = 50;
    }
  }
  else
  {
    PWM = 0;
  }

  return PWM;
}

float gas_level(int speed, float combustivel)
{ int i = 0;
  float consumo = map(speed, 0, 255, 0, 1);
  if(i > 10000000){
    combustivel -= consumo;
    i = 0;
  }
  return combustivel; 
}
