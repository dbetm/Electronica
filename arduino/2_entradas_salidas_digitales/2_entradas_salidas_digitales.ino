void setup() {
  // Pin 2 como entrada y pin 3 como salid
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // Se evalúa si la entrada está a nivel alto
  if(digitalRead(2) == HIGH) {
    // Se enciende el led
    digitalWrite(3, HIGH);
  }
  else {
    // Se apaga el led
    digitalWrite(3, LOW);
  }
}
