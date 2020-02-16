/* BANCADA DE TESTE JACTO
 * ARDUINO NANO
 * V.1 
 * gerar sinal de rotação (sinal negativo indutivo NPN)
 *  - roda direita +/- 20 dentes
 *  - roda esquerda +/- 20 dentes
 *  - sensor de vazão 10 dentes
 * leitura dos potenciômetros
 *  - roda esquerda+direita simular velocidade
 *  - vazão simular velocidade
 *  - pressão apenas leitura, o mesmo sinal que vai para o Arduino vai pro controlador
 * leitura do comando enviado pelo controlador para abrir/fechar regulador de pressão
 *  - necessário manualmente ajustar o sinal de pressão enviado para o controlador
 */

#define pushButton 2
#define outRodas 3
#define outVazao 4
#define CLK1 7
#define DIO1 8
#define CLK2 9
#define DIO2 10
#define CLK3 11
#define DIO3 12
#define LED_BUILTIN 13
#define potRodas A0
#define potVazao A1
#define potPressao A2
#define inAumentar A3
#define inDiminuir A4

const int max_rodas = 100; //rotacao maxima das rodas
int max_vazao = 1000; //rotacao maxima do sensor de vazao
unsigned long rpm_rodas;
unsigned long rpm_vazao;
bool state_rodas = false;
bool state_vazao = false;

#include <TM1637Display.h>

TM1637Display display1(CLK1, DIO1); //RODAS
TM1637Display display2(CLK2, DIO2); //VAZAO
TM1637Display display3(CLK3, DIO3); //PRESSAO
  
const uint8_t SEG_JACT[] = {
  SEG_B | SEG_C | SEG_D | SEG_E,                   // J
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,   // A
  SEG_A | SEG_D | SEG_E | SEG_F,                   // C
  SEG_D | SEG_E | SEG_F | SEG_G                    // t
  };

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(outRodas, OUTPUT);
  pinMode(potRodas, INPUT);
  pinMode(outVazao, OUTPUT);
  pinMode(potVazao, INPUT);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(potPressao, INPUT);
  pinMode(inAumentar, OUTPUT);
  pinMode(inDiminuir, OUTPUT);
  
  display1.setBrightness(7);  //set the diplay to maximum brightness (0x0f)
  display2.setBrightness(7);  //set the diplay to maximum brightness (0x0f)
  display3.setBrightness(7);  //set the diplay to maximum brightness (0x0f)
  display1.showNumberDec(1, false);
  display2.showNumberDec(2, false);
  display3.showNumberDec(3, false);
  delay(1200);
}

void loop() {
  update_displays();
  update_signals();
}
