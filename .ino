#include <LiquidCrystal_I2C.h>  
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

////////////////CONFIGURAÇÕES/////////////////////////////////////////
//PLACA SOLAR
const float potencia_painel = 60; // Potência do painel solar em Watts-Pico
const float capacidade_bateria = 480; // Carga da bateria em Watts

//DIMENSÃO DA PLACA
const float altura_painel = 25; // Altura do painel solar
const float largura_painel = 27; // Largura do painel solar 
String medida_painel = "cm"; // Tipo da medida do painel solar, pode ser escrito "m","cm" ou "mm"

//LAMPADAS
const int lampadas = 5; // Quantidade de lampadas que vai consumir a bateria
const int potencia_lampada = 10; // Potência das lampadas em Watts

//SISTEMA DE BATERIA 
const int porcentagem_desativar = 95; // Porcentagem da bateria para desativar para evitar sobrecarga
const int porcentagem_ativar = 80; // Porcentagem da bateria para reativar a transferência de potência após ter chegado no limite

//MODO HORA
const int modo_hora = 1; // Modo hora: 0 - Todo processo é feito por segundo
                        // 1 - Todo processo é feito por hora (Não converte para segundos)

//DEBUG
const int aumento_debug = 0; // Utilize apenas para debug, aumento da bateria direta
const int consumo_debug = 0; // Utilize apenas para debug, diminução da bateria direta

////////////////CÓDIGO DO ARDUINO ABAIXO/////////////////////////////////////////

int ldr_pin = A0;
float carga_bateria = 0;
bool desativar = false;

const int button_pin = 13;
unsigned long last_button_press = 0;  
const unsigned long button_delay = 200; 
bool consumo_mode = false;

int conversao_hora;
float area_painel;

// Desenho de lampada
byte light_ul[8] = { B00000, B00111, B01100, B01000, B10000, B10000, B10000, B10000 };
byte light_ur[8] = { B00000, B11100, B00110, B00010, B00001, B00001, B00001, B00001 };
byte light_dl[8] = { B01001, B01010, B01010, B00100, B00111, B00100, B00100, B00011 };
byte light_dr[8] = { B10010, B01010, B01010, B00100, B11100, B00100, B00100, B11000 };

void setup() {
  pinMode(button_pin, INPUT);
  Serial.begin(9600);
  lcd.begin(16,2);   
  lcd.backlight();               
  lcd.createChar(0, light_ul);
  lcd.createChar(1, light_ur);
  lcd.createChar(2, light_dl);
  lcd.createChar(3, light_dr);
  lcd.setCursor(0,0);
  lcd.write(byte(0));
  lcd.setCursor(1,0);
  lcd.write(byte(1));
  lcd.setCursor(0,1);
  lcd.write(byte(2));
  lcd.setCursor(1,1);
  lcd.write(byte(3));
  lcd.setCursor(3,0);
  lcd.print("Bateria");
  lcd.setCursor(9,1);
  lcd.print("%");

  // Conversão para m²
  if (medida_painel == "cm"){
    area_painel = (altura_painel * largura_painel)/10000;
  }else if (medida_painel == "mm"){
    area_painel = (altura_painel * largura_painel)/1000000;
  } else {
    area_painel = altura_painel * largura_painel;
  }
  
  // Modo hora
  if (modo_hora == 1){
    conversao_hora = 1;
  } else{
    conversao_hora = 3600;
  }
}

float converterLux(){
  // Essas constantes devem corresponder aos atributos "gama" e "rl10" do fotoresistor
  // Código utilizado do Wokwi para pegar Lux
  const float GAMMA = 0.7;
  const float RL10 = 50;

  // Converte o valor analógico em valor lux:
  int analogValue = analogRead(ldr_pin);
  float voltage = analogValue / 1024. * 5;
  float resistance = 2000 * voltage / (1 - voltage / 5);
  float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));


  return lux;
}

void aumento(){
  Serial.println("Carregando...");
  const float conversao_lux = 93;
  float lux = converterLux();


  float incremento = (((lux * area_painel)/conversao_lux) * potencia_painel) / conversao_hora;
  Serial.println(incremento);
  carga_bateria += incremento + aumento_debug;
  Serial.println(carga_bateria);

  if (carga_bateria > capacidade_bateria) {
    carga_bateria = capacidade_bateria;
  }
}

void consumo(){
  Serial.println("Consumindo...");
  float potencia_resultado = (lampadas * potencia_lampada)/ conversao_hora;
  carga_bateria -= potencia_resultado + consumo_debug; 
  Serial.println(potencia_resultado);
  if (carga_bateria <= 0){
    carga_bateria = 0;
  }
}

void loop() {
float carga_porcento = (carga_bateria / capacidade_bateria) * 100;
if (carga_porcento <= porcentagem_desativar && desativar == false){
  aumento();
  } else{
  desativar = true;
  Serial.println("Desativado");
}
if (desativar == true && carga_porcento <=  porcentagem_ativar){
    desativar = false;
    Serial.println("Ativado");
}

int button_press = digitalRead(button_pin);
if (button_press == HIGH && millis() -  last_button_press > button_delay){
  last_button_press = millis();
  consumo_mode = !consumo_mode;
}

if (consumo_mode == true){
  consumo();
}

lcd.setCursor(3,1);
lcd.print(carga_porcento);
if (carga_porcento >= 100){
  lcd.setCursor(8,1);
  lcd.print(" ");
}
Serial.print("Nível de carga da bateria: ");
Serial.print(carga_porcento);
Serial.println(" %");

delay(1000);  
}
