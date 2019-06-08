#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

float tiempo, distancia;

void setup() {
  pinMode(9, OUTPUT); // Trigger
  pinMode(13, OUTPUT); // Led rojo
  pinMode(10, INPUT);  // Echo
  Serial.begin(9600);
  lcd.begin(16, 2);
  
}

void loop() {
  digitalWrite(9, LOW);
  delayMicroseconds(5);
  digitalWrite(9, HIGH);
  delayMicroseconds(12);
  digitalWrite(9, LOW);

  tiempo = pulseIn(10, HIGH);
  //Serial.print("Tiempo" );
  //Serial.println(tiempo);
  //delay(1000);
  // Para obtener la distancia en cm
  distancia = (34000) * (tiempo / 1000000);
  Serial.println("Distancia: "); 
  lcd.print("Distancia: ");
  lcd.setCursor(0,8);
  if (distancia / 2 < 3 || distancia / 2 > 350) { // - 2.5 cm < d < 350 cm
    Serial.println("Fuera de rango");
    lcd.print(" Fuera de rango"); // Se escribe en el display
    digitalWrite(13, HIGH);
  }
  else {
    //lcd.print(" Distancia");
    lcd.print(distancia / 2);
    lcd.print(" cm");
    digitalWrite(13, LOW);
  }
  Serial.println(distancia / 2);
  delay(1000);
  lcd.clear();

  //Serial.print("Velocidad ");
  //Serial.println(52 / (tiempo / 1000000));

}
