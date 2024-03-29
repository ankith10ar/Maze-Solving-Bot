    #define vel_motor_left 10  
    #define vel_motor_right 11          
    #define e1 8  
    #define e2 9  
    #define d1 12  
    #define d2 7  
    #define b1 5
 
#include <SoftwareSerial.h>// import the serial library
SoftwareSerial bt(4,5); // RX, TX

String senseval,path="";
int x,n = 0;

    int trigger_front = A4; 
    int echo_front = A5; 
    int trigger_left = A2;
    int echo_left = A3;
    int trigger_right = A0;
    int echo_right = A1;


    void setup()
    {
      Serial.begin(9600);
      bt.begin(9600);
        pinMode(b1,OUTPUT);
        pinMode(trigger_front, OUTPUT); 
        pinMode(echo_front, INPUT);
        
        pinMode(trigger_left, OUTPUT);
        pinMode(echo_left, INPUT);        
        
        pinMode(trigger_right, OUTPUT);
        pinMode(echo_right, INPUT);
       
        pinMode(vel_motor_left, OUTPUT);
        pinMode(vel_motor_right, OUTPUT);
     
        pinMode(e1, OUTPUT);
        pinMode(e2, OUTPUT);
        pinMode(d1, OUTPUT);
        pinMode(d2, OUTPUT);      
        delay(5000);
    }
    
 
    void loop()
    {
      delay(3500);
     long duration_front, duration_left, duration_right, right_distance, left_distance, front; 
     
     
     digitalWrite(trigger_front, LOW);  
     delayMicroseconds(2);               
     digitalWrite(trigger_front, HIGH); 
     delayMicroseconds(5);               
     digitalWrite(trigger_front, LOW);  
     duration_front = pulseIn(echo_front, HIGH); 
     front = duration_front/29/2;
     
    
    
     digitalWrite(trigger_left, LOW);
     delayMicroseconds(2);
     digitalWrite(trigger_left, HIGH);
     delayMicroseconds(5);
     digitalWrite(trigger_left, LOW); 
     duration_left = pulseIn(echo_left, HIGH);
     left_distance = duration_left/29/2;
     

     
    
     digitalWrite(trigger_right, LOW);
     delayMicroseconds(2);
     digitalWrite(trigger_right, HIGH);
     delayMicroseconds(5);
     digitalWrite(trigger_right, LOW); 
     duration_right = pulseIn(echo_right, HIGH);
     right_distance = duration_right/29/2;
     
     analogWrite(vel_motor_left, 0);  
     analogWrite(vel_motor_right, 0); 
     analogWrite(e1, 0);            
     analogWrite(e2, 0);              
     analogWrite(d1, 0);            
     analogWrite(d2, 0);
     
 if ((left_distance<20&&front<13)&&(right_distance<20))
        senseval = "000";
        else if ((left_distance>20&&front<13)&&(right_distance<20))
        senseval = "L00";
        else if ((left_distance>20&&front>13)&&(right_distance<20))
        senseval = "LF0";
        else if ((left_distance>20&&front<13)&&(right_distance>20))
        senseval = "L0R";
        else if ((left_distance<20&&front>13)&&(right_distance<20))
        senseval = "0F0";
        else if ((left_distance<20&&front>13)&&(right_distance>20))
        senseval = "0FR";
        else if ((left_distance<20&&front<13)&&(right_distance>20))
        senseval = "00R";
        else 
        senseval = "LFR";

        if (senseval=="LFR")
           n++;
           else
           n--;
           if (n==2)
           endpath();

       if(front >10) 
         {    
           
           if(right_distance >4 && right_distance< 10) 
             {               
               analogWrite(vel_motor_left, 150);
               analogWrite(vel_motor_right, 120);
           
               analogWrite(e1, 0);
               analogWrite(e2, 255);
               analogWrite(d1, 0);
               analogWrite(d2, 255); 
   
             }
            
         
           else if(right_distance >=10)  
             {
               analogWrite(vel_motor_left, 180);
               analogWrite(vel_motor_right, 60);
           
               analogWrite(e1, 0);
               analogWrite(e2, 255);
               analogWrite(d1, 0);
               analogWrite(d2, 255);

               
             }
             
                 
           else if(right_distance <=4)   
             {
               analogWrite(vel_motor_left, 60);
               analogWrite(vel_motor_right, 180);
           
               analogWrite(e1, 0);
               analogWrite(e2, 255);
               analogWrite(d1, 0);
               analogWrite(d2, 255);

           
             }
         path = path+(senseval+"F");
         }

      
       if(left_distance <=20 && right_distance>20 && front <=10) 
       {
        right();   
        path = path + (senseval+"R");
       }
            
       if(left_distance >20 && right_distance>20 && front <=10)
       {
        right(); 
        path = path + (senseval+"R");
       }
       
       if(right_distance <=20 && left_distance>20 && front <=10)
       {
        left(); 
        path = path + (senseval+"L");
       }
       
       if(right_distance<=20 && left_distance<=20 && front<=10)
       {
        back();                               
        path = path + (senseval+"U");
       }
    Serial.println(left_distance);
    Serial.println(front);
    Serial.println(right_distance);
    Serial.println(senseval);
    }
       
    void left() 
      {
       
        analogWrite(vel_motor_left, 0);
        analogWrite(vel_motor_right, 120);
         
        analogWrite(e1, 255);
        analogWrite(e2, 0);
        analogWrite(d1, 0);
        analogWrite(d2, 255);
        digitalWrite(b1,HIGH);
        delay(700);   
        digitalWrite(b1,LOW);   
        
      }
    
    void right() 
      {
        
      
        analogWrite(vel_motor_left, 120);
        analogWrite(vel_motor_right, 0);
        
        analogWrite(e1, 0);
        analogWrite(e2, 255);
        analogWrite(d1, 255);
        analogWrite(d2, 0);        
        digitalWrite(b1,HIGH);   
        delay(800);
        digitalWrite(b1,LOW);
               
      }
    
    void back() 
      {
       
        analogWrite(vel_motor_left, 120);
        analogWrite(vel_motor_right, 120);
           
        analogWrite(e1, 0);
        analogWrite(e2, 255);
        analogWrite(d1, 255);
        analogWrite(d2, 0);
        digitalWrite(b1,HIGH);
        delay(1200); 
        digitalWrite(b1,LOW);
         
      }   
  
    void endpath()
    {
     analogWrite(vel_motor_left, 0);
        analogWrite(vel_motor_right, 0);
           
        analogWrite(e1, 0);
        analogWrite(e2, 0);
        analogWrite(d1, 0);
        analogWrite(d2, 0); 

      for (x=0;x<path.length();x+=4)
      {
        bt.println(path.substring(x,x+4));
        Serial.println(path.substring(x,x+4));
        delay(2000);
      }

      while(true)
      {
      digitalWrite(b1,HIGH);
      delay(500);
      digitalWrite(b1,LOW);
      }
    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
