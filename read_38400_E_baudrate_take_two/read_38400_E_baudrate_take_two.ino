/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
int frame[7];
unsigned long timeToDo = 0;
unsigned long timeout = 0;
boolean going = false;
void setup()  
{
  frame[0] = 74;
  frame[1] = 0;
  frame[2] = 0;
  frame[3] = 0;
  frame[4] = 0;
  frame[5] = 181;
  frame[6] = 128;
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8E1);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  
  Serial.println("Prepped");

}
void loop() // run over and over
{
  while (Serial1.available()) {
    if (Serial1.read() == 84) {
      Serial.write(84);
      int i = 1;
      while(true) {
        
        if(Serial1.available()) {
          Serial.write(Serial1.read());  
          i++;
        }  
        if(i == 6) {
          break;  
        }
      }
    
    }
    
    
  }


  if(Serial.available()) {
    frame[0] = Serial.read();
    frame[1] = Serial.read();
    frame[2] = Serial.read();
    frame[3] = Serial.read();
    frame[4] = Serial.read();
    frame[5] = Serial.read();
    frame[6] = Serial.read();
    timeout = millis()+1000;
    going = true;
  }
  
  
  if (going && millis() >= timeToDo){
    digitalWrite(2, HIGH);
    for(int i = 0; i < 6; i++) {
      Serial1.write(frame [i]);
    }
     Serial1.flush();
     
    digitalWrite(9, HIGH);  

    timeToDo = millis()+10;

  }
  
  if(millis() >= timeout) {
    digitalWrite(2, LOW);  
    going = false;
    //Serial.println("Going low");
  }

}




