//#include <Servo.h>

//Servo meuServo;

//void setup() {
  //meuServo.attach(8);  // Conecta o servo ao pino 8
//}

//void loop() {
  //meuServo.write(0);   // Move o servo para a posição 0
  //delay(1000);         // Espera 1 segundo
  //meuServo.write(90);  // Move o servo para a posição 90
  //delay(1000);         // Espera 1 segundo
//}

#include <Servo.h>

Servo meuServo;

const int servoPin = 8;
const int delayTime = 1000; // Atraso para dar tempo de o servo se mover

void setup() {
  Serial.begin(9600);  // Inicializa comunicação serial
  meuServo.write(45);
  meuServo.attach(servoPin);  // Conecta o servo ao pino 8
}

void loop() {
  if (Serial.available()) {
    String material = Serial.readStringUntil('\n');  // Lê a string até a quebra de linha
    Serial.print("Comando recebido: ");  // Log para verificar o que foi lido
    Serial.println(material); 

    if (material == "p") {
      Serial.println("Movendo para posição de PAPEL");
      meuServo.write(0);  // Posição para PAPEL
      delay(delayTime);    // Atraso para dar tempo ao servo
    } else if (material == "t") {
      Serial.println("Movendo para posição de PLÁSTICO");
      meuServo.write(90);  // Posição para PLÁSTICO
      delay(delayTime);    // Atraso para dar tempo ao servo
    } else {
       meuServo.write(180);
      Serial.println("Comando desconhecido.");
    }
  }
}
