

// Definir os pinos do sensor, do ventilador e do sensor de RPM
const int sensorPin = A0;
const int fanPin = 9;
const int rpmPin = 2;
const int resistorPin = 6;

// Função para ler a temperatura do sensor LM35
float readTemperature() {
  int sensorValue = analogRead(sensorPin);   // Lê o valor analógico do sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Converte para tensão
  float temperatureC = voltage * 100;       // Converte tensão para temperatura em Celsius (LM35)
  return temperatureC;
}

// Função para mapear a temperatura para o valor de PWM
int mapTemperatureToPWM(float temperature) {
  // Define os limites de temperatura
  float minTemp = 15.0; // Temperatura mínima para ligar o ventilador
  float maxTemp = 18.0; // Temperatura máxima para PWM 255

  // Mapeia a temperatura para o intervalo de 0 a 255
  int pwmValue = map(temperature, minTemp, maxTemp, 0, 255);
  
  // Garante que o valor de PWM esteja no intervalo permitido
  pwmValue = constrain(pwmValue, 0, 255);

  return pwmValue;
}

// Função para definir manualmente o PWM baseado na temperatura
int pwmmanual(float temperature) {
  int pwmValue;

  if (temperature >= 23) {
    pwmValue = 0;
  } else if (temperature >=21 && temperature < 23) {
    pwmValue = 125;
  } else if (temperature <21){
    pwmValue = 255; // Pode ajustar conforme necessário
  }

  return pwmValue;
}

void setup() {
  // Inicia a comunicação serial
  Serial.begin(9600);



  // Define o pino do ventilador como saída
  pinMode(fanPin, OUTPUT);

  // Define o pino do sensor de RPM como entrada
  pinMode(rpmPin, INPUT_PULLUP);
}

void loop() {
  // Lê a temperatura atual
  float temperature = readTemperature();

  // Converte a temperatura para um valor de PWM


  //int pwmValue = mapTemperatureToPWM(temperature);
  int pwmValue = pwmmanual(255);

  // Define o PWM do ventilador
  analogWrite(fanPin, pwmValue);
  analogWrite(resistorPin, 255);
  // Obtém a velocidade do ventilador em RPM



  // Imprime a temperatura no console serial

  Serial.println(temperature);


  // Espera um pouco antes da próxima leitura
  delay(1000);
}
