#include <Arduino.h>

//puertos esp
#define botonEmpezar1 25
#define botonGanar1 27
#define botonEmpezar2 14
#define botonGanar2 12

#define botonPerder 26

#define REDled 23
#define YELLOWled 22
#define GREENled 21

#define boton 25

//variables
unsigned long int tiempo1;
unsigned long int tiempo2;
unsigned long int diferencia;

bool estadoJugador1 = false;
bool estadoJugador2 = false;

bool ledStateRed = false;
bool ledStateYellow = false;
bool ledStateGreen = false;

enum Codigos {
  START = 0,
  RESTART = 1,
  STOP = 2,
  CLOSE = 3,
  TERMINO = 4,
  START_BOTON = 5
};

void setup()
{
  Serial.begin(9600);
  pinMode(botonEmpezar1, INPUT_PULLUP);
  pinMode(botonGanar1, INPUT_PULLUP);
  pinMode(botonEmpezar2, INPUT_PULLUP);
  pinMode(botonGanar2, INPUT_PULLUP);
  pinMode(botonPerder, INPUT_PULLUP);
  pinMode(boton, INPUT_PULLUP);
  pinMode(REDled, OUTPUT);
  pinMode(YELLOWled, OUTPUT);
  pinMode(GREENled, OUTPUT);
}

bool listoEmpezar = false;
bool iniciarBoton = false;

void terminarJuego(){
  listoEmpezar = false;
  

  tiempo1 = 1;
  tiempo2 = 1000000;
  diferencia = 1000000;

  int estadoJugador1 = false;
  int estadoJugador2 = false;

  int ledStateRed = false;
  int ledStateYellow = false;
  int ledStateGreen = false;

  digitalWrite(REDled, LOW);
  digitalWrite(YELLOWled, LOW);
  digitalWrite(GREENled, LOW);
}

void notificarTermino(){
  Serial.print(Codigos::TERMINO);
}

void recibirInfo(){
  if (Serial.available() > 0){
    int info = Serial.read();
    switch (info){
      case Codigos::START://iniciar
        listoEmpezar = true;
        break;
      case Codigos::STOP://terminar
        terminarJuego();
        break;
      case Codigos::RESTART://reiniciar
        terminarJuego();
        listoEmpezar = true;
      case Codigos::START_BOTON://inicia el juego del boton
        iniciarBoton = true;
        break;
    }
  }
}

void empezar(){
  ledStateRed = true;
  digitalWrite(REDled, ledStateRed);
  ledStateYellow = false;
  digitalWrite(YELLOWled, ledStateYellow);
}

void perder(){
  ledStateYellow = true;
  digitalWrite(YELLOWled, ledStateYellow);
  ledStateRed = false;
  digitalWrite(REDled, ledStateRed);
}

void ganarJ1(){
  tiempo1=millis();
  estadoJugador1 = true;
}

void ganarJ2(){
  tiempo2=millis();
  estadoJugador2 = true;
}

void calcularDiferencia(){
  diferencia=tiempo1-tiempo2;
  if(diferencia<0){
    diferencia=diferencia*-1;
  }
}

void ganar(){
  ledStateGreen = true;
  digitalWrite(GREENled, ledStateGreen);
  ledStateRed = false;
  digitalWrite(REDled, ledStateRed);
  
  delay(3000);

  terminarJuego();
  notificarTermino();
}

void perderXTiempo(){
  perder();
  tiempo1=10;
  tiempo2=100001;
  estadoJugador1 = false;
  estadoJugador2 = false;
}

void loop()
{
  recibirInfo();

  if (listoEmpezar){
    int botonEmpezarState1 = !digitalRead(botonEmpezar1);
    int botonPerderState = !digitalRead(botonPerder);
    int botonGanarState1 = !digitalRead(botonGanar1);
    int botonEmpezarState2 = !digitalRead(botonEmpezar2);
    int botonGanarState2 = !digitalRead(botonGanar2);


    if (botonEmpezarState1 == HIGH && botonEmpezarState2 == HIGH){
      empezar();
    }

    if (botonPerderState == HIGH){
      perder();
    }

    if ((botonGanarState1 == HIGH) && (ledStateYellow == LOW) && (estadoJugador1 == LOW)){
      ganarJ1();
    }

    if ((botonGanarState2 == HIGH) && (ledStateYellow == LOW) && (estadoJugador2 == LOW)){
      ganarJ2();
    }

    if (estadoJugador1==HIGH && estadoJugador2==HIGH){
      calcularDiferencia();
      if(diferencia<=1000){
        ganar();
      } else {
        perderXTiempo();
      }
    }
  }
}