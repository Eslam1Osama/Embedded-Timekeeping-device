#include<LiquidCrystal_I2C.h>
#include <DS3231.h>

/*=============================================*/
DS3231 RTC;
bool century = false;
bool H12Flag = false;
bool PmFlag  = false; 
/*=============================================*/
//create object from class LiquidCrystal_I2C
/* 0X27-> the address which arduino is going to address 
   LCD through I2C communication protocole
   20-> number of columns in LCD
   4-> number of rows in LCD
*/
LiquidCrystal_I2C LCD(0X27 , 20 , 4);

#define UP        3
#define DOWN      5
#define RIGHT     4
#define LEFT      2 
#define Menu      6 
#define BUZZER    7 

bool alarm_mode = false;
int alarm_status = 0;
int Alarm_Year , Alarm_Month , Alarm_Day , Alarm_Hour , Alarm_Minute , Alarm_Second;
unsigned long lastMillis = 0; 

void setup()
{
  //initialize LCD
  LCD.init();
  
  //clear LCD
  LCD.clear();
  
  //turn on back light of LCD
  LCD.backlight();
  
  LCD.clear();
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(Menu, INPUT);
  pinMode(BUZZER, OUTPUT);

  // modify date passed on your current date
  RTC.setYear(24);
  RTC.setMonth(5);
  RTC.setDate(18);
  RTC.setHour(6);
  RTC.setMinute(56);
}

void loop()
{
  print_date();
  if(digitalRead(Menu) == HIGH)
  {
    delay(25);
    if(digitalRead(Menu) == HIGH)
    {
      LCD.clear();
      LCD.print("Ti adjust conf....");
      delay(1000);
      alarm_mode = false;
      modify_date();
    }
  }
  if( ((digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH)) && (alarm_mode == false) )
  {
    delay(25);
    if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
    {
      LCD.clear();
      LCD.print("Set Alarm....");
      delay(1000);
      alarm_mode = true;
      modify_date();
      alarm_status = 1;
    }
  }
  if(alarm_mode)
  {
    unsigned long Now = millis();
    if( (Alarm_Year == RTC.getYear()) && (Alarm_Month == RTC.getMonth(century)) && (Alarm_Day == RTC.getDate()) && (Alarm_Hour == RTC.getHour(H12Flag , PmFlag)) && (Alarm_Minute == RTC.getMinute()) && (Alarm_Second == RTC.getSecond()) && (alarm_status == 1) )
    {
      digitalWrite(BUZZER, HIGH);
      alarm_status = 2;
      lastMillis = Now;
    }
    if( ((digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH)) && ( alarm_status == 2) )
    {
      delay(25);
      if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
      {
        digitalWrite(BUZZER, LOW);
        alarm_status = 0;
        alarm_mode = false;
      }
    }
    else if( (Now - lastMillis >= (60*1000)) && (alarm_status == 2) ) {
      lastMillis = Now;
      digitalWrite(BUZZER, LOW);
      alarm_status = 0;
      alarm_mode = false;
    }
  }

}
void print_date()
{
  /********************************/
  /* Printing current time on LCD */
  LCD.setCursor(0 ,0);
  //print current year on LCD
  LCD.print(RTC.getYear() , DEC);
  LCD.print("-");
  //print current Month on LCD
  LCD.print(RTC.getMonth(century) , DEC);
  LCD.print("-");
  //print current day on LCD
  LCD.print(RTC.getDate() , DEC);
  LCD.print(" ");
  //print current hour on LCD
  LCD.print(RTC.getHour(H12Flag , PmFlag) , DEC);
  LCD.print(":");
  //print current minute on LCD
  LCD.print(RTC.getMinute() , DEC);
  LCD.print(":");
  //print current second on LCD
  LCD.print(RTC.getSecond() , DEC);
  LCD.print("               ");
  LCD.setCursor(0 ,1);
  LCD.print("                ");
  delay(100);
  /********************************/
}

