void getReceiverValues(){
  int i, num;
  num = myIn.available();
  if (num > 0) {
    for (i=1; i <= num; i++) {
      ppmValues[i-1] = myIn.read(i);
      float val = myIn.read(i);
    }    
  }
}

void handleSerial() {
   // Logik of the Serial input 
   char incomingCharacter = Serial.read();
   switch (incomingCharacter) {
     case '9':
      pwmValue_motor_1 = 255; 
      Serial.println(pwmValue_motor_1);
      break;

     case '5':
      pwmValue_motor_1 = 192; 
      Serial.println(pwmValue_motor_1);
      break; 
     
     case '+':
      pwmValue_motor_1 = pwmValue_motor_1 + 2; 
      Serial.println(pwmValue_motor_1);
      break;

     case '-':
      pwmValue_motor_1 = pwmValue_motor_1 - 1;
      Serial.println(pwmValue_motor_1);
      break;
      
     case '0':
      pwmValue_motor_1 = 124;
      break;

      case 'i':
      pwmValue_motor_1 = 135;
      break;
     
     case 's':
      modulation_offset = pwmValue_motor_1 - 140;
      break;

    case 'b':
      modulation_offset = 0;
      break;
    
    case 'a':
      angle_offset += 45;
      break;

    case 'p':
      printInfo();
      break;
    }
}
