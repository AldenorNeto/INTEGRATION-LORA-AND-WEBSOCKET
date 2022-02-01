int umidadeSolo;
void setup() {
  Serial.begin(9600);
  Serial.println("Serial ON");
  pinMode(A14,OUTPUT);
  digitalWrite(A14,HIGH);
  pinMode(A13,OUTPUT);
  digitalWrite(A13,LOW);
  delay(1000);
}
void loop() {
   umidadeSolo = analogRead(A15);
   Serial.println(umidadeSolo);
   delay(200);
}
