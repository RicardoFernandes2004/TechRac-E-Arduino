# TechRac-E-Arduino
TECHRAC-E
Este projeto Arduino lê valores de um potenciômetro para simular a entrada de dados de um sensor EEG, sensores de distância ultrassônicos para simular a distância de um bluetooth e botões, e controla LEDs baseados nesses valores. Ele também envia dados de velocidade e direção lidos do potenciômetro para o monitor serial.

Link do circuito no Wokwi: https://wokwi.com/projects/400341831389162497

Componentes Necessários
Arduino UNO
Potenciômetro
Sensores ultrassônicos
Botões push-button (2)
LEDs (2)
Resistores
Fios jumpers
Protoboard
Conexões
Potenciômetro

Conecte o pino central do potenciômetro ao pino A0 do Arduino.
Conecte os outros dois pinos do potenciômetro ao VCC (5V) e GND.

Sensor Ultrassônico
Trigger -> Pino 11 do Arduino
Echo -> Pino 10 do Arduino
VCC -> 5V
GND -> GND

Botões
Botão Esquerdo: Conecte uma perna ao pino 3 do Arduino e a outra ao GND.
Botão Direito: Conecte uma perna ao pino 2 do Arduino e a outra ao GND.
Power Button: Conecte uma perna ao pino 6 do Arduino e a outra ao GND.
LEDs
LED Esquerdo: Conecte o anodo ao pino 13 do Arduino e o catodo ao GND através de um resistor.
LED Direito: Conecte o anodo ao pino 12 do Arduino e o catodo ao GND através de um resistor.


Código
int potPin = A0;
int potValor = 0;
int estado_esquerdo = 0;
int estado_direito = 0;
int esquerda = 3;
int direita = 2;
int led_direito = 12;
int led_esquerdo = 13;
int trigger = 11;
int echo = 10;
float dist = 0;
int power = 6;
int estado_power = 0;

void setup() {
    Serial.begin(9600);
    pinMode(esquerda, INPUT);
    pinMode(direita, INPUT);
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(power, INPUT);
}

void loop() {
    estado_power = digitalRead(power);
    if (estado_power == HIGH) {
        digitalWrite(trigger, LOW);
        delayMicroseconds(5);
        digitalWrite(trigger, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigger, LOW);

        dist = pulseIn(echo, HIGH);
        dist = dist / 58;

        if (dist <= 50) {
            potValor = analogRead(potPin);
            int receivedSpeed = map(potValor, 0, 1023, 0, 100);  
            Serial.println(receivedSpeed);
            delay(100);

            estado_esquerdo = digitalRead(esquerda);
            if (estado_esquerdo == LOW) {
                digitalWrite(led_esquerdo, LOW);
            } else {
                digitalWrite(led_esquerdo, HIGH);
                Serial.println("esquerda_apertada");
            }

            estado_direito = digitalRead(direita);
            if (estado_direito == LOW) {
                digitalWrite(led_direito, LOW);
            } else {
                digitalWrite(led_direito, HIGH);
                Serial.println("direita_apertada");
            }
        } else {
            Serial.println("bluetooth_desconectado");
        }
    } else {
        digitalWrite(led_direito, HIGH);
        digitalWrite(led_esquerdo, HIGH);
        delay(1000);
        digitalWrite(led_direito, LOW);
        digitalWrite(led_esquerdo, LOW);
        delay(1000);
    }
}

Funcionamento
Leitura do Potenciômetro: O valor do potenciômetro é lido e mapeado para um valor de 0 a 100, que é enviado ao monitor serial.
Sensor Ultrassônico: Mede a distância e verifica se é menor ou igual a 50 cm.
Botões: Lê o estado dos botões esquerdo e direito, acendendo os LEDs correspondentes e enviando mensagens ao monitor serial.
Botão de Energia: Controla o funcionamento geral do sistema. Se o botão estiver pressionado, o sistema mede a distância e processa os botões. Caso contrário, os LEDs piscam indicando que o sistema está em espera.