
#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>
#include <PWM.h>
#include <SimpleTimer.h>
/*
It is an avoidable property with Arduino's 8 bit timers. You can use pins 2, 3, 6, 7, 8, 11, 12, 44, 45, and 46. 
Pins 10 and 4 are lost for pwm output (they still work for digital input and output). 
In your case, since you use delay functions and the safe version of InitTimers(), you should avoid pin 5, since it is connected to timer 0.


+ recibe por osc los valores de velocidad para la pista de cada uno de los 4 clientes
+ envia el paso por vuelta para cada cliente (4)
+ controla el juego
- envia numero de vueltas
- cuando gana alguien
- estado de la partida

OSC

el mensaje ganador lo lanza cuando uno de los cuentavueltas llega al maximo
junto al mensaje manda un int con el numero de la pantalla ganadora 1-2-3-4
+ /ganador


*/
#define trackOneLap A1
#define trackTwoLap A2
#define trackTreeLap A3
#define trackFourLap A4

long minTiempoXvuelta = 1500; // tiempo para debiunce del sensor
int thresholdFotoInterruptor = 500; // si la lectura del interruptor es menor, pasa el coche

/// numero de vueltas de cada jugador
int vueltaPlayerOne = 0;
int vueltaPlayerTwo = 0;
int vueltaPlayerTree = 0;
int vueltaPlayerFour = 0;

// vueltas por partida
int vueltasPorCarrera = 9;

// tiempo desde la ultima vuelta de cada jugador
long ultimaLecturaPlayerOne = 0;
long ultimaLecturaPlayerTwo = 0;
long ultimaLecturaPlayerTree = 0;
long ultimaLecturaPlayerFour = 0;

OSCServer server;
OSCClient client;

// datos tcp osc del arduino
byte myMac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x62, 0x73 };
byte myIp[]  = { 192, 168, 0, 177 };
int  myPort  = 10000;

// direcciones ip de las tablet
byte tabletOneIp[] = { 192, 168, 0, 50 };
byte tabletTwoIp[] = { 192, 168, 0, 60 };
byte tabletTreeIp[] = { 192, 168, 0, 70 };
byte tabletFourIp[] = { 192, 168, 0, 80 };
int  tabletPort  = 12000;

// velocidades para cada una de las pistas
int speedOne = 0;
int speedTwo = 0;
int speedTree = 0;
int speedFour = 0;

// tiempo desde la ultima orden de cada player
// se usa para establecer un falisafe
long lastSpeedOneMsg = 0;
long lastSpeedTwoMsg = 0;
long lastSpeedThreeMsg = 0;
long lastSpeedFourMsg = 0;
long failsafeTime = 100;

// pines de los controladores de PWM
int E1 = 6;
int M1 = 5;

int E2 = 3;
int M2 = 4;

int E3 = 7;
int M3 = 8;

int E4 = 11;
int M4 = 12;

////
typedef enum{
  parado,
  cuentAtras,
  jugando,
  terminado,
} GameStatus;

////
typedef enum{
  ninguno,
  playerOne,
  playerTwo,
  playerTree,
  playerFour,
} Winner;

////
GameStatus estadoJuego = parado;
Winner ganador = ninguno;

// the timer object
SimpleTimer countDownTimer;

//--------------------------------------------------------------
void setup(){ 
 
 // pwm
 InitTimersSafe();
 SetPinFrequencySafe(E1, 60);
 SetPinFrequencySafe(E2, 60);
 SetPinFrequencySafe(E3, 60);
 SetPinFrequencySafe(E4, 60);
 pinMode(M1, OUTPUT); // TRACK ONE PWM PIN
 pinMode(M2, OUTPUT); // TRACK TWO PWM PIN
 pinMode(M3, OUTPUT); // TRACK TREE PWM PIN
 pinMode(M4, OUTPUT); // TRACK FOUR PWM PIN
 
  // serial pa debug
 Serial.begin(9600);
 
 // ethernete y osc
 Ethernet.begin(myMac ,myIp);
 
 server.begin(myPort);
 server.addCallback("/speedOne",&speedTrackOne);
 server.addCallback("/speedTwo",&speedTrackTwo);
 server.addCallback("/speedTree",&speedTrackThree);
 server.addCallback("/speedFour",&speedTrackFour);
 
}