void modify_date()
{
  int Year, Month , Day , Hour , Minute , Second;

  //for updating year
  Year = RTC.getYear();
  LCD.clear();
  LCD.setCursor(0 ,0);
  LCD.print("Current year: ");
  while(1)
  {
    LCD.setCursor(0 ,1);
    LCD.print(Year , DEC);
    LCD.print("    ");
    
    if(digitalRead(UP) == HIGH)
    {
      delay(100);
      if(digitalRead(UP) == HIGH)   Year++;
    }
    
    else if(digitalRead(DOWN) == HIGH)
    {
      delay(100);
      if(digitalRead(DOWN) == HIGH)   if(Year <= 0) Year = RTC.getYear(); else Year--;
    }

    if(digitalRead(Menu) == HIGH)//if you press Menu button, it's going to set year with updated year
    {
      delay(100);
      if(digitalRead(Menu) == HIGH)
      {
        if(alarm_mode) Alarm_Year = Year; 
        else           RTC.setYear(Year); 
        break;
      }
    }

    //if you want to not set year with the updated one press RIGTH or LEFT button
    //in Alarm mode, of you want to set Alarm year same as the current year
    if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
    {
      delay(100);
      if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
      {
        if(alarm_mode)  Alarm_Year = RTC.getYear();
        else            Year = RTC.getYear(); 
        break;
      }
    }
  }
    
  //for updating month
  Month = RTC.getMonth(century);
  LCD.clear();
  LCD.setCursor(0 ,0);
  LCD.print("Current month: ");
  while(1)
  {
    LCD.setCursor(0 ,1);
    LCD.print(Month , DEC);
    LCD.print("    ");
    
    if(digitalRead(UP) == HIGH)
    {
      delay(100);
      if(digitalRead(UP) == HIGH)   Month = (Month + 1) % 12;
    }
    
    else if(digitalRead(DOWN) == HIGH)
    {
      delay(100);
      if(digitalRead(DOWN) == HIGH)   {Month--; if(Month == 0) Month = 12;}
    }

    if(digitalRead(Menu) == HIGH)//if you press Menu button, it's going to set year with updated year
    {
      delay(100);
      if(digitalRead(Menu) == HIGH)
      {
        if(alarm_mode) Alarm_Month = Month;
        else           RTC.setMonth(Month); 
        break;
      }
    }

    //if you want to not set year with the updated one press RIGTH or LEFT button
    //in Alarm mode, of you want to set Alarm Month same as the current Month
    if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
    {
      delay(100);
      if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
      {
        if(alarm_mode) Alarm_Month = RTC.getMonth(century);
        else           Month = RTC.getMonth(century); 
        break;
      }
    }
  }

  
  //for updating day
  Day = RTC.getDate();
  LCD.clear();
  LCD.setCursor(0 ,0);
  LCD.print("Current day: ");
  while(1)
  {
    LCD.setCursor(0 ,1);
    LCD.print(Day , DEC);
    LCD.print("    ");
    
    if(digitalRead(UP) == HIGH)
    {
      delay(100);
      if(digitalRead(UP) == HIGH)
      {
        //because these months consists of 31 days
        if( (Month == 1) || (Month == 3) || (Month == 5) || (Month == 7) || (Month == 8) ||(Month == 10) || (Month == 12) )
          Day =( Day + 1 ) % 31;
        //because these months consists of 30 days
        else if( (Month == 4) || (Month == 9) || (Month == 11) || (Month == 6) )
            Day =( Day + 1 ) % 30;
        //Feb. can be 28 or 29 days depending on if the current year is leap year or not
        else if(Month == 2)
        {
          if( (Year % 4 == 0) && (Year % 10 != 0) )//leap year
            Day =( Day + 1 ) % 29;
          else                                     //not a leap year
            Day =( Day + 1 ) % 28;
        }
      }
    }
    
    else if(digitalRead(DOWN) == HIGH)
    {
      delay(100);
      if(digitalRead(DOWN) == HIGH)
      //because these months consists of 31 days
      if( (Month == 1) || (Month == 3) || (Month == 5) || (Month == 7) || (Month == 8) ||(Month == 10) || (Month == 12) )
        { Day--; if(Day == 0) Day = 31; }
      //because these months consists of 30 days
      else if( (Month == 4) || (Month == 9) || (Month == 11) || (Month == 6) )
          { Day--; if(Day == 0) Day = 30; }
      //Feb. can be 28 or 29 days depending on if the current year is leap year or not
      else if(Month == 2)
      {
        if( (Year % 4 == 0) && (Year % 10 != 0) )//leap year
          { Day--; if(Day == 0) Day = 29; }
        else                                     //not a leap year
          { Day--; if(Day == 0) Day = 28; }
      }
    }

    if(digitalRead(Menu) == HIGH)//if you press Menu button, it's going to set year with updated year
    {
      delay(100);
      if(digitalRead(Menu) == HIGH)
      {
        if(alarm_mode) Alarm_Day = Day;
        else           RTC.setDate(Day); 
        break;
      }
    }

    //if you want to not set year with the updated one press RIGTH or LEFT button
    //in Alarm mode, of you want to set Alarm day same as the current day
    if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
    {
      delay(100);
      if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
      {
        if(alarm_mode) Alarm_Day = RTC.getDate();
        break;
      }
    }
  }

  //for updating hour
  Hour = RTC.getHour(H12Flag , PmFlag);
  LCD.clear();
  LCD.setCursor(0 ,0);
  LCD.print("Current Hour: ");
  while(1)
  {
    LCD.setCursor(0 ,1);
    LCD.print(Hour , DEC);
    LCD.print("    ");
    
    if(digitalRead(UP) == HIGH)
    {
      delay(100);
      if(digitalRead(UP) == HIGH)   Hour = (Hour + 1) % 24;
    }
    
    else if(digitalRead(DOWN) == HIGH)
    {
      delay(100);
      if(digitalRead(DOWN) == HIGH)   {Hour--; if(Hour == 0) Hour = 24;}
    }

    if(digitalRead(Menu) == HIGH)//if you press Menu button, it's going to set year with updated year
    {
      delay(100);
      if(digitalRead(Menu) == HIGH)
      {
        if(alarm_mode) Alarm_Hour = Hour;
        else           RTC.setHour(Hour);
        break;
      }
    }

    //if you want to not set year with the updated one press RIGTH or LEFT button
    //in Alarm mode, of you want to set Alarm hour same as the current hour
    if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
    {
      delay(100);
      if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
      {
        if(alarm_mode) Alarm_Hour = RTC.getHour(H12Flag , PmFlag);
        break;
      }
    }
  }

  //for updating Minute
  Minute = RTC.getMinute();
  LCD.clear();
  LCD.setCursor(0 ,0);
  LCD.print("Current Minute: ");
  while(1)
  {
    LCD.setCursor(0 ,1);
    LCD.print(Minute , DEC);
    LCD.print("    ");
    
    if(digitalRead(UP) == HIGH)
    {
      delay(100);
      if(digitalRead(UP) == HIGH)   Minute = (Minute + 1) % 60;
    }
    
    else if(digitalRead(DOWN) == HIGH)
    {
      delay(100);
      if(digitalRead(DOWN) == HIGH)   {Minute--; if(Minute < 0) Minute = 59;}
    }

    if(digitalRead(Menu) == HIGH)//if you press Menu button, it's going to set year with updated year
    {
      delay(100);
      if(digitalRead(Menu) == HIGH)
      {
        if(alarm_mode) Alarm_Minute = Minute;
        else           RTC.setMinute(Minute); 
        break;
      }
    }

    //if you want to not set year with the updated one press RIGTH or LEFT button
    //in Alarm mode, of you want to set Alarm minute same as the current minute
    if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
    {
      delay(100);
      if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
      {
        if(alarm_mode) Alarm_Minute = RTC.getMinute();
        break;
      }
    }
  }

  //for updating second
  Second = RTC.getSecond();
  LCD.clear();
  LCD.setCursor(0 ,0);
  LCD.print("Current second: ");
  while(1)
  {
    LCD.setCursor(0 ,1);
    LCD.print(Second , DEC);
    LCD.print("    ");
    
    if(digitalRead(UP) == HIGH)
    {
      delay(100);
      if(digitalRead(UP) == HIGH)   Second = (Second + 1) % 60;
    }
    
    else if(digitalRead(DOWN) == HIGH)
    {
      delay(100);
      if(digitalRead(DOWN) == HIGH)   {Second--; if(Second < 0) Second = 59;}
    }

    if(digitalRead(Menu) == HIGH)//if you press Menu button, it's going to set year with updated year
    {
      delay(100);
      if(digitalRead(Menu) == HIGH)
      {
        if(alarm_mode) Alarm_Second = Second;
        else           RTC.setSecond(Second); 
        break;
      }
    }

    //if you want to not set year with the updated one press RIGTH or LEFT button
    //in Alarm mode, of you want to set Alarm second same as the current second
    if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
    {
      delay(100);
      if( (digitalRead(RIGHT) == HIGH) || (digitalRead(LEFT) == HIGH) )
      {
        if(alarm_mode) Alarm_Second = RTC.getSecond();
        break;
      }
    }
  }
}
