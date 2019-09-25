#ifndef CONJUNTOLETRAS_H
#define CONJUNTOLETRAS_H

#include <iostream>
#include <map>
using namespace std;

int PUNT_MAX=10;

struct Letra{
		int repeticiones;
		int puntuacion;
	};

class ConjuntoLetras{
private:
	map<char,Letra> letras;
public:
	/**
		@brief Constructor por defecto de ConjuntoLetras
	**/
	ConjuntoLetras(){}

	/**
		@brief Inserta una nueva entrada en el conjunto
		@param car: caracter a insertar
		@param rep: cuantas veces se repite el caracter car
		@param punt: puntuacion del caracter car
	**/
	void asignarLetra(char car, int rep, int punt){
		Letra anadir={rep,punt};
		letras[car]=anadir;
	}

	/**
		@brief Obtiene el tamaño del conjunto
		@return un entero que contiene el tamanio del conjunto
	**/
	inline int size(){
		return letras.size();
	}

	/**
		@brief Obtiene la puntuacion de un caracter en concreto
		@param car: caracter en concreto
		@return un entero con la puntuacion de car
	**/
	inline int puntuacion(char car){
		return letras[car].puntuacion;
	}
	
	/**
		@brief Obtiene la puntuacion maxima
		@return un entero con la puntuacion maxima
	**/
	inline int puntuacion_maxima(){
		return PUNT_MAX;
	}

	/**
		@brief Obtiene las repeticiones de un caracter en concreto
		@param car: caracter en concreto
		@return un entero con las repeticiones de car
	**/
	inline int repeticiones(char car){
		return letras[car].repeticiones;
	}

	/**
		@brief Operador de asignacion
		@param otro: el ConjuntoLetras a asginar
		@return el resultado de la asignacion
	**/
	ConjuntoLetras& operator=(ConjuntoLetras &otro){
		letras=otro.letras;
		return *this;
	}

	/**
		@brief Operador []
		@param a: caracter a buscar
		@return un struct Letra con la puntuacion y las repeticiones de a
	**/
	inline Letra& operator[](char a){
		return letras[a];
	}

	/**
		@brief Operador de entrada
	**/
	friend istream& operator>>(istream& in, ConjuntoLetras& v){
		char car;
		int rep;
		int punt;
		in.ignore(22,'\n');
		for(int i=0;i<26;++i){
			in >> car;
			in >> rep;
			in >> punt;
			v.asignarLetra(car,rep,punt);
		}
		return in;
	}

	/**
		@brief Operador de salida
	**/
    friend ostream& operator << (ostream& out, ConjuntoLetras& v){
    	out << "******Puntuaciones******" << endl;
    	char a='a';
    	for(int i=0;i<26;++i){
    		out << a << "\t" << v.puntuacion(a) << endl;
    		a++;
    	}
    	return out;
    }
};


#endif