//Definição dos pinos
#define resistor    5
#define cooler      6
#define sensor 0
#define pot1 1
#define pot2 2

//Variáveis
float erro, kp, setpoint;
float p;

void setup() {

  Serial.begin(2000000);

  pinMode(resistor, OUTPUT);
  pinMode(cooler, OUTPUT);

  analogWrite(resistor, 0);
  analogWrite(cooler, 0);

  kp = 50;
  setpoint = 40;
}


void loop() {

  float temperatura = 0;

  temperatura = medir_temperatura();

  erro = setpoint - temperatura;//calcula o erro

  p = kp * erro;//calcula a ação de controle

  if (p >= 255) {//limita o valor do sinal de controle
    p = 255;
  }
  if (p <= 0) {
    p = 0;
  }

  analogWrite(resistor, (int)p);//seta potência do resistor
  
  analogWrite(cooler, map(analogRead(pot2), 0, 1023, 0, 255));//Controla o cooler a partir do potenciômetro

  Serial.println(temperatura);
  delay(50);

}



float medir_temperatura() {
  float temperatura = 0;

  for (int x = 0; x < 200; x++) {
    temperatura = temperatura + analogRead(sensor);
  }
  temperatura = temperatura / 200.0;
  temperatura = temperatura * 0.48875;

  return temperatura;
}
