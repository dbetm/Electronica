int tonoInputPin = 0;
int volumenInputPin = 1;
int volumenOutputPin = 6;

// Se define un arreglo con valores que tomaría una señal senoidal.
//int sin16[] = {18, 1, 12, 13, 12, 11, 8, 6, 4, 6, 5, 3, 2, 2, 6, 7, 12, 19, 4, 0, 2, 5, 9, 3, 2, 4, 6, 7, 2, 4, 14};
//int sin16[] = {10, 11, 13, 16, 17, 18, 20, 17, 18, 20, 17, 14, 12, 10, 8, 6, 5, 2, 1, 0, 0, 1, 3, 6, 8, 9, 11, 14, 16, 17, 20};
//int sin16[] = {7, 8, 10, 11, 12, 13, 14, 14, 15, 14, 14, 13, 12, 11, 10, 8, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6};
int sin64[] = {7, 8, 10, 11, 12, 13, 14, 14, 15, 14, 14, 13, 12, 11, 10, 8, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6,
7, 8, 10, 11, 12, 13, 14, 14, 15, 14, 14, 13, 12, 11, 10, 8, 7, 6, 4, 3, 2, 1, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6};
//int sin16[] = {12, 8, 4, 1, 3, 12, 8, 4, 1, 3, 12, 8, 4, 1, 3, 12, 8, 4, 1, 12, 8, 4, 1, 3, 12, 8, 4, 1, 3, 12, 8, 4};


int cont = 0;
void setup() {
  Serial.begin(9600);
  pinMode(tonoInputPin, INPUT);
  pinMode(volumenInputPin, INPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(volumenOutputPin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  int retardoTono = map(analogRead(tonoInputPin), 0, 1023, 10, 80);
  int volumen = map(analogRead(volumenInputPin), 0, 1023, 0, 1023);

  for(int i = 0; i < 48; i++) {
    setOutput(sin64[i]);
    delayMicroseconds(retardoTono);
  }
  
  if(retardoTono < 40) digitalWrite(12, HIGH);
  else digitalWrite(12, LOW);
  
  if(cont == 10) {
    analogWrite(volumenOutputPin, volumen);
    cont = 0;
  }
  analogWrite(13, volumen*2);
  cont++;
}

void setOutput(byte val) {
  digitalWrite(8, ((val & 10) > 0));
  digitalWrite(7, ((val & 8) > 0));
  digitalWrite(4, ((val & 4) > 0));
  digitalWrite(2, ((val & 1) > 0));
}


