void update_displays() {

//-----------------------------------------------------RODAS  
  unsigned long ler_rodas = analogRead(potRodas);
  rpm_rodas = (ler_rodas * max_rodas) / 1023;
  display1.showNumberDec(rpm_rodas, false);


//-----------------------------------------------------VAZAO
  unsigned long ler_vazao = analogRead(potVazao);
  rpm_vazao = (ler_vazao * max_vazao) / 1023;
  display2.showNumberDec(rpm_vazao, false);


//---------------------------------------------------PRESSAO
  unsigned long ler_pressao = analogRead(potPressao);
  display3.showNumberDec((ler_pressao * 100) / 1023, false);  //em percentual
}

void update_signals() {

//-----------------------------------------------------RODAS 
  static unsigned int last_rodas; 
//hora da ultima inversao do sinal das rodas (static=nao perde)

  int intervalo_rodas = 3600000 / (rpm_rodas * 20 * 2); 
//intervalo de alternancia, em milisegundos, com 20 dentes

  unsigned int agora = millis();
  if (agora > (last_rodas + intervalo_rodas)) {
    state_rodas = !state_rodas;
    digitalWrite(outRodas, state_rodas);
    last_rodas = agora;
  }

//-----------------------------------------------------VAZAO
  static unsigned int last_vazao; 
  int intervalo_vazao = 3600000 / (rpm_vazao * 10 * 2); 
  if (agora > (last_vazao + intervalo_vazao)) {
    state_vazao = !state_vazao;
    digitalWrite(outVazao, state_vazao);
    last_vazao = agora;
  }

//-----------------------------LEITURA DO COMANDO DE PRESSÃO
  if(digitalRead(inAumentar) == HIGH) max_vazao = max_vazao * 1.01;
  if(digitalRead(inDiminuir) == HIGH) max_vazao = max_vazao * 0.99;
}
