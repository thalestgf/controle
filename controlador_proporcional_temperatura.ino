//Define os pinos utilizados
#define resistor 5 //Pino do resistor
#define cooler 6 //Pino do cooler
#define sensor 0 //Pino do sensor de temperatura
#define pot1 1 //Pino do primeiro potenciômetro
#define pot2 2 //Pino do segundo potenciômetro

//Variáveis
float erro, kp, setpoint; //Variáveis para o cálculo do erro e da ação de controle
float p; //Variável para a potência a ser aplicada no resistor

void setup() {
  //Inicializa a comunicação serial
  Serial.begin(2000000);

  //Define os pinos como saídas
  pinMode(resistor, OUTPUT);
  pinMode(cooler, OUTPUT);

  //Inicializa a saída dos pinos com 0
  analogWrite(resistor, 0);
  analogWrite(cooler, 0);

  //Define o ganho proporcional (kp) e o setpoint (valor alvo)
  kp = 50;
  setpoint = 40;
}

void loop() {
  float temperatura = 0; //Variável para armazenar a temperatura medida

  temperatura = medir_temperatura(); //Chama a função para medir a temperatura

  erro = setpoint - temperatura; //Calcula o erro entre o setpoint e a temperatura medida

  p = kp * erro; //Calcula a ação de controle

  //Limita o valor máximo e mínimo do sinal de controle
  if (p >= 255) {
    p = 255;
  }
  if (p <= 0) {
    p = 0;
  }

  //Aplica a potência no resistor
  analogWrite(resistor, (int)p);

  //Controla o cooler a partir do potenciômetro
  analogWrite(cooler, map(analogRead(pot2), 0, 1023, 0, 255));

  //Imprime a temperatura medida na comunicação serial
  Serial.println(temperatura);
  delay(50); //Espera 50 milissegundos antes de repetir o loop
}

//Função para medir a temperatura
float medir_temperatura() {
  float temperatura = 0; //Variável para armazenar a temperatura medida

  //Faz 200 leituras de temperatura e armazena na variável temperatura
  for (int x = 0; x < 200; x++) {
    temperatura = temperatura + analogRead(sensor);
  }

  //Calcula a média das 200 leituras de temperatura
  temperatura = temperatura / 200.0;

  //Converte a leitura do sensor para temperatura
  temperatura = temperatura * 0.48875;

  return temperatura; //Retorna a temperatur
}
