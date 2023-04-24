#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;


struct state{
	int fil;
	int col;
	Orientacion brujula;
};



class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
	current_state.fil = 99;
	current_state.col = 99;
	current_state.brujula = norte;
	last_action = actIDLE;
	girar_derecha = false;
	girar_mas_derecha = false;
	girar_mas_izquierda = false;
	bien_situado = false;
	zapatillas = false;
	bikini =false;
	inicia_exploracion = true;
	estoy_encerrado = false; 
    }

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    
    
    void PonerPrecipiciosEnMatriz(vector<vector<unsigned char>> & matriz){
    	for(int i = 0; i < 3; ++i)	// Pintamos la franja de 3 filas superior de la matriz
    		for(int j = 0; j < matriz.size(); ++j)
    			matriz[i][j] = 'P';
    		
  	
    	for(int i = matriz.size()-3; i < matriz.size(); i++)	// Pintamos la franja de 3 filas inferior de la matriz
    		for(int j = 0; j < matriz.size(); j++)
    			matriz[i][j] = 'P';	
    			
      	for(int i = 3; i < matriz.size()-3; i++)	// Pintamos la franja de 3 columnas izquierda de la matriz
    		for(int j = 0; j < 3; j++)
    			matriz[i][j] = 'P';	
    	
    	for(int i = 3; i < matriz.size()-3; i++)	// Pintamos la franja de 3 columnas derecha de la matriz
    		for(int j = matriz.size()-3; j < matriz.size(); j++)
    			matriz[i][j] = 'P';	
    }


    
    void PonerTerrenoEnMatriz(const vector<unsigned char> & terreno, const state &st,
    				vector<vector<unsigned char>> & matriz){
    	// Extiende esta versión inicial donde solo se pone la componente 0 en matriz
    	//a poner todas las componentes de terreno en función de la orientación del agente
    	matriz[st.fil][st.col] = terreno[0];
    	switch(current_state.brujula){
				case norte: 
					matriz[st.fil-1][st.col-1] = terreno[1];
					matriz[st.fil-1][st.col] = terreno[2];
					matriz[st.fil-1][st.col+1] = terreno[3];
					matriz[st.fil-2][st.col-2] = terreno[4];
					matriz[st.fil-2][st.col-1] = terreno[5];
					matriz[st.fil-2][st.col] = terreno[6];
					matriz[st.fil-2][st.col+1] = terreno[7];
					matriz[st.fil-2][st.col+2] = terreno[8];
					matriz[st.fil-3][st.col-3] = terreno[9];
					matriz[st.fil-3][st.col-2] = terreno[10];
					matriz[st.fil-3][st.col-1] = terreno[11];
					matriz[st.fil-3][st.col] = terreno[12];
					matriz[st.fil-3][st.col+1] = terreno[13];
					matriz[st.fil-3][st.col+2] = terreno[14];
					matriz[st.fil-3][st.col+3] = terreno[15];
					break;
				case noreste:  
					matriz[st.fil-1][st.col] = terreno[1];
					matriz[st.fil-1][st.col+1] = terreno[2];
					matriz[st.fil][st.col+1] = terreno[3];
					matriz[st.fil-2][st.col] = terreno[4];
					matriz[st.fil-2][st.col+1] = terreno[5];
					matriz[st.fil-2][st.col+2] = terreno[6];
					matriz[st.fil-1][st.col+2] = terreno[7];
					matriz[st.fil][st.col+2] = terreno[8];
					matriz[st.fil-3][st.col] = terreno[9];
					matriz[st.fil-3][st.col+1] = terreno[10];
					matriz[st.fil-3][st.col+2] = terreno[11];
					matriz[st.fil-3][st.col+3] = terreno[12];
					matriz[st.fil-2][st.col+3] = terreno[13];
					matriz[st.fil-1][st.col+3] = terreno[14];
					matriz[st.fil][st.col+3] = terreno[15];
					break;
				case este: 
					matriz[st.fil-1][st.col+1] = terreno[1];
					matriz[st.fil][st.col+1] = terreno[2];
					matriz[st.fil+1][st.col+1] = terreno[3];
					matriz[st.fil-2][st.col+2] = terreno[4];
					matriz[st.fil-1][st.col+2] = terreno[5];
					matriz[st.fil][st.col+2] = terreno[6];
					matriz[st.fil+1][st.col+2] = terreno[7];
					matriz[st.fil+2][st.col+2] = terreno[8];
					matriz[st.fil-3][st.col+3] = terreno[9];
					matriz[st.fil-2][st.col+3] = terreno[10];
					matriz[st.fil-1][st.col+3] = terreno[11];
					matriz[st.fil][st.col+3] = terreno[12];
					matriz[st.fil+1][st.col+3] = terreno[13];
					matriz[st.fil+2][st.col+3] = terreno[14];
					matriz[st.fil+3][st.col+3] = terreno[15];
					break;
				case sureste:
					matriz[st.fil][st.col+1] = terreno[1];
					matriz[st.fil+1][st.col+1] = terreno[2];
					matriz[st.fil+1][st.col] = terreno[3];
					matriz[st.fil][st.col+2] = terreno[4];
					matriz[st.fil+1][st.col+2] = terreno[5];
					matriz[st.fil+2][st.col+2] = terreno[6];
					matriz[st.fil+2][st.col+1] = terreno[7];
					matriz[st.fil+2][st.col] = terreno[8];
					matriz[st.fil][st.col+3] = terreno[9];
					matriz[st.fil+1][st.col+3] = terreno[10];
					matriz[st.fil+2][st.col+3] = terreno[11];
					matriz[st.fil+3][st.col+3] = terreno[12];
					matriz[st.fil+3][st.col+2] = terreno[13];
					matriz[st.fil+3][st.col+1] = terreno[14];
					matriz[st.fil+3][st.col] = terreno[15]; 
					break;
				case sur:
					matriz[st.fil+1][st.col+1] = terreno[1];
					matriz[st.fil+1][st.col] = terreno[2];
					matriz[st.fil+1][st.col-1] = terreno[3];
					matriz[st.fil+2][st.col+2] = terreno[4];
					matriz[st.fil+2][st.col+1] = terreno[5];
					matriz[st.fil+2][st.col] = terreno[6];
					matriz[st.fil+2][st.col-1] = terreno[7];
					matriz[st.fil+2][st.col-2] = terreno[8];
					matriz[st.fil+3][st.col+3] = terreno[9];
					matriz[st.fil+3][st.col+2] = terreno[10];
					matriz[st.fil+3][st.col+1] = terreno[11];
					matriz[st.fil+3][st.col] = terreno[12];
					matriz[st.fil+3][st.col-1] = terreno[13];
					matriz[st.fil+3][st.col-2] = terreno[14];
					matriz[st.fil+3][st.col-3] = terreno[15];
					break;
				case suroeste:  
					matriz[st.fil+1][st.col] = terreno[1];
					matriz[st.fil+1][st.col-1] = terreno[2];
					matriz[st.fil][st.col-1] = terreno[3];
					matriz[st.fil+2][st.col] = terreno[4];
					matriz[st.fil+2][st.col-1] = terreno[5];
					matriz[st.fil+2][st.col-2] = terreno[6];
					matriz[st.fil+1][st.col-2] = terreno[7];
					matriz[st.fil][st.col-2] = terreno[8];
					matriz[st.fil+3][st.col] = terreno[9];
					matriz[st.fil+3][st.col-1] = terreno[10];
					matriz[st.fil+3][st.col-2] = terreno[11];
					matriz[st.fil+3][st.col-3] = terreno[12];
					matriz[st.fil+2][st.col-3] = terreno[13];
					matriz[st.fil+1][st.col-3] = terreno[14];
					matriz[st.fil][st.col-3] = terreno[15]; 
					break;
				case oeste:
					matriz[st.fil+1][st.col-1] = terreno[1];
					matriz[st.fil][st.col-1] = terreno[2];
					matriz[st.fil-1][st.col-1] = terreno[3];
					matriz[st.fil+2][st.col-2] = terreno[4];
					matriz[st.fil+1][st.col-2] = terreno[5];
					matriz[st.fil][st.col-2] = terreno[6];
					matriz[st.fil-1][st.col-2] = terreno[7];
					matriz[st.fil-2][st.col-2] = terreno[8];
					matriz[st.fil+3][st.col-3] = terreno[9];
					matriz[st.fil+2][st.col-3] = terreno[10];
					matriz[st.fil+1][st.col-3] = terreno[11];
					matriz[st.fil][st.col-3] = terreno[12];
					matriz[st.fil-1][st.col-3] = terreno[13];
					matriz[st.fil-2][st.col-3] = terreno[14];
					matriz[st.fil-3][st.col-3] = terreno[15];
					break; 
				case noroeste:  
					matriz[st.fil][st.col-1] = terreno[1];
					matriz[st.fil-1][st.col-1] = terreno[2];
					matriz[st.fil-1][st.col] = terreno[3];
					matriz[st.fil][st.col-2] = terreno[4];
					matriz[st.fil-1][st.col-2] = terreno[5];
					matriz[st.fil-2][st.col-2] = terreno[6];
					matriz[st.fil-2][st.col-1] = terreno[7];
					matriz[st.fil-2][st.col] = terreno[8];
					matriz[st.fil][st.col-3] = terreno[9];
					matriz[st.fil-1][st.col-3] = terreno[10];
					matriz[st.fil-2][st.col-3] = terreno[11];
					matriz[st.fil-3][st.col-3] = terreno[12];
					matriz[st.fil-3][st.col-2] = terreno[13];
					matriz[st.fil-3][st.col-1] = terreno[14];
					matriz[st.fil-3][st.col] = terreno[15]; 
					break;
			}				
    
    }
 
  private:
  
  // Declarar aquí las variables de estado
	state current_state;
	Action last_action; 
	bool girar_derecha;
	bool girar_mas_derecha;
	bool girar_mas_izquierda;
	bool bien_situado;
	bool bikini;
	bool zapatillas;
	bool inicia_exploracion;
	bool estoy_encerrado;
	
};

#endif
