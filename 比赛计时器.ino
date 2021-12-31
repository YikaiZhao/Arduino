#include <Wire.h>//IIC通信库
#include <LiquidCrystal_I2C.h>//LCD库
#include <IRremote.h>//红外接收库
#include <HCSR04.h>//超声波
#include <DS3231.h>//时钟
DS3231 Clock;
LiquidCrystal_I2C lcd(0x27,16,2);
 SR04 Ultra1(12,11);//记录圈数
 SR04 Ultra2(8,10);//记录名次
IRrecv ir(9);
void setup() 
{
  Wire.begin();
  lcd.init();
  lcd.backlight();
  decode_results results;
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  
}
bool h12;
bool PM;
String minute, second;
String str;//组合比赛成绩
long a,b;//存储超声波的距离
int j;//用于记录圈数
int mingci;
void loop() 
{
   digitalWrite(4,HIGH);
   digitalWrite(5,HIGH);
   digitalWrite(6,HIGH);
   digitalWrite(7,HIGH);
  while(results.value!=0xFF38C7)//OK键
  {
  }
  //DS3231计时
  tone(3,1000);//蜂鸣器发声
  delay(1000);
   digitalWrite(4,HIGH);
   digitalWrite(5,HIGH);
   digitalWrite(6,HIGH);
   digitalWrite(7,HIGH);
  while(j!=4)
  {
    a=Ultra1.Distance();
    if(a<50)
    j++;                //记录圈数
    lcd.setCursor(1,14);
    lcd.print(j);
    delay(500);
  }
  while(results.value!=0xFF9867)  //0按键结束比赛
  {
    b=Ultra2.Distance();
    minute = String(Clock.getMinute(), DEC);
    second = String(Clock.getSecond(), DEC);
    str = minute + ":" + second;
    if(b<50&&mingci==0)
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(str);
      lcd.setCursor(1,0);
      lcd.print("The First");
      mingci++;
      delay(500);
      digitalWrite(4,LOW);
    }
    if(b<50&&mingci==1)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(str);
      lcd.setCursor(1,0);
      lcd.print("The Second");
      mingci++;
      delay(500);
       digitalWrite(5,LOW);
    }
    if(b<50&&mingci==2)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(str);
      lcd.setCursor(1,0);
      lcd.print("The Third");
      mingci++;
      delay(500);
       digitalWrite(6,LOW);
    }
    if(b<50&&mingci==3)
     {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(str);
      lcd.setCursor(1,0);
      lcd.print("The Fourth");
      mingci++;
      delay(500);
       digitalWrite(7,LOW);
    }
  }
}
