#include <LiquidCrystal.h>

#define SOM0  300
#define SOM1  350
#define SOM2  400
#define SOM3  450
#define SOM4  500

// declarar as portas do arduino
int leds[4] = {2, 3, 4, 5};
char botoes[4] = {A3, A2, A1, A0};
int buzzer = 6;
int sons[5] = {SOM0, SOM1, SOM2, SOM3, SOM4};

// declarar as portas do lcd
LiquidCrystal lcd (12, 11, 10, 9, 8, 7);

//sequencia de ate 20 combinaçoes
int sequencia[20] = {}; 

int rodada = 0;

// em que posição ele vai ta na sequencia
int posicao_na_sequencia = 0;
 
 //se o o botao foi apertado ou nao
int botao_apertado = 0;

// se ele perdeu o jogo
int perdeu_o_jogo = 0;

// marcar pontuaçao
int pontuacao = 0;
int pontuacaofake = 0;

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


 // quando o jogo inicia, eh executado essa funçao de som, led e lcd
void somInicial() {
  
  digitalWrite(leds[0], HIGH);
  tone(buzzer, sons[0]);
  delay(200);
  noTone(buzzer);
  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], HIGH);
  tone(buzzer, sons[1]);
  delay(200);
  noTone(buzzer);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], HIGH);
  tone(buzzer, sons[2]);
  delay(200);
  noTone(buzzer);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], HIGH);
  tone(buzzer, sons[3]);
  delay(200);
  noTone(buzzer);
  digitalWrite(leds[3], LOW);

  delay(500);
  
  tone(buzzer, sons[4]);
  digitalWrite(leds[0], HIGH);
  digitalWrite(leds[1], HIGH);
  digitalWrite(leds[2], HIGH);
  digitalWrite(leds[3], HIGH);

  delay(500);

  digitalWrite(leds[0], LOW);
  digitalWrite(leds[1], LOW);
  digitalWrite(leds[2], LOW);
  digitalWrite(leds[3], LOW);
  
  delay(500);

  noTone(buzzer);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// sorteia um novo botao e adiciona na sequencia
