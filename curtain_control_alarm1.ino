// C++ code
//

#include <LiquidCrystal.h> //this includes the library for the LCD display
#include <Stepper.h> //This includes the library for the stepper motor
#define STEPS 2048 //This defines STEPS and sets it to 2048

Stepper stepper(STEPS, 8,9,10,11); //This allows the stepper motor recognize that its using the pins, 8,9,10 and 11
LiquidCrystal lcd( 13,12,5,4,3,2); //this declares the pins for the LCD screen


int sensorValue = 0;
int buttonValue1 = 0;
int buttonValue2 = 0;
int buttonValue3 = 0;
int hours = 0;
int alarmMins = 0;
int alarmHours = 0;
int mins = 0;
int checker = 0;
int checker2 = 0;
int snooze = 0;

void setup() //this part of the code only repeats once
{
  Serial.begin(9600); //this is used for the stepper motor to initialize it
  stepper.setSpeed(10); //this sets the speed for the stepper motor
 
  //the following pinMode lines of code declare the pins as either Input or Output pins, depending on their functions.
  pinMode(9, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
 
    lcd.begin(16,2); //this starts the LCD display
    lcd.clear();
    lcd.setCursor(0,0); //sets the cursor
    lcd.print("Enter your alarm"); //makes the LCD display the following message
    lcd.setCursor(0,1); //changes the cursor to be one line down
    lcd.print("00:");
    lcd.setCursor(3,1);
    lcd.print("00");
}

void loop()
{
   //the following three lines of code below sets an integer variable to equal to the value of those pin slots on the arduino. These pins "A0, A1, A2" correspond to the pins that each pushbutton is attached to
    buttonValue1 = digitalRead(A0);
    buttonValue2 = digitalRead(A1);  
    buttonValue3 = digitalRead(A2);  
 
 if (checker == 0) //Checker is already set to 0 so when the code gets to the void loop, it always goes through this if-statement first
  {
    if (buttonValue1 == HIGH) //if the first button is pressed,
    {
      if (alarmMins < 59) //this makes it so that the minutes section cannot be greater than 59.
      {
         alarmMins += 1; //increases the value of the minutes variable by one
          delay(500); //delay for 500 milliseconds
      }
      else //if the minutes variable is greater than 59 then it sets the value back to zero
      {
        alarmMins = 0;
        lcd.setCursor(3,1);
        lcd.print("0"); //this overwrites the number that took that place and replaces it with 0.
      }
    }
    if (buttonValue2 == HIGH)
    {
      if (alarmHours < 23)
      {
        alarmHours += 1;
        delay(500);
      }
      else //the variable's value is set back to 0.
      {
        alarmHours = 0;
        lcd.setCursor(0,1);
        lcd.print("0");
      }
    }
    if ((buttonValue3 == HIGH) && (buttonValue1 == LOW) && (buttonValue2 == LOW)) //if the third button is pressed and the other two buttons are not pressed,
    {
      checker = 1; //the variable checker changes to 1, making it so that the code does not repeat this if statement and moves on to the next one
      delay(500);
    }  
   
   if (alarmMins < 10) //this part of the code is for formatting. If the value is under 10, it only takes one place value
   {
      lcd.setCursor(4,1); //sets the cursor to be the fourth space instead of the third one so that when the number is less 10, there is a zero before it. For example, the number 4 would display 04.
      lcd.print(alarmMins,DEC); //this part of the code displays the value of the minutes variable and parses it to a decimal value. This is done so that the number can be displayed.
   }
   if (alarmMins >= 10) //if the number is 10 or greater, then the cursor is set to the third space so that it displays the code one line before.
   {
      lcd.setCursor(3,1);
      lcd.print(alarmMins,DEC); //same as above
   }
   if (alarmHours < 10) //the following is the same as above (works the same way)
   {
      lcd.setCursor(1,1);
      lcd.print(alarmHours,DEC);
   }
   if (alarmHours >= 10)
   {
      lcd.setCursor(0,1);
      lcd.print(alarmHours,DEC);
   }  
  }
  else if (checker == 1) //If the third button is pressed, it makes checker 1. So when the third button is pressed, this else-if statement will run.
  {
   
    if (checker2 == 0) //this part of the code clears the display from before and asks the user to enter their time instead of their alarm
    {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Enter your time");
    lcd.setCursor(0,1);
    lcd.print("00:");
    lcd.setCursor(3,1);
    lcd.print("00");
    }
    checker2 = 1; //makes checker 2 equal to 1 so that it does not constantly repeat the code where it clears the display
   
    if (buttonValue1 == HIGH) //The following code is the exact same as above. However, it uses a different variable
    {
      if (mins < 59)
      {
         mins += 1;
         delay(500);
         Serial.print(buttonValue1);
      }
      else
      {
        mins = 0;
        lcd.setCursor(3,1);
        lcd.print("0");
      }
    }
    if (buttonValue2 == HIGH)
    {
      if (hours < 23)
      {
        hours += 1;
        delay(500);
      }
      else
      {
        hours = 0;
        lcd.setCursor(0,1);
        lcd.print("0");
      }
    }
    if ((buttonValue3 == HIGH) && (buttonValue1 == LOW) && (buttonValue2 == LOW))
    {
      checker = 2;
      delay(500);
    }  
   
   if (mins < 10)
   {
      lcd.setCursor(4,1);
      lcd.print(mins,DEC);
   }
   if (mins >= 10)
   {
      lcd.setCursor(3,1);
      lcd.print(mins,DEC);
   }
   if (hours < 10)
   {
      lcd.setCursor(1,1);
      lcd.print(hours,DEC);
   }
   if (hours >= 10)
   {
      lcd.setCursor(0,1);
      lcd.print(hours,DEC);
   }      
  }
 
  else if (checker == 2) //once the third button is pressed again, it goes to this else-if statement
  {
    lcd.setCursor(0,0);
    lcd.print("                "); //this clears the first line of the display by overwriting it with spaces
   
    if (mins < 10)
   {
      lcd.setCursor(4,1);
      lcd.print(mins,DEC);
   }
   if (mins >= 10)
   {
      lcd.setCursor(3,1);
      lcd.print(mins,DEC);
   }
   if (hours < 10)
   {
      lcd.setCursor(1,1);
      lcd.print(hours,DEC);
   }
   if (hours >= 10)
   {
      lcd.setCursor(0,1);
      lcd.print(hours,DEC);
   }      
   
   if (mins < 59)
    {
     
     }
     if ((hours == alarmHours)&&(mins == alarmMins)) //if the time equals the same values as the alarm
     {
        stepper.step(STEPS); //this turns the motor clockwise one revolution
        delay(10);
     
     for (int i = 0; i <60; i++) 
     {

     if (digitalRead(6) == HIGH
     {
       snooze = 1;      
     }

      if (snooze == 0) //if the snooze variable is 0 (aka the touch sensor not pressed), then the tone of the alarm is set so that it repeats the same two notes with a delay in the middle
      {
         tone(7, 200, 100);
         delay(500);
         tone(7, 500, 300);
         delay(500);  
      }
      else
      {
        delay (1000);
      }    
     }    
       mins += 1;
     }
     else
     {
       mins += 1;
       delay(60000);
     }
       
    }
   else
    {
       mins = 0;
       hours +=1;
       lcd.setCursor(3,1);
       lcd.print("0");
    }
    if (hours > 23)
      {
        hours = 0;
        lcd.setCursor(0,1);
        lcd.print("0");
      }
  }