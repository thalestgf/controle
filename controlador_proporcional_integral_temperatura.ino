#include <TimerOne.h>

#define resistor    5
#define cooler      6
#define sensor 0
#define pot1 1
#define pot2 2

//Variáveis
float erro, kp, ki, setpoint;
float p, i = 0, controle;

int tempo = 0;

#define ts 0.005


float temperatura = 0;

void setup() {

  Serial.begin(2000000);

  pinMode(resistor, OUTPUT);
  pinMode(cooler, OUTPUT);

  analogWrite(resistor, 0);
  analogWrite(cooler, 0);

  kp = 20;
  ki = 0.04;
  setpoint = 40;


  Timer1.initialize(ts * 1000000);
  Timer1.attachInterrupt(reset_tempo);

}


void loop() {

  Serial.println(medir_temperatura());

  for (int x = 0; x < 10; x++) {
    int potenciometro = 0;
    for (int x = 0; x < 20; x++) {
      potenciometro = potenciometro + analogRead(pot2);
    }
    potenciometro = potenciometro / 20.0;
    //Serial.println((int)(potenciometro * (70.0 / 1023.0)));
    analogWrite(cooler, (int)(potenciometro * (70.0 / 1023.0)));
    delay(100);
  }
}



float medir_temperatura() {
  float temperatura = 0;

  for (int x = 0; x < 20; x++) {
    temperatura = temperatura + analogRead(sensor);
  }
  temperatura = temperatura / 20.0;
  temperatura = temperatura * 0.48875;

  return temperatura;
}



void reset_tempo() {

  temperatura = medir_temperatura();
  erro = setpoint - temperatura;

  p = kp * erro;
  i = i + (ki * erro * ts);

  if (i >= 255) {
    i = 255;
  }
  if (i <= -255) {
    i = -255;
  }

  controle = p + i;

  if (controle >= 255) {
    controle = 255;
  }
  if (controle <= 0) {
    controle = 0;
  }

  analogWrite(resistor, (int)controle);
}
