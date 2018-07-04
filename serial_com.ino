#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

long baud = 9600;
int amplitude = 3600;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(baud);
  delay(1000);

}

int c;
char buf[20];
void loop() {
  if(mySerial.available()){
    Serial.write(mySerial.read());
   }
  if(Serial.available()){
    c = Serial.read();
    if(c == '$')
      {
        baud += amplitude;
        sprintf(buf,"Baudrate = %u",baud);
        Serial.println(buf);
        mySerial.flush();
        mySerial.begin(baud);
        delay(50);
      }else if(c == '*')
      {
        baud -= amplitude;
        sprintf(buf,"Baudrate = %u",baud);
        Serial.println(buf);
        mySerial.flush();
        mySerial.begin(baud);
        delay(50);
      }else if (c == '%'){
        mySerial.write('\x1A');
      }else{
        
        mySerial.write(c);
      }
   }
}
