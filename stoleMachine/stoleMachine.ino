//{"c":"w","x":10,"y":30}


//http://www.arduino.cc/playground/uploads/Code/FSM_1-6.zip
#include <FiniteStateMachine.h>
#include <ArduinoJson.h>

struct HandiFrame {
  byte startByte;
  byte cmdByte;
  byte btnByte;
  char x;
  char y;
  byte checksum;
  int ttl;
};
HandiFrame handiFrame;
HandiFrame* handiFramePtr = &handiFrame;



char wheelKey[] = "w";
const int TIMEOUT = 1000;


char json[200];
char* jsonPtr1 = &json[0];

bool newIncomming = false;
int timer;


/* state functions*/
State idle = State(idleEnter, idleUpdate, idleExit);
State active = State(activeEnter, activeUpdate, activeExit);


/** the state machine controls which of the states get attention and execution time */
FSM stateMachine = FSM(idle); //initialize state machine, start in state: noop


void setup() {
  pinMode(4,OUTPUT);
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8E1);
}


void loop() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar != 0XD) {
      *jsonPtr1 = inChar;
      if (inChar == 0XA) {
        newIncomming = true;
        jsonPtr1 = &json[0];
      } else {
        jsonPtr1++;
       }
    }
  }
  if (newIncomming) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    if (!root.success()) {
      Serial.println("parseObject() failed");
    } else {
      const char* c = root["c"];
      //root.prettyPrintTo(Serial);
      
      // command wheel decode and set ative
      if (strcmp(wheelKey, c) == 0) {
        handiFrame.startByte = 74;
        handiFrame.cmdByte = 0;
        handiFrame.btnByte = 0;
        int x = root["x"]; 
        handiFrame.x = x;
        int y = root["y"]; 
        handiFrame.y = y;
        handiFrame.ttl = millis() + TIMEOUT;
        updateCRC(&handiFrame);
        stateMachine.transitionTo(active);
      }
      // Other commands here
      
    }
    newIncomming = false;
  }
  stateMachine.update();
}

void idleEnter() {
  Serial.println ("idle");
}
void idleUpdate() {
}
void idleExit() {
  
}


void activeEnter() {
  Serial.println ("active");
  digitalWrite(4, HIGH);
  timer = millis();
}
void activeUpdate() {
  /*if (millis() > handiFrame.ttl)
  {
    stateMachine.transitionTo(idle);
  }*/
  if (millis() > timer) {
    timer = millis() + 10;
    printToChair(&handiFrame);
  }
}
void activeExit() {
  digitalWrite(4, LOW);
}



void updateCRC(struct HandiFrame *frame) {
          frame->checksum = 255 - frame->startByte - frame->cmdByte - frame->btnByte - frame->x - frame->y;
  }

void printToChair(struct HandiFrame *frame) {
      Serial1.print (frame->startByte);
      Serial1.print (frame->cmdByte);
      Serial1.print (frame->btnByte);
      Serial1.print (frame->x);
      Serial1.print (frame->y);
      Serial1.print (frame->checksum);
  
  /*
  handiFrame.checksum = 255 - handiFrame.startByte - handiFrame.cmdByte - handiFrame.btnByte - handiFrame.x - handiFrame.y;
  Serial.print (handiFrame.startByte);
  Serial.print ("c");
  Serial.print (handiFrame.cmdByte);
  Serial.print ("c");
  Serial.print (handiFrame.btnByte);
  Serial.print ("c");
  Serial.print (handiFrame.x, DEC);
  Serial.print ("c");
  Serial.print (handiFrame.y, DEC);
  Serial.print ("c");
  Serial.println (handiFrame.checksum);
  */
}


