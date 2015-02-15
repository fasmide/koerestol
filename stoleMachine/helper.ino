void serialEvent() {
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
}
void serialEvent1() {
  while (Serial1.available()) {
    char inChar = (char)Serial1.read();
    Serial.write (inChar);

  }
}
