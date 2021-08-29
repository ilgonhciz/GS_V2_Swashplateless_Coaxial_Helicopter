boolean analyse_mode = 1;
long starting_time = micros();

void printInfo(){
   //print different output using Serial print
    if (analyse_mode == 1){
    Serial.print("Ch1: ");
    Serial.print(pwmValue_motor_2);
    Serial.print(" ");

    Serial.print("Ch2: ");
    Serial.print(channel_2_pulse_time);
    Serial.print(" ");

    Serial.print("Ch3: ");
    Serial.print(channel_3_pulse_time);
    Serial.print(" ");

    Serial.print("Ch4: ");
    Serial.print(channel_4_pulse_time);
    Serial.print(" ");
    }
    if (analyse_mode == 2){
        Serial.print("V: ");
        Serial.print(moduelate_pwmValue);
        Serial.print(" ");
        Serial.print("R: ");
        Serial.print(rpm);
        Serial.print(" ");
        Serial.print("x: ");
        Serial.print(controlAngle);
        Serial.print(" ");
        Serial.print(angle_offset);
        Serial.print(" ");
        Serial.print(modulation_offset);
        Serial.print(" ");
      }
    if (analyse_mode == 3){
        Serial.print(micros()-starting_time);
        Serial.print(",");
        Serial.print(pwmValue_motor_1);
        Serial.print(",");
    
        Serial.print(a.acceleration.x);
        Serial.print(",");
        Serial.print(a.acceleration.y);
        Serial.print(",");
        Serial.print(a.acceleration.z);
    //Serial.print(",");
    //Serial.println(" ");
    //Serial.print("main_loop_duration: ");
    //Serial.print(main_loop_duration); 
      }                       
    Serial.println();
  }