void proximaRodada() {
  int numerorandom = random(0, 4); // um numero aleatorio de 0 a 3 e adiciona à "rodada", começando em sequencia 0 e até o jogador errar// por exemplo: sequencia[1] = 2, vai acender o led 2
  sequencia[rodada] = numerorandom;
  rodada++;
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// reproduz a sequência // loop que faz acontecer tudo, a cada rodada aumenta 1 led se o jogador acertar
void reproduzirSequencia() {

  if (rodada >= 0 && rodada < 4) {
    for (int i = 0; i < rodada; i++) {
      digitalWrite(leds[sequencia[i]], HIGH);
      tone(buzzer, sons[sequencia[i]]);
      delay(500);
      noTone(buzzer);
      digitalWrite(leds[sequencia[i]], LOW);
      delay(150);
    }
    noTone(buzzer);
  }

  else if(rodada >= 3 && rodada < 7) {
    for (int i = 0; i < rodada; i++) {
      digitalWrite(leds[sequencia[i]], HIGH);
      tone(buzzer, sons[sequencia[i]]);
      delay(300);
      noTone(buzzer);
      digitalWrite(leds[sequencia[i]], LOW);
      delay(100);
    }
    noTone(buzzer);
  }

  else if(rodada >= 7) {
    for (int i = 0; i < rodada; i++) {
      digitalWrite(leds[sequencia[i]], HIGH);
      tone(buzzer, sons[sequencia[i]]);
      delay(200);
      noTone(buzzer);
      digitalWrite(leds[sequencia[i]], LOW);
      delay(50);
    }
    noTone(buzzer);
  }
}
 

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


 // verifica se a jogada foi certa ou errada
void errouOUacertou() {
  for (int i = 0; i < rodada; i++) {
    jogadafeita();

    if (sequencia[posicao_na_sequencia] == botao_apertado) { // verifica cada botao apertado (se a jogada foi certa)
      pontuacaofake++;
    }

    if (sequencia[posicao_na_sequencia] != botao_apertado) { // se acertou, o botao apertado vai ser igual ao da sequencia e vai dar continuidade ao jogo
        errouperdeu(); // se errou, executa essa funçao
     }

     // e vai parar o jogo por que vai ter valor verdadeiro dentro da funçao "errouperdeu"
    if (perdeu_o_jogo == 1) {
        break;
      }
    posicao_na_sequencia++;
    }
  
  // redefine a variável para 0 para começar um novo loop
  posicao_na_sequencia = 0;
  lcd.clear();
  
  // se a rodada for diferente de 0, ou seja, nao ser a inicial, vai mostrar essa condiçao
  if (rodada != 0) {
    lcd.print("PONTUACAO: ");                   
    pontuacao = pontuacao + (pontuacaofake-(pontuacaofake-1)); 
    lcd.print(pontuacao);
  }
  
   // se a rodada for , ou seja, a inicial, vai mostrar essa condição
   if (rodada == 0) {
    lcd.print("PONTUACAO: ");
    pontuacao = pontuacao + (pontuacaofake-(pontuacaofake-1));
    lcd.print(pontuacao-1);
  }
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// quando um jogador clicar no botao certo, essa função ocorrerá
void jogadafeita() {
    for (int i = 0; i <= 3; i++) { // le o estado dos 4 botoes por causa do for, e o que tiver pressionado (LOW), será atrbuidado ao "botao_apertado", então se errar, "botao apertado" vai ser diferente do correto, e irá sair do while
      if (!digitalRead(botoes[i])) {
        botao_apertado = i;
 
        tone(buzzer, sons[i]); // toda vez que um botao for pressionado, vai ocorrer esse bloco
        digitalWrite(leds[i], HIGH); 
        delay(300);
        digitalWrite(leds[i], LOW);
        noTone(buzzer);
      }
    }
    delay(10);
}


// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


 // caso erre, essa funçao será executada
void errouperdeu() {
  lcd.clear();
  lcd.print("ERROOOOUU!! ");
  
  for (int i = 0; i <= 3; i++) { 
    tone(buzzer, sons[i]);
    digitalWrite(leds[i], HIGH);
    delay(200);
    digitalWrite(leds[i], LOW);
    noTone(buzzer);
  }                                  // quando errar esse bloco será executado como uma animaçao de erro do jogador
    
  for (int i = 0; i < 4; i++) {
    tone(buzzer, sons[2]);
    digitalWrite(leds[0], HIGH);
    digitalWrite(leds[1], HIGH);
    digitalWrite(leds[2], HIGH);
    digitalWrite(leds[3], HIGH);
    delay(100);
    digitalWrite(leds[0], LOW);
    digitalWrite(leds[1], LOW);
    digitalWrite(leds[2], LOW);
    digitalWrite(leds[3], LOW);
    delay(100);
  }
  
  noTone(buzzer);
 
  rodada = 0;
  perdeu_o_jogo = 1; // como precisa ser diferente de 0 a condição pro loop inicial ser utilizado, atribui-se o valor 1 pra ela
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


void setup() {

// iniciando o lcd 16x2
  lcd.begin(16,2);

// colocando botao, led e buzzer pra suas funçoes
  for (int i = 0; i <= 3; i++) {
    pinMode(leds[i], OUTPUT);
  }
  
  for (int i = 0; i <= 3; i++) {    
    pinMode(botoes[i], INPUT_PULLUP);
  }
 
  pinMode(buzzer, OUTPUT);
}


void loop() {

  if (perdeu_o_jogo == 1) { //depois que o jogador errar, as variaveis resetam, entao o jogo recomeça com a variavel "rodada" = 0 de novo
    sequencia[20] = {};
    posicao_na_sequencia = 0;
    perdeu_o_jogo = 0;
    pontuacao = 0;
  }
  // todo inicial de jogo vai executar esse codigo
  if (rodada == 0) {
    
    lcd.clear();
    lcd.print("APERTE BOTAO");
    lcd.setCursor(0, 1);
    lcd.print("PRA INICIAR!");

    // Aguardar até que qualquer botão seja pressionado
    while (digitalRead(botoes[0]) == HIGH && digitalRead(botoes[1]) == HIGH && digitalRead(botoes[2]) == HIGH && digitalRead(botoes[3]) == HIGH) {
    }
    
    // o gerador de "sementes" aleatorias para o codigo
  randomSeed(micros());
    
    delay(200);
    
    lcd.clear();
    lcd.print("VAMOS JOGAR!");
    somInicial();
    lcd.clear();
    delay(500);
    lcd.print("PONTUACAO: 0");
  }

  // funçoes que serao executadas no codigo
  proximaRodada(); 
  reproduzirSequencia();
  errouOUacertou();
 
  delay(1000);
}
