    #define vel_motor_left 10 // controls speed of the left engine;
    #define vel_motor_right 11 // controls speed of the right engine;
    #define e1 // 8 controls the direction of rotation of the left engine;
    #define e2 // 9 controls the direction of rotation of the left engine;
    #define d1 12 // controls the direction of rotation of the right engine;
    #define d2 7 // controls the direction of rotation of the right engine;
    #include <VirtualWire.h>
    char inData[50];
    int newmessage = 0;
    int front,left,right;
    
    char flag = '0';
    int trigger_front = A4; // Controls the impulse sent from the front sensor
    int echo_front = A5; // Controls the pulse received from the front sensor
    
    int trigger_left = A2; // controls the impulse sent from the front sensor
    int echo_left = A3; // controls the boost received from the front of the sensor
    
    int trigger_right = A0; // controls the impulse sent from the front sensor
    int echo_right = A1; // controls the boost received from the front of the sensor
    
    // Configuration of input types of variables declared;
    void setup ()
    {
        vw_setup(2000);
        vw_set_tx_pin(2);
        vw_rx_start();
        pinMode (13,OUTPUT);
        pinMode (trigger_front, OUTPUT); //signal output // the Arduino trigger_front
        pinMode (echo_front, INPUT); //signal input // the Arduino echo_front
        
        pinMode (trigger_left, OUTPUT); // signal output from the Arduino trigger_front
        pinMode (echo_left, INPUT);// signal input // the Arduino echo_front
        
        pinMode (trigger_right, OUTPUT); // signal output from the Arduino trigger_front
        pinMode (echo_right, INPUT); //signal input // the Arduino echo_front
       
        pinMode (vel_motor_left, OUTPUT); // signal output from the Arduino left engine speed
        pinMode (vel_motor_right, OUTPUT); // output signal of the right engine speed arduino
     
        pinMode (e1, OUTPUT); // Arduino signal output control the direction of rotation of the left engine
        pinMode (e2, OUTPUT); // Arduino signal output control the direction of rotation of the left engine
        pinMode (d1, OUTPUT); // Arduino signal output control the direction of rotation of the right engine
        pinMode (d2, OUTPUT); // Arduino signal output control the direction of rotation of the right engine
        delay (5000);
    }
    
    // Code in the endless repetition;
    void loop ()
    {
     // Declaration of variables used for project control;
     long duracao_frente, duracao_esq, duracao_dir;
     
     
     digitalWrite (trigger_front, LOW); // Is declared their inputs and signal outputs
     delayMicroseconds (2); // Ultrasonic sensor and stored by the variable sensor
     digitalWrite (trigger_front, HIGH); // That converts the speed of sound is 340 m / s or
     delayMicroseconds (5); // 29 microseconds per centimeter, as the signal comes and goes
     digitalWrite (trigger_front, LOW); // This time is half being time = sensor / 29/2;
     duracao_frente = pulseIn (echo_front, HIGH); // Thus also follows the other two sensors.
     front = duracao_frente / 29/2;
    
     digitalWrite (trigger_left, LOW);
     delayMicroseconds (2);
     digitalWrite (trigger_left, HIGH);
     delayMicroseconds (5);
     digitalWrite (trigger_left, LOW);
     duracao_esq = pulseIn (echo_left, HIGH);
     left = duracao_esq / 29/2;
    
     digitalWrite (trigger_right, LOW);
     delayMicroseconds (2);
     digitalWrite (trigger_right, HIGH);
     delayMicroseconds (5);
     digitalWrite (trigger_right, LOW);
     duracao_dir = pulseIn (echo_right, HIGH);
     right = duracao_dir / 29/2;
     
     analogWrite (vel_motor_left, 0); // Block to initialize the inputs with pulse 0 or off;
     analogWrite (vel_motor_right, 0); //
     analogWrite (e1, 0); //
     analogWrite (e2, 0); //
     analogWrite (a1, 0); //
     analogWrite (D2 0); //

     if (left>50 && right>50 && front>50)
     {
      sendbot();
      end1:
      while(true)
      {
        digitalWrite(13,HIGH);
        delay(1000);
        digitalWrite(12,LOW);
        delay(1000);
      }
     }
     

     if (flag=='1')
     {
      back();
      leftbot();
     }
     else
       rightbot();`
       if (left <= 20 && right> 20 && front <= 8) dir (); // If the distance to the front is less than or equal to 8 cm
                                                            // Distance to the right is greater than 20 cm and the distance
                                                            // The left is less than or equal to 20 cm it calls the dir () function;
            
       else if (left> 20 && right> 20 && front <= 8) dir (); // If the distance to the front is less than or equal to 8 cm
                                                            // Distance to the right is greater than 20 cm and the distance
                                                            // The left is greater than 20 cm it calls the dir () function;
       
       else if (right <= 20 && left <= 20 && front <= 8) back (); // If the distance to the front is less than or equal to 8 cm
                                                            // The right distance is less than or equal to 20 cm and the distance
                                                            // The left is less than or equal to 20 cm it calls the function back ();
    getbot();
    }

    void sendbot()
    {
      char mss[20];
     inData[0] = '1';
     sprintf(mss, "%s", inData);
     vw_send((uint8_t *)mss, strlen(mss));
     vw_wait_tx();
     delay(600);
     byte message[VW_MAX_MESSAGE_LEN];
     byte messageLength = VW_MAX_MESSAGE_LEN;
     if (vw_get_message(message, &messageLength))
     {
      message.trim();
      temp=message[0];
     }
     if (temp=='1')
     goto end1;
     else
     sendbot();
    }

    void getbot()
    {
      byte message[VW_MAX_MESSAGE_LEN];
      byte messageLength = VW_MAX_MESSAGE_LEN;
      if (vw_get_message(message, &messageLength))
      {
        message.trim();
        flag=message[0];
      }      
      delay(1000);
      char mss[20];
     inData[0] = '1';
     sprintf(mss, "%s", inData);
     vw_send((uint8_t *)mss, strlen(mss));
     vw_wait_tx();
    }

    void leftbot()
    {
      if (front> 8) // if if there is clear path forward he follows this logic below:
         {
           // Use the four if's below in this if they are to control the robot handling,
           // To keep it following the left wall straight;
           
           else if (left > 7 && left <13) // if the distance to the left wall is between 9 and 12 cm, the robot
                                         // Keep straight;
             {
               analogWrite (vel_motor_left, 150);
               analogWrite (vel_motor_right, 120);
           
               analogWrite (e1, 255);
               analogWrite (e2, 0);
               analogWrite (a1, 0);
               analogWrite (d2, 255);
             }
         
           else if (left >= 13) // if the distance to the left wall is greater than or equal to 13 cm, the robot increases
                             // A right engine speed to approach the left wall;
             {
               analogWrite (vel_motor_left, 60);
               analogWrite (vel_motor_right, 255);
           
               analogWrite (e1, 255);
               analogWrite (e2, 0);
               analogWrite (d1, 0);
               analogWrite (d2, 255);
             }
             
                 
           else if (left <= 7) // if the distance to the left wall is less than or equal to 8 cm, the robot increases
                             // Its left engine speed to distance themselves from the left wall;
             {
               analogWrite (vel_motor_left, 255);
               analogWrite (vel_motor_right, 60);
           
               analogWrite (e1, 255);
               analogWrite (e2, 0);
               analogWrite (d1, 0);
               analogWrite (d2, 255);
             }
          if (left <= 20 && right> 20 && front <= 8) rightdir (); // If the distance to the front is less than or equal to 8 cm
                                                            // The right distance is less than or equal to 20 cm and the distance
                                                            // The left is greater than 20 cm it calls the Left () function;
         }  
    }

     void rightbot()
     {
       if (front> 8) // if if there is clear path forward he follows this logic below:
         {
           // Use the four if's below in this if they are to control the robot handling,
           // To keep it following the right wall straight;
           
           if (right> 7 right && <13) // if the distance to the right wall is between 9 and 12 cm, the robot
                                         // Keep straight;
             {
               analogWrite (vel_motor_left, 120);
               analogWrite (vel_motor_right, 150);
           
               analogWrite (e1, 255);
               analogWrite (e2, 0);
               analogWrite (a1, 0);
               analogWrite (d2 255);
             }
         
           else if (right> = 13) // if the distance to the right wall is greater than or equal to 13 cm, the robot increases
                             // A left engine speed to approach the right wall;
             {
               analogWrite (vel_motor_left, 255);
               analogWrite (vel_motor_right, 60);
           
               analogWrite (e1, 255);
               analogWrite (e2, 0);
               analogWrite (d1, 0);
               analogWrite (d2 255);
             }
             
                 
           else if (right <= 7) // if the distance to the right wall is less than or equal to 8 cm, the robot increases
                             // Its right engine speed to distance themselves from the right wall;
             {
               analogWrite (vel_motor_left, 60);
               analogWrite (vel_motor_right, 255);
           
               analogWrite (e1, 255);
               analogWrite (e2, 0);
               analogWrite (d1, 0);
               analogWrite (d2 255);
             }
         }
         if (right <= 20 && left> 20 && front <= 8) leftdir (); // If the distance to the front is less than or equal to 8 cm
                                                            // The right distance is less than or equal to 20 cm and the distance
                                                            // The left is greater than 20 cm it calls the Left () function;
       
    }
       
    void leftdir () // function to make the robot turn 90 degrees left if he did not have out front and right;
      {
       
        analogWrite (vel_motor_left, 120);
        analogWrite (vel_motor_right, 120);
           
        analogWrite (e1, 0);
        analogWrite (e2, 255);
        analogWrite (d1, 0);
        analogWrite (d2 255);
        delay (700);
        
      }
    
    void dir () // function to make the robot turn 90 right up if you do not exit the front or the left;
      {
        
      
        analogWrite (vel_motor_left, 120);
        analogWrite (vel_motor_right, 120);
        
        analogWrite (e1, 255);
        analogWrite (e2, 0);
        analogWrite (d1, 255);
        analogWrite (d2 0);
        delay (800);
               
      }
    
    void back () // function to make the robot rotate 180 ° if the case has not output the front, right and left;
      {
       
        analogWrite (vel_motor_left, 120);
        analogWrite (vel_motor_right, 120);
           
        analogWrite (e1, 255);
        analogWrite (e2, 0);
        analogWrite (d1, 255);
        analogWrite (d2 0);
        delay (1200);
         
      }
       void rightdir () // function to make the robot turn 90 degrees right if he did not have out front and right;
      {
       
        analogWrite (vel_motor_left, 120);
        analogWrite (vel_motor_right, 120);
           
        analogWrite (e1, 255);
        analogWrite (e2, 0);
        analogWrite (d1, 255);
        analogWrite (d2, 0);
        delay (700);
        
      }
