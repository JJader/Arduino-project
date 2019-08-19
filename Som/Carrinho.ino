int som = 6;
bool ja;

void setup() {
Serial.begin(9600);
pinMode(som, INPUT);
}

void loop() {

  ja= digitalRead(som);
  if(!ja){
    Serial.println("Estou escutando");
    delay(1000);
    } else{}



}
