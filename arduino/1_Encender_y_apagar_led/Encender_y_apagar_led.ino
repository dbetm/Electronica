void setup() {
  /* el pin 13 es al cual está conectado el
  led interno de la placa */
  pinMode(13, OUTPUT);
}

void loop() {
  // Escribimos un 1 para encender el led por un segundo
  digitalWrite(13, HIGH);
  // Retardo de un segundo
  delay(1000);
  // Apagamos el led
  digitalWrite(13, LOW);
  delay(1000);
}


