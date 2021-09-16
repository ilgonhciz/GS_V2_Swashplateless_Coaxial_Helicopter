



void calcSignal1() 
{
    //record the interrupt time so that we can tell if the receiver has a signal from the transmitter 
    last_interrupt_time1 = micros(); 
    //if the pin has gone HIGH, record the microseconds since the Arduino started up 
    if(digitalRead(CHANNEL_1_PIN) == HIGH) 
    { 
        timer_start1 = micros();
    } 
    //otherwise, the pin has gone LOW 
    else
    { 
        //only worry about this if the timer has actually started
        if(timer_start1 != 0)
        { 
            //record the pulse time
            channel_1_pulse_time = ((volatile int)micros() - timer_start1);
            //restart the timer
            timer_start1 = 0;
        }
    } 
} 

void calcSignal2() 
{
    //record the interrupt time so that we can tell if the receiver has a signal from the transmitter 
    last_interrupt_time2 = micros(); 
    //if the pin has gone HIGH, record the microseconds since the Arduino started up 
    if(digitalRead(CHANNEL_2_PIN) == HIGH) 
    { 
        timer_start2 = micros();
    } 
    //otherwise, the pin has gone LOW 
    else
    { 
        //only worry about this if the timer has actually started
        if(timer_start2 != 0)
        { 
            //record the pulse time
            channel_2_pulse_time = ((volatile int)micros() - timer_start2);
            //restart the timer
            timer_start2 = 0;
        }
    } 
} 
void calcSignal3() 
{
    //record the interrupt time so that we can tell if the receiver has a signal from the transmitter 
    last_interrupt_time3 = micros(); 
    //if the pin has gone HIGH, record the microseconds since the Arduino started up 
    if(digitalRead(CHANNEL_3_PIN) == HIGH) 
    { 
        timer_start3 = micros();
    } 
    //otherwise, the pin has gone LOW 
    else
    { 
        //only worry about this if the timer has actually started
        if(timer_start3 != 0)
        { 
            //record the pulse time
            channel_3_pulse_time = ((volatile int)micros() - timer_start3);
            //restart the timer
            timer_start3 = 0;
        }
    } 
} 
void calcSignal4() 
{
    //record the interrupt time so that we can tell if the receiver has a signal from the transmitter 
    last_interrupt_time4 = micros(); 
    //if the pin has gone HIGH, record the microseconds since the Arduino started up 
    if(digitalRead(CHANNEL_4_PIN) == HIGH) 
    { 
        timer_start4 = micros();
    } 
    //otherwise, the pin has gone LOW 
    else
    { 
        //only worry about this if the timer has actually started
        if(timer_start4 != 0)
        { 
            //record the pulse time
            channel_4_pulse_time = ((volatile int)micros() - timer_start4);
            //restart the timer
            timer_start4 = 0;
        }
    } 
} 
