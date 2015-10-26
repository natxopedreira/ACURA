//
//  game.h
//  leapTest
//
//  Created by Natxo Pedreira gonzalez on 22/9/15.
//
//

#ifndef leapTest_game_h
#define leapTest_game_h

#include "ofMain.h"
#include "ofxOsc.h"

class game {
    
private:
    
    int numeroVueltas;
    int vueltaNum;
    
    ofxOscReceiver receptorOsc;
    int puertoOsc = 12000;
    
    long tiempoLastOsc = 0;
    
    string direccionCuentaVueltas = "/trackOneLap";
    
    //--------------------------------------------------------------
    void miraEstado(){
        
        // si acabo la ultima vuelta
        if(vueltaNum == numeroVueltas){
            // se acabo la partida
            gameStatus = FINISHED;
        }
    }
    
    //--------------------------------------------------------------
    void resetPartida(){
        gameStatus = READY_TO_RUN;
        
        // reseteamos el contador a la primera vuelta
        vueltaNum = 1;
    }
    
public:
    enum estadoPartida {
        READY_TO_RUN, // esta listo para comenzar
        COUNTDOWN, // lanza la cuenta atras
        RACING, // manda datos al ardu para controlar los coches
        FINISHED // se acabo, muestra el ganador
    };
    
    estadoPartida gameStatus;
    
    //--------------------------------------------------------------
    void setup(string _dirCuentaVueltas){
        // escucha al ardu por osc
        receptorOsc.setup(puertoOsc);
        
        // direccion pa escuchar por osc al cuentavueltas
        direccionCuentaVueltas = _dirCuentaVueltas;
        
        // partida a 10 vueltas
        numeroVueltas = 10;
        
        // iniciamos el juego listo para correr
        gameStatus = READY_TO_RUN;
    }
    
    //--------------------------------------------------------------
    void update(){
        // mira si hay mensajes
        while(receptorOsc.hasWaitingMessages()){
            
            // get the next message
            ofxOscMessage m;
            receptorOsc.getNextMessage(&m);
            
            if(m.getAddress() == direccionCuentaVueltas){
                // el mensaje es para nosotros
                
                if ((ofGetElapsedTimeMillis() - tiempoLastOsc ) > 2000) {
                    // miramos cuanto hace del ultimo
                    // si es mas de dos segundo nos vale
                    tiempoLastOsc = ofGetElapsedTimeMillis();
                    
                    // una vuelta mas
                    vueltaNum ++;
                }
                
                // actualizamos el estado
                miraEstado();

            }
        }
        
        
    }

    
};
#endif
