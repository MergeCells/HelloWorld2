/*
8文字*2行のLCDをアレしてアレするやつ

pin接続

01: GND
02: 5V
03:   D11（PWMでバックライト制御・可聴音がするかも -> やめました）
04:   D2
05: GND（R/Wの切り替え用信号だけど，WしかしないからLOW->GND -> LCD側で短絡した）
06:   D3
07: N/A（使わない）
08: N/A
09: N/A
10: N/A
11:   D4
12:   D5
13:   D6
14:   D7
15: N/A（基盤のJP2,3を短絡すれば内部抵抗使ってバックライト光るよ）
16: N/A
*/

#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
//un long 4294967295まで
unsigned long now_t0 = 0;  //50日くらいでオーバーフロー
unsigned long chg_t1 = 0;
unsigned long chg_t2 = 0;
int frg = 0;

byte motion0[8] = {
  B00000,
  B00000,
  B11110,
  B11110,
  B11110,
  B11110,
  B00000,
};
byte motion1[8] = {
  B00000,
  B11110,
  B11110,
  B11110,
  B11110,
  B00000,
  B00000,
};
byte motion2[8] = {
  B00000,
  B01111,
  B01111,
  B01111,
  B01111,
  B00000,
  B00000,
};
byte motion3[8] = {
  B00000,
  B00000,
  B01111,
  B01111,
  B01111,
  B01111,
  B00000,
};
/*
  lcd.createChar(0, smiley);
  //lcd.begin(16, 2);  
  lcd.write(0);
*/

void setup() {
  lcd.createChar(0, motion0);
  lcd.createChar(1, motion1);
  lcd.createChar(2, motion2);
  lcd.createChar(3, motion3);
  lcd.begin(8, 2);
  //lcd.print("hello, world!");
  //analogWrite(9,0);  //  LCDコントラスト制御（0～100ぐらいで）
  //analogWrite(10,50);  //  LCDコントラスト制御（0～100ぐらいで）
  //analogWrite(11,100);  //  LCDコントラスト制御（0～100ぐらいで）
}

void loop() {
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(frg);
  if(frg++ >= 3)  frg = 0;
  
  now_t0 = millis();  
  chg_t1 = now_t0 / 1000;  //秒単位にする
  chg_t2 = now_t0 / 1000;
  
  lcd.setCursor(4, 0);
  /*
  if( chg_t1 < 600 ){
    if( chg_t1 < 60 ){
      if( chg_t1 < 10 )   lcd.print("   ");  //10秒未満
      else                lcd.print("  ");   //1分未満
    }
    else  lcd.print(" ");    //10分未満
  }
  lcd.print( chg_t1/60*100 + chg_t1%60);  // 分+秒
  */
  
  if( chg_t1 < 36000 ){
    if( chg_t1 < 3600 ){
      if( chg_t1 < 600 )   lcd.print("   ");  //10秒未満
      else                 lcd.print("  ");   //1分未満
    }
    else                   lcd.print(" ");    //10分未満
  }
  lcd.print( chg_t1/3600*100 + chg_t1/60%3600);  // 時+分
  
  
  
  lcd.setCursor(0, 1);
  lcd.print( now_t0 );
  
  delay(550 - millis() % 500);
}

