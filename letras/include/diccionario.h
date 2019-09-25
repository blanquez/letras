#ifndef DICCIONARIO_H
#define DICCIONARIO_H

#include <iostream>
#include <cstring>
#include <set>
#include <vector>
#include "conjuntoletras.h"

using namespace std;

class Diccionario{
public:
	static char modo;
	static ConjuntoLetras conjunto;
private:
	struct classcomp{
		bool operator()(const string lhs, const string rhs) const{
			if(modo=='L') return strlen(lhs.c_str())>strlen(rhs.c_str());
			else{
				int men=0, may=0;
				for(int i=0;i<strlen(lhs.c_str());++i)
					men += conjunto.puntuacion(lhs[i]);
				for(int i=0;i<strlen(rhs.c_str());++i)
					may += conjunto.puntuacion(rhs[i]);
				return men>may;
			}
		}
	};

	multiset<string,classcomp> diccionario;
public:

	/**
		@brief Constructor de Diccionario
	**/
	Diccionario(){}

	/**
		@brief Prepara el diccionario para mejorar su eficiencia
		@param corte: numero maximo de puntuacion o longitud en el juego
	**/
	void preparar(int corte){
		multiset<string,classcomp>::iterator it = diccionario.begin();
		if(modo=='L'){
			while(it!=diccionario.end() && strlen((*it).c_str())>corte)
				++it;
			diccionario.erase(diccionario.begin(), it);
		}
		else{
			int punt=0;
			for(int i=0;i<strlen((*it).c_str());++i)
					punt += conjunto.puntuacion((*it)[i]);
			while(it!=diccionario.end() && punt>corte){
				++it;
				punt=0;
				for(int i=0;i<strlen((*it).c_str());++i)
					punt += conjunto.puntuacion((*it)[i]);
			}
			diccionario.erase(diccionario.begin(), it);
		}
	}

	/**
		@brief Obtiene el tamanio del Diccionario
		@return un entero con el tamanio del Diccionario
	**/
	inline int size(){
		return diccionario.size();
	}

	/**
		@brief Inserta una palabra al Diccionario
		@param in: string a insertar
	**/
	void insert(string in){
		diccionario.insert(in);
	}

	/**
		@brief Obtiene todas las palabras en el diccionario de un longitud dada
		@param longitud: la longitud de las palabras de salida
		@return un vector con las palabras de longitud especifica en el parametro de entrada
	**/
	vector<string> PalabrasLongitud(int longitud){
		vector<string> resultado;
		set<string,classcomp>::iterator it;
		it=diccionario.begin();
		while(strlen((*it).c_str()) != longitud && it != diccionario.end()){
			++it;
		}
		while(strlen((*it).c_str()) == longitud && it != diccionario.end()){
			resultado.push_back(*it);
			++it;
		}
		return resultado;
	}

	/**
		@brief Indica si una palabra está en el diccionario o no
		@param palabra: la palabra que se quiere buscar
		@return true si la palabra esta en el diccionario. False en caso contrario
	**/
	bool Esta(string p){
		multiset<string,classcomp>::iterator it;
		for(it=diccionario.begin();it!=diccionario.end();++it){
			if(strcmp(p.c_str(),(*it).c_str())==0)
				return true;
		}
		return false;
	}

	/**
		@brief Busca la mejor palabra en el diccionario a partir de un vector de letras
		@param letras: array de char con las letras que han de componer la palabra
		@return un string con la palabra encontrada, devuelve un espacio si no hay ninguna
	**/
	string buscarPalabra(vector<char> letras){
		multiset<string,classcomp>::iterator it;
		multiset<char>::iterator mit;
		multiset<char> conj;
		bool correcto;
		for(int i=0;i<letras.size();++i)
			conj.insert(letras[i]);
		multiset<char> palabra;
		for(it=diccionario.begin();it!=diccionario.end();++it){
			for(int i=0;i<(*it).size();++i)
				palabra.insert((*it)[i]);
			correcto=true;
			for(mit=palabra.begin();mit!=palabra.end();++mit){
				if(palabra.count(*mit)>conj.count(*mit)){
					correcto=false;
					break;
				}
			}
			if(correcto) return (*it);
			palabra.clear();
		}
		return " ";
	}

    class iterator{
	private:
		multiset<string,classcomp>::iterator it;
	public:
		iterator(){}
		string operator *(){
			return *it;
		}
		iterator & operator ++(){
			it++;
			return *this;
		}

		iterator & operator=(const iterator &i){
			it=i.it;
			return *this;
		}

		bool operator ==(const iterator &i){
			return it==i.it;
		}
		bool operator !=(const iterator &i){
			return it!=i.it;
		}
		friend class Diccionario;
	};

	iterator begin(){
		Diccionario::iterator it;
		it.it=diccionario.begin();
		return it;
	}

	iterator end(){
		Diccionario::iterator it;
		it.it=diccionario.end();
		return it;
	}

	/**
		@brief Operador de entrada
	**/
	friend istream& operator >> (istream& in, Diccionario& v){
		string entrada;
		while(getline(in,entrada))
			v.insert(entrada);
		return in;
	}

	/**
		@brief Operador de salida
	**/
    friend ostream& operator << (ostream& out, Diccionario& v){
   		Diccionario::iterator it;
   		for(it=v.begin();it != v.end();++it)
   			out << *it << endl;
   		return out;
    }
};

#endif