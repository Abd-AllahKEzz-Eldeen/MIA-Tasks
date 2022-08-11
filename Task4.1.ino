#define LED 5
#define PB1 2
#define WM 3
#define RM 4
#define FSR A0
#define MSR A1
unsigned long t;
unsigned int c,Mread,Mwrite,Fread,Fwrite;
void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(PB1,INPUT_PULLUP);
  pinMode(WM,OUTPUT);
  pinMode(RM,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PB1),interrupt,FALLING);
}

void loop()
{
   if((millis()-t)>=10000)
    digitalWrite(RM,LOW);

  Serial.print("Number of refills = ");
  Serial.println(c);

  Fwrite=map(analogRead(FSR),0,1023,0,255);
  analogWrite(LED,Fwrite);
  
  Mwrite=map(analogRead(MSR),0,1023,255,0);
  analogWrite(WM,Mwrite);
}

void interrupt()
{
  c++;
  digitalWrite(RM,HIGH);
  t=millis();
}
