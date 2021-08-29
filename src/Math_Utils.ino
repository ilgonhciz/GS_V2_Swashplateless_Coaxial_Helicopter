void computeRPM(){
    // compute the RPM of the brushless motor using the as5047p sensory.  
      float angleDifference;
      if(abs(motorAngle- previousMotorAngle)>300){
          if(motorAngle>300){
              angleDifference = -(360 - motorAngle + previousMotorAngle);
            }
          else{
              angleDifference = 360 + motorAngle - previousMotorAngle;
            }
        }
      else{
          angleDifference = motorAngle - previousMotorAngle;
        }
      rpm = (angleDifference)/360*1000; 
      previousMotorAngle = motorAngle;
  }



float normalizeThrottle(float pulseValue){
    return (pulseValue - 1000)/ 1000;
  }


float normalizePRY(float pulseValue){
    return (pulseValue - 1500)/ 500;
  }
