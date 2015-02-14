
//http://www.arduino.cc/playground/uploads/Code/FSM_1-6.zip
#include <FiniteStateMachine.h>


String serialIn = "";
bool newIncomming = false;
int inX,inY;


/* state functions*/
State idle = State(idleUpdate); 
State drive = State(driveUpdate);
State hight = State(hightUpdate);
State tilt = State(tiltUpdate);

/** the state machine controls which of the states get attention and execution time */
FSM stateMachine = FSM(idle); //initialize state machine, start in state: noop


void setup(){ 
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8E1);
}


void loop(){
if (newIncomming) {
  switch (serialIn.charAt(0)){
    case 0x01: stateMachine.transitionTo(idle); 

    break;
    case 0x02: stateMachine.transitionTo(drive); 
        inX = serialIn.toInt();
        inY = serialIn.toInt();
        serialIn = "";
    break;
    case 0x03: stateMachine.transitionTo(hight); 
    break;
    case 0x04: stateMachine.transitionTo(tilt); 
    break;
    }
  }
//      case 0: stateMachine.transitionTo(noop); break;
//      case 1: stateMachine.transitionTo(fade); break; //first press
//      case 2: stateMachine.transitionTo(flash); break; //second press
  stateMachine.update();
}

void idleUpdate() {
//importent things here
}
void driveUpdate() {
}
void hightUpdate() {
}
void tiltUpdate() {
}



