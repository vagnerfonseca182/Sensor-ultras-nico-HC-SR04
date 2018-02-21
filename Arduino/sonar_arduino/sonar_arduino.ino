/**
 * #######################################################################
 * Software Arduino Sonar Monitor
 *
 * alterado por Rodrigues <https://rodriguesfas.github.io>
 * by Dejan Nedelkovski <www.HowToMechatronics.com>  
 *########################################################################
 *Babuino.tec
 *vagnerromari@hotmail.com
 *
 */

 /*Inclue bibliotecas*/
 #include <Servo.h>. 
 #include <NewPing.h>

 #define TRIGGER_PIN  12    /* Arduino pino trigger (envia onda)*/
 #define ECHO_PIN     13   /* Arduino pino echo (recebe onda) */
 #define MAX_distancia 10  /* Distancia máxima do ping em centimetro. */ 

 NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_distancia); /* NewPing configuração de pinos e distancia máxima. */
 int led = 8;
 int distancia;

 Servo myServo; /* Cria um objeto servo para controlar o servo motor. */

/**
 * setup -
 */
 void setup() {
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  Serial.begin(9600); /* Config serial monitor (valor taxa de transmição). */
  myServo.attach(11);  /* Definido no qual pino é o servo motor ligado no arduino. */ 
}


/**
 * loop - 
 */
 void loop() {
  /* faz rotacionar o servo motroe de 15º à 165º graus. */
  for(int i = 15; i <= 165; i++){  
    myServo.write(i);
    delay(30);

    /* chama a função que calcula a sistância medida pelo sensor ultrasônico para cada grau. */
    distancia = calcularPING();

    Serial.print(i);         /* Envia o atual grau na porta serial. */
    Serial.print(",");       /* Envia carácter adicional à direita préximo ao valor anterior necessário mais tarde na IDE Processing  */ 
    Serial.print(distancia);  /* Envia o valor da distância na porta serial. */ 
    Serial.print(".");       /* Envia carácter à direita próximo ao valor anterior necessário mais tarde na IDE processing.*/ 
 if ((distancia <= 10)&&(distancia > 0)){
  digitalWrite(led,LOW);
 }
  else{
    digitalWrite(led,HIGH);  
  }
  }

  /* Repete as linha anteriores de 165º a 15º graus. */
  for(int i = 165; i > 15; i--){
    myServo.write(i);
    delay(30);
    
    distancia = calcularPING();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distancia);
    Serial.print(".");
     if ((distancia <= 10)&&(distancia > 0)){
  digitalWrite(led,LOW);
 }
  else{
    digitalWrite(led,HIGH);  
  }
    
  }

}

/**
 * calcularPING - Função pa calcular a distácia medida pelo sensor ultrasônico..
 */
 int calcularPING(){ 
  unsigned int uS = sonar.ping();  /* Envia ping, retorna ping tempo em microseconds (uS). */
  distancia = uS / US_ROUNDTRIP_CM; /* Converte oing tempo para distancia em cm e retorana resultado. */
  
  return distancia;
}
