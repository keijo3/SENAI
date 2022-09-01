#include <LiquidCrystal.h>

#define pino_trigger 11
#define pino_echo 10
#define PWM 9

LiquidCrystal lcd(7,6,5,4,3,2);

int menu = 1;
int estadoA, estadoB=0;
int cont = 1;
int lote = 0;
int dutycycle, vel = 0;
int s4 = 0;
int pecast = 0;
int  estado = 0;
float distancia;



void liga_desliga(){
  if (analogRead(A0) > 500 && analogRead(A0) < 800){
    estadoA = 1;
    if ((estadoA == 1)){
      estado = !estado;
      delay(500);      
    }
    
   
    if (estado == 1){
      LimpaTela();
      lcd.home();
      lcd.print("INICIANDO");
      lcd.setCursor(0, 1);
      lcd.print("ESTEIRA...");
      delay(1000);
      LimpaTela();
      lcd.home();
      lcd.print("CONTA SENAI");
      lcd.setCursor(0, 1);
      lcd.print("GIANLUCA B.");
      delay(1000);
      LimpaTela();
    }
    else{
      lcd.print("DESLIGANDO");
      lcd.setCursor(0, 1);
      lcd.print("ESTEIRA...");
      delay(1000);
      LimpaTela();
      dutycycle = 0;
      lote = 0;
      cont = 1;
      pecast=0;
    }
  }
   estadoA = 0;
}

  void left()
  {
    if (analogRead(A0) > 300 && analogRead(A0) < 500)
    {
      menu--;
      if (menu < 1)
      {
        menu = 1;
      }
      while (analogRead(A0) > 300 && analogRead(A0) < 500)
      {
        delay(20);
        lcd.clear();
      }
    }
  }
  void right()
  {
    if (analogRead(A0) < 50)
    {
      menu++;
      if (menu > 2)
      {
        menu = 2;
      }

      while (analogRead(A0) < 50)
      {
        delay(20);
        lcd.clear();
      }
    }
  }
  void up()
  {
    if (menu == 1)
    {
      if (analogRead(A0) > 50 && analogRead(A0) < 150)
      {
        cont++;
      }
      if (cont > 65000)
      {
        cont = 65000;
      }
      while (analogRead(A0) > 50 && analogRead(A0) < 150)
      {
        delay(20);
        lcd.clear();
      }
    }
    if (menu == 2)
    {
      if (analogRead(A0) > 50 && analogRead(A0) < 150)
      {
        dutycycle = dutycycle + 10;
      }
      if (dutycycle > 100)
      {
        dutycycle = 100;
      }
      while (analogRead(A0) > 50 && analogRead(A0) < 150)
      {
        delay(20);
        lcd.clear();
      }
    }
  }
  void down()
  {
    if (menu == 1)
    {
      if (analogRead(A0) > 150 && analogRead(A0) < 300)
      {
        cont--;
      }

      if (cont < 1)
      {
        cont = 1;
      }

      while (analogRead(A0) > 150 && analogRead(A0) < 300)
      {
        delay(20);
        lcd.clear();
      }
    }
    if (menu == 2)
    {
      if (analogRead(A0) > 150 && analogRead(A0) < 300)
      {
        dutycycle = dutycycle - 10;
      }
      if (dutycycle < 0)
      {
        dutycycle = 0;
      }
      while (analogRead(A0) > 150 && analogRead(A0) < 300)
      {
        delay(20);
        lcd.clear();
      }
    }
  }
  void LimpaTela(){
    lcd.clear();
    lcd.setCursor(0, 0);
  }
  void setup()
  {
    lcd.begin(16, 2);
    LimpaTela();
    pinMode(A0, INPUT);
    pinMode(10, INPUT);
    pinMode(11,OUTPUT);
    pinMode(PWM,OUTPUT);
   
  }
  void loop(){
    liga_desliga();
    left();
    right();
   	delay(1000);
    if (menu == 1 && estado == 1){
      
      lcd.home();
      lcd.print("PECAS/LOTE:");
      lcd.print(cont);
      lcd.setCursor(0, 1);
      lcd.print("TOTAL LOTES:");
      lcd.print(lote);
      if (s4 >= cont)
      {
        lote++;
        s4 = 0;
      }
      up();
      down();
      liga_desliga();
    }
    if (menu == 2 && estado == 1){
      lcd.home();
      lcd.print("MOTOR:");
      lcd.print(dutycycle);
      lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("PECAS:");
      lcd.print(pecast);
      up();
      down();
      liga_desliga();
      if (dutycycle==0)
      {
        analogWrite(PWM,0);
      }
      else{
        analogWrite(PWM,map(dutycycle,0,100,0,255));
       }
      
      
    }
     if (distancia<=300 && distancia >=20)
      {
         s4++;
       	 pecast++;	
      }
  digitalWrite(pino_trigger, LOW);
  delay(0005);
  digitalWrite(pino_trigger, HIGH);
  delay(0010);
  digitalWrite(pino_trigger, LOW);
  
  distancia = pulseIn (pino_echo, HIGH);
  distancia = distancia/58;
    
  }
