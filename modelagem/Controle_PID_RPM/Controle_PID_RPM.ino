#include <FanMonitor.h>
#include <PID_v1.h>

// Definir os pinos do ventilador e do sensor de RPM
const int fanPin = 9;//Pino do PWM da ventuinha
const int rpmPin = 8;//Pino do tacoemtro da ventuinha

FanMonitor _fanMonitor = FanMonitor(rpmPin, FAN_TYPE_BIPOLE);

// Definir o RPM desejado
const uint16_t desiredRPM = 800; // RPM desejado que o sistema deve estabilziar

// Variáveis para o controlador PID
double setpoint;
double input;
double output;

// Coeficientes do controlador PID
double Kp = 2.0;
double Ki = 0.5;
double Kd = 0.1;
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  // Inicializar a comunicação serial
  Serial.begin(9600);

  _fanMonitor.begin();

  // Define o pino do ventilador como saída
  pinMode(fanPin, OUTPUT);

  // Define o pino do sensor de RPM como entrada
  pinMode(rpmPin, INPUT_PULLUP);

  // Configura os parâmetros do PID
  setpoint = desiredRPM;
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255); // Limita a saída do PID para os valores de PWM (0-255)
  
  // Inicializar o ventilador na velocidade máxima
  output = 255;
  analogWrite(fanPin, (int)output);
}

void loop() {
  // Obtém a velocidade do ventilador em RPM
  input = _fanMonitor.getSpeed();

  // Verifica se o valor de RPM lido está dentro do intervalo esperado
  if (input < 0) {
    input = 0;
  } else if (input > 1090) {
    input = 1090;
  }

  // Atualiza o PID
  myPID.Compute();

  // Define o PWM do ventilador com base na saída do PID
  analogWrite(fanPin, (int)output);

  // Imprime o valor de PWM e a velocidade em RPM
  Serial.print("PWM: ");
  Serial.print(output);
  Serial.print(", RPM: ");
  Serial.print(input);
  Serial.print(", Setpoint: ");
  Serial.println(setpoint);

  
  delay(1); // Delay de 1ms
}
