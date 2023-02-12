#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Timers.h>
#include "OneButton.h"
//---------------------------------------------------------------------------------------------------
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//------------------------------------------------------------------------------------------------


#define hamulec 4       //czujnik hamowania     
#define motor_pwm 11    //
#define manetka A0          //182 min   867 max
//#define button1 5  
//#define button2 6
#define LED_tyl 9
#define LED_przod 10
#define czuj_predkosci 2    //kotaktorn
#define Vbattery A1

OneButton button1(5, true, true);     //swiatla
OneButton button2(6, true, true);     //power

void interrupt_rpm();

Timer rpm_counter_timer;
Timer disp_timer;
Timer speed_modes_timer;

void setup() {

  Serial.begin(9600);
  rpm_counter_timer.begin(MSEC(1000));
  disp_timer.begin(MSEC(500));
  speed_modes_timer.begin(MSEC(10));

  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);

  pinMode(manetka, INPUT);
  //pinMode(button1, INPUT_PULLUP);          //przyciski manetki
  // pinMode(button2, INPUT_PULLUP);
  pinMode(hamulec, INPUT_PULLUP);
  pinMode(motor_pwm, OUTPUT);
  pinMode(LED_tyl, OUTPUT);
  pinMode(LED_przod, OUTPUT);
  pinMode(Vbattery, INPUT);

  pinMode(czuj_predkosci, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(czuj_predkosci), interrupt_rpm, FALLING);


 if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 16);
  display.println("Hulajnoga");
  display.setCursor(0, 40);
  display.setTextSize(1);
  display.println("Beta edition 0.1");
  display.display(); 
  delay(3000);
  display.clearDisplay();
  display.display();
}


//-----------------------------------------------------------------
void click1() {
 // Serial.println("Button 1 click.");

} // click1



bool lights;
void doubleclick1() {


 if( lights == 1){
    lights = 0;  
  }
  else{
    lights = 1;
  }
  
} 


void click2() {
 // Serial.println("Button 2 click.");
} // click2

bool speed_mode = 0;
void doubleclick2() {
if( speed_mode == 1){
    speed_mode = 0;  
  }
  else{
    speed_mode = 1;
  }

} 
//--------------------------------------------------------------------------------


//----------------------------------------------------------------------
void swiatla(int on_off){
 bool brake = digitalRead(hamulec);
    
  if(on_off == 1 && brake == 0){
   analogWrite(LED_przod, 255);
   analogWrite(LED_tyl, 40);
  }
  if(on_off == 1 && brake == 1){
   analogWrite(LED_przod, 255);
   analogWrite(LED_tyl, 255);
  }
  if(on_off == 0 && brake == 1){
   analogWrite(LED_przod, 0);
   analogWrite(LED_tyl, 255);
  }
 if(on_off == 0 && brake == 0){
   analogWrite(LED_przod, 0);
   analogWrite(LED_tyl, 0);
  }
}
//-----------------------------------------------------------------------
//-------------------------------------------------------------------------

int srednica = 50; //centymtry
volatile int impulsy;
 float kph ;

void predkosc (){
 if (rpm_counter_timer.available())
  {
    //Serial.println(srednica); 
      //Serial.println(impulsy);  
    int rpm = 60 * impulsy;
     kph = srednica * rpm * 0.001885;
   //Serial.print(kph); 
     // Serial.print(">"); 
     // Serial.println(rpm);
   impulsy =0;
    rpm_counter_timer.restart();
  }
  //return kph;
}

void interrupt_rpm(){
  static unsigned long lastTime;
  unsigned long timeNow = millis();
  if (timeNow - lastTime < 50){
    return;
  }
    
  impulsy++;
  lastTime = timeNow;

}
//-----------------------------------------------------------------------------------------

float vbat(){

  float vbat = analogRead(Vbattery) * (5.00 / 1023.00) * 2 ; // tutaj mnozenie trzeba dac zeby nie zabijać procesora i jeszcze dobre wartosci ustawic
  return vbat;

}

//--------------------------------------------------------------------------------------------wypadało by dodac jeszcze tyyby jakies
int throttle_modes(){
  
   int throttle_value = analogRead(manetka);
   bool brake = digitalRead(hamulec);

  if (brake == 1) throttle_value = 182;
  throttle_value = map(throttle_value, 182, 867, 0, 255);

  if(speed_mode == 0){
    analogWrite(motor_pwm, throttle_value);
  }


}

//-----------------------------------------------------------------------------------------------


void oled_disp(){


if (disp_timer.available())
  {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Ubat:");
  display.setTextSize(2);
  display.setCursor(35, 0);
  display.print(vbat());
  display.print("V");
  display.setCursor(0, 25);
  display.println("V:");  
  display.setCursor(25, 25);
  display.print(kph);
  display.setTextSize(1);
  display.print("km/h");
  
    
  display.display();
  


    disp_timer.restart();
  }
  


}



void loop() {

  button1.tick();
  button2.tick();
  swiatla (lights);
  //vbat();
  predkosc();
  throttle_modes();
  oled_disp();
  //Serial.println(impulsy);
  



}




