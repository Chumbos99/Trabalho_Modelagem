#include <PID_v1.h>

// Define os pinos utilizados
const int sensorPin = A0; // Pino do sensor de temperatura
const int resPIN = 6; // Pino de controle (PWM) da potencia da resistencia
const int fanPin = 9; // Pino de controle (PWM) para a ventoinha

// Variáveis de controle PID
double setpoint = 35.0; // Temperatura desejada que sistema foi escolhido para estabilizar
double input = 0.0; // Varaivel para salvar o valor lido pelo sensor
double output = 0.0; // Saída do controle PID(PWM)

// Parâmetros PID
double Kp = 70.0; 
double Ki = 10.0; 
double Kd = 1.0; 

// Cria o objeto PID
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, REVERSE); // Inverte a ação do PID para ele apenas acionar quanto estiver acima do setpoint

// Função para ler a temperatura do sensor LM35
float readTemperature() {
  int sensorValue = analogRead(sensorPin);   // Lê o valor analógico do sensor na porta A0
  float voltage = sensorValue * (5.0 / 1023.0); // Converte para tensão
  float temperatureC = voltage * 100;       // Converte tensão para temperatura em Celsius (LM35)
  return temperatureC;
}

void setup() {
  // Inicializar a comunicação serial
  Serial.begin(9600);

  // Configuração os pinos
  pinMode(sensorPin, INPUT);
  pinMode(resPIN, OUTPUT);
  pinMode(fanPin, OUTPUT);

  // Inicializa o PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255); // Limita a saida do PID para PWM
}

void loop() {
  // Lê a temperatura atual do sensor
  input = readTemperature();

  // Calcula a saída PID
  myPID.Compute();

  // Define a potência da resistência como constante (máxima)
  analogWrite(resPIN, 255);

  // Aplica a saída do PID ao pino de controle da ventoinha (PWM)
  analogWrite(fanPin, output);

  // Imprime os valores para monitoramento
  Serial.print("Setpoint: ");
  Serial.print(setpoint);
  /*Serial.print(" Input: ");
  Serial.print(input);*/
  Serial.print(" Output: ");
  Serial.print(output);
  Serial.print(" Temperature: ");
  Serial.println(input);

  
  delay(1000);//delay de 1s para cada interação
}
