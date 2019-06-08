void setup() {
  analogWriteResolution(12);  // Define resolución del DAC
}

void loop() {
  // Definición de variables
  int numIncrementos = 10;
  int uno = 0;
  int valor = 0;
  int incremento = 4000 / numIncrementos;
  int valorMaximo = incremento * numIncrementos;

  while(1) 
  {
    analogWrite(DAC1, valor);         // Escribir al DAC la variable valor
    valor += incremento;            // Incrementar valor
    valor = (valor > valorMaximo ? 0 : valor);  // Compara si ha llegado al valor máximo
    delayMicroseconds(uno);           // Retardo
  }
}
