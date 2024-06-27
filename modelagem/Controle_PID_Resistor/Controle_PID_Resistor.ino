#include <PID_v1.h>

// Define os pinos utilizados
const int sensorPin = A0; // Pino do sensor de temperatura
const int resPin = 6; // Pino de controle do PWM para a potencia entregue ao resistor

// Variáveis de controle PID
double setpoint = 40.0; // Temperatura que o sistema deve estabilizar
double input = 0.0; // Valor lido do sensor de temperatura
double output = 0.0; // Saída do controle PID (PWM)

// Parâmetros PID (tentativa e erro)
double Kp =70.0;
double Ki = 20.0;
double Kd = 5.0;
// Parâmetros PI (lugar das raizes)
/*double Kp =1.4811;
double Ki = 0.14811;
double Kd = 0.0;*/

// Cria o objeto PID
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);


// Função para ler a temperatura do sensor LM35
float readTemperature() {
  int sensorValue = analogRead(sensorPin);   // Lê o valor analógico do sensor
  float voltage = sensorValue * (5.0 / 1023.0); // Converte para tensão
  float temperatureC = voltage * 100;       // Converte tensão para temperatura em Celsius (LM35)
  return temperatureC;
}

void setup() {
  // Inicializar a comunicação serial
  Serial.begin(9600);

  // Configuração dos pinos
  pinMode(sensorPin, INPUT);
  pinMode(resPin, OUTPUT);

  // Inicializa o PID
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255); // Limites da saída PWM
}

void loop() {
  // Lê a temperatura atual do sensor
  input = readTemperature();

  // Calcula a saída PID
  myPID.Compute();

  // Aplica a saída ao pino de controle (PWM)
  analogWrite(resPin, output);

  // Imprime os valores para monitoramento
  Serial.print("Setpoint: ");
  Serial.print(setpoint);
  /*Serial.print(" Input: ");
  Serial.print(input);*/
  Serial.print(" Output: ");
  Serial.print(output);
  Serial.print(" Temperature: ");
  Serial.println(input);

  //Dealy de 1s ate a proxima interação
  delay(1000);
}
