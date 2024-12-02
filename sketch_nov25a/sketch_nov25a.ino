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

// #include <Servo.h>

// Servo meuServo;

// const int servoPin = 8;
// const int delayTime = 1000; // Atraso para dar tempo de o servo se mover

// void setup() {
//   Serial.begin(9600);  // Inicializa comunicação serial
//   meuServo.write(45);
//   meuServo.attach(servoPin);  // Conecta o servo ao pino 8
// }

// void loop() {
//   if (Serial.available()) {
//     String material = Serial.readStringUntil('\n');  // Lê a string até a quebra de linha
//     Serial.print("Comando recebido: ");  // Log para verificar o que foi lido
//     Serial.println(material); 

//     if (material == "p") {
//       Serial.println("Movendo para posição de PAPEL");
//       meuServo.write(0);  // Posição para PAPEL
//       delay(delayTime);    // Atraso para dar tempo ao servo
//     } else if (material == "t") {
//       Serial.println("Movendo para posição de PLÁSTICO");
//       meuServo.write(90);  // Posição para PLÁSTICO
//       delay(delayTime);    // Atraso para dar tempo ao servo
//     } else {
//        meuServo.write(180);
//       Serial.println("Comando desconhecido.");
//     }
//   }
// }




// // # código completo

// #include <Servo.h>

// Servo servoEsteira;  // Servo para movimentar o material na esteira
// Servo servoPorta;    // Servo para abrir a porta e liberar o material

// const int servoPinEsteira = 8;  // Pino para o servo da esteira
// const int servoPinPorta = 9;    // Pino para o servo da porta
// const int delayTime = 1000;     // Atraso para dar tempo de o servo se mover

// void setup() {
//   Serial.begin(9600);  // Inicializa comunicação serial
  
//   // Conecta os servos aos pinos
//   servoEsteira.attach(servoPinEsteira);
//   servoPorta.attach(servoPinPorta);
  
//   // Inicializa os servos nas posições iniciais
//   servoEsteira.write(35);  // Posição inicial da esteira
//   servoPorta.write(0);    // Posição inicial da porta (fechada)
  
//   delay(delayTime); // Aguarda o servo ir para a posição inicial
// }

// void loop() {
//   if (Serial.available()) {
//     String material = Serial.readStringUntil('\n');  // Lê a string até a quebra de linha
//     Serial.print("Comando recebido: ");  // Log para verificar o que foi lido
//     Serial.println(material); 

//     if (material == "p") {
//       Serial.println("Movendo para posição de PAPEL");
//       servoEsteira.write(68);  // Posição para PAPEL (ajuste conforme necessário)
//       delay(delayTime);        // Atraso para dar tempo ao servo

//       // Após mover a esteira, abre a porta para liberar o material
//       Serial.println("Abrindo porta para liberar o material");
//       servoPorta.write(90);    // Abre a porta (ajuste conforme necessário)
//       delay(delayTime);        // Espera o tempo necessário

//       // Fecha a porta após liberar o material
//       servoPorta.write(0);     // Fecha a porta
//       delay(delayTime);        // Aguarda o fechamento da porta

//     } else if (material == "t") {
//       Serial.println("Movendo para posição de PLÁSTICO");
//       servoEsteira.write(25);  // Posição para PLÁSTICO (ajuste conforme necessário)
//       delay(delayTime);        // Atraso para dar tempo ao servo

//       // Após mover a esteira, abre a porta para liberar o material
//       Serial.println("Abrindo porta para liberar o material");
//       servoPorta.write(90);    // Abre a porta (ajuste conforme necessário)
//       delay(delayTime);        // Espera o tempo necessário

//       // Fecha a porta após liberar o material
//       servoPorta.write(0);     // Fecha a porta
//       delay(delayTime);        // Aguarda o fechamento da porta

//     } else {
//       Serial.println("Comando desconhecido.");
//     }
//   }
// }

// CÓDIGO NOVO COM ESPACO VAZIO

#include <Servo.h>

Servo servoEsteira;  // Servo para movimentar o material na esteira
Servo servoPorta;    // Servo para abrir a porta e liberar o material

const int servoPinEsteira = 8;  // Pino para o servo da esteira
const int servoPinPorta = 9;    // Pino para o servo da porta
const int delayTime = 1000;     // Atraso para dar tempo de o servo se mover

void setup() {
  Serial.begin(9600);  // Inicializa comunicação serial
  
  // Conecta os servos aos pinos
  servoEsteira.attach(servoPinEsteira);
  servoPorta.attach(servoPinPorta);
  
  // Inicializa os servos nas posições iniciais
  servoEsteira.write(35);  // Posição inicial da esteira
  servoPorta.write(0);    // Posição inicial da porta (fechada)
  
  delay(delayTime); // Aguarda o servo ir para a posição inicial
}

void loop() {
  if (Serial.available()) {
    String material = Serial.readStringUntil('\n');  // Lê a string até a quebra de linha
    Serial.print("Comando recebido: ");  // Log para verificar o que foi lido
    Serial.println(material); 

    if (material == "p") {
      Serial.println("Movendo para posição de PAPEL");
      servoEsteira.write(68);  // Posição para PAPEL (ajuste conforme necessário)
      delay(delayTime);        // Atraso para dar tempo ao servo

      // Após mover a esteira, abre a porta para liberar o material
      Serial.println("Abrindo porta para liberar o material");
      servoPorta.write(90);    // Abre a porta (ajuste conforme necessário)
      delay(delayTime);        // Espera o tempo necessário

      // Fecha a porta após liberar o material
      servoPorta.write(0);     // Fecha a porta
      delay(delayTime);        // Aguarda o fechamento da porta

    } else if (material == "t") {
      Serial.println("Movendo para posição de PLÁSTICO");
      servoEsteira.write(25);  // Posição para PLÁSTICO (ajuste conforme necessário)
      delay(delayTime);        // Atraso para dar tempo ao servo

      // Após mover a esteira, abre a porta para liberar o material
      Serial.println("Abrindo porta para liberar o material");
      servoPorta.write(90);    // Abre a porta (ajuste conforme necessário)
      delay(delayTime);        // Espera o tempo necessário

      // Fecha a porta após liberar o material
      servoPorta.write(0);     // Fecha a porta
      delay(delayTime);        // Aguarda o fechamento da porta

    } else if (material == "v") { // Comando para espaço vazio
      Serial.println("Espaço vazio detectado. Mantendo esteira e porta em posição inicial.");
      servoEsteira.write(35);  // Mantém a esteira na posição inicial
      servoPorta.write(0);     // Mantém a porta fechada
      delay(delayTime);        // Aguarda para evitar ações repetitivas

    } else {
      Serial.println("Comando desconhecido.");
    }
  }
}

