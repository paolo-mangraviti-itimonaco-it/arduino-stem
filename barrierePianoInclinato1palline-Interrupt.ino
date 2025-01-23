#define LEDPIN 13
#define BARRIERA_INIZIO 2       // Barriera inizio
#define BARRIERA_FINE 3         // Barriera fine

volatile long int t0 = 0;
volatile long int t1 = 0;

void setT0()
{
  t0 = millis();
  Serial.print("Inizio discesa: "); Serial.print(t0); Serial.print("\n");
}

void setT1()
{
  t1 = millis();
  Serial.print("Fine discesa: "); Serial.print(t1); Serial.print("\n");
}

void setup()
{
  attachInterrupt(digitalPinToInterrupt(BARRIERA_INIZIO),setT0,RISING);
  attachInterrupt(digitalPinToInterrupt(BARRIERA_FINE),setT1,RISING);

  t0 = 0; t1 = 0;

  // Imposta le porte per il funzionamento ad alta impedenza
  digitalWrite(BARRIERA_INIZIO,HIGH);
  digitalWrite(BARRIERA_FINE,HIGH);
  Serial.begin(9600);
}

void loop()
{
  if (t1 > 0) 
  {
    Serial.print("Tempo di discesa: "); Serial.print((int)(t1-t0)/100); Serial.print(" decimi di secondo."); Serial.print("\n");
    Serial.print("Velocita': "); Serial.print((float)(950/((int)(t1-t0)/100))); Serial.print(" cm/s\n");
    t0 = 0; t1 = 0;
  }
}
