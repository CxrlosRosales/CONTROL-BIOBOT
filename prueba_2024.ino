//LIBRERIAS
#include <Servo.h>

// PUENTE H (DERECHO)
int r_en = 2;
int l_en = 3;
int r_pwm = 5;
int l_pwm = 6;
// PUENTE H (IZQUIERDO)
int r2_en = 7;
int l2_en = 8;
int r2_pwm = 9;
int l2_pwm = 10;
// SENSOR ULTRASONICO
int trigPin = 11;
int echoPin = 12;
// SERVOMOTOR
Servo servo;
int servoPin = 13;

// BUZZER
int buzzerPin = 22; // Ahora el buzzer está conectado al pin 22 del Arduino Mega

long duration;
int distance;
bool obstacleDetected = false; // Variable para controlar el estado del buzzer

void setup() {
  pinMode(r_en, OUTPUT);
  pinMode(l_en, OUTPUT);
  pinMode(r_pwm, OUTPUT);
  pinMode(l_pwm, OUTPUT);
  pinMode(r2_en, OUTPUT);
  pinMode(l2_en, OUTPUT);
  pinMode(r2_pwm, OUTPUT);
  pinMode(l2_pwm, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT); // Configura el pin del buzzer como salida

  servo.attach(servoPin);
  servo.write(90); // Inicializa el servo en el centro

  // Activa ambos puentes H para movimiento hacia adelante
  digitalWrite(r_en, HIGH);
  digitalWrite(l_en, HIGH);
  digitalWrite(r2_en, HIGH);
  digitalWrite(l2_en, HIGH);
}

void loop() {
  // Mide la distancia con el sensor ultrasónico
  distance = measureDistance();

  if (distance > 0 && distance <= 40) { // Si la distancia es válida y menor o igual a 40 cm
    if (!obstacleDetected) { // Verifica si el obstáculo fue detectado por primera vez
      digitalWrite(buzzerPin, HIGH); // Activa el buzzer
      delay(100); // Hace sonar el buzzer por un breve momento
      digitalWrite(buzzerPin, LOW);  // Apaga el buzzer
      obstacleDetected = true; // Marca que se detectó el obstáculo
    }
    stopMotors();
    delay(2500); // Pausa por medio segundo

    // Retrocede durante 1.5 segundos
    moveBackward();
    delay(100); // Retrocede por 1.5 segundos
    stopMotors(); // Detener después de retroceder

    // Gira el servo a la izquierda y derecha para determinar hacia dónde girar
    int leftDistance = checkSide(0);  // Verifica a la izquierda
    int rightDistance = checkSide(180); // Verifica a la derecha

    // Decide hacia dónde girar basándose en las distancias
    if (leftDistance > rightDistance) {
      turnLeft();
    } else {
      turnRight();
    }

    delay(3500); // Gira por un segundo
    servo.write(90); // Restablece el servo al centro
    moveForward(); // Continua moviéndose hacia adelante
  } else {
    obstacleDetected = false; // Reinicia el estado del obstáculo si no hay nada detectado
    moveForward(); // Si no hay obstáculos, sigue adelante
  }
}

int measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // Tiempo límite de espera de 30ms
  return duration * 0.034 / 2; // Calcula la distancia en cm
}

int checkSide(int angle) {
  servo.write(angle);
  delay(500); // Pausa para estabilizar la lectura
  return measureDistance(); // Mide la distancia en esa dirección
}

void stopMotors() {
  analogWrite(r_pwm, 0);
  analogWrite(l_pwm, 0);
  analogWrite(r2_pwm, 0);
  analogWrite(l2_pwm, 0);
}

void moveForward() {
  analogWrite(r_pwm, 0);    // Cambia el sentido del motor derecho
  analogWrite(l_pwm, 255);  // Motor derecho a velocidad máxima
  analogWrite(r2_pwm, 90); // Motor derecho a velocidad máxima
  analogWrite(l2_pwm, 0);   // Motor izquierdo
}

// Nueva función para retroceder
void moveBackward() {
  analogWrite(r_pwm, 100);  // Retrocede motor derecho
  analogWrite(l_pwm, 0);     // Retrocede motor izquierdo
  analogWrite(r2_pwm, 0);    // Retrocede motor derecho
  analogWrite(l2_pwm, 100);  // Retrocede motor izquierdo
}

void turnLeft() {
  analogWrite(r_pwm, 100);
  analogWrite(l_pwm, 0);
  analogWrite(r2_pwm, 100);
  analogWrite(l2_pwm, 0);
}

void turnRight() {
  analogWrite(r_pwm, 0);
  analogWrite(l_pwm, 100);
  analogWrite(r2_pwm, 0);
  analogWrite(l2_pwm, 100);
}
