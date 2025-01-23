#define LEDPIN 13
#define BARRIERA_INIZIO 2       // Barriera inizio
#define BARRIERA_FINE 3         // Barriera fine

volatile long int t0p1 = 0;
volatile long int t0p2 = 0;
volatile long int t1p1 = 0;
volatile long int t1p2 = 0;

void setT1()
{
  if (t1p1 == 0) 
    t1p1 = millis();
  else
    t1p2 = millis();
  
  Serial.print("Rilevato T1 (Barriera Finale)"); Serial.print("\n");
  Serial.print("P1: "); Serial.print(t1p1); Serial.print(" P2: "); Serial.print(t1p2); Serial.print("\n");
}

void setT0()
{
  if (t0p1 == 0) 
    t0p1 = millis();
  else
    t0p2 = millis();
  Serial.print("Rilevato T0 (Barriera Iniziale) "); Serial.print("\n");
  Serial.print("P1: "); Serial.print(t0p1); Serial.print(" P2: "); Serial.print(t0p2); Serial.print("\n");
}

void setup()
{
  attachInterrupt(digitalPinToInterrupt(BARRIERA_INIZIO),setT0,RISING);
  attachInterrupt(digitalPinToInterrupt(BARRIERA_FINE),setT1,RISING);

  t0p1 = 0; t1p1 = 0; t0p1 = 0; t1p2 = 0;

  // Imposta le porte per il funzionamento ad alta impedenza
  digitalWrite(BARRIERA_INIZIO,HIGH);
  digitalWrite(BARRIERA_FINE,HIGH);
  Serial.begin(9600);
}

void loop()
{
  if (t1p1 > 0 && t1p2 > 0) 
  {
    Serial.print("Tempo di discesa (1): "); Serial.print((int)(t1p1-t0p1)/100); Serial.print(" decimi di secondo."); 
    Serial.print("\n");

    Serial.print("Tempo di discesa (2): "); Serial.print((int)(t1p2-t0p2)/100); Serial.print(" decimi di secondo."); 
    Serial.print("\n");
    
    Serial.print("Velocita' (1): "); Serial.print((float)(950/((int)(t1p1-t0p1)/100))); Serial.print(" cm/s\n");
    Serial.print("Velocita' (2): ");  Serial.print((float)(950/((int)(t1p2-t0p2)/100))); Serial.print(" cm/s\n");
    t0p1 = 0; t1p1 = 0; t0p2 = 0; t1p2 = 0;
  }
}
