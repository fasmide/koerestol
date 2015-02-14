void serialEvent() {
  int i;
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      newIncomming = true;
      }else{
        serialIn += inChar;        
        }
    }
}
void serial1Event() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    
  
  }
}
