//Programa: Acelerometro MMA8452
//Autor: Arduino e Cia
//Baseado no programa exemplo da biblioteca Sparkfun SFE_MMA8452
#include <Wire.h>
#include <SFE_MMA8452Q.h>
#include <TimerOne.h>
//Cria uma instancia do MMA8452 chamada acelerometro
//com endereco I2C 0x1C (pino SA0 em LOW/Desligado)
MMA8452Q acelerometro(0x1D);
#define buzzer 9
void setup()
{
  Serial.begin(9600);
  Serial.println("Teste de comunicacao MMA8452");
  //Inicializa o acelerometro com o valores padrao de +/-2g e
  //saida de 800 Hz
  acelerometro.init();
  //Utilize a linha abaixo para inicializar o acelerometro com
  //+/-2g, 4g, or 8g, usando SCALE_2G, SCALE_4G, ou SCALE_8G
  //acelerometro.init(SCALE_4G);
  //Utilize a linha abaixo para determinar tambem a frequencia
  //de saida do acelerometro (padrao de 800 Hz), utilizando
  //como segundo parametro ODR_800 (800 Hz), ODR_400 (400 Hz),
  //ODR_200 (200 Hz), ODR_100 (100 Hz), ODR_50 (50 Hz),
  //ODR_12 (12.5 Hz), ODR_6 (6.25 Hz), ou ODR_1 (1.56 Hz)  
  //acelerometro.init(SCALE_8G, ODR_6);
  Timer1.initialize(30000000);
}
void loop()
{
  //A linha abaixo aguarda o envio de novos dados pelo acelerometro
  if (acelerometro.available())
  {
    //Efetua a leitura dos dados do sensor
    acelerometro.read();
    //acelerometro.read() atualiza dois grupos de variaveis:
    //* int x, y, e z armazena o valor de 12 bits lido do
    //acelerometro
    // * float cx, cy, e cz armazena o calculo da aceleracao
    //dos valores de 12 bits. Essas variaveis estao em
    //unidades de "g"
    
    //Mostra as coordenadas lidas do sensor
    printCalculatedAccels();
    
    //Selecione a linha abaixo para mostra os valores digitais
    //printAccels();
    
    //Mostra a orientacao (retrato/paisagem/flat)
    printOrientation();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    delay(500);
  }
}
void printAccels()
{
  Serial.print(acelerometro.x, 3);
  Serial.print("t");
  Serial.print(acelerometro.y, 3);
  Serial.print("t");
  Serial.print(acelerometro.z, 3);
  Serial.print("t");
}
void printCalculatedAccels()
{ 
  Serial.println("Coord X");
  Serial.print(acelerometro.cx, 3);
  Serial.println();
  Serial.println("Coord Y");
  Serial.print(acelerometro.cy, 3);
  Serial.println();
  Serial.println("Coord Z");
  Serial.println(acelerometro.cz, 3);
  Serial.println("Tempo: ");
  Serial.println(Timer1.read());
}
void printOrientation()
{
  //acelerometro.readPL() retorna um byte contendo informacoes sobre
  //a orientacao do sensor (retrato/paisagem)
  //PORTRAIT_U (Retrato Up/Para cima), PORTRAIT_D (Retrato Down/Para Baixo), 
  //LANDSCAPE_R (Paisagem right/direita), LANDSCAPE_L (Paisagem left/esquerda)
  //e LOCKOUT (bloqueio)
  byte pl = acelerometro.readPL();
  Serial.println();
  switch (pl)
  {
  case PORTRAIT_U:
    Serial.println("Retrato Para Cima");
    noTone(buzzer);
    break;
  case PORTRAIT_D:
    Serial.println("Retrato Para Baixo");
    noTone(buzzer);
    break;
  case LANDSCAPE_R:
    Serial.println("Paisagem Direita");
    noTone(buzzer);
    break;
  case LANDSCAPE_L:
    Serial.println("Paisagem Esquerda");
    noTone(buzzer);
    break;
  case LOCKOUT:
    Serial.println("Plano");
    tone(buzzer,300);
    
    break;
  default:
    noTone(buzzer);
  }
}