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


    
void setup()
{
Serial.begin(9600);
pinMode(esquerda, INPUT);
pinMode(direita, INPUT);
pinMode(trigger, OUTPUT);
pinMode(echo, INPUT);
pinMode(power, INPUT);

}

void loop()
{
  estado_power = digitalRead(power);
  if(estado_power == HIGH){
    digitalWrite(trigger,LOW);
    delayMicroseconds(5);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);

    dist = pulseIn(echo,HIGH);
    dist = dist/58;

    if(dist <= 50){
      potValor = analogRead(potPin);
      int receivedSpeed = map(potValor, 0, 1023, 0, 100);  
      Serial.println(receivedSpeed);
      delay(100);

        estado_esquerdo = digitalRead(esquerda);
      if (estado_esquerdo == LOW) {
      digitalWrite(led_esquerdo, LOW);
      }else{
      
      digitalWrite(led_esquerdo, HIGH);
      Serial.println("esquerda_apertada");
      }

        estado_direito = digitalRead(direita);
      if (estado_direito == LOW) {
        digitalWrite(led_direito, LOW);

      }else{
      digitalWrite(led_direito, HIGH);
      Serial.println("direita_apertada");
      }
    }else{
      Serial.println("bluetooth_desconectado");
    }

  }else{
    digitalWrite(led_direito, HIGH);
    digitalWrite(led_esquerdo, HIGH);
    delay(1000);
    digitalWrite(led_direito, LOW);
    digitalWrite(led_esquerdo, LOW);
    delay(1000);

  }



    



}