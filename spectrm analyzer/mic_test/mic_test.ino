#define CHANNEL 4
#define DIGITAL 5

float ave,val=0;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(256000);
 pinMode(DIGITAL,INPUT);
 for(int i=0;i<50000;i++)
 {
    ave = ave+ analogRead(CHANNEL);
 }
 
 ave = ave/50000; 
}

void loop() {
  // put your main code here, to run repeatedly:
 if(digitalRead(DIGITAL)==1){ 
val=analogRead(CHANNEL);
 }
 else
 {
  val=0;
 }
Serial.println(val);
}