//--------------------------------------------------------------
void loop(){
  if(server.aviableCheck()>0){
   //Serial.println("alive! "); 
  }
  
  /// comprobamos el paso por pista
  /// mirando los sensores opticos
  checkLapSensor();
  
  // miramos si alguien ha terminado
  checkForFinish();
  
  // tenemos un ganador????
  checkWinner();
  
  // FAIL SAFE
  checkFailSafe();
  
  // TRACK SPEED
  setSpeedTrackOne();
  setSpeedTrackTwo();
  setSpeedTrackTree();
  setSpeedTrackFour();
}

//--------------------------------------------------------------
void newGame(){
  resetLaps();
}

//--------------------------------------------------------------
void newCountDown(){
  
}

//--------------- PASO POR PISTA -------------------------------
//--------------------------------------------------------------

void checkLapSensor(){
  
  /// analog pins de los pasos por vuelta
  int t1 = analogRead( trackOneLap );
  int t2 = analogRead( trackTwoLap );
  int t3 = analogRead( trackTreeLap );
  int t4 = analogRead( trackFourLap );
  
  // sensor uno
  if(t1 < thresholdFotoInterruptor){
    // paso por meta
    if ((millis() - ultimaLecturaPlayerOne) > minTiempoXvuelta) {
        // envia el mensaje
        ultimaLecturaPlayerOne = millis();
        vueltaPlayerOne ++;
      }
  }
  
  // sensor dos
  if(t2 < thresholdFotoInterruptor){
    // paso por meta
    if ((millis() - ultimaLecturaPlayerTwo) > minTiempoXvuelta) {
        // envia el mensaje
        ultimaLecturaPlayerTwo = millis();
        vueltaPlayerTwo++;
      }
  } 
  
  // sensor tres
  if(t3 < thresholdFotoInterruptor){
    // paso por meta
    if ((millis() - ultimaLecturaPlayerTree) > minTiempoXvuelta) {
        // envia el mensaje
        ultimaLecturaPlayerTree = millis();
        vueltaPlayerTree++;
      }
  } 
  
  // sensor cuatro
  if(t4< thresholdFotoInterruptor){
    // paso por meta
    if ((millis() - ultimaLecturaPlayerFour) > minTiempoXvuelta) {
        // envia el mensaje
        ultimaLecturaPlayerFour = millis();
        vueltaPlayerFour++;
      }
  }
  
  
  
}

//------------------- resetLaps() ------------------------------
//--------------------------------------------------------------
void resetLaps(){
  vueltaPlayerOne = 0;
  vueltaPlayerTwo = 0;
  vueltaPlayerTree = 0;
  vueltaPlayerFour = 0;
  
  ganador = ninguno;
}

//---------------- checkForFinish() ----------------------------
//--------------------------------------------------------------
void checkForFinish(){
  /// compruebas que nadie haya acabado
  if(vueltaPlayerOne > vueltasPorCarrera){
    // gano el playerOne
    estadoJuego = terminado;
    ganador = playerOne;
  }
  
  if(vueltaPlayerTwo > vueltasPorCarrera){
    // gano el playerTwo
    estadoJuego = terminado;
    ganador = playerTwo;
  }
  
  if(vueltaPlayerTree > vueltasPorCarrera){
    // gano el playerTree
    estadoJuego = terminado;
    ganador = playerTree;
  }
 
  if(vueltaPlayerFour > vueltasPorCarrera){
    // gano el playerFour
    estadoJuego = terminado;
    ganador = playerFour;
  }
  
}

