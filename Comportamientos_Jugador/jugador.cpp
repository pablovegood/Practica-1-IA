#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
using namespace std;



Action ComportamientoJugador::think(Sensores sensores){

	Action accion = actIDLE;
	int a;
	
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC << " ";
	switch(sensores.sentido){
		case 0: cout << "Norte" << endl; break;
		case 1: cout << "Noreste" << endl; break;
		case 2: cout << "Este" << endl; break;
		case 3: cout << "Sureste" << endl; break;
		case 4: cout << "Sur " << endl; break;
		case 5: cout << "Suroeste" << endl; break;
		case 6: cout << "Oeste" << endl; break;
		case 7: cout << "Noroeste" << endl; break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];
	cout << endl;

	cout << "Superficie: ";
	for (int i=0; i<sensores.superficie.size(); i++)
		cout << sensores.superficie[i];
	cout << endl;

	cout << "Colisión: " << sensores.colision << endl;
	cout << "Reset: " << sensores.reset << endl;
	cout << "Vida: " << sensores.vida << endl;
	cout << endl;


	if(sensores.reset ==  true){ 
		bien_situado = false;
		bikini = false;
		zapatillas = false;	
	}	


	// Determinar el efecto de la ultima accion enviada
	switch(last_action){
		case actFORWARD: 
			//Actualización en caso de avanzar
			switch(current_state.brujula){
				case norte: current_state.fil--; break;
				case noreste: current_state.fil--; current_state.col++; break;
				case este: current_state.col++; break;
				case sureste: current_state.fil++; current_state.col++; break;
				case sur: current_state.fil++; break;
				case suroeste: current_state.fil++; current_state.col--; break;
				case oeste: current_state.col--; break;
				case noroeste: current_state.fil--; current_state.col--; break;
			}
			break;
		case actTURN_SL: 
			//Actualización en caso de girar 45º a la izquierda
			a = current_state.brujula;
			a = (a+7)%8;
			current_state.brujula =static_cast<Orientacion>(a);
			break;
		case actTURN_SR: 
			//Actualización en caso de girar 45º a la derecha
			a = current_state.brujula;
			a = (a+1)%8;
			current_state.brujula =static_cast<Orientacion>(a);
			break;
		case actTURN_BL:
			//Actualización en caso de girar 135º a la izquierda
			a = current_state.brujula;
			a = (a+5)%8;
			current_state.brujula =static_cast<Orientacion>(a);
			break;
		case actTURN_BR: 
			//Actualización en caso de girar 135º a la derecha
			a = current_state.brujula;
			a = (a+3)%8;
			current_state.brujula =static_cast<Orientacion>(a);
			break;
	}
	
	if(sensores.terreno[0] == 'G' and !bien_situado){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true; 
	}
	
	if(sensores.terreno[0] == 'K'){
		bikini = true;
	}
	
	if(sensores.terreno[0] == 'D'){
		zapatillas = true;
	}
	
	if(sensores.terreno[0] == 'X'){
		while(sensores.bateria < 5000){
			accion = actIDLE;
			sensores.bateria += 10;
		}
	}
	
	if(inicia_exploracion == true){	
		PonerPrecipiciosEnMatriz(mapaResultado);
		inicia_exploracion = false;
	}
	
	if(sensores.nivel == 0){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		bien_situado = true;
	} 
	
	if(bien_situado)
		PonerTerrenoEnMatriz(sensores.terreno, current_state, mapaResultado);
	
	
	// Decidir la nueva acción	
	if((sensores.terreno[3] == 'M' && sensores.terreno[7] == 'M' && sensores.terreno[6] == 'M' && !estoy_encerrado) || sensores.bateria < 2800){
		estoy_encerrado = true;
	}
	
	if(estoy_encerrado == true && (sensores.terreno[1] == 'S' || sensores.terreno[3] == 'T') && (sensores.terreno[5] == 'M' || sensores.terreno[5] == 'P') ){ 
		accion = actTURN_SL;
	}else if(sensores.terreno[0] == 'B' && !zapatillas){
		if(sensores.terreno[1] == ('S' || 'G' || 'K' || 'X' || 'D' || 'T')){
			accion = actTURN_SL;
		}else if(sensores.terreno[3] == ('S' || 'G' || 'K' || 'X' || 'D' || 'T')){
			accion = actTURN_SR;
		}else if(sensores.superficie[2] == '_'){
			accion = actFORWARD;
		}
	}else if(sensores.terreno[0] == 'A' && bikini == false && sensores.superficie[2] == '_'){		
		accion = actFORWARD;
	}else if((sensores.terreno[1] == 'K' && bikini == false) or (sensores.terreno[1] == 'G' && bien_situado == false) or
	   (sensores.terreno[1] == 'D' && zapatillas == false) or (sensores.terreno[1] == 'X' && sensores.bateria < 3500)){
		accion = actTURN_SL;
	}else if((sensores.terreno[3] == 'K' && bikini == false) ||(sensores.terreno[3] == 'G' && bien_situado == false) ||
	   (sensores.terreno[3] == 'D' && zapatillas == false) || (sensores.terreno[3] == 'X' && sensores.bateria < 3500)){
		accion = actTURN_SR;
	}else if((sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S'
		or sensores.terreno[2] == 'G' or sensores.terreno[2] == 'K' 
		or sensores.terreno[2] == 'D' or (sensores.terreno[2] == 'B' && zapatillas == true)
		or sensores.terreno[2] == 'X' or sensores.terreno[2] == 'A' && bikini == true) and sensores.superficie[2] == '_'){
	    accion = actFORWARD;
	}else if(!girar_derecha){	
		accion = actTURN_SL;
		girar_derecha = (rand()%2 == 0);
		girar_mas_derecha = (rand()%2 == 0);
		girar_mas_izquierda = (rand()%2 == 0);
	}else if(girar_mas_derecha){
		accion = actTURN_BR;
		girar_derecha = (rand()%2==0);
		girar_mas_derecha = (rand()%2 == 0);
		girar_mas_izquierda = (rand()%2 == 0);	
	}else if (girar_mas_izquierda){
		accion = actTURN_BL;
		girar_derecha = (rand()%2==0);
		girar_mas_derecha = (rand()%2 == 0);	
		girar_mas_izquierda = (rand()%2 == 0);	
	}else{
		accion = actTURN_SR;
		girar_derecha = (rand()%2==0);
		girar_mas_derecha = (rand()%2 == 0);
		girar_mas_izquierda = (rand()%2 == 0);
	} 

	// Recordar la última acción
	last_action = accion;	
		
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}

