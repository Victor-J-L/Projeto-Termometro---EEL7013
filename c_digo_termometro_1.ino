#include <LiquidCrystal_I2C.h>

//Programa: Sensor de temperatura I2C MLX90614 Arduino
//Autor: Arduino e Cia
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//Define o endereco I2C do display e qtde de colunas e linhas
LiquidCrystal_I2C lcd(0x27, 16, 2);
//Array que desenha o simbolo de grau
byte grau[8] = {B00110, B01001, B01001, B00110,
                B00000, B00000, B00000, B00000,};

double temp_amb;
double temp_obj;
double temp_obj1;
int botao = 7;
int ledVerde = 4;
int ledVermelho = 8;
int buzzer = 13;
int leituraBotao = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("Sensor de temperatura MLX90614");
  //Inicializa o display LCD I2C
  lcd.init();
  lcd.backlight();
  //Atribui a "1" o valor do array "grau", que desenha o simbolo de grau
  lcd.createChar(1, grau);
  //Inicializa o MLX90614
  mlx.begin();
  //Inicializa os leds e o buzzer e o botão
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer,LOW);
}
void tempNormal(){
  digitalWrite(ledVerde,HIGH);
  digitalWrite(ledVermelho,LOW);
  digitalWrite(buzzer,HIGH);
  delay(110);
  digitalWrite(buzzer,LOW);
  delay(110);
  digitalWrite(buzzer,HIGH);
  delay(110);
  digitalWrite(buzzer,LOW);
  delay(110);
  }
  
void tempCovid(){
  digitalWrite(ledVerde,LOW);
  digitalWrite(ledVermelho,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(2000);
  digitalWrite(buzzer,LOW);
  delay(110);
  }

 //Leitura do objeto
 void leituraTemp()
 {
    for (int i = 0 ; i<20 ; i++){
      temp_obj = mlx.readObjectTempC()+ temp_obj;
      delay(1); 
    }
    temp_obj/=20.0;
    temp_obj+= 2.82; //Fator de Correção
  }
void loop()
{
  //Leitura da temperatura ambiente e do objeto
  temp_amb = mlx.readAmbientTempC();
  temp_obj1 = mlx.readObjectTempC();
  leituraBotao = digitalRead(botao);



  digitalWrite(ledVerde,LOW);
  digitalWrite(ledVermelho,LOW);
  delay(5);
  if (leituraBotao == 0) {
    leituraTemp();
    if (temp_obj<38.0) {
      tempNormal();

      lcd.setBacklight(LOW);
      delay(200);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setBacklight(HIGH);
      lcd.setCursor(2, 0);
      lcd.print("Temperatura:");
      lcd.setCursor(5, 1);
      lcd.print(temp_obj);
      lcd.setCursor(10, 1);
      lcd.write(1);
      delay(2500);

      
      lcd.setBacklight(LOW);
      delay(200);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setBacklight(HIGH);
      lcd.setCursor(2, 0);
      lcd.print("Temperatura");
      lcd.setCursor(5, 1);
      lcd.print("Normal");
      delay(2500);

      lcd.setBacklight(LOW);
      delay(200);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setBacklight(HIGH);
      lcd.setCursor(2, 0);
      lcd.print("Temp:");
      lcd.setCursor(8, 0);
      lcd.print(temp_obj);
      lcd.setCursor(13, 0);
      lcd.write(1);
      lcd.setCursor(2, 1);
      lcd.print("Temp. Normal");
       }

    
    
    else if (temp_obj>=38.0) {
      tempCovid();
      lcd.setBacklight(LOW);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(2, 0);
      lcd.print("Temperatura:");
      lcd.setCursor(5, 1);
      lcd.print(temp_obj);
      lcd.setCursor(10, 1);
      lcd.write(1);
      delay(200);
      lcd.setBacklight(HIGH);
      delay(2500);

      
      lcd.setBacklight(LOW);
      delay(200);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setBacklight(HIGH);
      lcd.setCursor(2, 0);
      lcd.print("Temperatura");
      lcd.setCursor(6, 1);
      lcd.print("Alta");
      delay(2500);

      lcd.setBacklight(LOW);
      delay(200);
      lcd.setCursor(0, 0);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setBacklight(HIGH);
      lcd.setCursor(2, 0);
      lcd.print("Temp:");
      lcd.setCursor(8, 0);
      lcd.print(temp_obj);
      lcd.setCursor(13, 0);
      lcd.write(1);
      lcd.setCursor(3, 1);
      lcd.print("Temp. Alta");                                                                                                                   
      }
     }
  
  //Mostra as informacoes no display
      lcd.setBacklight(HIGH);
      lcd.setCursor(0, 0);
      lcd.print("  ");
      lcd.setCursor(2, 0);
      lcd.print("Temp:");
      lcd.setCursor(7, 0);
      lcd.print(" ");
      lcd.setCursor(8, 0);
      lcd.print(temp_obj);
      lcd.setCursor(13, 0);
      lcd.write(1);
  //Mostra as informacoes no Serial Monitor
  Serial.print("Ambiente = ");
  Serial.print(temp_amb);
  Serial.print("*CtObjeto = ");
  Serial.print(temp_obj1); Serial.println("*C");
  //Aguarda 1 segundo ate nova leitura
  delay(1000);
     }
  