//---------------- checkWinner() -------------------------------
//--------------------------------------------------------------
void checkWinner(){
  if((ganador != ninguno) && (estadoJuego == terminado)){
    // alguien ha ganado y el estado de juego es terminado
    /// enviamos el mensaje al ganador
    
    OSCMessage winnerMsg;
    winnerMsg.beginMessage("/ganador");
    
    switch(ganador){
      case playerOne:
        // gano el uno, mandale un mensaje de winner
        winnerMsg.setAddress(tabletOneIp,tabletPort);
        winnerMsg.addArgInt32(1);
        client.send(&winnerMsg);
        
      break;
      
      case playerTwo:
        // gano el dos, mandale un mensaje de winner
        winnerMsg.setAddress(tabletTwoIp,tabletPort);
        winnerMsg.addArgInt32(2);
        client.send(&winnerMsg);
        
      break;
      
      case playerTree:
        // gano el tres, mandale un mensaje de winner
        winnerMsg.setAddress(tabletTreeIp,tabletPort);
        winnerMsg.addArgInt32(3);
        client.send(&winnerMsg);
        
      break;
      
      case playerFour:
        // gano el cuatro, mandale un mensaje de winner
        winnerMsg.setAddress(tabletFourIp,tabletPort);
        winnerMsg.addArgInt32(4);
        client.send(&winnerMsg);
        
      break;
      
    }
    
  }
  
}


//-------------- CONTROLES PISTA -------------------------------
//--------------------------------------------------------------
void setSpeedTrackOne(){
  digitalWrite(M1,HIGH); // DIRECTION
  pwmWrite(E1, speedOne); // SPEED
}
//--------------------------------------------------------------
void setSpeedTrackTwo(){
  digitalWrite(M2,HIGH); // DIRECTION
  pwmWrite(E2, speedTwo); // SPEED
}
//--------------------------------------------------------------
void setSpeedTrackTree(){
  digitalWrite(M3,HIGH); // DIRECTION
  pwmWrite(E3, speedTree); // SPEED
}
//--------------------------------------------------------------
void setSpeedTrackFour(){
  digitalWrite(M4,HIGH); // DIRECTION
  pwmWrite(E4, speedFour); // SPEED
}




//-------------------------- FAILSAFE COCHES --------------------------
//--------------------------------------------------------------------
void checkFailSafe(){
  // si en un segundo no hay msg en una pista la ponemos a 0
  if((millis() - lastSpeedOneMsg) > failsafeTime){
    speedOne = 0;
  }
  
  if((millis() - lastSpeedTwoMsg) > failsafeTime){
    speedTwo = 0;
  }
  
  if((millis() - lastSpeedThreeMsg) > failsafeTime){
    speedTree = 0;
  }
  
  if((millis() - lastSpeedFourMsg) > failsafeTime){
    speedFour = 0;
  }
  
}



//-------------- DATOS VELOCIDAD QUE RECIBE POR OSC --------------
//----------------------------------------------------------------
void speedTrackOne(OSCMessage *_mes){
    speedOne = _mes->getArgInt32(0);
    lastSpeedOneMsg = millis();
    //Serial.println("speedOne " + speedOne); 
}

//--------------------------------------------------------------
void speedTrackTwo(OSCMessage *_mes){
    speedTwo = _mes->getArgInt32(0);
    lastSpeedTwoMsg = millis();
    //Serial.println("speedTwo " + speedTwo); 
}

//--------------------------------------------------------------
void speedTrackThree(OSCMessage *_mes){
    speedTree = _mes->getArgInt32(0);
    lastSpeedThreeMsg = millis();
    //Serial.println("speedTree " + speedTree); 
}

//--------------------------------------------------------------
void speedTrackFour(OSCMessage *_mes){ 
    speedFour = _mes->getArgInt32(0);
    lastSpeedFourMsg = millis();
    //Serial.println("speedFour " + speedFour); 
}
