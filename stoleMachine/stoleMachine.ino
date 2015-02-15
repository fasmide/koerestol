//{"command":"wheel","data":[10,30]}


//http://www.arduino.cc/playground/uploads/Code/FSM_1-6.zip
#include <FiniteStateMachine.h>
#include <ArduinoJson.h>

struct Frame {
  byte startByte = 74;
  byte cmdByte;
  byte btnByte;
  char x;
  char y;
  byte checksum;
  int ttl;
};
Frame data;


char wheel[] = "wheel";
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
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8E1);
}


void loop() {
  if (newIncomming) {
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    if (!root.success()) {
      Serial.println("parseObject() failed");
    } else {
      const char* command = root["command"];
      //root.prettyPrintTo(Serial);
      
      // command wheel decode and set ative
      if (strcmp(wheel, command) == 0) {
        data.startByte = 74;
        data.cmdByte = 0;
        data.btnByte = 0;
        int x = root["data"][0]; 
        data.x = x;
        int y = root["data"][1]; 
        data.y = y;
        data.ttl = millis() + TIMEOUT;
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
  digitalWrite(13, HIGH);
  timer = millis();
}
void activeUpdate() {
  if (millis() > data.ttl)stateMachine.transitionTo(idle);
  if (millis() > timer) {
    timer = millis() + 10;
    printToChair();
  }
}
void activeExit() {
  digitalWrite(13, LOW);
}





void printToChair() {
  data.checksum = 255 - data.startByte - data.cmdByte - data.btnByte - data.x - data.y;
  Serial.print (data.startByte);
  Serial.print (" ");
  Serial.print (data.cmdByte);
  Serial.print (" ");
  Serial.print (data.btnByte);
  Serial.print (" ");
  Serial.print (data.x, DEC);
  Serial.print (" ");
  Serial.print (data.y, DEC);
  Serial.print (" ");
  Serial.println (data.checksum);
}


