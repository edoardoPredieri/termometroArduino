//#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
//#include <ir_Lego_PF_BitStreamEncoder.h>


const int GREEN = 10;  
const int BLUE = 11;  
const int RED = 9;

const int BUZZ = 6;

const int IRDA = 5;

int flag=0;

float R1 = 10500;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

IRrecv irrecv(IRDA); // create instance of 'irrecv'
decode_results results;

float calcTemp(int value){
   R2 = R1 * (1023.0 / (float)value - 1.0);
   logR2 = log(R2);
   T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
   Tc = T - 273.15;
   return Tc;
}

void setup() {  
  pinMode(A0,INPUT);
  Serial.begin(9600);
  pinMode(GREEN, OUTPUT);  
  pinMode(BLUE, OUTPUT);  
  pinMode(RED, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}  
 
  
void loop() {  
  if (irrecv.decode(&results)){ // have we received an IR signal?
    digitalWrite(BUZZ,HIGH);
    delay(100);
    digitalWrite(BUZZ,LOW);
    delay(100);
    if(flag==0) flag++;
    else flag--; 
    irrecv.resume();
  }

  if(flag){
    float temp=calcTemp(analogRead(A0));
    if(temp < 18.00){ 
      digitalWrite(BUZZ,HIGH);
      delay(100);
      digitalWrite(BUZZ,LOW);
      delay(100);
      digitalWrite(BUZZ,HIGH);
      delay(100);
      digitalWrite(BUZZ,LOW);
      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 255);
   }
    else if(temp >= 18.00 and temp < 23.00){
      digitalWrite(BUZZ,LOW);
      analogWrite(RED, 0);
      analogWrite(BLUE, 0);
      analogWrite(GREEN, 255);
    }
    else{
      digitalWrite(BUZZ,HIGH);
      delay(100);
      digitalWrite(BUZZ,LOW);
      delay(100);
      digitalWrite(BUZZ,HIGH);
      delay(100);
      digitalWrite(BUZZ,LOW);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0);
      analogWrite(RED, 255);  
   }
  }
  else{
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    analogWrite(RED, 0);  
  }
 // Serial.println(temp);
  delay(4000);
}
