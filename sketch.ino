#include <Arduino.h>

// Pins
const int CombustivelSensorPin = 32;   // Potenciometro para combustivel
const int inputSensorPin = 33; // Potenciometro para input
const int AguaSensorPin = 34; // Potenciometro para agua
const int startButtonPin = 18; // Button for starting the system

// Constantes
const int maxADC = 4095;
const int VelocidadeTrator = 10; // Velocidade do Trator em km/h

// Funcao para ler sensor e converter em porcentagem
float readSensor(int pin) {
  int value = analogRead(pin);
  return ((float)value / maxADC) * 100;
}

// Funcao para calculo dos recursos
void calculoUso(float velocidade, float combustivel, float input, float agua) {
  float CombustivelUso = velocidade * (combustivel / 100) * 0.1;
  float InputUso = velocidade * (input / 100) * 0.05;
  float AguaUso= velocidade * (agua / 100) * 0.07;

  // Display dos diferentes niveis e % de uso
  Serial.print("Nivel de Combustivel: ");
  Serial.print(combustivel, 2);
  Serial.print("% | Uso: ");
  Serial.print(CombustivelUso, 2);
  Serial.println("%");

  Serial.print("Nivel de Input Agricula: ");
  Serial.print(input, 2);
  Serial.print("% | Uso: ");
  Serial.print(InputUso, 2);
  Serial.println("%");

  Serial.print("Nivel de Agua: ");
  Serial.print(agua, 2);
  Serial.print("% | Uso: ");
  Serial.print(AguaUso, 2);
  Serial.println("%\n");

  // check para ver se o nivel estiver baixo
  if (combustivel < 10) Serial.println("Aviso: Combustivel Baixo!");
  if (input < 10) Serial.println("Aviso: Nivel de Input Agricultural Baixo!");
  if (agua < 10) Serial.println("Aviso: Nivel de Agua baixo!");
}

void setup() {
  Serial.begin(115200);

  // Inicializacao do botao
  pinMode(startButtonPin, INPUT_PULLUP);
}

void loop() {
  // Esperamos para o botao ser pressionado
  if (digitalRead(startButtonPin) == LOW) {
    Serial.println("\n Monitorando Recursos...\n");

    while (true) { // Loop Monitoramento
      float NivelCombustivel = readSensor(CombustivelSensorPin);
      float NivelInput = readSensor(inputSensorPin);
      float NivelAgua = readSensor(AguaSensorPin );

      calculoUso(VelocidadeTrator, NivelCombustivel, NivelInput, NivelAgua);

      delay(2000);//delay de 2 segundos
    }
  }
}