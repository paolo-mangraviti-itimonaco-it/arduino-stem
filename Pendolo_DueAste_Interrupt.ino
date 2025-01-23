#define BARRIERA_90 2      // Barriera pendolo 90
#define BARRIERA_60 3      // Barriera pendolo 60


volatile long int t0_90 = 0;

volatile long int t1_90 = 0;
volatile long int t0_60 = 0;
volatile long int t1_60 = 0;
volatile long int T_90 = 0;
volatile long int T_60 = 0;

int oscillazioni_90 = 0;
int oscillazioni_60 = 0;

long int tGrafico = 0;
int fattore_90 = 1;
int fattore_60 = 1;

void setT_90()
{
  t1_90 = millis();
}

void setT_60()
{
  t1_60 = millis();
}

void setup()
{
  attachInterrupt(digitalPinToInterrupt(BARRIERA_90),setT_90,RISING);
  attachInterrupt(digitalPinToInterrupt(BARRIERA_60),setT_60,RISING);

  t0_90 = 0; t1_90 = 0;
  t0_90 = 0; t1_90 = 0;

  // Imposta le porte per il funzionamento ad alta impedenza
  digitalWrite(BARRIERA_90,HIGH);
  digitalWrite(BARRIERA_60,HIGH);
  Serial.begin(9600);
}

void loop()
{
  if (t1_90 > 0) 
  {
    //Serial.print((fattore_90*=-1)*((int)(t1_90-t0_90)/100));  Serial.print("\n");
    Serial.print("Pendolo_Asta_Lunga:");
    Serial.print((fattore_90*=-1)*(3));
    Serial.print(",");
    oscillazioni_90++;
    if ((oscillazioni_90 > 5) && (oscillazioni_90 % 2 == 0))
      T_90 = (t1_90-t0_90)*2;
    t0_90 = t1_90; t1_90 = 0;
  }
  if (t1_60 > 0) 
  {
    //Serial.print((fattore_60*=-1)*((int)(t1_60-t0_60)/100));  Serial.print("\n");
    Serial.print("Pendolo_Asta_Corta:");
    Serial.print((fattore_60*=-1)*(3));
    Serial.print(",");
    oscillazioni_60++;
    if ((oscillazioni_60 > 5) && (oscillazioni_60 % 2 == 0))
      T_60 = (t1_60-t0_60)*2;
    t0_60 = t1_60; t1_60 = 0;
  }
  if ((millis()-tGrafico)>200)
  {
    Serial.print("Pulse:");
    Serial.print(0);  Serial.print(",");
    Serial.print("Periodo_90:");
    Serial.print(T_90);  Serial.print("\n");
    Serial.print("Periodo_60:");
    Serial.print(T_60);  Serial.print("\n");
    Serial.print("Oscillazioni_90:");
    Serial.print(oscillazioni_90);  Serial.print("\n");
    Serial.print("Oscillazioni_60:");
    Serial.print(oscillazioni_60);  Serial.print("\n");
    tGrafico = millis();
  }
}
