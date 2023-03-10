
# include <Encoder.h>





// This is a fcuntion from the encoder library, it sets up an interrupt automatically

Encoder knobLeft(3, 5);
Encoder knobRight(7, 8);


// Use a baud rate of 9600 or else the program breaks


const int period = 10;
long positionLeft = -999;
long positionRight = -999;
float angular_position = 0.5;
float difference = 0;
float previous_state_velocity = 0;
float beginning = 0;
float angular_velocity = 0.0;
float time_previous = 0.0;
float milliseconds;
float previous_increment = 0.0;
float new_angular_velocity = 0;
float counter_per_rotation = 3200.0;
float ms_to_s = 1000.0;
int time_now = 0;
int time_now_now = 0;
int difference_2 = 0;
int counter = 0;




void setup() {
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,INPUT);
  digitalWrite(4,HIGH);
      
}



void loop() {

  if(millis() >= 1000 && millis() <= 1100){
    analogWrite(9,125);
    digitalWrite(7,LOW);
  }

  // This will make it so that it outputs data and runs for the 10ms period.

  if (millis() > time_now + period) {



    time_now = millis();

    // motor code for later

    // The .read functions will read the encoder in its current state

    long newLeft, newRight;
    newLeft = knobLeft.read();
    newRight = knobRight.read();

    // difference is the new position it is as at minus the old position of the motor

    difference = 2*PI*(newLeft - positionLeft)/3200 ;    
    counter = counter + difference;

    // To find the angular velocity, we multiply the difference of the two positions by 1000, since we are dividing by
    // ms. We divide by the time the new position is at minus the time the old position was at to get the angualar velocity
    // create a tab so that it can easily be copied into matlab.

    new_angular_velocity = 1000 * (difference) / (millis() - time_previous);
    Serial.print(millis()/ms_to_s);
    Serial.print("\t");    
    Serial.println(new_angular_velocity);    

    // We then set the old positions to the current one so we can get ready to loop again.

    positionLeft = newLeft;
    positionRight = newRight;
    time_previous = time_now;   
    
     
  }

  // This is the code that resets the angular_position of the wheel, changing the reference if not set to 0pi.

  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }




}
/*
  if (counter >= 800) {

    counter = 0;
    if (angular_position == 0) {
      angular_position = 1.5;
    } else {
      angular_position = angular_position - 0.5;
    }

    //Serial.print("Angular Position = ");
    //Serial.print(angular_position);
    //Serial.println("pi");

    angular_velocity = (abs((angular_position * PI) - (previous_increment * PI))) / (difference_2 / 1000);

    //Serial.print("rad/s = ");
    //Serial.println(angular_velocity);
    //previous_increment = angular_position;
    //angular_velocity = 0;
  }

  if (counter <= -800) {
    time_now_now = millis();
    difference_2 = time_now_now - time_previous;
    counter = 0;
    angular_position = angular_position + 0.5;
    if (angular_position == 2) {
      angular_position = 0;
      previous_increment = 0.5;
    }

    //Serial.print("Angular Position = ");
    //Serial.print(angular_position);
    //Serial.println("pi");

    //angular_velocity = (abs((angular_position*PI)-(previous_increment*PI)))/(difference_2/1000);

    //Serial.print("rad/s = ");
    //Serial.println(angular_velocity);
    //previous_increment = angular_position;
    //angular_velocity = 0;



    // if a character is sent from the serial monitor,
    // reset both back to zero.
  }
  
  angular_velocity = 0;
}
*/
